
#include "HistogramKeeper.hpp"

#include "TFile.h"
#include "TH1.h"

#include <algorithm>
#include <iostream>

HistogramKeeper::HistogramKeeper() : m_saved(false), m_content() {}

HistogramKeeper::~HistogramKeeper()
{
    if (!m_saved) {
        std::clog << "Histograms not saved, deleting ..\n";
        std::for_each(begin(m_content), end(m_content), [](auto& p) {
            delete p.second;
            p.second = nullptr;
        });
    }
}

void HistogramKeeper::Register(const HistogramConfig& hist)
{
    const std::string& name = GetName(hist.index);
    TH1* h = new TH1F(name.c_str(), hist.title.c_str(), hist.nbins, hist.start,
                      hist.end);
    h->SetDirectory(0);
    if (m_content.find(hist.index) != m_content.end()) {
        std::clog << "Found duplicated histogram named " << name
                  << ". Will override!\n";
        delete m_content.at(hist.index);
        m_content[hist.index] = nullptr;
    }
    m_content[hist.index] = h;
}

void HistogramKeeper::Fill(Index index, float value, float weight)
{
    if (m_content.find(index) == m_content.end()) {
        std::clog << "Histogram [" << GetName(index) << "] does not exist"
                  << ". Skipping ..\n";
        return;
    }
    m_content.at(index)->Fill(value, weight);
}

int HistogramKeeper::Count() const { return m_content.size(); }

void HistogramKeeper::Show() const
{
    int i = 0;
    std::clog << "----------------------------------------------------\n";
    std::clog << "Booking histograms:\n";
    std::clog << "----------------------------------------------------\n";
    std::for_each(begin(m_content), end(m_content), [&i](const auto& p) {
        std::clog << i++ << ":\t" << GetName(p.first) << '\n';
    });
    std::clog << "----------------------------------------------------\n";
}

void HistogramKeeper::SaveToFile(TFile* file)
{
    if (m_saved) {
        std::clog << "Already saved, returning ..\n";
        return;
    }

    std::for_each(begin(m_content), end(m_content), [&file](const auto& p) {
        p.second->SetDirectory(file);
        p.second->Write();
    });
    std::clog << "All histograms saved to " << file->GetName() << '\n';
    m_saved = true;
}
