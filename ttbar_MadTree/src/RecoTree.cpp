
#include "RecoTree.hpp"
#include "HistogramKeeper.hpp"
#include "TreeWriter.hpp"

#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TStyle.h"
#include "TTree.h"

#include <iostream>
#include <utility>

#define APPLY_CUT(criteria) \
    if (!(criteria)) return;

RecoTree::RecoTree(const IOConfig& cfg)
    : DelphesTree(), m_event(), m_config(cfg)
{
    m_input = TFile::Open(cfg.inputPath.c_str(), "read");
    if (!m_input) {
        std::clog << cfg.inputPath << " does not exist!\n";
        exit(0);
    }
    auto tree = dynamic_cast<TTree*>(m_input->Get("Delphes"));
    if (!tree) {
        std::clog << "Tree \'Delphes\' does not exist!\n";
        exit(0);
    }
    Init(tree);
}

RecoTree::~RecoTree()
{
    m_input->Close();
    m_output->Close();
}

void RecoTree::Loop()
{
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntries();

    auto             histKeeper  = std::make_unique<HistogramKeeper>();
    HistogramKeeper* pHistKeeper = histKeeper.get();
    auto             treeWriter  = std::make_unique<TreeWriter>();
    TreeWriter*      pTreeWriter = treeWriter.get();
    Register(pHistKeeper, pTreeWriter);

    pHistKeeper->Show();
    pTreeWriter->Show();

    // Loop starts here
    for (Long64_t i = 0; i < nentries; ++i) {
        Entry(i, pHistKeeper, pTreeWriter);
    }

    // save histogram, etc to file
    m_output = TFile::Open(m_config.outputPath.c_str(), "recreate");
    histKeeper->SaveToFile(m_output);
    treeWriter->SaveToFile(m_output);
}

void RecoTree::Entry(Long64_t i, HistogramKeeper* histKeeper,
                     TreeWriter* treeWriter)
{
    fChain->GetEntry(i);

    // meta information
    if (i == 0) {
        histKeeper->Fill(Index::xsec, 0, Event_CrossSection[0]);
        histKeeper->Fill(Index::xsec_error, 0, Event_CrossSectionError[0]);
    }
    histKeeper->Fill(Index::sum_of_weight, 0, Event_Weight[0]);

    // early stop
    // if (i > 10) return;

    // for debugging
    if (i % 1000 == 0) std::clog << "Event " << i << '\n';

    // apply cuts
    int b0 = 0, b1 = 1;
    APPLY_CUT(m_event.HasTwoMu(this));
    APPLY_CUT(m_event.HasTwoB(this, b0, b1));

    int t0 = 0, t1 = 1;
    APPLY_CUT(m_event.FindTwoTop(this, t0, t1));

    // 4-momentum
    auto ToFourMomentum = [](float pt, float eta, float phi,
                             float m) -> TLorentzVector {
        auto fourMomentum = TLorentzVector();
        fourMomentum.SetPtEtaPhiM(pt, eta, phi, m);
        return fourMomentum;
    };

    auto ToFourMomentumParticle = [&ToFourMomentum,
                                   this](int i) -> TLorentzVector {
        return ToFourMomentum(Particle_PT[i], Particle_Eta[i], Particle_Phi[i],
                              Particle_Mass[i]);
    };

    // truth
    m_event.Set(Index::t0_truth_Pt, Particle_PT[t0]);
    m_event.Set(Index::t1_truth_Pt, Particle_PT[t1]);
    auto t0_truth_P4 = ToFourMomentumParticle(t0);
    auto t1_truth_P4 = ToFourMomentumParticle(t1);
    m_event.Set(Index::tt_truth_Pt, (t0_truth_P4 + t1_truth_P4).Pt());
    m_event.Set(Index::tt_truth_m, (t0_truth_P4 + t1_truth_P4).M());
    m_event.Set(Index::ST_truth, Particle_PT[t0] + Particle_PT[t1]);

    auto ToFourMomentumJet = [&ToFourMomentum, this](int i) -> TLorentzVector {
        return ToFourMomentum(Jet_PT[i], Jet_Eta[i], Jet_Phi[i], Jet_Mass[i]);
    };

    auto ToFourMomentumMuon = [&ToFourMomentum, this](int i) -> TLorentzVector {
        return ToFourMomentum(Muon_PT[i], Muon_Eta[i], Muon_Phi[i],
                              0); // ignore mass of muon
    };

    // reco
    auto mu0_P4 = ToFourMomentumMuon(0);
    auto mu1_P4 = ToFourMomentumMuon(1);
    auto b0_P4  = ToFourMomentumJet(b0);
    auto b1_P4  = ToFourMomentumJet(b1);
    m_event.Set(Index::tt_Pt, (mu0_P4 + mu1_P4 + b0_P4 + b1_P4).Pt());
    m_event.Set(Index::tt_m, (mu0_P4 + mu1_P4 + b0_P4 + b1_P4).M());
    m_event.Set(Index::ST, Muon_PT[0] + Muon_PT[1] + Jet_PT[b0] + Jet_PT[b1]
                               + MissingET_MET[0]);

    // fill histograms
    histKeeper->Fill(Index::t0_truth_Pt, m_event.Get(Index::t0_truth_Pt),
                     Event_Weight[0]);
    histKeeper->Fill(Index::t1_truth_Pt, m_event.Get(Index::t1_truth_Pt),
                     Event_Weight[0]);
    histKeeper->Fill(Index::tt_truth_Pt, m_event.Get(Index::tt_truth_Pt),
                     Event_Weight[0]);
    histKeeper->Fill(Index::tt_truth_m, m_event.Get(Index::tt_truth_m),
                     Event_Weight[0]);
    histKeeper->Fill(Index::ST_truth, m_event.Get(Index::ST_truth),
                     Event_Weight[0]);
    histKeeper->Fill(Index::tt_Pt, m_event.Get(Index::tt_Pt), Event_Weight[0]);
    histKeeper->Fill(Index::tt_m, m_event.Get(Index::tt_m), Event_Weight[0]);
    histKeeper->Fill(Index::ST, m_event.Get(Index::ST), Event_Weight[0]);
    histKeeper->Fill(Index::mu0_Pt, Muon_PT[0], Event_Weight[0]);
    histKeeper->Fill(Index::mu1_Pt, Muon_PT[1], Event_Weight[0]);
    histKeeper->Fill(Index::b0_Pt, Jet_PT[b0], Event_Weight[0]);
    histKeeper->Fill(Index::b1_Pt, Jet_PT[b1], Event_Weight[0]);
    histKeeper->Fill(Index::MET, MissingET_MET[0], Event_Weight[0]);
    histKeeper->Fill(Index::n_jets, Jet_size, Event_Weight[0]);

    // Fill Tree
    treeWriter->SetValue(Index::t0_truth_Pt, m_event.Get(Index::t0_truth_Pt));
    treeWriter->SetValue(Index::t1_truth_Pt, m_event.Get(Index::t1_truth_Pt));
    treeWriter->SetValue(Index::tt_truth_Pt, m_event.Get(Index::tt_truth_Pt));
    treeWriter->SetValue(Index::tt_truth_m, m_event.Get(Index::tt_truth_m));
    treeWriter->SetValue(Index::ST_truth, m_event.Get(Index::ST_truth));
    treeWriter->SetValue(Index::tt_Pt, m_event.Get(Index::tt_Pt));
    treeWriter->SetValue(Index::tt_m, m_event.Get(Index::tt_m));
    treeWriter->SetValue(Index::ST, m_event.Get(Index::ST));
    treeWriter->SetValue(Index::mu0_Pt, Muon_PT[0]);
    treeWriter->SetValue(Index::mu1_Pt, Muon_PT[1]);
    treeWriter->SetValue(Index::b0_Pt, Jet_PT[b0]);
    treeWriter->SetValue(Index::b1_Pt, Jet_PT[b1]);
    treeWriter->SetValue(Index::MET, MissingET_MET[0]);
    treeWriter->SetValue(Index::n_jets, Jet_size);
    treeWriter->SetValue(Index::event_number, Event_Number[0]);
    treeWriter->SetValue(Index::weight, Event_Weight[0]);
    treeWriter->Fill();
}

void RecoTree::Register(HistogramKeeper* histKeeper, TreeWriter* treeWriter)
{
    histKeeper->Register({ Index::t0_truth_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::t1_truth_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::tt_truth_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::tt_truth_m, "", 800, 200, 1000 });
    histKeeper->Register({ Index::ST_truth, "", 1000, 0, 1000 });
    histKeeper->Register({ Index::tt_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::tt_m, "", 500, 0, 500 });
    histKeeper->Register({ Index::ST, "", 1000, 0, 1000 });
    histKeeper->Register({ Index::mu0_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::mu1_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::b0_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::b1_Pt, "", 500, 0, 500 });
    histKeeper->Register({ Index::MET, "", 500, 0, 500 });
    histKeeper->Register({ Index::n_jets, "", 20, 0, 20 });
    histKeeper->Register({ Index::sum_of_weight, "", 1, 0, 1 });
    histKeeper->Register({ Index::xsec, "", 1, 0, 1 });
    histKeeper->Register({ Index::xsec_error, "", 1, 0, 1 });

    treeWriter->Register(Index::t0_truth_Pt);
    treeWriter->Register(Index::t1_truth_Pt);
    treeWriter->Register(Index::tt_truth_Pt);
    treeWriter->Register(Index::tt_truth_m);
    treeWriter->Register(Index::ST_truth);
    treeWriter->Register(Index::tt_Pt);
    treeWriter->Register(Index::tt_m);
    treeWriter->Register(Index::ST);
    treeWriter->Register(Index::mu0_Pt);
    treeWriter->Register(Index::mu1_Pt);
    treeWriter->Register(Index::b0_Pt);
    treeWriter->Register(Index::b1_Pt);
    treeWriter->Register(Index::MET);
    treeWriter->Register(Index::n_jets);
    treeWriter->Register(Index::event_number);
    treeWriter->Register(Index::weight);
    treeWriter->InitBranches();
}