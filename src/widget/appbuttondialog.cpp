﻿/**
 * Copyright (c) 2016, luckytianyiyan <luckytianyiyan@gmail.com>
 * 
 * This file is part of TyLauncher.
 * 
 * TyLauncher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TyLauncher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TyLauncher.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "appbuttondialog.h"
#include "ui_appbuttondialog.h"
#include "widget/appbutton.h"
#include <QFileDialog>
#include <QFileIconProvider>
AppButtonDialog::AppButtonDialog(QWidget *parent, AppButton *btn) :
    QDialog(parent),
    ui(new Ui::AppButtonDialog),
    _btn(nullptr)
{
    ui->setupUi(this);
    ui->pushButtonIcon->setIconSize(QSize(48, 48));
    if(btn == nullptr)
        return;
    _btn = btn;
    const QPixmap *pixmap = _btn->getPixmap();
    if(pixmap != nullptr)
    {
        QIcon icon(*pixmap);
        ui->pushButtonIcon->setIcon(icon);
    }
    ui->lineEditName->setText(_btn->getAppName());
    ui->lineEditTarget->setText(_btn->getFileName());
}

AppButtonDialog::~AppButtonDialog()
{
    delete ui;
}

void AppButtonDialog::on_pushButtonFile_clicked()
{
    QFileDialog fileDialog(this, tr("Browse File"), ".");
    QString fileName = "";
    if(fileDialog.exec() == QDialog::Accepted)
    {
        fileName = fileDialog.selectedFiles()[0];
        ui->lineEditTarget->setText(fileName);
        QFileInfo fileInfo(fileName);
        QFileIconProvider iconProvider;
        ui->pushButtonIcon->setIcon(iconProvider.icon(fileInfo));// 自动设置应用图标
        ui->lineEditName->setText(fileInfo.baseName());// 自动设置应用名
    }
}

void AppButtonDialog::on_pushButtonDir_clicked()
{
    QFileDialog fileDialog(this, tr("Browse Folder"), ".");
    fileDialog.setFileMode(QFileDialog::DirectoryOnly);
    QString fileName = "";
    if(fileDialog.exec() == QDialog::Accepted)
    {
        fileName = fileDialog.selectedFiles()[0];
        ui->lineEditTarget->setText(fileDialog.selectedFiles()[0]);
        QFileInfo fileInfo(fileName);
        QFileIconProvider iconProvider;
        ui->pushButtonIcon->setIcon(iconProvider.icon(fileInfo));// 自动设置应用图标
        ui->lineEditName->setText(fileInfo.baseName());// 自动设置应用名
    }
}

void AppButtonDialog::on_buttonBox_accepted()
{
    if(_btn != nullptr && !(ui->lineEditName->text().isEmpty() && ui->lineEditTarget->text().isEmpty()))
    {
        _btn->setAppName(ui->lineEditName->text());
        _btn->setAppFileName(ui->lineEditTarget->text());
    }
    this->close();
}

void AppButtonDialog::on_buttonBox_rejected()
{
    this->close();
}
