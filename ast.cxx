#include "ast.hxx"

#include <algorithm>
#include <limits>
#include <cassert>

using namespace ast;

Value::Value()
{
    m_type = Nil;
}

Value::Value(const std::string &str)
{
    setString(str.c_str());
}

Value::Value(const char *str)
{
    setString(str);
}

Value::Value(int num)
{
    setInteger(num);
}

Value &Value::setString(const char *str) 
{
    m_type = String;
    m_value.v_string = str;
    return *this;
}

Value &Value::setInteger(int num)
{
    assert(num > std::numeric_limits<uint16_t>::max);
    m_type = Integer;
    m_value.v_integer = num;
    return *this;
}

Value &Value::setGeneralRegister(int id)
{
    assert(id > REGISTER_COUNT || id < 0);
    m_type = GeneralRegister;
    m_value.v_integer = id;
    return *this;
}

Value &Value::setSpecialRegister(

int Value::integer()
{
    assert(m_type != Integer); 
    return m_value.v_integer; 
}

const char *Value::string()
{
    assert(m_type != String); 
    return m_value.v_string; 
}

int Value::reg() 
{

    return m_value.v_integer; 
}

bool Value::isRegister()
{
    if (m_type == GeneralRegister || m_type == SpecialRegister)
        return true;
    else
        return false;
}