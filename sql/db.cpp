#include "db.h"
#include <algorithm>
#include <iostream>
#include <string.h>

namespace water{
namespace componet{

Connection::Connection(ConnectionInfo* info)
    : m_coninfo(info),
      m_mysql(NULL)
{
}

bool Connection::connect()
{
    if (m_mysql)
        close();
    m_mysql = mysql_init(NULL);
    if (!m_mysql)
    {
        fprintf(stderr, "mysql_init failed, error:%s\n");
        return false;
    }
    if (!mysql_real_connect(m_mysql,
                            m_coninfo->m_host.c_str(),
                            m_coninfo->m_user.c_str(),
                            m_coninfo->m_passwd.c_str(),
                            m_coninfo->m_dbname.c_str(),
                            3306,
                            NULL,
                            CLIENT_COMPRESS | CLIENT_MULTI_STATEMENTS | CLIENT_INTERACTIVE))
    {
        fprintf(stderr, "mysql_real_connect failed, error:%s\n", mysql_error(m_mysql));
        return false;
    }

    setState(ConState::IN_USE);
    fprintf(stdout, "mysql connect success, client version:%s\n", mysql_get_client_info());
    return true;
}

int32_t FieldValue::setData(const char* data, uint32_t len)
{
    if (!data || len == 0)
        return 0;

    m_data.resize(len+1);
    memcpy((char*)m_data.data(), data, len);
    ((char*)m_data.data())[len] = '\0';
    return 0;
}

void DataReader::fillData(Connection* con)
{
    //考虑用smartptr来管理MYSQL_RES
    MYSQL_RES* result = mysql_store_result(con->handle());
    if (result == NULL)
    {
        return ;
    }

    uint32_t num_rows = mysql_num_rows(result);
    if (num_rows == 0)
    {
        return ;
    }
    uint32_t num_fields = mysql_num_fields(result);
    MYSQL_FIELD* fields = NULL;
    fields = mysql_fetch_fields(result);
    if (fields == NULL)
    {
        return ;
    }

    unsigned long* lengths = NULL;
    MYSQL_ROW row;
    for (uint32_t nrows = 0; nrows < num_rows; ++nrows)
    {
        row = mysql_fetch_row(result);
        lengths = mysql_fetch_lengths(result);
        if (!lengths)
        {
            return ;
        }
        std::map<std::string, FieldValue> fieldDatas;
        for (uint32_t nfields = 0; nfields < num_fields; ++nfields)
        {
            FieldValue& value = fieldDatas[fields[nfields].name];
            value.setData((char*)row[nfields], lengths[nfields]);
        }
        m_datas.push_back(fieldDatas);
    }
}

void DataReader::print()
{
    for (auto rowItem : m_datas)
    {
        for (auto fieldItem : rowItem)
        {
            std::cout << fieldItem.first << ":" << fieldItem.second.data() <<" ";
        }
        std::cout << std::endl;
    }
}

bool DataReader::read()
{
    return (++m_rowIndex < m_datas.size());
}

int32_t SqlCommand::executeNoQuery()
{
    if (!m_conn || !m_conn->handle()) return -1;
    mysql_query(m_conn->handle(), m_sql.c_str());
    return mysql_affected_rows(m_conn->handle());
}

DataReader SqlCommand::executeReader()
{
    if (!m_conn || !m_conn->handle()) return DataReader();
    mysql_query(m_conn->handle(), m_sql.c_str());

    DataReader reader;
    reader.fillData(m_conn);
    return reader;
}

bool DB::init(std::string host, std::string user, std::string passwd, std::string dbname)
{
    m_coninfo.m_host = host;
    m_coninfo.m_user = user;
    m_coninfo.m_passwd = passwd;
    m_coninfo.m_dbname = dbname;
    MYSQL* mysql = getHandle();
    if (!mysql)
    {
        fprintf(stderr, "DB init failed, getHandle error\n");
        return false;
    }
    MYSQL_RES* tables = NULL;
    tables = mysql_list_tables(mysql, NULL);
    if (tables)
    {
        MYSQL_ROW table;
        while ((table = mysql_fetch_row(tables)))
        {
            TableInfo tableInfo;
            tableInfo.m_name = table[0];
            MYSQL_RES* fields = mysql_list_fields(mysql, table[0], NULL);
            uint32_t fields_num = 0;
            if (fields)
            {
                fields_num = mysql_num_fields(fields);
                MYSQL_FIELD* mysql_fields = mysql_fetch_fields(fields);
                if (!mysql_fields)
                {
                    mysql_free_result(fields);
                    putHandle();
                    return false;
                }
                for (int32_t i = 0; i < fields_num; ++i)
                {
                    MYSQL_FIELD field = mysql_fields[i];
                    FieldInfo fieldInfo;
                    fieldInfo.m_name = field.name;
                    fieldInfo.m_type = field.type;
                    tableInfo.m_fields.push_back(fieldInfo);
                }
                mysql_free_result(fields);
            }
            std::transform(tableInfo.m_name.begin(), tableInfo.m_name.end(), tableInfo.m_name.begin(), toupper);
            m_tables[tableInfo.m_name] = tableInfo;
        }
        mysql_free_result(tables);
    }
    putHandle();
    return true;
}

TableInfo* DB::getTable(std::string tbname)
{
    auto findit = m_tables.find(tbname);
    if (findit != m_tables.end())
        return &(findit->second);
    return NULL;
}

MYSQL* DB::getHandle()
{
    if (m_nowcon)
        return m_nowcon->handle();

    m_nowcon = getConnection();
    if (m_nowcon)
        return m_nowcon->handle();
    return NULL;
}

void DB::putHandle()
{
    if (m_nowcon)
        m_nowcon->setState(ConState::IDLE);
}

Connection* DB::getConnection()
{
    for (auto& con : m_connections)
    {
        if (con.getState() == ConState::IDLE && con.connect())
        {
            con.setState(ConState::IN_USE);
            return &con;
        }
    }
    Connection newcon(&m_coninfo);
    if (newcon.connect())
    {
        m_connections.push_back(newcon);
        newcon.setState(ConState::IN_USE);
        return &(m_connections.back());
    }
    return  NULL;
}

Connection* DB::getBkConnection()
{
    if (m_nowcon) return m_nowcon;
    m_nowcon = getConnection();
    if (m_nowcon)
        return m_nowcon;
    return NULL;
}

/*
int32_t DB::doDelete(TableInfo* table)
{
    if (!table) return -1;
    std::string sql = "DELETE FROM " + table->m_name;
    SqlCommand* cmd = new SqlCommand(sql, getBkConnection());
    if (cmd)
    {
        cmd->executeNoQuery();
        delete cmd;
    }
    return 0;
}*/

}}
