/*
 * Copyright 2011 Heidi Martinez Kempff-Andersen
 *
 * This file is part of jennicDaemon.
 *
 * jennicDaemon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * jennicDaemon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with jennicDaemon. If not, see http://www.gnu.org/licenses/.
 */

#include "databaseexplorer.h"
#include "ui_databaseexplorer.h"

DatabaseExplorer::DatabaseExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseExplorer)
{
    ui->setupUi(this);
}

DatabaseExplorer::~DatabaseExplorer()
{
    delete ui;
}

void DatabaseExplorer::on_pushButton_update_clicked()
{

}

void DatabaseExplorer::on_listView_tables_doubleClicked(QModelIndex index)
{

}
