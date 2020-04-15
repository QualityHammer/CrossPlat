#pragma once

#include <array>
#include <string>

#include "../constructs/Types.hpp"

enum class ClientErrorType : u8 {
    INIT_FAILED,
    NO_SERVER_FOUND,
    CONNECTION_FAILED,
    TYPE_COUNT
};

enum class ServerErrorType : u8 {
    INIT_FAILED,
    TYPE_COUNT
};

using ClientErrorArray = std::array<const std::string, static_cast<u8>(ClientErrorType::TYPE_COUNT)>;
using ServerErrorArray = std::array<const std::string, static_cast<u8>(ServerErrorType::TYPE_COUNT)>;

const ClientErrorArray clientErrorMsgStrings{
    "Client could not be initialized.",
    "No available game servers to connect to.",
    "Connection has failed."
};

const ServerErrorArray serverErrorMsgStrings {
    "Server could not be initialized.",
};

void ClientError(const ClientErrorType type);
void ServerError(const ServerErrorType type);
