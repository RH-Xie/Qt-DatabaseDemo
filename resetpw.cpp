#include "resetpw.h"

ResetPW::ResetPW(MyTableWidget *parent)
{
    this->m_parent = parent;
    this->setWindowTitle("修改密码");
    this->resize(300, 150);

    QLabel* _1 = new QLabel(this);
    _1->setText("原密码");
    _1->move(60, 15);

    this->_BEAGLE = new QLineEdit(this);
    this->_BEAGLE->setPlaceholderText("输入原有密码...");
    this->_BEAGLE->setEchoMode(QLineEdit::Password);
    _BEAGLE->move(60 ,35);

    QLabel* _2 = new QLabel(this);
    _2->setText("新密码");
    _2->move(60, 65);

    this->KROOS_W = new QLineEdit(this);
    this->KROOS_W->setEchoMode(QLineEdit::Password);
    this->KROOS_W->setPlaceholderText("输入新密码...");
    KROOS_W->move(60 ,83);

    QPushButton* cancelBtn = new QPushButton(this);
    cancelBtn->move(180, 120);
    cancelBtn->setText("取消");

    QPushButton* ensureBtn = new QPushButton(this);
    ensureBtn->move(130, 120);
    ensureBtn->setText("确认");

    connect(ensureBtn, QPushButton::clicked, this, onClickEnsureButton);
    connect(ensureBtn, QPushButton::clicked, this, close);
    QObject::connect(this, ResetPW::sendModifySignal, this->m_parent, MyTableWidget::resetPW);
    connect(cancelBtn, QPushButton::clicked, this, close);
}
