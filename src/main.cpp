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
#include "widget/mainwindow.h"
#include "application.h"
#include <QTranslator>
#include <QFile>
#include "dynamicdata.h"
#include "utils/apputils.h"
#include "utils/uiutils.h"
#include <QObject>
#include "utils/stringutils.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
#ifndef QT_DEBUG
    // 检查程序是否 已经启动
    if(!AppUtils::isRunTimeOnly()){
        UIUtils::showInfoMsgBox(QObject::tr("%1 is runnig.").arg(a.applicationName()));
        return 0;
    }
#endif
    
    MainWindow w;
    w.show();
    return a.exec();
}
