
#include "RooUnfoldResponse.h"
#include "RooUnfoldSvd.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"

#include <iostream>

void RunUnfolding(TH1* h_true, TH1* h_reco)
{

}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::clog << "Usage:\n\tUnfold <path/to/histogram>\n";
        exit(0);
    }

    gStyle->SetErrorX(0.5f);
    TFile* f = TFile::Open(argv[1], "recreate");
    if (!f->IsOpen()) {
        std::clog << "Failed to open " << argv[1] << ". exiting ..\n";
        exit(0);
    }

    // ST is the targetting kinematic variable
    TH1* h_true = dynamic_cast<TH1*>(f->Get("ST_truth"));
    TH1* h_reco = dynamic_cast<TH1*>(f->Get("ST"));

    if (!h_true || !h_reco)  {
        std::clog << "Failed to retrive required histograms. exiting ..\n";
        exit(0);
    }

    RunUnfolding(h_true, h_reco);

    f->Close();
    h_true = nullptr;
    h_reco = nullptr;
    f = nullptr;

    return 0;
}
