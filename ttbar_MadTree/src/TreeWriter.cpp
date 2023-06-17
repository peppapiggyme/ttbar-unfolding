
#include "TreeWriter.hpp"

#include <algorithm>
#include <iostream>

TreeWriter::TreeWriter(const std::string_view& name)
    : m_name(name), m_tree(nullptr), m_variables(), m_values()
{
    m_tree = new TTree(m_name.data(), "");
    m_tree->SetDirectory(0);
    m_tree->SetMaxTreeSize(500'000'000);
    InitBranches();
}

void TreeWriter::Register(Index index)
{
    if (std::find(begin(m_variables), end(m_variables), index)
        != m_variables.end()) {
        std::clog << "Found duplicated variable named " << GetName(index)
                  << ". Will override!\n";
    }
    m_variables[static_cast<int>(index)] = index;
    m_values[static_cast<int>(index)]    = 0.f;
}

void TreeWriter::SetValue(Index index, float value)
{
    if (std::find(begin(m_variables), end(m_variables), index)
        == m_variables.end()) {
        std::clog << "Variable named " << GetName(index)
                  << " does not exist. Will skip!\n";
        return;
    }
    m_values[static_cast<int>(index)] = value;
}

void TreeWriter::Fill() { m_tree->Fill(); }

int TreeWriter::Count() const { return m_variables.size(); }

void TreeWriter::Show() const
{
    int i = 0;
    std::clog << "----------------------------------------------------\n";
    std::clog << "Writing Tree:\n";
    std::clog << "----------------------------------------------------\n";
    std::for_each(begin(m_variables), end(m_variables), [&i](const auto& p) {
        if (p != Index::none) std::clog << i++ << ":\t" << GetName(p) << '\n';
    });
    std::clog << "----------------------------------------------------\n";
}

void TreeWriter::SaveToFile(TFile* file)
{
    m_tree->SetDirectory(reinterpret_cast<TDirectory*>(file));
    m_tree->Write();
}

void TreeWriter::InitBranches()
{
    for (int i = 0; i < N; ++i) {
        if (m_variables[i] != Index::none)
            m_tree->Branch(GetName(m_variables[i]).data(), m_values.data() + i);
    }
}

void TreeWriter::Init()
{
    for (int i = 0; i < N; ++i) {
        m_variables[i] = Index::none;
        m_values[i]    = 0.f;
    }
}
