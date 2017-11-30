#ifndef EvdUtils_h
#define EvdUtils_h

#include <TEveBox.h>
#include <TEveManager.h>

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
   if (!gEve) return 0;
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
};

#endif



