//
// Celcius.cpp
// Version timestamp: 2-9-2020, 1:33 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

celcius::celcius(celcius_variant &r)
{
    celcius_variant c = r;
    
    celcius temp = boost::apply_visitor(tkelvin_variant(), c);
    this->degrees_celcius = temp.degrees_celcius;
}

celcius::operator kelvin()
{
    kelvin temp = this->degrees_celcius + 273.15;
    return (temp);
}

celcius::operator fahrenheit()
{
    fahrenheit temp = this->degrees_celcius * (1.8) + 32.0;
    return (temp);
}

celcius::operator rankine()
{
    rankine temp = (this->degrees_celcius + 273.15) * (1.8);
    return (temp);
}

void celcius::operator=(celcius_variant &temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    this->degrees_celcius = temp.degrees_celcius;
}

celcius celcius::operator-(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius - boost::apply_visitor(tcelcius_variant(), temp2);
    return (temp);
}

celcius celcius::operator+(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius + boost::apply_visitor(tcelcius_variant(), temp2);
    return (temp);
}

celcius operator+(const double &c1, const celcius &c2)
{
    celcius temp = c1 + c2.degrees_celcius;
    return (temp);
}

celcius operator*(const double &c1, const celcius &c2)
{
    celcius temp = c1 * c2.degrees_celcius;
    return (temp);
}

celcius operator/(const double &c1, const celcius &c2)
{
    celcius temp = c1 / c2.degrees_celcius;
    return (temp);
}

celcius operator-(const double &c1, const celcius &c2)
{
    celcius temp = c1 - c2.degrees_celcius;
    return (temp);
}

celcius celcius::operator++(int incr) 
{
    this->degrees_celcius +=  1.0;
    return (this->degrees_celcius);
}

celcius celcius::operator--(int incr) 
{
    this->degrees_celcius -=  1.0;
    return (this->degrees_celcius);
}

celcius celcius::operator*(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius * boost::apply_visitor(tcelcius_variant(), temp2);
    return (temp);
}

celcius celcius::operator/(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius / boost::apply_visitor(tcelcius_variant(), temp2);
    return (temp);
}

double celcius::operator()(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    return (temp.degrees_celcius);
}

double celcius::operator()() 
{
    celcius temp = this->degrees_celcius;
    return (temp.degrees_celcius);
}

celcius celcius::operator-=(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius - boost::apply_visitor(tcelcius_variant(), temp2);
    this->degrees_celcius = temp.degrees_celcius;
    return (this->degrees_celcius);
}

celcius celcius::operator+=(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius + boost::apply_visitor(tcelcius_variant(), temp2);
    this->degrees_celcius = temp.degrees_celcius;
    return (this->degrees_celcius);
}

celcius celcius::operator*=(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius * boost::apply_visitor(tcelcius_variant(), temp2);
    this->degrees_celcius = temp.degrees_celcius;
    return (this->degrees_celcius);
}

celcius celcius::operator/=(celcius_variant temp2) 
{
    celcius temp = this->degrees_celcius / boost::apply_visitor(tcelcius_variant(), temp2);
    this->degrees_celcius = temp.degrees_celcius;
    return (this->degrees_celcius);
}

bool celcius::operator>(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    if (this->degrees_celcius > temp.degrees_celcius) return (1);
    return (0);
}

bool celcius::operator<(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    if (this->degrees_celcius < temp.degrees_celcius) return (1);
    return (0);
}

bool celcius::operator==(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    if (fabs(temp.degrees_celcius - this->degrees_celcius) <= 
        __DBL_EPSILON__ * fmax(fabs(temp.degrees_celcius), fabs(this->degrees_celcius))) return (1);
    return (0);
}

bool celcius::operator!=(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    if (fabs(temp.degrees_celcius - this->degrees_celcius) <=
        __DBL_EPSILON__ * fmax(fabs(temp.degrees_celcius), fabs(this->degrees_celcius))) return (0);
    return (1);
}

bool celcius::operator>=(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    if (this->degrees_celcius >= temp.degrees_celcius) return (1);
    return (0);
}

bool celcius::operator<=(celcius_variant temp2) 
{
    celcius temp = boost::apply_visitor(tcelcius_variant(), temp2);
    if (this->degrees_celcius <= temp.degrees_celcius) return (1);
    return (0);
}

