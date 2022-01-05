#include "addform.h"

AddForm::AddForm(MyTableWidget *parent, int type)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->m_parent = parent;
    this->setWindowTitle("添加");
    this->resize(300, 150);
    QLabel* tips = new QLabel(this);
    tips->resize(200, 30);
    tips->move(60, 20);
    this->lineEdit = new QLineEdit(this);
    if(type == 0) {
        // TEACHER、STUDENT和COUSE这类单主码的表
        tips->setText("添加主码：");
    }
    else if (type == 1) {
        // 复合主码
        tips->setText("填写复合主码：");
        this->lineEdit->setInputMask("0000 00000");

    }
    this->lineEdit->move(60 ,50);
    this->lineEdit->resize(190, 30);
    QPushButton* cancelBtn = new QPushButton(this);
    cancelBtn->move(160, 90);
    cancelBtn->setText("取消");
    QPushButton* ensureBtn = new QPushButton(this);
    ensureBtn->move(60, 90);
    ensureBtn->setText("确认");

    connect(ensureBtn, QPushButton::clicked, this, onClickEnsureButton);
    connect(ensureBtn, QPushButton::clicked, this, close);
    QObject::connect(this, AddForm::sendLineText, this->m_parent, MyTableWidget::addInfo);
    connect(cancelBtn, QPushButton::clicked, this, close);
}
