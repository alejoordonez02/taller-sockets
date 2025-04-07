#include "common_text_protocol.h"


TextProtocol::TextProtocol(Socket&& skt) : skt(std::move(skt)) {}

/*
 * Commands
 * */
int TextProtocol::send(const Command& cmd) {return 0;}
int TextProtocol::recv(Command& cmd) {return 0;}

/*
 * Outputs
 * */
int TextProtocol::send(const Output& output) {return 0;}
int TextProtocol::recv(Output& output) {return 0;}
