#include "client/Client.hpp"
#include "server/Server.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Enter either client or server as an argument";
        return 1;
    }
    if (strcmp(argv[1], "client") == 0) {
        Client::ClientEngine client{};
        client.run();
    } else if (strcmp(argv[1], "server") == 0) {
        Server::ServerEngine server{};
        server.run();
    } else {
        std::cout << "Enter either client or server as an argument";
        return 1;
    }
	return 0;
}
