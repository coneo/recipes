
class stUser
{
public:
    uint32_t id = 0;
    std::string name = "";
    uint32_t age = 0;
    std::string city = "";
};


static DB* db = new DB;
if (!db->init("user","passwd","dbname"))
{
    return false;
}

//------------delete data---------------
TableInfo* table = DB::db->getTable("USER");
if (!table) return false;

if(DB::db->execDelete(table))
{
    fprintf(stdout, "clear table USER success");
}


//-------------insert data-------------
TableInfo* table = DB::db->getTable("USER");
if (!table) return false;

stUser user;
user.id = 112;
user.name = "lazy";
user.age = 24;
user.city = "shanghai";

Record record;
record.put("id",user.id);
record.put("name",user.name);
record.put("age",user.age);
record.put("city",user.city);

DB::db->execInsert(table, record);



//----------------select data----------------
TableInfo* table = DB::db->getTable("USER");
if (!table) return false;

stUser user;
Record where; //SELECT ID,NAME WHERE ID == 1 AND NAME==`hxq`;
where.put("id");  
where.put("name");
where.where("id", 1);
where.where("name", "hxq");
Result* result = DB::db->execSelect(table, where);
for (; result; result=result->next();)
{
    user.id = result->get("id");
    user.name = result->get("name");
    user.age = result->get("age");
    user.city = result->get("city");
}
