//#include <TEveManager.h>
//#include "EvdUtils.C"
#include "Selector.C"
#include <RQ_OBJECT.h>
#include <TEveEventManager.h>
#include <TTree.h>
#include <TEvePointSet.h>

#ifdef __MAKECINT__
#pragma link C++ class Selector+;
#endif

class EventManager : public TEveEventManager{ //Implements TEveEventManager
RQ_OBJECT("EventManager")
private:
	TTree * fCurTree;
	Selector * fSelector;
	TEvePointSetArray * fHits; //Array of Sets of Points
	Int_t fCurEvent;
	Int_t ** fHitsParams;
	Int_t fNhits;
	Int_t fNentries;
	
public:
	EventManager(const char *n="TEveEventManager", const char *t="");
	~EventManager() {};
    Bool_t SetCurrentTree(TTree * tree); //Set pointer of tree to current tree and initialize selector
    void Open(); //Open current event
    void GotoEvent(Int_t event);
    void NextEvent();
    void PrevEvent();
    void Close();//Not implemented
    Int_t GetCurrentEvent(){ return fCurEvent;}
 
	ClassDef(EventManager,0);
};

EventManager::EventManager(const char *n,const char *t):TEveEventManager(n,t),
fCurTree(0),
fSelector(0),
fHits(0),fCurEvent(0),
fHitsParams(0),
fNhits(0),
fNentries(0){
	fCurTree=new TTree();
	fSelector = new Selector(fCurTree);
	fHits = new TEvePointSetArray("No Hits","");
	AddElement(fHits);
	
};

Bool_t EventManager::SetCurrentTree(TTree * tree){ 
	if(tree==0) return kFALSE;
	fCurTree=tree;
	fSelector->Init(tree);
	fNentries=tree->GetEntries();
	fSelector->GetEntry(0);
	SetName(TString::Format("Run %i Subrun %i",fSelector->Run,fSelector->Subrun));
	fCurEvent=0;

	return kTRUE;
}

void EventManager::Open() {
	fCurTree->GetEntry(fCurEvent);
	Int_t ntracks = fSelector->NumberOfTracks_pmtrack;
	if(fHits){ delete fHits; fHits=0;}//Delete existing hits
	if(ntracks<1) return;
	fHits=new TEvePointSetArray(TString::Format("Event  #%i",fCurEvent),"");//new array of set of points
	//printf("Event number %i, %i tracks\n",fCurEvent,ntracks);
	//Initialize bins of pointsetarray corresponding to number of tracks
	fHits->InitBins("Track Id", ntracks,0,ntracks);
	if(ntracks==0) return;
	//Define margins of hits according to Track_NumberOfHitsPerView_pmtrack
	Int_t * hitMargins = new Int_t[2*ntracks+1];
	hitMargins[0]=0;
	//Short_t ** ntpv = (Short_t **)fSelector->Track_NumberOfHitsPerView_pmtrack;
	for(Int_t i=0;i<ntracks;i++){

		hitMargins[2*i+1]=hitMargins[2*i]+fSelector->Track_NumberOfHitsPerView_pmtrack[i][0];
		hitMargins[2*i+2]=hitMargins[2*i+1]+fSelector->Track_NumberOfHitsPerView_pmtrack[i][1];
		//printf("Track number %i/%i margins %i,%i value %i, %i\n",i,ntracks-1,hitMargins[2*i+1],hitMargins[2*i+2], fSelector->Track_NumberOfHitsPerView_pmtrack[i][0],fSelector->Track_NumberOfHitsPerView_pmtrack[i][1]);
	}
	if(fHitsParams){
		for(Int_t i=0;i<fNhits;++i) delete fHitsParams[i];
		delete fHitsParams;
	}
	fNhits = hitMargins[2*ntracks];
	if (fNhits==0) return;
	fHitsParams = new Int_t*[fNhits];//Array of parameters for each point in set of points
	//printf("fNhits %i\n",fNhits);
	//hitMargins[0]=ntpv[0][0]+ntpv[0][1];
	//Fill TEvePointSetArray with points
	for(Int_t i=0;i<2*ntracks;i++){
		//hitMargins[i+1]=hitMargins[i]+ntpv[i][0]+fSelector->ntpv[i][1];
		TEvePointSet * fCurPS = fHits->GetBin(i/2+1); //Get TEvePointSet, Bin 0 is underflow bin
		//Change parameters of TEvePointSet - color, style of markers
		if(i%2==0) fCurPS->SetName(TString::Format("Track %i", i/2));
		fCurPS->SetMarkerColor(i/2+2);
		fCurPS->SetMarkerStyle(7);
		//Fill TEvePointSet and set parameters for each points - track id, number of hit, number of view, relative number of hit
		for(Int_t j=hitMargins[i];j<hitMargins[i+1];++j){
			
			//printf("j=%i/%i\n",j,fNhits);
			fHitsParams[j] = new Int_t[4];
			fHitsParams[j][0] = i/2;
			fHitsParams[j][1] = j;
			fHitsParams[j][2] = i%2;
			fHitsParams[j][3] = j-hitMargins[i];
			fCurPS->SetNextPoint(fSelector->Track_HitZ_pmtrack[j],fSelector->Track_HitX_pmtrack[j],fSelector->Track_HitY_pmtrack[j]);
			fCurPS->SetPointIntIds(fHitsParams[j]);
		}


	}
	fHits->CloseBins();
	AddElement(fHits);
	if(!gEve) TEveManager::Create();
	//Add this event manager to current eve display
	if(gEve->GetCurrentEvent()==0){
		 gEve->AddEvent(this);
		 gEve->SetCurrentEvent(this);
	}
	delete hitMargins;
	gEve->Redraw3D();
};
void EventManager::GotoEvent(Int_t event) {
	if((event>=0)&&(event<fNentries)) fCurEvent=event;
	fSelector->GetEntry(fCurEvent);
	Open();

};
void EventManager::NextEvent() {
	if(fCurEvent<fNentries-1) ++fCurEvent;
	fSelector->GetEntry(fCurEvent);
	Open();
};
void EventManager::PrevEvent() {
	if(fCurEvent>0) --fCurEvent;
	fSelector->GetEntry(fCurEvent);
	Open();
};
void EventManager::Close() {
	
};
