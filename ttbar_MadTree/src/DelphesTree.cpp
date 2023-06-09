#include "DelphesTree.hpp"
#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

Int_t DelphesTree::GetEntry(Long64_t entry)
{
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

void DelphesTree::Init(TTree* tree)
{
    if (!tree) return;
    fChain   = tree;
    fCurrent = -1;
    // fChain->SetMakeClass(1); // this line cause seg fault ..

    fChain->SetBranchAddress("Event", &Event_, &b_Event_);
    fChain->SetBranchAddress("Event.fUniqueID", Event_fUniqueID,
                             &b_Event_fUniqueID);
    fChain->SetBranchAddress("Event.fBits", Event_fBits, &b_Event_fBits);
    fChain->SetBranchAddress("Event.Number", Event_Number, &b_Event_Number);
    fChain->SetBranchAddress("Event.ReadTime", Event_ReadTime,
                             &b_Event_ReadTime);
    fChain->SetBranchAddress("Event.ProcTime", Event_ProcTime,
                             &b_Event_ProcTime);
    fChain->SetBranchAddress("Event.ProcessID", Event_ProcessID,
                             &b_Event_ProcessID);
    fChain->SetBranchAddress("Event.MPI", Event_MPI, &b_Event_MPI);
    fChain->SetBranchAddress("Event.Weight", Event_Weight, &b_Event_Weight);
    fChain->SetBranchAddress("Event.CrossSection", Event_CrossSection,
                             &b_Event_CrossSection);
    fChain->SetBranchAddress("Event.CrossSectionError", Event_CrossSectionError,
                             &b_Event_CrossSectionError);
    fChain->SetBranchAddress("Event.Scale", Event_Scale, &b_Event_Scale);
    fChain->SetBranchAddress("Event.AlphaQED", Event_AlphaQED,
                             &b_Event_AlphaQED);
    fChain->SetBranchAddress("Event.AlphaQCD", Event_AlphaQCD,
                             &b_Event_AlphaQCD);
    fChain->SetBranchAddress("Event.ID1", Event_ID1, &b_Event_ID1);
    fChain->SetBranchAddress("Event.ID2", Event_ID2, &b_Event_ID2);
    fChain->SetBranchAddress("Event.X1", Event_X1, &b_Event_X1);
    fChain->SetBranchAddress("Event.X2", Event_X2, &b_Event_X2);
    fChain->SetBranchAddress("Event.ScalePDF", Event_ScalePDF,
                             &b_Event_ScalePDF);
    fChain->SetBranchAddress("Event.PDF1", Event_PDF1, &b_Event_PDF1);
    fChain->SetBranchAddress("Event.PDF2", Event_PDF2, &b_Event_PDF2);
    fChain->SetBranchAddress("Event_size", &Event_size, &b_Event_size);
    fChain->SetBranchAddress("Weight", &Weight_, &b_Weight_);
    fChain->SetBranchAddress("Weight.fUniqueID", Weight_fUniqueID,
                             &b_Weight_fUniqueID);
    fChain->SetBranchAddress("Weight.fBits", Weight_fBits, &b_Weight_fBits);
    fChain->SetBranchAddress("Weight.Weight", Weight_Weight, &b_Weight_Weight);
    fChain->SetBranchAddress("Weight_size", &Weight_size, &b_Weight_size);
    fChain->SetBranchAddress("Particle", &Particle_, &b_Particle_);
    fChain->SetBranchAddress("Particle.fUniqueID", Particle_fUniqueID,
                             &b_Particle_fUniqueID);
    fChain->SetBranchAddress("Particle.fBits", Particle_fBits,
                             &b_Particle_fBits);
    fChain->SetBranchAddress("Particle.PID", Particle_PID, &b_Particle_PID);
    fChain->SetBranchAddress("Particle.Status", Particle_Status,
                             &b_Particle_Status);
    fChain->SetBranchAddress("Particle.IsPU", Particle_IsPU, &b_Particle_IsPU);
    fChain->SetBranchAddress("Particle.M1", Particle_M1, &b_Particle_M1);
    fChain->SetBranchAddress("Particle.M2", Particle_M2, &b_Particle_M2);
    fChain->SetBranchAddress("Particle.D1", Particle_D1, &b_Particle_D1);
    fChain->SetBranchAddress("Particle.D2", Particle_D2, &b_Particle_D2);
    fChain->SetBranchAddress("Particle.Charge", Particle_Charge,
                             &b_Particle_Charge);
    fChain->SetBranchAddress("Particle.Mass", Particle_Mass, &b_Particle_Mass);
    fChain->SetBranchAddress("Particle.E", Particle_E, &b_Particle_E);
    fChain->SetBranchAddress("Particle.Px", Particle_Px, &b_Particle_Px);
    fChain->SetBranchAddress("Particle.Py", Particle_Py, &b_Particle_Py);
    fChain->SetBranchAddress("Particle.Pz", Particle_Pz, &b_Particle_Pz);
    fChain->SetBranchAddress("Particle.P", Particle_P, &b_Particle_P);
    fChain->SetBranchAddress("Particle.PT", Particle_PT, &b_Particle_PT);
    fChain->SetBranchAddress("Particle.Eta", Particle_Eta, &b_Particle_Eta);
    fChain->SetBranchAddress("Particle.Phi", Particle_Phi, &b_Particle_Phi);
    fChain->SetBranchAddress("Particle.Rapidity", Particle_Rapidity,
                             &b_Particle_Rapidity);
    fChain->SetBranchAddress("Particle.T", Particle_T, &b_Particle_T);
    fChain->SetBranchAddress("Particle.X", Particle_X, &b_Particle_X);
    fChain->SetBranchAddress("Particle.Y", Particle_Y, &b_Particle_Y);
    fChain->SetBranchAddress("Particle.Z", Particle_Z, &b_Particle_Z);
    fChain->SetBranchAddress("Particle_size", &Particle_size, &b_Particle_size);
    fChain->SetBranchAddress("GenJet", &GenJet_, &b_GenJet_);
    fChain->SetBranchAddress("GenJet.fUniqueID", GenJet_fUniqueID,
                             &b_GenJet_fUniqueID);
    fChain->SetBranchAddress("GenJet.fBits", GenJet_fBits, &b_GenJet_fBits);
    fChain->SetBranchAddress("GenJet.PT", GenJet_PT, &b_GenJet_PT);
    fChain->SetBranchAddress("GenJet.Eta", GenJet_Eta, &b_GenJet_Eta);
    fChain->SetBranchAddress("GenJet.Phi", GenJet_Phi, &b_GenJet_Phi);
    fChain->SetBranchAddress("GenJet.T", GenJet_T, &b_GenJet_T);
    fChain->SetBranchAddress("GenJet.Mass", GenJet_Mass, &b_GenJet_Mass);
    fChain->SetBranchAddress("GenJet.DeltaEta", GenJet_DeltaEta,
                             &b_GenJet_DeltaEta);
    fChain->SetBranchAddress("GenJet.DeltaPhi", GenJet_DeltaPhi,
                             &b_GenJet_DeltaPhi);
    fChain->SetBranchAddress("GenJet.Flavor", GenJet_Flavor, &b_GenJet_Flavor);
    fChain->SetBranchAddress("GenJet.FlavorAlgo", GenJet_FlavorAlgo,
                             &b_GenJet_FlavorAlgo);
    fChain->SetBranchAddress("GenJet.FlavorPhys", GenJet_FlavorPhys,
                             &b_GenJet_FlavorPhys);
    fChain->SetBranchAddress("GenJet.BTag", GenJet_BTag, &b_GenJet_BTag);
    fChain->SetBranchAddress("GenJet.BTagAlgo", GenJet_BTagAlgo,
                             &b_GenJet_BTagAlgo);
    fChain->SetBranchAddress("GenJet.BTagPhys", GenJet_BTagPhys,
                             &b_GenJet_BTagPhys);
    fChain->SetBranchAddress("GenJet.TauTag", GenJet_TauTag, &b_GenJet_TauTag);
    fChain->SetBranchAddress("GenJet.TauWeight", GenJet_TauWeight,
                             &b_GenJet_TauWeight);
    fChain->SetBranchAddress("GenJet.Charge", GenJet_Charge, &b_GenJet_Charge);
    fChain->SetBranchAddress("GenJet.EhadOverEem", GenJet_EhadOverEem,
                             &b_GenJet_EhadOverEem);
    fChain->SetBranchAddress("GenJet.NCharged", GenJet_NCharged,
                             &b_GenJet_NCharged);
    fChain->SetBranchAddress("GenJet.NNeutrals", GenJet_NNeutrals,
                             &b_GenJet_NNeutrals);
    fChain->SetBranchAddress("GenJet.NeutralEnergyFraction",
                             GenJet_NeutralEnergyFraction,
                             &b_GenJet_NeutralEnergyFraction);
    fChain->SetBranchAddress("GenJet.ChargedEnergyFraction",
                             GenJet_ChargedEnergyFraction,
                             &b_GenJet_ChargedEnergyFraction);
    fChain->SetBranchAddress("GenJet.Beta", GenJet_Beta, &b_GenJet_Beta);
    fChain->SetBranchAddress("GenJet.BetaStar", GenJet_BetaStar,
                             &b_GenJet_BetaStar);
    fChain->SetBranchAddress("GenJet.MeanSqDeltaR", GenJet_MeanSqDeltaR,
                             &b_GenJet_MeanSqDeltaR);
    fChain->SetBranchAddress("GenJet.PTD", GenJet_PTD, &b_GenJet_PTD);
    fChain->SetBranchAddress("GenJet.FracPt[5]", GenJet_FracPt,
                             &b_GenJet_FracPt);
    fChain->SetBranchAddress("GenJet.Tau[5]", GenJet_Tau, &b_GenJet_Tau);
    fChain->SetBranchAddress("GenJet.SoftDroppedJet", GenJet_SoftDroppedJet,
                             &b_GenJet_SoftDroppedJet);
    fChain->SetBranchAddress("GenJet.SoftDroppedSubJet1",
                             GenJet_SoftDroppedSubJet1,
                             &b_GenJet_SoftDroppedSubJet1);
    fChain->SetBranchAddress("GenJet.SoftDroppedSubJet2",
                             GenJet_SoftDroppedSubJet2,
                             &b_GenJet_SoftDroppedSubJet2);
    fChain->SetBranchAddress("GenJet.TrimmedP4[5]", GenJet_TrimmedP4,
                             &b_GenJet_TrimmedP4);
    fChain->SetBranchAddress("GenJet.PrunedP4[5]", GenJet_PrunedP4,
                             &b_GenJet_PrunedP4);
    fChain->SetBranchAddress("GenJet.SoftDroppedP4[5]", GenJet_SoftDroppedP4,
                             &b_GenJet_SoftDroppedP4);
    fChain->SetBranchAddress("GenJet.NSubJetsTrimmed", GenJet_NSubJetsTrimmed,
                             &b_GenJet_NSubJetsTrimmed);
    fChain->SetBranchAddress("GenJet.NSubJetsPruned", GenJet_NSubJetsPruned,
                             &b_GenJet_NSubJetsPruned);
    fChain->SetBranchAddress("GenJet.NSubJetsSoftDropped",
                             GenJet_NSubJetsSoftDropped,
                             &b_GenJet_NSubJetsSoftDropped);
    fChain->SetBranchAddress("GenJet.ExclYmerge23", GenJet_ExclYmerge23,
                             &b_GenJet_ExclYmerge23);
    fChain->SetBranchAddress("GenJet.ExclYmerge34", GenJet_ExclYmerge34,
                             &b_GenJet_ExclYmerge34);
    fChain->SetBranchAddress("GenJet.ExclYmerge45", GenJet_ExclYmerge45,
                             &b_GenJet_ExclYmerge45);
    fChain->SetBranchAddress("GenJet.ExclYmerge56", GenJet_ExclYmerge56,
                             &b_GenJet_ExclYmerge56);
    fChain->SetBranchAddress("GenJet.Area", GenJet_Area, &b_GenJet_Area);
    fChain->SetBranchAddress("GenJet_size", &GenJet_size, &b_GenJet_size);
    fChain->SetBranchAddress("GenMissingET", &GenMissingET_, &b_GenMissingET_);
    fChain->SetBranchAddress("GenMissingET.fUniqueID", GenMissingET_fUniqueID,
                             &b_GenMissingET_fUniqueID);
    fChain->SetBranchAddress("GenMissingET.fBits", GenMissingET_fBits,
                             &b_GenMissingET_fBits);
    fChain->SetBranchAddress("GenMissingET.MET", GenMissingET_MET,
                             &b_GenMissingET_MET);
    fChain->SetBranchAddress("GenMissingET.Eta", GenMissingET_Eta,
                             &b_GenMissingET_Eta);
    fChain->SetBranchAddress("GenMissingET.Phi", GenMissingET_Phi,
                             &b_GenMissingET_Phi);
    fChain->SetBranchAddress("GenMissingET_size", &GenMissingET_size,
                             &b_GenMissingET_size);
    fChain->SetBranchAddress("Jet", &Jet_, &b_Jet_);
    fChain->SetBranchAddress("Jet.fUniqueID", Jet_fUniqueID, &b_Jet_fUniqueID);
    fChain->SetBranchAddress("Jet.fBits", Jet_fBits, &b_Jet_fBits);
    fChain->SetBranchAddress("Jet.PT", Jet_PT, &b_Jet_PT);
    fChain->SetBranchAddress("Jet.Eta", Jet_Eta, &b_Jet_Eta);
    fChain->SetBranchAddress("Jet.Phi", Jet_Phi, &b_Jet_Phi);
    fChain->SetBranchAddress("Jet.T", Jet_T, &b_Jet_T);
    fChain->SetBranchAddress("Jet.Mass", Jet_Mass, &b_Jet_Mass);
    fChain->SetBranchAddress("Jet.DeltaEta", Jet_DeltaEta, &b_Jet_DeltaEta);
    fChain->SetBranchAddress("Jet.DeltaPhi", Jet_DeltaPhi, &b_Jet_DeltaPhi);
    fChain->SetBranchAddress("Jet.Flavor", Jet_Flavor, &b_Jet_Flavor);
    fChain->SetBranchAddress("Jet.FlavorAlgo", Jet_FlavorAlgo,
                             &b_Jet_FlavorAlgo);
    fChain->SetBranchAddress("Jet.FlavorPhys", Jet_FlavorPhys,
                             &b_Jet_FlavorPhys);
    fChain->SetBranchAddress("Jet.BTag", Jet_BTag, &b_Jet_BTag);
    fChain->SetBranchAddress("Jet.BTagAlgo", Jet_BTagAlgo, &b_Jet_BTagAlgo);
    fChain->SetBranchAddress("Jet.BTagPhys", Jet_BTagPhys, &b_Jet_BTagPhys);
    fChain->SetBranchAddress("Jet.TauTag", Jet_TauTag, &b_Jet_TauTag);
    fChain->SetBranchAddress("Jet.TauWeight", Jet_TauWeight, &b_Jet_TauWeight);
    fChain->SetBranchAddress("Jet.Charge", Jet_Charge, &b_Jet_Charge);
    fChain->SetBranchAddress("Jet.EhadOverEem", Jet_EhadOverEem,
                             &b_Jet_EhadOverEem);
    fChain->SetBranchAddress("Jet.NCharged", Jet_NCharged, &b_Jet_NCharged);
    fChain->SetBranchAddress("Jet.NNeutrals", Jet_NNeutrals, &b_Jet_NNeutrals);
    fChain->SetBranchAddress("Jet.NeutralEnergyFraction",
                             Jet_NeutralEnergyFraction,
                             &b_Jet_NeutralEnergyFraction);
    fChain->SetBranchAddress("Jet.ChargedEnergyFraction",
                             Jet_ChargedEnergyFraction,
                             &b_Jet_ChargedEnergyFraction);
    fChain->SetBranchAddress("Jet.Beta", Jet_Beta, &b_Jet_Beta);
    fChain->SetBranchAddress("Jet.BetaStar", Jet_BetaStar, &b_Jet_BetaStar);
    fChain->SetBranchAddress("Jet.MeanSqDeltaR", Jet_MeanSqDeltaR,
                             &b_Jet_MeanSqDeltaR);
    fChain->SetBranchAddress("Jet.PTD", Jet_PTD, &b_Jet_PTD);
    fChain->SetBranchAddress("Jet.FracPt[5]", Jet_FracPt, &b_Jet_FracPt);
    fChain->SetBranchAddress("Jet.Tau[5]", Jet_Tau, &b_Jet_Tau);
    fChain->SetBranchAddress("Jet.SoftDroppedJet", Jet_SoftDroppedJet,
                             &b_Jet_SoftDroppedJet);
    fChain->SetBranchAddress("Jet.SoftDroppedSubJet1", Jet_SoftDroppedSubJet1,
                             &b_Jet_SoftDroppedSubJet1);
    fChain->SetBranchAddress("Jet.SoftDroppedSubJet2", Jet_SoftDroppedSubJet2,
                             &b_Jet_SoftDroppedSubJet2);
    fChain->SetBranchAddress("Jet.TrimmedP4[5]", Jet_TrimmedP4,
                             &b_Jet_TrimmedP4);
    fChain->SetBranchAddress("Jet.PrunedP4[5]", Jet_PrunedP4, &b_Jet_PrunedP4);
    fChain->SetBranchAddress("Jet.SoftDroppedP4[5]", Jet_SoftDroppedP4,
                             &b_Jet_SoftDroppedP4);
    fChain->SetBranchAddress("Jet.NSubJetsTrimmed", Jet_NSubJetsTrimmed,
                             &b_Jet_NSubJetsTrimmed);
    fChain->SetBranchAddress("Jet.NSubJetsPruned", Jet_NSubJetsPruned,
                             &b_Jet_NSubJetsPruned);
    fChain->SetBranchAddress("Jet.NSubJetsSoftDropped", Jet_NSubJetsSoftDropped,
                             &b_Jet_NSubJetsSoftDropped);
    fChain->SetBranchAddress("Jet.ExclYmerge23", Jet_ExclYmerge23,
                             &b_Jet_ExclYmerge23);
    fChain->SetBranchAddress("Jet.ExclYmerge34", Jet_ExclYmerge34,
                             &b_Jet_ExclYmerge34);
    fChain->SetBranchAddress("Jet.ExclYmerge45", Jet_ExclYmerge45,
                             &b_Jet_ExclYmerge45);
    fChain->SetBranchAddress("Jet.ExclYmerge56", Jet_ExclYmerge56,
                             &b_Jet_ExclYmerge56);
    fChain->SetBranchAddress("Jet.Area", Jet_Area, &b_Jet_Area);
    fChain->SetBranchAddress("Jet_size", &Jet_size, &b_Jet_size);
    fChain->SetBranchAddress("Electron", &Electron_, &b_Electron_);
    fChain->SetBranchAddress("Electron.fUniqueID", Electron_fUniqueID,
                             &b_Electron_fUniqueID);
    fChain->SetBranchAddress("Electron.fBits", Electron_fBits,
                             &b_Electron_fBits);
    fChain->SetBranchAddress("Electron.PT", Electron_PT, &b_Electron_PT);
    fChain->SetBranchAddress("Electron.Eta", Electron_Eta, &b_Electron_Eta);
    fChain->SetBranchAddress("Electron.Phi", Electron_Phi, &b_Electron_Phi);
    fChain->SetBranchAddress("Electron.T", Electron_T, &b_Electron_T);
    fChain->SetBranchAddress("Electron.Charge", Electron_Charge,
                             &b_Electron_Charge);
    fChain->SetBranchAddress("Electron.EhadOverEem", Electron_EhadOverEem,
                             &b_Electron_EhadOverEem);
    fChain->SetBranchAddress("Electron.IsolationVar", Electron_IsolationVar,
                             &b_Electron_IsolationVar);
    fChain->SetBranchAddress("Electron.IsolationVarRhoCorr",
                             Electron_IsolationVarRhoCorr,
                             &b_Electron_IsolationVarRhoCorr);
    fChain->SetBranchAddress("Electron.SumPtCharged", Electron_SumPtCharged,
                             &b_Electron_SumPtCharged);
    fChain->SetBranchAddress("Electron.SumPtNeutral", Electron_SumPtNeutral,
                             &b_Electron_SumPtNeutral);
    fChain->SetBranchAddress("Electron.SumPtChargedPU", Electron_SumPtChargedPU,
                             &b_Electron_SumPtChargedPU);
    fChain->SetBranchAddress("Electron.SumPt", Electron_SumPt,
                             &b_Electron_SumPt);
    fChain->SetBranchAddress("Electron.D0", Electron_D0, &b_Electron_D0);
    fChain->SetBranchAddress("Electron.DZ", Electron_DZ, &b_Electron_DZ);
    fChain->SetBranchAddress("Electron.ErrorD0", Electron_ErrorD0,
                             &b_Electron_ErrorD0);
    fChain->SetBranchAddress("Electron.ErrorDZ", Electron_ErrorDZ,
                             &b_Electron_ErrorDZ);
    fChain->SetBranchAddress("Electron_size", &Electron_size, &b_Electron_size);
    fChain->SetBranchAddress("Photon", &Photon_, &b_Photon_);
    fChain->SetBranchAddress("Photon.fUniqueID", Photon_fUniqueID,
                             &b_Photon_fUniqueID);
    fChain->SetBranchAddress("Photon.fBits", Photon_fBits, &b_Photon_fBits);
    fChain->SetBranchAddress("Photon.PT", Photon_PT, &b_Photon_PT);
    fChain->SetBranchAddress("Photon.Eta", Photon_Eta, &b_Photon_Eta);
    fChain->SetBranchAddress("Photon.Phi", Photon_Phi, &b_Photon_Phi);
    fChain->SetBranchAddress("Photon.E", Photon_E, &b_Photon_E);
    fChain->SetBranchAddress("Photon.T", Photon_T, &b_Photon_T);
    fChain->SetBranchAddress("Photon.EhadOverEem", Photon_EhadOverEem,
                             &b_Photon_EhadOverEem);
    fChain->SetBranchAddress("Photon.IsolationVar", Photon_IsolationVar,
                             &b_Photon_IsolationVar);
    fChain->SetBranchAddress("Photon.IsolationVarRhoCorr",
                             Photon_IsolationVarRhoCorr,
                             &b_Photon_IsolationVarRhoCorr);
    fChain->SetBranchAddress("Photon.SumPtCharged", Photon_SumPtCharged,
                             &b_Photon_SumPtCharged);
    fChain->SetBranchAddress("Photon.SumPtNeutral", Photon_SumPtNeutral,
                             &b_Photon_SumPtNeutral);
    fChain->SetBranchAddress("Photon.SumPtChargedPU", Photon_SumPtChargedPU,
                             &b_Photon_SumPtChargedPU);
    fChain->SetBranchAddress("Photon.SumPt", Photon_SumPt, &b_Photon_SumPt);
    fChain->SetBranchAddress("Photon.Status", Photon_Status, &b_Photon_Status);
    fChain->SetBranchAddress("Photon_size", &Photon_size, &b_Photon_size);
    fChain->SetBranchAddress("Muon", &Muon_, &b_Muon_);
    fChain->SetBranchAddress("Muon.fUniqueID", Muon_fUniqueID,
                             &b_Muon_fUniqueID);
    fChain->SetBranchAddress("Muon.fBits", Muon_fBits, &b_Muon_fBits);
    fChain->SetBranchAddress("Muon.PT", Muon_PT, &b_Muon_PT);
    fChain->SetBranchAddress("Muon.Eta", Muon_Eta, &b_Muon_Eta);
    fChain->SetBranchAddress("Muon.Phi", Muon_Phi, &b_Muon_Phi);
    fChain->SetBranchAddress("Muon.T", Muon_T, &b_Muon_T);
    fChain->SetBranchAddress("Muon.Charge", Muon_Charge, &b_Muon_Charge);
    fChain->SetBranchAddress("Muon.IsolationVar", Muon_IsolationVar,
                             &b_Muon_IsolationVar);
    fChain->SetBranchAddress("Muon.IsolationVarRhoCorr",
                             Muon_IsolationVarRhoCorr,
                             &b_Muon_IsolationVarRhoCorr);
    fChain->SetBranchAddress("Muon.SumPtCharged", Muon_SumPtCharged,
                             &b_Muon_SumPtCharged);
    fChain->SetBranchAddress("Muon.SumPtNeutral", Muon_SumPtNeutral,
                             &b_Muon_SumPtNeutral);
    fChain->SetBranchAddress("Muon.SumPtChargedPU", Muon_SumPtChargedPU,
                             &b_Muon_SumPtChargedPU);
    fChain->SetBranchAddress("Muon.SumPt", Muon_SumPt, &b_Muon_SumPt);
    fChain->SetBranchAddress("Muon.D0", Muon_D0, &b_Muon_D0);
    fChain->SetBranchAddress("Muon.DZ", Muon_DZ, &b_Muon_DZ);
    fChain->SetBranchAddress("Muon.ErrorD0", Muon_ErrorD0, &b_Muon_ErrorD0);
    fChain->SetBranchAddress("Muon.ErrorDZ", Muon_ErrorDZ, &b_Muon_ErrorDZ);
    fChain->SetBranchAddress("Muon_size", &Muon_size, &b_Muon_size);
    fChain->SetBranchAddress("MissingET", &MissingET_, &b_MissingET_);
    fChain->SetBranchAddress("MissingET.fUniqueID", MissingET_fUniqueID,
                             &b_MissingET_fUniqueID);
    fChain->SetBranchAddress("MissingET.fBits", MissingET_fBits,
                             &b_MissingET_fBits);
    fChain->SetBranchAddress("MissingET.MET", MissingET_MET, &b_MissingET_MET);
    fChain->SetBranchAddress("MissingET.Eta", MissingET_Eta, &b_MissingET_Eta);
    fChain->SetBranchAddress("MissingET.Phi", MissingET_Phi, &b_MissingET_Phi);
    fChain->SetBranchAddress("MissingET_size", &MissingET_size,
                             &b_MissingET_size);
    fChain->SetBranchAddress("ScalarHT", &ScalarHT_, &b_ScalarHT_);
    fChain->SetBranchAddress("ScalarHT.fUniqueID", ScalarHT_fUniqueID,
                             &b_ScalarHT_fUniqueID);
    fChain->SetBranchAddress("ScalarHT.fBits", ScalarHT_fBits,
                             &b_ScalarHT_fBits);
    fChain->SetBranchAddress("ScalarHT.HT", ScalarHT_HT, &b_ScalarHT_HT);
    fChain->SetBranchAddress("ScalarHT_size", &ScalarHT_size, &b_ScalarHT_size);
    fChain->SetBranchAddress("Rho", &Rho_, &b_Rho_);
    fChain->SetBranchAddress("Rho.fUniqueID", Rho_fUniqueID, &b_Rho_fUniqueID);
    fChain->SetBranchAddress("Rho.fBits", Rho_fBits, &b_Rho_fBits);
    fChain->SetBranchAddress("Rho.Rho", Rho_Rho, &b_Rho_Rho);
    fChain->SetBranchAddress("Rho.Edges[2]", Rho_Edges, &b_Rho_Edges);
    fChain->SetBranchAddress("Rho_size", &Rho_size, &b_Rho_size);
    fChain->SetBranchAddress("Vertex", &Vertex_, &b_Vertex_);
    fChain->SetBranchAddress("Vertex.fUniqueID", Vertex_fUniqueID,
                             &b_Vertex_fUniqueID);
    fChain->SetBranchAddress("Vertex.fBits", Vertex_fBits, &b_Vertex_fBits);
    fChain->SetBranchAddress("Vertex.T", Vertex_T, &b_Vertex_T);
    fChain->SetBranchAddress("Vertex.X", Vertex_X, &b_Vertex_X);
    fChain->SetBranchAddress("Vertex.Y", Vertex_Y, &b_Vertex_Y);
    fChain->SetBranchAddress("Vertex.Z", Vertex_Z, &b_Vertex_Z);
    fChain->SetBranchAddress("Vertex.ErrorT", Vertex_ErrorT, &b_Vertex_ErrorT);
    fChain->SetBranchAddress("Vertex.ErrorX", Vertex_ErrorX, &b_Vertex_ErrorX);
    fChain->SetBranchAddress("Vertex.ErrorY", Vertex_ErrorY, &b_Vertex_ErrorY);
    fChain->SetBranchAddress("Vertex.ErrorZ", Vertex_ErrorZ, &b_Vertex_ErrorZ);
    fChain->SetBranchAddress("Vertex.Index", Vertex_Index, &b_Vertex_Index);
    fChain->SetBranchAddress("Vertex.NDF", Vertex_NDF, &b_Vertex_NDF);
    fChain->SetBranchAddress("Vertex.Sigma", Vertex_Sigma, &b_Vertex_Sigma);
    fChain->SetBranchAddress("Vertex.SumPT2", Vertex_SumPT2, &b_Vertex_SumPT2);
    fChain->SetBranchAddress("Vertex.GenSumPT2", Vertex_GenSumPT2,
                             &b_Vertex_GenSumPT2);
    fChain->SetBranchAddress("Vertex.GenDeltaZ", Vertex_GenDeltaZ,
                             &b_Vertex_GenDeltaZ);
    fChain->SetBranchAddress("Vertex.BTVSumPT2", Vertex_BTVSumPT2,
                             &b_Vertex_BTVSumPT2);
    fChain->SetBranchAddress("Vertex_size", &Vertex_size, &b_Vertex_size);
}