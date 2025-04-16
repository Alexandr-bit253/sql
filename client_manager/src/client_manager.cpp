#include "../include/client_manager.hpp"
#include <iostream>
#include <stdexcept>

ClientManager::ClientManager(const std::string &connStr) {
  try {
    conn = std::make_unique<pqxx::connection>(connStr);
  } catch (const pqxx::sql_error &e) {
    throw ConnectionException("Connection " + connStr +
                              " failed: " + std::string(e.what()));
  } catch (const std::exception &e) {
    throw ConnectionException("Connection " + connStr +
                              "error: " + std::string(e.what()));
  }
}

void ClientManager::createTables() const {
  try {
    pqxx::work txn(*conn);

    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS clients (
            id SERIAL PRIMARY KEY,
            first_name TEXT,
            last_name TEXT,
            email TEXT UNIQUE
        );
    )");

    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS phones (
            id SERIAL PRIMARY KEY,
            client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE,
            phone TEXT
        );
    )");

    txn.commit();
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in createTables: " +
                            std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in createTables: " + std::string(e.what()));
  }
}

int ClientManager::addClient(const std::string &firstName,
                             const std::string &lastName,
                             const std::string &email) const {
  try {
    int clientId{};

    pqxx::work txn(*conn);

    const pqxx::result res =
        txn.exec_params("INSERT INTO clients (first_name, last_name, email) "
                        "VALUES ($1, $2, $3) RETURNING id;",
                        firstName, lastName, email);

    clientId = res[0][0].as<int>();
    txn.commit();

    return clientId;
  } catch (const pqxx::unique_violation &e) {
    throw InvalidQueryException("Email already exists: " + email);
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in addClient: " + std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in addClient: " + std::string(e.what()));
  }
}

void ClientManager::addPhone(int clientId, const std::string &phone) const {
  if (phone.empty()) {
    throw InvalidQueryException("Phone number cannot be empty");
  }
  try {
    pqxx::work txn(*conn);

    txn.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2);",
                    clientId, phone);
    txn.commit();
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in addPhone: " + std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in addPhone: " + std::string(e.what()));
  }
}

void ClientManager::updateClient(
    const int clientId, const std::optional<std::string> &firstName,
    const std::optional<std::string> &lastName,
    const std::optional<std::string> &email) const {
  if (!firstName && !lastName && !email) {
    throw InvalidQueryException(
        "At least one field must be provided for update");
  }

  try {
    pqxx::work txn(*conn);
    std::ostringstream query{};
    query << "UPDATE clients SET ";
    bool first{true};
    if (firstName) {
      query << "first_name = " << txn.quote(*firstName);
      first = false;
    }
    if (lastName) {
      if (!first)
        query << ", ";
      query << "last_name = " << txn.quote(*lastName);
      first = false;
    }
    if (email) {
      if (!first)
        query << ", ";
      query << "email = " << txn.quote(*email);
    }
    query << " WHERE id = " << clientId;

    txn.exec(query.str());
    txn.commit();
  } catch (const pqxx::unique_violation &e) {
    throw InvalidQueryException("Email already exists: " +
                                (email ? *email : ""));
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in updateClient: " +
                            std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in updateClient: " + std::string(e.what()));
  }
}

void ClientManager::deletePhone(int clientId, const std::string &phone) const {
  try {
    pqxx::work txn(*conn);
    txn.exec_params("DELETE FROM phones WHERE client_id = $1 AND phone = $2;",
                    clientId, phone);
    txn.commit();
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in deletePhone: " +
                            std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in deletePhone: " + std::string(e.what()));
  }
}

void ClientManager::deleteClient(int clientId) const {
  try {
    pqxx::work txn(*conn);
    txn.exec_params("DELETE FROM clients WHERE id = $1;", clientId);
    txn.commit();
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in deleteClient: " +
                            std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in deleteClient: " + std::string(e.what()));
  }
}

std::vector<Client>
ClientManager::findClients(const std::optional<std::string> &firstName,
                           const std::optional<std::string> &lastName,
                           const std::optional<std::string> &email,
                           const std::optional<std::string> &phone) const {
  try {
    pqxx::work txn(*conn);
    std::ostringstream query;
    query << R"(
        SELECT c.id, c.first_name, c.last_name, c.email, p.phone
        FROM clients c
        LEFT JOIN phones p ON c.id = p.client_id
  )";

    std::vector<std::string> conditions;
    if (firstName)
      conditions.push_back("c.first_name = " + txn.quote(*firstName));
    if (lastName)
      conditions.push_back("c.last_name = " + txn.quote(*lastName));
    if (email)
      conditions.push_back("c.email = " + txn.quote(*email));
    if (phone)
      conditions.push_back("c.phone = " + txn.quote(*phone));

    if (!conditions.empty()) {
      query << " WHERE ";
      for (size_t i = 0; i < conditions.size(); ++i) {
        if (i > 0)
          query << " AND ";
        query << conditions[i];
      }
    }

    const auto result = txn.exec(query.str());

    std::map<int, Client> clientMap;
    for (const auto &row : result) {
      int id = row[0].as<int>();
      auto &client = clientMap[id];
      client.id = id;
      client.firstName = row[1].as<std::string>();
      client.lastName = row[2].as<std::string>();
      client.email = row[3].as<std::string>();
      if (!row[4].is_null()) {
        client.phones.push_back(row[4].as<std::string>());
      }
    }

    std::vector<Client> clients;
    for (auto &[_, c] : clientMap) {
      clients.push_back(std::move(c));
    }

    return clients;
  } catch (const pqxx::sql_error &e) {
    throw DatabaseException("SQL error in findClients: " +
                            std::string(e.what()));
  } catch (const std::exception &e) {
    throw DatabaseException("Error in findClients: " + std::string(e.what()));
  }
}
