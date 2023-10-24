
#include "HistDraw.hpp"
#include "SimilarityTest.hpp"

#include "TFile.h"
#include "TH1.h"

#include <iostream>
#include <optional>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::clog << "Usage:\n\tUnfold "
                     "<path/to/nf_output> <path/to/png>\n";
        exit(0);
    }

    TFile* f_test = TFile::Open(argv[1], "read");
    if (!f_test->IsOpen()) {
        std::clog << "Failed to open " << argv[1] << ". exiting ..\n";
        exit(0);
    }

    // ST is the targetting kinematic variable
    TH1* h_true   = dynamic_cast<TH1*>(f_test->Get("ST_truth"));
    TH1* h_reco   = dynamic_cast<TH1*>(f_test->Get("ST"));
    TH1* h_unfold = dynamic_cast<TH1*>(f_test->Get("ST_NF"));

    if (!h_true || !h_reco || !h_unfold) {
        std::clog << "Failed to retrive required histograms. exiting ..\n";
        exit(0);
    }
    auto hist_draw = std::make_unique<HistDraw>();
    auto sim = std::make_unique<SimilarityTest>(h_true, h_unfold);
    hist_draw->SetTag("Normalising flow method");
    hist_draw->SetResult(sim->GetResults());
    hist_draw->Append({ "True", "True", "f", 2, 1, 1, h_true });
    hist_draw->Append({ "Unfold", "Unfold", "lep", 4, 1, 1, h_unfold });
    hist_draw->Append({ "Reco", "Reco", "f", 1, 1, 1, h_reco });
    hist_draw->Draw(argv[2], "Sum of transverse momentum [GeV]", "Events");

    f_test->Close();
    return 0;
}
