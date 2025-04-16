#pragma once

#include <optional>
#include <pqxx/pqxx>
#include <string>
#include <vector>

struct Client {
  int id;
  std::string firstName;
  std::string lastName;
  std::string email;
  std::vector<std::string> phones;
};

class DatabaseException : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class ConnectionException : public DatabaseException {
public:
  using DatabaseException::DatabaseException;
};

class InvalidQueryException : public DatabaseException {
public:
  using DatabaseException::DatabaseException;
};

class ClientManager {
public:
  explicit ClientManager(const std::string &connStr);
  void createTables() const;
  int addClient(const std::string &firstName, const std::string &lastName,
                const std::string &email) const;
  void addPhone(int clientId, const std::string &phone) const;
  auto updateClient(const int clientId,
                    const std::optional<std::string> &firstName,
                    const std::optional<std::string> &lastName,
                    const std::optional<std::string> &email) const->void;
  void deletePhone(int clientId, const std::string &phone) const;
  void deleteClient(int clientId) const;

  std::vector<Client>
  findClients(const std::optional<std::string> &firstName,
              const std::optional<std::string> &lastName,
              const std::optional<std::string> &email,
              const std::optional<std::string> &phone) const;

private:
  std::unique_ptr<pqxx::connection> conn;

  void validateClientExists(int clientId);
  void validatePhoneExists(int clientId, const std::string &phone);
};