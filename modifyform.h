#ifndef MODIFYFORM_H
#define MODIFYFORM_H

#include "mainwindow.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MyTableWidget;

class ModifyForm : public QDialog
{
    Q_OBJECT
public:
    ModifyForm(MyTableWidget *parent);

signals:
    void sendLineText(const QString& values);
public slots:
    void onClickEnsureButton() {
        emit sendLineText(this->lineEdit->text());
    }

private:
    QLineEdit* lineEdit;
    QPushButton* cancelBtn;
    QPushButton* ensureBtn;
    MyTableWidget* m_parent; // 直接依赖
};

#endif // MODIFYFORM_H
