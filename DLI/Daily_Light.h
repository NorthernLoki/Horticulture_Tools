//
// Daily_Light.h
// Version timestamp: 9-30-2018, 7:42 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include "integrate.h" /* Numerical Integration Class*/
#include "sun.h" /* Solar Position Calculation Class */
#include "bird.h" /* Bird Insolation Model */
#include "ashre.h" /* ASHRE 2009, 2013 Insolation Models */

/* Air mass (optical depth) models */
enum AIR_MASS_MODEL : unsigned short
{
	AM_HARDIE,
	AM_KASTENYOUNG,
	AM_KASTEN,
	AM_PICKERING,
	AM_GUEYMARD
};

/* Insolation models */
enum ATMOSPHERIC_MODEL : unsigned short
{
	ATOM_NONE,
    ATOM_SIMPLE,
	ATOM_BIRD,
	ATOM_PEREZ,
	ATOM_INEICHEN,
	ATOM_ASHRE
};

class Daily_Light : public integrate, sun
{
public:
	Daily_Light();
	~Daily_Light();
	double calculate_dli(zoned_sun_time time, sun *sun_element);
	double calculate_dli(zoned_sun_time time, sun *sun_element, ATMOSPHERIC_MODEL atmosphere);
	double calculate_irrad(zoned_sun_time time, sun *sun_element, ATMOSPHERIC_MODEL atmosphere);
	double calculate_extraterestrial_radiation(double rad_vector);
	double calculate_incident_surface_irradiation(double normal_radiation, double solar_elevation);
	double calculate_plane_surface_angle(double solar_zenith);
	double calculate_projection(double surface_tilt, double solar_zenith, double surface_azimuth, double solar_azimuth);
	double calculate_incident_angle(double surface_tilt, double solar_zenith, double surface_azimuth, double solar_azimuth);

	double calculate_beam_transmittance_clear(double optical_air_mass, std::tuple<double, double, double> climate, double solar_elevation);
	double calculate_diffuse_radiation(double beam_transmittance);
	double optical_air_mass(double solar_elevation, double inverse_secant_zenith, double altitude, AIR_MASS_MODEL model);
	double absolute_air_mass(double relative_optical_path);
	double absolute_air_mass(double relative_optical_path, double air_pressure);

	double ic_prime;
	double relative_optical_path;
	double beam_transmittance;
	double diffuse_radiation;
	double irrad_tilted;
	double irrad;
	double ppfd;
	
	double direct_normal;
	double direct_horizontal;
	double global_horizontal;
};
