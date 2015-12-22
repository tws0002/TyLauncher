﻿#ifndef APPBUTTONFORM_H
#define APPBUTTONFORM_H

#include <QWidget>
#include <QVector>

class AppButton;
class AppInfo;

QT_BEGIN_NAMESPACE
class QJsonArray;
class QMenu;
QT_END_NAMESPACE

namespace Ui {
class AppButtonForm;
}

class AppButtonForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AppButtonForm(const int &rowCount, const int &columnCount, QWidget *parent = 0);
    ~AppButtonForm();
    
    bool configFromVector(QVector<AppInfo> dataVector);
    QJsonArray jsonArray() const;
    /**
     * @brief clear all app button data
     * @note  hotkey will not clear.
     */
    void clearAllAppBtnData();
private slots:
    void onAppButtonRightClicked(QPoint);
    void on_actionOpenFolder_triggered();
    void on_actionDelete_triggered();
    void on_actionCopy_triggered();
    void on_actionShear_triggered();
    void on_actionPaste_triggered();
    void on_actionEdit_triggered();
private:
    Ui::AppButtonForm *ui;
    int _rowCount;
    int _columnCount;
    /**
     * @brief 按钮右键菜单缓存
     * 用来保存右键菜单的按钮地址
     */
    AppButton *_btnCurMenu;
    /// @brief 按钮右键菜单
    QMenu *_btnMenu;
    
    void initBtnRightMenu();
};

#endif // APPBUTTONFORM_H
