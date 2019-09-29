//
// vpd_runtime_test.cpp
// Version timestamp: 9-4-2018, 4:23 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//

// This source serves as an example of utilizing the vpd class for use with control systems to check and respond to VPD conditions.
//
// Usage example:
//
// vpd_runtime_test vpd_runtime;
// farenheit test_temp = 75.0;
//	
// float vpd_result = vpd_runtime.check_vpd(test_temp, test_temp, 60.0, 0.8, 1.2);
// if (vpd_result != 0.0)
// {
//	 /* Do something to alert / correct the VPD */
// }
//	
// vpd_runtime.check_vpd_and_print(test_temp, test_temp, 60.0, 0.8, 1.2);
//	
// test_temp = 90.5;
// vpd_runtime.check_vpd_and_print(test_temp, test_temp, 60.0, 0.8, 1.2);

#include "vpd_runtime_test.h"


namespace
{
	enum Code
	{
		BOLD             = 1,
		UNDERLINE        = 4,
		NEGATIVE         = 7,
		CONCEAL          = 8,
		STRIKE           = 28,
		FG_BLACK         = 30,
		FG_RED           = 31,
		FG_GREEN         = 32,
		FG_YELLOW        = 33,
		FG_BLUE          = 34,
		FG_MAGENTA       = 35,
		FG_CYAN          = 36,
		FG_WHITE         = 37,
		FG_DARK_GRAY     = 38,
		FG_DEFAULT       = 39,
		FG_LIGHT_BLACK   = 90,
		FG_ORANGE        = 91,
		FG_LIGHT_GREEN   = 92,
		FG_LIGHT_YELLOW  = 93,
		FG_LIGHT_BLUE    = 94,
		FG_LIGHT_MAGENTA = 95,
		FG_LIGHT_CYAN    = 96,
		BG_BLACK         = 40,
		BG_RED           = 41,
		BG_GREEN         = 42,
		BG_YELLOW        = 43,
		BG_BLUE          = 44,
		BG_MAGENTA       = 45,
		BG_CYAN          = 46,
		BG_WHITE         = 47,
		BG_DARK_GRAY     = 48,
		BG_DEFAULT       = 49,
		BG_LIGHT_BLACK   = 100,
		BG_ORANGE        = 101,
		BG_LIGHT_GREEN   = 102,
		BG_LIGHT_YELLOW  = 103,
		BG_LIGHT_BLUE    = 104,
		BG_LIGHT_MAGENTA = 105,
		BG_LIGHT_CYAN    = 106,
		BG_LIGHT_WHITE   = 107	
	};
	
	std::ostream& operator<<(std::ostream& os, Code code) 
	{
		return os << "\033[" << static_cast<int>(code) << "m";
	}
}


vpd_runtime_test::vpd_runtime_test()
{
}


vpd_runtime_test::~vpd_runtime_test()
{
}

float vpd_runtime_test::print_status(float vapor_pressure_deficit, float min_vpd, float max_vpd)
{
	
	if (vapor_pressure_deficit > max_vpd)
	{
		std::cout << boost::format("%=8i")  % " " << FG_RED << "WARN :" << FG_DEFAULT << "Vapor pressure deficit is too high (" << vapor_pressure_deficit << ")" << std::endl;
		return (vapor_pressure_deficit - max_vpd);
	}
	else if (vapor_pressure_deficit < min_vpd)
	{
		std::cout << boost::format("%=8i")  % " " << FG_RED << "WARN :" << FG_DEFAULT << "Vapor pressure deficit is too low (" << vapor_pressure_deficit << ")" << std::endl;
		return (vapor_pressure_deficit - min_vpd);
	}
	else
	{
		std::cout << boost::format("%=8i")  % " " << FG_GREEN << "OK :" << FG_DEFAULT << "Vapor pressure deficit is nominal (" << vapor_pressure_deficit << ")" << std::endl;
		return (0.0);
	}
}

float vpd_runtime_test::check_vpd(vpd vapor_pressure, float min_vpd, float max_vpd)
{
	double vapor_pressure_deficit = vapor_pressure.vapor_pressure_deficit;
	return (print_status(vapor_pressure_deficit, min_vpd, max_vpd));
}

float vpd_runtime_test::check_vpd(celcius temperature, float humidity, float min_vpd, float max_vpd)
{
	double vapor_pressure_deficit = calc_boundary(temperature, temperature, humidity);
	return (print_status(vapor_pressure_deficit, min_vpd, max_vpd));
}

float vpd_runtime_test::check_vpd(celcius temperature, celcius leaf_temperature, float humidity, float min_vpd, float max_vpd)
{
	double vapor_pressure_deficit = calc_boundary(temperature, leaf_temperature, humidity);
	return (print_status(vapor_pressure_deficit, min_vpd, max_vpd));
}

float vpd_runtime_test::check_vpd_and_print(vpd vapor_pressure, float min_vpd, float max_vpd)
{
	double vapor_pressure_deficit = vapor_pressure.vapor_pressure_deficit;
	print_table(vapor_pressure.degrees_celcius, vapor_pressure.humidity*100, (vapor_pressure.degrees_celcius_leaf - vapor_pressure.degrees_celcius), min_vpd, max_vpd);
	return (print_status(vapor_pressure_deficit, min_vpd, max_vpd));
}

float vpd_runtime_test::check_vpd_and_print(celcius temperature, float humidity, float min_vpd, float max_vpd)
{
	double vapor_pressure_deficit = calc_boundary(temperature, temperature, humidity);
	print_table(temperature, humidity, 0, min_vpd, max_vpd);
	float result = print_status(vapor_pressure_deficit, min_vpd, max_vpd);
	return (result);
}

float vpd_runtime_test::check_vpd_and_print(celcius temperature, celcius leaf_temperature, float humidity, float min_vpd, float max_vpd)
{
	double vapor_pressure_deficit = calc_boundary(temperature, leaf_temperature, humidity);
	print_table(temperature, humidity, (leaf_temperature - temperature), min_vpd, max_vpd);
	float result = print_status(vapor_pressure_deficit, min_vpd, max_vpd);
	return (result);
}

double vpd_runtime_test::calc_boundary(celcius temperature, celcius leaf_temperature, float humidity)
{
	vpd pressure_deficit = vpd(temperature, leaf_temperature, (float)humidity / 100.0);
	return (pressure_deficit.vapor_pressure_deficit);
}


void vpd_runtime_test::print_table(celcius actual_temperature, float actual_humidity, float temperature_difference, float min, float max)
{
	float humidity = 0;
	float humidity_step = 5;
	celcius temperature = 0;
	celcius temperature_step = 1;
	
	/* Top of plot, create scale and labels for relative humidity. */
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
		if ((actual_humidity >= humidity) && (actual_humidity <= (humidity + humidity_step)))
		{
			std::cout << FG_YELLOW << BG_LIGHT_BLACK << boost::format("%=8i")  % humidity << BG_DEFAULT << FG_DEFAULT << "|";
		}
		else
		{
			std::cout << boost::format("%=8i|")  % humidity;
		}
		
	}
	std::cout << std::endl;
	/* End of scale and labels. */
	
	int temp_string_cnt = 0;
	const char temp_string[255] = "                      Temperature degrees celcius                        ";
	
	for (temperature = 5; temperature <= 40; temperature += temperature_step)
	{
		std::cout << FG_BLUE << boost::format("%=1c")  % temp_string[temp_string_cnt++] << FG_DEFAULT;
		std::cout << boost::format("%=7i|")  % " ";
		for (humidity = 0; humidity <= 100; humidity += humidity_step)
		{
			if ((actual_humidity >= humidity) && (actual_humidity <= (humidity + humidity_step)))
			{
				std::cout << BG_LIGHT_BLACK;
				std::cout << boost::format("%=8s")  % "--------" << BG_DEFAULT <<"|";
			}
			else
			{
				std::cout << boost::format("%=8s|")  % "--------";
			}
		}
		
		std::cout << std::endl;
		
		std::cout << FG_BLUE << boost::format("%=1c")  % temp_string[temp_string_cnt++] << FG_DEFAULT;
		if ((actual_temperature >= temperature) && (actual_temperature <= (temperature + temperature_step)))
		{
			std::cout << FG_YELLOW << BG_LIGHT_BLACK << boost::format("%=7i")  % temperature << BG_DEFAULT << FG_DEFAULT << "|";
		}
		else
		{
			std::cout << boost::format("%=7i|")  % temperature;
		}
		

		for (humidity = 0; humidity <= 100; humidity += humidity_step)
		{
			if ((actual_humidity >= humidity) && (actual_humidity <= (humidity + humidity_step)) && (actual_temperature >= temperature) && (actual_temperature <= (temperature + temperature_step)))
			{
				vpd pressure_deficit = vpd(temperature, temperature + temperature_difference, (float)humidity / 100.0, VPD_GOFF);
				if ((pressure_deficit() < min) || (pressure_deficit() > max))
				{
					std::cout << BG_RED << FG_YELLOW << boost::format("%=8.3f")  % pressure_deficit << BG_DEFAULT << FG_DEFAULT << "|";
				}
				else
				{
					std::cout << BG_GREEN << boost::format("%=8.3f")  % pressure_deficit << BG_DEFAULT << "|";
				}	
			}
			else
			{
				if ((actual_humidity >= humidity) && (actual_humidity <= (humidity + humidity_step)))
				{
					std::cout << BG_LIGHT_BLACK;
				}
				
				if ((actual_temperature >= temperature) && (actual_temperature <= (temperature + temperature_step)))
				{
					std::cout << BG_LIGHT_BLACK;
				}
				
				vpd pressure_deficit = vpd(temperature, temperature + temperature_difference, (float)(humidity / 100.0), VPD_GOFF);
				if ((pressure_deficit() < min) || (pressure_deficit() > max))
				{
					std::cout << FG_RED << boost::format("%=8.3f")  % pressure_deficit << FG_DEFAULT << "|";
				}
				else
				{
					std::cout << FG_GREEN << boost::format("%=8.3f")  % pressure_deficit << FG_DEFAULT << "|";
				}
				
				std::cout << BG_DEFAULT;
			}
		}
		std::cout << std::endl;
	}
	
	std::cout << boost::format("%=8i|")  % " ";
	for (humidity = 0; humidity <= 100; humidity += humidity_step)
	{
		std::cout << boost::format("%=8s|")  % "--------";
	}
	std::cout << std::endl;
}
