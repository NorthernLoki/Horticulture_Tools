//
// bird.cpp
// Version timestamp: 9-30-2018, 7:31 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "bird.h"

bird::bird()
{
}

bird::bird(double solar_elevation, double ic_prime, double relative_optical_path, double air_pressure, double ozone_cm, double h2o_cm, double depth_380nm, double depth_500nm, double Ba, double tau_aerosol, double albedo)
{
	this->solar_elevation = solar_elevation;
	this->ic_prime = ic_prime;
	this->relative_optical_path = relative_optical_path;
	this->air_pressure = air_pressure;
	this->ozone_cm = ozone_cm;
	this->h2o_cm = h2o_cm;
	this->depth_380nm = depth_380nm;
	this->depth_500nm = depth_500nm;
	this->Ba = Ba;
	this->tau_aerosol = tau_aerosol;
	this->albedo = albedo;
	
	calculate_bird();
}

bird::~bird()
{
}

/* Air mass, absolute air mass at input atmospheric pressure. Return is in pascals */
double bird::absolute_air_mass(double relative_optical_path, double air_pressure)
{
	double absolute_airmass = (relative_optical_path*air_pressure) / (ATM1_AVE);
    
	return (absolute_airmass);
}

/* Air mass, absolute air mass at sea level. Return is in pascals */
double bird::absolute_air_mass(double relative_optical_path)
{
	double absolute_airmass = (relative_optical_path);
    
	return (absolute_airmass);
}

/* Incident plane angle to inbound radiation */
/* Incident radiation is on a plane that is tangent to the outer surface of the atmosphere. E.g. laying flat on the surface. */
double bird::calculate_plane_surface_angle(double solar_zenith)
{
	double angle = TO_DEGREE(cos(TO_RADIAN(solar_zenith)));
	return (angle);
}

/* Extraterrestrial radiation at surface angle (horizontal plane) to inbound radiation */
double bird::calculate_incident_surface_irradiation(double solar_elevation)
{
	double irrad;
	if (solar_elevation > 0.0)
	{
		double solar_zenith = 90.0 - solar_elevation;
		irrad = fabs(TO_RADIAN(calculate_plane_surface_angle(solar_zenith)));
	}
	else
	{
		irrad = 0;	
	}
	
	return (irrad);
}

/* Estimate broadband aerosol optical depth from depth at 380nm and 500nm. */
/* Bird and Hulstrom, "Direct Insolation Models" (1980) */
/* http://www.nrel.gov/docs/legosti/old/344.pdf */
/* Outputs range from 0.02 - 0.5 */
double bird::calculate_aerosol_taua(double depth_380nm, double depth_500nm)
{
	return (0.27583 * depth_380nm + 0.35 * depth_500nm);
}


/* Rayleigh scattering / attenuation */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
double bird::calculate_rayleigh_scattering(double relative_optical_path, double air_pressure)
{
	double rayleigh = 0.0;
	if (relative_optical_path > 0.0)
	{
		double abs_air_mass = absolute_air_mass(relative_optical_path, air_pressure) * 100.0;
		
		double a3 = powf(abs_air_mass, 1.01);
		double a4 = 1 + abs_air_mass;
		double a5 = pow(abs_air_mass, 0.84);
		double a2 = -0.0903 * a5 * (a4 - a3);
				
		rayleigh = exp(a2);
	}
    
	return (rayleigh);
}

/* Ozone Depth / attenuation */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_ozone_depth(double relative_optical_path, double ozone_cm)
{
	double ozone = 0.0;
	if (relative_optical_path > 0.0)
	{
		double o1 = ozone_cm*relative_optical_path;
		double o2 = 0.0003 * (o1) * (o1);
		double pow1 = powf((1.0 + 139.48 * o1), -0.3034);
		
		ozone = 1.0 - 0.1611 * o1 * pow1 - 0.002715 * o1 / (1.0 + 0.044 * o1 + o2);
	}
    
	return (ozone);
}

/* Mixed Gas Depth / attenuation */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_mixed_gas_depth(double relative_optical_path, double air_pressure)
{
	double mixed_gas = 0.0;
	if (relative_optical_path > 0.0)
	{
		double abs_air_mass = absolute_air_mass(relative_optical_path, air_pressure) * 100.0;
		
		mixed_gas = exp(-0.0127*powf(abs_air_mass, 0.26));
	}
    
	return (mixed_gas);
}

/* Water H2O depth / attenuation */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_h20_depth(double relative_optical_path, double h2o_cm)
{
	double h2o = 0.0;
	if (relative_optical_path > 0.0)
	{
		double abs_h2o_mass = relative_optical_path*h2o_cm;
		
		double a1 = 6.385 * abs_h2o_mass;
		double a2 = powf((1 + 79.034 *  abs_h2o_mass), 0.6828);
		h2o = 1 - ((2.4959*abs_h2o_mass) / (a2 + a1));
	}
    
	return (h2o);
}

/* Aerosol depth / attenuation. AKA turbidity */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_aerosol_depth(double relative_optical_path, double tau_aerosol)
{
	double aerosol = 0.0;
	if (relative_optical_path > 0.0)
	{
		double pow1 = -1.0*powf(tau_aerosol, 0.873);
		double pow2 = powf(tau_aerosol, 0.7088);
		double pow3 = powf(relative_optical_path, 0.9108);
		aerosol = exp((pow1)*(1 + tau_aerosol - pow2)*pow3);
	}
    
	return (aerosol);
}

double bird::calculate_aerosol_depth(double relative_optical_path, double depth_380nm, double depth_500nm)
{
	double aerosol = 0.0;
	double tau_aerosol = calculate_aerosol_taua(depth_380nm, depth_500nm);
	
	if (relative_optical_path > 0.0)
	{
		double pow1 = powf(tau_aerosol, 0.873);
		double pow2 = powf(tau_aerosol, 0.7088);
		double pow3 = powf(relative_optical_path, 0.9108);
		aerosol = exp(-1.0*(pow1)*(1 + tau_aerosol - pow2)*pow3);
	}
    
	return (aerosol);
}


/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_taa(double aerosol_tranmittance, double relative_optical_path)
{
	double taa = 0.0;
	if (relative_optical_path > 0.0)
	{
		double pow1 = powf(relative_optical_path, 1.06);
		taa = 1.0 - 0.1 * (1.0 - relative_optical_path + pow1) * (1.0 - aerosol_tranmittance);
	}
    
	return (taa);
}

/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_rs(double aerosol_transmittance, double taa, double Ba)
{
	double rs = 0.0;

	rs = 0.0685 + (1.0 - Ba) * (1.0 - aerosol_transmittance / taa);
	
	return (rs);
}

double bird::calculate_rs(double aerosol_transmittance, double taa)
{
	double rs = 0.0;
	double Ba = 0.85;
	
	rs = calculate_rs(aerosol_transmittance, taa, Ba);
	
	return (rs);
}

/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_tas(double relative_optical_path, double rayleigh_transmittance, double aerosol_transmittance, double ozone_transmittance, double h2o_transmittance, double mixed_transmittance, double taa, double Ba)
{
	double tas = 0.0;
	if (relative_optical_path > 0.0)
	{	
		double pow1 = powf(relative_optical_path, 1.02);
		tas = 0.79 * ozone_transmittance * mixed_transmittance * h2o_transmittance * taa * (0.5 * (1.0 - rayleigh_transmittance) + Ba * (1.0 - (aerosol_transmittance / taa))) / (1.0 - relative_optical_path + pow1);
	}
    
	return (tas);
}


/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_global_horizontal(double irrad_tilted, double direct_horizontal, double tas, double albedo, double rs)
{
	double global_horizontal = 0.0;
	
	global_horizontal = (direct_horizontal + (irrad_tilted * tas)) / (1.0 - albedo * rs);
				    
	return (global_horizontal);
}

/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_diffuse_horizontal(double direct_horizontal, double global_horizontal)
{
	double diffuse_horizontal = 0.0;
		
	diffuse_horizontal = global_horizontal - direct_horizontal;

	return (diffuse_horizontal);
}

/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_direct_normal_irradiation(double aerosol_tranmittance, double h20_transmittance, double mixed_gas_transmittance, double ozone_transmittance, double rayleigh_transmittance)
{
	double direct_normal = 0.0;
	
	direct_normal = 0.9662 * aerosol_tranmittance * h20_transmittance * mixed_gas_transmittance * ozone_transmittance * rayleigh_transmittance;
    
	return (direct_normal);
}

/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_bird(double relative_optical_path, double air_pressure, double ozone_cm, double h2o_cm, double depth_380nm, double depth_500nm, double Ba)
{
	double direct_normal = 0.0;
	if (relative_optical_path > 0.0)
	{	
		this->tau_aerosol = calculate_aerosol_taua(depth_380nm, depth_500nm);
		this->direct_normal = calculate_bird();
	}
    
	return (this->direct_normal);
}

/*  */
/* Bird 1991,"A Simplified Clear Sky model for Direct and Diffuse Insolation on Horizontal Surfaces" */
/* http://rredc.nrel.gov/solar/pubs/pdfs/tr-642-761.pdf */
/* Returns transmissive ratio. */
double bird::calculate_bird()
{

	if (relative_optical_path > 0.0)
	{	
		this->raleigh = calculate_rayleigh_scattering(this->relative_optical_path, this->air_pressure);/**/
		this->ozone = calculate_ozone_depth(this->relative_optical_path, this->ozone_cm);/**/
		this->mixed = calculate_mixed_gas_depth(this->relative_optical_path, this->air_pressure);/**/
		this->h2o = calculate_h20_depth(this->relative_optical_path, this->h2o_cm);/**/
		this->aerosol = calculate_aerosol_depth(this->relative_optical_path, this->tau_aerosol);/**/
		this->taa = calculate_taa(this->aerosol, this->relative_optical_path);/**/
		this->rs = calculate_rs(this->aerosol, this->taa, this->Ba);/**/
		this->direct_normal = calculate_direct_normal_irradiation(this->aerosol, this->h2o, this->mixed, this->ozone, this->raleigh);/**/
		this->tas = calculate_tas(relative_optical_path, this->raleigh, this->aerosol, this->ozone, this->h2o, this->mixed, this->taa, Ba);
		
		this->direct_beam = ic_prime * this->direct_normal;
		this->plane_angle = calculate_incident_surface_irradiation(this->solar_elevation);
		this->irrad_horizontal  = ic_prime * this->plane_angle;
		this->direct_horizontal = direct_normal * irrad_horizontal;
		this->global_horizontal = calculate_global_horizontal(irrad_horizontal, direct_horizontal, this->tas, this->albedo, this->rs);
		this->diffuse_horizontal = calculate_diffuse_horizontal(this->direct_horizontal, this->global_horizontal);
	}
	else
	{
		this->raleigh = 0.0;/**/
		this->ozone = 0.0;/**/
		this->mixed = 0.0;/**/
		this->h2o = 0.0;/**/
		this->aerosol = 0.0;/**/
		this->taa = 0.0;/**/
		this->rs = 0.0;/**/
		this->direct_normal = 0.0;/**/
		this->tas = 0.0;
		
		this->direct_beam = 0.0;
		this->plane_angle = 0.0;
		this->irrad_horizontal  = 0.0;
		this->direct_horizontal = 0.0;
		this->global_horizontal = 0.0;
		this->diffuse_horizontal = 0.0;
	}
    
	return (this->direct_normal);
}


