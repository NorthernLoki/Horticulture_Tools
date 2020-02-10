//
// Rankine.cpp
// Version timestamp: 2-9-2020, 1:33 PM
//
// Attribution : Copyright (c) 2020 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

rankine::rankine(rankine_variant &r)
{
    rankine_variant c = r;
    rankine temp = boost::apply_visitor(trankine_variant(), c);
    this->degrees_rankine = temp.degrees_rankine;
}

rankine::operator fahrenheit()
{
    fahrenheit temp = (this->degrees_rankine) - 459.67;
    return (temp);
}

rankine::operator celcius()
{
    celcius temp = (this->degrees_rankine - 491.67) / (1.8);
    return (temp);
}

rankine::operator kelvin()
{
    kelvin temp = this->degrees_rankine * (1.8);
    return (temp);
}

void rankine::operator=(rankine_variant &temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    this->degrees_rankine = temp.degrees_rankine;
}

rankine rankine::operator-(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp -= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((rankine)temp);
}

rankine rankine::operator+(celcius_variant temp2) 
{
    celcius temp = celcius(*this);
    temp += boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((rankine)temp);
}

rankine operator+(const double &c1, rankine c2)
{
    celcius temp = c1 + celcius(c2);
    return ((rankine)temp);
}

rankine operator*(const double &c1, rankine c2)
{
    celcius temp = c1 * celcius(c2);
    return ((rankine)temp);
}

rankine operator/(const double &c1, rankine c2)
{
    celcius temp = c1 / celcius(c2);
    return ((rankine)temp);
}

rankine operator-(const double &c1, rankine c2)
{
    celcius temp = c1 - celcius(c2);
    return ((rankine)temp);
}

rankine rankine::operator*(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp *= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((rankine)temp);
}

rankine rankine::operator/(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp /= boost::apply_visitor(tcelcius_variant(), temp2);
    
    return ((rankine)temp);
}

double rankine::operator()(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    return (temp.degrees_rankine);
}

double rankine::operator()() 
{
    double temp = this->degrees_rankine;
    return (temp);
}

rankine rankine::operator-=(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp - boost::apply_visitor(tcelcius_variant(), temp2);
    rankine tempk = temp;
    this->degrees_rankine = tempk.degrees_rankine;
    
    return (tempk);
}

rankine rankine::operator+=(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp + boost::apply_visitor(tcelcius_variant(), temp2);
    rankine tempk = temp;
    this->degrees_rankine = tempk.degrees_rankine;
    
    return (tempk);
}

rankine rankine::operator++(int incr) 
{
    this->degrees_rankine +=  1.0;
    return (this->degrees_rankine);
}

rankine rankine::operator--(int incr) 
{
    this->degrees_rankine -= 1.0;
    return (this->degrees_rankine);
}

rankine rankine::operator*=(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp * boost::apply_visitor(tcelcius_variant(), temp2);
    rankine tempk = temp;
    this->degrees_rankine = tempk.degrees_rankine;
    
    return (tempk);
}

rankine rankine::operator/=(rankine_variant temp2) 
{
    celcius temp = celcius(*this);
    temp = temp / boost::apply_visitor(tcelcius_variant(), temp2);
    rankine tempk = temp;
    this->degrees_rankine = tempk.degrees_rankine;
    
    return (tempk);
}

bool rankine::operator>(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    if (this->degrees_rankine > temp.degrees_rankine) return (1);
    return (0);
}

bool rankine::operator<(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    if (this->degrees_rankine < temp.degrees_rankine) return (1);
    return (0);
}

bool rankine::operator==(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    if (fabs(temp.degrees_rankine - this->degrees_rankine) <= 
    __DBL_EPSILON__ * fmax(fabs(temp.degrees_rankine), fabs(this->degrees_rankine))) return (1);
    return (0);
}

bool rankine::operator!=(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    if (fabs(temp.degrees_rankine - this->degrees_rankine) <= 
        __DBL_EPSILON__ * fmax(fabs(temp.degrees_rankine), fabs(this->degrees_rankine))) return (0);
    return (1);
}

bool rankine::operator>=(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    if (this->degrees_rankine >= temp.degrees_rankine) return (1);
    return (0);
}
bool rankine::operator<=(rankine_variant temp2) 
{
    rankine temp = boost::apply_visitor(trankine_variant(), temp2);
    if (this->degrees_rankine <= temp.degrees_rankine) return (1);
    return (0);
}
