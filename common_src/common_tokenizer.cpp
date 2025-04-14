#include "common_tokenizer.h"

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Tokenizer::tknz(const std::string& s) {
    std::vector<std::string> tkns;

    std::istringstream iss(s);

    std::string tkn;
    while (iss >> tkn) tkns.push_back(tkn);

    return tkns;
}

std::vector<std::string> Tokenizer::tknz(const std::string& s, const std::string& delims) {
    std::vector<std::string> tkns;
    size_t start = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        if (delims.find(s[i]) != std::string::npos) {
            if (i > start)
                tkns.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }

    if (start < s.size())
        tkns.push_back(s.substr(start));

    return tkns;
}
