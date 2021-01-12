// file      : CScoreNameDlg.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CSCORENAMEDLG_H_INCLUDED
#define CSCORENAMEDLG_H_INCLUDED

#include <string>

class CScoreNameDlg : public CDialogImpl<CScoreNameDlg>
{
public:
   enum { IDD = IDD_SCORE_NAME };

   BEGIN_MSG_MAP(CAboutDlg)
      MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
      COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
      COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
   END_MSG_MAP()

   LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      SetDlgItemText(IDC_USER_NAME, "Unknown"); 
      CenterWindow(GetParent());
      return TRUE;
   }

   LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      char szTmp[100]; 
      GetDlgItemText(IDC_USER_NAME, szTmp, 100); 

      m_userName = std::string(szTmp); 

      EndDialog(wID);
      return 0;
   }

   std::string m_userName; 
};


#endif 
