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
#include "tabwidget.h"
#include "ui_tabwidget.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGridLayout>
#include <QTabBar>
#include <QResizeEvent>
#include <QKeyEvent>
#include "widget/appbutton.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
#include "widget/appbuttondialog.h"
#include "dynamicdata.h"
#include "widget/appbuttonform.h"
#include "widget/tabbar.h"
#include "shearplate.h"

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
    , _rowCount(DEFAULT_TAB_ROW_COUNT)
    , _columnCount(DEFAULT_TAB_COLUMN_COUNT)
{
    ui->setupUi(this);
    TabBar *tabBar = new TabBar(this);
    this->setTabBar(tabBar);
    this->tabBar()->setDocumentMode(true);
    initTabs();
}

TabWidget::~TabWidget()
{
    delete ui;
}

QString TabWidget::jsonString() const
{
    QJsonDocument doc;
    QJsonArray tabArr;
    // 遍历所有tab
    for(int i = 0; i < this->count(); ++i){
        AppButtonForm* tab = dynamic_cast<AppButtonForm*>(this->widget(i));
        tabArr.append(tab->jsonArray());
    }
    doc.setArray(tabArr);
    return doc.toJson();
}

bool TabWidget::configFromVector(QVector<QVector<AppBtnInfo> > dataVector)
{
    Q_ASSERT(dataVector.size() == DEFAULT_TAB_COUNT); 
    try{
        // 每一个Tab
        for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
            AppButtonForm *tab = dynamic_cast<AppButtonForm*>(this->widget(i));
            tab->configFromVector(dataVector[i]);
        }
    }catch(QString e){
        return false;
    }
    return true;
}

void TabWidget::clearAllAppBtnData()
{
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
        AppButtonForm *tab = dynamic_cast<AppButtonForm*>(this->widget(i));
        tab->clearAllAppBtnData();
    }
}

void TabWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{
    Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
    if(!(modifiers & Qt::ControlModifier)) {
        return;
    }
    
    QList<AppButton *> appButtonList = this->currentWidget()->findChildren<AppButton *>();
    switch(keyEvent->key())
    {
    case Qt::Key_C:
        for(AppButton* btn : appButtonList){ // 遍历所有AppButton，寻找当前鼠标指向的按钮
            if(btn->isBeMousePointing()){
                SHEAR_PLATE->copy(btn);
            }
        }
        break;
    case Qt::Key_X:
        for(AppButton* btn : appButtonList){ // 遍历所有AppButton，寻找当前鼠标指向的按钮
            if(btn->isBeMousePointing()){
                SHEAR_PLATE->shear(btn);
            }
        }
        break;
    case Qt::Key_V:
        for(AppButton* btn : appButtonList){ // 遍历所有AppButton
            if(btn->isBeMousePointing()){// 找到被鼠标指向的AppButton
                SHEAR_PLATE->paste(btn);
            }
        }
        break;
    case Qt::Key_Z:
        if (modifiers & Qt::ShiftModifier) {
            SHEAR_PLATE->redo();
        } else {
            SHEAR_PLATE->undo();
        }
        break;
    default:
        break;
    }
}

void TabWidget::initTabs()
{
    for(int i = 0; i < DEFAULT_TAB_COUNT; ++i){
        this->addTab(new AppButtonForm(_rowCount, _columnCount, this), QString::number((i + 1)%10));
    }
}


