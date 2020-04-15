#include "Net.hpp"

#include <iostream>

namespace Net {

void netInit() {
#ifdef WIN32
  if (enet_initialize() != 0) {
        std::cerr << "An error occurred when initializing ENet." << std::endl;
        exit(1);
    }
#endif
    return;
}

void win32Close() {
#ifdef WIN32
    atexit(enet_deinitialize);
#endif
    return;
}

}
