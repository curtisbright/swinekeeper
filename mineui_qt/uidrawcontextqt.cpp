/***************************************************************************
                          uidrawcontextkde.cpp  -  description
                             -------------------
    begin                : Sat Jul 8 2000
    copyright            : (C) 2000 by Hans Kopp
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "uidrawcontextqt.h"

#include <qpainter.h>
#include <cassert>
#include <qpoint.h>
#include <qrect.h>
#include <qsize.h>
#include <time.h>

#include <resources/resources.cpp>   

// Just call the generated function
// "name" is the original image filename WITHOUT the extension
QImage myFindImage(const char* name)
{
   return qembed_findImage(name);
}


double CUISystemQt::getTime() {
   time_t nTime;
   time(&nTime);
   return double(nTime);
}

CIconSetQt *CUISystemQt::loadIconSet(const char *pszName, int nIconsX, int nIconsY) {
    CIconSetQt *pIconSet = new CIconSetQt;
    if (pIconSet == NULL) return NULL;
    bool bSuc = pIconSet->load(pszName, nIconsX, nIconsY);
    if (!bSuc) {
        delete pIconSet;
        return 0;
    }
    
    return pIconSet;
}


CIconSetQt *CUISystemQt::loadIconSetEmbedded(const char *pszName, int nIconsX, int nIconsY)
{
    CIconSetQt *pIconSet = new CIconSetQt;
    if (pIconSet == NULL) return NULL;
    bool bSuc = pIconSet->loadEmbedded(pszName, nIconsX, nIconsY);
    if (!bSuc) {
        delete pIconSet;
        return 0;
    }
    
    return pIconSet;    
}

CIconSetQt::CIconSetQt() : m_nInstX(0), m_nInstY(0) {}

CUISize CIconSetQt::getSize() const {
    return m_size;
}

bool CIconSetQt::initLoad(int nIconsX, int nIconsY)
{
    CUISize pixSize = toUI(m_pixmap.size());     
    // Qt seems to have problems with embedded images that are not aligned by 4-bytes...
    // assert(pixSize.x() % nIconsX == 0);
    assert(pixSize.y() % nIconsY == 0);
    m_size = CUISize(pixSize.x()/nIconsX, pixSize.y()/nIconsY);
    m_nInstX = nIconsX;
    m_nInstY = nIconsY;
    return true;
}


/** 
 * Tries to load the icon set first from the embedded resource
 * named pszName.
 * 
 * @param pszPath: path to a picture file, NULL if non is available 
 * @param pszName: name of a embedded qt resource, NULL if not available 
 
 */ 
bool CIconSetQt::loadEmbedded(const char *pszName, int nIconsX, int nIconsY) 
{
    m_pixmap = qembed_findImage(pszName); 
    if (m_pixmap.isNull()) 
	return false; 
    return initLoad(nIconsX, nIconsY); 
}

bool CIconSetQt::load(const char *pszPath, int nIconsX, int nIconsY) {
    if (!m_pixmap.load(pszPath)) 
	return false; 
    return initLoad(nIconsX, nIconsY); 
}

void CIconSetQt::drawIcon(QPainter *painter, int nIdxX, int nIdxY, const CUIPoint &pos) const
{
     painter->drawPixmap(pos.x(), pos.y(), m_pixmap, m_size.x()*nIdxX, m_size.y()*nIdxY, m_size.x(), m_size.y());
}

CUIDrawContextQt::CUIDrawContextQt(QPainter *p) : m_pPainter(p) {
}
CUIDrawContextQt::~CUIDrawContextQt(){
}

QColor CUIDrawContextQt::getQtColor(Color col)
{
    assert(col >= 0 && col <END_COLOR);
    return toQt(mStatic_RGBPalette[col]);
}


void CUIDrawContextQt::drawOuterFrame(const CUIRect &r, Color upperLeft, Color lowerRight, int nSize)
{
   for(int i=0;i<nSize;i++)
   {
      CUIRect r(r.outerRect().inflate(i));

      m_pPainter->moveTo(toQt(r.vertex(3)));
      m_pPainter->setPen(getQtColor(upperLeft)); m_pPainter->lineTo(toQt(r.vertex(0))); m_pPainter->lineTo(toQt(r.vertex(1)));
      m_pPainter->setPen(getQtColor(lowerRight)); m_pPainter->lineTo(toQt(r.vertex(2))); m_pPainter->lineTo(toQt(r.vertex(3)));
   }
}

void CUIDrawContextQt::fillRect(const CUIRect &r, Color col)
{
    m_pPainter->fillRect(toQt(r), getQtColor(col));
}

void CUIDrawContextQt::drawIcon(const CIconSetBase *pIconSet, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY)
{
    const CIconSetQt *pQtIcon = static_cast<const CIconSetQt*>(pIconSet);
    pQtIcon->drawIcon(m_pPainter, nIdxX, nIdxY, p + pIconSet->getSize().scaled(nX, nY));
}

void CUIDrawContextQt::drawPixel(const CUIPoint &p, Color col)
{
   assert(col >= 0 && col < END_COLOR);
   if (col >= END_COLOR) col = WHITE;
   m_pPainter->setPen(getQtColor(col));
   m_pPainter->drawPoint(toQt(p));
}

