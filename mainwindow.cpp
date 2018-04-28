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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  unsavedChanges(false)
{
  ui->setupUi(this);
  pakFile = QSharedPointer<Pak>(new Pak());
  pakModel  = QSharedPointer<PakModel>(new PakModel(pakFile, nullptr));
  dirmodel = QSharedPointer<DirModel>(new DirModel(nullptr));
  ui->treeView->setModel(pakModel.data());
  ui->listView_2->setModel(dirmodel.data());


  connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(aboutQT()));
  connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openPak()));
  connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(savePak()));
  connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closePak()));
  connect(ui->actionExportDirectoryTree, SIGNAL(triggered()), this, SLOT(exportDirectoryTree()));
  connect(ui->actionExportEntireFile, SIGNAL(triggered()), this, SLOT(exportFile()));
  connect(ui->actionImportDirectoryTree, SIGNAL(triggered()), this, SLOT(importDirectoryTree()));
  connect(ui->actionImportFile, SIGNAL(triggered()), this, SLOT(importFile()));
  connect(ui->treeView,SIGNAL(clicked(QModelIndex)), this, SLOT(changedTreeView(QModelIndex)));
  connect(ui->actionDeleteDirectory, SIGNAL(triggered()), this, SLOT(deleteTree()));
  connect(ui->actionDeleteFile, SIGNAL(triggered()), this, SLOT(deleteFile()));
  connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(savePakAs()));
  connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newPak()));
  connect(ui->actionManual, SIGNAL(triggered()), this, SLOT(displayManual()));

  // If we have specified a file, load it

  QStringList arguments = QApplication::arguments();

  if (arguments.size() > 1) {
      if (openPak(arguments.at(1)) == -1) {
          QString message = "Could not open file ";
          message += arguments.at(1);
          throw (PakException("Error opening file", message.toStdString().c_str()));
        }
      setEnableGUI(true);
    }

  // so we'll set the views by 'clicking' on the root item.
  ui->treeView->setCurrentIndex(ui->treeView->rootIndex());
  changedTreeView(ui->treeView->rootIndex()); // There already is an empty root,


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::clearFileInfoLabels()
{
  ui->offsetLabel->clear();
  ui->sizeLabel->clear();
  ui->typeLabel->clear();
  ui->summaryLabel->clear();
}

void MainWindow::changedTreeView(QModelIndex index)
{
  TreeItem *x = static_cast<TreeItem*>(index.internalPointer());

  if (index.row() == -1) {
      x = pakFile->rootEntry();
    }
  dirmodel->beginEditing();
  dirmodel->setTreeItem(x);
  // ui->listView_2->reset();
  dirmodel->endEditing();
  clearFileInfoLabels();
}

void MainWindow::listSelected(QModelIndex index)
{
  ui->sizeLabel->setText(QString::number(static_cast<DirectoryEntry*>(index.internalPointer())->getLength()));
  auto extension = getExtension(static_cast<DirectoryEntry*>(index.internalPointer())->filename);
  auto fileType = getFileType(extension);
  ui->typeLabel->setText(getFileTypeDescription(fileType));
  ui->offsetLabel->setText(QString::number(static_cast<DirectoryEntry*>(index.internalPointer())->getPosition()));
  ui->summaryLabel->setText(arrayToQString(static_cast<DirectoryEntry*>(index.internalPointer())->filename));
}

void MainWindow::aboutQT()
{
  QApplication::aboutQt();
}


void MainWindow::about()
{
  QDialog dialog;
  Ui::Dialog aboutDialog;
  aboutDialog.setupUi(&dialog);
  aboutDialog.versionLabel->setText(Version);
  dialog.exec();
}


int MainWindow::openPakFile()
{
  try {
    dirmodel->beginEditing();
    pakModel->beginEditing();
    pakFile->open(pakFilename.toStdString().c_str());
    dirmodel->endEditing();
    pakModel->endEditing();
    //    ui->treeView->reset();
    //   ui->listView_2->reset();
  }  catch (const PakException &e) {
    exceptionHandler(e);
    dirmodel->endEditing();
    pakModel->endEditing();
    //ui->treeView->reset();
    clearFileInfoLabels();
    return -1;
  }

  ui->treeView->setCurrentIndex(ui->treeView->rootIndex());
  changedTreeView(ui->treeView->rootIndex());
  ui->fileNameLabel->setText(getFileName(pakFilename));
  return 0;

}

void MainWindow::setEnableGUI(bool enabled)
{
  ui->listView_2->setEnabled(enabled);
  ui->treeView->setEnabled(enabled);
  ui->pushButtonAddEntry->setEnabled(enabled);
  ui->pushButtonAddTree->setEnabled(enabled);
  ui->pushButtonDeleteEntry->setEnabled(enabled);
  ui->pushButtonDeleteTree->setEnabled(enabled);
  ui->pushButtonExtractEntry->setEnabled(enabled);
  ui->pushButtonExtractTree->setEnabled(enabled);
  ui->menuExport->setEnabled(enabled);
  ui->menuImport->setEnabled(enabled);
  ui->menuDelete->setEnabled(enabled);
  ui->actionCheck->setEnabled(enabled);
}


int MainWindow::openPak(QString filename)
{


  pakFilename = filename;
  return openPakFile();
}

int MainWindow::openPak()
{
  QString fname  = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Pak File (*.pak)"));
  QString filename = QDir::toNativeSeparators(fname);

  if (!filename.isNull()) {
      closePak();
    } else {
      return 0;
    }
  pakFilename = filename;
  int result = openPakFile();
  if (!result) {
      setEnableGUI(true);
    }
  return result;
}

int MainWindow::savePak()
{

  try {
    pakFile->writePak(pakFilename.toStdString().c_str());
  } catch (const PakException &e) {
    exceptionHandler(e);
    //ui->treeView->reset();
    return -1;
  }
  unsavedChanges = false;
  return 0;
}

int MainWindow::savePakAs()
{
  QFileDialog fileDialog(this, "Save File As");
  fileDialog.setNameFilter("Pak File (*.pak)");
  fileDialog.setDefaultSuffix("pak");

  if (fileDialog.exec()) {

      QString fname = fileDialog.selectedFiles().first();
      QString filename = QDir::toNativeSeparators(fname);
      if (!filename.isNull()) {
          pakFilename = filename;
          ui->fileNameLabel->setText(getFileName(pakFilename));
          return savePak();
        } else {
          return 1;
        }
    }
  ui->fileNameLabel->setText(getFileName(pakFilename));
  return 1;
}

int MainWindow::closePak()
{
  if (unsavedChanges) {
      QMessageBox msgBox;
      msgBox.setWindowTitle("Unsaved changes");
      msgBox.setText("The file has been modified.");
      msgBox.setInformativeText("Do you want to continue and lose changes?");
      msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Save | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int result = msgBox.exec();
      switch (result) {
        case QMessageBox::Save:
          if (savePak() == -1) {
              return -1;
            }
          break;
        case QMessageBox::Cancel:
          return 1;
          break;
        case QMessageBox::Close:
          break;
        default:
          return 1;
        }
    }
  try {
    pakFile->close();
  }  catch (const PakException &e) {
    exceptionHandler(e);
  }
  dirmodel->beginEditing();
  pakModel->beginEditing();
  pakFilename.clear();
  dirmodel->setTreeItem(pakFile->rootEntry());
  dirmodel->endEditing();
  pakModel->endEditing();
  changedTreeView(QModelIndex());
  clearFileInfoLabels();
  ui->fileNameLabel->clear();
  setEnableGUI(false);
  return 0;
}

int MainWindow::newPak()
{
  closePak();
  QString fname = QFileDialog::getSaveFileName(this, tr("Create new File"),"", tr("Pak File (*.pak)"));
  pakFilename = QDir::toNativeSeparators(fname);

  ui->fileNameLabel->setText(getFileName(pakFilename));
  pakFile->reset();
  setEnableGUI(true);
  return 0;
}

void MainWindow::exportDirectoryTree()
{

  QModelIndexList selectedItems = ui->treeView->selectionModel()->selectedIndexes();
  QString path = getSinglePathSelection();
  if (selectedItems.empty()) {
      ui->statusBarLabel->setText("Exporting entire file.");
      pakFile->exportPak(path.toStdString().c_str());
      return;
    }

  if (path.isNull()) {
      return;
    }

  try {
    for (QModelIndex x : selectedItems) {
        qDebug() << static_cast<TreeItem*>(x.internalPointer())->label().c_str();
        pakFile->exportDirectory(path.toStdString().c_str(), static_cast<TreeItem*>(x.internalPointer()));
        // qtcreator really shoudl deduce x here, so we can use auto in the range for loop
        // and still get proper autocompletion.
      }
  }  catch (const PakException &e) {
    exceptionHandler(e);
  }
}

void MainWindow::importDirectoryTree()
{

  TreeItem *destination{nullptr};
  QModelIndexList selectedItems = ui->treeView->selectionModel()->selectedIndexes();

  if (selectedItems.empty()) {
      destination = pakFile->rootEntry();
    }  else if (selectedItems.size() > 1) {
      QMessageBox(QMessageBox::Warning, QString("Multiple destinations"), QString("Can only import into a single directory."),QMessageBox::Close).exec();
    } else {
      destination = static_cast<TreeItem*>((selectedItems.at(0).internalPointer()));
    }

  QString path = getSinglePathSelection();
  if (path.isNull()) {
      return;
    }
  pakModel->beginEditing();
  try {
    pakFile->importDirectory(path.toStdString().c_str(), destination);

    //ui->treeView->reset();

  } catch (const PakException &e) {
    exceptionHandler(e);
    // ui->treeView->reset();
    pakModel->endEditing();
  }
  unsavedChanges = true;
  pakModel->endEditing();
  return;
}

void MainWindow::exportFile()
{
  QModelIndexList selectedItems = ui->listView_2->selectionModel()->selectedIndexes();

  if (selectedItems.empty()) {
      ui->statusBarLabel->setText("No files selected.");
      QMessageBox(QMessageBox::Warning, QString("No selection"), QString("No files selected."),QMessageBox::Close).exec();
      return;
    }

  QString path = getSinglePathSelection();

  try {
    for (QModelIndex x : selectedItems) {
        qDebug() << absoluteFileName(static_cast<DirectoryEntry*>(x.internalPointer())->filename );
        static_cast<DirectoryEntry*>(x.internalPointer())->exportFile(path.toStdString().c_str(), pakFile->getFileHandle());
      }
  } catch (const PakException &e) {
    exceptionHandler(e);
  }
}

void MainWindow::importFile()
{
  TreeItem *destination{nullptr};
  QModelIndexList selectedItems = ui->treeView->selectionModel()->selectedIndexes();

  if (selectedItems.size() > 1) {
      QMessageBox(QMessageBox::Warning, QString("Multiple selections"), QString("Can only import file to one directory."),QMessageBox::Close).exec();
      return;
    } else if (selectedItems.empty()) {
      destination = pakFile->rootEntry();
    } else {
      destination = static_cast<TreeItem*>((selectedItems.at(0).internalPointer()));
    }

  QStringList files = getFileSelections();

  for (QString file : files) {
      QString x = QDir::toNativeSeparators(file);
      DirectoryEntry newEntry;
      QString path = QString(destination->pathLabel().c_str());
      dirmodel->beginEditing();
      try {
        pakFile->addEntry(path.toStdString(), x.toStdString().c_str(), destination);
      } catch (PakException &e) {
        exceptionHandler(e);
        dirmodel->endEditing();
      }
    }
  //ui->listView_2->reset();
  dirmodel->endEditing();
  unsavedChanges = true;
}

void MainWindow::deleteTree()
{
  QMap<TreeItem *, int> offsets;

  QModelIndexList selectedItems = ui->treeView->selectionModel()->selectedIndexes();


  if (selectedItems.empty()) {
      ui->statusBarLabel->setText("No directories selected.");
      QMessageBox(QMessageBox::Warning, QString("No selection"), QString("No directories selected."),QMessageBox::Close).exec();
      return;
    }

  pakModel->beginEditing();
  int offset{0};

  std::sort(selectedItems.begin(), selectedItems.end(), [] (QModelIndex x, QModelIndex y)
  {return x.row() < y.row();});

  for (QModelIndex x : selectedItems) {
      TreeItem *ptr = static_cast<TreeItem*>(x.internalPointer());
      if (ptr  == nullptr) {
          QMessageBox(QMessageBox::Warning, QString("Root directory selected"), QString("The root directory of a PAK file cannot be deleted."),QMessageBox::Close).exec();
          return;
        } else {
          ptr = static_cast<TreeItem*>(x.internalPointer())->paren();

          QMap<TreeItem*, int>::iterator itr = offsets.find(ptr);

          if (itr == offsets.end()) { // No current key, add one with offset 0;
              itr = offsets.insert(ptr, 0);
              offset = 0;
            } else {
              offset = itr.value();  // If found, set the offset to it.
            }

          pakFile->deleteChild(ptr, (x.row() - offset));
          *itr+=1;
        }
    }

  //ui->listView_2->reset();
  //ui->treeView->reset();
  unsavedChanges = true;
  pakModel->endEditing();
  changedTreeView(QModelIndex());
}

void MainWindow::deleteFile()
{
  TreeItem *parentTree = nullptr;
  QModelIndexList selectedItems = ui->listView_2->selectionModel()->selectedIndexes();
  QModelIndex parentTreeSelection = ui->treeView->currentIndex();

  if (parentTreeSelection.row() == -1) {
      parentTree = pakFile->rootEntry();
    } else {
      parentTree = static_cast<TreeItem*>(ui->treeView->currentIndex().internalPointer());
    }

  if (selectedItems.empty()) {
      ui->statusBarLabel->setText("No files selected.");
      QMessageBox(QMessageBox::Warning, QString("No selection"), QString("No files selected to be deleted."),QMessageBox::Close).exec();
      return;
    }

  std::sort(selectedItems.begin(), selectedItems.end(), [] (QModelIndex x, QModelIndex y)
  {return x.row() < y.row();});

  dirmodel->beginEditing();
  try {
    int offset{0};
    for (auto x : selectedItems) {
        pakFile->deleteEntry(parentTree, (x.row() - offset++));

      }
    //ui->listView_2->reset();
    unsavedChanges = true;
  } catch (PakException &e) {
    exceptionHandler(e);
    dirmodel->endEditing();
  }
  dirmodel->endEditing();
}

void MainWindow::displayManual()
{
  QDialog dialog;
  Ui::Manual manualDialog;
  manualDialog.setupUi(&dialog);
  dialog.exec();

}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (unsavedChanges == true) {
      if (closePak() == -1) {
          event->ignore();
        }
    }
  event->accept();
}
