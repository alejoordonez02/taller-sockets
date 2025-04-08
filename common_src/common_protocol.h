#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <memory>

#include "common_protocol_types.h"
#include "common_socket.h"
#include "common_serializer.h"
#include "common_command.h"
#include "common_output.h"

class Protocol {
private:
    std::unique_ptr<Serializer> srl;
    Socket skt;
public:
    /*
     * Server protocol
     * */
    Protocol(
        const ProtocolType& type,
        const std::string& servname);

    /*
     * Client protocol
     * */
    Protocol(
        const ProtocolType& type,
        const std::string& hostname,
        const std::string& servname);

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
    static int send_username(const std::string& username);
    static int recv_username(std::string& username);

    /*
     * Send protocol type
     * */
    static int send_type(const ProtocolType& type);
    static int recv_type(ProtocolType& type);
};

#endif
