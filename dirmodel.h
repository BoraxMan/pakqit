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

#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include "pak.h"
#include "directoryentry.h"
#include "treeitem.h"
#include "func.h"

class DirModel : public QAbstractItemModel
{
    Q_OBJECT

public:
  explicit DirModel(QObject *parent = 0);
  ~DirModel() = default;

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  void beginEditing();
  void endEditing();


  TreeItem *getTreeItem() const;
  void setTreeItem(TreeItem *value);

  Pak *getPak() const;
  void setPak(Pak *value);

private:
  Pak *pak;
  TreeItem *treeItem;
};

#endif // DIRMODEL_H
