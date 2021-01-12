// file      : MineStd.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef MINESTD_H_INCLUDED
#define MINESTD_H_INCLUDED

namespace MineStd {

// can't use std::max here because 
// msvc defines the macros 'min' and 'max' somewhere in 
// its headers 
template<typename T> 
T auxMax(const T &a, const T &b) {
   if (a > b) return a; else return b; 
}

template<typename T> 
T auxMin(const T &a, const T &b) {
   if (a < b) return a; else return b; 
}

}; 
#endif 
