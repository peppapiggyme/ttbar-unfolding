#ifndef RecoTree_hpp
#define RecoTree_hpp

#include "Config.hpp"
#include "DelphesTree.hpp"
#include "Event.hpp"

#include "TFile.h"

class HistogramKeeper;
class TreeWriter;

class RecoTree : public DelphesTree
{
public:
    RecoTree(const IOConfig& cfg);
    virtual ~RecoTree() override;
    virtual void Loop() override;

private:
    virtual void Entry(Long64_t i, HistogramKeeper* histKeeper,
                       TreeWriter* treeWriter);
    void         Register(HistogramKeeper* histKeeper, TreeWriter* treeWriter);

private:
    Event    m_event;
    IOConfig m_config;
    TFile*   m_input;
    TFile*   m_output;
};

#endif