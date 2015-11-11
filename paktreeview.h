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

#ifndef PAKTREEVIEW_H
#define PAKTREEVIEW_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QTreeView>
#include <QMouseEvent>
#include <QModelIndex>

class pakTreeView : public QTreeView
{
public:
  pakTreeView(QWidget *parent) : QTreeView(parent) {}
private:
  virtual void mousePressEvent(QMouseEvent *event);

};

#endif // PAKTREEVIEW_H
