#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>

#include "../common_src/common_protocol.h"

#include "server_command_processor.h"

class Server {
private:
    std::unique_ptr<Protocol> protocol;
    CommandProcessor processor;

public:
    Server(std::unique_ptr<Protocol>&& protocol, const std::string& username);
    void run();
};

#endif
