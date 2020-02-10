//
// temperature_types.h
// Version timestamp: 2-9-2020, 1:33 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once

#include <string>
#include <sstream>
#include <boost/variant.hpp>
#include <iostream>

#include "Conversion_Constants.h"

class celcius; class kelvin; class Temperature; class fahrenheit; class rankine;
typedef boost::variant<celcius, kelvin, fahrenheit, rankine, double> celcius_variant;
typedef boost::variant<celcius, kelvin, fahrenheit, rankine, double> kelvin_variant;
typedef boost::variant<celcius, kelvin, fahrenheit, rankine, double> fahrenheit_variant;
typedef boost::variant<celcius, kelvin, fahrenheit, rankine, double> rankine_variant;

class fahrenheit
{
    
public:
    double degrees_fahrenheit = 0;
    fahrenheit()
        : degrees_fahrenheit(0) {}
    fahrenheit(const fahrenheit& c) { degrees_fahrenheit = c.degrees_fahrenheit; } // Copy contructor
    fahrenheit(double r) { degrees_fahrenheit = r; }
    fahrenheit(fahrenheit_variant &r);
    void operator=(fahrenheit_variant &temp2);
    virtual fahrenheit operator-(fahrenheit_variant temp2);
    virtual fahrenheit operator+(fahrenheit_variant temp2); 
    virtual fahrenheit operator*(fahrenheit_variant temp2); 
    virtual fahrenheit operator/(fahrenheit_variant temp2); 
    virtual fahrenheit operator-=(fahrenheit_variant temp2);
    virtual fahrenheit operator+=(fahrenheit_variant temp2); 
    virtual fahrenheit operator++(int incr);
    virtual fahrenheit operator--(int incr); 
    virtual fahrenheit operator*=(fahrenheit_variant temp2);
    virtual fahrenheit operator/=(fahrenheit_variant temp2); 
    virtual double operator()(fahrenheit_variant temp2);
    virtual double operator()(); 
    virtual bool operator>(fahrenheit_variant temp2); 
    virtual bool operator<(fahrenheit_variant temp2); 
    virtual bool operator>=(fahrenheit_variant temp2); 
    virtual bool operator<=(fahrenheit_variant temp2); 
    virtual bool operator==(fahrenheit_variant temp2); 
    virtual bool operator!=(fahrenheit_variant temp2); 
    virtual operator celcius();
    virtual operator kelvin();
    virtual operator rankine();

    friend std::ostream& operator<<(std::ostream& lhs, const fahrenheit& rhs)
    {
        return (lhs << rhs.degrees_fahrenheit);
    }
    
    friend fahrenheit operator+(const double &c1, fahrenheit c2); 
    friend fahrenheit operator*(const double &c1, fahrenheit c2); 
    friend fahrenheit operator/(const double &c1, fahrenheit c2); 
    friend fahrenheit operator-(const double &c1, fahrenheit c2); 
    
    explicit operator double() const { return degrees_fahrenheit;}
    explicit operator float() const { return degrees_fahrenheit;}
    explicit operator int() const { return (int)(degrees_fahrenheit + 0.5);}
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
    virtual kelvin operator-(kelvin_variant temp2);
    virtual kelvin operator+(kelvin_variant temp2); 
    virtual kelvin operator*(kelvin_variant temp2); 
    virtual kelvin operator/(kelvin_variant temp2); 
    virtual kelvin operator-=(kelvin_variant temp2);
    virtual kelvin operator+=(kelvin_variant temp2); 
    virtual kelvin operator++(int incr);
    virtual kelvin operator--(int incr); 
    virtual kelvin operator*=(kelvin_variant temp2);
    virtual kelvin operator/=(kelvin_variant temp2); 
    virtual double operator()(kelvin_variant temp2); 
    virtual double operator()(); 
    virtual bool operator>(kelvin_variant temp2); 
    virtual bool operator<(kelvin_variant temp2); 
    virtual bool operator>=(kelvin_variant temp2); 
    virtual bool operator<=(kelvin_variant temp2); 
    virtual bool operator==(kelvin_variant temp2); 
    virtual bool operator!=(kelvin_variant temp2); 
    virtual operator celcius();
    virtual operator fahrenheit();
    virtual operator rankine();

    friend std::ostream& operator<<(std::ostream& lhs, const kelvin& rhs)
    {
        return (lhs << rhs.degrees_kelvin);
    }
    
    friend kelvin operator+(const double &c1, kelvin c2); 
    friend kelvin operator*(const double &c1, kelvin c2); 
    friend kelvin operator/(const double &c1, kelvin c2); 
    friend kelvin operator-(const double &c1, kelvin c2); 
    
    explicit operator double() const { return degrees_kelvin;}
    explicit operator float() const { return degrees_kelvin;}
    explicit operator int() const { return (int)(degrees_kelvin + 0.5);}
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
    virtual celcius operator-(celcius_variant temp2);
    virtual celcius operator+(celcius_variant temp2); 
    virtual celcius operator*(celcius_variant temp2); 
    virtual celcius operator/(celcius_variant temp2); 
    virtual celcius operator-=(celcius_variant temp2);
    virtual celcius operator+=(celcius_variant temp2); 
    virtual celcius operator++(int incr);
    virtual celcius operator--(int incr); 
    virtual celcius operator*=(celcius_variant temp2);
    virtual celcius operator/=(celcius_variant temp2); 
    virtual double operator()(celcius_variant temp2); 
    virtual double operator()(); 
    virtual bool operator>(celcius_variant temp2); 
    virtual bool operator<(celcius_variant temp2); 
    virtual bool operator>=(celcius_variant temp2); 
    virtual bool operator<=(celcius_variant temp2); 
    virtual bool operator==(celcius_variant temp2); 
    virtual bool operator!=(celcius_variant temp2); 
    virtual operator kelvin();
    virtual operator fahrenheit();
    virtual operator rankine();
    
    friend std::ostream& operator<<(std::ostream& lhs, const celcius& rhs)
    {
        return (lhs << rhs.degrees_celcius);
    }
    
    friend celcius operator+(const double &c1, const celcius &c2); 
    friend celcius operator*(const double &c1, const celcius &c2); 
    friend celcius operator/(const double &c1, const celcius &c2); 
    friend celcius operator-(const double &c1, const celcius &c2); 
    
    explicit operator double() const { return degrees_celcius;}
    explicit operator float() const { return degrees_celcius;}
    explicit operator int() const { return (int)(degrees_celcius + 0.5);}
    
};

class rankine
{
    
public:
    double degrees_rankine = 0;
    rankine()
        : degrees_rankine(0) {}
    rankine(const rankine& c) { degrees_rankine = c.degrees_rankine; } // Copy contructor
    rankine(double r) { degrees_rankine = r; }
    rankine(rankine_variant &r);
    void operator=(rankine_variant &temp2);
    virtual rankine operator-(rankine_variant temp2);
    virtual rankine operator+(rankine_variant temp2); 
    virtual rankine operator*(rankine_variant temp2); 
    virtual rankine operator/(rankine_variant temp2); 
    virtual rankine operator-=(rankine_variant temp2);
    virtual rankine operator+=(rankine_variant temp2); 
    virtual rankine operator++(int incr);
    virtual rankine operator--(int incr); 
    virtual rankine operator*=(rankine_variant temp2);
    virtual rankine operator/=(rankine_variant temp2); 
    virtual double operator()(rankine_variant temp2); 
    virtual double operator()(); 
    virtual bool operator>(rankine_variant temp2); 
    virtual bool operator<(rankine_variant temp2); 
    virtual bool operator>=(rankine_variant temp2); 
    virtual bool operator<=(rankine_variant temp2); 
    virtual bool operator==(rankine_variant temp2); 
    virtual bool operator!=(rankine_variant temp2); 
    virtual operator kelvin();
    virtual operator fahrenheit();
    virtual operator celcius();
    
    friend std::ostream& operator<<(std::ostream& lhs, const rankine& rhs)
    {
        return (lhs << rhs.degrees_rankine);
    }
    
    friend rankine operator+(const double &c1, const rankine &c2); 
    friend rankine operator*(const double &c1, const rankine &c2); 
    friend rankine operator/(const double &c1, const rankine &c2); 
    friend rankine operator-(const double &c1, const rankine &c2); 
    
    explicit operator double() const { return degrees_rankine;}
    explicit operator float() const { return degrees_rankine;}
    explicit operator int() const { return (int)(degrees_rankine + 0.5);}
};



class tcelcius_variant : public boost::static_visitor<celcius>
{
public:
    celcius operator()(double temperature) const
    {
        return (temperature);
    }
    
    celcius operator()(celcius temperature) const
    {
        return (temperature);
    }
    
    celcius operator()(kelvin temperature) const
    {
        celcius temp = temperature.degrees_kelvin - 273.15;
        return (temp);
    }
    
    celcius operator()(fahrenheit temperature) const
    {
        celcius temp = (temperature.degrees_fahrenheit - 32.0) / (1.8);
        return (temp);
    }
    
    celcius operator()(rankine temperature) const
    {
        celcius temp = (temperature.degrees_rankine -  491.67) / (1.8);
        return (temp);
    }
    
};

class tkelvin_variant : public boost::static_visitor<kelvin>
{
public:
    kelvin operator()(double temperature) const
    {
        return (temperature);
    }
    
    kelvin operator()(kelvin temperature) const
    {
        return (temperature);
    }
    
    kelvin operator()(celcius temperature) const
    {
        kelvin temp = temperature.degrees_celcius + 273.15;
        return (temp);
    }
    
    kelvin operator()(fahrenheit temperature) const
    {
        kelvin temp = (temperature.degrees_fahrenheit - 32.0) / (1.8) + 273.15;
        return (temp);
    }
    
    kelvin operator()(rankine temperature) const
    {
        kelvin temp = (temperature.degrees_rankine) / (1.8);
        return (temp);
    }
    
};

class tfahrenheit_variant : public boost::static_visitor<fahrenheit>
{
public:
    fahrenheit operator()(double temperature) const
    {
        return (temperature);
    }
    
    fahrenheit operator()(fahrenheit temperature) const
    {
        return (temperature);
    }
    
    fahrenheit operator()(celcius temperature) const
    {
        fahrenheit temp = temperature.degrees_celcius * (1.8) + 32.0;
        return (temp);
    }
    
    fahrenheit operator()(kelvin temperature) const
    {
        fahrenheit temp = (temperature.degrees_kelvin) * (1.8) - 459.67;
        return (temp);
    }
    
    fahrenheit operator()(rankine temperature) const
    {
        fahrenheit temp = (temperature.degrees_rankine) - 459.67;
        return (temp);
    }
    
};

class trankine_variant : public boost::static_visitor<rankine>
{
public:
    rankine operator()(double temperature) const
    {
        return (temperature);
    }
    
    rankine operator()(rankine temperature) const
    {
        return (temperature);
    }
    
    rankine operator()(celcius temperature) const
    {
        rankine temp = (temperature.degrees_celcius + 273.15) * (1.8);
        return (temp);
    }
    
    rankine operator()(kelvin temperature) const
    {
        rankine temp = (temperature.degrees_kelvin) * (1.8);
        return (temp);
    }
    
    rankine operator()(fahrenheit temperature) const
    {
        rankine temp = (temperature.degrees_fahrenheit) + 459.67;
        return (temp);
    }
    
};


