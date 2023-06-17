#ifndef Config_hpp
#define Config_hpp

#include <array>
#include <string>

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

constexpr static int              N = static_cast<int>(Index::end);
static std::array<std::string, N> Names {
    "none",       "t0_truth_Pt",   "t1_truth_Pt",  "tt_truth_Pt", "tt_truth_m",
    "ST_truth",   "t0_Pt",         "t1_Pt",        "tt_Pt",       "tt_m",
    "ST",         "mu0_Pt",        "mu1_Pt",       "b0_Pt",       "b1_Pt",
    "MET",        "n_jets",        "event_number", "weight",      "xsec",
    "xsec_error", "sum_of_weight", "pass_reco_sel"
};

inline const std::string& GetName(Index i)
{
    return Names[static_cast<int>(i)];
}

struct HistogramConfig {
    Index       index;
    std::string title;
    int         nbins;
    float       start;
    float       end;
};

#endif