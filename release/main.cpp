#include <string>
#include "location_server.hpp"

int main(void)
{
  location_server_t server;

  std::string user_input;
  user_input.reserve(128);

  server.open().get();

  std::cout << "\nType 'exit' to quit\n\n";
  std::getline(std::cin, user_input);
  while (user_input != "exit") {
    std::getline(std::cin, user_input);
  }

  server.close().get();

  return 0;
}