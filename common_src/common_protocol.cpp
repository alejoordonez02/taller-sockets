#include <string>
#include <memory>

#include "common_socket.h"
#include "common_protocol.h"
#include "common_binary_protocol.h"
#include "common_text_protocol.h"

/*
 * Server
 * */
int Protocol::create(
    Protocol*& protocol,
    const ProtocolType& type,
    const std::string& servname) {

    /*
     * Server socket
     * */
    Socket skt(servname.c_str());

    return create(protocol, type, skt);
}

/*
 * Client
 * */
int Protocol::create(
    Protocol*& protocol,
    const ProtocolType& type,
    const std::string& hostname,
    const std::string& servname) {

    /*
     * Client socket
     * */
    Socket skt(hostname.c_str(), servname.c_str());

    return create(protocol, type, skt);
}

/*
 * Con el socket
 * */
int Protocol::create(
    Protocol*& protocol,
    const ProtocolType& type,
    Socket& skt) {

    int ret;

    switch(type) {
    case ProtocolType::BINARY:
        protocol = new BinaryProtocol(std::move(skt));
        ret = 0;
        break;
    case ProtocolType::TEXT:
        protocol = new TextProtocol(std::move(skt));
        ret = 0;
        break;
    default:
        protocol = nullptr;
        ret = -1;
        break;
    }

    return ret;
}

/*
 * Send usernmae
 * */
// int Protocol::send_username(const std::string& username) {
//     return 0;
// }


/*
 * Send protocol type
 * */
