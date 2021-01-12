// file      : CHallOfFameDlg.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CHALLOFFAMEDLG_H_INCLUDED
#define CHALLOFFAMEDLG_H_INCLUDED


#include <mineui_common/CPersistentState.h>

class CHallOfFameDlg : public CDialogImpl<CHallOfFameDlg>
{
public:
   enum { IDD = IDD_HALL_OF_FAME };

   BEGIN_MSG_MAP(CAboutDlg)
      MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
      COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
      COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
   END_MSG_MAP()

   CHallOfFameDlg(const CScoreTable &scoreTable) : m_scoreTable(scoreTable) {}

   LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      SetDlgItemText(IDC_NAME_BEGINNER, m_scoreTable.m_scoreTable[0].m_name.c_str()); 
      SetDlgItemText(IDC_NAME_ADVANCED, m_scoreTable.m_scoreTable[1].m_name.c_str()); 
      SetDlgItemText(IDC_NAME_PROFI, m_scoreTable.m_scoreTable[2].m_name.c_str()); 

      SetDlgItemInt(IDC_TIME_BEGINNER, m_scoreTable.m_scoreTable[0].m_nTime); 
      SetDlgItemInt(IDC_TIME_ADVANCED, m_scoreTable.m_scoreTable[1].m_nTime); 
      SetDlgItemInt(IDC_TIME_PROFI, m_scoreTable.m_scoreTable[2].m_nTime); 

      CenterWindow(GetParent());
      return TRUE;
   }

   LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      EndDialog(wID);
      return 0;
   }
private: 
      CScoreTable m_scoreTable; 
   
};


#endif 
