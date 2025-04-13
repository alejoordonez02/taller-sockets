#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include <string>

#include "common_command.h"
#include "common_output.h"
#include "common_protocol_types.h"
#include "common_serializer.h"
#include "common_socket.h"

class Protocol {
public:
    /*
     * Virtual methods
     * */
    /*
     * Commands
     * */
    virtual bool send(const Command& cmd) = 0;
    virtual Command recv_command() = 0;

    /*
     * Outputs
     * */
    virtual bool send(const Output& output) = 0;
    virtual Output recv_output() = 0;

    /*
     * Static methods
     * */
    /*
     * Factory
     * */
    static std::unique_ptr<Protocol> create(const ProtocolType& type, Socket&& skt);

    /*
     * Send username
     * */
    static void send_username(const std::string& username, Socket& skt);
    static std::string recv_username(Socket& skt);

    /*
     * Send protocol type
     * */
    static void send_protocol_type(const ProtocolType& type, Socket& skt);
    static ProtocolType recv_protocol_type(Socket& skt);

    /*
     * Destructor
     * */
    virtual ~Protocol() = default;
};

#endif
