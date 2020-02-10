//
// fahrenheit.cpp
// Version timestamp: 2-9-2020, 1:33 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

fahrenheit::fahrenheit(fahrenheit_variant &r)
{
    fahrenheit_variant c = r;
    
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), c);
    this->degrees_fahrenheit = temp.degrees_fahrenheit;
}

fahrenheit::operator kelvin()
{
    kelvin temp = (this->degrees_fahrenheit - 32.0) / (1.8) + 273.15;
    return (temp);
}

fahrenheit::operator celcius()
{
    celcius temp = (this->degrees_fahrenheit - 32.0) / (1.8);
    return (temp);
}

fahrenheit::operator rankine()
{
    rankine temp = (this->degrees_fahrenheit + 459.67);
    return (temp);
}

void fahrenheit::operator=(fahrenheit_variant &temp2) 
{
    fahrenheit temp = boost::apply_visitor(tcelcius_variant(), temp2);
    this->degrees_fahrenheit = temp.degrees_fahrenheit;
}

fahrenheit fahrenheit::operator-(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp -= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((fahrenheit)temp);
}

fahrenheit fahrenheit::operator+(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp += boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((fahrenheit)temp);
}

fahrenheit operator+(const double &c1, fahrenheit c2)
{
    celcius temp = c1 + celcius(c2);
    return ((fahrenheit)temp);
}

fahrenheit operator*(const double &c1, fahrenheit c2)
{
    celcius temp = c1 * celcius(c2);
    return ((fahrenheit)temp);
}

fahrenheit operator/(const double &c1, fahrenheit c2)
{
    celcius temp = c1 / celcius(c2);
    return ((fahrenheit)temp);
}

fahrenheit operator-(const double &c1, fahrenheit c2)
{
    celcius temp = c1 - celcius(c2);
    return ((fahrenheit)temp);
}

fahrenheit fahrenheit::operator*(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp *= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((fahrenheit)temp);
}

fahrenheit fahrenheit::operator/(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp /= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((fahrenheit)temp);
}

double fahrenheit::operator()(fahrenheit_variant temp2) 
{
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    return (temp.degrees_fahrenheit);
}

double fahrenheit::operator()() 
{
    double temp = this->degrees_fahrenheit;
    return (temp);
}

fahrenheit fahrenheit::operator-=(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp - boost::apply_visitor(tcelcius_variant(), temp2);
    fahrenheit tempf = temp;
    this->degrees_fahrenheit = tempf.degrees_fahrenheit;
    
    return (tempf);
}

fahrenheit fahrenheit::operator+=(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp + boost::apply_visitor(tcelcius_variant(), temp2);
    fahrenheit tempf = temp;
    this->degrees_fahrenheit = tempf.degrees_fahrenheit;
    
    return (tempf);
}

fahrenheit fahrenheit::operator++(int incr) 
{
    this->degrees_fahrenheit +=  1.0;
    return (this->degrees_fahrenheit);
}

fahrenheit fahrenheit::operator--(int incr) 
{
    this->degrees_fahrenheit -=  1.0;
    return (this->degrees_fahrenheit);
}

fahrenheit fahrenheit::operator*=(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp * boost::apply_visitor(tcelcius_variant(), temp2);
    fahrenheit tempf = temp;
    this->degrees_fahrenheit = tempf.degrees_fahrenheit;
    
    return (tempf);
}

fahrenheit fahrenheit::operator/=(fahrenheit_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp / boost::apply_visitor(tcelcius_variant(), temp2);
    fahrenheit tempf = temp;
    this->degrees_fahrenheit = tempf.degrees_fahrenheit;
    
    return (tempf);
}

bool fahrenheit::operator>(fahrenheit_variant temp2) 
{ 
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    if (this->degrees_fahrenheit > temp.degrees_fahrenheit) return (1);
    return (0);
}

bool fahrenheit::operator<(fahrenheit_variant temp2) 
{
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    if (this->degrees_fahrenheit < temp.degrees_fahrenheit) return (1);
    return (0);
}

bool fahrenheit::operator==(fahrenheit_variant temp2) 
{
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    if (fabs(temp.degrees_fahrenheit - this->degrees_fahrenheit) <= 
    __DBL_EPSILON__ * fmax(fabs(temp.degrees_fahrenheit), fabs(this->degrees_fahrenheit))) return (1);
    return (0);
}

bool fahrenheit::operator!=(fahrenheit_variant temp2) 
{
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    if (fabs(temp.degrees_fahrenheit - this->degrees_fahrenheit) <= 
    __DBL_EPSILON__ * fmax(fabs(temp.degrees_fahrenheit), fabs(this->degrees_fahrenheit))) return (0);
    return (1);
}

bool fahrenheit::operator>=(fahrenheit_variant temp2) 
{
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    if (this->degrees_fahrenheit >= temp.degrees_fahrenheit) return (1);
    return (0);
}
bool fahrenheit::operator<=(fahrenheit_variant temp2) 
{
    fahrenheit temp = boost::apply_visitor(tfahrenheit_variant(), temp2);
    if (this->degrees_fahrenheit <= temp.degrees_fahrenheit) return (1);
    return (0);
}
