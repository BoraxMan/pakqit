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

#include <cassert>
#include "mainwindow.h"
#include <QApplication>
#include "func.h"
#include "qfunc.h"
#include <cassert>
#include <QDebug>
#include "pakexception.h"
#include "exceptionhandler.h"
#include "config.h"


#include <iostream>

int main(int argc, char *argv[])
{
  qDebug() << "Debug mode!" << Version;
  int result;

  QApplication a(argc, argv);
  MainWindow *w;

  a.setOrganizationName("Dekay Software");
  a.setApplicationName("pakqit");
  qDebug << "Test";

  // Initialise the QMap with known types.
  // We map to the type, and not a descriptive string
  // in case we just want to know what type, but not
  // display the description of the type.

  extensionMap().insert("bsp", fileTypes::Map);
  extensionMap().insert("wal", fileTypes::Texture);
  extensionMap().insert("wav", fileTypes::Sound);
  extensionMap().insert("mdl", fileTypes::Model);
  extensionMap().insert("dem", fileTypes::Demo);
  extensionMap().insert("pcx", fileTypes::Graphic);
  extensionMap().insert("md2", fileTypes::Model);
  extensionMap().insert("dm2", fileTypes::Demo);
  extensionMap().insert("tga", fileTypes::Texture);
  extensionMap().insert("wad", fileTypes::Texture);
  extensionMap().insert("lmp", fileTypes::Data);
  extensionMap().insert("bin", fileTypes::Data);
  extensionMap().insert("rc", fileTypes::Config);
  extensionMap().insert("cfg", fileTypes::Config);

  try {
    w = new MainWindow;
    w->show();
  } catch (const PakException &e) {
    exceptionHandler(e);
    exit(1);
  }
  result =  a.exec();
  delete w;
  return result;
}
