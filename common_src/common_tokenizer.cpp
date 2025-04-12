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
