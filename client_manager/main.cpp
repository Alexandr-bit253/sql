#include <iostream>

#include "include/client_manager.hpp"
#include "include/env_loader.hpp"

int main() {
  try {
    auto env = loadEnvFile(".env");

    const std::string connStr =
        "host=" + env["DB_HOST"] + " port=" + env["DB_PORT"] +
        " dbname=" + env["DB_NAME"] + " user=" + env["DB_USER"] +
        " password=" + env["DB_PASSWORD"];

    ClientManager manager(connStr);

    manager.createTables();

    const int id = manager.addClient("Александр", "Котов", "alex@example.com");
    std::cout << "Add client. ID = " << id << std::endl;

    manager.addPhone(id, "+79991234567");
    manager.addPhone(id, "+78889998877");

    manager.updateClient(id, std::nullopt, std::make_optional("Котов"),
                         std::nullopt);

    auto found = manager.findClients(std::nullopt, std::nullopt,
                                     "alex@example.com", std::nullopt);
    for (const auto &client : found) {
      std::cout << "Client found: " << client.firstName << " "
                << client.lastName << " (" << client.email << ")" << std::endl;
      for (const auto &phone : client.phones) {
        std::cout << "  Phone: " << phone << std::endl;
      }
    }

    manager.deletePhone(id, "+79991234567");

    manager.deleteClient(id);
    std::cout << "Client delete. ID = " << id << std::endl;
  } catch (const ConnectionException &e) {
    std::cerr << "Connection error: " << e.what() << std::endl;
    return 1;
  } catch (const InvalidQueryException &e) {
    std::cerr << "Query error: " << e.what() << std::endl;
    return 1;
  } catch (const EnvFileException &e) {
    std::cerr << "Env file error: " << e.what() << std::endl;
    return 1;
  } catch (const DatabaseException &e) {
    std::cerr << "Database error: " << e.what() << std::endl;
    return 1;
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
    return 1;
}

  return 0;
}