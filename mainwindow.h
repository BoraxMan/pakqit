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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QModelIndex>
#include <QSharedPointer>
#include <QModelIndexList>
#include <QModelIndex>
#include <QMessageBox>
#include <QEvent>
#include <QMap>
#include <QVector>
#include <QShortcut>
#include <QDir>
#include <algorithm>

#include "pakmodel.h"
#include "dirmodel.h"
#include "qfunc.h"
#include "func.h"
#include "ui_about.h"
#include "ui_manual.h"
#include "pak.h"
#include "exceptionhandler.h"
#include "config.h"

namespace Ui {
  class MainWindow;
}


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  QSharedPointer<PakModel> pakModel;
  QSharedPointer<DirModel> dirmodel;
  QSharedPointer<Pak> pakFile;

  //QPixmap image;
  void clearFileInfoLabels();
  bool unsavedChanges;
  QString pakFilename;
  int openPakFile();
  void setEnableGUI(bool enabled);
  //QSettings pakqitSettings;
  // QQueue<QString> recentFileList;

private slots:
  void changedTreeView(QModelIndex index);
  void listSelected(QModelIndex index);
  void aboutQT();
  void about();
  int openPak();
  int openPak(QString filename);
  int savePak(); // 0 if OK.  -1 on error.
  int savePakAs();
  int closePak();
  int newPak();
  void exportDirectoryTree();
  void importDirectoryTree();
  void exportFile();
  void importFile();
  void deleteTree();
  void deleteFile();
  void displayManual();

protected:
  void closeEvent(QCloseEvent *event);

};


#endif // MAINWINDOW_H
