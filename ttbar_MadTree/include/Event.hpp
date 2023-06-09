#ifndef Event_hpp
#define Event_hpp

#include "Config.hpp"

#include <optional>
#include <unordered_map>

class DelphesTree;

class Event
{
public:
    Event() = default;

    void  Set(Index index, float value);
    float Get(Index index) const;

public:
    // selections
    bool HasTwoMu(const DelphesTree* tree) const;
    bool HasTwoB(const DelphesTree* tree, int& b0, int& b1) const;

    // find objects from particles
    bool FindTwoTop(const DelphesTree* tree, int& t0, int& t1) const;

private:
    using Vmap = std::unordered_map<Index, std::optional<float>>;
    Vmap m_variables;
};

#endif