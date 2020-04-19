#include "NetworkErrors.hpp"

#include <iostream>

void ClientError(const ClientErrorType type) {
    std::cout << clientErrorMsgStrings[static_cast<u8>(type)] << std::endl;
}

void ServerError(const ServerErrorType type) {
    std::cout << serverErrorMsgStrings[static_cast<u8>(type)] << std::endl;
}
