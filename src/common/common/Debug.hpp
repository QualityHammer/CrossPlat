#pragma once

#include <string>

#include "network/Packet.hpp"
#include "constructs/Types.hpp"

namespace Debug {

static bool verbose{false};

// Client debug
void serverConnected(const std::string& address);
void serverDisconnected();
void serverPacketRecieved();

// Server debug
void clientConnected();
void clientDisconnected();
void clientPacketRecieved();
void serverRunning(const std::string& address, const u16& port);

// Common debug
void showPacket(const Net::Packet& packet);

}
