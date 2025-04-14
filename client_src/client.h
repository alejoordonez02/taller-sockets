#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include "../common_src/common_protocol.h"

class Client {
private:
    std::unique_ptr<Protocol> protocol;

public:
    explicit Client(std::unique_ptr<Protocol>&& protocol);
    void run();
};

#endif
