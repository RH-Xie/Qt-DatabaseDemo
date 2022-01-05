#include "mainwindow.h"
#include "addform.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // SQL
    sql* DB_Obj = new sql;
    DB_Obj->database.transaction();
    DB_Obj->database.commit();
    /*
     * 连通性测试，起初因传递问题无法提交至数据库，用下面的来测试连通性
    if(DB_Obj->database.transaction()) {
        qDebug() << "SUCCESS";
        DB_Obj->database.commit();
    }
    else {
        qDebug() << "FAIL" << this->DB.lastError();
    }
    */
    this->DB = DB_Obj->database;
    /*
    if(this->DB.transaction()) {
        qDebug() << "SUCCESS";
        this->DB.commit();
    }
    else {
        qDebug() << "FAIL" << this->DB.lastError();
    }
    */

    // Main view

    this->tableWidget = new MyTableWidget(this);
    // this->tableWidget->switchView("STUDENT");

    // Menus
    /*
    QMenuBar* menubar = menuBar();
    QMenu* testMenu = menuBar()->addMenu(tr("菜单(&F)"));

    menubar->addMenu(testMenu);
    */

    // Images
    QPixmap gzhu_pixmap(":/icon/gzhu_op.png");
    QLabel* gzhu_lb = new QLabel(this);
    gzhu_lb->move(640, 40);
    gzhu_lb->resize(120, 120);
    gzhu_lb->setScaledContents(true);
    gzhu_lb->setPixmap(gzhu_pixmap);

    // Items
    viewBox = new QComboBox(this);
    viewBox->move(90, 530);
    viewBox->resize(170, 30);
    QStringList viewList;
    viewList << "<无>" << "STUDENT" << "TEACHER" << "COURSE" << "TC" << "SC" << "PASSWORD";
    viewBox->addItems(viewList);
    QLabel* viewLb = new QLabel(this);
    viewLb->setText("视图：");
    viewLb->move(30, 530);

    connect(viewBox, QComboBox::currentTextChanged, tableWidget, MyTableWidget::switchView);

    modifyBtn = new QPushButton(this);
    modifyBtn->setText("修改");
    modifyBtn->move(500, 530);
    modifyBtn->resize(83, 30);

    recordScoreBtn = new QPushButton(this);
    recordScoreBtn->setText("录入成绩");
    recordScoreBtn->move(400, 530);
    recordScoreBtn->resize(100, 30);
    recordScoreBtn->hide();

    addBtn = new QPushButton(this);
    addBtn->setText("添加");
    addBtn->move(410, 530);
    addBtn->resize(83, 30);

    deleteBtn = new QPushButton(this);
    deleteBtn->setText("删除");
    deleteBtn->move(320, 530);
    deleteBtn->resize(83, 30);

    QLabel* searchLB = new QLabel(this);
    searchLB->move(600, 375);
    searchLB->setText("查询：");
    searchCMB = new QComboBox(this);
    searchCMB->move(650, 375);
    searchCMB->resize(135, 30);
    QStringList searchList;
    searchList << "<无>" << "各职称教师数量" << "各职称平均工资" <<"课程平均成绩" << "课程最高分" << "课程最低分";
    /*
    else if(this->userType == "学生") {
        addBtn->hide();
        QPushButton* selectBtn = new QPushButton(this);
        selectBtn->setText("选择");
        selectBtn->move(410, 530);
        selectBtn->resize(83, 30);
        connect(selectBtn, QPushButton::clicked, this, selectCouse);
    }
    */
    searchCMB->addItems(searchList);
    connect(searchCMB, QComboBox::currentTextChanged, this, MainWindow::showSearchResult);

    userGroupLB = new QLabel(this);
    userGroupLB->move(640, 185);

}

void MainWindow::sighout() {

}

MainWindow::~MainWindow()
{

}

void MainWindow::showSearchResult(const QString& requestName) {
    QSqlQuery temp;
    if(requestName == "<无>") {
        return;
    }
    else if (requestName == "各职称教师数量") {
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // create visual table according to user type
        this->tableWidget->setColumnCount((2));
        this->tableWidget->setColumnWidth(0, 259);
        this->tableWidget->setColumnWidth(1, 260);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "职称" << "数量");

        temp = SELECT("TEACHER", "JOBTITLE, COUNT(*)", "GROUP BY JOBTITLE");
        int i = 0;
        while(temp.next()) {
            this->tableWidget->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
            this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
            i++;
        }
        this->tableWidget->setRowCount(i);
    }
    else if (requestName == "各职称平均工资") {
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // create visual table according to user type
        this->tableWidget->setColumnCount((2));
        this->tableWidget->setColumnWidth(0, 259);
        this->tableWidget->setColumnWidth(1, 260);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "职称" << "平均工资");

        temp = SELECT("TEACHER", "JOBTITLE, AVG(TSALARY)", "GROUP BY JOBTITLE");
        int i = 0;
        while(temp.next()) {
            this->tableWidget->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
            this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
            i++;
        }
        this->tableWidget->setRowCount(i);
    }
    else if (requestName == "课程平均成绩") {
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // create visual table according to user type
        this->tableWidget->setColumnCount((3));
        this->tableWidget->setColumnWidth(0, 160);
        this->tableWidget->setColumnWidth(1, 240);
        this->tableWidget->setColumnWidth(2, 119);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "平均成绩");

        temp = SELECT("SC", "CNO, AVG(SSCORE)", "GROUP BY CNO");
        int i = 0;
        while(temp.next()) {
            this->tableWidget->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL3 = temp.value(1).toString();
            QSqlQuery m_temp = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL1);
            m_temp.next();
            QString COL2 = m_temp.value(0).toString();
            this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
            this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
            this->tableWidget->setItem(i, 2, new QTableWidgetItem(COL3));
            i++;
        }
        this->tableWidget->setRowCount(i);
    }
    else if (requestName == "课程最高分") {
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // create visual table according to user type
        this->tableWidget->setColumnCount((5));
        this->tableWidget->setColumnWidth(0, 60);
        this->tableWidget->setColumnWidth(1, 200);
        this->tableWidget->setColumnWidth(2, 60);
        this->tableWidget->setColumnWidth(3, 130);
        this->tableWidget->setColumnWidth(4, 69);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "最高分" << "获得者" << "学号");

        temp = SELECT("SC", "CNO, MAX(SSCORE),SNO", "GROUP BY CNO");
        int i = 0;
        while(temp.next()) {
            this->tableWidget->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL3 = temp.value(1).toString();
            QString COL5 = temp.value(2).toString();
            QSqlQuery m_temp = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL1);
            m_temp.next();
            QString COL2 = m_temp.value(0).toString();
            m_temp = SELECT("STUDENT", "NAME", "WHERE SNO = " + COL5);
            m_temp.next();
            QString COL4 = m_temp.value(0).toString();
            this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
            this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
            this->tableWidget->setItem(i, 2, new QTableWidgetItem(COL3));
            this->tableWidget->setItem(i, 3, new QTableWidgetItem(COL4));
            this->tableWidget->setItem(i, 4, new QTableWidgetItem(COL5));
            i++;
        }
        this->tableWidget->setRowCount(i);
    }
    else if (requestName == "课程最低分") {
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        // create visual table according to user type
        this->tableWidget->setColumnCount((5));
        this->tableWidget->setColumnWidth(0, 60);
        this->tableWidget->setColumnWidth(1, 200);
        this->tableWidget->setColumnWidth(2, 60);
        this->tableWidget->setColumnWidth(3, 130);
        this->tableWidget->setColumnWidth(4, 69);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "最高分" << "获得者" << "学号");

        temp = SELECT("SC", "CNO, MIN(SSCORE),SNO", "GROUP BY CNO");
        int i = 0;
        while(temp.next()) {
            this->tableWidget->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL3 = temp.value(1).toString();
            QString COL5 = temp.value(2).toString();
            QSqlQuery m_temp = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL1);
            m_temp.next();
            QString COL2 = m_temp.value(0).toString();
            m_temp = SELECT("STUDENT", "NAME", "WHERE SNO = " + COL5);
            m_temp.next();
            QString COL4 = m_temp.value(0).toString();
            this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
            this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
            this->tableWidget->setItem(i, 2, new QTableWidgetItem(COL3));
            this->tableWidget->setItem(i, 3, new QTableWidgetItem(COL4));
            this->tableWidget->setItem(i, 4, new QTableWidgetItem(COL5));
            i++;
        }
        this->tableWidget->setRowCount(i);
    }
    else if (requestName == "学生选修总分") {

    }
    // 学生用
    else if (requestName == "总学分/成绩") {
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->tableWidget->setColumnCount(3);
        this->tableWidget->setColumnWidth(0, 160);
        this->tableWidget->setColumnWidth(1, 240);
        this->tableWidget->setColumnWidth(2, 119);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "课程名" << "学分" << "成绩");

        QSqlQuery score_query = SELECT("SC", "CNO, SSCORE", "WHERE SNO = " + this->no);
        int i = 0;
        while(score_query.next()) {
            this->tableWidget->insertRow(i);
            QString CNO = score_query.value(0).toString();
            QSqlQuery course_query = SELECT("COURSE", "CNAME,CCREDIT", "WHERE CNO = " + CNO);
            course_query.next();
            QString COL1 = course_query.value(0).toString();
            QString COL2 = course_query.value(1).toString();
            QString COL3 = score_query.value(1).toString();
            this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
            this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
            this->tableWidget->setItem(i, 2, new QTableWidgetItem(COL3));
            i++;
        }
        this->tableWidget->insertRow(i);
        QTableWidgetItem* COL1 = new QTableWidgetItem();
        COL1->setBackground(QColor(135,175,255));
        COL1->setText("学业情况");
        COL1->setTextColor(Qt::red);
        COL1->setTextAlignment(Qt::AlignCenter);
        this->tableWidget->setItem(i, 0, COL1);
        double totalCredits = 0;
        for(int j = 0; j < i; j++) {
            totalCredits += this->tableWidget->item(j, 1)->text().toDouble();
        }
        QTableWidgetItem* COL2 = new QTableWidgetItem;
        COL2->setText("总学分：" + QString::number(totalCredits));
        COL2->setTextColor(Qt::red);
        COL2->setBackground(QColor(135,175,255));
        COL2->setTextAlignment(Qt::AlignCenter);
        double avg = 0;

        for(int j = 0; j < i; j++) {
            avg += this->tableWidget->item(j, 2)->text().toDouble() * this->tableWidget->item(j, 1)->text().toDouble();
        }
        avg /= totalCredits;
        QTableWidgetItem* COL3 = new QTableWidgetItem;
        COL3->setBackgroundColor(QColor(135,175,255));
        COL3->setTextAlignment(Qt::AlignCenter);
        if(avg <= 60) {
            COL3->setTextColor(Qt::gray);
            COL3->setText("绩点：无");
        }
        else if(avg <= 75) {
            COL3->setTextColor(Qt::yellow);
            COL3->setText("绩点：" + QString::number((avg - 50) / 10, 'f', 2));
        }
        else if(avg <= 85) {
            COL3->setTextColor(Qt::green);
            COL3->setText("绩点：" + QString::number((avg - 50) / 10, 'f', 2));
        }
        else if(avg <= 100) {
            COL3->setTextColor(Qt::red);
            COL3->setText("绩点：" + QString::number((avg - 50) / 10, 'f', 2));
        }

        this->tableWidget->setItem(i, 1, COL2);
        this->tableWidget->setItem(i, 2, COL3);

        i++;
        this->tableWidget->setRowCount(i);
    }

    else if (requestName == "我的学生") {
        this->enableRecordScore(requestName);
        this->tableWidget->clear();
        this->tableWidget->resize(570, 470);
        this->tableWidget->move(25, 45);
        this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->tableWidget->setColumnCount(4);
        this->tableWidget->setColumnWidth(0, 200);
        this->tableWidget->setColumnWidth(1, 80);
        this->tableWidget->setColumnWidth(2, 120);
        this->tableWidget->setColumnWidth(3, 119);
        this->tableWidget->setHorizontalHeaderLabels(QStringList() << "课程名" << "学号" << "姓名"<< "成绩");
        // 多层子查询，用QSqlQuery装载每一层的查询结果
        QSqlQuery myLessons = SELECT("TC", "CNO", "WHERE TNO = " + this->no);
        int i = 0;
        while (myLessons.next()) {
            QString CNO = myLessons.value(0).toString();
            QSqlQuery course_name_query = SELECT("COURSE", "CNAME", "WHERE CNO = " + CNO);
            course_name_query.next();
            QSqlQuery myStudents = SELECT("SC", "SNO, SSCORE", "WHERE CNO = " + CNO);
            while (myStudents.next()) {
                QString SNO = myStudents.value(0).toString();
                QSqlQuery student_name_query = SELECT("STUDENT", "NAME", "WHERE SNO = " + SNO);
                student_name_query.next();
                this->tableWidget->insertRow(i);
                QString COL1 = course_name_query.value(0).toString();
                QString COL2 = myStudents.value(0).toString();
                QString COL3 = student_name_query.value(0).toString();
                QString COL4 = myStudents.value(1).toString();
                this->tableWidget->setItem(i, 0, new QTableWidgetItem(COL1));
                this->tableWidget->setItem(i, 1, new QTableWidgetItem(COL2));
                this->tableWidget->setItem(i, 2, new QTableWidgetItem(COL3));
                this->tableWidget->setItem(i, 3, new QTableWidgetItem(COL4));
                i++;
            }
        }
        this->tableWidget->setRowCount(i);
    }
}

void MainWindow::identifyUser(QString no) {
    this->no = no;
    QSqlQuery request = SELECT("STUDENT", "SNO", "");
    bool adminFlag = true;
    while (request.next()) {
        if(request.value(0).toString() == no) {
            this->userType = "学生";
            this->userGroupLB->setText("用户：" + this->userType);
            adminFlag = false;
            request = SELECT("STUDENT", "NAME", "WHERE SNO = " + no);
            request.next();
            this->searchLB = request.value(0).toString();
            request = SELECT("PASSWORD", "PASSWORD", "WHERE PNO = " + this->searchLB);
            request.next();
            this->sighoutLB = request.value(0).toString();
            break;
        }
    }
    request = SELECT("TEACHER", "TNO", "");
    while (request.next()) {
        if(adminFlag == false) {
            break;
        }
        if(request.value(0).toString() == no) {
            this->userType = "教师";
            this->userGroupLB->setText("用户：" + this->userType);
            adminFlag = false;
            request = SELECT("TEACHER", "TNAME", "WHERE TNO = " + no);
            request.next();
            this->searchLB = request.value(0).toString();
            request = SELECT("PASSWORD", "PASSWORD", "WHERE PNO = " + this->searchLB);
            request.next();
            this->sighoutLB = request.value(0).toString();
            break;
        }
    }
    if(adminFlag) {
        this->userType = "管理员";
        this->userGroupLB->setText("用户：" + this->userType);
    }
    QLabel* connectionLB = new QLabel(this);
    connectionLB->move(640, 205);
    connectionLB->resize(100, 30);
    connectionLB->setText("状态：已连接");

    QLabel* userIDLB = new QLabel(this);
    userIDLB->move(640, 225);
    userIDLB->resize(140, 30);
    userIDLB->setText("ID: " + this->no);

    this->tableWidget->reset(no, this->userType);
    renewInfo();
}

void MainWindow::renewUI(const QString& value) {
    this->searchCMB->setCurrentIndex(0);
    if(this->userType == "学生") {
        if(value == "可选课程") {
            this->selectBtn->show();
            this->deselectBtn->show();
        }
        else {
            this->selectBtn->hide();
            this->deselectBtn->hide();
            this->recordScoreBtn->hide();
        }
    }
    else {
        this->selectBtn->hide();
        this->deselectBtn->hide();
        this->recordScoreBtn->hide();
        this->modifyBtn->show();
    }
}

void MainWindow::enableRecordScore(const QString& value) {

    if (this->userType == "教师"){
        if(value == "我的学生") {
            this->recordScoreBtn->show();
            this->modifyBtn->hide();
        }
        else {
            this->recordScoreBtn->hide();
            this->modifyBtn->show();
        }
    }
}

void MainWindow::selectCourse() {
    QList<QTableWidgetItem*> list = this->tableWidget->selectedItems();
    if(list.length() > 0) {
        int row = list[0]->row();
        QString CNO_toBeInsert = this->tableWidget->item(row, 0)->text();
        QSqlQuery checkValid = SELECT("SC", "CNO", "WHERE SNO = " + this->no);
        while (checkValid.next()) {
            if(checkValid.value(0).toString() == CNO_toBeInsert) {
                QMessageBox::warning(this, "操作失败","您已拥有该课程！");
                return;
            }
        }
        QString randomScore = QString(rand() % 5 + 53) + QString(rand() % 10 + 48);
        QString pointer[3] = {this->no, CNO_toBeInsert, randomScore};
        if(INSERT("SC", pointer, 3)) {
            qDebug() << "选课成功";
            QMessageBox::information(this, "提示","选课成功");
            this->tableWidget->refresh();
        }
        else {
            QMessageBox::warning(this, "操作失败","请求错误");
        }
    }
}

void MainWindow::deselectCourse() {
    QList<QTableWidgetItem*> list = this->tableWidget->selectedItems();
    if(list.length() > 0) {
        int row = list[0]->row();
        QString CNO_toBeRemoved = this->tableWidget->item(row, 0)->text();
        QSqlQuery checkValid = SELECT("SC", "CNO", "WHERE SNO = " + this->no);
        bool selected = false;
        while (checkValid.next()) {
            if(checkValid.value(0).toString() == CNO_toBeRemoved) {
                selected = true;
            }
        }
        if(selected) {
            this->DB.transaction();
            if(DELETE("SC", "WHERE SNO = " + this->no + " AND CNO = " + CNO_toBeRemoved)) {
                qDebug() << "退课成功";
                this->DB.commit();
                QMessageBox::information(this, "提示","退课成功");
                this->tableWidget->refresh();
            }
            else {
                this->DB.rollback();
                QMessageBox::warning(this, "操作失败","请求错误");
            }
        }
        else {
            QMessageBox::warning(this, "操作失败","您并未选择该课程");
        }
    }
}

void MainWindow::renewInfo() {
    if(this->userType != "管理员") {
        this->deleteBtn->hide();
        this->addBtn->hide();
        this->searchCMB->clear();
        this->viewBox->clear();
        QSqlQuery getInfo;
        QStringList items;
        this->modifyBtn->setText("修改密码");
        this->modifyBtn->resize(100, 30);
        connect(modifyBtn, QPushButton::clicked, new ResetPW(this->tableWidget), ResetPW::exec);

        this->selectBtn = new QPushButton(this);
        this->selectBtn->move(400, 530);
        this->selectBtn->resize(100, 30);
        this->selectBtn->setText("确认选课");
        this->selectBtn->hide();
        connect(selectBtn, QPushButton::clicked, this, MainWindow::selectCourse);

        this->deselectBtn = new QPushButton(this);
        this->deselectBtn->move(300, 530);
        this->deselectBtn->resize(100, 30);
        this->deselectBtn->setText("退选");
        this->deselectBtn->hide();
        connect(deselectBtn, QPushButton::clicked, this, MainWindow::deselectCourse);
        connect(this->viewBox, QComboBox::currentTextChanged, this, MainWindow::renewUI);
        connect(this->searchCMB, QComboBox::currentTextChanged, this, MainWindow::showSearchResult);
        if(this->userType == "学生") {
            items << "<无>" << "我的基本信息" << "我的选课" << "可选课程";
            viewBox->addItems(items);

            QStringList searchList;
            searchList << "<无>" << "总学分/成绩";
            searchCMB->addItems(searchList);

            this->viewBox->setCurrentIndex(1);
        }
        else if (this->userType == "教师") {
            items << "<无>" << "我的基本信息" << "我的授课";
            viewBox->addItems(items);

            QStringList searchList;
            searchList << "<无>" << "我的学生";
            searchCMB->addItems(searchList);

            connect(this->recordScoreBtn, QPushButton::clicked, new ModifyForm(tableWidget), ModifyForm::exec);

            this->viewBox->setCurrentIndex(1);
        }
    }
    else {
        this->viewBox->setCurrentIndex(1);
        connect(modifyBtn, QPushButton::clicked, new ModifyForm(tableWidget), ModifyForm::exec);
        connect(addBtn, QPushButton::clicked, tableWidget, tableWidget->newDialog);
        connect(deleteBtn, QPushButton::clicked, tableWidget, MyTableWidget::deleteInfo);

    }

}

MyTableWidget::MyTableWidget(MainWindow* parent):QTableWidget(parent) {
    this->DB = parent->DB;
    this->m_parent = parent;
}

bool MyTableWidget::switchView(const QString& viewName) {
    if(viewName == "<无>") {
        return true;
    }

    this->tableName = viewName;
    if(viewName == "STUDENT" || viewName == "TEACHER" \
            || viewName == "COURSE" || viewName == "PASSWORD" \
            || viewName == "我的基本信息"){
        // 单主码
        this->type = 0;
    }
    else if (viewName == "TC" || viewName == "SC" || viewName == "我的选课" ||viewName == "我的授课" || viewName == "可选课程") {
        // 复合主码/双主码
        this->type = 1;
    }
    else {
        this->type = -1;
        qDebug() << "表类型错误，请及时更正";
        return false;
    }

    this->clear();
    this->resize(570, 470);
    this->move(25, 45);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // create visual table according to user type
    if (viewName == "TEACHER" || viewName == "STUDENT") {
        this->setColumnCount((4));
        this->setColumnWidth(0, 100);
        this->setColumnWidth(1, 150);
        this->setColumnWidth(2, 100);
        if(viewName == "TEACHER") {
            this->setHorizontalHeaderLabels(QStringList() << "工号" << "姓名" << "职称" << "工资");
        }
        else if (viewName == "STUDENT"){
            this->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "性别" << "年龄");
        }

        QSqlQuery temp = SELECT_ALL(viewName);
        int i = 0;
        while(temp.next())
        {
            this->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            QString COL3 = temp.value(2).toString();
            QString COL4 = temp.value(3).toString();
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            this->setItem(i, 2, new QTableWidgetItem(COL3));
            this->setItem(i, 3, new QTableWidgetItem(COL4));
            i++;
        }
        this->setRowCount(i);
    }
    else if (viewName == "COURSE") {
        this->setColumnCount((3));
        this->setColumnWidth(1, 300);
        this->setColumnWidth(0, 100);
        this->setColumnWidth(2, 100);
        this->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "学分");
        QSqlQuery temp = SELECT_ALL(viewName);
        int i = 0;
        while(temp.next())
        {
            this->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            QString COL3 = temp.value(2).toString();
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            this->setItem(i, 2, new QTableWidgetItem(COL3));
            i++;
        }
        this->setRowCount(i);

    }
    else if (viewName == "TC") {
        this->setColumnCount(3);
        this->setColumnWidth(0, 140);
        this->setColumnWidth(1, 140);
        this->setColumnWidth(2, 170);
        this->setHorizontalHeaderLabels(QStringList() << "教师工号" << "课程号" << "课程名");
        QSqlQuery temp = SELECT_ALL(viewName);
        int i = 0;
        while(temp.next())
        {
            this->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            QSqlQuery reference = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL2);
            reference.next();
            QString COL3 = reference.value(0).toString();
            this->setItem(i, 2, new QTableWidgetItem(COL3));

            i++;
        }
        this->setRowCount(i);
    }
    else if (viewName == "SC") {
        this->setColumnCount(4);
        this->setColumnWidth(0, 100);
        this->setColumnWidth(1, 100);
        this->setColumnWidth(2, 190);
        this->setHorizontalHeaderLabels(QStringList() << "学生号" << "课程号" << "课程名" << "成绩");
        QSqlQuery temp = SELECT_ALL(viewName);
        int i = 0;
        while(temp.next())
        {
            this->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            QString COL4 = temp.value(2).toString();
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            this->setItem(i, 3, new QTableWidgetItem(COL4));
            QSqlQuery reference = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL2);
            reference.next();
            QString COL3 = reference.value(0).toString();
            this->setItem(i, 2, new QTableWidgetItem(COL3));
            i++;
        }
        this->setRowCount(i);
    }
    else if (viewName == "PASSWORD"){
        this->setColumnCount(2);
        this->setColumnWidth(0, 260);
        this->setColumnWidth(1, 260);
        this->setHorizontalHeaderLabels(QStringList() << "账号" << "密码" );
        QSqlQuery temp = SELECT_ALL(viewName);
        int i = 0;
        while(temp.next())
        {
            this->insertRow(i);
            QString COL1 = temp.value(0).toString();
            QString COL2 = temp.value(1).toString();
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            i++;
        }
        this->setRowCount(i);
    }
    else if (viewName == "我的基本信息") {
        this->setColumnCount((4));
        this->setColumnWidth(0, 100);
        this->setColumnWidth(1, 150);
        this->setColumnWidth(2, 100);
        QSqlQuery temp;
        if(this->userType == "教师") {
            this->setHorizontalHeaderLabels(QStringList() << "工号" << "姓名" << "职称" << "工资");
            temp = SELECT("TEACHER", "*", "WHERE TNO = " + this->no);
        }
        else if (this->userType == "学生"){
            this->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "性别" << "年龄");
            temp = SELECT("STUDENT", "*", "WHERE SNO = " + this->no);
        }
        else {
            qDebug() << "错误。特征值：10175";
            return false;
        }
        this->insertRow(0);
        temp.next();
        QString COL1 = temp.value(0).toString();
        QString COL2 = temp.value(1).toString();
        QString COL3 = temp.value(2).toString();
        QString COL4 = temp.value(3).toString();
        this->setItem(0, 0, new QTableWidgetItem(COL1));
        this->setItem(0, 1, new QTableWidgetItem(COL2));
        this->setItem(0, 2, new QTableWidgetItem(COL3));
        this->setItem(0, 3, new QTableWidgetItem(COL4));
        this->setRowCount(1);
    }
    else if (viewName == "我的选课") {
        this->setColumnCount(3);
        this->setColumnWidth(0, 100);
        this->setColumnWidth(1, 150);
        this->setColumnWidth(2, 100);
        this->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "状态");
        QSqlQuery query_no = SELECT("SC", "CNO", "WHERE SNO = " + this->no);
        int i = 0;
        while(query_no.next()) {
            this->insertRow(i);
            QString COL1 = query_no.value(0).toString();
            QSqlQuery query_name = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL1);
            query_name.next();
            QString COL2 = query_name.value(0).toString();
            QString COL3 = "已选上";
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            QTableWidgetItem* _3 = new QTableWidgetItem(COL3);
            _3->setTextColor(QColor(Qt::blue));
            this->setItem(i, 2, _3);
            i++;
        }
        this->setRowCount(i);
    }
    else if (viewName == "我的授课") {
        this->setColumnCount(4);
        this->setColumnWidth(0, 100);
        this->setColumnWidth(1, 229);
        this->setColumnWidth(2, 100);
        this->setColumnWidth(3, 100);
        this->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "状态" << "人数");
        QSqlQuery query_no = SELECT("TC", "CNO", "WHERE TNO = " + this->no);
        int i = 0;
        while(query_no.next()) {
            this->insertRow(i);
            QString COL1 = query_no.value(0).toString();
            QSqlQuery query_name = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL1);
            query_name.next();
            QString COL2 = query_name.value(0).toString();
            QString COL3 = "开选中";
            QSqlQuery query_num = SELECT("SC", "COUNT(*)", "WHERE CNO = " + COL1);
            query_num.next();
            QString COL4 = query_num.value(0).toString() + "/20";
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            QTableWidgetItem* _3 = new QTableWidgetItem(COL3);
            _3->setTextColor(QColor(Qt::blue));
            this->setItem(i, 2, _3);
            this->setItem(i, 3, new QTableWidgetItem(COL4));
            i++;
        }
        this->setRowCount(i);
    }
    else if (viewName == "可选课程") {
        this->setColumnCount(5);
        this->setColumnWidth(0, 80);
        this->setColumnWidth(1, 180);
        this->setColumnWidth(2, 120);
        this->setColumnWidth(3, 80);
        this->setColumnWidth(4, 59);
        this->setHorizontalHeaderLabels(QStringList() << "课程号" << "课程名" << "授课老师" << "职称" << "状态");
        QSqlQuery course_query = SELECT_ALL("TC");
        int i = 0;
        while(course_query.next())
        {
            this->insertRow(i);
            QString teacher_no = course_query.value(0).toString();
            QString COL1 = course_query.value(1).toString();
            this->setItem(i, 0, new QTableWidgetItem(COL1));
            QSqlQuery course_query = SELECT("COURSE", "CNAME", "WHERE CNO = " + COL1);
            course_query.next();
            QString COL2 = course_query.value(0).toString();
            this->setItem(i, 1, new QTableWidgetItem(COL2));
            QSqlQuery teacher_query = SELECT("TEACHER", "TNAME, JOBTITLE", "WHERE TNO = " + teacher_no);
            teacher_query.next();
            QString COL3 = teacher_query.value(0).toString();
            QString COL4 = teacher_query.value(1).toString();
            this->setItem(i, 2, new QTableWidgetItem(COL3));
            this->setItem(i, 3, new QTableWidgetItem(COL4));
            QSqlQuery selected = SELECT("SC", "CNO", "WHERE SNO = " + this->no);
            bool selectedOrNot = false;
            while (selected.next()) {
                if(COL1 == selected.value(0).toString()) {
                    selectedOrNot = true;
                    break;
                }
            }
            if(selectedOrNot) {
                QTableWidgetItem* COL5 = new QTableWidgetItem("已选上");
                COL5->setTextColor(Qt::blue);
                this->setItem(i, 4, COL5);
            }
            else {
                QTableWidgetItem* COL5 = new QTableWidgetItem("未选上");
                COL5->setTextColor(Qt::red);
                this->setItem(i, 4, COL5);
            }
            i++;
        }
        this->setRowCount(i);
    }
    return true;
}

void MyTableWidget::updateSlot(const QString& value) {
    QList<QTableWidgetItem*> list = this->selectedItems();
    if(userType == "教师") {
        if(list.length() < 1) {
            return;
        }
        if(list[0]->column() != 3) {
            qDebug() << "抱歉，您不能修改该信息，请联系管理员进行审核";
            return;
        }
        else {
            int row = list[0]->row();
            QString SNO = this->item(row, 1)->text();
            QString CNAME = "\"" + this->item(row, 0)->text() + "\"";
            QSqlQuery CNO_query = SELECT("COURSE", "CNO", "WHERE CNAME = " + CNAME);
            while(CNO_query.next()) {
                QString CNO = CNO_query.value(0).toString();
                this->DB.transaction();
                if(UPDATE("SC", "SSCORE", value, "WHERE SNO = " + SNO + " AND CNO = " + CNO)) {
                    this->DB.commit();
                    QMessageBox::information(this, "提示","学生" + SNO + "成绩录入成功");
                    this->m_parent->showSearchResult("我的学生");
                    return;
                }
                else {
                    this->DB.rollback();
                    QMessageBox::warning(this, "操作失败","请求错误");
                    return;
                }
            }

        }
        return;
    }
    if(userType != "管理员") {

        qDebug() << "抱歉，您不能修改该信息，请联系管理员进行审核";
        return;
    }

    if(list.length() > 0) {
        int row = list[0]->row();
        int col = list[0]->column();

        // 指定一下那些是字符串，并转化
        QString m_value = value;
        if(this->tableName == "STUDENT" || this->tableName == "TEACHER") {
            if(col == 1 || col == 2) {
                m_value = "\'" + m_value + "\'";
            }
        }
        if (this->tableName == "COURSE") {
            if(col == 1) {
                m_value = "\'" + m_value + "\'";
            }
        }

        // 列名表
        QString columnNameSTUDENT[4] = {"SNO","NAME", "SSEX", "SAGE"};
        QString columnNameTEACHER[4] = {"TNO","TNAME", "JOBTITLE", "TSALARY"};
        QString columnNameCOURSE[3] = {"CNO", "CNAME", "CCREDIT"};
        QString columnNamePASSWORD[2] = {"PNO", "PASSWORD"};
        QString columnNameTC[2] = {"TNO", "CNO"};
        QString columnNameSC[2] = {"SNO", "CNO"};

        // 主码表
        QString primaryKeyTable[4] = {"SNO", "TNO", "CNO", "PNO"};
        QString condition = "WHERE ";
        // 列名
        QString keyWord;
        if(this->tableName == "STUDENT") {
            condition += primaryKeyTable[0] + " = " + this->item(row, 0)->text();
            keyWord = columnNameSTUDENT[col];
        }
        if(this->tableName == "TEACHER") {
            condition += primaryKeyTable[1] + " = " + this->item(row, 0)->text();
            keyWord = columnNameTEACHER[col];
        }
        if(this->tableName == "COURSE") {
            condition += primaryKeyTable[2] + " = " + this->item(row, 0)->text();
            keyWord = columnNameCOURSE[col];
        }
        if(this->tableName == "TC") {
            condition += primaryKeyTable[1] + " = " + this->item(row, 0)->text() + " AND " + primaryKeyTable[2] + " = " + this->item(row, 1)->text();
            keyWord = columnNameTC[col];
        }
        if(this->tableName == "SC") {
            condition += primaryKeyTable[0] + " = " + this->item(row, 0)->text() + " AND " + primaryKeyTable[2] + " = " + this->item(row, 1)->text();
            keyWord = columnNameSC[col];
        }
        if(this->tableName == "PASSWORD") {
            condition += primaryKeyTable[3] + " = " + this->item(row, 0)->text();
            keyWord = columnNamePASSWORD[col];
        }
        this->DB.transaction();
        if(UPDATE(this->tableName, keyWord, m_value, condition)) {
            if(this->DB.commit()) {
                qDebug() << "修改成功并提交";
                this->switchView(this->tableName);
            }
            else {
                qDebug() << "提交失败并回滚";
                this->DB.rollback();
            }

        }
        else {
             qDebug() << "修改失败";
        }
    }
    return;
}

void MyTableWidget::resetPW(const QString& _FANG, const QString& _ALVA) {
    QSqlQuery request = SELECT("PASSWORD", "PASSWORD", "WHERE PNO = " + this->no);
    request.next();
    if(request.value(0).toString() == _FANG) {
        if(_ALVA.length() < 3) {
            QMessageBox::warning(this, "警告","密码长度过短");
        }
        else {
            if(UPDATE("PASSWORD", "PASSWORD", _ALVA, "WHERE PNO = " + this->no)) {
                QMessageBox::information(this, "提示","修改成功");
            }
            else {
                QMessageBox::critical(this, "错误","未知错误：10492");
            }

        }
    }
    else {
        QMessageBox::warning(this, "错误","原密码不正确");
    }
}

void MyTableWidget::addInfo(const QString* value, int length) {
    if(this->tableName == "STUDENT" || this->tableName == "TEACHER") {
        if(length != 1) {
            qDebug() << "长度有误";
            return;
        }
        QString content[4] = {value[0], "NULL", "NULL", "NULL"};
        this->DB.transaction();
        if(INSERT(this->tableName, content, 4)) {
            qDebug() << "插入成功，已提交" ;
            this->DB.commit();
        }
        else {
            this->DB.rollback();
        }
        this->switchView(this->tableName);
    }
    else if (this->tableName == "COURSE") {
        if(length != 1) {
            qDebug() << "长度有误";
            return;
        }
        QString content[3] = {value[0], "NULL", "NULL"};
        this->DB.transaction();
        if(INSERT(this->tableName, content, 3)) {
            qDebug() << "插入成功，已提交" ;
            this->DB.commit();
        }
        else {
            this->DB.rollback();
        }
        this->switchView(this->tableName);
    }
    else if (this->tableName == "TC" || this->tableName == "SC") {
        if(length != 2) {
            qDebug() << "长度有误";
            return;
        }
        QString content[2] = {value[0], value[1]};
        this->DB.transaction();
        if(INSERT(this->tableName, content, 2)) {
            qDebug() << "插入成功已提交" ;
            this->DB.commit();
        }
        else {
            qDebug() << "插入失败已回滚" ;
            this->DB.rollback();
        }
        this->switchView(this->tableName);
    }

    else if (this->tableName == "PASSWORD") {
        if(length != 1) {
            qDebug() << "长度有误";
            return;
        }
        QString content[2] = {value[0], "NULL"};
        this->DB.transaction();
        if(INSERT(this->tableName, content, 2)) {
            qDebug() << "插入成功已提交" ;
            this->DB.commit();
        }
        else {
            qDebug() << "插入失败已回滚" ;
            this->DB.rollback();
        }
        this->switchView(this->tableName);
    }
}

void MyTableWidget::deleteInfo() {
    QList<QTableWidgetItem*> list = this->selectedItems();
    if(list.length() > 0) {
        int row = list[0]->row();
        QString primaryKey = "WHERE ";
        QString primaryKeyTable[3] = {"SNO ", "TNO ", "CNO "};
        QString keyValue = this->item(row, 0)->text();
        if(this->tableName == "STUDENT" ) {
            primaryKey += primaryKeyTable[0] + "= " +  keyValue;
            // 删除以STUDENT为前置的所有相关信息，以解决删除触发器在级联删除上的问题
            this->DB.transaction();
            DELETE("SC", "WHERE SNO = " + keyValue);
            DELETE("PASSWORD", "WHERE PNO = " + keyValue);
            this->DB.commit();
        }
        if(this->tableName == "TEACHER") {
            primaryKey += primaryKeyTable[1] + "=" + keyValue;
            // 同上
            this->DB.transaction();
            DELETE("SC", "WHERE SNO = " + keyValue);
            DELETE("PASSWORD", "WHERE PNO = " + keyValue);
            this->DB.commit();
        }
        if(this->tableName == "COURSE") {
            primaryKey += primaryKeyTable[2] + " =" + keyValue;
        }
        if(this->tableName == "TC") {
            primaryKey += primaryKeyTable[1] + " =" + keyValue + " AND " + primaryKeyTable[2] + " = " + this->item(row, 1)->text();
        }
        if(this->tableName == "SC") {
            primaryKey += primaryKeyTable[0] + " =" + keyValue + " AND " + primaryKeyTable[2] + " = " + this->item(row, 1)->text();
        }
        if(this->tableName == "PASSWORD") {
            qDebug() << "拒绝请求，若需要请联系调试人员";
            return;
        }
        this->DB.transaction();
        if(DELETE(this->tableName, primaryKey)) {
            if(this->DB.commit()) {
                qDebug() << "删除成功并提交";
            }
            else {
                qDebug() << "删除失败，事务回滚";
                this->DB.rollback();
            }
        }
        this->switchView(this->tableName);
    }
}

void MyTableWidget::newDialog() {
    this->addForm = new AddForm(this, this->type);
    this->addForm->exec();
}

void MyTableWidget::reset(QString _a, QString _MINTQ) {
    this->no = _a;
    this->userType = _MINTQ;
}

void MyTableWidget::refresh() {
    switchView(this->tableName);
}
