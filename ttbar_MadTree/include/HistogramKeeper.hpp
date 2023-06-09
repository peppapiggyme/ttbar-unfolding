#ifndef HistogramKeeper_hpp
#define HistogramKeeper_hpp

#include "Config.hpp"

#include <string>
#include <unordered_map>

class TH1;
class TFile;

class HistogramKeeper
{
public:
    HistogramKeeper();
    ~HistogramKeeper();

    HistogramKeeper(HistogramKeeper&)             = delete;
    HistogramKeeper(HistogramKeeper&&)            = delete;
    HistogramKeeper& operator=(HistogramKeeper&)  = delete;
    HistogramKeeper& operator=(HistogramKeeper&&) = delete;

    void Register(const HistogramConfig& hist);
    void Fill(Index index, float value, float weight);
    int  Count() const;
    void Show() const;
    void SaveToFile(TFile* file);

    using Hmap = std::unordered_map<Index, TH1*>;
    inline const Hmap& Content() { return m_content; }

private:
    bool m_saved;
    Hmap m_content;
};

#endif