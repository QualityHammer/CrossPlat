#pragma once

#include <enet/enet.h>

namespace Net {

// Calls enet initialization on win32 systems
void netInit();
// Calls enet de-initialization on win32 systems
void netClose();

}
