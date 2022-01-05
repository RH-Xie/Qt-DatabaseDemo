#include "mainwindow.h"
#include "loginform.h"
#include "sql.h"
#include "modifyform.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include <QTreeWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QTabWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("管理界面");
    w.resize(800, 600);
    w.setFixedSize(800, 600);
    QFile file(":/Adaptic.qss");
    if(file.open(QFile::ReadOnly)) {
        QString stylesheet = QLatin1String(file.readAll());
        a.setStyleSheet(stylesheet);
        file.close();
    }
    else {
        QMessageBox::warning(NULL, "warning", "样式文件打开失败", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    // Login
    LoginForm loginForm;
    loginForm.setFixedSize(360, 260);
    QObject::connect(&loginForm, LoginForm::sendIdentifySignal, &w, MainWindow::identifyUser);
    if(loginForm.exec() == QDialog::Accepted) {

        // Window
        /*
        QTreeWidget treeWidget(&w);
        treeWidget.resize(620, 400);
        treeWidget.move(25, 45);
        treeWidget.setHeaderLabel("STUDENT");
        QTreeWidgetItem topItem;
        treeWidget.addTopLevelItem(&topItem);
        */

        /*
        // Student table
        tableWidget.setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "性别" << "年龄");

        QSqlQuery temp = SELECT_ALL("STUDENT");
        int i = 0;
        while(temp.next())
        {
            QString SNO = temp.value(0).toString();
            QString NAME = temp.value(1).toString();
            QString SSEX = temp.value(2).toString();
            QString SAGE = temp.value(3).toString();
            tableWidget.setItem(i, 0, new QTableWidgetItem(SNO));
            tableWidget.setItem(i, 1, new QTableWidgetItem(NAME));
            tableWidget.setItem(i, 2, new QTableWidgetItem(SSEX));
            tableWidget.setItem(i, 3, new QTableWidgetItem(SAGE));
            i++;
        }
        while (temp.previous()) {
        }
        */

        w.show();
        return a.exec();
    }

    else {
        return 0;
    }
}
