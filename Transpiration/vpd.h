//
// vpd.h
// Version timestamp: 10-4-2018, 1:29 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <boost/variant.hpp>
#include "temperature_types.h"

enum VPD_ALGORITHMS : unsigned short
{
    VPD_BUCK_1981,
    VPD_BUCK_1996,
    VPD_GOFF,
    VPD_WMO
};

class vpd : public celcius, farenheit, kelvin
{
public:
    vpd();
    vpd(celcius_variant temperature, float humidity);
    vpd(celcius_variant temperature, float relative_humidity, VPD_ALGORITHMS algorithm);
    vpd(celcius_variant temperature, celcius_variant leaf_temperature, float humidity);
    vpd(celcius_variant temperature, celcius_variant leaf_temperature, float relative_humidity, VPD_ALGORITHMS algorithm);
    vpd(const vpd& c); 
    ~vpd();
    void calculate_vpd(celcius temperature, celcius temperature_leaf, float relative_humidity, VPD_ALGORITHMS algorithm);
    double calculate_vapor_pressure(celcius temperature, unsigned int method);
    double calculate_buck_1981(celcius temperature);
    double calculate_buck_1996(celcius temperature);
    double calculate_wmo(celcius temperature);
    double calculate_goff_gratch(celcius temperature);
	double calculate_dewpoint(celcius temperature, double relative_humidity);
	double calculate_precipital_water(celcius dewpoint);
    double operator()(celcius_variant temperature, float relative_humidity);
    double operator()(celcius_variant temperature, celcius_variant temperature_leaf, float relative_humidity); 
    double operator()(celcius_variant temperature, float relative_humidity, VPD_ALGORITHMS algorithm);
    double operator()(celcius_variant temperature, celcius_variant temperature_leaf, float relative_humidity, VPD_ALGORITHMS algorithm); 
    double operator()();
    friend std::ostream& operator<<(std::ostream& lhs, const vpd& rhs)
    {
        return (lhs << rhs.vapor_pressure_deficit);
    }
    
    celcius degrees_celcius = 0.0;
    celcius degrees_celcius_leaf = 0.0;
	celcius dewpoint_atmosphere;
	celcius dewpoint_leaf;
	double  precipital_h2o;
    float   humidity = 0.0;
    double saturation_vapor_pressure_atmosphere = 0.0;
    double saturation_vapor_pressure_leaf = 0.0;
    double vapor_pressure_atmosphere = 0.0;
    double vapor_pressure_leaf = 0.0;
    double vapor_pressure_deficit = 0.0;
};

