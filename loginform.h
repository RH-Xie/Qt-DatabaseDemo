#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "sql.h"

#include "mainwindow.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>

class LoginForm : public QDialog {
    Q_OBJECT
public:
    explicit LoginForm(QDialog * parent = 0);
    QPushButton* loginBtn;
signals:
    void sendIdentifySignal(QString no);
public slots:
    void login();
private:
    void emitI();
    QLabel* welcomLab;
    QLabel* userNameLab;
    QLabel* passwordLab;
    QLineEdit* userNameLE;
    QLineEdit* passwordLE;
    QPushButton* exitBtn;
    QStringList* _m;
    QStringList* _q;
    QSqlQuery _c;
};



#endif // LOGINFORM_H
