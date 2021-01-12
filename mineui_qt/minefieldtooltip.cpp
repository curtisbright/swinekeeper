/***************************************************************************
                          minefieldtooltip.cpp  -  description
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
#include "StdAfx.h"
#include "minefieldtooltip.h"
#include <gamecontrol/CGameManager.h>
#include <qrect.h>
#include <qpoint.h>

MineFieldToolTip::MineFieldToolTip(QWidget *parent, CGameManager *pGameMgr) :
   QToolTip(parent),
   m_pGameMgr(pGameMgr)
{
}

void MineFieldToolTip::maybeTip (const QPoint &p)
{
  std::string msg;
    if (m_pGameMgr->getToolTipMsg(msg))
    {
         QPoint diff(2,2);
     tip(QRect(p-diff, p+diff), msg.c_str());
    }        
}
