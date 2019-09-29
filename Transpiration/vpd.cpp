//
// vpd.cpp
// Version timestamp: 10-4-2018, 1:30 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//

// This source code may be utilized to calculate the vapor pressure deficit between plant mass and the surrounding environment.
// Requires the temperature conversion classes celcius, farenheit, and kelvin
//
// Some usage examples:
//
//  /* Determine the vapor pressure deficit for 80 degrees farenheit and 60 percent relative humidity. */
//  vpd vapor_pressure_deficit((farenheit) 80, 0.60);
//  std::cout << "Vapor pressure deficit" << vapor_pressure_deficit << std::endl;
//
//  /* Determine the vapor pressure deficit for 23 degrees celcius and 40 percent relative humidity. */
//  vpd vapor_pressure_deficit((celcius) 23, 0.40);
//  std::cout << "Vapor pressure deficit" << vapor_pressure_deficit << std::endl;
//
//  /* Using printf. */
//  vpd vapor_pressure_deficit((celcius) 23, 0.40);
//  printf("Vapor pressure deficit %8.3f \n",vapor_pressure_deficit());
//
//  /* If you know or have estimated the actual leaf temperature. */
//  vpd vapor_pressure_deficit((farenheit) 80, (farenheit) (80+1), 0.60);
//  std::cout << "Vapor pressure deficit" << vapor_pressure_deficit << std::endl;
//

#include "vpd.h"

/* Empty constructor for vapor pressure deficit. */
vpd::vpd()
{
    this->humidity = 0.0;
    this->degrees_celcius = 0.0;
    this->degrees_celcius_leaf = 0.0;
    this->vapor_pressure_atmosphere = 0.0;
    this->vapor_pressure_deficit = 0.0;
    this->vapor_pressure_leaf = 0.0;
}

/* Constructor */
/* Calculate the vapor pressure deficit based on the environment temperature and the relative humidity. */
/* In this case, the temperature of the plant mass is considered to be at the same temperature as the surrounding environment. */
vpd::vpd(celcius_variant temperature, float relative_humidity)
{
    if (relative_humidity > 1)
    {
        this->humidity = 1.0;
    }
    else if (relative_humidity < 0)
    {
        this->humidity = 0.0;
    }
    else
    {
        this->humidity = relative_humidity;
    }
    
    calculate_vpd(temperature, temperature, relative_humidity, VPD_BUCK_1981);
}

/* Constructor */
/* Calculate the vapor pressure deficit based on the environment temperature and the relative humidity. */
/* In this case, the temperature of the plant mass is considered to be at the same temperature as the surrounding environment. */
vpd::vpd(celcius_variant temperature, float relative_humidity, VPD_ALGORITHMS algorithm)
{
    if (relative_humidity > 1)
    {
        this->humidity = 1.0;
    }
    else if (relative_humidity < 0)
    {
        this->humidity = 0.0;
    }
    else
    {
        this->humidity = relative_humidity;
    }
    
    calculate_vpd(temperature, temperature, relative_humidity, algorithm);
}

/* Constructor */
/* Calculate the vapor pressure deficit based on the environment temperature, leaf temperature and the relative humidity. */
/* In this case, the temperature of the plant mass is used in the calculation of the pressure deficit. */
vpd::vpd(celcius_variant temperature, celcius_variant leaf_temperature, float relative_humidity)
{
    if (relative_humidity > 1)
    {
        humidity = 1.0;
    }
    else if (relative_humidity < 0)
    {
        humidity = 0.0;
    }
    else
    {
        humidity = relative_humidity;
    }
    
    calculate_vpd(temperature, leaf_temperature, relative_humidity, VPD_BUCK_1981);
}

/* Constructor */
/* Calculate the vapor pressure deficit based on the environment temperature, leaf temperature and the relative humidity. */
/* In this case, the temperature of the plant mass is used in the calculation of the pressure deficit and the calculation method is specified. */
vpd::vpd(celcius_variant temperature, celcius_variant leaf_temperature, float relative_humidity, VPD_ALGORITHMS algorithm)
{
    if (relative_humidity > 1)
    {
        humidity = 1.0;
    }
    else if (relative_humidity < 0)
    {
        humidity = 0.0;
    }
    else
    {
        humidity = relative_humidity;
    }
    
    calculate_vpd(temperature, leaf_temperature, relative_humidity, algorithm);
}


/* Copy Constructor */
vpd::vpd(const vpd& c) 
{ 
    this->degrees_celcius = c.degrees_celcius;  
    this->degrees_celcius_leaf = c.degrees_celcius_leaf; 
    this->humidity = c.humidity; 
    this->saturation_vapor_pressure_atmosphere = c.saturation_vapor_pressure_atmosphere;
    this->saturation_vapor_pressure_leaf = c.saturation_vapor_pressure_leaf;
    this->vapor_pressure_atmosphere = c.vapor_pressure_atmosphere; 
    this->vapor_pressure_leaf = c.vapor_pressure_leaf; 
    this->vapor_pressure_deficit = c.vapor_pressure_deficit;
} 

/* Destructor */
vpd::~vpd()
{
}

/* Do the VPD calculations. */
/* VPD units are in kPa. A rough estimate in millibars would be to multiply the results in kPa by ten.  */
void vpd::calculate_vpd(celcius temperature, celcius temperature_leaf, float relative_humidity, VPD_ALGORITHMS algorithm) 
{
    /* Save the temperatures and humidity. */
    this->degrees_celcius = temperature;
    this->degrees_celcius_leaf = temperature_leaf;
    this->humidity = relative_humidity;
    
    /* Calculate the water vapor pressure of the air. */
    this->saturation_vapor_pressure_atmosphere = calculate_vapor_pressure(this->degrees_celcius, algorithm);
    this->vapor_pressure_atmosphere = (humidity) * this->saturation_vapor_pressure_atmosphere;
    
    /* Calculate the water vapor pressure in the leaf. */
    
    /* Leaf has 100% humidity */
    this->saturation_vapor_pressure_leaf = calculate_vapor_pressure(this->degrees_celcius_leaf, algorithm);
    this->vapor_pressure_leaf = (1) * this->saturation_vapor_pressure_leaf;
    
    /* Calculate the water vapor pressure deficit of the air. */
    this->vapor_pressure_deficit = vapor_pressure_leaf - vapor_pressure_atmosphere;
	
	/* Calculate the dewpoints */
	this->dewpoint_atmosphere = calculate_dewpoint(temperature, relative_humidity);
	this->dewpoint_leaf = calculate_dewpoint(temperature_leaf, relative_humidity);
	
	/* Estimate the percipital H20 water column (in cm at sea level) */
	this->precipital_h2o = calculate_precipital_water(this->dewpoint_atmosphere);
	
}

double vpd::calculate_vapor_pressure(celcius temperature, unsigned int method)
{
    double vapor_pressure = 0.0;
    
    switch(method)
    {
    case VPD_BUCK_1981:
        vapor_pressure = calculate_buck_1981(temperature);
        break;
    case VPD_BUCK_1996:
        vapor_pressure = calculate_buck_1996(temperature);
        break;
    case VPD_GOFF:
        vapor_pressure = calculate_goff_gratch(temperature);
        break;
    case VPD_WMO:
        vapor_pressure = calculate_wmo(temperature);
        break;
    default: 
        vapor_pressure = calculate_buck_1981(temperature);
        break;
    }
    
    return (vapor_pressure);	
}

double vpd::calculate_buck_1981(celcius temperature)
{
    /* Buck, A. L., New equations for computing vapor pressure and enhancement factor, J. Appl. Meteorol., 20, 1527-1532, 1981. */
    double vapor_pressure = 0.61121 * pow(EULER, (17.502*temperature()) / (temperature() + 240.97));
    return (vapor_pressure);
}

double vpd::calculate_buck_1996(celcius temperature)
{
    double vapor_pressure = 0.61121 * pow(EULER, ((18.678 - temperature() / 234.5)*temperature()) / (temperature() + 257.14));
    return (vapor_pressure);
}

double vpd::calculate_wmo(celcius temperature)
{
    double vapor_pressure = 0.61121 * pow(EULER, (17.62*temperature()) / (temperature() + 243.12));
    return (vapor_pressure);
}

double vpd::calculate_goff_gratch(celcius temperature)
{
    kelvin Tkelvin = temperature;
    
    double a1 = -7.90298 * (373.16 / Tkelvin() - 1.0);
    double a2 = 5.02808 * log10(373.16 / Tkelvin() );
    double a3 = (-1.3816 / 10000000) * (powf(10, 11.344*(1.0 - Tkelvin() / 373.16)) - 1.0);
    double a4 = (8.1328 / 1000) * (powf(10, -3.49149*(373.16 / Tkelvin() - 1.0) - 1.0) );
        
    double vapor_pressure = a1 + a2 + a3 + a4 + log10(1013.246);
    
    return (powf(10.0,vapor_pressure)/10.0);
}

double vpd::calculate_dewpoint(celcius temperature, double relative_humidity)
{
	double dewpoint = 0.0;
	dewpoint = pow((relative_humidity), (1.0 / 8.0)) * (112.0 + (0.9 * temperature())) - 112.0 + (0.1 * temperature());
	
	return (dewpoint);
}

/* Estimate the clearday precipital water in the atomospheric column based on the surface dewpoint. */
/* “Modeling Daylight Availability and Irradiance Components from Direct and Global Irradiance,” Perez, et.al. 1990 Solar Energy 44(5) eq. 3. */
/* The coefficients are emperically generated based on monthly averages across 15 sites in the US. */
/* This may have significant error components depending on application and environmental conditions. */
double vpd::calculate_precipital_water(celcius dewpoint)
{
	double prcp = 0.0;
	
	prcp = exp(0.07 * dewpoint() - 0.075);
	
	return (prcp);
}


double vpd::operator()(celcius_variant temperature, float relative_humidity) 
{
    calculate_vpd(temperature, temperature, relative_humidity, VPD_BUCK_1981);
    double temp = this->vapor_pressure_deficit;
    return (temp);
}

double vpd::operator()(celcius_variant temperature, celcius_variant temperature_leaf, float relative_humidity) 
{
    calculate_vpd(temperature, temperature_leaf, relative_humidity, VPD_BUCK_1981);
    double temp = this->vapor_pressure_deficit;
    return (temp);
}

double vpd::operator()(celcius_variant temperature, float relative_humidity, VPD_ALGORITHMS algorithm) 
{
    calculate_vpd(temperature, temperature, relative_humidity, algorithm);
    double temp = this->vapor_pressure_deficit;
    return (temp);
}

double vpd::operator()(celcius_variant temperature, celcius_variant temperature_leaf, float relative_humidity, VPD_ALGORITHMS algorithm) 
{
    calculate_vpd(temperature, temperature_leaf, relative_humidity, algorithm);
    double temp = this->vapor_pressure_deficit;
    return (temp);
}

double vpd::operator()() 
{
    double temp = this->vapor_pressure_deficit;
    return (temp);
}