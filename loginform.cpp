#include "loginform.h"
#include <QMessageBox>

LoginForm::LoginForm(QDialog *parent): QDialog(parent) {
    this->setWindowTitle(tr("登录界面"));

    welcomLab = new QLabel(this);
    welcomLab->move(65, 25);
    welcomLab->setText("欢迎，");
    welcomLab->setFont(QFont("KaiTi_GB2312", 20));

    userNameLab = new QLabel(this);
    userNameLab->move(80, 85);
    userNameLab->setText("ID:");

    userNameLE = new QLineEdit(this);
    userNameLE->move(120, 80);
    userNameLE->setPlaceholderText("用户ID...");

    passwordLab = new QLabel(this);
    passwordLab->move(68, 135);
    passwordLab->setText("密码:");

    passwordLE = new QLineEdit(this);
    passwordLE->move(120, 130);
    passwordLE->setPlaceholderText("密码...");
    passwordLE->setEchoMode(QLineEdit::Password);

    loginBtn = new QPushButton(this);
    loginBtn->move(100, 200);
    loginBtn->resize(90, 35);
    loginBtn->setText("登录");

    exitBtn = new QPushButton(this);
    exitBtn->move(200, 200);
    exitBtn->resize(90, 35);
    exitBtn->setText("关闭");

    connect(loginBtn, &QPushButton::clicked, this, login);
    connect(exitBtn, &QPushButton::clicked, this, close);

    _m = new QStringList;
    _q = new QStringList;
    _c = SELECT("PASSWORD", "PNO, PASSWORD", "");
    while (_c.next()) {
        QString windowSize = _c.value(0).toString();
        QString closeBtn = _c.value(1).toString();
        _m->append(windowSize);
        _q->append(closeBtn);
    }
}

void LoginForm::login() {
    // 以后这里后面要写一个用户类，给予确定权限，也允许管理员创建用户
    QSqlQuery _A = SELECT("PASSWORD", "PASSWORD", "WHERE PNO = " + this->userNameLE->text().trimmed());
    _A.next();
    if(_A.value(0).toString() == this->passwordLE->text()) {
        emit sendIdentifySignal(userNameLE->text());
        accept();
    }
    else {
        QMessageBox::warning(this, tr("WARNING"), tr("Invalid username or password"),QMessageBox::Yes);
        userNameLE->setFocus();
    }
}
