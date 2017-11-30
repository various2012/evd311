#ifndef EvdUtils_h
#define EvdUtils_h

#include <TEveBox.h>
#include <TEveManager.h>
#include <TEveStraightLineSet.h>
#include <TEveText.h>
#include <TGLFontManager.h>
#include <TGLAnnotation.h>
#include <TGLViewer.h>

class TEveBox;
namespace EvdUtils{


	TEveBox * FidBox(const char * name);
	TEveBox * CRPPlane(const char * name);

};

#endif


#ifndef EvdUtils_cxx
#define EvdUtils_cxx



namespace EvdUtils{
TEveBox * FidBox(const char * name)
{
   //if (!gEve) return 0;
   TEveBox* b = new TEveBox(name);
   b->SetMainColor(kCyan);
   b->SetMainTransparency(75);
   Int_t a1=300;
   Int_t a2=50;
   b->SetVertex(0, 0 ,-a2,-a2);
   b->SetVertex(1, a1,-a2,-a2);
   b->SetVertex(2, a1,-a2, a2);
   b->SetVertex(3, 0 ,-a2, a2);
   b->SetVertex(4, 0 , a2,-a2);
   b->SetVertex(5, a1, a2,-a2);
   b->SetVertex(6, a1, a2, a2);
   b->SetVertex(7, 0 , a2, a2);

   return b;
}

TEveBox * CRPPlane(const char * name) {
   //if (!gEve) return 0;
   TEveBox* b = new TEveBox(name);
   b->SetMainColor(kYellow);
   b->SetMainTransparency(0);
   Int_t a1=300;
   Int_t a2=50;
   Int_t z1=a2+2;
   Int_t z2=z1+1;
   b->SetVertex(0, 0 , z1,-a2);
   b->SetVertex(1, a1, z1,-a2);
   b->SetVertex(2, a1, z1, a2);
   b->SetVertex(3, 0 , z1, a2);
   b->SetVertex(4, 0 , z2,-a2);
   b->SetVertex(5, a1, z2,-a2);
   b->SetVertex(6, a1, z2, a2);
   b->SetVertex(7, 0 , z2, a2);
   return b;
}


TEveStraightLineSet * MakeAxis(const char * name, Int_t ndivx=15,Int_t ndivy=7,Int_t ndivz=7){
	if(ndivx<2) ndivx=2;
	if(ndivx<2) ndivy=2;
	if(ndivx<2) ndivz=2;
	TEveStraightLineSet * axis = new TEveStraightLineSet(name);
	TEveStraightLineSet::Line_t * xaxis = axis->AddLine(-25,0,0,325,0,0);
	TEveStraightLineSet::Line_t * yaxis = axis->AddLine(0,-75,0,0,75,0);
	TEveStraightLineSet::Line_t * zaxis = axis->AddLine(0,0,-75,0,0,75);
	for(Int_t i=0;i<ndivx;++i)
		axis->AddMarker(xaxis->fId,i/(ndivx-1.0));
	for(Int_t i=0;i<ndivy;++i)
		axis->AddMarker(yaxis->fId,i/(ndivy-1.0));
	for(Int_t i=0;i<ndivz;++i)
		axis->AddMarker(zaxis->fId,i/(ndivz-1.0));

	axis->SetLineColor(kYellow);
	axis->SetMarkerStyle(kPlus);
	axis->SetMarkerColor(kYellow);
	TEveText * xaxislbl = new TEveText("X");
	xaxislbl->PtrMainTrans()->Move3LF(0,76,0);
	xaxislbl->SetMainColor(kYellow);
	xaxislbl->SetFontSize(16);
	xaxislbl->SetFontMode(TGLFont::kPixmap);
	xaxislbl->SetLighting(kTRUE);
	axis->AddElement(xaxislbl);
	TEveText * yaxislbl = new TEveText("Y");
	yaxislbl->PtrMainTrans()->Move3LF(0,0,76);
	yaxislbl->SetMainColor(kYellow);
	yaxislbl->SetFontSize(16);
	yaxislbl->SetFontMode(TGLFont::kPixmap);
	yaxislbl->SetLighting(kTRUE);
	axis->AddElement(yaxislbl);
	TEveText * zaxislbl = new TEveText("Z");
	zaxislbl->PtrMainTrans()->Move3LF(326,0,0);
	zaxislbl->SetMainColor(kYellow);
	zaxislbl->SetFontSize(16);
	zaxislbl->SetFontMode(TGLFont::kBitmap);
	zaxislbl->SetLighting(kTRUE);
	axis->AddElement(zaxislbl);
	return axis;

}

TGLAnnotation * EventCount(TGLViewer * v,const char * text="No Events"){
	//if(!gEve) return 0;
	//TGLViewer * v = gEve->GetDefaultGLViewer();
	TGLAnnotation * ann = new TGLAnnotation(v,text,0.1,0.1);
	ann->SetTextSize(0.05);
	ann->SetTextColor(kYellow);
	return ann;
}

//TEveText * EventCount(const char * text="Event 0"){
//	TEveText * t = new TEveText(text);
//	t->SetFontMode(TGLFont::kPolygon);
//	t->SetMainColor(kGreen);
//	t->SetFontSize(24);
//	return t;
//	
//}

};

#endif



