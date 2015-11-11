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

#include "pakmodel.h"
#include <QDebug>

PakModel::PakModel(QObject *parent)
    : QAbstractItemModel(parent), rootItem(nullptr)
{

}

PakModel::PakModel(QSharedPointer<Pak> pakfile, QObject *parent)
    : QAbstractItemModel(parent)
{
  pak = pakfile;

  rootItem = pak->rootEntry();


}

QVariant PakModel::data(const QModelIndex &index, int role) const
{

  if (!index.isValid())
      return QVariant();

  if (role != Qt::DisplayRole)
      return QVariant();

  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
 // DirectoryEntry entry = item->data(0);
  //return entry.filename
  return QVariant(item->label().c_str());
}


Qt::ItemFlags PakModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
      return 0;

  return QAbstractItemModel::flags(index);
}

QVariant PakModel::headerData(int, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return QVariant("Header");

  return QVariant();
}

QModelIndex PakModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
         return QModelIndex();

     TreeItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     TreeItem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();

}

QModelIndex PakModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
      return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
      return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int PakModel::rowCount(const QModelIndex &parent) const
{

  TreeItem *parentItem;
     if (parent.column() > 0)
         return 0;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     return parentItem->childCount();

}

int PakModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
      return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  else {
      return rootItem->columnCount();
  }
  return 1;

}

void PakModel::beginEditing()
{
  beginResetModel();
}

void PakModel::endEditing()
{
  endResetModel();
}


