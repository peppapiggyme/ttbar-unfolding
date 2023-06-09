//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 25 23:47:18 2023 by ROOT version 6.28/00
// from TTree Delphes/Analysis tree
// found on file: ttbar_nlo_ATLAS_PileUp.root
//////////////////////////////////////////////////////////

#ifndef DelphesTree_hpp
#define DelphesTree_hpp

#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TObject.h"

class DelphesTree
{
public:
    DelphesTree() : fChain(0) {}
    virtual ~DelphesTree() {}
    virtual void  Loop() = 0;
    virtual Int_t GetEntry(Long64_t entry);
    virtual void  Init(TTree* tree);

public:
    TTree* fChain;   //! pointer to the analyzed TTree or TChain
    Int_t  fCurrent; //! current Tree number in a TChain

    // Fixed size dimensions of array or collections stored in the TTree if any.
    static constexpr Int_t kMaxEvent        = 1;
    static constexpr Int_t kMaxWeight       = 11;
    static constexpr Int_t kMaxParticle     = 1733;
    static constexpr Int_t kMaxGenJet       = 14;
    static constexpr Int_t kMaxGenMissingET = 1;
    static constexpr Int_t kMaxJet          = 14;
    static constexpr Int_t kMaxElectron     = 2;
    static constexpr Int_t kMaxPhoton       = 2;
    static constexpr Int_t kMaxMuon         = 3;
    static constexpr Int_t kMaxMissingET    = 1;
    static constexpr Int_t kMaxScalarHT     = 1;
    static constexpr Int_t kMaxRho          = 3;
    static constexpr Int_t kMaxVertex       = 78;

    // Declaration of leaf types
    Int_t          Event_;
    UInt_t         Event_fUniqueID[kMaxEvent];         //[Event_]
    UInt_t         Event_fBits[kMaxEvent];             //[Event_]
    Long64_t       Event_Number[kMaxEvent];            //[Event_]
    Float_t        Event_ReadTime[kMaxEvent];          //[Event_]
    Float_t        Event_ProcTime[kMaxEvent];          //[Event_]
    Int_t          Event_ProcessID[kMaxEvent];         //[Event_]
    Int_t          Event_MPI[kMaxEvent];               //[Event_]
    Float_t        Event_Weight[kMaxEvent];            //[Event_]
    Float_t        Event_CrossSection[kMaxEvent];      //[Event_]
    Float_t        Event_CrossSectionError[kMaxEvent]; //[Event_]
    Float_t        Event_Scale[kMaxEvent];             //[Event_]
    Float_t        Event_AlphaQED[kMaxEvent];          //[Event_]
    Float_t        Event_AlphaQCD[kMaxEvent];          //[Event_]
    Int_t          Event_ID1[kMaxEvent];               //[Event_]
    Int_t          Event_ID2[kMaxEvent];               //[Event_]
    Float_t        Event_X1[kMaxEvent];                //[Event_]
    Float_t        Event_X2[kMaxEvent];                //[Event_]
    Float_t        Event_ScalePDF[kMaxEvent];          //[Event_]
    Float_t        Event_PDF1[kMaxEvent];              //[Event_]
    Float_t        Event_PDF2[kMaxEvent];              //[Event_]
    Int_t          Event_size;
    Int_t          Weight_;
    UInt_t         Weight_fUniqueID[kMaxWeight]; //[Weight_]
    UInt_t         Weight_fBits[kMaxWeight];     //[Weight_]
    Float_t        Weight_Weight[kMaxWeight];    //[Weight_]
    Int_t          Weight_size;
    Int_t          Particle_;
    UInt_t         Particle_fUniqueID[kMaxParticle]; //[Particle_]
    UInt_t         Particle_fBits[kMaxParticle];     //[Particle_]
    Int_t          Particle_PID[kMaxParticle];       //[Particle_]
    Int_t          Particle_Status[kMaxParticle];    //[Particle_]
    Int_t          Particle_IsPU[kMaxParticle];      //[Particle_]
    Int_t          Particle_M1[kMaxParticle];        //[Particle_]
    Int_t          Particle_M2[kMaxParticle];        //[Particle_]
    Int_t          Particle_D1[kMaxParticle];        //[Particle_]
    Int_t          Particle_D2[kMaxParticle];        //[Particle_]
    Int_t          Particle_Charge[kMaxParticle];    //[Particle_]
    Float_t        Particle_Mass[kMaxParticle];      //[Particle_]
    Float_t        Particle_E[kMaxParticle];         //[Particle_]
    Float_t        Particle_Px[kMaxParticle];        //[Particle_]
    Float_t        Particle_Py[kMaxParticle];        //[Particle_]
    Float_t        Particle_Pz[kMaxParticle];        //[Particle_]
    Float_t        Particle_P[kMaxParticle];         //[Particle_]
    Float_t        Particle_PT[kMaxParticle];        //[Particle_]
    Float_t        Particle_Eta[kMaxParticle];       //[Particle_]
    Float_t        Particle_Phi[kMaxParticle];       //[Particle_]
    Float_t        Particle_Rapidity[kMaxParticle];  //[Particle_]
    Float_t        Particle_T[kMaxParticle];         //[Particle_]
    Float_t        Particle_X[kMaxParticle];         //[Particle_]
    Float_t        Particle_Y[kMaxParticle];         //[Particle_]
    Float_t        Particle_Z[kMaxParticle];         //[Particle_]
    Int_t          Particle_size;
    Int_t          GenJet_;
    UInt_t         GenJet_fUniqueID[kMaxGenJet];             //[GenJet_]
    UInt_t         GenJet_fBits[kMaxGenJet];                 //[GenJet_]
    Float_t        GenJet_PT[kMaxGenJet];                    //[GenJet_]
    Float_t        GenJet_Eta[kMaxGenJet];                   //[GenJet_]
    Float_t        GenJet_Phi[kMaxGenJet];                   //[GenJet_]
    Float_t        GenJet_T[kMaxGenJet];                     //[GenJet_]
    Float_t        GenJet_Mass[kMaxGenJet];                  //[GenJet_]
    Float_t        GenJet_DeltaEta[kMaxGenJet];              //[GenJet_]
    Float_t        GenJet_DeltaPhi[kMaxGenJet];              //[GenJet_]
    UInt_t         GenJet_Flavor[kMaxGenJet];                //[GenJet_]
    UInt_t         GenJet_FlavorAlgo[kMaxGenJet];            //[GenJet_]
    UInt_t         GenJet_FlavorPhys[kMaxGenJet];            //[GenJet_]
    UInt_t         GenJet_BTag[kMaxGenJet];                  //[GenJet_]
    UInt_t         GenJet_BTagAlgo[kMaxGenJet];              //[GenJet_]
    UInt_t         GenJet_BTagPhys[kMaxGenJet];              //[GenJet_]
    UInt_t         GenJet_TauTag[kMaxGenJet];                //[GenJet_]
    Float_t        GenJet_TauWeight[kMaxGenJet];             //[GenJet_]
    Int_t          GenJet_Charge[kMaxGenJet];                //[GenJet_]
    Float_t        GenJet_EhadOverEem[kMaxGenJet];           //[GenJet_]
    Int_t          GenJet_NCharged[kMaxGenJet];              //[GenJet_]
    Int_t          GenJet_NNeutrals[kMaxGenJet];             //[GenJet_]
    Float_t        GenJet_NeutralEnergyFraction[kMaxGenJet]; //[GenJet_]
    Float_t        GenJet_ChargedEnergyFraction[kMaxGenJet]; //[GenJet_]
    Float_t        GenJet_Beta[kMaxGenJet];                  //[GenJet_]
    Float_t        GenJet_BetaStar[kMaxGenJet];              //[GenJet_]
    Float_t        GenJet_MeanSqDeltaR[kMaxGenJet];          //[GenJet_]
    Float_t        GenJet_PTD[kMaxGenJet];                   //[GenJet_]
    Float_t        GenJet_FracPt[kMaxGenJet][5];             //[GenJet_]
    Float_t        GenJet_Tau[kMaxGenJet][5];                //[GenJet_]
    TLorentzVector GenJet_SoftDroppedJet[kMaxGenJet];
    TLorentzVector GenJet_SoftDroppedSubJet1[kMaxGenJet];
    TLorentzVector GenJet_SoftDroppedSubJet2[kMaxGenJet];
    TLorentzVector GenJet_TrimmedP4[5][kMaxGenJet];
    TLorentzVector GenJet_PrunedP4[5][kMaxGenJet];
    TLorentzVector GenJet_SoftDroppedP4[5][kMaxGenJet];
    Int_t          GenJet_NSubJetsTrimmed[kMaxGenJet];     //[GenJet_]
    Int_t          GenJet_NSubJetsPruned[kMaxGenJet];      //[GenJet_]
    Int_t          GenJet_NSubJetsSoftDropped[kMaxGenJet]; //[GenJet_]
    Double_t       GenJet_ExclYmerge23[kMaxGenJet];        //[GenJet_]
    Double_t       GenJet_ExclYmerge34[kMaxGenJet];        //[GenJet_]
    Double_t       GenJet_ExclYmerge45[kMaxGenJet];        //[GenJet_]
    Double_t       GenJet_ExclYmerge56[kMaxGenJet];        //[GenJet_]
    TLorentzVector GenJet_Area[kMaxGenJet];
    Int_t          GenJet_size;
    Int_t          GenMissingET_;
    UInt_t         GenMissingET_fUniqueID[kMaxGenMissingET]; //[GenMissingET_]
    UInt_t         GenMissingET_fBits[kMaxGenMissingET];     //[GenMissingET_]
    Float_t        GenMissingET_MET[kMaxGenMissingET];       //[GenMissingET_]
    Float_t        GenMissingET_Eta[kMaxGenMissingET];       //[GenMissingET_]
    Float_t        GenMissingET_Phi[kMaxGenMissingET];       //[GenMissingET_]
    Int_t          GenMissingET_size;
    Int_t          Jet_;
    UInt_t         Jet_fUniqueID[kMaxJet];             //[Jet_]
    UInt_t         Jet_fBits[kMaxJet];                 //[Jet_]
    Float_t        Jet_PT[kMaxJet];                    //[Jet_]
    Float_t        Jet_Eta[kMaxJet];                   //[Jet_]
    Float_t        Jet_Phi[kMaxJet];                   //[Jet_]
    Float_t        Jet_T[kMaxJet];                     //[Jet_]
    Float_t        Jet_Mass[kMaxJet];                  //[Jet_]
    Float_t        Jet_DeltaEta[kMaxJet];              //[Jet_]
    Float_t        Jet_DeltaPhi[kMaxJet];              //[Jet_]
    UInt_t         Jet_Flavor[kMaxJet];                //[Jet_]
    UInt_t         Jet_FlavorAlgo[kMaxJet];            //[Jet_]
    UInt_t         Jet_FlavorPhys[kMaxJet];            //[Jet_]
    UInt_t         Jet_BTag[kMaxJet];                  //[Jet_]
    UInt_t         Jet_BTagAlgo[kMaxJet];              //[Jet_]
    UInt_t         Jet_BTagPhys[kMaxJet];              //[Jet_]
    UInt_t         Jet_TauTag[kMaxJet];                //[Jet_]
    Float_t        Jet_TauWeight[kMaxJet];             //[Jet_]
    Int_t          Jet_Charge[kMaxJet];                //[Jet_]
    Float_t        Jet_EhadOverEem[kMaxJet];           //[Jet_]
    Int_t          Jet_NCharged[kMaxJet];              //[Jet_]
    Int_t          Jet_NNeutrals[kMaxJet];             //[Jet_]
    Float_t        Jet_NeutralEnergyFraction[kMaxJet]; //[Jet_]
    Float_t        Jet_ChargedEnergyFraction[kMaxJet]; //[Jet_]
    Float_t        Jet_Beta[kMaxJet];                  //[Jet_]
    Float_t        Jet_BetaStar[kMaxJet];              //[Jet_]
    Float_t        Jet_MeanSqDeltaR[kMaxJet];          //[Jet_]
    Float_t        Jet_PTD[kMaxJet];                   //[Jet_]
    Float_t        Jet_FracPt[kMaxJet][5];             //[Jet_]
    Float_t        Jet_Tau[kMaxJet][5];                //[Jet_]
    TLorentzVector Jet_SoftDroppedJet[kMaxJet];
    TLorentzVector Jet_SoftDroppedSubJet1[kMaxJet];
    TLorentzVector Jet_SoftDroppedSubJet2[kMaxJet];
    TLorentzVector Jet_TrimmedP4[5][kMaxJet];
    TLorentzVector Jet_PrunedP4[5][kMaxJet];
    TLorentzVector Jet_SoftDroppedP4[5][kMaxJet];
    Int_t          Jet_NSubJetsTrimmed[kMaxJet];     //[Jet_]
    Int_t          Jet_NSubJetsPruned[kMaxJet];      //[Jet_]
    Int_t          Jet_NSubJetsSoftDropped[kMaxJet]; //[Jet_]
    Double_t       Jet_ExclYmerge23[kMaxJet];        //[Jet_]
    Double_t       Jet_ExclYmerge34[kMaxJet];        //[Jet_]
    Double_t       Jet_ExclYmerge45[kMaxJet];        //[Jet_]
    Double_t       Jet_ExclYmerge56[kMaxJet];        //[Jet_]
    TLorentzVector Jet_Area[kMaxJet];
    Int_t          Jet_size;
    Int_t          Electron_;
    UInt_t         Electron_fUniqueID[kMaxElectron];           //[Electron_]
    UInt_t         Electron_fBits[kMaxElectron];               //[Electron_]
    Float_t        Electron_PT[kMaxElectron];                  //[Electron_]
    Float_t        Electron_Eta[kMaxElectron];                 //[Electron_]
    Float_t        Electron_Phi[kMaxElectron];                 //[Electron_]
    Float_t        Electron_T[kMaxElectron];                   //[Electron_]
    Int_t          Electron_Charge[kMaxElectron];              //[Electron_]
    Float_t        Electron_EhadOverEem[kMaxElectron];         //[Electron_]
    Float_t        Electron_IsolationVar[kMaxElectron];        //[Electron_]
    Float_t        Electron_IsolationVarRhoCorr[kMaxElectron]; //[Electron_]
    Float_t        Electron_SumPtCharged[kMaxElectron];        //[Electron_]
    Float_t        Electron_SumPtNeutral[kMaxElectron];        //[Electron_]
    Float_t        Electron_SumPtChargedPU[kMaxElectron];      //[Electron_]
    Float_t        Electron_SumPt[kMaxElectron];               //[Electron_]
    Float_t        Electron_D0[kMaxElectron];                  //[Electron_]
    Float_t        Electron_DZ[kMaxElectron];                  //[Electron_]
    Float_t        Electron_ErrorD0[kMaxElectron];             //[Electron_]
    Float_t        Electron_ErrorDZ[kMaxElectron];             //[Electron_]
    Int_t          Electron_size;
    Int_t          Photon_;
    UInt_t         Photon_fUniqueID[kMaxPhoton];           //[Photon_]
    UInt_t         Photon_fBits[kMaxPhoton];               //[Photon_]
    Float_t        Photon_PT[kMaxPhoton];                  //[Photon_]
    Float_t        Photon_Eta[kMaxPhoton];                 //[Photon_]
    Float_t        Photon_Phi[kMaxPhoton];                 //[Photon_]
    Float_t        Photon_E[kMaxPhoton];                   //[Photon_]
    Float_t        Photon_T[kMaxPhoton];                   //[Photon_]
    Float_t        Photon_EhadOverEem[kMaxPhoton];         //[Photon_]
    Float_t        Photon_IsolationVar[kMaxPhoton];        //[Photon_]
    Float_t        Photon_IsolationVarRhoCorr[kMaxPhoton]; //[Photon_]
    Float_t        Photon_SumPtCharged[kMaxPhoton];        //[Photon_]
    Float_t        Photon_SumPtNeutral[kMaxPhoton];        //[Photon_]
    Float_t        Photon_SumPtChargedPU[kMaxPhoton];      //[Photon_]
    Float_t        Photon_SumPt[kMaxPhoton];               //[Photon_]
    Int_t          Photon_Status[kMaxPhoton];              //[Photon_]
    Int_t          Photon_size;
    Int_t          Muon_;
    UInt_t         Muon_fUniqueID[kMaxMuon];           //[Muon_]
    UInt_t         Muon_fBits[kMaxMuon];               //[Muon_]
    Float_t        Muon_PT[kMaxMuon];                  //[Muon_]
    Float_t        Muon_Eta[kMaxMuon];                 //[Muon_]
    Float_t        Muon_Phi[kMaxMuon];                 //[Muon_]
    Float_t        Muon_T[kMaxMuon];                   //[Muon_]
    Int_t          Muon_Charge[kMaxMuon];              //[Muon_]
    Float_t        Muon_IsolationVar[kMaxMuon];        //[Muon_]
    Float_t        Muon_IsolationVarRhoCorr[kMaxMuon]; //[Muon_]
    Float_t        Muon_SumPtCharged[kMaxMuon];        //[Muon_]
    Float_t        Muon_SumPtNeutral[kMaxMuon];        //[Muon_]
    Float_t        Muon_SumPtChargedPU[kMaxMuon];      //[Muon_]
    Float_t        Muon_SumPt[kMaxMuon];               //[Muon_]
    Float_t        Muon_D0[kMaxMuon];                  //[Muon_]
    Float_t        Muon_DZ[kMaxMuon];                  //[Muon_]
    Float_t        Muon_ErrorD0[kMaxMuon];             //[Muon_]
    Float_t        Muon_ErrorDZ[kMaxMuon];             //[Muon_]
    Int_t          Muon_size;
    Int_t          MissingET_;
    UInt_t         MissingET_fUniqueID[kMaxMissingET]; //[MissingET_]
    UInt_t         MissingET_fBits[kMaxMissingET];     //[MissingET_]
    Float_t        MissingET_MET[kMaxMissingET];       //[MissingET_]
    Float_t        MissingET_Eta[kMaxMissingET];       //[MissingET_]
    Float_t        MissingET_Phi[kMaxMissingET];       //[MissingET_]
    Int_t          MissingET_size;
    Int_t          ScalarHT_;
    UInt_t         ScalarHT_fUniqueID[kMaxScalarHT]; //[ScalarHT_]
    UInt_t         ScalarHT_fBits[kMaxScalarHT];     //[ScalarHT_]
    Float_t        ScalarHT_HT[kMaxScalarHT];        //[ScalarHT_]
    Int_t          ScalarHT_size;
    Int_t          Rho_;
    UInt_t         Rho_fUniqueID[kMaxRho]; //[Rho_]
    UInt_t         Rho_fBits[kMaxRho];     //[Rho_]
    Float_t        Rho_Rho[kMaxRho];       //[Rho_]
    Float_t        Rho_Edges[kMaxRho][2];  //[Rho_]
    Int_t          Rho_size;
    Int_t          Vertex_;
    UInt_t         Vertex_fUniqueID[kMaxVertex]; //[Vertex_]
    UInt_t         Vertex_fBits[kMaxVertex];     //[Vertex_]
    Float_t        Vertex_T[kMaxVertex];         //[Vertex_]
    Float_t        Vertex_X[kMaxVertex];         //[Vertex_]
    Float_t        Vertex_Y[kMaxVertex];         //[Vertex_]
    Float_t        Vertex_Z[kMaxVertex];         //[Vertex_]
    Double_t       Vertex_ErrorT[kMaxVertex];    //[Vertex_]
    Double_t       Vertex_ErrorX[kMaxVertex];    //[Vertex_]
    Double_t       Vertex_ErrorY[kMaxVertex];    //[Vertex_]
    Double_t       Vertex_ErrorZ[kMaxVertex];    //[Vertex_]
    Int_t          Vertex_Index[kMaxVertex];     //[Vertex_]
    Int_t          Vertex_NDF[kMaxVertex];       //[Vertex_]
    Double_t       Vertex_Sigma[kMaxVertex];     //[Vertex_]
    Double_t       Vertex_SumPT2[kMaxVertex];    //[Vertex_]
    Double_t       Vertex_GenSumPT2[kMaxVertex]; //[Vertex_]
    Double_t       Vertex_GenDeltaZ[kMaxVertex]; //[Vertex_]
    Double_t       Vertex_BTVSumPT2[kMaxVertex]; //[Vertex_]
    Int_t          Vertex_size;

    // List of branches
    TBranch* b_Event_;                       //!
    TBranch* b_Event_fUniqueID;              //!
    TBranch* b_Event_fBits;                  //!
    TBranch* b_Event_Number;                 //!
    TBranch* b_Event_ReadTime;               //!
    TBranch* b_Event_ProcTime;               //!
    TBranch* b_Event_ProcessID;              //!
    TBranch* b_Event_MPI;                    //!
    TBranch* b_Event_Weight;                 //!
    TBranch* b_Event_CrossSection;           //!
    TBranch* b_Event_CrossSectionError;      //!
    TBranch* b_Event_Scale;                  //!
    TBranch* b_Event_AlphaQED;               //!
    TBranch* b_Event_AlphaQCD;               //!
    TBranch* b_Event_ID1;                    //!
    TBranch* b_Event_ID2;                    //!
    TBranch* b_Event_X1;                     //!
    TBranch* b_Event_X2;                     //!
    TBranch* b_Event_ScalePDF;               //!
    TBranch* b_Event_PDF1;                   //!
    TBranch* b_Event_PDF2;                   //!
    TBranch* b_Event_size;                   //!
    TBranch* b_Weight_;                      //!
    TBranch* b_Weight_fUniqueID;             //!
    TBranch* b_Weight_fBits;                 //!
    TBranch* b_Weight_Weight;                //!
    TBranch* b_Weight_size;                  //!
    TBranch* b_Particle_;                    //!
    TBranch* b_Particle_fUniqueID;           //!
    TBranch* b_Particle_fBits;               //!
    TBranch* b_Particle_PID;                 //!
    TBranch* b_Particle_Status;              //!
    TBranch* b_Particle_IsPU;                //!
    TBranch* b_Particle_M1;                  //!
    TBranch* b_Particle_M2;                  //!
    TBranch* b_Particle_D1;                  //!
    TBranch* b_Particle_D2;                  //!
    TBranch* b_Particle_Charge;              //!
    TBranch* b_Particle_Mass;                //!
    TBranch* b_Particle_E;                   //!
    TBranch* b_Particle_Px;                  //!
    TBranch* b_Particle_Py;                  //!
    TBranch* b_Particle_Pz;                  //!
    TBranch* b_Particle_P;                   //!
    TBranch* b_Particle_PT;                  //!
    TBranch* b_Particle_Eta;                 //!
    TBranch* b_Particle_Phi;                 //!
    TBranch* b_Particle_Rapidity;            //!
    TBranch* b_Particle_T;                   //!
    TBranch* b_Particle_X;                   //!
    TBranch* b_Particle_Y;                   //!
    TBranch* b_Particle_Z;                   //!
    TBranch* b_Particle_size;                //!
    TBranch* b_GenJet_;                      //!
    TBranch* b_GenJet_fUniqueID;             //!
    TBranch* b_GenJet_fBits;                 //!
    TBranch* b_GenJet_PT;                    //!
    TBranch* b_GenJet_Eta;                   //!
    TBranch* b_GenJet_Phi;                   //!
    TBranch* b_GenJet_T;                     //!
    TBranch* b_GenJet_Mass;                  //!
    TBranch* b_GenJet_DeltaEta;              //!
    TBranch* b_GenJet_DeltaPhi;              //!
    TBranch* b_GenJet_Flavor;                //!
    TBranch* b_GenJet_FlavorAlgo;            //!
    TBranch* b_GenJet_FlavorPhys;            //!
    TBranch* b_GenJet_BTag;                  //!
    TBranch* b_GenJet_BTagAlgo;              //!
    TBranch* b_GenJet_BTagPhys;              //!
    TBranch* b_GenJet_TauTag;                //!
    TBranch* b_GenJet_TauWeight;             //!
    TBranch* b_GenJet_Charge;                //!
    TBranch* b_GenJet_EhadOverEem;           //!
    TBranch* b_GenJet_NCharged;              //!
    TBranch* b_GenJet_NNeutrals;             //!
    TBranch* b_GenJet_NeutralEnergyFraction; //!
    TBranch* b_GenJet_ChargedEnergyFraction; //!
    TBranch* b_GenJet_Beta;                  //!
    TBranch* b_GenJet_BetaStar;              //!
    TBranch* b_GenJet_MeanSqDeltaR;          //!
    TBranch* b_GenJet_PTD;                   //!
    TBranch* b_GenJet_FracPt;                //!
    TBranch* b_GenJet_Tau;                   //!
    TBranch* b_GenJet_SoftDroppedJet;        //!
    TBranch* b_GenJet_SoftDroppedSubJet1;    //!
    TBranch* b_GenJet_SoftDroppedSubJet2;    //!
    TBranch* b_GenJet_TrimmedP4;             //!
    TBranch* b_GenJet_PrunedP4;              //!
    TBranch* b_GenJet_SoftDroppedP4;         //!
    TBranch* b_GenJet_NSubJetsTrimmed;       //!
    TBranch* b_GenJet_NSubJetsPruned;        //!
    TBranch* b_GenJet_NSubJetsSoftDropped;   //!
    TBranch* b_GenJet_ExclYmerge23;          //!
    TBranch* b_GenJet_ExclYmerge34;          //!
    TBranch* b_GenJet_ExclYmerge45;          //!
    TBranch* b_GenJet_ExclYmerge56;          //!
    TBranch* b_GenJet_Area;                  //!
    TBranch* b_GenJet_size;                  //!
    TBranch* b_GenMissingET_;                //!
    TBranch* b_GenMissingET_fUniqueID;       //!
    TBranch* b_GenMissingET_fBits;           //!
    TBranch* b_GenMissingET_MET;             //!
    TBranch* b_GenMissingET_Eta;             //!
    TBranch* b_GenMissingET_Phi;             //!
    TBranch* b_GenMissingET_size;            //!
    TBranch* b_Jet_;                         //!
    TBranch* b_Jet_fUniqueID;                //!
    TBranch* b_Jet_fBits;                    //!
    TBranch* b_Jet_PT;                       //!
    TBranch* b_Jet_Eta;                      //!
    TBranch* b_Jet_Phi;                      //!
    TBranch* b_Jet_T;                        //!
    TBranch* b_Jet_Mass;                     //!
    TBranch* b_Jet_DeltaEta;                 //!
    TBranch* b_Jet_DeltaPhi;                 //!
    TBranch* b_Jet_Flavor;                   //!
    TBranch* b_Jet_FlavorAlgo;               //!
    TBranch* b_Jet_FlavorPhys;               //!
    TBranch* b_Jet_BTag;                     //!
    TBranch* b_Jet_BTagAlgo;                 //!
    TBranch* b_Jet_BTagPhys;                 //!
    TBranch* b_Jet_TauTag;                   //!
    TBranch* b_Jet_TauWeight;                //!
    TBranch* b_Jet_Charge;                   //!
    TBranch* b_Jet_EhadOverEem;              //!
    TBranch* b_Jet_NCharged;                 //!
    TBranch* b_Jet_NNeutrals;                //!
    TBranch* b_Jet_NeutralEnergyFraction;    //!
    TBranch* b_Jet_ChargedEnergyFraction;    //!
    TBranch* b_Jet_Beta;                     //!
    TBranch* b_Jet_BetaStar;                 //!
    TBranch* b_Jet_MeanSqDeltaR;             //!
    TBranch* b_Jet_PTD;                      //!
    TBranch* b_Jet_FracPt;                   //!
    TBranch* b_Jet_Tau;                      //!
    TBranch* b_Jet_SoftDroppedJet;           //!
    TBranch* b_Jet_SoftDroppedSubJet1;       //!
    TBranch* b_Jet_SoftDroppedSubJet2;       //!
    TBranch* b_Jet_TrimmedP4;                //!
    TBranch* b_Jet_PrunedP4;                 //!
    TBranch* b_Jet_SoftDroppedP4;            //!
    TBranch* b_Jet_NSubJetsTrimmed;          //!
    TBranch* b_Jet_NSubJetsPruned;           //!
    TBranch* b_Jet_NSubJetsSoftDropped;      //!
    TBranch* b_Jet_ExclYmerge23;             //!
    TBranch* b_Jet_ExclYmerge34;             //!
    TBranch* b_Jet_ExclYmerge45;             //!
    TBranch* b_Jet_ExclYmerge56;             //!
    TBranch* b_Jet_Area;                     //!
    TBranch* b_Jet_size;                     //!
    TBranch* b_Electron_;                    //!
    TBranch* b_Electron_fUniqueID;           //!
    TBranch* b_Electron_fBits;               //!
    TBranch* b_Electron_PT;                  //!
    TBranch* b_Electron_Eta;                 //!
    TBranch* b_Electron_Phi;                 //!
    TBranch* b_Electron_T;                   //!
    TBranch* b_Electron_Charge;              //!
    TBranch* b_Electron_EhadOverEem;         //!
    TBranch* b_Electron_IsolationVar;        //!
    TBranch* b_Electron_IsolationVarRhoCorr; //!
    TBranch* b_Electron_SumPtCharged;        //!
    TBranch* b_Electron_SumPtNeutral;        //!
    TBranch* b_Electron_SumPtChargedPU;      //!
    TBranch* b_Electron_SumPt;               //!
    TBranch* b_Electron_D0;                  //!
    TBranch* b_Electron_DZ;                  //!
    TBranch* b_Electron_ErrorD0;             //!
    TBranch* b_Electron_ErrorDZ;             //!
    TBranch* b_Electron_size;                //!
    TBranch* b_Photon_;                      //!
    TBranch* b_Photon_fUniqueID;             //!
    TBranch* b_Photon_fBits;                 //!
    TBranch* b_Photon_PT;                    //!
    TBranch* b_Photon_Eta;                   //!
    TBranch* b_Photon_Phi;                   //!
    TBranch* b_Photon_E;                     //!
    TBranch* b_Photon_T;                     //!
    TBranch* b_Photon_EhadOverEem;           //!
    TBranch* b_Photon_IsolationVar;          //!
    TBranch* b_Photon_IsolationVarRhoCorr;   //!
    TBranch* b_Photon_SumPtCharged;          //!
    TBranch* b_Photon_SumPtNeutral;          //!
    TBranch* b_Photon_SumPtChargedPU;        //!
    TBranch* b_Photon_SumPt;                 //!
    TBranch* b_Photon_Status;                //!
    TBranch* b_Photon_size;                  //!
    TBranch* b_Muon_;                        //!
    TBranch* b_Muon_fUniqueID;               //!
    TBranch* b_Muon_fBits;                   //!
    TBranch* b_Muon_PT;                      //!
    TBranch* b_Muon_Eta;                     //!
    TBranch* b_Muon_Phi;                     //!
    TBranch* b_Muon_T;                       //!
    TBranch* b_Muon_Charge;                  //!
    TBranch* b_Muon_IsolationVar;            //!
    TBranch* b_Muon_IsolationVarRhoCorr;     //!
    TBranch* b_Muon_SumPtCharged;            //!
    TBranch* b_Muon_SumPtNeutral;            //!
    TBranch* b_Muon_SumPtChargedPU;          //!
    TBranch* b_Muon_SumPt;                   //!
    TBranch* b_Muon_D0;                      //!
    TBranch* b_Muon_DZ;                      //!
    TBranch* b_Muon_ErrorD0;                 //!
    TBranch* b_Muon_ErrorDZ;                 //!
    TBranch* b_Muon_size;                    //!
    TBranch* b_MissingET_;                   //!
    TBranch* b_MissingET_fUniqueID;          //!
    TBranch* b_MissingET_fBits;              //!
    TBranch* b_MissingET_MET;                //!
    TBranch* b_MissingET_Eta;                //!
    TBranch* b_MissingET_Phi;                //!
    TBranch* b_MissingET_size;               //!
    TBranch* b_ScalarHT_;                    //!
    TBranch* b_ScalarHT_fUniqueID;           //!
    TBranch* b_ScalarHT_fBits;               //!
    TBranch* b_ScalarHT_HT;                  //!
    TBranch* b_ScalarHT_size;                //!
    TBranch* b_Rho_;                         //!
    TBranch* b_Rho_fUniqueID;                //!
    TBranch* b_Rho_fBits;                    //!
    TBranch* b_Rho_Rho;                      //!
    TBranch* b_Rho_Edges;                    //!
    TBranch* b_Rho_size;                     //!
    TBranch* b_Vertex_;                      //!
    TBranch* b_Vertex_fUniqueID;             //!
    TBranch* b_Vertex_fBits;                 //!
    TBranch* b_Vertex_T;                     //!
    TBranch* b_Vertex_X;                     //!
    TBranch* b_Vertex_Y;                     //!
    TBranch* b_Vertex_Z;                     //!
    TBranch* b_Vertex_ErrorT;                //!
    TBranch* b_Vertex_ErrorX;                //!
    TBranch* b_Vertex_ErrorY;                //!
    TBranch* b_Vertex_ErrorZ;                //!
    TBranch* b_Vertex_Index;                 //!
    TBranch* b_Vertex_NDF;                   //!
    TBranch* b_Vertex_Sigma;                 //!
    TBranch* b_Vertex_SumPT2;                //!
    TBranch* b_Vertex_GenSumPT2;             //!
    TBranch* b_Vertex_GenDeltaZ;             //!
    TBranch* b_Vertex_BTVSumPT2;             //!
    TBranch* b_Vertex_size;                  //!
};

#endif
