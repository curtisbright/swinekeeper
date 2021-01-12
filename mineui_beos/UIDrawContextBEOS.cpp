#include "UIDrawContextBEOS.h"

#include <time.h>
#include <be/interface/View.h>
#include <be/interface/Bitmap.h>
#include <be/translation/TranslationUtils.h>

double CUISystemBeOS::getTime() {
   time_t nTime;
   time(&nTime);
   return double(nTime);
}

CIconSetBeOS *CUISystemBeOS::loadIconSet(const char *pszName, int nIconsX, int nIconsY) {
    CIconSetBeOS *pIconSet = new CIconSetBeOS;
    if (pIconSet == NULL) return NULL;
    bool bSuc = pIconSet->load(pszName, nIconsX, nIconsY);
    if (!bSuc) {
        delete pIconSet;
        return 0;
    }
    
    return pIconSet;
}

CIconSetBeOS::CIconSetBeOS() : 
    m_pBitmap(NULL),
    m_nInstX(0), m_nInstY(0)    
{}

CIconSetBeOS::~CIconSetBeOS() 
{
    delete m_pBitmap;
}

CUISize CIconSetBeOS::getSize() const {
    return m_size;
}

bool CIconSetBeOS::load(const char *pszName, int nIconsX, int nIconsY) {
    m_pBitmap = BTranslationUtils::GetBitmap(pszName); 
    if (!m_pBitmap) 
        return false; 

    CUISize pixSize = toUISize(m_pBitmap->Bounds());     
    assert(pixSize.x() % nIconsX == 0);
    assert(pixSize.y() % nIconsY == 0);
    m_size = CUISize(pixSize.x()/nIconsX, pixSize.y()/nIconsY);
    m_nInstX = nIconsX;
    m_nInstY = nIconsY;
    return true;
}

void CIconSetBeOS::drawIcon(BView *pView, int nIdxX, int nIdxY, const CUIPoint &pos) const
{
    assert(m_pBitmap); if (!m_pBitmap) return; 
    CUIRect srcRect(CUIPoint(m_size.x()*nIdxX, m_size.y()*nIdxY), m_size); 
    CUIRect dstRect(CUIPoint(pos.x(), pos.y()), m_size); 
    
    pView-> DrawBitmapAsync(m_pBitmap,  toBeOS(srcRect), toBeOS(dstRect));
}

CUIDrawContextBeOS::CUIDrawContextBeOS(BView *p) : m_pView(p) {
    assert(m_pView); 
}
CUIDrawContextBeOS::~CUIDrawContextBeOS(){
    // m_pView not owned by this class 
}

rgb_color CUIDrawContextBeOS::getBeOSColor(Color col)
{
    assert(col >= 0 && col <END_COLOR);
    return toBeOS(mStatic_RGBPalette[col]);
}


void CUIDrawContextBeOS::drawOuterFrame(const CUIRect &r, Color upperLeft, Color lowerRight, int nSize)
{
   for(int i=0;i<nSize;i++)
   {
      CUIRect r(r.outerRect().inflate(i));

      m_pView->MovePenTo(toBeOS(r.vertex(3)));
      
      m_pView->SetHighColor(getBeOSColor(upperLeft)); 
      m_pView->StrokeLine(toBeOS(r.vertex(0))); m_pView->StrokeLine(toBeOS(r.vertex(1)));
      m_pView->SetHighColor(getBeOSColor(lowerRight)); 
      m_pView->StrokeLine(toBeOS(r.vertex(2))); m_pView->StrokeLine(toBeOS(r.vertex(3)));
   }
}

void CUIDrawContextBeOS::fillRect(const CUIRect &r, Color col)
{
    m_pView->SetHighColor(getBeOSColor(col)); 
    
    m_pView->FillRect(toBeOS(r));
}

void CUIDrawContextBeOS::drawIcon(const CIconSetBase *pIconSet, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY)
{
    const CIconSetBeOS *pBeOSIcon = static_cast<const CIconSetBeOS*>(pIconSet);
    pBeOSIcon->drawIcon(m_pView, nIdxX, nIdxY, p + pIconSet->getSize().scaled(nX, nY));
}

void CUIDrawContextBeOS::drawPixel(const CUIPoint &p, Color col)
{
   assert(col >= 0 && col < END_COLOR);
   if (col >= END_COLOR) col = WHITE;
   m_pView->SetHighColor(getBeOSColor(col)); 
   m_pView->StrokeLine(toBeOS(p)); m_pView->StrokeLine(toBeOS(p));
}


