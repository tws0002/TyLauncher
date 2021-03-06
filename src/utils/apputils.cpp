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
#include "apputils.h"
#include "TyLog_Qt.h"
#include <QCryptographicHash>
#include <QSysInfo>

static const QString kMacAddressNULL = "00:00:00:00:00:00:00:E0";
static const QString kDiskDriveSerialNumberNULL = "000000000000";

#ifdef Q_OS_WIN32
#include <QDir>
#include <QFileInfoList>
#include <QNetworkInterface>
#include <QProcess>
#include <windows.h>
#elif (defined(Q_OS_LINUX) || defined(Q_OS_MAC))
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

bool AppUtils::isRunTimeOnly()
{
#ifdef Q_OS_WIN32
    // 创建互斥量
    HANDLE m_hMutex = CreateMutex(NULL, FALSE,  L"TyLauncher" );
    // 检查错误代码
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        // 如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);
        m_hMutex  =  NULL;
        return false;
    }
#elif (defined(Q_OS_LINUX) || defined(Q_OS_MAC))
    const char filename[]  = "/tmp/tylauncher_lockfile";
    int fd = open(filename, O_WRONLY | O_CREAT , 0644);
    // 使用文件区域做进程锁
    int flock = lockf(fd, F_TLOCK, 0 );
    if (fd == -1) {
        TyLogCritical("open lockfile error/n");
        return false;
    }
    // 给文件加锁
    if (flock == -1) {
        TyLogCritical("lock file error/n");
        return false;
    }
#endif
    return true;
}

QStringList AppUtils::fileNameList(const QString &dirPath, const QStringList &filter)
{
    QStringList strList;
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList(filter);
    for (QFileInfo info : fileInfoList){
        strList.append(info.baseName());
    }
    return strList;
}

QString AppUtils::macAddress()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface netInterface, list) {
        QString hardwareAddress = netInterface.hardwareAddress();
        if (!hardwareAddress.isEmpty() && hardwareAddress != kMacAddressNULL){
            return hardwareAddress;
        }
    }
    return kMacAddressNULL;
}

QString AppUtils::diskdriveSerialNumber()
{
    QProcess proc;
//  QStringList args;
//  args << "-c" << "ioreg -rd1 -c IOPlatformExpertDevice |  awk '/IOPlatformSerialNumber/ { print $3; }'";
//  proc.start( "/bin/bash", args );
//  若是想获取硬件ID可把上面的 IOPlatformSerialNumber 改为 IOPlatformUUID 即可
#if defined(Q_OS_WIN32)
    proc.start("wmic diskdrive get SerialNumber");
    proc.waitForFinished();
    QString info = proc.readAll().simplified();
    QStringList list = info.simplified().split(" ");
    return list.count() < 2 ? kDiskDriveSerialNumberNULL :list[1];
#endif
}

QString AppUtils::driveUniqueID()
{
    QString data = AppUtils::diskdriveSerialNumber() + AppUtils::macAddress();
    QByteArray hash = QCryptographicHash::hash ( data.toUtf8(), QCryptographicHash::Md5 );  
    QString md5 = hash.toHex();

    return md5;
}

QString AppUtils::currentSystem()
{
    return QSysInfo::kernelType();
}

QString AppUtils::currentSystemVersion()
{
    return QSysInfo::kernelVersion();
}
