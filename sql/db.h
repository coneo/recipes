#ifndef WATER_BASE_DB_HPP
#define WATER_BASE_DB_HPP

#include "mysql.h"
#include <sstream>
#include <vector>
#include <map>

namespace water{
namespace componet{

static const uint32_t DEFAULT_MYSQL_PORT = 3306;

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
    uint32_t m_port = 0;
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

    bool read();

    template <typename T>
    bool get(std::string name, T& value)
    {
        if (m_rowIndex < 0 || m_rowIndex >= m_datas.size()) return false;
        auto data = m_datas[m_rowIndex];
        auto iter = data.find(name);
        if (iter != data.end())
        {
            std::stringstream ss;
            ss << iter->second.data();
            ss >> value;
            return true;
        }
        return false;
    }

private:
    std::vector<std::map<std::string, FieldValue>> m_datas;
    uint32_t m_rowIndex = -1;
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

    uint32_t getAffectedRows() const;

private:
    std::string m_sql;
    Connection* m_conn;
};

class DB
{
public:
    bool init(std::string host, std::string user, std::string passwd, std::string dbname, uint32_t port=DEFAULT_MYSQL_PORT);

    TableInfo* getTable(std::string tbname);

    MYSQL* getHandle();

    void putHandle();

    Connection* getUseConnection();

    Connection* getConnection();

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
