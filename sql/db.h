#ifndef WATER_BASE_DB_HPP
#define WATER_BASE_DB_HPP

#include "mysql.h"
#include <vector>
#include <map>

namespace water{
namespace componet{

enum class DBRetcode : uint32_t
{
    SUCCESS = 0,
};
enum class ConState : uint8_t
{
    IDLE,
    IN_USE
};

struct ConnectionInfo
{
    std::string m_host = "";
    std::string m_user = "";
    std::string m_passwd = "";
    std::string m_dbname = "";
};

class Connection
{
public:
    Connection(ConnectionInfo* info);

    bool connect();

    void close()
    {
        mysql_close(m_mysql);
        m_mysql = NULL;
    }

    MYSQL* handle(){ return m_mysql; }

    void setState(ConState state){ m_state = state; }
    ConState getState() const { return m_state; }

private:
    MYSQL* m_mysql = NULL;
    ConnectionInfo* m_coninfo = NULL;
    ConState m_state = ConState::IDLE;
};

class FieldInfo
{
public:
    std::string m_name = "";
    int32_t m_type = -1;
};

class TableInfo
{
public:
    std::string m_name = "";
    std::vector<FieldInfo> m_fields;
};

class FieldValue
{
public:
    int32_t setData(const char* data, uint32_t len);

    const char* data()
    {
        return m_data.data();
    }

private:
    std::string m_data;
};

class DataReader
{
public:
    void fillData(Connection* con);

    void print();

private:
    std::vector<std::map<std::string, FieldValue>> m_datas;
};

class SqlCommand
{
public:
    SqlCommand(std::string sql, Connection* conn)
        : m_sql(sql),
          m_conn(conn)
    {
    }

    int32_t executeNoQuery();

    DataReader executeReader();

private:
    std::string m_sql;
    Connection* m_conn;
};

class DB
{
public:
    bool init(std::string host, std::string user, std::string passwd, std::string dbname);

    TableInfo* getTable(std::string tbname);

    MYSQL* getHandle();

    void putHandle();

    Connection* getConnection();

    Connection* getBkConnection();

    //int32_t doDelete(TableInfo* table);

    //int32_t doInsert(TableInfo* table, Record* record);

    //int32_t doSelect(TableInfo* table, Record* record);

private:
    std::map<std::string, TableInfo> m_tables;
    ConnectionInfo m_coninfo;
    std::vector<Connection> m_connections;
    Connection* m_nowcon = NULL;
};

}}
#endif
