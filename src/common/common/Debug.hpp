#pragma once

#include <string>

#include "constructs/Types.hpp"

namespace Debug {

// Client debug
void serverConnected(const std::string& address);
void serverDisconnected();
void serverPacketRecieved();

// Server debug
void clientConnected();
void clientDisconnected();
void clientPacketRecieved();
void serverRunning(const std::string& address, const u16& port);

}
