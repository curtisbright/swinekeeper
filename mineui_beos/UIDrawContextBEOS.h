#ifndef UIDRAWCONTEXTBEOS_H
#define UIDRAWCONTEXTBEOS_H

/* 
*/ 
#include <mineuibase/UIDrawContext.h>
#include <be/interface/Rect.h>
#include <be/interface/Point.h>
#include <be/interface/GraphicsDefs.h> // rgb_color
#include <cassert>

class CIconSetBeOS; 
class BBitmap; 
class BView; 

inline BPoint toBeOS(const CUIPoint &p) {return BPoint(p.x(), p.y());}
inline BRect toBeOS(const CUIRect &r) {return BRect(toBeOS(r.minV()), toBeOS(r.maxV() - CUISize(1,1)));}
inline rgb_color toBeOS(const CUIRGBColor &col) {
   rgb_color beosCol; 
   beosCol.red = col.red(); 
   beosCol.green = col.green(); 
   beosCol.blue = col.blue();
   beosCol.alpha = 0; 
   return beosCol; 
}
inline BRect toBeOS(const CUISize &s) {return BRect(0,0,s.x()-1, s.y()-1);}

inline CUISize toUISize(const BRect &s) {
   assert(s.left == 0); 
   assert(s.top == 0); 
   return CUISize(s.right - s.left + 1, s.bottom-s.top + 1);
}
inline CUIPoint toUI(const BPoint &p) {return CUIPoint(p.x, p.y);}


class CUISystemBeOS : public CUISystemBase {
public:
   static CUISystemBeOS *instanceBeOS() {return static_cast<CUISystemBeOS *>(instance());}
   CIconSetBeOS *loadIconSet(const char *pszName, int nIconsX, int nIconsY);
   virtual double getTime();
};

class CIconSetBeOS : public CIconSetBase {
public:
   CIconSetBeOS();
   ~CIconSetBeOS(); 
   CUISize getSize() const;
   bool load(const char *pszName, int nIconsX, int nIconsY);
   void drawIcon(BView *, int nIdxX, int nIdxY, const CUIPoint &pos) const;
private:
   BBitmap *m_pBitmap; 
   CUISize m_size;
   int m_nInstX, m_nInstY;
};


class CUIDrawContextBeOS : public CUIDrawContextBase {
public: 
   CUIDrawContextBeOS(BView *p);
   ~CUIDrawContextBeOS();
   
   virtual void drawOuterFrame(const CUIRect &r, Color upperLeft, Color lowerRight, int nSize);
   virtual void fillRect(const CUIRect &, Color);
   virtual void drawIcon(const CIconSetBase *pIconSet, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY);
    virtual void drawPixel(const CUIPoint&, Color);

   static rgb_color getBeOSColor(Color col);

private:
   BView *m_pView;
};



#endif 
