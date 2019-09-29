//
// sun.cpp
// Version timestamp: 9-26-2018, 10:36 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//

/* Based on the calculation methods per NOAA at https://www.esrl.noaa.gov/gmd/grad/solcalc/ */
/* This is a bit more complicated but is also a relatively accurate calculation method in comparision to some of the short cut algorithms. */

#include "sun.h"

sun::sun()
{
	this->name = "";
	this->zone_time = NULL;
	this->utc_offset = 0.0;
	this->observer_longitude = 0.0;
	this->observer_latitude = 0.0;
	this->julian = 0.0;
	this->julian_century = 0.0;
	this->geom_mean_longitude = 0.0;
	this->geom_mean_anomoly = 0.0;
	this->eccentric_earth_orbit = 0.0;
	this->sun_center = 0.0;
	this->true_longitude = 0.0;
	this->true_anomoly = 0.0;
	this->rad_vector = 0.0;
	this->apparent_longitude = 0.0;
	this->mean_obliquity_ecliptic = 0.0;
	this->mean_obliquity_correction = 0.0;
	this->right_ascension = 0.0;
	this->sunrise_hour_angle = 0.0;
	this->sunset_hour_angle = 0.0;
	this->hour_angle = 0.0;
	this->sec_z_inverse = 0.0;
	this->zenith_angle = 0.0;
	this->solar_elevation = 0.0;
	this->declincation = 0.0;
	this->solar_azimuth_angle = 0.0;
	this->atmospheric_refraction = 0.0;
	this->solar_elevation_corrected = 0.0;
	this->EoT = 0.0;
	this->solar_time = 0.0;
	this->solar_noon = 0.0;
	this->sunset = 0.0;
	this->time_midnight = 0.0;
	this->sunrise = 0.0;
	//boost::posix_time::ptime sunset_time;
	//boost::posix_time::ptime sunrise_time;
	//length_of_day daylength;
	//solar_seasons seasons;
}

/* Constructor with user supplied latitude and longitude of the observor's position. Time is derived from the local */
/* system time and timezone. These must be correctly set in order to retreive accurate results. It will adjust for daylight savings time. */
sun::sun(const double &latitude, const double &longitude)
{
	/* Initialize the timezone. */
	tzset();

	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = "undefined";
	this->zone_time = NULL;
    
	/* No date/time provided, use the current system time. */
	this->utc_time = boost::posix_time::second_clock::universal_time();
	this->local_time = boost::posix_time::second_clock::local_time();
    
	set_julian(std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1));
    
	this->perform_solar_calculations();
}

sun::sun(std::string name, const double &latitude, const double &longitude)
{
	/* Initialize the timezone. */
	tzset();

	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = name;
	this->zone_time = NULL;
    
	/* No date/time provided, use the current system time. */
	this->utc_time = boost::posix_time::second_clock::universal_time();
	this->local_time = boost::posix_time::second_clock::local_time();
    
	set_julian(std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1));
    
	this->perform_solar_calculations();
}

/* Constructor with user supplied latitude and longitude along with the date, time, and timezone of the observor's position,  */
/* This will adjust for daylight savings time depending on the user's timezone. */
sun::sun(const double &latitude, const double &longitude, std::tm &timeinfo)
{
	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = "undefined";
	this->zone_time = NULL;
    
	strncpy(this->timezone, timeinfo.tm_zone, 0x05);
	set_julian(std::mktime(&timeinfo));
    
	this->perform_solar_calculations();
}

/* Constructor with user supplied latitude and longitude along with the date, time, and timezone of the observor's position,  */
/* This will adjust for daylight savings time depending on the user's timezone. */
sun::sun(std::string name, const double &latitude, const double &longitude, std::tm &timeinfo)
{
	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = name;
	this->zone_time = NULL;
    
	strncpy(this->timezone, timeinfo.tm_zone, 0x05);
	set_julian(std::mktime(&timeinfo));
    
	this->perform_solar_calculations();
}

sun::sun(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo)
{
	using namespace date;
	using namespace std;
	using namespace std::chrono;
    
	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = name;
	this->zone_time = &timeinfo;
    
	int current_year = (date::year_month_day{ date::floor<date::days>(timeinfo.get_local_time()) }.year() - 0_y).count();
    
	int year = current_year;

	set_julian(timeinfo);
    
	this->perform_solar_calculations();
}

sun::~sun()
{
}

void sun::set_julian(unsigned long epoch)
{
	this->time_epoch = epoch;
	this->julian = calculate_julian_time(this->time_epoch, true);
	this->julian_century = calculate_julian_century(this->julian);
}

void sun::set_julian(zoned_sun_time &timeinfo)
{
	this->julian = calculate_julian_time(timeinfo, true);
	this->julian_century = calculate_julian_century(this->julian);
}

void sun::set(const double &latitude, const double &longitude, std::tm &timeinfo)
{
	this->set("undefined", latitude, longitude, timeinfo);
}

void sun::set(std::string name, const double &latitude, const double &longitude, std::tm &timeinfo)
{
	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = name;
	this->zone_time = NULL;
    
	strncpy(this->timezone, timeinfo.tm_zone, 0x05);
	set_julian(std::mktime(&timeinfo));
    
	this->utc_offset = get_offset_from_UTC(true) * 60.0;
	this->perform_solar_calculations();
}

void sun::set(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo)
{
	this->set(name, latitude, longitude, timeinfo, false);
}

void sun::set(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo, bool irrad)
{
	this->observer_latitude = latitude;
	this->observer_longitude = longitude;
	this->name = name;
	this->zone_time = &timeinfo;
    
	set_julian(timeinfo);
    
	this->utc_offset = get_offset_from_UTC(true) * 60.0;
	this->perform_solar_calculations();
}

void sun::operator()(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo)
{
	this->set(name, latitude, longitude, timeinfo, false);
}

void sun::operator()(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo, bool irrad)
{
	this->set(name, latitude, longitude, timeinfo, irrad);
}


void sun::perform_solar_calculations()
{
	/* Perform the calculations. */
	/* All of this to get the sunrise and sunset times, phew :) */
	this->geom_mean_longitude = calculate_mean_geom_longitude(this->julian_century);
	this->geom_mean_anomoly = calculate_mean_geom_anomoly(this->julian_century);
	this->eccentric_earth_orbit = calculate_eccentric_earth_orbit(this->julian_century);
	this->sun_center = calculate_center_of_sun(this->julian_century, this->geom_mean_anomoly);
	this->true_longitude = calculate_true_longitude(this->sun_center, this->geom_mean_longitude);
	this->true_anomoly = calculate_true_anomoly(this->sun_center, this->geom_mean_anomoly);
	this->rad_vector = calculate_rad_vector(this->true_anomoly, this->eccentric_earth_orbit);
	this->apparent_longitude = calculate_apparent_longitude(this->julian_century, this->true_longitude);
	this->mean_obliquity_ecliptic = calculate_mean_obliquity_ecliptic(this->julian_century);
	this->mean_obliquity_correction = calculate_obliquity_correction(this->julian_century, this->mean_obliquity_ecliptic);
	this->right_ascension = calculate_right_ascension(this->apparent_longitude, this->mean_obliquity_correction);
	this->declincation = calculate_declination(this->apparent_longitude, this->mean_obliquity_correction);
	this->EoT = calculate_EoT(this->mean_obliquity_correction, this->geom_mean_longitude, this->geom_mean_anomoly, this->eccentric_earth_orbit);
	this->sunrise_hour_angle = calculate_sunrise_hour_angle(this->observer_latitude, this->declincation);
	this->sunset_hour_angle = calculate_sunset_hour_angle(this->sunrise_hour_angle);
	this->solar_noon = calculate_solar_noon(this->observer_longitude, this->EoT, this->utc_offset);
	this->sunrise = calculate_sunrise_time(this->solar_noon, this->sunrise_hour_angle);
	this->sunset  = calculate_sunset_time(this->solar_noon, this->sunrise_hour_angle);
	
	/* Calculate other metrics */
	this->daylength = calculate_daylength(sunrise_hour_angle);
	/* True solar time / apparent solar time */
	this->time_midnight = time_since_midnight(this->zone_time);
	this->solar_time = calculate_solar_time(this->observer_longitude, this->time_midnight, this->EoT, this->utc_offset);
	/* Hour angle and zenith angle */
	this->hour_angle = calculate_hour_angle(this->solar_time);
	this->sec_z_inverse = calculate_inverse_secant_z(this->observer_latitude, this->declincation, this->hour_angle);
	this->zenith_angle = calculate_zenith_angle(this->sec_z_inverse);
	/* This is the true solar elevation without refraction. */
	this->solar_elevation = calculate_solar_elevation(this->zenith_angle);
	/* The following is what the observor would experience due to atmospheric refraction. Apparent elevation. */
	this->atmospheric_refraction = calculate_atmospheric_refraction(this->solar_elevation);
	this->solar_elevation_corrected = this->solar_elevation + this->atmospheric_refraction;
	    
	this->solar_azimuth_angle = calculate_solar_azimuth_angle(this->observer_latitude, this->zenith_angle, this->hour_angle, this->declincation);
	   
	/* Save some interesting values to easily utilized formats. */
	/* Any other values are accessible via class accessors. */
	this->sunrise_time = float_to_ptime(this->sunrise);
	this->sunset_time = float_to_ptime(this->sunset);
	    
	/* Avoid performing the calculation at this point since it slows down the class construction. */
	//set_length_of_seasons(this->zone_time);
}

/* Reduced set of calculation for irradiation calculations. */
void sun::perform_solar_calculations_irrad()
{
	/* Placeholder. */
}

boost::posix_time::ptime sun::float_to_ptime(double value)
{
	boost::posix_time::ptime postime;
    
	tm test;
	test.tm_year = 2018 - 1900; 
	test.tm_mon = 1;
	test.tm_mday = 2;
    
	postime = boost::posix_time::from_time_t(this->time_epoch);
    
	value = value * 24.0;
	int hours = (int)(value);
	value -= hours;
	value = value * 60.0;
	int minutes = (int)(value);
	value -= minutes;
	value = value * 60.0;
	int seconds = (int)(value);
	value -= seconds;
	value = value * 1000.0;
	int milliseconds = (int)(value);
    
	test.tm_mday = postime.date().day();
	test.tm_year = postime.date().year() - 1900;
	test.tm_mon = postime.date().month() - 1;
	test.tm_yday = postime.date().day_of_year();
	test.tm_hour = hours;
	test.tm_min = minutes;
	test.tm_sec = seconds;
	test.tm_zone = this->timezone;
    
	postime = boost::posix_time::ptime_from_tm(test);
    
	return (postime);
}

/* Calculation of the solar angle between current solar angle and solar noon in radians. Input is the solar time in hours. Output is in degrees. */
double sun::calculate_hour_angle(double solar_time)
{
	double time = solar_time * (MINUTES_DAY);
    
	if ((time / 4.0) < 0)
	{
		hour_angle = (time / 4.0) + 180.0;
	}
	else
	{
		hour_angle = (time / 4.0) - 180.0;
	}
    
	return (hour_angle);
}


/* Julian centuries since Equinox J2000. J2000 is the julian date with 0 set to 12 noon January 1, 2000 */
/* this is due to the Precession of Equinoxes affect on the reference systems. The earth has a a precession */
/* "wobble" (nutation) with a cycle time of 26K years. J2000 references this effect as of the date of 1/1/2000. */
/* Verified */
double sun::calculate_julian_time(double time, bool unix_time)
{
	double julian;
    
	/* Calculate the Julian date */
	if (unix_time == true) 
	{
		julian = (time / SECONDS_DAY) + UNIX_JULIAN_EPOCH;
	}
	else 
	{
		julian = (time / SECONDS_DAY);
	}
    
	return (julian);
}

double sun::calculate_julian_time(zoned_sun_time &timeinfo, bool unix_time)
{
	this->time_epoch = (timeinfo.get_sys_time()).time_since_epoch().count() / 1000000000.0;
	double julian = calculate_julian_time(time_epoch, unix);
    
	return (julian);
}

/* Julian centuries since J2000 */
/* Verified */
double sun::calculate_julian_century(double julian)
{
	/* Calculate the Julian century */
	double julian_century = (julian - J2000) / (JULIAN_DAYS_CENTURY);
    
	return (julian_century);
}

/* Calculate the geometric mean longitude, degrees */
/* Verified */
double sun::calculate_mean_geom_longitude(double julian_century)
{
	double geom_mean = 280.46646 + julian_century*(36000.76983 + julian_century * 0.0003032);
	if (geom_mean < 0) geom_mean += 360;
	else if (geom_mean > 360) geom_mean = fmod(geom_mean, 360);  
    
	return (geom_mean);
}

/* Calculate the geometric anomoly, degrees */
/* Note, need to compare with "Calendrical Calculations: The Ultimate Edition", Reingold. NOAA factors differ. */
double sun::calculate_mean_geom_anomoly(double julian_century)
{
	double geom_anomoly = 357.52911 + julian_century * ((35999.05029) - (0.0001537 * julian_century));
    
	return (geom_anomoly);
}

/* Calculate the earth orbit eccentricity. Return is floating point factor. */
/* Note, need to compare with "Calendrical Calculations: The Ultimate Edition", Reingold. NOAA factors differ. */
double sun::calculate_eccentric_earth_orbit(double julian_century)
{
	double eccentric_earth = 0.016708634 - julian_century * (0.000042037 + 0.0000001267 * julian_century);
    
	return (eccentric_earth);
}

/* Calculate the center of the sun in degrees. */
double sun::calculate_center_of_sun(double julian_century, double geom_anomoly)
{
	double geom_anomoly_radians = TO_RADIAN(geom_anomoly);

	double sun_center = (sin(geom_anomoly_radians) * (1.914602 - julian_century * (0.004817 + 0.000014 * julian_century))) 
	    + (sin(geom_anomoly_radians * 2.0) * (0.019993 - 0.000101 * julian_century)) 
	    + (sin(geom_anomoly_radians * 3.0) * 0.000289);
    
	return (sun_center);
}

/* Calculate true longitude using center of sun angle adjustment. */
double sun::calculate_true_longitude(double sun_center, double geom_mean)
{
	double true_longitude = geom_mean + sun_center;
    
	return (true_longitude);
}

/* Calculate true anomoly using center of sun angle adjustment. */
double sun::calculate_true_anomoly(double sun_center, double geom_anomoly)
{
	double true_anomoly = geom_anomoly + sun_center;
    
	return (true_anomoly);
}

/* Calculate the distance to the sun. Results in astronomical units (AU) */
double sun::calculate_rad_vector(double true_anomoly, double eccentric_earth)
{
	double rad_vector = (1.000001018*(1.0 - eccentric_earth*eccentric_earth)) / (1.0 + eccentric_earth*cos(TO_RADIAN(true_anomoly)));
    
	return (rad_vector);
}

double sun::calculate_apparent_longitude(double julian_century, double true_longitude)
{
	double apparent_longitude = (true_longitude - 0.00569);
	apparent_longitude -= (0.00478*sin(TO_RADIAN(125.04 - (1934.136 * julian_century))));
    
	return (apparent_longitude);
}

/* Calculate the mean obliquity of the ecliptic. Return is in degrees. */
/* The equator is inclined at 23 degees, 26 minuts, and 21.448 seconds with respect to the earth's plane of rotation (the ecliptic) around the sun. */
/* This inclination (the obliquity) has a cycle that varies over 100K years a couple of degrees. We calculate the variation, here. */
/* Verified */
double sun::calculate_mean_obliquity_ecliptic(double julian_century)
{
	double mean_obliquity = 23.0 + (26.0 + ((21.448 - julian_century*(46.815 + julian_century*(0.00059 - julian_century * 0.001813)))) / 60.0) / 60.0;

	return (mean_obliquity);
}

/* Calculate the corrected mean obliquity of the ecliptic. Return is in degrees. */
double sun::calculate_obliquity_correction(double julian_century, double mean_obliquity)
{
	double obliquity_correction = mean_obliquity + 0.00256*cos(TO_RADIAN(125.04 - 1934.136*julian_century));
    
	return (obliquity_correction);
}

/* Calculate the right ascention. Return is in degrees. */
double sun::calculate_right_ascension(double apparent_longitude, double obliquity_correction)
{
	double right_ascension = TO_DEGREE(atan2(cos(TO_RADIAN(obliquity_correction))*sin(TO_RADIAN(apparent_longitude)), cos(TO_RADIAN(apparent_longitude))));
    
	return (right_ascension);
}

/* Calculate the solar declination. Return is in degrees. */
double sun::calculate_declination(double apparent_longitude, double obliquity_correction)
{
	double declination = TO_DEGREE(asin(sin(TO_RADIAN(obliquity_correction))*sin(TO_RADIAN(apparent_longitude))));
    
	return (declination);
}


/* Calculation of the approximate equation of time (correction) for the difference between mean and apparent solar time. */
/* Results in floating point minutes. */
double sun::calculate_EoT(double obliquity_correction, double geom_mean_longitude, double geom_mean_anomoly, double eccentric_earth_orbit)
{
	double tan_y = tan(TO_RADIAN(obliquity_correction / 2.0));
	double y = tan_y*tan_y;
	double geom_mean_longitude_radian = 2.0*TO_RADIAN(geom_mean_longitude);
	double geom_mean_anomoly_radian = TO_RADIAN(geom_mean_anomoly);
	double sin_anomoly = sin(geom_mean_anomoly_radian);
    
	double EoT1 = (y*sin(geom_mean_longitude_radian));
	double EoT2 = (2.0*eccentric_earth_orbit*sin_anomoly);
	double EoT3 = (4.0*eccentric_earth_orbit*y*sin_anomoly*cos(geom_mean_longitude_radian));
	double EoT4 = (0.5*y*y*sin(2*geom_mean_longitude_radian));
	double EoT5 = (1.25*eccentric_earth_orbit*eccentric_earth_orbit*sin(2.0*geom_mean_anomoly_radian));
    
	double EoT = EoT1 - EoT2 + EoT3 - EoT4 - EoT5;

	return (4.0*TO_DEGREE(EoT));
}


/* Calculation the local solar time of sunrise. Return is in floating point hours from noon. */
double sun::calculate_sunrise_time(double solar_noon, double hour_angle_sunrise)
{
	double sunset = solar_noon - ((hour_angle_sunrise * 4.0) / (MINUTES_DAY));
    
	return (sunset);
}

/* Calculation the local solar time of sunset. Return is in floating point hours from noon. */
double sun::calculate_sunset_time(double solar_noon, double hour_angle_sunrise)
{
	double sunset = solar_noon + ((hour_angle_sunrise * 4.0) / (MINUTES_DAY));
    
	return (sunset);
}


/* Calculate the number of hour of sunlight. Return is in floating point hours. */
double sun::calculate_daylength(double sunrise_hour_angle)
{
	return ((8.0 * sunrise_hour_angle) / (SECONDS_HOUR));
}

/* Calculation of the solar hour angle from the zenith. Output in degrees. */
double sun::calculate_hour_angle(float latitude, double declination)
{	
	double hour_angle = TO_DEGREE((cos(TO_RADIAN(90.8333)) - sin(TO_RADIAN(latitude))*sin(TO_RADIAN(declination))) / (cos(TO_RADIAN(latitude))*cos(TO_RADIAN(declination))));
	
	return (hour_angle);
}

/* Calculation of the solar angle at sunrise. Output in degrees. */
double sun::calculate_sunrise_hour_angle(float latitude, double declination)
{
	double latitude_radians = TO_RADIAN(latitude);
	double declination_radians = TO_RADIAN(declination);
	double tan_angle = tan(latitude_radians)*tan(declination_radians);
	double cos_angle = cos(latitude_radians)*cos(declination_radians);
	double sunrise = cos(TO_RADIAN(90.8333)) / (cos_angle);
	sunrise = acos(sunrise - tan_angle);
	sunrise = TO_DEGREE(sunrise);
	if (isnanf(sunrise)) 
	{
		if (tan_angle < 0) sunrise = 0.0; /* No sunrise. */
		else sunrise = 180.0; /* No sunset. */
	}
	
	return (sunrise);
}

double sun::calculate_sunset_hour_angle(double sunrise_hour_angle)
{
	double sunset = (-1.0) * sunrise_hour_angle;
    
	return (sunset);
}

double sun::calculate_solar_noon(double observer_longitude, double EoT, double utc_offset)
{
	double solar_noon = ((720.0 - (4.0 *  observer_longitude) - EoT) + (utc_offset));
	solar_noon = solar_noon / (MINUTES_DAY);
    
	return (solar_noon);
}

/* Calculation of the solar time from the local time. Input is the local time in float days. Return is in floating point days. */
double sun::calculate_solar_time(double local_longitude, double time, double EoT, double utc_offset)
{
	double solar_time = (time * (MINUTES_DAY));
	solar_time += EoT;
	solar_time += (4.0*local_longitude);
	solar_time -= (utc_offset);
    
	if (solar_time > (MINUTES_DAY)) 
	{
		solar_time = fmod(solar_time, (MINUTES_DAY));
	}
    
	return (solar_time / (MINUTES_DAY));
}

double sun::calculate_zenith_angle(double sec_z_inverse)
{
    
	double zenith = TO_DEGREE(acos(TO_RADIAN(sec_z_inverse)));
    
	return (zenith);
}

double sun::calculate_inverse_secant_z(double observer_latitude, double declincation, double hour_angle)
{    
	double secant_z_inverse = TO_DEGREE(sin(TO_RADIAN(observer_latitude))*sin(TO_RADIAN(declincation)) + cos(TO_RADIAN(observer_latitude))*cos(TO_RADIAN(declincation))*cos(TO_RADIAN(hour_angle)));
    
	return (secant_z_inverse);
}


double sun::calculate_solar_elevation(double zenith_angle)
{
	double elevation = 90.0 - zenith_angle;
    
	return (elevation);
}

/* Calculate the estimated refraction of light due to the atmospehere based on the solar elevation. This is an approximation. */
/* Zimmerman, John C.  1981.  Sun-pointing programs and their accuracy. */
double sun::calculate_atmospheric_refraction(double elevation)
{
	double refraction;
    
	if (elevation > 85.0)
	{
		refraction = 0.0;
	}
	else if (elevation > 5.0)
	{
		refraction = 58.1 / tan(TO_RADIAN(elevation)) - 0.07 / pow(tan(TO_RADIAN(elevation)), 3) + 0.000086 / pow(tan(TO_RADIAN(elevation)), 5);
	}
	else if (elevation > -0.575)
	{
		refraction = 1735.0 + elevation*(-518.2 + elevation*(103.4 + elevation*(-12.79 + elevation * 0.711)));
	}
	else
	{
		refraction = -20.772 / tan(TO_RADIAN(elevation));
	}
  
	return (refraction / (SECONDS_HOUR));
}

double sun::calculate_solar_azimuth_angle(double observer_latitude, double zenith, double hour_angle, double declination)
{
    
	double azimuth;
	if (hour_angle > 0)
	{
		azimuth = TO_DEGREE(acos(((sin(TO_RADIAN(observer_latitude))*cos(TO_RADIAN(zenith))) - sin(TO_RADIAN(declination))) / (cos(TO_RADIAN(observer_latitude))*sin(TO_RADIAN(zenith))))) + 180.0;
	}
	else
	{
		azimuth = 540.0 - TO_DEGREE(acos(((sin(TO_RADIAN(observer_latitude))*cos(TO_RADIAN(zenith))) - sin(TO_RADIAN(declination))) / (cos(TO_RADIAN(observer_latitude))*sin(TO_RADIAN(zenith)))));
	}
    
	if (azimuth > 360.0) azimuth = fmod(azimuth, 360.0);

	return (azimuth);
}


double sun::tune_soltice_equinox(double julian_estimate, double degrees)
{
	double correction = 0;
	double julian_century, geom_mean_longitude, geom_mean_anomoly, sun_center, true_longitude, apparent_longitude;
    
	do
	{
		/* Recalculate the sun position for each correction. */
		julian_century = calculate_julian_century(julian_estimate);
		geom_mean_longitude = calculate_mean_geom_longitude(julian_century);
		geom_mean_anomoly = calculate_mean_geom_anomoly(julian_century);
		sun_center = calculate_center_of_sun(julian_century, geom_mean_anomoly);
		true_longitude = calculate_true_longitude(sun_center, geom_mean_longitude);
		apparent_longitude = calculate_apparent_longitude(julian_century, true_longitude);
		correction = 58.0 * sin(TO_RADIAN(degrees - apparent_longitude));  
		julian_estimate += correction;
        
	} while (fabs(correction) > 0.00005); 
    
	return (julian_estimate);
    
}

/* Calculation of the earth nutation. Return is in degrees. */
double sun::calculate_earth_nutation(double julian_century)
{
	double c2 = julian_century * julian_century;
	double A = 124.90 - (1934.134 * julian_century) + (0.002063 * c2);
	double B = 201.11 + (72001.5377 * julian_century) + (0.00057 * c2);
    
	double nutation = TO_DEGREE(-0.004778 * sin(TO_RADIAN(A))) - (0.0003667 * sin(TO_RADIAN(B)));
    
	return (nutation);
}

void sun::calculate_soltice_equinox(zoned_sun_time *timeinfo, equinox_soltices_p solar_seasons)
{
	unsigned int year_int = ((date::year_month_day{ date::floor<date::days>(timeinfo->get_local_time()) }.year() - date::year{ 0 }).count());

	double julian_nw_equinox = 0;
	double julian_sw_equinox = 0;
	double julian_n_solstice = 0;
	double julian_s_solstice = 0;

	/* Astronomical Algorithms by Jean Meeus, (c) 1991 by Willman-Bell, Inc. */
	if (year_int <= 1000)
	{
		double year = (year_int) / 1000.0;
		double year2 = year*year;
		double year3 = year2*year;
		double year4 = year3*year;
		julian_nw_equinox = 1721139.29189 + 365242.13740*year + 0.06134*year2 + 0.00111*year3 - 0.00071*year4;
		julian_sw_equinox = 1721325.70455 + 365242.49558*year - 0.11677*year2 - 0.00297*year3 + 0.00074*year4;
		julian_n_solstice = 1721233.25401 + 365241.72562*year - 0.05323*year2 + 0.00907*year3 + 0.00025*year4;
		julian_s_solstice = 1721414.39987 + 365242.88257*year - 0.00769*year2 - 0.00933*year3 - 0.00006*year4;
	}
	else
	{
		double year = (year_int - 2000) / 1000.0;
		double year2 = year*year;
		double year3 = year2*year;
		double year4 = year3*year;
		julian_nw_equinox = 2451623.80984 + 365242.37404*year + 0.05169*year2 - 0.00411*year3 - 0.00057*year4;
		julian_sw_equinox = 2451810.21715 + 365242.01767*year - 0.11575*year2 + 0.00337*year3 + 0.00078*year4;
		julian_n_solstice = 2451716.56767 + 365241.62603*year + 0.00325*year2 + 0.00888*year3 - 0.00030*year4;
		julian_s_solstice = 2451900.05952 + 365242.74049*year - 0.06223*year2 - 0.00823*year3 + 0.00032*year4;
	}   

	julian_nw_equinox = tune_soltice_equinox(julian_nw_equinox, 0.0);
	julian_n_solstice = tune_soltice_equinox(julian_n_solstice, 90.0);
	julian_sw_equinox = tune_soltice_equinox(julian_sw_equinox, 180.0);
	julian_s_solstice = tune_soltice_equinox(julian_s_solstice, 270.0);
    
	solar_seasons->julian_nw_equinox = from_julian_date(julian_nw_equinox);
	solar_seasons->julian_sw_equinox = from_julian_date(julian_sw_equinox);
	solar_seasons->julian_n_solstice  = from_julian_date(julian_n_solstice);
	solar_seasons->julian_s_solstice  = from_julian_date(julian_s_solstice);
}

void sun::set_length_of_seasons(zoned_sun_time *timeinfo)
{
	equinox_soltices_t solar_seasons, solar_seasons_next; 
    
	/* Determine the solar seasons for this year.*/
	calculate_soltice_equinox(timeinfo, &solar_seasons);
    
	/* Determine the soloar seasons for the enxt year.*/
	std::chrono::duration<long long> tf(date::years{ 1 });
	auto next_year = timeinfo->get_local_time() + tf;
	zoned_sun_time timeinfo_next = date::make_zoned(timeinfo->get_time_zone(), next_year);
	calculate_soltice_equinox(&timeinfo_next, &solar_seasons_next);
    
	bool northern_hemisphere = this->observer_latitude > 0 ? (true) : (false);
	if (northern_hemisphere)
	{
		this->seasons.LengthOfSpring = (solar_seasons.julian_n_solstice.get_sys_time() - solar_seasons.julian_nw_equinox.get_sys_time());
		this->seasons.LengthOfSummer = (solar_seasons.julian_sw_equinox.get_sys_time() - solar_seasons.julian_n_solstice.get_sys_time());
		this->seasons.LengthOfAutumn = (solar_seasons.julian_s_solstice.get_sys_time() - solar_seasons.julian_sw_equinox.get_sys_time());
		this->seasons.LengthOfWinter = (solar_seasons_next.julian_nw_equinox.get_sys_time() - solar_seasons.julian_s_solstice.get_sys_time());
	}
	else
	{
		this->seasons.LengthOfSpring = (solar_seasons.julian_s_solstice.get_sys_time() - solar_seasons.julian_sw_equinox.get_sys_time());
		this->seasons.LengthOfSummer = (solar_seasons_next.julian_nw_equinox.get_sys_time() - solar_seasons.julian_s_solstice.get_sys_time());
		this->seasons.LengthOfAutumn = (solar_seasons.julian_n_solstice.get_sys_time() - solar_seasons.julian_nw_equinox.get_sys_time());
		this->seasons.LengthOfWinter = (solar_seasons.julian_sw_equinox.get_sys_time() - solar_seasons.julian_n_solstice.get_sys_time());
	}	
    
	this->seasons.julian_nw_equinox = solar_seasons.julian_nw_equinox;
	this->seasons.julian_sw_equinox = solar_seasons.julian_sw_equinox;
	this->seasons.julian_n_solstice = solar_seasons.julian_n_solstice;
	this->seasons.julian_s_solstice = solar_seasons.julian_s_solstice;
    
}

double sun::time_since_midnight(zoned_sun_time *timeinfo)
{
	auto timeinfo_copy = this->zone_time;
	auto timeinfo_local = timeinfo_copy->get_local_time();
	auto zero_hour = date::make_zoned(timeinfo_copy->get_time_zone(), date::floor<date::days>(timeinfo_local));
	unsigned long zero_hour_epoch = zero_hour.get_local_time().time_since_epoch().count();
	unsigned long seconds_since_midnight_epoch = timeinfo_local.time_since_epoch().count() / 1000000000;
	double time = (seconds_since_midnight_epoch - zero_hour_epoch);
	time = time / (SECONDS_DAY);
    
	if (time <= 0) time = 1.0;
    
	return (time);
}

zoned_sun_time sun::from_julian_date(double julian)
{
	time_t timez;
	struct tm *p;
    
	/* Convert the julian time to unix time. */
	timez = (julian - UNIX_JULIAN_EPOCH)*SECONDS_DAY;
	p = gmtime(&timez);
    
	/* Daylight savings time. */
	std::string timezone_string = this->zone_time->get_time_zone()->name();
    
	/* Convert this to zone time, associated it to UTC then convert to the timezone of the user's operation. */
	date::sys_seconds t_sec = to_sys_time(*p);
	auto utc = date::make_zoned("UTC", t_sec);
	auto ny3 = date::make_zoned(timezone_string, utc);
    
	return (ny3);
}

date::local_seconds sun::to_local_time(std::tm const& t)
{
	using namespace date;
	using namespace std::chrono; 
	return (local_days{ year{ t.tm_year + 1900 } / (t.tm_mon + 1) / t.tm_mday } + hours{ t.tm_hour } + minutes{ t.tm_min } + seconds{ t.tm_sec });
}

date::sys_seconds sun::to_sys_time(std::tm const& t)
{
	using namespace date;
	using namespace std::chrono; 
	return (sys_days{ year{ t.tm_year + 1900 } / (t.tm_mon + 1) / t.tm_mday } + hours{ t.tm_hour } + minutes{ t.tm_min } + seconds{ t.tm_sec });
}

chrono_duration sun::fp_days_to_chrono(double fp_days)
{
	double hms_time = (fp_days * 24.0); 
	auto time = std::chrono::hours((unsigned int)hms_time);
    
	hms_time -= (unsigned int)hms_time;
	hms_time = hms_time * 60.0;
	auto time_hm = time + std::chrono::minutes((unsigned int)hms_time);
    
	hms_time -= (unsigned int)hms_time;
	hms_time = hms_time * 60.0;
	auto time_hms = time_hm + std::chrono::seconds((unsigned int)hms_time);
    
	fp_days -= (unsigned int)hms_time;
	hms_time = hms_time * 1000.0;
	auto time_hmsm = time_hms + std::chrono::milliseconds((unsigned int)hms_time);
    
	return (time_hms);
    
}



double sun::get_offset_from_UTC(bool adjust_for_dst)
{
	double offsetFromUTC;
    
	if (this->zone_time != NULL)
	{  
		auto info = this->zone_time->get_info();
		offsetFromUTC = info.offset.count() / (SECONDS_HOUR);
		if ((adjust_for_dst) && (info.save != std::chrono::minutes{ 0 })) offsetFromUTC = offsetFromUTC - 1;
	}
	else
	{
		time_t currtime;
		struct tm * timeinfo;

		/* Update the OS specific timezone information. */
		tzset();

		time(&currtime);
		timeinfo = gmtime(&currtime);
		time_t utc = mktime(timeinfo);
		timeinfo = localtime(&currtime);
		time_t local = mktime(timeinfo);
    
		// Get offset in hours from UTC
		offsetFromUTC = difftime(local, utc) / (SECONDS_HOUR);

		// Adjust for DST
		if((adjust_for_dst) && (timeinfo->tm_isdst))
		{
			offsetFromUTC += 1;
		}
	}

	return offsetFromUTC;
}


