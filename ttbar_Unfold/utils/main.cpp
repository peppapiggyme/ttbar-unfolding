
#include "HistDraw.hpp"

#include "TFile.h"
#include "TH1.h"

#include <iostream>


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::clog << "Usage:\n\tUnfold <path/to/histogram>\n";
        exit(0);
    }

    TFile* f = TFile::Open(argv[1], "read");
    if (!f->IsOpen()) {
        std::clog << "Failed to open " << argv[1] << ". exiting ..\n";
        exit(0);
    }

    // ST is the targetting kinematic variable
    TH1* h_true = dynamic_cast<TH1*>(f->Get("ST_truth"));
    TH1* h_reco = dynamic_cast<TH1*>(f->Get("ST"));
    h_true->Rebin(10);
    h_reco->Rebin(10);

    if (!h_true || !h_reco)  {
        std::clog << "Failed to retrive required histograms. exiting ..\n";
        exit(0);
    }

    auto hist_draw = std::make_unique<HistDraw>();
    hist_draw->Append({"Reco", "Reco", "lep", 1, 1, 1, h_reco});
    hist_draw->Append({"True", "True", "lep", 2, 1, 1, h_true});
    hist_draw->Draw("dist.png", "Sum of transverse momentum [GeV]", "Events");

    f->Close();
    h_true = nullptr;
    h_reco = nullptr;
    f = nullptr;

    return 0;
}
