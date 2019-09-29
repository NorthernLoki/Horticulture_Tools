//
// vpd_text_table.cpp
// Version timestamp: 9-4-2018, 4:23 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//

// This source serves as an example of utilizing the vpd class to generate vpd charts.
//
// Usage example:
//
// // Generate charts for the case where leaf temperature difference is known to be 1 degree greater than the environment.
// vpd_text_table(1);
//
// // Generate charts for the case where leaf temperature difference is unknown or the leaf temperature equals the environment.
// vpd_text_table();



#include "vpd_text_table.h"


namespace
{
	enum Code
	{
		FG_RED     = 31,
		FG_GREEN   = 32,
		FG_YELLOW  = 33,
		FG_BLUE    = 34,
		FG_MAGENTA = 35,
		FG_DEFAULT = 39,
		BG_RED     = 41,
		BG_GREEN   = 42,
		BG_BLUE    = 44,
		BG_DEFAULT = 49
	};
	
	std::ostream& operator<<(std::ostream& os, Code code) 
	{
		return os << "\033[" << static_cast<int>(code) << "m";
	}
}


/* Calculate and print VPD tables for the case where the leaf temperatures are the same as the atmosphere. */
vpd_text_table::vpd_text_table()
{
	/* The following are examples VPD values for different stages of plant growth */
	/* VPD is actually quite a bit more complicated than simply looking at temperature and humidity */
	/* but, this will provide a general goal until you are looking at actual transpiration estimations. Set these to your expectations. */
	float early_veg_min = 0.4;
	float early_veg_max = 0.8;
	float late_veg_min = 0.8;
	float late_veg_max = 1.2;
	float late_flower_min = 1.2;
	float late_flower_max = 1.6;
	
	float leaf_diff = 0;
	
	std::cout << boost::format("%=8i")  % " " << "Suggested VPD during propagation and early vegetation:" << std::endl;
	print_table(leaf_diff, early_veg_min, early_veg_max);
	std::cout << boost::format("%=8i")  % " " << "Suggested VPD during late vegetation and early flowering:" << std::endl;
	print_table(leaf_diff, late_veg_min, late_veg_max);	
	std::cout << boost::format("%=8i")  % " " << "Suggested VPD during mid to late flowering:" << std::endl;
	print_table(leaf_diff, late_flower_min, late_flower_max);	
}

/* Calculate and print VPD tables for the case where the leaf temperatures are different than the surrounding atmosphere. */
/* leaf_temperature_differential is the difference between the leaf and the atmosphere in degrees celcius */
vpd_text_table::vpd_text_table(float leaf_temperature_differential)
{
	/* The following are examples VPD values for different stages of plant growth */
	/* VPD is actually quite a bit more complicated than simply looking at temperature and humidity */
	/* but, this will provide a general goal until you are looking at actual transpiration estimations. Set these to your expectations. */
	float early_veg_min = 0.4;
	float early_veg_max = 0.8;
	float late_veg_min = 0.8;
	float late_veg_max = 1.2;
	float late_flower_min = 1.2;
	float late_flower_max = 1.6;
	
	float leaf_diff = leaf_temperature_differential;
	
	std::cout << boost::format("%=8i")  % " " << "Suggested VPD during" << FG_YELLOW << " propagation and early vegetation" << FG_DEFAULT << " with leaf temperature difference of " << leaf_temperature_differential << " degree :" << std::endl;
	print_table(leaf_diff, early_veg_min, early_veg_max);
	std::cout << boost::format("%=8i")  % " " << "Suggested VPD during" << FG_YELLOW << " late vegetation and early flowering" << FG_DEFAULT << " with leaf temperature difference of " << leaf_temperature_differential << " degree :" << std::endl;
	print_table(leaf_diff, late_veg_min, late_veg_max);	
	std::cout << boost::format("%=8i")  % " " << "Suggested VPD during" << FG_YELLOW << " mid to late flowering" << FG_DEFAULT << " with leaf temperature difference of " << leaf_temperature_differential << " degree :" << std::endl;
	print_table(leaf_diff, late_flower_min, late_flower_max);	
	
}


vpd_text_table::~vpd_text_table()
{
}


void vpd_text_table::print_table(float temperature_difference, float min, float max)
{
	float humidity = 0;
	float humidity_step = 5;
	celcius temperature = 0;
	
	std::cout << boost::format("%=8i")  % " " << FG_BLUE << "Relative Humidity (\%) ----->" << FG_DEFAULT << std::endl;
	
	std::cout << boost::format("%=8i|")  % " ";
	for (humidity = 0; humidity <= 100; humidity += humidity_step)
	{
		std::cout << boost::format("%=8s|")  % "--------";
	}
	std::cout << std::endl;
	
	std::cout << boost::format("%=8i|")  % " ";
	for (humidity = 0; humidity <= 100; humidity += humidity_step)
	{
		std::cout << boost::format("%=8i|")  % humidity;
	}
	std::cout << std::endl;
	
	int temp_string_cnt = 0;
	const char temp_string[255] = "                      Temperature degrees celcius                        ";
	
	for (temperature = 5; temperature <= 40; temperature += 1)
	{
		std::cout << FG_BLUE << boost::format("%=1c")  % temp_string[temp_string_cnt++] << FG_DEFAULT;
		std::cout << boost::format("%=7i|")  % " ";
		for (humidity = 0; humidity <= 100; humidity += humidity_step)
		{
			std::cout << boost::format("%=8s|")  % "--------";
		}
		std::cout << std::endl;
	
		std::cout << FG_BLUE << boost::format("%=1c")  % temp_string[temp_string_cnt++] << FG_DEFAULT;
		std::cout << boost::format("%=7i|")  % temperature;

		for (humidity = 0; humidity <= 100; humidity += humidity_step)
		{
			vpd pressure_deficit = vpd(temperature, temperature + temperature_difference, (float)humidity / 100.0);
			if ((pressure_deficit() < min) || (pressure_deficit() > max))
			{
				std::cout << FG_RED << boost::format("%=8.3f")  % pressure_deficit << FG_DEFAULT << "|";
			}
			else
			{
				std::cout << FG_GREEN << boost::format("%=8.3f")  % pressure_deficit << FG_DEFAULT << "|";
			}
			
		}
		std::cout << std::endl;
	}
	
	std::cout << boost::format("%=8i|")  % " ";
	for (humidity = 0; humidity <= 100; humidity += humidity_step)
	{
		std::cout << boost::format("%=8s|")  % "--------";
	}
	std::cout << std::endl << std::endl;
}