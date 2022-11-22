#ifndef CS236_PROJECT_1_HEADER_H
#define CS236_PROJECT_1_HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> attributes;
public:
    Header(const std::vector<std::string>& headerValues) : attributes(headerValues) {}
    ~Header() = default;
    std::string ToString() const;
    std::vector<std::string> GetAttributes() const { return attributes; };
    bool operator!=(const Header& other) { return attributes != other.attributes; }
};

#endif //CS236_PROJECT_1_HEADER_H
