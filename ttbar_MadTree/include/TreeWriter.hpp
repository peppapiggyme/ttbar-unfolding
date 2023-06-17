#ifndef TreeWriter_hpp
#define TreeWriter_hpp

#include "Config.hpp"
#include "TTree.h"

#include <array>

class TreeWriter
{
public:
    explicit TreeWriter(const std::string_view& name);

public:
    void Register(Index index);
    void SetValue(Index index, float value);
    void Fill();
    int  Count() const;
    void Show() const;
    void SaveToFile(TFile* file);
    void InitBranches();

private:
    void Init();

private:
    std::string_view m_name;
    TTree* m_tree;
    using Vmap = std::vector<float>;
    std::array<Index, N> m_variables;
    std::array<float, N> m_values;
};

#endif