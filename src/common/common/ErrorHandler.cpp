#include "ErrorHandler.hpp"

#include <iostream>

extern void Error(const ErrorMsg msg) {
    std::cerr << "Error: "
        << errorMsgStrings[static_cast<u8>(msg)]
        << std::endl;
    
}
