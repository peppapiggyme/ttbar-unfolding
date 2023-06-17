#ifndef ResponseKeeper_hpp
#define ResponseKeeper_hpp

#include "Config.hpp"

#include <string>
#include <unordered_map>
#include <utility>

class RooUnfoldResponse;
class TFile;

class ResponseKeeper
{
public:
    ResponseKeeper();
    ~ResponseKeeper();

    ResponseKeeper(ResponseKeeper&)             = delete;
    ResponseKeeper(ResponseKeeper&&)            = delete;
    ResponseKeeper& operator=(ResponseKeeper&)  = delete;
    ResponseKeeper& operator=(ResponseKeeper&&) = delete;

    void Register(const ResponseConfig& hist);
    void Fill(IndexPair index, float value, float value_true, float weight);
    void Miss(IndexPair index, float value_true, float weight);
    void Fake(IndexPair index, float value, float weight);
    int  Count() const;
    void Show() const;
    void SaveToFile(TFile* file);

    using Hmap = std::unordered_map<IndexPair, RooUnfoldResponse*>;
    inline const Hmap& Content() { return m_content; }

private:
    bool m_saved;
    Hmap m_content;
};

#endif