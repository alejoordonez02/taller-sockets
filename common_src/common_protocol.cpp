#include "common_protocol.h"

#include <string>
#include <vector>

#include "common_command.h"
#include "common_output.h"
#include "common_serializer.h"
#include "common_socket.h"

/*
 * Server
 * */
Protocol::Protocol(const ProtocolType& type, const std::string& servname):
        srl(Serializer::create(type)), skt(servname.c_str()) {}

/*
 * Client
 * */
Protocol::Protocol(const ProtocolType& type, const std::string& hostname,
                   const std::string& servname):
        srl(Serializer::create(type)), skt(hostname.c_str(), servname.c_str()) {}

/*
 * Commands
 * */
int Protocol::send(const Command& cmd) { return 0; }
int Protocol::recv(Command& cmd) { return 0; }

/*
 * Outputs
 * */
int Protocol::send(const Output& output) { return 0; }
int Protocol::recv(Output& output) { return 0; }

/*
 * Static methods
 * */
/*
 * Send username
 * */
void Protocol::send_username(const std::string& username, Socket& skt) {
    std::vector<uint8_t> srlzd_username = Serializer::serialize_username(username);
    skt.sendall(srlzd_username.data(), srlzd_username.size());
}

int Protocol::recv_username(std::string& username) { return 0; }

/*
 * Send protocol type
 * */
int Protocol::send_type(const ProtocolType& type) { return 0; }
int Protocol::recv_type(ProtocolType& type) { return 0; }
