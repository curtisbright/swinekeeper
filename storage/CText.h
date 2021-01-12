// file      : CText.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_CTEXT_H__C0F01232_931F_11D4_BF0C_000000000000__INCLUDED_)
#define AFX_CTEXT_H__C0F01232_931F_11D4_BF0C_000000000000__INCLUDED_

#include <string>

namespace Storage {

class CText {
public: 
   CText() {}
   CText(const std::string &text); 
   CText(int nVal) {setInt(nVal);}
   CText(bool bVal) {setBool(bVal);}

   std::string getString() const {return m_text;}
   void setString(const std::string &text); 

   void setQuotedString(const std::string &text); 
   bool getQuotedString(std::string &text); 

   bool isValidInt() const; 
   int getInt() const; 
   void setInt(int nVal); 
   bool getInt(int &nVal) const;

   bool isValidBool() const; 
   bool getBool() const; 
   void setBool(bool bVal); 
   bool getBool(bool &bVal) const; 

   bool isValidFloat() const;
   double getFloat() const; 
   bool getFloat(double &dV) const; 
   void setFloat(double dV); 

   static bool isValidTextString(const std::string &str); 

private: 
   static std::string stripWS(const std::string &str); 
   static bool isValidTextChar(char c); 

   std::string m_text; 
}; 

}

#endif // !defined(AFX_CTEXT_H__C0F01232_931F_11D4_BF0C_000000000000__INCLUDED_)
