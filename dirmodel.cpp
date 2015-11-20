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

#include "dirmodel.h"


DirModel::DirModel(QObject *parent)
  : QAbstractItemModel(parent), pak(nullptr), treeItem(nullptr)
{

}

QVariant DirModel::data(const QModelIndex &index, int role) const
{
  if (treeItem == nullptr) return QVariant();

  DirectoryEntry &entry = treeItem->data(index.row());

  if (index.row() < 0 || index.row() >= treeItem->size() )
    return QVariant();

  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();


  return QVariant(absoluteFileName(entry.filename));
}

Qt::ItemFlags DirModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return 0;

  return QAbstractItemModel::flags(index);
}

QVariant DirModel::headerData(int section, Qt::Orientation orientation, int role) const
{


  return QVariant();
}

QModelIndex DirModel::index(int row, int column, const QModelIndex &parent) const
{
  if (treeItem != nullptr) {
      return createIndex(row, column, (void*)&treeItem->data(row));
    } else return createIndex(row, column, nullptr);

}


int DirModel::rowCount(const QModelIndex &parent) const
{

  if (treeItem == nullptr) {
      return 0;
    }
  else {
      return treeItem->size();
    }
}

int DirModel::columnCount(const QModelIndex &parent) const
{
  return 1;
}

QModelIndex DirModel::parent(const QModelIndex &index) const
{



  return QModelIndex();
}

void DirModel::beginEditing()
{
  beginResetModel();
}

void DirModel::endEditing()
{
  endResetModel();
}

TreeItem *DirModel::getTreeItem() const
{
  return treeItem;
}

void DirModel::setTreeItem(TreeItem *value)
{

  if (value == nullptr) qDebug() << "Null ptr";
  treeItem = value;
  emit layoutChanged();
}

Pak *DirModel::getPak() const
{
  return pak;
}

void DirModel::setPak(Pak *value)
{
  pak = value;
}



