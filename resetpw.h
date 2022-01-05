#ifndef RESETPW_H
#define RESETPW_H

#include "mainwindow.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ResetPW : public QDialog
{
    Q_OBJECT
public:
    ResetPW(MyTableWidget * parent = 0);
    QPushButton* ensureBtn;
signals:
    void sendModifySignal(const QString& _TACHAN2KA, const QString& _MELAN_THA);
public slots:
    void onClickEnsureButton() {
        emit sendModifySignal(this->_BEAGLE->text(), this->KROOS_W->text());
    }

private:
    QLineEdit* _BEAGLE;
    QLineEdit* KROOS_W;
    MyTableWidget* m_parent;
};

#endif // RESETPW_H
