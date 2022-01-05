#include "modifyform.h"

ModifyForm::ModifyForm(MyTableWidget *parent)
{
    this->m_parent = parent;
    this->setWindowTitle("修改");
    this->resize(300, 100);
    this->lineEdit = new QLineEdit(this);
    lineEdit->move(70 ,15);
    lineEdit->resize(160, 33);
    QPushButton* cancelBtn = new QPushButton(this);
    cancelBtn->move(185, 60);
    cancelBtn->setText("取消");
    QPushButton* ensureBtn = new QPushButton(this);
    ensureBtn->move(135, 60);
    ensureBtn->setText("确认");

    connect(ensureBtn, QPushButton::clicked, this, onClickEnsureButton);
    connect(ensureBtn, QPushButton::clicked, this, close);
    QObject::connect(this, ModifyForm::sendLineText, this->m_parent, MyTableWidget::updateSlot);
    connect(cancelBtn, QPushButton::clicked, this, close);
}
