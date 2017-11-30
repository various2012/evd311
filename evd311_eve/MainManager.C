#include <TEveManager.h>
#include <TEveBrowser.h>
#include "EvdUtils.C"
#include <RQ_OBJECT.h>
//#include ".C"
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>
#include <TRegexp.h>
#include <TGFileBrowser.h>
#include <TGListTree.h>
#include "EventManager.C"
#include <TGLViewer.h>
#include <TGLCamera.h>
#include <TGButtonGroup.h>
#include <TGButton.h>
#include <TGNumberEntry.h>
#include <TGLabel.h>
#include <TGTab.h>
#include <TGDimension.h>
//class TGlabel;

#ifdef __MAKECINT__
#pragma link C++ class EventManager+;
#endif

enum eControlButtons{
	kPrevEvent,
	kEntryField,
	kNextEvent

};

class MainManager : public TEveManager{
RQ_OBJECT("MainManager")
private:
	TEveBox * fLArBox;
	TEveBox * fCRPBox;
	TEveStraightLineSet * fAxis;
	TGLAnnotation * fEventCount;
	//RunSel * fSel;
	TTree * fCurTree;
	TGFileBrowser * fFileBrowser;
	EventManager * fEventManager;
	TGNumberEntryField * fEntryField;
	TGLabel * fNumEvtLabel;
	void MakeEvtGui();
;
	//void HandleButtonsEvt();
	//TEveManager * fEveMan;
public:
	MainManager(UInt_t w, UInt_t h);
	~MainManager();
	void ReloadTree(TGListTreeItem * item, Int_t btn);
	void SetEntryValue() {fEntryField->SetIntNumber(fEventManager->GetCurrentEvent());fEventCount->SetText(TString::Format("Event %li",fEntryField->GetIntNumber()));};
	void EntryPressed() {fEventManager->GotoEvent(fEntryField->GetIntNumber());};
	

	//void LoadFile();

	ClassDef(MainManager,0);
};

MainManager::MainManager(UInt_t w, UInt_t h):TEveManager(w,h,kTRUE,"FIV"),
//MainManager::MainManager(UInt_t w, UInt_t h):(&(TEveManager::Create())),
fLArBox(0),
fCRPBox(0),
//fSel(0),
fCurTree(0),
fFileBrowser(0),
fAxis(0),
fEventCount(0),
fEventManager(0),
fEntryField(0),
fNumEvtLabel(0)
{
	//TEveManager::Create();
	//gStyle->SetMarkerStyle(7);
	fLArBox = EvdUtils::FidBox("Fiducial Volume");
	fCRPBox = EvdUtils::CRPPlane("CRP plane");
	fAxis = EvdUtils::MakeAxis("Axis",15,7,7);
	fEventCount=EvdUtils::EventCount(GetDefaultGLViewer());
	fCurTree=new TTree();
	fFileBrowser=fBrowser->fFileBrowser;
	fFileBrowser->fListTree->Connect("DoubleClicked(TGListTreeItem * , Int_t )","MainManager",this,"ReloadTree(TGListTreeItem * , Int_t )");
	fEventManager = new EventManager("Event_is_not_loaded");
	AddEvent(fEventManager);
	SetCurrentEvent(fEventManager);
	AddGlobalElement(fLArBox);
	AddGlobalElement(fCRPBox);
	AddGlobalElement(fAxis);
	//AddGlobalElement(fEveCount);
	GetDefaultGLViewer()->CurrentCamera().SetCenterVec(150,0,0);
	MakeEvtGui();
	FullRedraw3D();
	//GetMainWindow()->MapWindow();

	
}

MainManager::~MainManager(){
	//Cleanup();
	//CloseEveWindow();
}

void MainManager::ReloadTree(TGListTreeItem * item, Int_t btn){
	if(!gFile) return;	
	TRegexp re("^.+\\.root$");
	Int_t len;
	if(re.Index(gFile->GetName(),&len)<0){
		//printf("File %s does not match",gFile->GetName());
		 return;
	}
	//printf ("Len=%i\n",len);
	if(fCurTree->GetCurrentFile()==gFile) return;
	TTree *fTmpTree=(TTree*) gFile->Get("analysistree/anatree");
	if(fTmpTree==0) return;
	fCurTree=fTmpTree;
	fEventManager->SetCurrentTree(fCurTree);
	//fEventManager->GotoEvent(0);	
	Int_t nEntries=fCurTree->GetEntries();
	fEntryField->SetText("0",kTRUE);
	fEntryField->SetLimits(TGNumberFormat::kNELLimitMinMax,0,nEntries-1);


	fNumEvtLabel->SetText(TString::Format("/%i",nEntries-1));
	fNumEvtLabel->Resize(fNumEvtLabel->GetDefaultSize());
	EntryPressed();
	FullRedraw3D();
	//printf("Tree loaded from file %s\n",gFile->GetName());
}

void MainManager::MakeEvtGui(){
	//fBrowser->StartEmbedding(TRootBrowser::kLeft);
	TGTab * ctab = fBrowser->GetTab(TRootBrowser::kLeft);
	TGCompositeFrame * cont=ctab->AddTab("Event Control");
	cont->SetLayoutManager(new TGVerticalLayout(cont));
	TGDimension btnsize(20,20);
	//cont->Layout();
	//TGMainFrame * evtMain= new TGMainFrame(gClient->GetRoot(),400,400);
	//evtMain->SetWindowName("Evt Gui");
	//evtMain->SetCleanup(kDeepCleanup);
	
	//TGButtonGroup * btnGroup = new TGButtonGroup(evtMain,"Controls");
	
	TGHorizontalFrame * fFrame = new TGHorizontalFrame(cont,400,400);
	fFrame->SetName("fFrame");

	TGPictureButton * bPrev = new TGPictureButton(fFrame, gClient->GetPicture("arrow_left.xpm"),kPrevEvent);
	bPrev->Connect("Clicked()", "EventManager", fEventManager,"PrevEvent()");
	bPrev->Connect("Clicked()", "MainManager", this,"SetEntryValue()");
	fFrame->AddFrame(bPrev, new  TGLayoutHints(kLHintsNormal|kLHintsCenterY));

	bPrev->Resize(btnsize);

	TGLabel * fEventLabel = new TGLabel(fFrame,"Event: ");
	fFrame->AddFrame(fEventLabel, new TGLayoutHints(kLHintsNormal|kLHintsCenterY,2,2,2,2));

	fEntryField = new TGNumberEntryField(fFrame, kEntryField,0,
		TGNumberFormat::kNESInteger,
		TGNumberFormat::kNEANonNegative,
		TGNumberFormat::kNELLimitMinMax,0,1);
	fEntryField->SetWidth(45);
	fEntryField->Connect("ReturnPressed()","MainManager",this,"EntryPressed()");
	fEntryField->Connect("ReturnPressed()", "MainManager", this,"SetEntryValue()");
//fEntryField->Connect("Clicked()", "MainManager", this,"SetEntryValue()");
	fFrame->AddFrame(fEntryField, new TGLayoutHints(kLHintsNormal|kLHintsExpandX,2,2,2,2));

	fNumEvtLabel =new TGLabel(fFrame,"/0    ");
	fFrame->AddFrame(fNumEvtLabel, new TGLayoutHints(kLHintsNormal|kLHintsCenterY,2,2,2,2));

	TGPictureButton * bNext = new TGPictureButton(fFrame, gClient->GetPicture("arrow_right.xpm"),kNextEvent);
	bNext->Resize(btnsize);
	fFrame->AddFrame(bNext, new  TGLayoutHints(kLHintsNormal|kLHintsCenterY));
	fFrame->MapSubwindows();
	bNext->Connect("Clicked()", "EventManager", fEventManager,"NextEvent()");
	bNext->Connect("Clicked()", "MainManager", this,"SetEntryValue()");
//	
	cont->AddFrame(fFrame, new TGLayoutHints(kLHintsNormal|kLHintsExpandX,2,2,2,2));
	//cont->MapSubwindows();
	//cont->Resize();
	//cont->Layout();
	ctab->MapSubwindows();
	ctab->Layout();
//	evtMain->MapSubwindows();
//	evtMain->Resize();
//	evtMain->MapWindow();
	//gEve->GetMainWindow()->MapSubwindows();
	//Browser->StopEmbedding();
	//fBrowser->SetTabTitle("Event Control",0);
	
	
}

//void MainManager::SetEntryValue(){
//	fEntryField->SetIntNumber(fEventManager->GetCurrentEvent());
//}

