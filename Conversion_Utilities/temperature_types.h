//
// temperature_types.h
// Version timestamp: 9-4-2018, 4:23 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
//
//
// Some usage examples: 
//
//	//Initialize some temperature variables
//	celcius cel_temp = 32.0;
//  celcius cel_temp2(31.0);
//  kelvin kel_temp(280);
//  farenheit far_temp(80);
//  kelvin kel_temp2(cel_temp);
//  farenheit far_temp2(kel_temp);
//
//  //Print the value in celcius with alternatives
//  std::cout << "Temperature celcius(32)" << cel_temp << std::endl;
//  std::cout << "Temperature celcius(32): " << cel_temp.degrees_celcius << std::endl;
//  std::cout << "Temperature celcius(32): " << cel_temp() << std::endl;
//  std::cout << "Temperature F to c: " << (celcius) far_temp << std::endl;
//  std::cout << "Temperature K to c: " << (celcius) kel_temp << std::endl;
//  std::cout << "Temperature F to K: " << (kelvin) far_temp << std::endl;
//  std::cout << "Temperature c to K: " << (kelvin) cel_temp << std::endl;
//  std::cout << "Temperature c to F: " << (farenheit) cel_temp << std::endl;
//  std::cout << "Temperature kelvin to F: " << (farenheit) kel_temp << std::endl;
//	
//  printf("Temperature: %8.3f\n", cel_temp());
//
//  //Print the celcius value in kelvin
//  std::cout << "Temperature c to K" << (kelvin)cel_temp << std::endl;
//
//  //Print the celcius value in farenheit
//  std::cout << "Temperature c to F" << (farenheit)cel_temp << std::endl;
//
//  //Do some math with different units
//  celcius cel_temp3 = 32.0;
//  cel_temp2 = cel_temp3 + far_temp;
//  cel_temp3++;
//  cel_temp += 10;
//  std::cout << "Temperature celcius (33): " << cel_temp3 << std::endl;
//  std::cout << "Temperature celcius (32 + 80F): " << cel_temp2 << std::endl;
//  std::cout << "Temperature celcius (42):" << cel_temp << std::endl;
//  std::cout << "Temperature celcius + kelvin: " << cel_temp + kel_temp << std::endl;
//	
//  if (cel_temp > kel_temp) std::cout << "Celcius Temperature is greater" << std::endl;
//  else if (cel_temp < kel_temp) std::cout << "Kelvin Temperature is greater" << std::endl;
//  else if (cel_temp == kel_temp) std::cout << "Temperatures are equivalent" << std::endl;
//


#pragma once

#include <string>
#include <sstream>
#include <boost/variant.hpp>
#include <iostream>

#include "Conversion_Constants.h"

class celcius; class kelvin; class Temperature; class farenheit;
typedef boost::variant<celcius, kelvin, farenheit, double> celcius_variant;
typedef boost::variant<celcius, kelvin, farenheit, double> kelvin_variant;
typedef boost::variant<celcius, kelvin, farenheit, double> farenheit_variant;


class farenheit
{
	
public:
	double degrees_farenheit = 0;
	farenheit()
		: degrees_farenheit(0) {}
	farenheit(const farenheit& c) { degrees_farenheit = c.degrees_farenheit; } // Copy contructor
	farenheit(double r) { degrees_farenheit = r; }
	farenheit(farenheit_variant &r);
	void operator=(farenheit_variant &temp2);
	virtual double operator-(farenheit_variant temp2);
	virtual double operator+(farenheit_variant temp2); 
	virtual double operator*(farenheit_variant temp2); 
	virtual double operator/(farenheit_variant temp2); 
	virtual double operator-=(farenheit_variant temp2);
	virtual double operator+=(farenheit_variant temp2); 
	virtual double operator++(int incr);
	virtual double operator--(int incr); 
	virtual double operator*=(farenheit_variant temp2);
	virtual double operator/=(farenheit_variant temp2); 
	virtual double operator()(farenheit_variant temp2);
	virtual double operator()(); 
	virtual double operator>(farenheit_variant temp2); 
	virtual double operator<(farenheit_variant temp2); 
	virtual double operator>=(farenheit_variant temp2); 
	virtual double operator<=(farenheit_variant temp2); 
	virtual double operator==(farenheit_variant temp2); 
	virtual operator celcius();
	virtual operator kelvin();
	friend std::ostream& operator<<(std::ostream& lhs, const farenheit& rhs)
	{
		return (lhs << rhs.degrees_farenheit);
	}
};


class kelvin 
{
	
public:
	double degrees_kelvin = 0;
	kelvin()
		: degrees_kelvin(0) {}
	kelvin(const kelvin& c) { degrees_kelvin = c.degrees_kelvin; } // Copy contructor
	kelvin(double r) { degrees_kelvin = r; }
	kelvin(kelvin_variant &r);
	void operator=(kelvin_variant &temp2);
	virtual double operator-(kelvin_variant temp2);
	virtual double operator+(kelvin_variant temp2); 
	virtual double operator*(kelvin_variant temp2); 
	virtual double operator/(kelvin_variant temp2); 
	virtual double operator-=(kelvin_variant temp2);
	virtual double operator+=(kelvin_variant temp2); 
	virtual double operator++(int incr);
	virtual double operator--(int incr); 
	virtual double operator*=(kelvin_variant temp2);
	virtual double operator/=(kelvin_variant temp2); 
	virtual double operator()(kelvin_variant temp2); 
	virtual double operator()(); 
	virtual double operator>(kelvin_variant temp2); 
	virtual double operator<(kelvin_variant temp2); 
	virtual double operator>=(kelvin_variant temp2); 
	virtual double operator<=(kelvin_variant temp2); 
	virtual double operator==(kelvin_variant temp2); 
	virtual operator celcius();
	virtual operator farenheit();
	friend std::ostream& operator<<(std::ostream& lhs, const kelvin& rhs)
	{
		return (lhs << rhs.degrees_kelvin);
	}
};


class celcius
{
	
public:
	double degrees_celcius = 0;
	celcius()
		: degrees_celcius(0) {}
	celcius(const celcius& c) { degrees_celcius = c.degrees_celcius; } // Copy contructor
	celcius(double r) { degrees_celcius = r; }
	celcius(celcius_variant &r);
	void operator=(celcius_variant &temp2);
	virtual double operator-(celcius_variant temp2);
	virtual double operator+(celcius_variant temp2); 
	virtual double operator*(celcius_variant temp2); 
	virtual double operator/(celcius_variant temp2); 
	virtual double operator-=(celcius_variant temp2);
	virtual double operator+=(celcius_variant temp2); 
	virtual double operator++(int incr);
	virtual double operator--(int incr); 
	virtual double operator*=(celcius_variant temp2);
	virtual double operator/=(celcius_variant temp2); 
	virtual double operator()(celcius_variant temp2); 
	virtual double operator()(); 
	virtual double operator>(celcius_variant temp2); 
	virtual double operator<(celcius_variant temp2); 
	virtual double operator>=(celcius_variant temp2); 
	virtual double operator<=(celcius_variant temp2); 
	virtual double operator==(celcius_variant temp2); 
	virtual operator kelvin();
	virtual operator farenheit();
	friend std::ostream& operator<<(std::ostream& lhs, const celcius& rhs)
	{
		return (lhs << rhs.degrees_celcius);
	}
};



class tcelcius_variant : public boost::static_visitor<double>
{
public:
	double operator()(double temperature) const
	{
		return (temperature);
	}
	
	double operator()(celcius temperature) const
	{
		return (temperature.degrees_celcius);
	}
	
	double operator()(kelvin temperature) const
	{
		double temp = temperature.degrees_kelvin - 273.15;
		return (temp);
	}
	
	double operator()(farenheit temperature) const
	{
		double temp = (temperature.degrees_farenheit - 32.0) * (5.0 / 9.0);
		return (temp);
	}
	
};

class tkelvin_variant : public boost::static_visitor<double>
{
public:
	double operator()(double temperature) const
	{
		return (temperature);
	}
	
	double operator()(kelvin temperature) const
	{
		return (temperature.degrees_kelvin);
	}
	
	double operator()(celcius temperature) const
	{
		double temp = temperature.degrees_celcius + 273.15;
		return (temp);
	}
	
	double operator()(farenheit temperature) const
	{
		double temp = (temperature.degrees_farenheit - 32.0) * (5.0 / 9.0) + 273.15;
		return (temp);
	}
	
};

class tfarenheit_variant : public boost::static_visitor<double>
{
public:
	double operator()(double temperature) const
	{
		return (temperature);
	}
	
	double operator()(farenheit temperature) const
	{
		return (temperature.degrees_farenheit);
	}
	
	double operator()(celcius temperature) const
	{
		double temp = temperature.degrees_celcius * (9.0 / 5.0) + 32.0;
		return (temp);
	}
	
	double operator()(kelvin temperature) const
	{
		double temp = (temperature.degrees_kelvin) * (9.0 / 5.0) - 459.67;
		return (temp);
	}
	
};


