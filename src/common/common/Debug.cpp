#include "Debug.hpp"

#include <iostream>

#include "GameOptions.hpp"

namespace Debug {

void serverConnected(const std::string& address) {
    if (GameOptions::verbose) {
        std::cout << "Connection to " << address << " has succeeded." << std::endl;
    }
}

void serverDisconnected() {
    if (GameOptions::verbose) {
        std::cout << "Disconnect successful" << std::endl;
    }
}

void showFrameTime(const u16& ms) {
    if (GameOptions::showFrameTime) {
        std::cout << "Frame: " << ms << "ms\n";
    }
}

void clientConnected() {
    if (GameOptions::verbose) {
        std::cout << "Client connected" << std::endl;
    }
}

void clientDisconnected() {
    if (GameOptions::verbose) {
        std::cout << "Client disconnected" << std::endl;
    }
}

void clientPacketRecieved() {
    if (GameOptions::verbose) {
        std::cout << "Packet recieved from client" << std::endl;
    }
}

void serverPacketRecieved() {
    if (GameOptions::verbose) {
        std::cout << "Packet recieved from server" << std::endl;
    }
}

void serverRunning(const std::string& address, const u16& port) {
    if (GameOptions::verbose) {
        std::cout << "Server running on " << address << ":" << port << std::endl;
    }
}

void showPacket(const Net::Packet& packet) {
    if (GameOptions::verbose) {
        std::cout << "Packet(" << std::endl << "    Type: " << (int)packet.type << std::endl
        << "    Size: " << packet.size << std::endl << "    Data:" << std::endl << "        ";
        for (u16 i{0}; i < packet.size; ++i) {
            std::cout << (int)packet.data[i];
            if (i != packet.size - 1)
                std::cout << ", ";
            if (i != 0 && i % 16 == 0)
                std::cout << std::endl << "        ";
        }
        std::cout << std::endl << ")" << std::endl;
    }
}

}
