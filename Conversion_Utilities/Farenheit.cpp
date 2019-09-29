//
// Farenheit.cpp
// Version timestamp: 9-4-2018, 4:23 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "temperature_types.h"

farenheit::farenheit(farenheit_variant &r)
{
	farenheit_variant c = r;
	this->degrees_farenheit = boost::apply_visitor(tfarenheit_variant(), c);
}

farenheit::operator kelvin()
{
	//boost::apply_visitor(tcelcius_variant(), this);
	double temp = (this->degrees_farenheit - 32.0) * (5.0 / 9.0) + 273.15;
	return (temp);
}

farenheit::operator celcius()
{
	double temp = (this->degrees_farenheit - 32.0) * (5.0 / 9.0);
	return (temp);
}

void farenheit::operator=(farenheit_variant &temp2) 
{
	this->degrees_farenheit = boost::apply_visitor(tfarenheit_variant(), temp2);
}

double farenheit::operator-(farenheit_variant temp2) 
{
	double temp = this->degrees_farenheit - boost::apply_visitor(tfarenheit_variant(), temp2);
	return (temp);
}

double farenheit::operator+(farenheit_variant temp2) 
{
	double temp = this->degrees_farenheit + boost::apply_visitor(tfarenheit_variant(), temp2);
	return (temp);
}

double farenheit::operator*(farenheit_variant temp2) 
{
	double temp = this->degrees_farenheit * boost::apply_visitor(tfarenheit_variant(), temp2);
	return (temp);
}

double farenheit::operator/(farenheit_variant temp2) 
{
	double temp = this->degrees_farenheit / boost::apply_visitor(tfarenheit_variant(), temp2);
	return (temp);
}

double farenheit::operator()(farenheit_variant temp2) 
{
	double temp = boost::apply_visitor(tfarenheit_variant(), temp2);
	return (temp);
}

double farenheit::operator()() 
{
	double temp = this->degrees_farenheit;
	return (temp);
}

double farenheit::operator-=(farenheit_variant temp2) 
{
	this->degrees_farenheit = this->degrees_farenheit - boost::apply_visitor(tfarenheit_variant(), temp2);
	return (this->degrees_farenheit);
}

double farenheit::operator+=(farenheit_variant temp2) 
{
	this->degrees_farenheit = this->degrees_farenheit + boost::apply_visitor(tfarenheit_variant(), temp2);
	return (this->degrees_farenheit);
}

double farenheit::operator++(int incr) 
{
	this->degrees_farenheit +=  1.0;
	return (this->degrees_farenheit);
}

double farenheit::operator--(int incr) 
{
	this->degrees_farenheit -=  1.0;
	return (this->degrees_farenheit);
}

double farenheit::operator*=(farenheit_variant temp2) 
{
	this->degrees_farenheit = this->degrees_farenheit * boost::apply_visitor(tfarenheit_variant(), temp2);
	return (this->degrees_farenheit);
}

double farenheit::operator/=(farenheit_variant temp2) 
{
	this->degrees_farenheit = this->degrees_farenheit / boost::apply_visitor(tfarenheit_variant(), temp2);
	return (this->degrees_farenheit);
}

double farenheit::operator>(farenheit_variant temp2) 
{
	if (this->degrees_farenheit > boost::apply_visitor(tfarenheit_variant(), temp2)) return (1);
	return (0);
}

double farenheit::operator<(farenheit_variant temp2) 
{
	if (this->degrees_farenheit < boost::apply_visitor(tfarenheit_variant(), temp2)) return (1);
	return (0);
}

double farenheit::operator==(farenheit_variant temp2) 
{
	if (this->degrees_farenheit == boost::apply_visitor(tfarenheit_variant(), temp2)) return (1);
	return (0);
}

double farenheit::operator>=(farenheit_variant temp2) 
{
	if (this->degrees_farenheit >= boost::apply_visitor(tfarenheit_variant(), temp2)) return (1);
	return (0);
}
double farenheit::operator<=(farenheit_variant temp2) 
{
	if (this->degrees_farenheit <= boost::apply_visitor(tfarenheit_variant(), temp2)) return (1);
	return (0);
}