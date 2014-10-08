#include "db.h"

using namespace water::componet;
int main()
{
    DB db;
    db.init("localhost", "hxq", "123456", "testlazy");

    /*
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
    reader.print();
}
