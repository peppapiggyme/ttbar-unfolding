
#include "HistDraw.hpp"

#include "RooUnfoldResponse.h"
#include "TFile.h"
#include "TH1.h"
#include "UnfoldFactory.hpp"

#include <iostream>
#include <optional>

int main(int argc, char* argv[])
{
    if (argc < 4) {
        std::clog << "Usage:\n\tUnfold "
                     "<path/to/response> <path/to/reco> <path/to/png>\n";
        exit(0);
    }

    TFile* f_train = TFile::Open(argv[1], "read");
    TFile* f_test  = TFile::Open(argv[2], "read");
    if (!f_train->IsOpen()) {
        std::clog << "Failed to open " << argv[1] << ". exiting ..\n";
        exit(0);
    }

    if (!f_test->IsOpen()) {
        std::clog << "Failed to open " << argv[2] << ". exiting ..\n";
        exit(0);
    }

    // ST is the targetting kinematic variable
    TH1* h_true = dynamic_cast<TH1*>(f_test->Get("ST_truth"));
    TH1* h_reco = dynamic_cast<TH1*>(f_test->Get("ST"));

    if (!h_true || !h_reco) {
        std::clog << "Failed to retrive required histograms. exiting ..\n";
        exit(0);
    }

    // Get Response object
    RooUnfoldResponse* response =
        dynamic_cast<RooUnfoldResponse*>(f_train->Get("Response_ST"));
    std::optional<double> reg;
    auto                  mem_unfold =
        UnfoldFactory::Create(RooUnfold::kBayes, response, h_reco, reg);
    auto unfold   = mem_unfold.get();
    TH1* h_unfold = unfold->Hunfold();
    h_unfold->SetName("Unfold");
    h_unfold->SetDirectory(0);

    auto hist_draw = std::make_unique<HistDraw>();
    hist_draw->SetTag("Bayes method");
    hist_draw->Append({ "True", "True", "f", 2, 1, 1, h_true });
    hist_draw->Append({ "Unfold", "Unfold", "lep", 4, 1, 1, h_unfold });
    hist_draw->Append({ "Reco", "Reco", "f", 1, 1, 1, h_reco });
    hist_draw->Draw(argv[3], "Sum of transverse momentum [GeV]", "Events");

    TFile* f_output = TFile::Open("/tmp/output.root", "recreate");
    f_output->cd();
    h_true->Write();
    h_reco->Write();
    h_unfold->Write();

    f_train->Close();
    f_test->Close();
    f_output->Close();

    return 0;
}
