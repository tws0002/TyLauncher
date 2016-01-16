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
#ifndef APP_BTN_INFO_H
#define APP_BTN_INFO_H
#include <QString>
#include "model/appinfo.h"
/**
 * @brief Application Button Information Model
 */
class AppBtnInfo : public AppInfo
{
public:
    AppBtnInfo();
    
    AppBtnInfo(const QString &name, const QString &fileName = QString(), const QString &hotKey = QString());
    
    QString hotKey() const;
    void setHotKey(const QString &hotKey);
    
private:
    QString _hotKey;
};

#endif // APPINFO_H
