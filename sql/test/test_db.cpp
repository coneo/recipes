#include "db.h"
#include <iostream>
#include <sstream>

using namespace water::componet;
using namespace std;

static DB db;
class stUser
{
public:
    void print()
    {
        cout << "ID:" << id << " AGE:" << age << " NAME:" << string(name) << " CITY:" << city << endl;
    }

    void set(uint32_t id_, uint32_t age_, string name_, string city_)
    {
        id = id_;
        age = age_;
        name = name_;
        city = city_;
    }

public:
    uint32_t id = 0;
    uint32_t age = 0;
    std::string name = "";
    std::string city = "";
};

void testOld()
{
    /*****old style *******
    TableInfo* table = db.getTable("USER");
    if (table)
    {
        if (db.doDelete(table) == 0)
            fprintf(stdout, "delete table USER success\n");
    }*/
}

void testDelete()
{
    Connection* con = db.getConnection();
    SqlCommand* cmd = new SqlCommand("DELETE FROM USER", con);
    cmd->executeNoQuery();
    delete cmd;
}

void testInsert()
{
    stringstream ss;
    ss << "INSERT INTO USER(AGE,NAME,CITY) VALUES (";
    ss << "'24'" <<","<< "'lazy'"<< "," << "'fuling'";
    ss << ")";
    Connection* con = db.getConnection();
    SqlCommand* cmd = new SqlCommand(ss.str(), con);
    cmd->executeNoQuery();
    cout << "affected rows: " << cmd->getAffectedRows() << endl;
    delete cmd;
}

void testUpdate()
{
    stringstream ss;
    ss << "UPDATE USER SET NAME='lazyqiang' WHERE ID=1;";
    Connection* con = db.getConnection();
    SqlCommand* cmd = new SqlCommand(ss.str(), con);
    cmd->executeNoQuery();
    cout << "affected rows: " << cmd->getAffectedRows() << endl;
    delete cmd;
}

void testSelect()
{
    Connection* con = db.getConnection();
    SqlCommand* cmd = new SqlCommand("SELECT * FROM USER", con);
    DataReader reader = cmd->executeReader();
    stUser user;
    while (reader.read())
    {
        reader.get("ID", user.id);
        reader.get("AGE", user.age);
        reader.get("NAME", user.name);
        reader.get("CITY", user.city);
        user.print();
    }
    cout << "affected rows: " << cmd->getAffectedRows() << endl;
    delete cmd;
}

int main()
{
    db.init("localhost", "hxq", "123456", "testlazy");
    //testSelect();
    testUpdate();
}
