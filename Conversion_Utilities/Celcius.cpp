//
// Celcius.cpp
// Version timestamp: 9-4-2018, 4:23 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

celcius::celcius(celcius_variant &r)
{
	celcius_variant c = r;
	this->degrees_celcius = boost::apply_visitor(tcelcius_variant(), c);
}

celcius::operator kelvin()
{
	double temp = this->degrees_celcius + 273.15;
	return (temp);
}

celcius::operator farenheit()
{
	double temp = this->degrees_celcius * (9.0 / 5.0) + 32.0;
	return (temp);
}

void celcius::operator=(celcius_variant &temp2) 
{
	this->degrees_celcius = boost::apply_visitor(tcelcius_variant(), temp2);
}

double celcius::operator-(celcius_variant temp2) 
{
	double temp = this->degrees_celcius - boost::apply_visitor(tcelcius_variant(), temp2);
	return (temp);
}

double celcius::operator+(celcius_variant temp2) 
{
	double temp = this->degrees_celcius + boost::apply_visitor(tcelcius_variant(), temp2);
	return (temp);
}

double celcius::operator++(int incr) 
{
	this->degrees_celcius +=  1.0;
	return (this->degrees_celcius);
}

double celcius::operator--(int incr) 
{
	this->degrees_celcius -=  1.0;
	return (this->degrees_celcius);
}

double celcius::operator*(celcius_variant temp2) 
{
	double temp = this->degrees_celcius * boost::apply_visitor(tcelcius_variant(), temp2);
	return (temp);
}

double celcius::operator/(celcius_variant temp2) 
{
	double temp = this->degrees_celcius / boost::apply_visitor(tcelcius_variant(), temp2);
	return (temp);
}

double celcius::operator()(celcius_variant temp2) 
{
	double temp = boost::apply_visitor(tcelcius_variant(), temp2);
	return (temp);
}

double celcius::operator()() 
{
	double temp = this->degrees_celcius;
	return (temp);
}

double celcius::operator-=(celcius_variant temp2) 
{
	this->degrees_celcius = this->degrees_celcius - boost::apply_visitor(tcelcius_variant(), temp2);
	return (this->degrees_celcius);
}

double celcius::operator+=(celcius_variant temp2) 
{
	this->degrees_celcius = this->degrees_celcius + boost::apply_visitor(tcelcius_variant(), temp2);
	return (this->degrees_celcius);
}

double celcius::operator*=(celcius_variant temp2) 
{
	this->degrees_celcius = this->degrees_celcius * boost::apply_visitor(tcelcius_variant(), temp2);
	return (this->degrees_celcius);
}

double celcius::operator/=(celcius_variant temp2) 
{
	this->degrees_celcius = this->degrees_celcius / boost::apply_visitor(tcelcius_variant(), temp2);
	return (this->degrees_celcius);
}

double celcius::operator>(celcius_variant temp2) 
{
	if (this->degrees_celcius > boost::apply_visitor(tcelcius_variant(), temp2)) return (1);
	return (0);
}

double celcius::operator<(celcius_variant temp2) 
{
	if (this->degrees_celcius < boost::apply_visitor(tcelcius_variant(), temp2)) return (1);
	return (0);
}

double celcius::operator==(celcius_variant temp2) 
{
	if (this->degrees_celcius == boost::apply_visitor(tcelcius_variant(), temp2)) return (1);
	return (0);
}

double celcius::operator>=(celcius_variant temp2) 
{
	if (this->degrees_celcius >= boost::apply_visitor(tcelcius_variant(), temp2)) return (1);
	return (0);
}
double celcius::operator<=(celcius_variant temp2) 
{
	if (this->degrees_celcius <= boost::apply_visitor(tcelcius_variant(), temp2)) return (1);
	return (0);
}
