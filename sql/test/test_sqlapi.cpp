#include "mysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MYSQL* conn = NULL;

void close_with_error(MYSQL* mysql)
{
    fprintf(stderr, "%s\n",mysql_error(mysql));
    mysql_close(mysql);
    exit(1);
}

bool init()
{
    conn = mysql_init(NULL);
    if (!conn)
    {
        fprintf(stderr, "mysql_init error\n");
        return false;
    }
    if (!mysql_real_connect(conn, "localhost", "hxq", "123456", "testlazy", 3306, NULL, 0))
    {
        fprintf(stderr, "mysql_real_connect failed, error:%s\n", mysql_error(conn));
        return false;
    }
    return true;
}

void quit()
{
    mysql_close(conn);
}

void insertData()
{
    if (mysql_query(conn, "DELETE FROM USER"))
    {
        close_with_error(conn);
    }
    if (mysql_query(conn, "INSERT INTO USER VALUES(1, 'hxq', 22, 'shanghai')"))
    {
        close_with_error(conn);
    }
    if (mysql_query(conn, "INSERT INTO USER VALUES(2, 'hxq2', 22, 'chongqing')"))
    {
        close_with_error(conn);
    }
    if (mysql_query(conn, "INSERT INTO USER VALUES(3, 'hxq3', 22, 'shanghai')"))
    {
        close_with_error(conn);
    }
    if (mysql_query(conn, "INSERT INTO USER VALUES(4, 'hxq4', 22, 'shanghai')"))
    {
        close_with_error(conn);
    }
}

void selectData()
{
    if (mysql_query(conn, "SELECT * FROM USER"))
    {
        close_with_error(conn);
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL)
    {
        close_with_error(conn);
    }

    int num_field = mysql_num_fields(result);
    MYSQL_ROW row;
    while (row = mysql_fetch_row(result))
    {
        for (int i = 0; i < num_field; ++i)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    mysql_free_result(result);
}

#define STRING_SIZE 256
void preparedStat()
{
    MYSQL_STMT* stmt = NULL;
    MYSQL_BIND param[1], result[1];

    const char* sql = "SELECT `NAME` FROM `USER` WHERE ID=?";

    int           param_count;
    short         small_data;
    int           int_data;
    //char          str_data[STRING_SIZE];
    int           user_id;
    char          result_data[STRING_SIZE];
    unsigned long str_length;
    unsigned long data_length;
    my_bool       is_null;

    stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        close_with_error(conn);
    }
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
    {
        close_with_error(conn);
    }

    memset(param, 0, sizeof(param));
    memset(result, 0, sizeof(result));

    /* STRING PARAM */
    param[0].buffer_type = MYSQL_TYPE_LONG;
    param[0].buffer = (void *)&user_id;
    param[0].is_null = 0;
    param[0].length = 0;
    param[0].is_unsigned = 0;

    result[0].buffer_type= MYSQL_TYPE_VAR_STRING;
    result[0].buffer = result_data;
    result[0].buffer_length = STRING_SIZE;
    result[0].is_null = 0;
    result[0].length = &data_length;

    if (mysql_stmt_bind_param(stmt, param))
    {
        close_with_error(conn);
    }
    if (mysql_stmt_bind_result(stmt, result) != 0)
    {
        close_with_error(conn);
    }
    /* Specify the parameter that we send to the query */
    user_id = 3;

    if (mysql_stmt_execute(stmt))
    {
        close_with_error(conn);
    }
    /* Print our results */
    if(mysql_stmt_fetch (stmt) == 0)
    {
        printf("%s\n", result_data);
    }
    else
    {
        printf("No results found!\n");
    }

    if (mysql_stmt_close(stmt))
    {
        close_with_error(conn);
    }

}

int main()
{
    if (!init()) 
        return 0;

    insertData();
    //selectData();
    //preparedStat();

    quit();
    return 0;
}
