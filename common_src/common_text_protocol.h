#ifndef TEXT_PROTOCOL_H
#define TEXT_PROTOCOL_H

#include "common_protocol.h"

class TextProtocol : public Protocol {
public:
    std::string srlz(std::string &cmd) override;
};

#endif
