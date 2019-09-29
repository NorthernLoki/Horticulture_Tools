//
// bird.h
// Version timestamp: 9-30-2018, 7:31 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <math.h>
#include "Conversion_Constants.h"

class bird
{
public:
	bird();
	bird(double solar_elevation, double ic_prime, double relative_optical_path, double air_pressure, double ozone_cm, double h2o_cm, double depth_380nm, double depth_500nm, double Ba, double tau_aerosol, double albedo);
	~bird();
	
	double absolute_air_mass(double relative_optical_path);
	double absolute_air_mass(double relative_optical_path, double air_pressure);
	double calculate_plane_surface_angle(double solar_zenith);
	double calculate_incident_surface_irradiation(double solar_elevation);
	
	/* Bird */
	double calculate_aerosol_taua(double depth_380nm, double depth_500nm);
	double calculate_aerosol_depth(double relative_optical_path, double depth_380nm, double depth_500nm);
	double calculate_rayleigh_scattering(double relative_optical_path, double air_pressure);
	double calculate_ozone_depth(double relative_optical_path, double ozone_cm);
	double calculate_mixed_gas_depth(double relative_optical_path, double air_pressure);
	double calculate_h20_depth(double relative_optical_path, double air_pressure);
	double calculate_aerosol_depth(double relative_optical_path, double air_pressure);
	double calculate_taa(double aerosol_tranmittance, double relative_air_mass);
	double calculate_rs(double aerosol_tranmittance, double taa, double Ba);
	double calculate_rs(double aerosol_tranmittance, double taa);
	double calculate_tas(double relative_optical_path, double rayleigh_transmittance, double aerosol_transmittance, double ozone_transmittance, double h2o_transmittance, double mixed_transmittance, double taa, double Ba);
	double calculate_global_horizontal(double irrad_tilted, double direct_horizontal, double tas, double albedo, double rs);
	double calculate_diffuse_horizontal(double direct_horizontal, double global_horizontal);
	double calculate_direct_normal_irradiation(double aerosol_tranmittance, double h20_transmittance, double mixed_gas_transmittance, double ozone_transmittance, double rayleigh_transmittance);
	double calculate_bird(double relative_optical_path, double air_pressure, double ozone_cm, double h2o_cm, double depth_380nm, double depth_500nm, double Ba);
	double calculate_bird();
    
	/* Input parameters */
	double solar_elevation;
	double ic_prime;
	double relative_optical_path;
	double air_pressure;
	double ozone_cm;
	double h2o_cm;
	double depth_380nm;
	double depth_500nm;
	double Ba;
	double tau_aerosol;
	double albedo;
	
	/* Generated results */
	double raleigh;
	double ozone;
	double mixed;
	double h2o;
	double aerosol;
	double taa;
	double rs;
	double direct_normal;
	double direct_beam;
	double tas;
	double plane_angle;
	double irrad_horizontal;
	double direct_horizontal;
	double global_horizontal;
	double diffuse_horizontal;
	
};

