#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

enum class ProtocolType {TEXT, BINARY};

class Protocol {
protected:
    std::vector<std::string> tknz(const std::string &cmd);

public:
    static std::unique_ptr<Protocol> create(ProtocolType &prtcl_t);
    virtual std::string srlz(std::string &cmd) = 0;
    static std::string srlz_username(const std::string &username);
    static std::string srlz_prtcl_t(const std::string &prtcl_t);
    static std::string dsrlz_username(char *srlzd_username);
    static ProtocolType dsrlz_prtcl_t(char &srlzd_prtcl_t);
    virtual ~Protocol() = default;
};

#endif
