#include "common_binary_protocol.h"

BinaryProtocol::BinaryProtocol(Socket&& skt) : skt(std::move(skt)) {}

/*
 * Commands
 * */
int BinaryProtocol::send(const Command& cmd) {return 0;}
int BinaryProtocol::recv(Command& cmd) {return 0;}

/*
 * Outputs
 * */
int BinaryProtocol::send(const Output& output) {return 0;}
int BinaryProtocol::recv(Output& output) {return 0;}
