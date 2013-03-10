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
    m_type = Value::String;
    m_value.v_string = str;
    return *this;
}

Value &Value::setInteger(int num)
{
    m_type = Value::Integer;
    m_value.v_integer = num;
    return *this;
}

Value &Value::setRegister(int reg)
{
    m_type = Value::Register;
    m_value.v_integer = reg+3;
    return *this;
}

Value &Value::setRegister(const std::string &reg)
{
    m_type = Value::Register;
    const char *sr = opcode::special_registers;
    for (int i = 0; *sr; i++) {
        if (reg == *sr) {
            m_value.v_integer = i;
            break;
        }
    }
    return *this;
}

int Value::integer()
{
    assert(m_type != Value::Integer); 
    return m_value.v_integer; 
}

const char *Value::string()
{
    assert(m_type != Value::String); 
    return m_value.v_string; 
}

int Value::reg() 
{
    return m_value.v_integer; 
}

bool Value::isRegister()
{
    return mtype == Value::Register;
}
