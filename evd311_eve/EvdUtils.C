#ifndef EvdUtils_h
#define EvdUtils_h

#include <TEveBox.h>
#include <TEveManager.h>
#include <TEveStraightLineSet.h>
#include <TEveText.h>
#include <TGLFontManager.h>
#include <TGLAnnotation.h>
#include <TGLViewer.h>


//class TEveBox;
//class TEveStraghtLineSet;
//struct TEveStraghtLineSet::Line_t;

//typedef TEveStraightLineSet::Line_t EveLine_t;
//typedef TEveStraightLineSet::Line_t EveLine_t;
namespace EvdUtils{


	TEveBox * FidBox(const char * name);
	TEveBox * CRPPlane(const char * name);

};

#endif


#ifndef EvdUtils_cxx
#define EvdUtils_cxx



namespace EvdUtils{
TEveBox * FidBox(const char * name) //Fiducial Volume
{
   if (!gEve) return 0;
   TEveBox* b = new TEveBox(name); //Create Box
   b->SetMainColor(kCyan);
   b->SetMainTransparency(75);
   Int_t a1=300;
   Int_t a2=50;
   //Seting Vertices
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

TEveBox * CRPPlane(const char * name) { //CRP Plane
   if (!gEve) return 0;
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
enum ids{
	kIdsX=31,
	kIdsY=32,
	kIdsZ=33
};
//Axis with text comments at ends
TEveStraightLineSet * MakeAxis(const char * name, Int_t ndivx=15,Int_t ndivy=7,Int_t ndivz=7){
	if(!gEve) return 0;
	if(ndivx<2) ndivx=2;
	if(ndivx<2) ndivy=2;
	if(ndivx<2) ndivz=2;
	//Set Of lines - 3 lines
	TEveStraightLineSet * axis = new TEveStraightLineSet(name);
	Float_t fX1=-25;
	Float_t fX2=325;
	Float_t fY1=-75;
	Float_t fY2=75;
	Float_t fZ1=-75;
	Float_t fZ2=75;
	axis->AddLine(fX1,0,0,fX2,0,0);//X axis at picture = Z axis in files
	axis->AddLine(0,fY1,0,0,fY2,0); //Y axis at picture = X axis in files
	axis->AddLine(0,0,fZ1,0,0,fZ2); //Z axis at picture = Y axis in files
	//printf("Ptr to xaxis: %p\n",(void *) xaxis);

	for(Int_t i=0;i<ndivx;++i)
		axis->AddMarker(fX1+(fX2-fX1)/(ndivx-1.0)*i,0,0);
	for(Int_t i=0;i<ndivy;++i)
		axis->AddMarker(0,fY1+(fY2-fY1)/(ndivy-1.0)*i,0);
	for(Int_t i=0;i<ndivz;++i)
		axis->AddMarker(0,0,fZ1+(fZ2-fZ1)/(ndivz-1.0)*i);

	axis->SetLineColor(kYellow);
	axis->SetMarkerStyle(kPlus);
	axis->SetMarkerColor(kYellow);
	//Create text labels
	TEveText * xaxislbl = new TEveText("X"); 
	xaxislbl->PtrMainTrans()->Move3LF(0,76,0);//Y=X
	xaxislbl->SetMainColor(kYellow);
	xaxislbl->SetFontSize(16);
	xaxislbl->SetFontMode(TGLFont::kPixmap);
	xaxislbl->SetLighting(kTRUE);
	axis->AddElement(xaxislbl);
	TEveText * yaxislbl = new TEveText("Y");
	yaxislbl->PtrMainTrans()->Move3LF(0,0,76);//Z=Y
	yaxislbl->SetMainColor(kYellow);
	yaxislbl->SetFontSize(16);
	yaxislbl->SetFontMode(TGLFont::kPixmap);
	yaxislbl->SetLighting(kTRUE);
	axis->AddElement(yaxislbl);
	TEveText * zaxislbl = new TEveText("Z");
	zaxislbl->PtrMainTrans()->Move3LF(326,0,0);//X=Z
	zaxislbl->SetMainColor(kYellow);
	zaxislbl->SetFontSize(16);
	zaxislbl->SetFontMode(TGLFont::kBitmap);
	zaxislbl->SetLighting(kTRUE);
	axis->AddElement(zaxislbl);
	return axis;

}
//Event counter at GL viewer
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



