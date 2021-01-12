// file      : CAboutDlg.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__D96F56DA_26BE_11D4_BE74_000000000000__INCLUDED_)
#define AFX_ABOUTDLG_H__D96F56DA_26BE_11D4_BE74_000000000000__INCLUDED_

class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
   enum { IDD = IDD_ABOUTBOX };

   BEGIN_MSG_MAP(CAboutDlg)
      MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
      COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
      COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
   END_MSG_MAP()

   LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      CenterWindow(GetParent());
      return TRUE;
   }

   LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      EndDialog(wID);
      return 0;
   }
};

#endif // !defined(AFX_ABOUTDLG_H__D96F56DA_26BE_11D4_BE74_000000000000__INCLUDED_)
