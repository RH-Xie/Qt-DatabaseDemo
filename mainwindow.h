#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "modifyform.h"
#include "sql.h"
#include "addform.h"
#include "resetpw.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <qpushbutton.h>
#include <QPushButton>
#include <QMessageBox>

#include <QPixmap>
#include <QLabel>
#include <QComboBox>
#include <QString>

#include <QTableWidget>
#include <QFont>
#include <QList>

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
class AddForm;
class MyTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void sighout();
    void showSearchResult(const QString& requestName);
    void identifyUser(QString no);
    void selectCourse();
    void deselectCourse();
    void renewUI(const QString& value);
    void enableRecordScore(const QString& value);
private:
    QLabel* userGroupLB;
    QLabel* tableLb;
    QPushButton* closeBtn;
    QPushButton* signoutBtn;
    MyTableWidget* tableWidget;
    QString userType;
    QString no;
    QString searchLB;
    QString sighoutLB;
    QComboBox* viewBox;
    QComboBox* searchCMB;
    QPushButton* modifyBtn;
    QPushButton* recordScoreBtn;
    QPushButton* deleteBtn;
    QPushButton* addBtn;
    QPushButton* selectBtn;
    QPushButton* deselectBtn;

public:
    QSqlDatabase DB;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void renewInfo();
};

class MyTableWidget : public QTableWidget {
    Q_OBJECT
    QString tableName;
    QString no;
    QString userType;
    MainWindow* m_parent;
public slots:
    bool switchView(const QString& viewName);
    void updateSlot(const QString& value);
    void resetPW(const QString& _FANG, const QString& _ALVA);
    void addInfo(const QString* value, int length);
    void deleteInfo();
    void newDialog();

public:
    QSqlDatabase DB;
    int type;
    AddForm* addForm;
    MyTableWidget(MainWindow*parent = 0);
    void reset(QString, QString);
    void refresh();
};


#endif // MAINWINDOW_H
