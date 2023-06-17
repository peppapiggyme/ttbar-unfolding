#ifndef RecoTree_hpp
#define RecoTree_hpp

#include "Config.hpp"
#include "DelphesTree.hpp"
#include "Event.hpp"
#include "HistogramKeeper.hpp"
#include "ResponseKeeper.hpp"
#include "TreeWriter.hpp"

#include "TFile.h"

#include <memory>

class RecoTree : public DelphesTree
{
public:
    RecoTree(const IOConfig& cfg);
    virtual ~RecoTree() override;
    virtual void Loop() override;

private:
    virtual void Entry(Long64_t i);
    virtual void Register();

private:
    Event    m_event;
    IOConfig m_config;
    TFile*   m_input;
    TFile*   m_output;

    std::unique_ptr<ResponseKeeper>  m_responseKeeper;
    std::unique_ptr<HistogramKeeper> m_histKeeper;
    std::unique_ptr<TreeWriter>      m_treeWriter;
    std::unique_ptr<TreeWriter>      m_treeWriterTruth;
};

#endif