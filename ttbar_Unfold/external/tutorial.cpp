//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Simple example usage of the RooUnfold package using toy MC.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Fergus Wilson
// <fwilson@slac.stanford.edu>
//
// (Modified by Bowen Zhang)
//
//==============================================================================

// See also:
// https://statisticalmethods.web.cern.ch/StatisticalMethods/unfolding/RooUnfold_01-Methods/

#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TROOT.h"

#include "UnfoldFactory.hpp"
#endif

//==============================================================================
// Global definitions
//==============================================================================

const Double_t cutdummy = -99999.0;

//==============================================================================
// Gaussian smearing, systematic translation, and variable inefficiency
//==============================================================================

Double_t smear(Double_t xt)
{
    Double_t xeff = 0.3 + (1.0 - 0.3) / 20 * (xt + 10.0); // efficiency
    Double_t x    = gRandom->Rndm();
    if (x > xeff) return cutdummy;
    Double_t xsmear = gRandom->Gaus(-2.5, 0.2); // bias and smear
    return xt + xsmear;
}

//==============================================================================
// Example Unfolding
//==============================================================================

void RooUnfoldExample()
{
    cout << "==================================== TRAIN "
            "===================================="
         << endl;
    // First term is the number of bins
    // The variable ranges from -10 to 10
    RooUnfoldResponse response(40, -10.0, 10.0);

    auto* f0 = new TH1F("f0", "f0", 40, -10, 10);
    auto* g0 = new TH1F("g0", "g0", 40, -10, 10);

    // Train with a Breit-Wigner, mean 0.3 and width 2.5.
    for (Int_t i = 0; i < 100000; i++) {
        Double_t xt = gRandom->BreitWigner(0.3, 2.5);
        f0->Fill(xt);
        Double_t x = smear(xt);
        if (x != cutdummy) {
            // x:  the measured values
            // xt: the truth values
            // Fill: mapping the event to a response function
            response.Fill(x, xt);
            g0->Fill(x);
        } else {
            // Miss: calculate the efficiency of the system accross
            // the space of the true system
            response.Miss(xt);
        }
    }

    auto* c = new TCanvas();
    f0->SetStats(0);
    f0->SetTitle("");
    f0->SetFillColor(7);
    f0->Draw();
    g0->SetFillColor(42);
    g0->Draw("same");
    auto* leg = new TLegend(.55, 0.7, .9, .9);
    leg->AddEntry(f0, "True Distribution");
    leg->AddEntry(g0, "Predicted Measured");
    leg->Draw();
    c->Draw();
    c->SaveAs("true-response.png");

    auto* R  = response.HresponseNoOverflow();
    auto* c1 = new TCanvas();
    R->SetStats(0);
    R->Draw("colz");
    c1->Draw();
    c1->SaveAs("response.png");

    cout << "==================================== TEST "
            "====================================="
         << endl;
    TH1D* hTrue = new TH1D("true", "Test Truth", 40, -10.0, 10.0);
    TH1D* hMeas = new TH1D("meas", "Test Measured", 40, -10.0, 10.0);
    // Test with a Gaussian, mean 0 and width 2.
    for (Int_t i = 0; i < 10000; i++) {
        Double_t xt = gRandom->Gaus(0.0, 2.0), x = smear(xt);
        hTrue->Fill(xt);
        if (x != cutdummy) hMeas->Fill(x);
    }

    cout << "==================================== UNFOLD "
            "==================================="
         << endl;

    std::optional<double> reg;
    auto mem_unfold = UnfoldFactory::Create(RooUnfolding::kSVD, &response, hMeas, reg);
    auto unfold = mem_unfold.get();

    TH1D* hUnfold = (TH1D*) unfold->Hunfold();

    TCanvas* c2 = new TCanvas("canvas", "canvas");

    unfold->PrintTable(cout, hTrue);
    hUnfold->Draw("e1");
    hUnfold->SetMarkerStyle(20);
    hUnfold->SetMarkerSize(1.2);
    hUnfold->SetMarkerColor(4);
    hUnfold->SetLineColor(4);
    hUnfold->SetStats(0);
    hMeas->Draw("SAME");
    hMeas->SetLineColor(1);
    hTrue->SetLineColor(2);
    hTrue->Draw("SAME");
    auto* leg2 = new TLegend(0.6, 0.6, 0.9, 0.9);
    leg2->AddEntry(hTrue, "True distribution","l");
    leg2->AddEntry(hMeas, "Measured distribution", "l");
    leg2->AddEntry(hUnfold, "Unfolded distribution","lep");
    leg2->Draw();

    c2->SaveAs("unfolding.png");
}

#ifndef __CINT__
int main()
{
    gStyle->SetErrorX(0.5f);
    RooUnfoldExample();
    return 0;
} // Main program when run stand-alone
#endif
