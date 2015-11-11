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

#ifndef PAKMODEL_H
#define PAKMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QVariant>
#include <QModelIndex>
#include <QtGlobal>
#include <QSharedPointer>
#include "treeitem.h"
#include "pak.h"


class PakModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  explicit PakModel(QObject *parent = 0);
  explicit PakModel(QSharedPointer<Pak> pakfile, QObject *parent = 0);
  ~PakModel() = default;

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  void beginEditing() ;
  void endEditing() ;

private:
  void setupModelData(const QStringList &lines, PakModel *parent);

  TreeItem *rootItem;
  QSharedPointer<Pak> pak;
};


#endif // PAKMODEL_H
