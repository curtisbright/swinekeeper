/***************************************************************************
                          uidrawcontextkde.h  -  description
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

#ifndef UIDRAWCONTEXTQt_H
#define UIDRAWCONTEXTQt_H

#include <mineuibase/UIDrawContext.h>
#include <qpixmap.h>

class QPainter;
class QColor;
class CIconSetQt;

inline QPoint toQt(const CUIPoint &p) {return QPoint(p.x(), p.y());}
inline QRect toQt(const CUIRect &r) {return QRect(toQt(r.minV()), toQt(r.maxV() - CUISize(1,1)));}
inline QColor toQt(const CUIRGBColor &col) {return QColor(col.red(), col.green(), col.blue());}
inline QSize toQt(const CUISize &s) {return QSize(s.x(), s.y());}

inline CUISize toUI(const QSize &s) {return CUISize(s.width(), s.height());}
inline CUIPoint toUI(const QPoint &p) {return CUIPoint(p.x(), p.y());}

class CUISystemQt : public CUISystemBase {
public:
   static CUISystemQt *instanceQt() {return static_cast<CUISystemQt *>(instance());}
   CIconSetQt *loadIconSet(const char *pszName, int nIconsX, int nIconsY);
   CIconSetQt *loadIconSetEmbedded(const char *pszName, int nIconsX, int nIconsY); 
   virtual double getTime();
};

class CIconSetQt : public CIconSetBase {
public:
   CIconSetQt();
   CUISize getSize() const;
   bool load(const char *pszName, int nIconsX, int nIconsY);
   bool loadEmbedded(const char *pszName, int nIconsX, int nIconsY); 
   void drawIcon(QPainter *, int nIdxX, int nIdxY, const CUIPoint &pos) const;
private:
   QPixmap m_pixmap;
   CUISize m_size;
   int m_nInstX, m_nInstY;

   bool initLoad(int nIconsX, int nIconsY); 
};


class CUIDrawContextQt : public CUIDrawContextBase {
public: 
   CUIDrawContextQt(QPainter *p);
   ~CUIDrawContextQt();
   
   virtual void drawOuterFrame(const CUIRect &r, Color upperLeft, Color lowerRight, int nSize);
   virtual void fillRect(const CUIRect &, Color);
   virtual void drawIcon(const CIconSetBase *pIconSet, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY);
   virtual void drawPixel(const CUIPoint&, Color);

   static QColor getQtColor(Color col);

private:
   QPainter *m_pPainter;
};

#endif
