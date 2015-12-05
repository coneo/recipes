/*
 * Author: HongXiaoqiang  - cool.hxq@gmail.com
 *
 * Last modified: 2015-09-03 15:28 +0800
 *
 * Description: 可变类型
 */
#ifndef _VARTYPE_H
#define _VARTYPE_H

#include <string>

class VarType
{
public:
    VarType();
    VarType(const VarType& val);

    VarType& operator = (const VarType& var);

    VarType(const char* val);
    VarType(const std::string& val);
    VarType(int val);
    VarType(unsigned int val);
    VarType(long val);
    VarType(unsigned long val);

    operator const char* ();
    operator int ();
    operator unsigned int ();
    operator long ();
    operator unsigned long ();

private:
    std::string m_str;
};

#endif
