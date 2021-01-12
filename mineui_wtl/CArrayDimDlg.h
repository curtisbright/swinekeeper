// file      : CArrayDimDlg.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CARRAYDIMDLG_H_INCLUDED
#define CARRAYDIMDLG_H_INCLUDED

#include "resource.h" 

#include <gamecontrol/GameMisc.h>

class CArrayDimDlg : public CDialogImpl<CArrayDimDlg>
{
public:
   enum { IDD = IDD_ARRAY_DIM };

   CArrayDimDlg() : m_gameDim(30, 16, 99) {} 

   BEGIN_MSG_MAP(CArrayDimDlg)
      MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
      COMMAND_ID_HANDLER(IDOK, OnOKCmd)
      COMMAND_ID_HANDLER(IDCANCEL, OnCancelCmd)
   END_MSG_MAP()

   LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      SetDlgItemInt(IDC_EDIT_WIDTH, m_gameDim.sizeX()); 
      SetDlgItemInt(IDC_EDIT_HEIGHT, m_gameDim.sizeY()); 
      SetDlgItemInt(IDC_EDIT_MINES, m_gameDim.bombCount()); 
      CenterWindow(GetParent());
      return TRUE;
   }

   LRESULT OnOKCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      BOOL bSuc; 
      m_gameDim.m_nSizeX = GetDlgItemInt(IDC_EDIT_WIDTH, &bSuc); 
      ATLASSERT(bSuc); 
      m_gameDim.m_nSizeY = GetDlgItemInt(IDC_EDIT_HEIGHT, &bSuc); 
      ATLASSERT(bSuc); 
      m_gameDim.m_nMines = GetDlgItemInt(IDC_EDIT_MINES, &bSuc); 
      ATLASSERT(bSuc); 
      EndDialog(wID);
      return 0;
   }

   LRESULT OnCancelCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      EndDialog(wID);
      return 0;
   }

   bool areValuesValid() {
      return m_gameDim.m_nSizeX >= 6 && m_gameDim.m_nSizeX <= 100 
          && m_gameDim.m_nSizeY >= 6 && m_gameDim.m_nSizeY <= 100 
          && m_gameDim.m_nMines >= 1 && m_gameDim.m_nMines < m_gameDim.m_nSizeX * m_gameDim.m_nSizeY; 
   } 

public: 
   CGameDim m_gameDim; 
};

#endif 
