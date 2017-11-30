#ifndef MainFrame_h
#define MainFrame_h

#include "RunSel.C"
#include "EvdUtils.C"

#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TGClient.h>
#include <TGLabel.h>
#include <TVirtualX.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <RQ_OBJECT.h>
#include <TGMenu.h>
#include <TGFileDialog.h>
#include <TGListTree.h>
#include <TRootEmbeddedCanvas.h>
#include <TGCanvas.h>
#include <list>
#include <TString.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGNumberEntry.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGDimension.h>
//#include <TGLSAViewer.h>
#include <TGLEmbeddedViewer.h>
//#include <TGLWidget.h>
//#include <TGraph2D.h>
#include <TEveManager.h>
#include <TEveBox.h>
#include <TEvePointSet.h>
//#include <TEvePointSetArray.h>
#include <TEveElement.h>
#include <TStyle.h>
#include <TEveViewer.h>
#include <TMultiGraph.h>




class MainFrame : public TGMainFrame{ //GUI mainframe class
RQ_OBJECT("MainFrame")

private:
	TGHorizontalFrame * tframe;
	RunSel * selc;
	TChain * fChain;
	TGListTree * fListTree;
	TRootEmbeddedCanvas * fECanvas;
	TTree * fCurTree;
	//TH2F * fHx,fHy,fHz;
	TGCanvas * fCanv1;
	//TGListTreeItem ** RunItems;

	TGLabel * fLabelEvt;
	TGNumberEntryField * fEntry;
	TGPictureButton * bStart;
	TGPictureButton * bEnd;
	TGPictureButton * bLeft;
	TGPictureButton * bRight;
	TGLabel * fLabelEvtl;
	TGCheckButton * bColorTracks;
	TGHorizontalFrame * fControlFrame;

	TGPopupMenu * viewpopup;
	TGPopupMenu * hitdrawpopup;
	TGPopupMenu * chdrawpopup;
	Int_t ncurent;

	TGTransientFrame * draw3DFrame;
	TGLEmbeddedViewer * glviewer;
	TEveManager * eveMan;
	TEvePointSetArray * tracks3D;





	
public:
	MainFrame(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~MainFrame();
	void DoExit();
	Int_t HandleButtons(Int_t id); //Slot

	Int_t LoadSelectedSubRun(TGListTreeItem * item,Int_t btn);
	Int_t LoadEvent(Int_t event);
	Int_t DrawHits(TTree * tree, Int_t eveid);
	Int_t OpenFileDialog();
	void ComposeListTree();
	Int_t ExcludeButtons(TGPopupMenu * parent,Int_t id, const Int_t * ids, Int_t nbts);
	Int_t TogglePopupEntry(TGPopupMenu * parent,Int_t id);
	Int_t ShowFirstEvent();//Slot
	Int_t ShowLastEvent();//Slot
	Int_t ShowEvent();//Slot
	Int_t MoveLeftEvent();//Slot
	Int_t MoveRightEvent();//Slot

	Int_t Show3DFrame();//Slot

	Int_t Hide3DFrame();//Slot

	ClassDef(MainFrame,0)

};
#endif

#ifdef __MAKECINT__ 
#pragma link C++ class MainFrame+;
#endif

#ifndef MainFrame_cxx
#define MainFrame_cxx


enum kButtonsID{

	kFileOpen,
	kFilePrint,
	kFileExit,

	kPlaneZY,
	kPlaneZX,
	kPlaneYX,


	kView0,
	kView1,
	kView01,


	kDrawTracks,
	kDrawDQDX,
	kDraw3D,

	kDrawHits,
	kDrawChannels,

	kDrawAssigned,
	kDrawNotAssigned,
	kDrawAll,
	kColorAssigned,
	kColorCharge,
	
	
	
	kMoveStart,
	kMoveLeft,
	kMoveRight,
	kNumEntry,
	kMoveEnd
};





MainFrame::MainFrame(const TGWindow *p, UInt_t w, UInt_t h) :
 TGMainFrame(p,w,h),fChain(0),selc(0),ncurent(0),fCurTree(0)
{
	gStyle->SetCanvasPreferGL(kTRUE);
	gStyle->SetOptStat(0);
	fChain=new TChain("analysistree/anatree");
	TGLayoutHints * mfr = new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 2,2,2,2);
	TGLayoutHints * stdlay = new TGLayoutHints(kLHintsNormal, 2,2,2,2);
	//tframe=new TGHorizontalFrame(this, w,h);
	//AddFrame(tframe, mfr);
	Connect("CloseWindow()","MainFrame",this,"DoExit()");
	TGPopupMenu * filepopup = new TGPopupMenu(gClient->GetRoot(),30,20);
	filepopup->AddEntry("Open",kFileOpen);
	filepopup->AddEntry("Print",kFilePrint);
	filepopup->AddSeparator();
	filepopup->AddEntry("Exit",kFileExit);

	viewpopup = new TGPopupMenu(gClient->GetRoot(),30,20);
	hitdrawpopup = new TGPopupMenu(gClient->GetRoot(),30,20);
	hitdrawpopup->AddEntry("Show Plane ZY",kPlaneZY);
	hitdrawpopup->AddEntry("Show Plane ZX",kPlaneZX);
	hitdrawpopup->AddEntry("Show Plane YX",kPlaneYX);
	hitdrawpopup->CheckEntry(kPlaneZY);
	hitdrawpopup->CheckEntry(kPlaneZX);
	hitdrawpopup->AddSeparator();
	hitdrawpopup->AddEntry("Show view 0",kView0);
	hitdrawpopup->AddEntry("Show view 1",kView1);
	hitdrawpopup->AddEntry("Show view 0 + 1",kView01);
	hitdrawpopup->CheckEntry(kView01);
	hitdrawpopup->AddSeparator();
	hitdrawpopup->AddEntry("Show tracks",kDrawTracks);
	hitdrawpopup->CheckEntry(kDrawTracks);
	hitdrawpopup->AddEntry("Show 3D", kDraw3D);
	hitdrawpopup->Connect("Activated(Int_t)","MainFrame",this,"HandleButtons(Int_t)");

	chdrawpopup = new TGPopupMenu(gClient->GetRoot(),30,20);
	chdrawpopup->AddEntry("Show hits assigned to tracks", kDrawAssigned);
	chdrawpopup->AddEntry("Show hits not assigned to tracks",kDrawNotAssigned);
	chdrawpopup->AddEntry("Show all hits",kDrawAll);
	chdrawpopup->CheckEntry(kDrawAll);
	chdrawpopup->AddSeparator();
	chdrawpopup->AddEntry("Show Hits by Track",kColorAssigned);
	chdrawpopup->CheckEntry(kColorAssigned);
	
	viewpopup->AddEntry("Draw Hits", kDrawHits);
	viewpopup->AddEntry("Draw Channels", kDrawChannels);
	viewpopup->CheckEntry(kDrawHits);
	viewpopup->AddSeparator();
	viewpopup->AddPopup("Track Options",hitdrawpopup);
	viewpopup->AddPopup("Channel Options", chdrawpopup);
	
	viewpopup->Connect("Activated(Int_t)","MainFrame",this,"HandleButtons(Int_t)");

	TGDimension * btnsize=new TGDimension(20,20);

	TGMenuBar * menubar=new TGMenuBar(this,w,20);
	menubar->AddPopup("&File",filepopup,new TGLayoutHints(kLHintsNormal,0,0,0,0));
	menubar->AddPopup("&View",viewpopup,new TGLayoutHints(kLHintsNormal,0,0,0,0));

	filepopup->Connect("Activated(Int_t)","MainFrame",this,"HandleButtons(Int_t)");
	AddFrame(menubar,new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,0,0));
	TGHorizontalFrame * fr1 = new TGHorizontalFrame(this,w,h-20);

	TGVerticalFrame * fr11 = new TGVerticalFrame(fr1,200,400);

	fCanv1=new TGCanvas(fr11,200,300);

	fListTree = new TGListTree(fCanv1,kHorizontalFrame);

	fr11->AddFrame(fCanv1,new TGLayoutHints(kLHintsTop|kLHintsLeft|kLHintsExpandY,2,2,2,2));
	fListTree->Connect("DoubleClicked(TGListTreeItem*,Int_t)","MainFrame",this,"LoadSelectedSubRun(TGListTreeItem*,Int_t)");
	fControlFrame = new TGHorizontalFrame(fr11,120,80);
	bStart=new TGPictureButton(fControlFrame,gClient->GetPicture("first_t.xpm"),kMoveStart);
	bStart->SetSize(*btnsize);
	bLeft=new TGPictureButton(fControlFrame,gClient->GetPicture("arrow_left.xpm"),kMoveLeft);
	bLeft->SetSize(*btnsize);
	fLabelEvtl = new TGLabel(fControlFrame,"Event:");
	fEntry=new TGNumberEntryField(fControlFrame,kNumEntry,0,TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative,TGNumberFormat::kNELLimitMinMax,0,1);
	fEntry->SetWidth(45);
	fLabelEvt=new TGLabel(fControlFrame,"/0   ");
	fLabelEvt->SetSize(*btnsize);
	bRight=new TGPictureButton(fControlFrame,gClient->GetPicture("arrow_right.xpm"),kMoveRight);
	bRight->SetSize(*btnsize);
	bEnd=new TGPictureButton(fControlFrame,gClient->GetPicture("last_t.xpm"),kMoveEnd);
	bEnd->SetSize(*btnsize);

	fControlFrame->AddFrame(bStart, stdlay);
	fControlFrame->AddFrame(bLeft, stdlay);
	fControlFrame->AddFrame(fLabelEvtl, new TGLayoutHints(kLHintsNormal|kLHintsCenterY,2,2,2,2));
	fControlFrame->AddFrame(fEntry, new TGLayoutHints(kLHintsNormal|kLHintsExpandX,2,2,2,2));
	fControlFrame->AddFrame(fLabelEvt, new TGLayoutHints(kLHintsNormal|kLHintsCenterY,2,2,2,2));
	fControlFrame->AddFrame(bRight, stdlay);
	fControlFrame->AddFrame(bEnd, stdlay);
	fr11->AddFrame(fControlFrame,stdlay);
	
	//bColorTracks = new TGCheckButton(fr11, "Show Tracks", kDrawTracks);
	//fr11->AddFrame(bColorTracks,stdlay);
	bStart->Connect("Clicked()","MainFrame",this,"ShowFirstEvent()");
	bLeft->Connect("Clicked()","MainFrame",this,"MoveLeftEvent()");
	fEntry->Connect("ReturnPressed()","MainFrame",this,"ShowEvent()");
	bRight->Connect("Clicked()","MainFrame",this,"MoveRightEvent()");
	bEnd->Connect("Clicked()","MainFrame",this,"ShowLastEvent()");
	//bColorTracks->Connect("Clicked()","MainFrame",this,"ShowEvent()");

	fECanvas = new TRootEmbeddedCanvas("Canvas",fr1,400,400);
	fr1->AddFrame(fr11,new TGLayoutHints(kLHintsTop|kLHintsLeft,2,2,2,2));
	fr1->AddFrame(fECanvas,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,2,2,2,2));
	AddFrame(fr1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,5,5,5,5));
	eveMan = TEveManager::Create(kFALSE);

	draw3DFrame = new TGTransientFrame(gClient->GetRoot(),this, 500,500);
	draw3DFrame->DontCallClose();
	draw3DFrame->Connect("CloseWindow()","MainFrame",this,"Hide3DFrame()");

	glviewer = new TGLEmbeddedViewer(draw3DFrame);
	TEveViewer * nv = new TEveViewer("embview");
	nv->SetGLViewer(glviewer, glviewer->GetFrame());
        nv->IncDenyDestroy();
  	nv->AddScene(gEve->GetEventScene());
   	gEve->GetViewers()->AddElement(nv);
	draw3DFrame->AddFrame(glviewer->GetFrame(), new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,2,2,2,2));
	draw3DFrame->Layout();
	draw3DFrame->MapSubwindows();
	draw3DFrame->SetWindowName("311evd 3D display");

	tracks3D=new TEvePointSetArray("tracks3D");
	
	eveMan->AddElement(EvdUtils::FidBox("Fid. Volume"));
	eveMan->AddElement(EvdUtils::CRPPlane("CRP Plane"));
	eveMan->AddElement(tracks3D);
	eveMan->Redraw3D(kTRUE);


	SetWindowName("311evd");
	MapSubwindows();
	Layout();
	//if (w<640) w=640;
	//if (h<480) h=480;
	//Resize(w,h);
	MapWindow();
	
}

MainFrame::~MainFrame()
{
	Cleanup();
}

Int_t MainFrame::HandleButtons(Int_t id)
{
	if(id==kFileExit){
			DoExit();
			return id;
		}
	if(id==kFileOpen){
			Int_t res=OpenFileDialog();
			if (res==0){
				return -1;
				//std::cout<<"No Run files found\n";
			} else {
				
			}
			ComposeListTree();
			return id;
		}
	if((id==kDrawHits)||(id==kDrawChannels)){
		Int_t ids[]={kDrawHits,kDrawChannels};
		ExcludeButtons(viewpopup,id,ids,2);
		ShowEvent();
		return id;
	}
	if((id==kPlaneZY)||(id==kPlaneZX)||(id==kPlaneYX)||(id==kDrawTracks)||(id==kDraw3D)){
		TogglePopupEntry(hitdrawpopup,id);
		ShowEvent();
		return id;
	}
	if((id==kView0)||(id==kView1)||(id==kView01)){	
		Int_t ids[]={kView0,kView1,kView01};
		ExcludeButtons(hitdrawpopup,id,ids,3);
		ShowEvent();
		return id;
	}
	if((id==kDrawAssigned)||(id==kDrawNotAssigned)||(id==kDrawAll)){
		Int_t ids[]={kDrawAssigned,kDrawNotAssigned,kDrawAll};
		ExcludeButtons(chdrawpopup,id,ids,3);
		ShowEvent();
		return id;
	}
	if(id==kColorAssigned){
		TogglePopupEntry(chdrawpopup,id);
		ShowEvent();
		return id;
	}
	return -1;
}
void MainFrame::DoExit()
{
	gApplication->Terminate(0);
}
Int_t MainFrame::OpenFileDialog()
{
	TGFileInfo  * fileinfo=new TGFileInfo();
	const char *filetypes[]={"Root files", "*.root",0,0};
	fileinfo->fFileTypes= filetypes;
	fileinfo->fIniDir=StrDup(".");
	fileinfo->SetMultipleSelection(kTRUE);
	new TGFileDialog(gClient->GetRoot(),this,kFDOpen,fileinfo);
	Int_t res=0;
	if (fileinfo->fFileNamesList!=0){
		if(fChain!=0) delete fChain;
		fChain=new TChain("analysistree/anatree");
		if (selc!=0) delete selc;
		selc=new RunSel(fChain);
		//fileinfo->fFileNamesList->ls();
		res=fChain->AddFileInfoList(fileinfo->fFileNamesList);
		selc->Init(fChain);
	} else if (fileinfo->fFilename!=0){
			//cout<<fileinfo->fFilename<<endl;
			if(fChain!=0) delete fChain;
			fChain=new TChain("analysistree/anatree");
			if (selc!=0) delete selc;
			selc=new RunSel(fChain);
			Int_t res=fChain->Add(fileinfo->fFilename);
			selc->Init(fChain);
		} else {
			res=0;
		}
	//res=fChain->GetNtrees();
	//cout<<res<<endl;
	return res;
}

void MainFrame::ComposeListTree(){
	//Int_t nfiles=selc->GetNTrees();
	Int_t nfiles=fChain->Draw("Run","","goff");
	std::list<Double_t> runs(fChain->GetV1(),fChain->GetV1()+nfiles);
	runs.sort();
	runs.unique();
	TGListTreeItem * item=0;
	while((item=fListTree->GetFirstItem())) fListTree->DeleteItem(item);
	for(std::list<Double_t>::iterator it=runs.begin();it!=runs.end();++it){
		TGListTreeItem * runitem=fListTree->AddItem(0,TString::Format("Run %i",(Int_t)*it));
		Int_t nsubruns=fChain->Draw("Subrun",TString::Format("Run==%i",(Int_t)*it),"goff");
		std::list<Double_t> subruns(fChain->GetV1(),fChain->GetV1() + nsubruns);
		subruns.sort();
		subruns.unique();
		for(std::list<Double_t>::iterator jt=subruns.begin();jt!=subruns.end();++jt){
			TGListTreeItem * subrunitem=fListTree->AddItem(runitem,TString::Format("Subrun %i",(Int_t)*jt));

		}
	}
	//MapSubwindows();
		
}

Int_t MainFrame::LoadSelectedSubRun(TGListTreeItem * item, Int_t btn){
	TGListTreeItem * paritem;
	if(!(paritem=item->GetParent())) return -1;
	Int_t subrun=-1;
	if(sscanf(item->GetText(),"Subrun %i",&subrun)==0) return -1;
	Int_t run=-1;
	if(sscanf(paritem->GetText(),"Run %i",&run)==0) return -1;
	//printf("Selected Run %i, Subrun %i\n",run,subrun);
	//Int_t nentries=fChain->GetEntries(TString::Format("(Run==%i)&&(Subrun==%i)",run,subrun));
	Int_t nentries=fChain->Draw("Entry$",TString::Format("(Run==%i)&&(Subrun==%i)",run,subrun),"goff");
	if(nentries<1) return -1;
	fLabelEvt->SetText(TString::Format("/%i",nentries-1));
	ncurent=nentries;
	//ncurent=0;
	fLabelEvt->Resize(fLabelEvt->GetDefaultSize());
	fEntry->SetText("0",kTRUE);
	fEntry->SetLimits(TGNumberFormat::kNELLimitMinMax,0,nentries-1);
	fChain->LoadTree(fChain->GetV1()[0]);
	fCurTree=fChain->GetTree();
	fControlFrame->MapSubwindows();
	fControlFrame->MapWindow();
	//printf("Current tree %p",(void *)fCurTree);
	LoadEvent(0);
	return nentries;
}

Int_t MainFrame::LoadEvent(Int_t event){
	if(fCurTree==0) return -1;
	Int_t res=DrawHits(fCurTree, event);
		return res;
}

Int_t MainFrame::ShowFirstEvent(){
	fEntry->SetText("0",kTRUE);
	Int_t res=LoadEvent(0);
	return res;
}

Int_t MainFrame::ShowLastEvent(){
	
	fEntry->SetText(TString::Format("%i",ncurent-1));
	return LoadEvent(ncurent-1);
}
Int_t MainFrame::MoveLeftEvent(){
	Int_t curent=fEntry->GetIntNumber();
	if (curent==0) return -1;
	fEntry->SetText(TString::Format("%i",curent-1));
	return LoadEvent(curent-1);
}
Int_t MainFrame::MoveRightEvent(){
	Int_t curent=fEntry->GetIntNumber();
	if (curent==ncurent-1) return -1;
	fEntry->SetText(TString::Format("%i",curent+1));
	return LoadEvent(curent+1);
}

Int_t MainFrame::ShowEvent(){
	Int_t curent=fEntry->GetIntNumber();
	return LoadEvent(curent);
}

Int_t MainFrame::DrawHits(TTree * tree, Int_t eveid){ //Function for drawing event in tree
	if (tree==0) return -1;
	if((eveid>=tree->GetEntries())||(eveid<0)) return -1;
	//RunSel * selc = new RunSel(tree);
	selc->Init(tree);
	tree->GetEntry(eveid);
	Int_t ntracks = selc->NumberOfTracks_pmtrack;

	//printf("Num of tracks: %i\n",ntracks);
	//Short_t (*viewnum)[2] = selc->Track_NumberOfHitsPerView_pmtrack;
	Int_t ** hitBounds = new Int_t*[ntracks];
	Int_t ncurpos=0;
	Bool_t isview0=hitdrawpopup->IsEntryChecked(kView0);
	Bool_t isview1=hitdrawpopup->IsEntryChecked(kView1);
	Bool_t isview01=hitdrawpopup->IsEntryChecked(kView01);
	for(Int_t i=0; i<ntracks; i++){
		Short_t * viewnum=selc->Track_NumberOfHitsPerView_pmtrack[i];
		hitBounds[i]=new Int_t[2];
		hitBounds[i][0]=ncurpos;
		if(isview1!=0) hitBounds[i][0]+=viewnum[0];
		ncurpos+=viewnum[0];
		hitBounds[i][1]=ncurpos-1;
		if(isview0==0) hitBounds[i][1]+=viewnum[1];
		ncurpos+=viewnum[1];
		//printf("Track %i bound: %i\n",i,hitBounds[i][0]);
		
	}
	TCanvas * canv=fECanvas->GetCanvas();
	canv->Clear();
	canv->SetGrid(kTRUE);
	if(viewpopup->IsEntryChecked(kDrawChannels)){
		canv->Divide(1,2);
		TPad ** pads = new TPad*[2];
		pads[0] = (TPad*)canv->GetPad(1);
		pads[1] = (TPad*)canv->GetPad(2);
		Int_t nchannels[]={320,960};
		Int_t nlength[]={3,1};
		//pads[1]->Divide(3,1);
		//pads[1]=(TPad*)pads[1]->GetPad(1);
		Int_t trID=-1;
		if(chdrawpopup->IsEntryChecked(kDrawAssigned)) trID=0;
		Int_t ntrackch=ntracks;
		if(chdrawpopup->IsEntryChecked(kDrawNotAssigned)) ntrackch=0;
		TMultiGraph **mgr = new TMultiGraph*[2];
		for(Int_t i=0;i<2;++i){
			pads[i]->cd();
			pads[i]->SetGrid();
			mgr[i]=new TMultiGraph();
			TGraph ** gr = new TGraph*[ntrackch-trID];
			for(Int_t j=0;j<ntrackch-trID;j++){
				gr[j]=new TGraph();
				if(chdrawpopup->IsEntryChecked(kColorAssigned)) gr[j]->SetMarkerColor(2+j+trID); else gr[j]->SetMarkerColor(1);
				gr[j]->SetMarkerStyle(7);
				gr[j]->SetName(TString::Format("View_%i_Hits_%i",i,j+trID));
			}
			for(Int_t k=0;k<selc->NumberOfHits;++k){
				Int_t nch=selc->Hit_Channel[k]-i*320;
				Int_t trackid =selc->Hit_TrackID[k];
				if((trackid>=trID)&&(trackid<ntrackch)) gr[trackid-trID]->SetPoint(k,nch,selc->Hit_PeakTime[k]);
			}
			//TString grname(TString::Format("View_%i_Hits_%i",i,j));
			for(Int_t j=0;j<ntrackch-trID;j++){
				if(gr[j]->GetN()!=0) mgr[i]->Add(gr[j]);
			}

			mgr[i]->SetTitle(TString::Format("View %i, %i channels over %i m",i,nchannels[i], nlength[i]));
			mgr[i]->Draw("AP");
			if(i==0) mgr[i]->GetXaxis()->SetLimits(0,320);
			if(i==1) mgr[i]->GetXaxis()->SetLimits(0,320*9);
			mgr[i]->GetXaxis()->SetTitle("Channels");
			mgr[i]->GetYaxis()->SetTitle("Time, ticks");
		}
		canv->Modified();
		canv->Update();
	}
	if(viewpopup->IsEntryChecked(kDrawHits)){
		Int_t ntotal=0;
		for(Int_t j=0;j<ntracks;j++){
			ntotal+=(hitBounds[j][1]-hitBounds[j][0]);
			//printf("Track %i\n",j);
		};
		Bool_t toDraw[]={hitdrawpopup->IsEntryChecked(kPlaneZY),hitdrawpopup->IsEntryChecked(kPlaneZX),hitdrawpopup->IsEntryChecked(kPlaneYX)};
		Int_t btnID[]={kPlaneZY,kPlaneZX,kPlaneYX};
		Int_t nplanes=0;
		for(Int_t i=0;i<3;i++) nplanes+=(Int_t)toDraw[i];
		//printf("nplanes: %i\n",nplanes);
		if (nplanes==0) return -1;
		canv->Divide(1,nplanes);
		TH2F * tHpl;
		while((tHpl=(TH2F*) gROOT->FindObject("tH0"))) delete tHpl;
		while((tHpl=(TH2F*) gROOT->FindObject("tH1"))) delete tHpl;
		while((tHpl=(TH2F*) gROOT->FindObject("tH2"))) delete tHpl;
		Int_t curplane=1;
		Int_t x1=0;
		Int_t y1=0;
		Int_t x2=0;
		Int_t y2=0;
		Float_t *xarr=0;
		Float_t *yarr=0;
		TString xtitle(6);
		TString ytitle(6);
		for(Int_t i=0;i<3;i++){
			canv->cd(curplane);
			if(toDraw[i]==0) continue;

			switch (i){
				case 0:{
	
					x1=0;
					x2=300;
					y1=-50;
					y2=50;
					xarr=selc->Track_HitZ_pmtrack;
					yarr=selc->Track_HitY_pmtrack;
					xtitle="Z, cm";
					ytitle="Y, cm";
					break;
				
				};
				case 1:{
					x1=0;
					x2=300;
					y1=-50;
					y2=50;
					xarr=selc->Track_HitZ_pmtrack;
					yarr=selc->Track_HitX_pmtrack;
					xtitle="Z, cm";
					ytitle="X, cm";
					break;
				};
				case 2:{
					x1=-50;
					x2=50;
					y1=-50;
					y2=50;
					xarr=selc->Track_HitY_pmtrack;
					yarr=selc->Track_HitX_pmtrack;
					xtitle="Y, cm";
					ytitle="X, cm";
					break;
				}
				default:{return -1;};
			};
			++curplane;
			tHpl = new TH2F(TString::Format("tH%i",i),TString::Format("Plane %c%c",xtitle[0],ytitle[0]),x2-x1,x1,x2,y2-y1,y1,y2);
			tHpl->GetXaxis()->SetTitle(xtitle.Data());
			tHpl->GetYaxis()->SetTitle(ytitle.Data());
			tHpl->Draw();
			for(Int_t j=0;j<ntracks;j++){
				Int_t npts=hitBounds[j][1]-hitBounds[j][0];
				//printf("npts=%i\n",npts);
				TGraph * graph = new TGraph(npts,&(xarr[hitBounds[j][0]]),&(yarr[hitBounds[j][0]]));
				graph->SetMarkerStyle(7);
				if(hitdrawpopup->IsEntryChecked(kDrawTracks)) graph->SetMarkerColor(j+2);
				if(graph->GetN()!=0) graph->Draw("P&same");
			};
			canv->Modified();
			canv->Update();
		}
	}
	if(hitdrawpopup->IsEntryChecked(kDraw3D)){
		//while(glviewer->CurrentLock()!=TGLLockable::kUnlocked) gSystem->Sleep(5);
		//gSystem->Sleep(1000);
		eveMan->DisableRedraw();
		tracks3D->InitBins("Number",ntracks+1,0,ntracks+1);
		Float_t * xarr=selc->Track_HitZ_pmtrack;
		Float_t * yarr=selc->Track_HitY_pmtrack;
		Float_t * zarr=selc->Track_HitX_pmtrack;
		for(Int_t j=0;j<ntracks;j++){
			Int_t npts=hitBounds[j][1]-hitBounds[j][0];
			tracks3D->GetBin(j+1)->SetMarkerStyle(7);
			tracks3D->GetBin(j+1)->SetMarkerColor(kGray);
			
			for(Int_t k=0;k<npts;k++){
				 tracks3D->GetBin(j+1)->SetNextPoint(xarr[hitBounds[j][0]+k],yarr[hitBounds[j][0]+k],zarr[hitBounds[j][0]+k]);
				//track->SetPointId(new TNamed(TString::Format("Point %i_%i",j,k),""));
			}
			if(hitdrawpopup->IsEntryChecked(kDrawTracks)) tracks3D->GetBin(j+1)->SetMarkerColor(j+2);
		}
		eveMan->EnableRedraw();
		eveMan->Redraw3D();
		Show3DFrame();
	}
		else Hide3DFrame(); 
	//selc->Delete();
	return 0;
}


Int_t MainFrame::Show3DFrame(){
	draw3DFrame->MapRaised();
	return 0;
}

Int_t MainFrame::Hide3DFrame(){
	draw3DFrame->UnmapWindow();
	return 0;
}

Int_t MainFrame::ExcludeButtons(TGPopupMenu * parent,Int_t id, const Int_t * ids, Int_t nbts){
	for(Int_t i=0;i<nbts;i++)
		parent->UnCheckEntry(ids[i]);
	parent->CheckEntry(id);
	return id;
	
}

Int_t MainFrame::TogglePopupEntry(TGPopupMenu * parent,Int_t id){
	if(parent->IsEntryChecked(id)) parent->UnCheckEntry(id); else parent->CheckEntry(id);
	return id;
}

#endif
