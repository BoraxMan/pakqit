/*
 * Utility to manipulate Quake PAK data files.
 * Copyright (C) 2015  Dennis Katsonis <dennisk (at) netspace dot net dot au>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#ifndef FUNC_H
#define FUNC_H


//#include <sys/sysinfo.h>
//#include <string>
#include <algorithm>
#include <array>
#include <string>
#include <fstream>

enum class fileTypes {
  Map,
  Texture,
  Graphic,
  Sound,
  Demo,
  Model,
  Skin,
  Data,
  Config,
  Other
};


const int PAK_HEADER_SIZE = 12;
const int PAK_DATA_LABEL_SIZE = 56;
const int DIRECTORY_ENTRY_SIZE = 64;
#ifdef CLI
std::string absoluteFileName(std::array<char, PAK_DATA_LABEL_SIZE> fname);
#endif
std::string arrayToString(std::array< char, int(PAK_DATA_LABEL_SIZE) > &filename);

void stringToArray(std::string s, std::array<char, PAK_DATA_LABEL_SIZE> &arrai);

#ifdef CLI
std::string getFileName(const char *filename);
#endif

unsigned long get_mem_total();


#endif // FUNC_H
