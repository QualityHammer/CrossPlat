#pragma once

#include <array>
#include <string>

#include "../constructs/Types.hpp"

// Client error types
enum class ClientErrorType : u8 {
    INIT_FAILED,
    NO_SERVER_FOUND,
    CONNECTION_FAILED,
    TYPE_COUNT
};

// Server error types
enum class ServerErrorType : u8 {
    INIT_FAILED,
    TYPE_COUNT
};

using ClientErrorArray = std::array<const std::string, static_cast<u8>(ClientErrorType::TYPE_COUNT)>;
using ServerErrorArray = std::array<const std::string, static_cast<u8>(ServerErrorType::TYPE_COUNT)>;

// Client error messages
const ClientErrorArray clientErrorMsgStrings{
    "Client could not be initialized.",
    "No available game servers to connect to.",
    "Connection has failed."
};

// Server error messages
const ServerErrorArray serverErrorMsgStrings {
    "Server could not be initialized.",
};

// Client error callback
void ClientError(const ClientErrorType type);
// Server error callback
void ServerError(const ServerErrorType type);
