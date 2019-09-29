//
// sun.h
// Version timestamp: 9-26-2018, 10:36 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <boost/date_time.hpp>
#include <boost/variant.hpp>
#include "Conversion_Constants.h"
#include "tz.h"

typedef std::chrono::duration<long int, std::ratio<1l, 1000000000l>> time_duration;
typedef std::chrono::duration<long int, std::ratio<1l, 1l>> chrono_duration;
typedef date::zoned_time<time_duration> zoned_sun_time;
typedef std::chrono::time_point<date::local_t, chrono_duration> chrono_sun_time;

typedef struct
{
    zoned_sun_time julian_nw_equinox;
    zoned_sun_time julian_sw_equinox;
    zoned_sun_time julian_n_solstice;
    zoned_sun_time julian_s_solstice;
    time_duration LengthOfSpring;
    time_duration LengthOfSummer;
    time_duration LengthOfAutumn;
    time_duration LengthOfWinter;
} equinox_soltices_t, *equinox_soltices_p;


class sun_time
{
public:
    sun_time() {}
    ~sun_time() {}	
    
    bool *require_update;
    zoned_sun_time solar_time;
    zoned_sun_time operator()() {return solar_time;}
    zoned_sun_time operator=(zoned_sun_time rhs) {solar_time = rhs;}
    friend std::ostream& operator<<(std::ostream& lhs, const sun_time& rhs)
    {
        return (lhs << date::format("%b/%d/%Y %H:%M %Z", rhs.solar_time));
    }
};

class sun_duration
{
public:
    sun_duration() {}
    ~sun_duration() {}	

    time_duration solar_time;
    time_duration operator()() {return solar_time;}
    time_duration operator=(time_duration rhs) {solar_time = rhs;}
    friend std::ostream& operator<<(std::ostream& lhs, const sun_duration& rhs)
    {
        return (lhs << date::format("%H:%M", rhs.solar_time));
    }
};

class solar_seasons
{
public:
    solar_seasons() {}
    ~solar_seasons() {}
    
    sun_time julian_nw_equinox;
    sun_time julian_sw_equinox;
    sun_time julian_n_solstice;
    sun_time julian_s_solstice;
    sun_duration LengthOfSpring;
    sun_duration LengthOfSummer;
    sun_duration LengthOfAutumn;
    sun_duration LengthOfWinter;
};

class float_time
{
public:
    float_time() {}
    float_time(double value)
        : hour(value * 24.0)
        , minutes(((value * 24.0) - hour) * 60.0)
        , seconds(((value * 1440.0) - (hour * 24.0 + minutes)) * 60.0)
        , time(value) {}
    ~float_time() {}
    double operator()() {return time;}
    friend std::ostream& operator<<(std::ostream& lhs, const float_time& rhs)
    {
        return (lhs << rhs.hour << ":" << rhs.minutes << ":" << rhs.seconds << ":");
    }
    
    int hour;
    int minutes;
    int seconds;
    double time;
};

class length_of_day
{
public:
    length_of_day() {}
    length_of_day(double daylength)
        : hours(daylength * 60.0)
        , minutes(((daylength * 60.0) - hours) * 60.0)
        , seconds(((daylength * 3600.0) - (hours * 60.0 + minutes)) * 60.0)
        , length(daylength) {}
    ~length_of_day() {}
    double operator()() {return length;}
    friend std::ostream& operator<<(std::ostream& lhs, const length_of_day& rhs)
    {
        return (lhs << rhs.hours << " hours " << rhs.minutes << " minutes " << rhs.seconds << " seconds");
    }
    
    int hours;
    int minutes;
    int seconds;
    double length;
};


typedef boost::variant<date::days, std::chrono::hours, std::chrono::minutes, std::chrono::seconds> sun_time_variant;
class sun
{
public:
    sun();
    sun(const double &latitude, const double &longitude);
    sun(std::string name, const double &latitude, const double &longitude);
    sun(const double &latitude, const double &longitude, std::tm &timeinfo);
    sun(std::string name, const double &latitude, const double &longitude, std::tm &timeinfo);
    sun(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo);
    ~sun();
	double operator+(sun_time_variant time); 
	double operator-(sun_time_variant time);
	double operator+=(sun_time_variant time); 
	double operator-=(sun_time_variant time);
    void set(const double &latitude, const double &longitude, std::tm &timeinfo);
    void set(std::string name, const double &latitude, const double &longitude, std::tm &timeinfo);
    void set(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo);
	void set(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo, bool irrad);
	void operator()(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo);
	void operator()(std::string name, const double &latitude, const double &longitude, zoned_sun_time &timeinfo, bool irrad);
    void perform_solar_calculations();
	void perform_solar_calculations_irrad();
    void set_julian(unsigned long epoch);
    void set_julian(zoned_sun_time &timeinfo);
    double calculate_julian_time(double time, bool unix_time);
    double calculate_julian_time(zoned_sun_time &timeinfo, bool unix_time);
    double calculate_julian_century(double julian);
    double calculate_mean_geom_longitude(double julian_century);
    double calculate_mean_geom_anomoly(double julian_century);
    double calculate_eccentric_earth_orbit(double julian_century);
    double calculate_center_of_sun(double julian_century, double geom_anomoly);
    double calculate_true_longitude(double geom_mean, double geom_anomoly);
    double calculate_true_anomoly(double sun_center, double geom_anomoly);
    double calculate_rad_vector(double true_anomoly, double eccentric_earth);
    double calculate_apparent_longitude(double julian_century, double true_longitude);
    double calculate_mean_obliquity_ecliptic(double julian_century);
    double calculate_obliquity_correction(double julian_century, double mean_obliquity_ecliptic);
    double calculate_right_ascension(double apparent_longitude, double obliquity_correction);
    double calculate_declination(double apparent_longitude, double obliquity_correction);
	double calculate_solar_noon(double observer_longitude, double EoT, double utc_offset);
    double calculate_hour_angle(double solar_time);
	double calculate_solar_time(double local_longitude, double time, double EoT, double utc_offset);
    double calculate_EoT(double obliquity_correction, double geom_mean_longitude, double geom_mean_anomoly, double eccentric_earth_orbit);
    double calculate_sunset_time(double solar_noon, double hour_angle_sunrise);
    double calculate_sunrise_time(double solar_noon, double hour_angle_sunrise);
	double calculate_hour_angle(float latitude, double declination);
    double calculate_sunrise_hour_angle(float latitude, double declination);
	double calculate_sunset_hour_angle(double sunrise_hour_angle);
    double calculate_daylength(double sunrise_hour_angle);
    double calculate_zenith_angle(double sec_z_inverse);
	double calculate_inverse_secant_z(double observer_latitude, double declincation, double hour_angle);
    double calculate_solar_elevation(double zenith_angle);
    double calculate_solar_azimuth_angle(double observer_latitude, double zenith, double hour_angle, double declination);
    double calculate_atmospheric_refraction(double elevation);
    double calculate_earth_nutation(double julian_century);
    double tune_soltice_equinox(double julian_estimate, double degrees);
    void calculate_soltice_equinox(zoned_sun_time *timeinfo, equinox_soltices_p solar_seasons);
    void set_length_of_seasons(zoned_sun_time *timeinfo);

	double time_since_midnight(zoned_sun_time *timeinfo);
    double get_offset_from_UTC(bool adjust_for_dst);
    boost::posix_time::ptime float_to_ptime(double value);
    zoned_sun_time from_julian_date(double julian);
    date::local_seconds to_local_time(std::tm const& t);
    date::sys_seconds to_sys_time(std::tm const& t);
	chrono_duration fp_days_to_chrono(double fp_days);
    
    std::string name;
    zoned_sun_time *zone_time;
	double utc_offset;
    float observer_longitude;
    float observer_latitude;
    double julian;
    double julian_century;
    double geom_mean_longitude;
    double geom_mean_anomoly;
    double eccentric_earth_orbit;
    double sun_center;
    double true_longitude;
    double true_anomoly;
    double rad_vector;
    double apparent_longitude;
    double mean_obliquity_ecliptic;
    double mean_obliquity_correction;
    double right_ascension;
    double sunrise_hour_angle;
	double sunset_hour_angle;
    double hour_angle;
	double sec_z_inverse;
    double zenith_angle;
    double solar_elevation;
    double declincation;
    double solar_azimuth_angle;
    double atmospheric_refraction;
    double solar_elevation_corrected;
    double EoT;
    double solar_time;
    double solar_noon;
    double sunset;
	double time_midnight;
    boost::posix_time::ptime sunset_time;
    double sunrise;
    boost::posix_time::ptime sunrise_time;
    length_of_day daylength;
    solar_seasons seasons;
    
private:
    boost::posix_time::ptime local_time;
    boost::posix_time::ptime utc_time;
    std::time_t time_epoch;
    char timezone[8];
    boost::posix_time::time_duration timezone_offset; 
};

//date::days, std::chrono::hours, std::chrono::minutes, std::chrono::seconds
//struct Nil {};
//class sun_varient : boost::static_visitor<sun> 
//{
//public:
//	sun operator()(date::years time)			const { return "double"; }
//	sun operator()(date::months time)			const { return "char const*"; }
//	sun operator()(date::days time)				const { return "long"; }
//	sun operator()(std::chrono::hours time)		const { return "float"; }
//	sun operator()(std::chrono::minutes time)   const { return "int"; }
//    
//	template<typename T>
//		std::string operator()(T const&)    const { throw "Not implemented"; } // TODO proper exception
//};

