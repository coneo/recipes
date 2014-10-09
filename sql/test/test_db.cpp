#include "db.h"
#include <iostream>

using namespace water::componet;
using namespace std;
struct stUser
{
public:
    void print()
    {
        cout << "ID:" << id << " AGE:" << age << " NAME:" << string(name) << " CITY:" << city << endl;
    }
public:
    uint32_t id = 0;
    uint32_t age = 0;
    char name[32] = {0};
    std::string city = "";
};
int main()
{
    DB db;
    db.init("localhost", "hxq", "123456", "testlazy");

    /*****old style *******
    TableInfo* table = db.getTable("USER");
    if (table)
    {
        if (db.doDelete(table) == 0)
            fprintf(stdout, "delete table USER success\n");
    }*/

    /*
    Connection* con = db.getBkConnection();
    SqlCommand* cmd = new SqlCommand("DELETE FROM USER", con);
    cmd->executeNoQuery();
    delete cmd;
    */

    Connection* con = db.getBkConnection();
    SqlCommand* cmd = new SqlCommand("SELECT * FROM USER", con);
    DataReader reader = cmd->executeReader();
    //reader.print();
    stUser user;
    while (reader.read())
    {
        reader.get("ID", user.id);
        reader.get("AGE", user.age);
        reader.get("NAME", user.name);
        reader.get("CITY", user.city);
        user.print();
    }
    delete cmd;
}
