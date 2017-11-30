#ifndef RunSel_h
#define RunSel_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>



// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class RunSel : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Subrun;
   Int_t           Event;
   Char_t          IsData;
   Int_t           NumberOfHits;
   Short_t         Hit_View[10597];   //[no_hits]
   Short_t         Hit_Channel[10597];   //[no_hits]
   Float_t         Hit_PeakTime[10597];   //[no_hits]
   Float_t         Hit_ChargeSummedADC[10597];   //[no_hits]
   Float_t         Hit_ChargeIntegral[10597];   //[no_hits]
   Float_t         Hit_PeakHeight[10597];   //[no_hits]
   Float_t         Hit_StartTime[10597];   //[no_hits]
   Float_t         Hit_EndTime[10597];   //[no_hits]
   Float_t         Hit_Width[10597];   //[no_hits]
   Float_t         Hit_GoodnessOfFit[10597];   //[no_hits]
   Short_t         Hit_Multiplicity[10597];   //[no_hits]
   Short_t         Hit_TrackID[10597];   //[no_hits]
   Short_t         Hit_ClusterID[10597];   //[no_hits]
   Short_t         NumberOfClusters;
   Short_t         ClusterID[586];   //[nclusters]
   Short_t         Cluster_NumberOfHits[586];   //[nclusters]
   Short_t         Cluster_View[586];   //[nclusters]
   Float_t         Cluster_ChargeIntegral[586];   //[nclusters]
   Float_t         Cluster_ChargeIntegralAveragePerHit[586];   //[nclusters]
   Short_t         Cluster_StartChannel[586];   //[nclusters]
   Short_t         Cluster_StartTick[586];   //[nclusters]
   Short_t         Cluster_EndChannel[586];   //[nclusters]
   Short_t         cluster_EndTick[586];   //[nclusters]
   Float_t         Cluster_StartCharge[586];   //[nclusters]
   Float_t         Cluster_StartAngle[586];   //[nclusters]
   Float_t         Cluster_EndCharge[586];   //[nclusters]
   Float_t         Cluster_EndAngle[586];   //[nclusters]
   Short_t         NumberOfTracks_pmtrack;
   Short_t         TrackID_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_PitchInViews_pmtrack[106][2];   //[NumberOfTracks_pmtrack]
   Short_t         Track_NumberOfHitsPerView_pmtrack[106][2];   //[NumberOfTracks_pmtrack]
   Float_t         Track_dEdx_pmtrack[10597];   //[no_hits]
   Float_t         Track_dQdx_pmtrack[10597];   //[no_hits]
   Float_t         Track_TPC_pmtrack[10597];   //[no_hits]
   Float_t         Track_HitX_pmtrack[10597];   //[no_hits]
   Float_t         Track_HitY_pmtrack[10597];   //[no_hits]
   Float_t         Track_HitZ_pmtrack[10597];   //[no_hits]
   Float_t         Track_StartX_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_StartY_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_StartZ_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_StartDistanceToBoundary_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_EndX_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_EndY_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_EndZ_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_EndDistanceToBoundary_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_Theta_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_Phi_pmtrack[106];   //[NumberOfTracks_pmtrack]
   Float_t         Track_Length_pmtrack[106];   //[NumberOfTracks_pmtrack]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_subrun;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isdata;   //!
   TBranch        *b_no_hits;   //!
   TBranch        *b_Hit_View;   //!
   TBranch        *b_Hit_Channel;   //!
   TBranch        *b_Hit_PeakTime;   //!
   TBranch        *b_Hit_ChargeSummedADC;   //!
   TBranch        *b_Hit_ChargeIntegral;   //!
   TBranch        *b_Hit_PeakHeight;   //!
   TBranch        *b_Hit_StartTime;   //!
   TBranch        *b_Hit_EndTime;   //!
   TBranch        *b_Hit_Width;   //!
   TBranch        *b_Hit_GoodnessOfFit;   //!
   TBranch        *b_Hit_Multiplicity;   //!
   TBranch        *b_Hit_TrackID;   //!
   TBranch        *b_Hit_ClusterID;   //!
   TBranch        *b_nclusters;   //!
   TBranch        *b_ClusterID;   //!
   TBranch        *b_Cluster_NumberOfHits;   //!
   TBranch        *b_Cluster_View;   //!
   TBranch        *b_Cluster_ChargeIntegral;   //!
   TBranch        *b_Cluster_ChargeIntegralAveragePerHit;   //!
   TBranch        *b_Cluster_StartChannel;   //!
   TBranch        *b_Cluster_StartTick;   //!
   TBranch        *b_Cluster_EndChannel;   //!
   TBranch        *b_cluster_EndTick;   //!
   TBranch        *b_Cluster_StartCharge;   //!
   TBranch        *b_Cluster_StartAngle;   //!
   TBranch        *b_Cluster_EndCharge;   //!
   TBranch        *b_Cluster_EndAngle;   //!
   TBranch        *b_NumberOfTracks_pmtrack;   //!
   TBranch        *b_TrackID_pmtrack;   //!
   TBranch        *b_Track_PitchInViews_pmtrack;   //!
   TBranch        *b_Track_NumberOfHitsPerView_pmtrack;   //!
   TBranch        *b_Track_dEdx_pmtrack;   //!
   TBranch        *b_Track_dQdx_pmtrack;   //!
   TBranch        *b_Track_TPC_pmtrack;   //!
   TBranch        *b_Track_HitX_pmtrack;   //!
   TBranch        *b_Track_HitY_pmtrack;   //!
   TBranch        *b_Track_HitZ_pmtrack;   //!
   TBranch        *b_Track_StartX_pmtrack;   //!
   TBranch        *b_Track_StartY_pmtrack;   //!
   TBranch        *b_Track_StartZ_pmtrack;   //!
   TBranch        *b_Track_StartDistanceToBoundary_pmtrack;   //!
   TBranch        *b_Track_EndX_pmtrack;   //!
   TBranch        *b_Track_EndY_pmtrack;   //!
   TBranch        *b_Track_EndZ_pmtrack;   //!
   TBranch        *b_Track_EndDistanceToBoundary_pmtrack;   //!
   TBranch        *b_Track_Theta_pmtrack;   //!
   TBranch        *b_Track_Phi_pmtrack;   //!
   TBranch        *b_Track_Length_pmtrack;   //!

   RunSel(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~RunSel() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(RunSel,0);
};

#endif
#ifdef __MAKECINT__ 
#pragma link C++ class RunSel+;
#endif



#ifndef RunSel_cxx
#define RunSel_cxx


void RunSel::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_run);
   fChain->SetBranchAddress("Subrun", &Subrun, &b_subrun);
   fChain->SetBranchAddress("Event", &Event, &b_event);
  // fChain->SetBranchAddress("EventTime", &EventTime, &b_evttime);
   fChain->SetBranchAddress("IsData", &IsData, &b_isdata);
   fChain->SetBranchAddress("NumberOfHits", &NumberOfHits, &b_no_hits);
 //  fChain->SetBranchAddress("Hit_TPC", Hit_TPC, &b_Hit_TPC);
   fChain->SetBranchAddress("Hit_View", Hit_View, &b_Hit_View);
   fChain->SetBranchAddress("Hit_Channel", Hit_Channel, &b_Hit_Channel);
   fChain->SetBranchAddress("Hit_PeakTime", Hit_PeakTime, &b_Hit_PeakTime);
   fChain->SetBranchAddress("Hit_ChargeSummedADC", Hit_ChargeSummedADC, &b_Hit_ChargeSummedADC);
   fChain->SetBranchAddress("Hit_ChargeIntegral", Hit_ChargeIntegral, &b_Hit_ChargeIntegral);
   fChain->SetBranchAddress("Hit_PeakHeight", Hit_PeakHeight, &b_Hit_PeakHeight);
   fChain->SetBranchAddress("Hit_StartTime", Hit_StartTime, &b_Hit_StartTime);
   fChain->SetBranchAddress("Hit_EndTime", Hit_EndTime, &b_Hit_EndTime);
   fChain->SetBranchAddress("Hit_Width", Hit_Width, &b_Hit_Width);
   fChain->SetBranchAddress("Hit_GoodnessOfFit", Hit_GoodnessOfFit, &b_Hit_GoodnessOfFit);
   fChain->SetBranchAddress("Hit_Multiplicity", Hit_Multiplicity, &b_Hit_Multiplicity);
   fChain->SetBranchAddress("Hit_TrackID", Hit_TrackID, &b_Hit_TrackID);
   fChain->SetBranchAddress("Hit_ClusterID", Hit_ClusterID, &b_Hit_ClusterID);
   fChain->SetBranchAddress("NumberOfClusters", &NumberOfClusters, &b_nclusters);
   fChain->SetBranchAddress("ClusterID", ClusterID, &b_ClusterID);
   fChain->SetBranchAddress("Cluster_NumberOfHits", Cluster_NumberOfHits, &b_Cluster_NumberOfHits);
   fChain->SetBranchAddress("Cluster_View", Cluster_View, &b_Cluster_View);
   fChain->SetBranchAddress("Cluster_ChargeIntegral", Cluster_ChargeIntegral, &b_Cluster_ChargeIntegral);
   fChain->SetBranchAddress("Cluster_ChargeIntegralAveragePerHit", Cluster_ChargeIntegralAveragePerHit, &b_Cluster_ChargeIntegralAveragePerHit);
   fChain->SetBranchAddress("Cluster_StartChannel", Cluster_StartChannel, &b_Cluster_StartChannel);
   fChain->SetBranchAddress("Cluster_StartTick", Cluster_StartTick, &b_Cluster_StartTick);
   fChain->SetBranchAddress("Cluster_EndChannel", Cluster_EndChannel, &b_Cluster_EndChannel);
   fChain->SetBranchAddress("cluster_EndTick", cluster_EndTick, &b_cluster_EndTick);
   fChain->SetBranchAddress("Cluster_StartCharge", Cluster_StartCharge, &b_Cluster_StartCharge);
   fChain->SetBranchAddress("Cluster_StartAngle", Cluster_StartAngle, &b_Cluster_StartAngle);
   fChain->SetBranchAddress("Cluster_EndCharge", Cluster_EndCharge, &b_Cluster_EndCharge);
   fChain->SetBranchAddress("Cluster_EndAngle", Cluster_EndAngle, &b_Cluster_EndAngle);
   fChain->SetBranchAddress("NumberOfTracks_pmtrack", &NumberOfTracks_pmtrack, &b_NumberOfTracks_pmtrack);
   fChain->SetBranchAddress("TrackID_pmtrack", TrackID_pmtrack, &b_TrackID_pmtrack);
   fChain->SetBranchAddress("Track_PitchInViews_pmtrack", Track_PitchInViews_pmtrack, &b_Track_PitchInViews_pmtrack);
   fChain->SetBranchAddress("Track_NumberOfHitsPerView_pmtrack", Track_NumberOfHitsPerView_pmtrack, &b_Track_NumberOfHitsPerView_pmtrack);
   fChain->SetBranchAddress("Track_dEdx_pmtrack", Track_dEdx_pmtrack, &b_Track_dEdx_pmtrack);
   fChain->SetBranchAddress("Track_dQdx_pmtrack", Track_dQdx_pmtrack, &b_Track_dQdx_pmtrack);
   fChain->SetBranchAddress("Track_TPC_pmtrack", Track_TPC_pmtrack, &b_Track_TPC_pmtrack);
   fChain->SetBranchAddress("Track_HitX_pmtrack", Track_HitX_pmtrack, &b_Track_HitX_pmtrack);
   fChain->SetBranchAddress("Track_HitY_pmtrack", Track_HitY_pmtrack, &b_Track_HitY_pmtrack);
   fChain->SetBranchAddress("Track_HitZ_pmtrack", Track_HitZ_pmtrack, &b_Track_HitZ_pmtrack);
   fChain->SetBranchAddress("Track_StartX_pmtrack", Track_StartX_pmtrack, &b_Track_StartX_pmtrack);
   fChain->SetBranchAddress("Track_StartY_pmtrack", Track_StartY_pmtrack, &b_Track_StartY_pmtrack);
   fChain->SetBranchAddress("Track_StartZ_pmtrack", Track_StartZ_pmtrack, &b_Track_StartZ_pmtrack);
   fChain->SetBranchAddress("Track_StartDistanceToBoundary_pmtrack", Track_StartDistanceToBoundary_pmtrack, &b_Track_StartDistanceToBoundary_pmtrack);
   fChain->SetBranchAddress("Track_EndX_pmtrack", Track_EndX_pmtrack, &b_Track_EndX_pmtrack);
   fChain->SetBranchAddress("Track_EndY_pmtrack", Track_EndY_pmtrack, &b_Track_EndY_pmtrack);
   fChain->SetBranchAddress("Track_EndZ_pmtrack", Track_EndZ_pmtrack, &b_Track_EndZ_pmtrack);
   fChain->SetBranchAddress("Track_EndDistanceToBoundary_pmtrack", Track_EndDistanceToBoundary_pmtrack, &b_Track_EndDistanceToBoundary_pmtrack);
   fChain->SetBranchAddress("Track_Theta_pmtrack", Track_Theta_pmtrack, &b_Track_Theta_pmtrack);
   fChain->SetBranchAddress("Track_Phi_pmtrack", Track_Phi_pmtrack, &b_Track_Phi_pmtrack);
   fChain->SetBranchAddress("Track_Length_pmtrack", Track_Length_pmtrack, &b_Track_Length_pmtrack);
}

Bool_t RunSel::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RunSel::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void RunSel::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t RunSel::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either RunSel::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.


   return kTRUE;
}

void RunSel::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void RunSel::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}


#endif
