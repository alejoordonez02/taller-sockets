#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    static std::vector<std::string> tknz(const std::string& s);
    static std::vector<std::string> tknz(const std::string& s, const std::string& delims);
};

#endif
