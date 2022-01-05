#include "sql.h"

sql::sql() {
    // Sql statements for load information
    // 装载数据库信息
    QSqlDatabase database;

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
        qDebug() << "Database exists";
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("Makri_BW");
        database.setPassword("1234");
    }
    this->database = database;
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        this->database = database;
        qDebug() << "Success: Database opened";
        if(database.transaction()) {
            qDebug() << "SUCCESS";
            database.commit();
        }
        else {
            qDebug() << "FAIL" << database.lastError();
        }
        //// These statements are dynamically changed before the project accomplish. ////
        //DELETE("STUDENT", "");
        /*
        QString create_table_student = "CREATE TABLE STUDENT (SNO int primary key, NAME varchar(30), SSEX varchar(10), SAGE int)";
        QSqlQuery sql_query;
        sql_query.prepare(create_table_student);
        if(!sql_query.exec()) {
            qDebug() << "Error: Failed to create table.";
            qDebug() << "Table may already exist.";
        }
        else {
            qDebug() << "Success: Create table STUDENT.";
        }
        QString* pointer = new QString[4];
        QString no[11] = {"2001","2002", "2003", "2004", "2005", "2006","2007", "2008", "2009", "2010", "2011"};
        QString nameList[11] = {"马冬梅","排骨仔", "蕾缪乐", "马卫国","陈晖洁","阿尔乔姆","刘桦蔷", "王洛", "帕秋莉·诺蕾姬", "张三", "安心院安洁莉娜"};
        QString sex[4] = {"女","男", "女", "男"};
        QString age[5] = {"18", "19", "21", "18", "20"};
        for(int i = 0; i < 11; i++) {
            pointer[0] = no[i];
            pointer[1] = "\"" + nameList[i] +"\"";
            pointer[2] = "\"" + sex[i % 4] +"\"";
            pointer[3] = age[i % 5];
            INSERT("STUDENT", pointer, 4);
        }
        */


        /*
        QString query = "CREATE TABLE TEACHER (TNO int primary key, TNAME varchar(30), JOBTITLE varchar(10), TSALARY int)";
        QSqlQuery temp;
        temp.prepare(query);
        if(temp.exec()) {
            qDebug() << "Error: Failed to create table.";
            qDebug() << "Table may already exist.";
        }
        else {
            qDebug() << "Success: Create table TEACHER.";
        }

        QString* pointer = new QString[4];
        QString no[6] = {"1001","1002", "1003", "1004", "1005", "1006"};
        QString nameList[6] = {"田一名","瑞克·阿斯特里", "李田所", "森下下士","奥尔加·依兹卡", "刘华强"};
        QString dept[3] = {"讲师","教授", "副教授"};
        QString salary[6] = {"6500","7000", "6700", "5500", "7100", "6200"};
        for(int i = 0; i < 6; i++) {
            pointer[0] = no[i];
            pointer[1] = "\"" + nameList[i] +"\"";
            pointer[2] = "\"" + dept[i % 3] +"\"";
            pointer[3] = salary[i];
            INSERT("TEACHER", pointer, 4);
        }
        */
        /*
        QString query = "CREATE TABLE COURSE (CNO int primary key, CNAME varchar(30), CCREDIT int)";
        QSqlQuery temp;
        temp.prepare(query);
        if(temp.exec()) {
            qDebug() << "Error: Failed to create table.";
            qDebug() << "Table may already exist.";
        }
        else {
            qDebug() << "Success: Create table COURSE.";
        }

        QString* pointer = new QString[3];
        QString no[13] = {"007","012", "084", "069", "141", "134","072", "073", "095", "122", "186", "099", "014"};
        QString nameList[13] = {"油田开发概论","新型骗术防范", "污道处理与给排水原理", "新兵训练", "体育规范", "瓜果保熟原理", "沼气处理", "油物提纯工艺", "江田岛精神概论", "买瓜原理", "卡其托里泰主义", "现代RickRoll艺术", "战前演讲艺术"};
        QString dept[5] = {"2","3", "1", "3", "4"};
        for(int i = 0; i < 13; i++) {
            pointer[0] = no[i];
            pointer[1] = "\"" + nameList[i] +"\"";
            pointer[2] =  dept[i % 5] ;
            INSERT("COURSE", pointer, 3);
        }
        */
        /*
        QString query = "CREATE TABLE TC (TNO int, CNO int, primary key (TNO, CNO), foreign key(TNO) references TEACHER(TNO), foreign key(CNO) references COURSE(CNO))";
        QSqlQuery temp;
        temp.prepare(query);
        if(temp.exec()) {
            qDebug() << "Error: Failed to create table.";
            qDebug() << "Table may already exist.";
        }
        else {
            qDebug() << "Success: Create table TC.";
        }
        //QString no[13] = {"072", "073", "095", "122", "186", "099", "014"};
        //QString nameList[13] = {"7沼气处理", "8油物提纯工艺", "9江田岛精神概论", "10买瓜原理", "11卡其托里泰主义", "12现代RickRoll艺术", "13战前演讲艺术"};

        //QString no[6] = {"1001","1002", "1003", "1004", "1005", "1006"};
        //QString nameList[6] = {"田一名","瑞克·阿斯特里", "李田所", "森下下士","奥尔加·依兹卡", "刘华强"};
        */
        /*
        DELETE("TC", "");
        QString* _pointer = new QString[2];
        QString _no[13] = {"1001","1002", "1003", "1004", "1005", "1006","1001","1002", "1003", "1004", "1005", "1006", "1005"};
        QString _nameList[13] = {"007","012", "084", "069", "141", "134", "073", "099", "072", "095", "186", "122", "014"};
        for(int i = 0; i < 13; i++) {
            _pointer[0] = _no[i];
            _pointer[1] = _nameList[i];
            INSERT("TC", _pointer, 2);
        }
        */
        /*
        DELETE("SC", "");
        QString query = "CREATE TABLE SC (SNO int, CNO int, primary key (SNO, CNO), foreign key(SNO) references STUDENT(SNO), foreign key(CNO) references COURSE(CNO))";
        QSqlQuery temp;
        temp.prepare(query);
        if(temp.exec()) {
            qDebug() << "Error: Failed to create table.";
            qDebug() << "Table may already exist.";
        }
        else {
            qDebug() << "Success: Create table SC.";
        }
        ALTER("SC", "ADD COLUMN SSCORE int", "");
        QString* pointer = new QString[3];
        QString courseList[13] = {"007","012", "084", "069", "141", "134", "073", "099", "072", "095", "186", "122", "014"};
        QString studentNo[11] = {"2001","2002", "2003", "2004", "2005", "2006","2007", "2008", "2009", "2010", "2011"};
        for(int i = 0; i < 11; i++) {
            for(int j = 0; j < 13; j++) {
                pointer[1] = courseList[j];
                pointer[0] = studentNo[i];
                pointer[2] = QString(rand() % 5 + 53) + QString(rand() % 10 + 48);
                INSERT("SC", pointer, 3);
                j += rand() % 3;
            }
        }
        */
        // 删除插入触发器
        QSqlQuery delete_trigger;
        if(!delete_trigger.exec("DROP TRIGGER DEFAULT_PASSWORD_STUDENT")) {
            qDebug() << "Error: Failed to DROP trigger.";
        }
        else {
            qDebug() << "Success: DROP trigger.";
        }
        if(!delete_trigger.exec("DROP TRIGGER DEFAULT_PASSWORD_TEACHER")) {
            qDebug() << "Error: Failed to DROP trigger.";
        }
        else {
            qDebug() << "Success: DROP trigger.";
        }
        if(!delete_trigger.exec("DROP TRIGGER PASSWORD_STUDENT_DELETE")) {
            qDebug() << "Error: Failed to DROP trigger.";
        }
        else {
            qDebug() << "Success: DROP trigger.";
        }
        if(!delete_trigger.exec("DROP TRIGGER PASSWORD_TEACHER_DELETE")) {
            qDebug() << "Error: Failed to DROP trigger.";
        }
        else {
            qDebug() << "Success: DROP trigger.";
        }


        QString query = "CREATE TABLE PASSWORD (PNO int primary key, PASSWORD VARCHAR(50))";
        QSqlQuery temp;
        temp.prepare(query);
        if(temp.exec()) {
            qDebug() << "Error: Failed to create table.";
            qDebug() << "Table may already exist.";
        }
        else {
            qDebug() << "Success: Create table PASSWORD.";
        }


        // 插入触发器
        // 学生默认密码1234
        if(temp.exec("CREATE TRIGGER DEFAULT_PASSWORD_STUDENT AFTER INSERT ON STUDENT FOR EACH ROW BEGIN INSERT INTO PASSWORD VALUES(SNO, \"1234\"); COMMIT; END")) {
            qDebug() << "Error: Failed to create trigger." << temp.lastError();
        }
        else {
            qDebug() << "Success: Create trigger.";
        }
        // 教师默认密码123456
        if(temp.exec("CREATE TRIGGER DEFAULT_PASSWORD_TEACHER AFTER INSERT ON TEACHER FOR EACH ROW BEGIN INSERT INTO PASSWORD VALUES(TNO, \"123456\"); COMMIT; END")) {
            qDebug() << "Error: Failed to create trigger." << temp.lastError();
        }
        else {
            qDebug() << "Success: Create trigger.";
        }

        // 删除触发器
        if(temp.exec("CREATE TRIGGER PASSWORD_STUDENT_DELETE BEFORE DELETE ON STUDENT FOR EACH ROW BEGIN DELETE FROM PASSWORD WHERE PNO = STUDENT.SNO; DELETE FROM SC WHERE SC.SNO = STUDENT.SNO; COMMIT; END")) {
            qDebug() << "Error: Failed to create delete trigger." << temp.lastError();
        }
        else {
            qDebug() << "Success: Create delete trigger.";
        }
        if(temp.exec("CREATE TRIGGER PASSWORD_TEACHER_DELETE BEFORE DELETE ON TEACHER FOR EACH ROW BEGIN DELETE FROM PASSWORD WHERE PNO = TEACHER.TNO;DELETE FROM TC WHERE TC.TNO = TEACHER.TNO; COMMIT; END")) {
            qDebug() << "Error: Failed to create delete trigger." << temp.lastError();
        }
        else {
            qDebug() << "Success: Create delete trigger.";
        }

        // 为管理员和设置触发器前已添加入表的师生设置密码
        //DELETE("PASSWORD", "");
        QString* _pointer = new QString[2];
        temp = SELECT("STUDENT", "SNO", "");
        while(temp.next()) {
            _pointer[0] = temp.value(0).toString();
            _pointer[1] = "\"1234\"";
            INSERT("PASSWORD", _pointer, 2);
        }
        _pointer = new QString[2];
        temp = SELECT("TEACHER", "TNO", "");
        while(temp.next()) {
            _pointer[0] = temp.value(0).toString();
            _pointer[1] = "\"123456\"";
            INSERT("PASSWORD", _pointer, 2);
        }
        _pointer[0] = "2006200029";
        _pointer[1] = "\"12345678\"";
        INSERT("PASSWORD", _pointer, 2);
    }
}
void sql::initialize()
{

}

// 标准：返回QSqkQuery在执行后的位置
bool INSERT(QString table, QString* pointer, int length) {     // 插入信息
    QSqlQuery temp_query;
    QString cmd;
    cmd += "INSERT INTO " + table + " VALUES(";
    for(int i = 0; i < length; i++) {
        if(i != length - 1) {
            cmd += *(pointer + i) + ", ";
        }
        else {
            cmd += *(pointer + i);
        }
    }
    cmd+= ")";
    temp_query.prepare(cmd);
    if(!temp_query.exec()) {
        qDebug() << "ERROR: Insert failed, " << temp_query.lastError();
        return false;
    }
    else {
        qDebug() << "Successfully inserted";
        return true;
    }
}

QSqlQuery SELECT_ALL(QString table) {       // 查询全表
    QSqlQuery temp_query;
    QString cmd;
    cmd += "SELECT * FROM " + table;
    temp_query.prepare(cmd);
    if(!temp_query.exec()) {
        qDebug() << "ERROR: Select failed, " << temp_query.lastError();
    }
    else {
        qDebug() << "Successfully select all";
    }
    return temp_query;
}

QSqlQuery SELECT(QString table, QString items, QString conditions) {        // 按条件查询
    QSqlQuery temp_query;
    QString cmd;
    cmd += "SELECT " + items + " FROM " + table + " " + conditions;
    temp_query.prepare(cmd);
    if(!temp_query.exec()) {
        qDebug() << "ERROR: Select failed, " << temp_query.lastError();
    }
    else {
        qDebug() << "Successfully select with conditions";
    }
    return temp_query;
}

bool UPDATE(QString table, QString columnName, QString value, QString conditions = "") {        // 修改一个值
    QSqlQuery temp_query;
    QString cmd;
    cmd += "UPDATE " + table + " SET " + columnName + " = " + value + " " + conditions + ";";
    //temp_query.exec("BEGIN TRANSACTION");
    temp_query.prepare(cmd);
    if(!temp_query.exec()) {
        qDebug() << "ERROR: Update failed, " << temp_query.lastError();
        /*
        if(temp_query.exec("ROLLBACK")) {
            qDebug() << "CHANGE ROLLBACK";
        }
        else {
            qDebug() << "FAILED TO ROLLBACK" << temp_query.lastError();
        }
        */
        return false;
    }
    else {
        qDebug() << "Successfully update";
        /*
        if(temp_query.exec("COMMIT")) {
            qDebug() << "CHANGE COMMITTED";
        }
        else {
            qDebug() << "FAILED TO COMMIT" << temp_query.lastError();
        }
        */
        return true;
    }
}

bool DELETE(QString table, QString conditions = "") {       // 删除信息
    QSqlQuery temp_query;
    QString cmd;
    cmd += "DELETE FROM " + table + " " + conditions;
    temp_query.prepare(cmd);
    if(!temp_query.exec()) {
        qDebug() << "ERROR: Delete failed, " << temp_query.lastError();
        return false;
    }
    else {
        qDebug() << "Successfully delete";
        return true;
    }
}

bool ALTER(QString table, QString operation, QString conditions) {       // 删除信息
    QSqlQuery temp_query;
    QString cmd;
    cmd += "ALTER TABLE " + table + " " + operation + " " + conditions;
    temp_query.prepare(cmd);
    if(!temp_query.exec()) {
        qDebug() << "ERROR: ALTER failed, " << temp_query.lastError();
        return false;
    }
    else {
        qDebug() << "Successfully ALTER";
        return true;
    }
}

