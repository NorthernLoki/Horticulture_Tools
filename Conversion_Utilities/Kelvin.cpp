//
// Kelvin.cpp
// Version timestamp: 9-4-2018, 4:23 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

kelvin::kelvin(kelvin_variant &r)
{
	kelvin_variant c = r;
	this->degrees_kelvin = boost::apply_visitor(tkelvin_variant(), c);
}

kelvin::operator farenheit()
{
	//boost::apply_visitor(tcelcius_variant(), this);
	double temp = (this->degrees_kelvin) * (9.0 / 5.0) - 459.67;
	return (temp);
}

kelvin::operator celcius()
{
	double temp = this->degrees_kelvin - 273.15;
	return (temp);
}

void kelvin::operator=(kelvin_variant &temp2) 
{
	this->degrees_kelvin = boost::apply_visitor(tkelvin_variant(), temp2);
}

double kelvin::operator-(kelvin_variant temp2) 
{
	double temp = this->degrees_kelvin - boost::apply_visitor(tkelvin_variant(), temp2);
	return (temp);
}

double kelvin::operator+(kelvin_variant temp2) 
{
	double temp = this->degrees_kelvin + boost::apply_visitor(tkelvin_variant(), temp2);
	return (temp);
}

double kelvin::operator*(kelvin_variant temp2) 
{
	double temp = this->degrees_kelvin * boost::apply_visitor(tkelvin_variant(), temp2);
	return (temp);
}

double kelvin::operator/(kelvin_variant temp2) 
{
	double temp = this->degrees_kelvin / boost::apply_visitor(tkelvin_variant(), temp2);
	return (temp);
}

double kelvin::operator()(kelvin_variant temp2) 
{
	double temp = boost::apply_visitor(tkelvin_variant(), temp2);
	return (temp);
}

double kelvin::operator()() 
{
	double temp = this->degrees_kelvin;
	return (temp);
}

double kelvin::operator-=(kelvin_variant temp2) 
{
	this->degrees_kelvin = this->degrees_kelvin - boost::apply_visitor(tkelvin_variant(), temp2);
	return (this->degrees_kelvin);
}

double kelvin::operator+=(kelvin_variant temp2) 
{
	this->degrees_kelvin = this->degrees_kelvin + boost::apply_visitor(tkelvin_variant(), temp2);
	return (this->degrees_kelvin);
}

double kelvin::operator++(int incr) 
{
	this->degrees_kelvin +=  1.0;
	return (this->degrees_kelvin);
}

double kelvin::operator--(int incr) 
{
	this->degrees_kelvin -= 1.0;
	return (this->degrees_kelvin);
}

double kelvin::operator*=(kelvin_variant temp2) 
{
	this->degrees_kelvin = this->degrees_kelvin * boost::apply_visitor(tkelvin_variant(), temp2);
	return (this->degrees_kelvin);
}

double kelvin::operator/=(kelvin_variant temp2) 
{
	this->degrees_kelvin = this->degrees_kelvin / boost::apply_visitor(tkelvin_variant(), temp2);
	return (this->degrees_kelvin);
}

double kelvin::operator>(kelvin_variant temp2) 
{
	if (this->degrees_kelvin > boost::apply_visitor(tkelvin_variant(), temp2)) return (1);
	return (0);
}

double kelvin::operator<(kelvin_variant temp2) 
{
	if (this->degrees_kelvin < boost::apply_visitor(tkelvin_variant(), temp2)) return (1);
	return (0);
}

double kelvin::operator==(kelvin_variant temp2) 
{
	if (this->degrees_kelvin == boost::apply_visitor(tkelvin_variant(), temp2)) return (1);
	return (0);
}

double kelvin::operator>=(kelvin_variant temp2) 
{
	if (this->degrees_kelvin >= boost::apply_visitor(tkelvin_variant(), temp2)) return (1);
	return (0);
}
double kelvin::operator<=(kelvin_variant temp2) 
{
	if (this->degrees_kelvin <= boost::apply_visitor(tkelvin_variant(), temp2)) return (1);
	return (0);
}