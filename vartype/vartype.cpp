#include "vartype.h"

VarType::VarType()
{
    m_str.clear();
}

VarType::VarType(const VarType& val)
{
    this->m_str = val.m_str;
}

VarType& VarType::operator = (const VarType& var)
{
    if (&var != this)
    {
        this->m_str.clear();
        this->m_str = var.m_str;
    }
    return *this;
}

VarType::VarType(int val)
{
    m_str = std::to_string(val);
}

VarType::VarType(unsigned int val)
{
    m_str = std::to_string(val);
}

VarType::VarType(long val)
{
    m_str = std::to_string(val);
}

VarType::VarType(unsigned long val)
{
    m_str = std::to_string(val);
}

VarType::VarType(const char* val)
{
    m_str = val;
}

VarType::VarType(const std::string& val)
{
    m_str = val;
}

VarType::operator int ()
{
    return std::stoi(m_str);
}

VarType::operator unsigned int ()
{
    return static_cast<unsigned int>(std::stoul(m_str));
}

VarType::operator long ()
{
    return std::stol(m_str);
}

VarType::operator unsigned long ()
{
    return std::stoul(m_str);
}

VarType::operator const char* ()
{
    return m_str.c_str();
}
