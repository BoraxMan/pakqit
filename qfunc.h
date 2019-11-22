#ifndef QFUNC_H
#define QFUNC_H

#include <array>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QModelIndexList>
#include <QMessageBox>
#include <QVector>
//#include <QtAlgorithms>


#include "func.h"

class QStringList;

fileTypes getFileType(QString extension);
bool confirmOverwrite(QString filename);
QString absoluteFileName(std::array<char, PAK_DATA_LABEL_SIZE> fname);
QString arrayToQString(std::array<char, PAK_DATA_LABEL_SIZE> &filename);
//void stringToArray(std::string s, std::array<char, PAK_DATA_LABEL_SIZE> &arrai);
QString getExtension(std::array<char, PAK_DATA_LABEL_SIZE> &filename);
QString getFileTypeDescription(fileTypes type);
QString getFileName(const QString &x);
QString getSinglePathSelection();
QString getSingleFileSelection(); // Not implemented yet.  May not need it.
QStringList getFileSelections();

QMap<QString, fileTypes>& extensionMap();
#endif // QFUNC_H

