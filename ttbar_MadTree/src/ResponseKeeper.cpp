
#include "ResponseKeeper.hpp"

#include "RooUnfoldResponse.h"
#include "TFile.h"

#include <algorithm>
#include <iostream>

ResponseKeeper::ResponseKeeper() : m_saved(false), m_content() {}

ResponseKeeper::~ResponseKeeper()
{
    if (!m_saved) {
        std::clog << "Histograms not saved, deleting ..\n";
        std::for_each(m_content.begin(), m_content.end(), [](auto& p) {
            delete p.second;
            p.second = nullptr;
        });
    }
}

void ResponseKeeper::Register(const ResponseConfig& hist)
{
    const std::string_view name = GetName(hist.index); /* reco name */
    auto* h = new RooUnfoldResponse(hist.nbins, hist.start, hist.end,
                                    name.data(), hist.title.data());
    if (m_content.find(hist.index) != m_content.end()) {
        std::clog << "Found duplicated histogram named " << name
                  << ". Will override!\n";
        delete m_content.at(hist.index);
        m_content[hist.index] = nullptr;
    }
    m_content[hist.index] = h;
}

void ResponseKeeper::Fill(IndexPair index, float value, float value_true,
                          float weight)
{
    if (m_content.find(index) == m_content.end()) {
        std::clog << "Response [" << GetName(index) << "] does not exist"
                  << ". Skipping ..\n";
        return;
    }
    m_content.at(index)->Fill(value, value_true, weight);
}

void ResponseKeeper::Miss(IndexPair index, float value_true, float weight)
{
    if (m_content.find(index) == m_content.end()) {
        std::clog << "Response [" << GetName(index) << "] does not exist"
                  << ". Skipping ..\n";
        return;
    }
    m_content.at(index)->Miss(value_true, weight);
}

void ResponseKeeper::Fake(IndexPair index, float value, float weight)
{
    if (m_content.find(index) == m_content.end()) {
        std::clog << "Response [" << GetName(index) << "] does not exist"
                  << ". Skipping ..\n";
        return;
    }
    m_content.at(index)->Fake(value, weight);
}

int ResponseKeeper::Count() const { return m_content.size(); }

void ResponseKeeper::Show() const
{
    int i = 0;
    std::clog << "----------------------------------------------------\n";
    std::clog << "Booking responses:\n";
    std::clog << "----------------------------------------------------\n";
    std::for_each(m_content.begin(), m_content.end(), [&i](const auto& p) {
        std::clog << i++ << ":\t" << GetName(p.first) << '\n';
    });
    std::clog << "----------------------------------------------------\n";
}

void ResponseKeeper::SaveToFile(TFile* file)
{
    if (m_saved) {
        std::clog << "Already saved, returning ..\n";
        return;
    }

    std::for_each(m_content.begin(), m_content.end(),
                  [&file](const auto& p) { p.second->Write(); });
    std::clog << "All responses saved to " << file->GetName() << '\n';
    m_saved = true;
}
