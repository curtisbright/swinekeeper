/***************************************************************************
                          minefieldtooltip.h  -  description
                             -------------------
    begin                : Sun Jul 30 2000
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

#include <qtooltip.h>

class CGameManager;

class MineFieldToolTip : public QToolTip
{
   public:
      MineFieldToolTip(QWidget *parent, CGameManager *pGameMgr);
      void maybeTip ( const QPoint & p );
   private:
     CGameManager *m_pGameMgr;
};
