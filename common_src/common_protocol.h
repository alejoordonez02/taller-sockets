#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <memory>

#include "common_socket.h"
#include "common_command.h"
#include "common_output.h"

enum class ProtocolType {BINARY, TEXT};

class Protocol {
private:
    static int create(
        Protocol*& protocol,
        const ProtocolType& type,
        Socket& skt);
public:
    /*
     * Server protocol factory
     * */
    static int create(
        Protocol*& protocol,
        const ProtocolType& type,
        const std::string& servname);

    /*
     * Client protocol factory
     * */
    static int create(
        Protocol*& protocol,
        const ProtocolType& type,
        const std::string& hostname,
        const std::string& servname);

    /*
     * Username
     * */
    static int send_username(const std::string& username);
    static int recv_username(std::string& username);

    /*
     * Protocol type
     * */
    static int send_type(const ProtocolType& type);
    static int recv_type(ProtocolType& type);

    /*
     * Commands
     * */
    virtual int send(const Command& cmd) const = 0;
    virtual int recv(Command& cmd) const = 0;

    /*
     * Outputs
     * */
    virtual int send(const Output& output) const = 0;
    virtual int recv(Output& output) const = 0;

    /*
     * Destructor
     * */
    virtual ~Protocol() = default;
};

#endif
