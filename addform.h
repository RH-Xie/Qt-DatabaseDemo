#ifndef ADDFORM_H
#define ADDFORM_H

#include "mainwindow.h"

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QCoreApplication>

class MyTableWidget;

class AddForm : public QDialog
{
    Q_OBJECT
public:
    explicit AddForm(MyTableWidget *parent = nullptr, int type = -1);
    MyTableWidget* m_parent;
    QLineEdit* lineEdit;
    QPushButton* cancelBtn;
    QPushButton* ensureBtn;

signals:
    void sendLineText(const QString* value, int length);
public slots:
    void onClickEnsureButton() {
        QStringList list = this->lineEdit->text().split(" ");
        QString value[list.length()];
        for(int i = 0; i < list.length(); i++) {
            value[i] = list[i];
        }
        emit sendLineText(value, list.length());
    }
};

#endif // ADDFORM_H
