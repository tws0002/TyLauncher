﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
QT_BEGIN_NAMESPACE
class QTranslator;
class QCloseEvent;
class QMenu;
QT_END_NAMESPACE

class AppButton;
class AboutDialog;
class AppConfigDialog;
class QxtGlobalShortcut;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    /// @brief 还原窗口
    virtual void restoreWindow();
    ~MainWindow();
private slots:
    /// @brief 托盘图标点击
    void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
    /**
     * @brief 退出菜单项响应
     * 这里包括 托盘菜单 以及 菜单栏中文件菜单的退出菜单项
     */
    void on_Quit_triggered();
    void on_hotKey_triggered();
    /// @brief 托盘菜单的显示主界面菜单项响应
    void on_actionShowWindow_triggered();
    /// @brief "关于"菜单项被点击
    void on_actionAbout_triggered();
    /// @brief "保存"菜单项响应
    void on_actionSave_triggered();
    /// @brief "另保存"菜单项响应
    void on_actionSave_As_triggered();
    /// @brief "检查更新"菜单项响应
    void on_actionCheck_Update_triggered();
    
    void on_actionSettings_triggered();
    
    void onAppConfigChanged(const QString &name);
    
    void checkUpdateFinished();
private:
    Ui::MainWindow *ui;
    /// @brief 托盘图标
    QSystemTrayIcon *_trayIcon;
    /// @brief 托盘菜单
    QMenu *_trayMenu;
    /// @brief 翻译
    QTranslator* _translator;
    
    /// @brief 读取存档文件
    bool loadSaveFile(const QString fileName);
    /// @brief 重置数据
    void reset();

    /// @brief 更新语言
    void updateLanguage();
protected:
    QxtGlobalShortcut* _globalShortcut;
    
    /// @brief 是否需要显示更新对话框
    bool _needShowUpdateDialog;

    /// @brief 初始化托盘
    void initTray();
    
    void initMenu();
    
    void initGlobalShortcut();

    /// @brief 检查更新
    void checkUpdate();
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
