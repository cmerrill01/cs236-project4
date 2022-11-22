#ifndef CS236_PROJECT_1_NTUPLE_H
#define CS236_PROJECT_1_NTUPLE_H

#include <vector>
#include <string>

class nTuple {
private:
    std::vector<std::string> values;
public:
    nTuple(const std::vector<std::string>& tupleValues) : values(tupleValues) {};
    ~nTuple() = default;
    std::string ToString() const;
    std::vector<std::string> GetValues () const {
        return values;
    }
    bool operator<(const nTuple &otherTuple) const;
};

#endif //CS236_PROJECT_1_NTUPLE_H
