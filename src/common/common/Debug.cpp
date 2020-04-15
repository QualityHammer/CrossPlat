#include "Debug.hpp"

#include <iostream>

namespace Debug {

void serverConnected(const std::string& address) {
    std::cout << "Connection to " << address << " has succeeded." << std::endl;
}

void serverDisconnected() {
    std::cout << "Disconnect successful" << std::endl;
}

void clientConnected() {
    std::cout << "Client connected" << std::endl;
}

void clientDisconnected() {
    std::cout << "Client disconnected" << std::endl;
}

void clientPacketRecieved() {
    std::cout << "Packet recieved from client" << std::endl;
}

void serverPacketRecieved() {
    std::cout << "Packet recieved from server" << std::endl;
}

void serverRunning(const std::string& address, const u16& port) {
    std::cout << "Server running on " << address << ":" << port << std::endl;
}

}
