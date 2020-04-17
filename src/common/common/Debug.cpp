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

void showPacket(const Net::Packet& packet) {
    std::cout << "Packet(" << std::endl << "    Type: " << (int)packet.type << std::endl
    << "    Size: " << packet.size << std::endl << "    Data:" << std::endl << "        ";
    for (u16 i{0}; i < packet.size; ++i) {
        std::cout << (int)packet.data[i];
        if (i != packet.size - 1)
            std::cout << ", ";
        if (i != 0 && i % 8 == 0)
            std::cout << std::endl << "        ";
    }
    std::cout << std::endl << ")" << std::endl;
}

}
