#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include "common_command.h"

enum class ProtocolType {TEXT, BINARY};

class Protocol {
protected:
    std::vector<std::string> tknz(
        const std::string &s);
public:
    static std::unique_ptr<Protocol> create(
        const ProtocolType &prtcl_t);

    virtual int srlz_cmd(
        std::vector<uint8_t> &srlzd_cmd,
        const Command &cmd) = 0;

    virtual int dsrlz_cmd(
        Command &cmd,
        const char *srlzd_cmd) = 0;

    static int srlz_username(
        std::vector<uint8_t> &srlzd_username,
        const std::string &username);
    static int srlz_prtcl_t(
        std::vector<uint8_t> &srlzd_prtcl_t,
        const std::string &prtcl_t);

    static int dsrlz_username(
        std::string &username,
        const char *srlzd_username);
    static int dsrlz_prtcl_t(
        ProtocolType *prtcl_t,
        const char *srlzd_prtcl_t);
    virtual ~Protocol() = default;
};

#endif
