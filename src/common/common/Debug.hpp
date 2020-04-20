#pragma once

#include <string>

#include "network/Packet.hpp"
#include "constructs/Types.hpp"

namespace Debug {

// Client debug
void serverConnected(const std::string& address);
void serverDisconnected();
void serverPacketRecieved();
void showFrameTime(const u16& ms);

// Server debug
void clientConnected();
void clientDisconnected();
void clientPacketRecieved();
void serverRunning(const std::string& address, const u16& port);

// Common debug
void showPacket(const Net::Packet& packet);

}
