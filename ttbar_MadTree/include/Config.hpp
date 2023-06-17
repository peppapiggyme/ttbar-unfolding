#ifndef Config_hpp
#define Config_hpp

#include <array>
#include <string>
#include <string_view>

struct IOConfig {
    std::string inputPath;
    std::string outputPath;
};

// Add names here and modify following accordingly!
enum class Index : int {
    none        = 0,
    t0_truth_Pt = 1,
    t1_truth_Pt,
    tt_truth_Pt,
    tt_truth_m,
    ST_truth, // 2t
    t0_Pt,    // mu + b
    t1_Pt,    // mu + b
    tt_Pt,    // 2mu + 2b + MET
    tt_m,     // 2mu + 2b + MET
    ST,       // scalar 2mu + 2b + MET
    mu0_Pt,
    mu1_Pt,
    b0_Pt,
    b1_Pt,
    MET,
    n_jets,
    event_number,
    weight,
    xsec,
    xsec_error,
    sum_of_weight,
    pass_reco_sel,
    end
};

constexpr static int N = static_cast<int>(Index::end);
constexpr static std::array<std::string_view, N> Names {
    "none",       "t0_truth_Pt",   "t1_truth_Pt",  "tt_truth_Pt", "tt_truth_m",
    "ST_truth",   "t0_Pt",         "t1_Pt",        "tt_Pt",       "tt_m",
    "ST",         "mu0_Pt",        "mu1_Pt",       "b0_Pt",       "b1_Pt",
    "MET",        "n_jets",        "event_number", "weight",      "xsec",
    "xsec_error", "sum_of_weight", "pass_reco_sel"
};

using IndexPair = std::pair<Index, Index>;
template <>
struct std::hash<IndexPair> {
    std::size_t operator()(IndexPair const& p) const noexcept
    {
        std::size_t h1 = std::hash<int> {}(static_cast<int>(p.first));
        std::size_t h2 = std::hash<int> {}(static_cast<int>(p.second));
        return h1 ^ (h2 << 1);
    }
};

struct HistogramConfig {
    Index            index;
    std::string_view title;
    int              nbins;
    float            start;
    float            end;
};

struct ResponseConfig {
    IndexPair        index; /* reco, truth pair */
    std::string_view title;
    int              nbins;
    float            start;
    float            end;
};

inline std::string GetName(Index i)
{
    return Names.at(static_cast<int>(i)).data();
}

inline std::string GetName(IndexPair i)
{
    return std::string("Response_") + GetName(i.first);
}

#endif