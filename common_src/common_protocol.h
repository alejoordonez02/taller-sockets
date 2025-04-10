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
private:
    std::unique_ptr<Serializer> srl;
    Socket skt;

public:
    /*
     * Constructor
     * */
    Protocol(const ProtocolType& type, Socket&& skt);

    /*
     * Commands
     * */
    int send(const Command& cmd);
    int recv(Command& cmd);

    /*
     * Outputs
     * */
    int send(const Output& output);
    int recv(Output& output);

    /*
     * Static methods
     * */
    /*
     * Send username
     * */
    static void send_username(const std::string& username, Socket& skt);
    static int recv_username(std::string& username);

    /*
     * Send protocol type
     * */
    static int send_type(const ProtocolType& type);
    static int recv_type(ProtocolType& type);
};

#endif
