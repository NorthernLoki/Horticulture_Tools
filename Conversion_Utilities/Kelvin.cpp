//
// Kelvin.cpp
// Version timestamp: 2-9-2020, 1:33 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

kelvin::kelvin(kelvin_variant &r)
{
    kelvin_variant c = r;
    kelvin temp = boost::apply_visitor(tkelvin_variant(), c);
    this->degrees_kelvin = temp.degrees_kelvin;
}

kelvin::operator fahrenheit()
{
    fahrenheit temp = (this->degrees_kelvin) * (1.8) - 459.67;
    return (temp);
}

kelvin::operator celcius()
{
    celcius temp = this->degrees_kelvin - 273.15;
    return (temp);
}

kelvin::operator rankine()
{
    rankine temp = this->degrees_kelvin * (1.8);
    return (temp);
}


void kelvin::operator=(kelvin_variant &temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    this->degrees_kelvin = temp.degrees_kelvin;
}

kelvin kelvin::operator-(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp -= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((kelvin)temp);
}

kelvin kelvin::operator+(celcius_variant temp2) 
{
    celcius temp = celcius(*this);
    temp += boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((kelvin)temp);
}

kelvin operator+(const double &c1, kelvin c2)
{
    celcius temp = c1 + celcius(c2);
    return ((kelvin)temp);
}

kelvin operator*(const double &c1, kelvin c2)
{
    celcius temp = c1 * celcius(c2);
    return ((kelvin)temp);
}

kelvin operator/(const double &c1, kelvin c2)
{
    celcius temp = c1 / celcius(c2);
    return ((kelvin)temp);
}

kelvin operator-(const double &c1, kelvin c2)
{
    celcius temp = c1 - celcius(c2);
    return ((kelvin)temp);
}

kelvin kelvin::operator*(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp *= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((kelvin)temp);
}

kelvin kelvin::operator/(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp /= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((kelvin)temp);
}

double kelvin::operator()(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    return (temp.degrees_kelvin);
}

double kelvin::operator()() 
{
    double temp = this->degrees_kelvin;
    return (temp);
}

kelvin kelvin::operator-=(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp - boost::apply_visitor(tcelcius_variant(), temp2);
    kelvin tempk = temp;
    this->degrees_kelvin = tempk.degrees_kelvin;
    
    return (tempk);
}

kelvin kelvin::operator+=(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp + boost::apply_visitor(tcelcius_variant(), temp2);
    kelvin tempk = temp;
    this->degrees_kelvin = tempk.degrees_kelvin;
    
    return (tempk);
}

kelvin kelvin::operator++(int incr) 
{
    this->degrees_kelvin +=  1.0;
    return (this->degrees_kelvin);
}

kelvin kelvin::operator--(int incr) 
{
    this->degrees_kelvin -= 1.0;
    return (this->degrees_kelvin);
}

kelvin kelvin::operator*=(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp * boost::apply_visitor(tcelcius_variant(), temp2);
    kelvin tempk = temp;
    this->degrees_kelvin = tempk.degrees_kelvin;
    
    return (tempk);
}

kelvin kelvin::operator/=(kelvin_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp / boost::apply_visitor(tcelcius_variant(), temp2);
    kelvin tempk = temp;
    this->degrees_kelvin = tempk.degrees_kelvin;
    
    return (tempk);
}

bool kelvin::operator>(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    if (this->degrees_kelvin > temp.degrees_kelvin) return (1);
    return (0);
}

bool kelvin::operator<(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    if (this->degrees_kelvin < temp.degrees_kelvin) return (1);
    return (0);
}

bool kelvin::operator==(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    if (fabs(temp.degrees_kelvin - this->degrees_kelvin) <= 
    __DBL_EPSILON__ * fmax(fabs(temp.degrees_kelvin), fabs(this->degrees_kelvin))) return (1);
    return (0);
}

bool kelvin::operator!=(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    if (fabs(temp.degrees_kelvin - this->degrees_kelvin) <= 
        __DBL_EPSILON__ * fmax(fabs(temp.degrees_kelvin), fabs(this->degrees_kelvin))) return (0);
    return (1);
}

bool kelvin::operator>=(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    if (this->degrees_kelvin >= temp.degrees_kelvin) return (1);
    return (0);
}
bool kelvin::operator<=(kelvin_variant temp2) 
{
    kelvin temp = boost::apply_visitor(tkelvin_variant(), temp2);
    if (this->degrees_kelvin <= temp.degrees_kelvin) return (1);
    return (0);
}
