// Author: Vladyslav Kaliuzhnyi 

//

#include "MainManager.C"
#include <TVirtualX.h>
#include <TROOT.h>
#include <TApplication.h>

//class MainFrame : public TGMainFrame;

#ifdef __MAKECINT__
#pragma link C++ class MainManager+;
#pragma link C++ class EventManager+;
#endif
void evd311()
{
	UInt_t ww,hh;
	Int_t wx,hx;
	UInt_t wmin=1024;
	UInt_t hmin=640;
	gVirtualX->GetWindowSize(gVirtualX->GetDefaultRootWindow(),wx,hx,ww,hh); //Get Maximum size of Window, may not work in VMs
	//if (ww<640) ww=640;
	//if (hh<480) hh=480;
	Int_t w,h;
	if( ww>wmin) w=wmin; else w=ww;
	if (hh>hmin) h=hmin; else h=hh;
	//printf("Width: %i, Height %i\n",w,h);
	new MainManager(w,h); //Start Main Frame
}

#ifndef __CINT__
int main(int argc, char **argv )
{
	TApplication theApp("App", &argc, argv);
	evd311();
	theApp.Run();
	return 0;
}
#endif


