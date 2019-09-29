#include "DLITests.h"

/*
	To test the library, include "DLI.h" from an application project
	and call DLITest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

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

static int s_Test = 0;

int DLITest()
{
	test_dli_tests_compare();
	test_dli_tests_multi();
	test_dlimap_tests();
	test_dlimap_atom_tests();
	test_dli_tests();
	return ++s_Test;
}

void test_dli_tests_compare()
{
	/*************/
	/* DLI tests */
	do
	{
		/* Estimated as 33.8MJ/m^2 day */
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::June / 1 / 2018 } + std::chrono::hours(0));
		sun_element_location.set("New York", 40.730610, -73.935242, solar_date, true);
		
		std::cout << "Solar Sunrise: " << sun_element_location.sunrise * 24.0 << " Solar Sunset: " << sun_element_location.sunset * 24.0 << std::endl;
		
		double daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_NONE);
		
		std::cout << "Beam Tb: " << dli.beam_transmittance << " Diffuse Td: " << dli.diffuse_radiation << " Air mass: " << dli.relative_optical_path << std::endl;
		std::cout << "DLI at latitude on 6/1 : " << daily_light << " kW/m^2 day " << "   PPFD : " << dli.ppfd << std::endl;
		
		daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_SIMPLE);
		std::cout << "DLI with atmosphere at (" << sun_element_location.name << ") on 6/1 : " << daily_light << " kW/m^2 day " << "   PPFD : " << dli.ppfd << std::endl;
		
		daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_BIRD);
		std::cout << "DLI with atmosphere at (" << sun_element_location.name << ") on 6/1 : " << daily_light << " kW/m^2 day " << "   PPFD : " << dli.ppfd << std::endl;
		
	} while (0);
}


void test_dli_tests_multi()
{
	/*************/
	/* DLI tests */
	do
	{
		/* Estimated as 33.8MJ/m^2 day */
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(0));
		sun_element_location.set("Boston", 43.0, -71, solar_date, true);
		
		double daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_NONE);
		
		std::cout << "DLI at latitude 43 north on 4/15 : " << daily_light << " kW/m^2 day" << std::endl;
		
		daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_BIRD);
		std::cout << "DLI with atmosphere at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << daily_light << " kW/m^2 day" << std::endl;
		
	} while (0);
	
	do
	{
		/* Estimated as 33.8MJ/m^2 day */
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::June / 15 / 2018 } + std::chrono::hours(0));
		sun_element_location.set("Boston", 43.0, -71, solar_date, true);
		
		double daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_NONE);
		
		std::cout << "DLI at latitude 43 north on 6/15 : " << daily_light << " kW/m^2 day" << std::endl;
		
		daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_BIRD);
		std::cout << "DLI with atmosphere at latitude 43 north (" << sun_element_location.name << ") on 6/15 : " << daily_light << " kW/m^2 day" << std::endl;
		
	} while (0);
	
	do
	{
		/* Estimated as 32.2MJ/m^2 day */
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::September / 3 / 2018 } + std::chrono::hours(0));
		sun_element_location.set("Unknown", -20.0, -112.074036, solar_date, true);
		
		double daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_NONE);
		
		std::cout << "DLI at latitude -20 north on 9/3 : " << daily_light << " kW/m^2 day" << std::endl;
		
		daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_BIRD);
		std::cout << "DLI with atmosphere at latitude -20 (" << sun_element_location.name << ") on 9/3 : " << daily_light << " kW/m^2 day" << std::endl;
		
	} while (0);
	
	
	do
	{
		/* Estimated as 25.1MJ/m^2 day */
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		
		solar_date = date::make_zoned("Brazil/East", date::local_days{ date::May / 15 / 2018 } + std::chrono::hours(0));
		sun_element_location.set("Rio de Janeiro", -22.9032, -43.1729, solar_date, true);
		
		double daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_NONE);
		std::cout << "DLI at latitude -22.9032 north (" << sun_element_location.name << ") on 5/15 : " << daily_light << " kW/m^2 day" << std::endl;
		
		daily_light = dli.calculate_dli(solar_date, &sun_element_location, ATOM_BIRD);
		std::cout << "DLI with atmosphere at latitude -22.9032 (" << sun_element_location.name << ") on 5/15 : " << daily_light << " kW/m^2 day" << std::endl;
		
	} while (0);
	
	
	do
	{
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		boost::container::flat_set<std::pair<double, double>> the_set;
		std::pair<double, double> element;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(10));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date);
		
		double hour1_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 10, hour1_light };
		the_set.insert(element);
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(11));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date);
		
		double hour2_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 11, hour2_light };
		the_set.insert(element);
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(12));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date);
		
		double hour3_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 12, hour3_light };
		the_set.insert(element);
		
		integrate integral(&the_set);
		double irrad = (integral.integral) * (SECONDS_HOUR) / 1000000.0; 
		
		std::cout << "Light integral between 10 and 12 at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << irrad << std::endl;
		
	} while (0);
	
	do
	{
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		boost::container::flat_set<std::pair<double, double>> the_set;
		std::pair<double, double> element;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(10));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, true);
		
		double hour1_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 10, hour1_light };
		the_set.insert(element);
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(11));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, false);
		
		double hour2_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 11, hour2_light };
		the_set.insert(element);
		
		integrate integral(&the_set);
		double irrad = (integral.integral) * (SECONDS_HOUR) / 1000000.0; 
		
		std::cout << "Light integral between 10 and 11 at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << irrad << std::endl;
		
	} while (0);
	
	do
	{
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		boost::container::flat_set<std::pair<double, double>> the_set;
		std::pair<double, double> element;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(11));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, true);
		
		double hour1_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 11, hour1_light };
		the_set.insert(element);
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(12));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, false);
		
		double hour2_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		element = { 12, hour2_light };
		the_set.insert(element);
		
		integrate integral(&the_set);
		double irrad = (integral.integral) * (SECONDS_HOUR) / 1000000.0; 
		
		std::cout << "Light integral between 11 and 12 at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << irrad << std::endl;
		
	} while (0);
	
	do
	{
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		boost::container::flat_set<std::pair<double, double>> the_set;
		std::pair<double, double> element;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(10));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, true);
		
		double hour1_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		double irrad = (hour1_light); 
		
		std::cout << "Quantum Flux (W/m^2/hr) at 10 at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << irrad << std::endl;
		
	} while (0);
	
	do
	{
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		boost::container::flat_set<std::pair<double, double>> the_set;
		std::pair<double, double> element;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(11));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, true);
		
		double hour1_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		double irrad = (hour1_light); 
		
		std::cout << "Quantum Flux (W/m^2/hr) at 11 at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << irrad << std::endl;
		
	} while (0);
	
	do
	{
		Daily_Light dli;
		zoned_sun_time solar_date;
		sun sun_element_location;
		boost::container::flat_set<std::pair<double, double>> the_set;
		std::pair<double, double> element;
		
		solar_date = date::make_zoned("America/New_York", date::local_days{ date::April / 15 / 2018 } + std::chrono::hours(12));
		sun_element_location.set("Boston", 43.0, -112.074036, solar_date, true);
		
		double hour1_light = dli.calculate_irrad(solar_date, &sun_element_location, ATOM_NONE);
		double irrad = (hour1_light); 
		
		std::cout << "Quantum Flux (W/m^2/hr)  at 12 at latitude 43 north (" << sun_element_location.name << ") on 4/15 : " << irrad << std::endl;
		
	} while (0);
	
	
	
	/* Calculate the extraterrestrial radiation per each day of a year normal to the plane of the sun. */
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Extraterrestrial radiation normal to solar radiation ***************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time newyork_area;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		
		double solar_noon;
		int day_stride = 4;
		
		double distmax, distmax_copy, distmin_copy, distmin = 5000.0;
		for (int day = 0; day < 365; day += day_stride)
		{
			/* Find the day with the maximum and minimum amounts of daylight. */
			newyork_area = date::make_zoned("America/Phoenix", date::local_days{ date::January / 01 / 2018 } + std::chrono::hours(12) + date::days(day));
			sun_element_newyork.set("Pheonix", 33.448376, -112.074036, newyork_area, false);
			solar_noon = sun_element_newyork.solar_noon;
			
			/* Calculate sun position at solar noon. */
			auto time_hms = sun_element_newyork.fp_days_to_chrono(solar_noon);
			auto time_hmsd = date::local_days{ date::January / 01 / 2018 } + time_hms + date::days(day);

			newyork_area = date::make_zoned("America/Phoenix", time_hmsd);
			sun_element_newyork.set("Pheonix", 40.730610, -73.935242, newyork_area, false);
			
			double distance = SOLAR_CONSTANT * dli.calculate_extraterestrial_radiation(sun_element_newyork.rad_vector);
			
			/* Save this information. */
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
        
			if (distance > distmax) distmax = distance;
			if (distance < distmin) distmin = distance;
		}
    
		distmax_copy = distmax;
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		/* Plot the chart */
		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);		
        
			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y", newyork_area) << ": " << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
        
				if ((distance) >= (distmax_copy))
				{
					std::cout << " <-max- " << distance  << " W/m^2";
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << " <-min- " << distance << " W/m^2";
				}
        
				std::cout << std::endl;
			}	    
		}
		
		std::cout << std::endl;
	
	} while (0);
	
	
	

	/*************/
	/* Calculate the extraterrestrial radiation per each day of a year tangent to the surface. */
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Extraterrestrial radiation tangent to surface **********************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time newyork_area;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		
		double distmax, distmax_copy, distmin_copy, distmin = 5000.0;
		int day_stride = 4;
		
		for (int day = 0; day < 365; day += day_stride)
		{
			/* Find the solar noons and the incident radiation max/mins throughout the year. */
			/* Find solar noon for today. */
			newyork_area = date::make_zoned("America/Phoenix", date::local_days{ date::January / 01 / 2018 } + std::chrono::hours(12) + date::days(day));
			sun_element_newyork.set("Pheonix", 33.448376, -112.074036, newyork_area, false);
			
			double solar_noon = sun_element_newyork.solar_noon;
			
			/* Calculate sun position at solar noon. */
			auto time_hms = sun_element_newyork.fp_days_to_chrono(solar_noon);
			auto time_hmsd = date::local_days{ date::days(day) } + time_hms;

			newyork_area = date::make_zoned("America/Phoenix", time_hmsd);
			sun_element_newyork.set("Pheonix", 33.448376, -112.074036, newyork_area, false);
			
			/* Determine radiation. */
			double radiation = dli.calculate_extraterestrial_radiation(sun_element_newyork.rad_vector);
			double distance = SOLAR_CONSTANT * dli.calculate_incident_surface_irradiation(radiation, sun_element_newyork.solar_elevation_corrected);
			/* Save this information. */
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
        
			if (distance > distmax) distmax = distance;
			if (distance < distmin) distmin = distance;
		}
    
		distmax_copy = distmax;
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		/* Plot the chart */

		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);

			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*(day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y %R", newyork_area) << " : " << FG_GREEN << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
				
				if ((distance) >= (distmax_copy))
				{
					std::cout << FG_GREEN << " <-max- W/m^2" << FG_DEFAULT;
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << FG_GREEN << " <-min- W/m^2" << FG_DEFAULT;
				}
				std::cout << std::endl;
			}	    
        
		}
		std::cout << std::endl;
	
	} while (0) ;
	
	
	
	/*************/
	/* Calculate the dli on the min/max solar radiation days. */
	do
	{
		zoned_sun_time shanghai1 = date::make_zoned("Asia/Shanghai", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time losangeles1 = date::make_zoned("America/Los_Angeles", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time sydney1 = date::make_zoned("Australia/Sydney", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time newyork1 = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time moscow1 = date::make_zoned("Europe/Moscow", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time chicago1 = date::make_zoned("America/Chicago", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time newzealand1 = date::make_zoned("Pacific/Auckland", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time quito1 = date::make_zoned("America/Guayaquil", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time Reykjavik = date::make_zoned("Atlantic/Reykjavik", date::local_days{ date::January / 01 / 2018 });
	
		std::vector<sun> sun_info_vec1;
		sun sun_element1("Reykjavik, Iceland", 64.135666, -21.862675, Reykjavik);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Shanghai", 31.22222, 121.45806, shanghai1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Los Angeles", 34.052235, -118.243683, losangeles1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Sydney", -33.865143, 151.209900, sydney1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("New York", 40.730610, -73.935242, newyork1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Moscow", 55.751244, 37.618423, moscow1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Chicago", 41.881832, -87.623177, chicago1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Auckland,NZ", -36.848461, 174.763336, newzealand1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Quito, Ecuador", -0.22985, -78.52495, quito1);
		sun_info_vec1.push_back(sun_element1);

	
		for (sun sun_element_location : sun_info_vec1)
		{
		
			std::cout << "********************************************************************************************************************" << std::endl;
			std::cout << "*********************** Min / Max DLI solar Radiation days without Atmosphere **************************************" << std::endl;
			std::cout << "********************************************************************************************************************" << std::endl;

			Daily_Light dli;
			std::list<std::tuple<double, double, double, zoned_sun_time>> rad_map;
			zoned_sun_time sun_time = *sun_element_location.zone_time;
		
			std::cout << "Calculating : ";
			double distmax = 0;
			double distmax_copy = 0;
			double distmin_copy = 0;
			double distmin = 5000.0; 
			double julian_last = 0;
			int day_stride = 5;
			
			for (int day = 0; day < 365; day += day_stride)
			{
				if (day % 5 == 0) std::cout << "." << std::flush;
			
				/* Determine radiation. */
				double distance = dli.calculate_dli(sun_time, &sun_element_location, ATOM_NONE);
			
				/* Save this information. */
				rad_map.push_back(std::tuple<double, double, double, zoned_sun_time>((double)day, distance, sun_element_location.solar_elevation_corrected, sun_time));
				if (distance > distmax)
				{
					distmax = distance;
				}
				if (distance < distmin) 
				{
					distmin = distance;
				}
				
				/* Update the time. */
				sun_time = sun_time.get_local_time() + date::days{ day_stride };
				sun_element_location.set(sun_element_location.name, sun_element_location.observer_latitude, sun_element_location.observer_longitude, sun_time);
			}
			std::cout << std::endl;
			std::cout << "Location : " << sun_element_location.name << std::endl;
    
			distmax_copy = distmax;
			int distmax_ceil = ceil(distmax);
			distmin_copy = distmin;
			int distmin_floor = floor(distmin);	
			double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		
			/* Plot the chart */
			
			double yearly_DLI = 0.0; julian_last = 0;
			for (std::tuple<double, double, double, zoned_sun_time> element : rad_map)
			{
				int day = std::get<0>(element);
				double distance = std::get<1>(element);
				double temp = std::get<2>(element);
				zoned_sun_time sun_time_location = std::get<3>(element);
				yearly_DLI += distance;
			
			
				//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
				if(1)
				{

					std::cout << date::format("%b %d %Y", sun_time_location) << " : " << FG_GREEN << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
				
					if ((distance) >= (distmax_copy))
					{
						std::cout << FG_GREEN << " <-max- DLI (MJ / m^2 day)" << FG_DEFAULT;
					}
            
					if ((distance) <= (distmin_copy))
					{
						std::cout << FG_GREEN << " <-min- DLI (MJ / m^2 day)" << FG_DEFAULT;
					}
					std::cout << std::endl;
				}	    
        
			}
			std::cout << std::endl;	
			std::cout << "Yearly DLI : " << yearly_DLI << " (MJ / m^2 year)" << std::endl;
			rad_map.clear();
		}
	
	} while (0);
	
	
	
	
	
	/*************/
	/* Calculate the dli on the min/max solar radiation days. */
	do
	{
		zoned_sun_time shanghai1 = date::make_zoned("Asia/Shanghai", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time losangeles1 = date::make_zoned("America/Los_Angeles", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time sydney1 = date::make_zoned("Australia/Sydney", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time newyork1 = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time moscow1 = date::make_zoned("Europe/Moscow", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time chicago1 = date::make_zoned("America/Chicago", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time newzealand1 = date::make_zoned("Pacific/Auckland", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time quito1 = date::make_zoned("America/Guayaquil", date::local_days{ date::January / 01 / 2018 });
		zoned_sun_time Reykjavik = date::make_zoned("GMT", date::local_days{ date::January / 01 / 2018 });
	
		std::vector<sun> sun_info_vec1;
		sun sun_element1("Shanghai", 31.22222, 121.45806, shanghai1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Los Angeles", 34.052235, -118.243683, losangeles1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Sydney", -33.865143, 151.209900, sydney1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("New York", 40.730610, -73.935242, newyork1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Moscow", 55.751244, 37.618423, moscow1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Chicago", 41.881832, -87.623177, chicago1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Auckland,NZ", -36.848461, 174.763336, newzealand1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Quito, Ecuador", -0.22985, -78.52495, quito1);
		sun_info_vec1.push_back(sun_element1);
		sun_element1.set("Reykjavik, Iceland", 64.135666, -21.862675, Reykjavik);
		sun_info_vec1.push_back(sun_element1);
	
		for (sun sun_element_location : sun_info_vec1)
		{
		
			std::cout << "********************************************************************************************************************" << std::endl;
			std::cout << "*********************** Min / Max DLI solar Radiation days with Atmosphere *****************************************" << std::endl;
			std::cout << "********************************************************************************************************************" << std::endl;

			Daily_Light dli;
			std::list<std::tuple<double, double, double, zoned_sun_time>> rad_map;
			zoned_sun_time sun_time = *sun_element_location.zone_time;
		
			std::cout << "Calculating : ";
			double distmax = 0;
			double distmax_copy = 0;
			double distmin_copy = 0;
			double distmin = 5000.0; 
			double julian_last = 0;
			int day_stride = 5;
			
			for (int day = 0; day < 365; day += day_stride)
			{
				if (day % 5 == 0) std::cout << "." << std::flush;
			
				/* Determine radiation. */
				double distance = dli.calculate_dli(sun_time, &sun_element_location, ATOM_BIRD);
			
				/* Save this information. */
				rad_map.push_back(std::tuple<double, double, double, zoned_sun_time>((double)day, distance, sun_element_location.solar_elevation_corrected, sun_time));
				if (distance > distmax)
				{
					distmax = distance;
				}
				if (distance < distmin) 
				{
					distmin = distance;
				}
				
				/* Update the time. */
				sun_time = sun_time.get_local_time() + date::days{ day_stride };
				sun_element_location.set(sun_element_location.name, sun_element_location.observer_latitude, sun_element_location.observer_longitude, sun_time);
			}
			std::cout << std::endl;
			std::cout << "Location : " << sun_element_location.name << std::endl;
    
			distmax_copy = distmax;
			int distmax_ceil = ceil(distmax);
			distmin_copy = distmin;
			int distmin_floor = floor(distmin);	
			double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		
			/* Plot the chart */
			
			double yearly_DLI = 0.0; julian_last = 0;
			for (std::tuple<double, double, double, zoned_sun_time> element : rad_map)
			{
				int day = std::get<0>(element);
				double distance = std::get<1>(element);
				double temp = std::get<2>(element);
				zoned_sun_time sun_time_location = std::get<3>(element);
				yearly_DLI += distance;
			
			
				//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
				if(1)
				{

					std::cout << date::format("%b %d %Y", sun_time_location) << " : " << FG_GREEN << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
				
					if ((distance) >= (distmax_copy))
					{
						std::cout << FG_GREEN << " <-max- DLI (MJ / m^2 day)" << FG_DEFAULT;
					}
            
					if ((distance) <= (distmin_copy))
					{
						std::cout << FG_GREEN << " <-min- DLI (MJ / m^2 day)" << FG_DEFAULT;
					}
					std::cout << std::endl;
				}	    
        
			}
			std::cout << std::endl;	
			std::cout << "Yearly DLI : " << yearly_DLI << " (MJ / m^2 year)" << std::endl;
			rad_map.clear();
		}
	
	} while (0);	
}


void test_dlimap_tests()
{
		
	/*************/
	/* Calculate the dli on the min/max solar radiation days. */
	std::cout << "****************************************************************************************************************************************" << std::endl;
	std::cout << "******************************************* DLI by latitude and year day **************************************************************" << std::endl;
	std::cout << "****************************************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time location;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, double>> rad_map;
		
		int day_stride = 3;
		std::cout << "LAT     1" <<  std::string((round(365 / day_stride) - 10) / 2, ' ') << "day" <<  std::string((round(365 / day_stride) - 1) / 2, ' ') << "365   Total(yr)" << std::endl;
		
		for (int calc_latitude = 84; calc_latitude >= -84; calc_latitude -= 2)
		{
			double total_irrad = 0.0;
			
			location = date::make_zoned("UTC", date::local_days{ date::days(0) } + std::chrono::hours(0));
			for (int day = 0; day < 365; day += day_stride)
			{
				/* Find the solar noons and the incident radiation max/mins throughout the year. */
				/* Find solar noon for today. */
				location = location.get_local_time() + date::days{ day_stride };
				
				sun_element_newyork.set("UTC", calc_latitude, -73.935242, location);
			
				/* Determine radiation. */
				double distance = dli.calculate_dli(location, &sun_element_newyork, ATOM_NONE);
			
				/* Save this information. */
				rad_map.push_back(std::tuple<double, double, double>((double)day, distance, calc_latitude));
			}
		
			/* Plot the chart */

			for (std::tuple<double, double, double> element : rad_map)
			{
				int day = std::get<0>(element);
				double distance = std::get<1>(element);
				double calc_latitude = std::get<2>(element);
				
				if (day == 0) std::cout << boost::format("%-5.1f")  % calc_latitude << " : ";
				
				total_irrad += distance;
				
				//if ((day % day_stride == 0))
				if(1)
				{

					if ((distance) >= (40))
					{
						std::cout << BG_RED << " " << FG_DEFAULT << BG_DEFAULT;
					}	
					else if ((distance) >= (35))
					{
						std::cout << BG_MAGENTA << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (30))
					{
						std::cout << BG_ORANGE << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (25))
					{
						std::cout << BG_YELLOW << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (20))
					{
						std::cout << BG_LIGHT_YELLOW  << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (15))
					{
						std::cout << BG_LIGHT_GREEN  << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (10))
					{
						std::cout << BG_GREEN << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (5))
					{
						std::cout << BG_CYAN << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (3))
					{
						std::cout << BG_LIGHT_BLUE  << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (2))
					{
						std::cout << BG_BLUE << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (0))
					{
						std::cout << BG_LIGHT_BLACK << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else
					{
						std::cout << BG_DARK_GRAY << " " << FG_DEFAULT << BG_DEFAULT;
					}
				}    
			} 
			std::cout << " : " << total_irrad << std::endl;
			rad_map.clear();
			
		} /* end calc_longitude */

		std::cout << "Legend:" << std::endl;	
		std::cout << "MJ/m^2 day :" << FG_RED << "* >40 \t" << FG_MAGENTA << "* >35 \t" << FG_ORANGE << "* >30 \t" << FG_YELLOW << "* >25 \t" << FG_LIGHT_YELLOW << "* >20 \t" << FG_DEFAULT << BG_DEFAULT << std::endl;
		std::cout << "MJ/m^2 day :" << FG_LIGHT_GREEN << "* >15 \t" << FG_GREEN << "* >10 \t" << FG_CYAN << "* >5 \t" << FG_LIGHT_BLUE << "* >3 \t" << FG_LIGHT_BLACK << "* >=0 \t" << FG_DEFAULT << BG_DEFAULT << std::endl;
		std::cout << std::endl;	
	} while (0) ;	
}


void test_dlimap_atom_tests()
{
		
	/*************/
	/* Calculate the dli on the min/max solar radiation days. */
	std::cout << "****************************************************************************************************************************************" << std::endl;
	std::cout << "******************************************* DLI by latitude and year day **************************************************************" << std::endl;
	std::cout << "****************************************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time location;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, double>> rad_map;
		
		int day_stride = 3;
		std::cout << "LAT     1" <<  std::string((round(365 / day_stride) - 10) / 2, ' ') << "day" <<  std::string((round(365 / day_stride) - 1) / 2, ' ') << "365   Total(yr)" << std::endl;
		
		for (int calc_latitude = 84; calc_latitude >= -84; calc_latitude -= 2)
		{
			double total_irrad = 0.0;
			
			location = date::make_zoned("UTC", date::local_days{ date::days(0) } + std::chrono::hours(0));
			for (int day = 0; day < 365; day += day_stride)
			{
				/* Find the solar noons and the incident radiation max/mins throughout the year. */
				/* Find solar noon for today. */
				location = location.get_local_time() + date::days{ day_stride };
				
				sun_element_newyork.set("UTC", calc_latitude, -73.935242, location);
			
				/* Determine radiation. */
				double distance = dli.calculate_dli(location, &sun_element_newyork, ATOM_BIRD);
			
				/* Save this information. */
				rad_map.push_back(std::tuple<double, double, double>((double)day, distance, calc_latitude));
			}
		
			/* Plot the chart */

			for (std::tuple<double, double, double> element : rad_map)
			{
				int day = std::get<0>(element);
				double distance = std::get<1>(element);
				double calc_latitude = std::get<2>(element);
				
				if (day == 0) std::cout << boost::format("%-5.1f")  % calc_latitude << " : ";
				
				total_irrad += distance;
				
				//if ((day % day_stride == 0))
				if(1)
				{

					if ((distance) >= (30))
					{
						std::cout << BG_RED << " " << FG_DEFAULT << BG_DEFAULT;
					}	
					else if ((distance) >= (25))
					{
						std::cout << BG_MAGENTA << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (20))
					{
						std::cout << BG_ORANGE << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (15))
					{
						std::cout << BG_YELLOW << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (10))
					{
						std::cout << BG_LIGHT_YELLOW  << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (8))
					{
						std::cout << BG_LIGHT_GREEN  << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (6))
					{
						std::cout << BG_GREEN << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (4))
					{
						std::cout << BG_CYAN << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (2))
					{
						std::cout << BG_LIGHT_BLUE  << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (1))
					{
						std::cout << BG_BLUE << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else if ((distance) >= (0))
					{
						std::cout << BG_LIGHT_BLACK << " " << FG_DEFAULT << BG_DEFAULT;
					}
					else
					{
						std::cout << BG_DARK_GRAY << " " << FG_DEFAULT << BG_DEFAULT;
					}
				}    
			} 
			std::cout << " : " << total_irrad << std::endl;
			rad_map.clear();
			
		} /* end calc_longitude */

		std::cout << "Legend:" << std::endl;	
		std::cout << "MJ/m^2 day :" << FG_RED << "* >40 \t" << FG_MAGENTA << "* >35 \t" << FG_ORANGE << "* >30 \t" << FG_YELLOW << "* >25 \t" << FG_LIGHT_YELLOW << "* >20 \t" << FG_DEFAULT << BG_DEFAULT << std::endl;
		std::cout << "MJ/m^2 day :" << FG_LIGHT_GREEN << "* >15 \t" << FG_GREEN << "* >10 \t" << FG_CYAN << "* >5 \t" << FG_LIGHT_BLUE << "* >3 \t" << FG_LIGHT_BLACK << "* >=0 \t" << FG_DEFAULT << BG_DEFAULT << std::endl;
		std::cout << std::endl;	
	} while (0) ;
		
}




void test_dli_tests()
{
	/*************/
	/* DLI tests */
	/* Calculate the extraterrestrial radiation per each day of a year normal to the plane of the sun. */
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Extraterrestrial radiation normal to solar radiation ***************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time newyork_area;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		
		double solar_noon;
		
		double distmax, distmax_copy, distmin_copy, distmin = 5000.0;
		int day_stride = 4;
		
		for (int day = 0; day < 365; day += day_stride)
		{
			/* Find the day with the maximum and minimum amounts of daylight. */
			newyork_area = date::make_zoned("America/Phoenix", date::local_days{ date::January / 01 / 2018 } + std::chrono::hours(12) + date::days(day));
			sun_element_newyork.set("Pheonix", 33.448376, -112.074036, newyork_area);
			solar_noon = sun_element_newyork.solar_noon;
			
			/* Calculate sun position at solar noon. */
			auto time_hms = sun_element_newyork.fp_days_to_chrono(solar_noon);
			auto time_hmsd = date::local_days{ date::days(day) } + time_hms;
			newyork_area = date::make_zoned("America/Phoenix", time_hmsd);
			sun_element_newyork.set("Pheonix", 40.730610, -73.935242, newyork_area);
			
			double distance = SOLAR_CONSTANT * dli.calculate_extraterestrial_radiation(sun_element_newyork.rad_vector);
			
			/* Save this information. */
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
        
			if (distance > distmax) distmax = distance;
			if (distance < distmin) distmin = distance;
		}
    
		distmax_copy = distmax;
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		/* Plot the chart */
		
		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);		
        
			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y", newyork_area) << ": " << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
        
				if ((distance) >= (distmax_copy))
				{
					std::cout << " <-max- " << distance  << " W/m^2";
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << " <-min- " << distance << " W/m^2";
				}
        
				std::cout << std::endl;
			}	    
		}
		
		std::cout << std::endl;
	
	} while (0);
	
	
	

	/*************/
	/* Calculate the extraterrestrial radiation per each day of a year tangent to the surface. */
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Extraterrestrial radiation tangent to surface **********************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time newyork_area;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		
		double distmax, distmax_copy, distmin_copy, distmin = 5000.0;
		int day_stride = 4;
		
		for (int day = 0; day < 365; day += day_stride)
		{
			/* Find the solar noons and the incident radiation max/mins throughout the year. */
			/* Find solar noon for today. */
			newyork_area = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 } + std::chrono::hours(12) + date::days(day));
			sun_element_newyork.set("New York", 40.730610, -73.935242, newyork_area);
			
			double solar_noon = sun_element_newyork.solar_noon;
			
			/* Calculate sun position at solar noon. */
			auto time_hms = sun_element_newyork.fp_days_to_chrono(solar_noon);
			//auto time_hmsd = date::local_days{ date::January / 01 / 2018 } + time_hms + date::days(day);
			auto time_hmsd = date::local_days{ date::days(day) } + time_hms;
			newyork_area = date::make_zoned("America/New_York", time_hmsd);
			sun_element_newyork.set("New York", 40.730610, -73.935242, newyork_area);
			
			/* Determine radiation. */
			double radiation = dli.calculate_extraterestrial_radiation(sun_element_newyork.rad_vector);
			double distance = SOLAR_CONSTANT * dli.calculate_incident_surface_irradiation(radiation, sun_element_newyork.solar_elevation_corrected);
			/* Save this information. */
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
        
			if (distance > distmax) distmax = distance;
			if (distance < distmin) distmin = distance;
		}
    
		distmax_copy = distmax;
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		/* Plot the chart */

		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);

			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y %R", newyork_area) << " : " << FG_GREEN << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
        
				if ((distance) >= (distmax_copy))
				{
					std::cout << FG_GREEN << " <-max- W/m^2" << FG_DEFAULT;
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << FG_GREEN << " <-min- W/m^2" << FG_DEFAULT;
				}
				std::cout << std::endl;
			}	    
        
		}
		std::cout << std::endl;
	
	} while (0) ;
	
	
	
	
	
	
	
	/*************/
	/* Calculate the dli on the min/max solar radiation days. */
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Min / Max DLI solar radiation days *********************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time newyork_area;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		int day_stride = 4;
		
		std::cout << "Calculating : ";
		newyork_area = date::make_zoned("America/Guayaquil", date::local_days{ date::January / 01 / 2018 });
		double distmax, distmax_copy, distmin_copy, distmin = 5000.0; double julian_last = 0;
		for (int day = 0; day < 365; day += day_stride)
		{
			if (day % 5 == 0) std::cout << "." << std::flush;
			/* Find the solar noons and the incident radiation max/mins throughout the year. */
			/* Find solar noon for today. */
			//newyork_area = date::make_zoned("America/Guayaquil", date::local_days{ date::days(day) });
			newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
			sun_element_newyork.set("Quito, Ecuador", -0.22985, -78.52495, newyork_area);
			
			if (julian_last == 274)
			{
				double distance = dli.calculate_dli(newyork_area, &sun_element_newyork, ATOM_BIRD);
			}
			else if (julian_last == 275)
			{
				double distance = dli.calculate_dli(newyork_area, &sun_element_newyork, ATOM_BIRD);
			}
			julian_last++;
			
			/* Determine radiation. */
			double distance = dli.calculate_dli(newyork_area, &sun_element_newyork, ATOM_BIRD);
			
			/* Save this information. */
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
			if (distance > distmax)
			{
				distmax = distance;
			}
			if (distance < distmin) 
			{
				distmin = distance;
			}
		}
		std::cout << std::endl;
    
		distmax_copy = distmax;
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		
		/* Plot the chart */
		
		double yearly_DLI = 0.0; julian_last = 0;
		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);
			yearly_DLI += distance;
			
			
			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y", newyork_area) << " : " << julian_last << " : " << FG_GREEN << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
				julian_last++;
				
				if ((distance) >= (distmax_copy))
				{
					std::cout << FG_GREEN << " <-max- DLI" << FG_DEFAULT;
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << FG_GREEN << " <-min- DLI" << FG_DEFAULT;
				}
				std::cout << std::endl;
			}	    
        
		}
		std::cout << std::endl;	
		std::cout << "Yearly DLI : " << yearly_DLI << std::endl;
	} while (0) ;
	
	
	
	
	
	
	/*************/
	/* Calculate the dli on the min/max solar radiation days. */
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Min / Max DLI solar radiation days *********************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{
		Daily_Light dli;
		zoned_sun_time newyork_area;
		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		
		std::cout << "Calculating : ";
		double distmax, distmax_copy, distmin_copy, distmin = 5000.0;
		int day_stride = 4;
		
		newyork_area = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 } + std::chrono::hours(0));
		for (int day = 0; day < 365; day += day_stride)
		{
			if (day % 5 == 0) std::cout << "." << std::flush;
			/* Find the solar noons and the incident radiation max/mins throughout the year. */
			/* Find solar noon for today. */
			//newyork_area = date::make_zoned("America/New_York", date::local_days{ date::days(day) });
			newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
			sun_element_newyork.set("New York", 40.730610, -73.935242, newyork_area);

			/* Determine radiation. */
			double distance = dli.calculate_dli(newyork_area, &sun_element_newyork, ATOM_BIRD);
			
			/* Save this information. */
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
			if (distance > distmax)
			{
				distmax = distance;
			}
			if (distance < distmin) 
			{
				distmin = distance;
			}
		}
		std::cout << std::endl;
    
		distmax_copy = distmax;
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		
		/* Plot the chart */
		
		double yearly_DLI = 0.0;
		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);
			yearly_DLI += distance;

			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y", newyork_area) << " : " << FG_GREEN << std::string(round(((distance) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " : " << FG_YELLOW << distance << FG_DEFAULT;
        
				if ((distance) >= (distmax_copy))
				{
					std::cout << FG_GREEN << " <-max- DLI" << FG_DEFAULT;
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << FG_GREEN << " <-min- DLI" << FG_DEFAULT;
				}
				std::cout << std::endl;
			}	    
        
		}
		std::cout << std::endl;	
		std::cout << "Yearly DLI : " << yearly_DLI << std::endl;
	} while (0) ;
	
}
