#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

enum class ProtocolType {TEXT, BINARY};

class Protocol {
public:
    static std::unique_ptr<Protocol> create(
        const ProtocolType &prtcl_t);
    static int srlz_username(
        std::vector<uint8_t> &srlzd_username,
        const std::string &username);
    static int dsrlz_username(
        std::string &username,
        const char *srlzd_username);
    static int srlz_prtcl_t(
        std::vector<uint8_t> &srlzd_prtcl_t,
        const std::string &prtcl_t);
    static int dsrlz_prtcl_t(
        ProtocolType *prtcl_t,
        const char *srlzd_prtcl_t);
    virtual ~Protocol() = default;
};

#endif
