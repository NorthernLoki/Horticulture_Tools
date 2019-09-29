//
// Daily_Light.cpp
// Version timestamp: 9-30-2018, 7:42 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "Daily_Light.h"

using namespace std::chrono;
using namespace date;
Daily_Light::Daily_Light()
{

}

Daily_Light::~Daily_Light()
{
    
}

double Daily_Light::calculate_dli(zoned_sun_time time, sun *sun_element)
{
	calculate_dli(time, sun_element, ATOM_SIMPLE);
}


double Daily_Light::calculate_dli(zoned_sun_time time, sun *sun_element, ATMOSPHERIC_MODEL atmosphere)
{
    
	sun sun_time;
    std::pair<double, double> element;
    boost::container::flat_set<std::pair<double, double>> the_set;
    unsigned int day_start = (unsigned int)(floor(sun_element->sunrise * 24.0));
    unsigned int day_end = (unsigned int)(floor(sun_element->sunset * 24.0));


    /* Skip over hours where there is no daylight locally, we are not calculating the moonlight contribution. */
	auto local_time = time.get_local_time() + hours(day_start);
	time = date::make_zoned(time.get_time_zone(), local_time);
    
    for (unsigned int hour = day_start;hour <= day_end;hour++)
    {
        
	    sun_time(sun_element->name, sun_element->observer_latitude, sun_element->observer_longitude, time, false);
	    double irrad = calculate_irrad(time, &sun_time, atmosphere);
	    
	    /* For the hours in the day where the sunrise and sunset begin at a fractional hour, we integrate on the minute. */
	    if (((hour == day_start) && (irrad <= 0.0)) || (hour == day_end))
	    {
		    /* Find the first and last daylight in the hour. */
		    zoned_sun_time temp_time = time;
		    unsigned int minute_stride = 5;
		    for (unsigned int minute = 1; minute <= 59; minute += minute_stride)
		    {
			    temp_time = time.get_local_time() + minutes(minute);
			    
			    sun_time(sun_element->name, sun_element->observer_latitude, sun_element->observer_longitude, temp_time, false);
			    irrad = calculate_irrad(temp_time, &sun_time, atmosphere);
		    
			    if (irrad > 0.0)
			    {
				    element = { (1.0*hour + minute / MINUTES_HOUR), irrad };
				    the_set.insert(element);
			    }
			    else if (hour == day_end)
			    {
				    element = { (1.0*hour + minute / MINUTES_HOUR), irrad  };
				    the_set.insert(element);
				    break;
			    }
		    }
	    }
	    else
	    {
		    element = { hour, irrad  };
		    the_set.insert(element);
	    }

	    time = time.get_local_time() + hours(1);
    }
    
    integrate integral(&the_set);
	
	/* SECONDS_HOUR converts the solar constant from unit J / m^2 s (or W m^2) to J m^2 hour */
	this->irrad = SOLAR_CONSTANT * ((integral.integral) * (SECONDS_HOUR)) / 1000000.0; /* MJ/m^2 */
	this->ppfd  = 4.5976 * SOLAR_CONSTANT * ((integral.integral) * (SECONDS_HOUR)) / 1000000.0;
	
	//this->irrad = SOLAR_CONSTANT * ((integral.integral)) / 1000000.0; /* MJ/m^2 */
	//this->ppfd  = 4.5976 * SOLAR_CONSTANT * ((integral.integral)) / 1000000.0;
		
    return (irrad);
}

/* Extraterrestrial radiation at 0 degree angle to incident sun radiation (normal plane) */
double Daily_Light::calculate_extraterestrial_radiation(double rad_vector)
{
	double ic_prime = 1 / (rad_vector * rad_vector);
    return (ic_prime);
}


/* Extraterrestrial radiation at surface angle (horizontal plane) to inbound radiation */
double Daily_Light::calculate_incident_surface_irradiation(double normal_radiation, double solar_elevation)
{
	double irrad;
	if (solar_elevation > 0.0)
	{
		double solar_zenith = 90.0 - solar_elevation;
		irrad = /* normal_radiation * */fabs(TO_RADIAN(calculate_plane_surface_angle(solar_zenith)));
	}
	else
	{
		irrad = 0;	
	}
	
    return (irrad);
}


/* Projection */
/* surface_tilt = surface tilt angle from horizontal. */
/* surface_azimuth = surface azimuth angle from the north. */
/* solar_zenith = apparent solar zenith of the sun/light source. */
/* solar_azimuth = apparent solar azimuth of the sun/light source. */
double Daily_Light::calculate_projection(double surface_tilt, double solar_zenith, double surface_azimuth, double solar_azimuth)
{
    double angle = cos(TO_RADIAN(surface_tilt)) * cos(TO_RADIAN(solar_zenith));
    angle += sin(TO_RADIAN(surface_tilt)) * sin(TO_RADIAN(solar_zenith));
    angle *= cos(TO_RADIAN(solar_azimuth - surface_azimuth));
    angle = TO_DEGREE(angle);
    
    return (angle);
}


/* Incident plane angle to inbound radiation */
/* Incident radiation is on a plane that is tangent to the outer surface of the atmosphere. E.g. laying flat on the surface. */
double Daily_Light::calculate_plane_surface_angle(double solar_zenith)
{
    double angle = TO_DEGREE(cos(TO_RADIAN(solar_zenith)) );
    return (angle);
}

/* Incident angle to inbound radiation */
/* surface_tilt = surface tilt angle from horizontal. */
/* surface_azimuth = surface azimuth angle from the north. */
/* solar_zenith = apparent solar zenith of the sun/light source. */
/* solar_azimuth = apparent solar azimuth of the sun/light source. */
double Daily_Light::calculate_incident_angle(double surface_tilt, double solar_zenith, double surface_azimuth, double solar_azimuth)
{
    double angle = calculate_projection(surface_tilt, solar_zenith, surface_azimuth, solar_azimuth);
    angle = TO_DEGREE(acos(TO_RADIAN(angle)));
    
    return (angle);
}


/* Clear day beam transmittance. */
/* The solar radiation received from the sun without having been scattered by the atmosphere. */
double Daily_Light::calculate_beam_transmittance_clear(double altitude_km, std::tuple<double, double, double> climate, double solar_elevation)
{
    double r0 = std::get<0>(climate);
    double r1 = std::get<1>(climate);
    double rk = std::get<2>(climate);
    
    /*  Hottel, ASHRAE 1985  */
	double a0 = r0 * (0.4237 - 0.00821 * (6.0 - altitude_km) * (6.0 - altitude_km));
	double a1 = r1 * (0.5055 - 0.00595 * (6.5 - altitude_km) * (6.5 - altitude_km));
	double k = (-1.0) * rk * (0.2711 - 0.01858 * (2.5 - altitude_km) * (2.5 - altitude_km));
   
    
    double tb = 0.0;
	double zenith = 90.0 - solar_elevation;
    
	if (solar_elevation > 0.0)
	{
		tb = a0 + a1 * exp(k / (TO_DEGREE(sin(TO_RADIAN(fabs(solar_elevation)))) + 0.0000001));
	}
	else
	{
		tb = 0.0;
	}

    return (tb);

}

/* The solar radiation received from the sun having been scattered by the atmosphere. */
double Daily_Light::calculate_diffuse_radiation(double beam_transmittance)
{
	double td = 0.0;
	
	/*  Liu and Jordan (1960)  */
	if (beam_transmittance > 0)
	{
		td = 0.2710 - (0.2939 * beam_transmittance);
	}
    
    return (td);
}

double Daily_Light::calculate_irrad(zoned_sun_time time, sun *sun_element, ATMOSPHERIC_MODEL atmosphere)
{
	double solar_elevation = sun_element->solar_elevation_corrected;
    std::tuple<double, double, double> climate = std::tuple<double, double, double>(0.97, 0.99, 1.02);
    
    this->ic_prime = calculate_extraterestrial_radiation(sun_element->rad_vector);
	this->irrad_tilted = calculate_incident_surface_irradiation(this->ic_prime, solar_elevation);
	switch (atmosphere)
	{
	case (ATOM_NONE):
		{
			this->direct_normal = 1.0;
			this->beam_transmittance = 1.0;
			this->diffuse_radiation = 0.0;
		
			/* Total solar radiation. */
			this->irrad = this->irrad_tilted * (this->beam_transmittance + this->diffuse_radiation);
			
			break;
		}
	case (ATOM_SIMPLE):
		{
			this->relative_optical_path = optical_air_mass(solar_elevation, sun_element->sec_z_inverse, 0.0, AM_PICKERING);
			this->beam_transmittance = calculate_beam_transmittance_clear(0.0, climate, solar_elevation);
			this->diffuse_radiation = calculate_diffuse_radiation(this->beam_transmittance);
			
			this->irrad = this->irrad_tilted * (this->beam_transmittance + this->diffuse_radiation);
			
			break;
		}
	case (ATOM_BIRD):
		{
			this->relative_optical_path = optical_air_mass(solar_elevation, sun_element->sec_z_inverse, 0.0, AM_PICKERING);
			bird bird_calculation(solar_elevation, ic_prime, this->relative_optical_path, TO_MILLIBAR(ATM1_AVE), 0.3, 1.5, 0.15, 0.1, 0.85, 0.076370, 0.2);
			this->global_horizontal = bird_calculation.global_horizontal;
			this->irrad = this->global_horizontal;
			
			break;
		}
	case (ATOM_PEREZ):
		{
			this->irrad = 0.0;
			break;
		}
	case (ATOM_INEICHEN):
		{
			this->irrad = 0.0;
			break;
		}
	default:
		{
			this->direct_normal = 1.0;
			this->beam_transmittance = 1.0;
			this->diffuse_radiation = 0.0;
		
			/* Total solar radiation. */
			this->irrad = this->irrad_tilted * (this->beam_transmittance + this->diffuse_radiation);
			break;
		}
	}
	
	
    return (this->irrad);
}

/* Air mass, relative optical path. solar_elevation is apparent solar_elevation. */
double Daily_Light::optical_air_mass(double solar_elevation, double inverse_secant_zenith, double altitude, AIR_MASS_MODEL model)
{
    double relative_optical_path;
    double altitude_h = 1.0;
	double zenith = 90.0 - solar_elevation;
    
    if (altitude > 0.0)
    {
        altitude_h = exp(-0.0001184 * altitude); 
    }
    
    switch (model)
    {
    case AM_KASTENYOUNG:
        {
            double power = 0.50572*pow((6.07995 + (90 - zenith)), -1.6364);
            relative_optical_path = altitude_h / (cos(TO_RADIAN(zenith)) + power);
            break;
        }	
    case AM_KASTEN:
        {
            double power = 0.15*pow((93.885 - zenith), -1.253);
            relative_optical_path = altitude_h / (cos(TO_RADIAN(zenith)) + power);
            break;
        }	
    case AM_PICKERING:
        {
            double power = pow(165.0 + 47.0 * (90.0 - zenith), 1.1);
            relative_optical_path = (altitude_h / (sin(TO_RADIAN(90.0 - zenith + 244.0 / power))));
            break;
        }
    case AM_GUEYMARD:
        {
            double power = zenith * 0.00176759 * pow((94.37515 - zenith), -1.21563);
            relative_optical_path = altitude_h / (cos(TO_RADIAN(zenith)) + power);
            break;
        }
    default:
	    relative_optical_path = 0.0;
        break;
    }
	
	if (isnanf(relative_optical_path))
	{
		relative_optical_path = 0.0;
	}

    return (relative_optical_path);
}

/* Air mass, absolute air mass at input atmospheric pressure. Return is in pascals */
double Daily_Light::absolute_air_mass(double relative_optical_path, double air_pressure)
{
    double absolute_airmass = (relative_optical_path*air_pressure) / (ATM1_AVE);
    
    return (absolute_airmass);
}

/* Air mass, absolute air mass at sea level. Return is in pascals */
double Daily_Light::absolute_air_mass(double relative_optical_path)
{
    double absolute_airmass = (relative_optical_path);
    
    return (absolute_airmass);
}
