#include "SunTest.h"

/*
	To test the library, include "Sun.h" from an application project
	and call SunTest().
	
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

int SunTest()
{
	test_sun_tests_multi();
	test_sun_tests();
	return ++s_Test;
}

void test_sun_tests_multi()
{
	
	/**********************/
	/* Sun tracking tests */
	
	do 
	{
		sun sun_element;
		std::vector<sun> sun_info_vec;
		zoned_sun_time moscow = date::make_zoned("Europe/Moscow", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time chicago = date::make_zoned("America/Chicago", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time newzealand = date::make_zoned("Pacific/Auckland", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time newyork_area = date::make_zoned("America/Guayaquil", date::local_time<date::days>{ date::January / 01 / 2018 });
		zoned_sun_time quito = date::make_zoned("America/Guayaquil", date::local_days{ date::January / 01 / 2018 });
		
		sun_element.set("Moscow", 55.751244, 37.618423, moscow);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Chicago", 41.881832, -87.623177, chicago);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Auckland,NZ", -36.848461, 174.763336, newzealand);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Chelmsford, MA", 42.5998, -71.3673, newyork_area);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Quito, Ecuador", -0.22985, -78.52495, quito);
		sun_info_vec.push_back(sun_element);
		
	
		for (sun element : sun_info_vec)
		{
			std::cout << "********************************************************************************************************************" << std::endl;
			std::cout << "*********************** Daylight hours *****************************************************************************" << std::endl;
			std::cout << "********************************************************************************************************************" << std::endl;
			std::cout << "Location : " << element.name << std::endl;
			/* Calculate and plot the daylight hours over the course of a year for New York, find the minimum and maximum daylight hours. */
	
			std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
			zoned_sun_time *sun_time = element.zone_time;
			double daymax = 0.0; 
			double daymax_copy;
			double daymin_copy = 0.0;
			double daymin = 1.0;
			int day_stride = 4;
			
	
			for (int day = 1; day < 365; day += day_stride)
			{
				/* Find the day with the maximum and minimum amounts of daylight. */
				element.set(element.name, element.observer_latitude, element.observer_longitude, *sun_time);
				double daylength = element.daylength();
        
				if (daylength > daymax) daymax = daylength;
				if (daylength < daymin) daymin = daylength;
		
				rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, daylength, *sun_time));
        
				*sun_time = sun_time->get_local_time() + date::days{ day_stride };
			}
    
			daymax_copy = daymax;
			daymax *= 60.0;
			int daymax_ceil = ceil(daymax);
			daymin_copy = daymin;
			daymin *= 60.0;
			int daymin_floor = floor(daymin);	
			double chart_x_quant = 96 / (daymax_ceil - daymin_floor);

			/* Plot the chart */
			
			for (std::tuple<double, double, zoned_sun_time> element : rad_map)
			{
				int day = std::get<0>(element);
				double daylength = std::get<1>(element);
				newyork_area = std::get<2>(element);
        
				//if ((daylength) >= (daymax_copy) || (daylength) <= (daymin_copy) /*|| (day % day_stride == 0)*/)
				if(1)
				{
					if ((daylength * 60) > 14)
					{
						std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_GREEN << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*') << FG_DEFAULT;
					}
					else if ((daylength * 60) > 12)
					{
						std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_YELLOW << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*') << FG_DEFAULT;
					}
					else if ((daylength * 60) > 10)
					{
						std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_RED << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*') << FG_DEFAULT;
					}
					else
					{
						std::cout << date::format("%b %d %Y", newyork_area) << ": " << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*');
					}
        
					if ((daylength) >= (daymax_copy))
					{
						length_of_day length(daylength);
						std::cout << " <-max- " << length;
					}
            
					if ((daylength) <= (daymin_copy))
					{
						length_of_day length(daylength);
						std::cout << " <-min- " << length;
					}
        
					std::cout << std::endl;
				}	    
        
				newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
			}
			std::cout << std::endl;
		} /* end for sun element vector */
	} while (0);
	
	do 
	{
		sun sun_element;
		std::vector<sun> sun_info_vec;
		zoned_sun_time moscow = date::make_zoned("Europe/Moscow", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time chicago = date::make_zoned("America/Chicago", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time newzealand = date::make_zoned("Pacific/Auckland", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time newyork_area = date::make_zoned("America/Guayaquil", date::local_time<date::days>{ date::January / 01 / 2018 });
		zoned_sun_time quito = date::make_zoned("America/Guayaquil", date::local_days{ date::January / 01 / 2018 });
		
		sun_element.set("Moscow", 55.751244, 37.618423, moscow);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Chicago", 41.881832, -87.623177, chicago);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Auckland,NZ", -36.848461, 174.763336, newzealand);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Chelmsford, MA", 42.5998, -71.3673, newyork_area);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Quito, Ecuador", -0.22985, -78.52495, quito);
		sun_info_vec.push_back(sun_element);
		
		for (sun element : sun_info_vec)
		{

			std::cout << "********************************************************************************************************************" << std::endl;
			std::cout << "*********************** Earth distance from the sun ****************************************************************" << std::endl;
			std::cout << "********************************************************************************************************************" << std::endl;
			std::cout << "Location : " << element.name << std::endl;

			/********************/
			/* Calculate and plot the distance over the course of a year for New York, find the minimum and maximum distance. */
			
			std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
			zoned_sun_time *sun_time = element.zone_time;
			int day_stride = 4;

			double distmax = 0;
			double distmax_copy = 0;
			double distmin_copy = 0;
			double distmin = 1.0;
			
			for (int day = 1; day < 365; day += day_stride)
			{
				/* Find the day with the maximum and minimum amounts of daylight. */
				element.set(element.name, element.observer_latitude, element.observer_longitude, *sun_time);
				double distance = element.rad_vector;
				rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, *sun_time));
			
				if (distance > distmax) distmax = distance;
				if (distance < distmin) distmin = distance;
        
				*sun_time = sun_time->get_local_time() + date::days{ day_stride };
			}
    
			distmax_copy = distmax;
			distmax *= (AU_KM);
			int distmax_ceil = ceil(distmax);
			distmin_copy = distmin;
			distmin *= (AU_KM);
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

					std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_YELLOW << std::string(round(((distance * (AU_KM)) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " :" << distance;
        
					if ((distance) >= (distmax_copy))
					{
						std::cout << " <-max- " << distance * (AU_KM) << " kilometers";
					}
            
					if ((distance) <= (distmin_copy))
					{
						std::cout << " <-min- " << distance * (AU_KM) << " kilometers";
					}
        
					std::cout << std::endl;
				}	    
        
				newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
			}
			std::cout << std::endl;
		}
	
	} while (0);
		
	
	do
	{
		std::cout << "********************************************************************************************************************" << std::endl;
		std::cout << "*********************** Sunrise, Sunset, Daylength, Zeniths ********************************************************" << std::endl;
		std::cout << "********************************************************************************************************************" << std::endl;
		/***************/
		zoned_sun_time shanghai = date::make_zoned("Asia/Shanghai", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time losangeles = date::make_zoned("America/Los_Angeles", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time sydney = date::make_zoned("Australia/Sydney", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time newyork = date::make_zoned("America/New_York", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time moscow = date::make_zoned("Europe/Moscow", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time chicago = date::make_zoned("America/Chicago", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time newzealand = date::make_zoned("Pacific/Auckland", date::local_days{ date::December / 01 / 2017 });
		zoned_sun_time quito = date::make_zoned("America/Guayaquil", date::local_days{ date::December / 01 / 2017 });

		std::time_t t = std::time(nullptr);
		std::tm timeinfo = *std::localtime(&t);
	
		std::vector<sun> sun_info_vec;
		sun sun_element;
		std::string months_of_year[] = { "December", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		for (int month = 1; month < 13; month++)
		{
			shanghai = shanghai.get_local_time() + date::months{ 1 };
			losangeles = losangeles.get_local_time() + date::months{ 1 };
			sydney = sydney.get_local_time() + date::months{ 1 };
			newyork = newyork.get_local_time() + date::months{ 1 };
			moscow = moscow.get_local_time() + date::months{ 1 };
			chicago = chicago.get_local_time() + date::months{ 1 };
			newzealand = newzealand.get_local_time() + date::months{ 1 };
			quito = quito.get_local_time() + date::months{ 1 };
		
			sun sun_element("Shanghai", 31.22222, 121.45806, shanghai);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Los Angeles", 34.052235, -118.243683, losangeles);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Sydney", -33.865143, 151.209900, sydney);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Chelmsford, MA", 42.5998, -71.3673, newyork);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Moscow", 55.751244, 37.618423, moscow);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Chicago", 41.881832, -87.623177, chicago);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Auckland,NZ", -36.848461, 174.763336, newzealand);
			sun_info_vec.push_back(sun_element);
			sun_element.set("Quito, Ecuador", -0.22985, -78.52495, quito);
			sun_info_vec.push_back(sun_element);

			std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
			std::cout << months_of_year[month] << std::endl;
			std::cout << boost::format("%-16s")  % "Location" <<  boost::format("%-24s")  % "Lat/Lon" <<  boost::format("%-24s")  % "Sunrise" <<  boost::format("%-24s")  % "Sunset" <<  boost::format("%-32s")  % "Daylength" <<  boost::format("%-10s")  % "Zenith" <<  boost::format("%-10s")  % "Elevation";
			std::cout << std::endl;
		
			for (sun element : sun_info_vec)
			{
				std::string latlon = "(" + std::to_string(element.observer_latitude) + "," + std::to_string(element.observer_longitude) + ")";
				std::cout << boost::format("%-16s")  % element.name <<  boost::format("%-24s")  % latlon <<  boost::format("%-24s")  % to_simple_string(element.sunrise_time) <<  boost::format("%-24s")  % to_simple_string(element.sunset_time) <<  boost::format("%-32s")  % element.daylength <<  boost::format("%-10.2f")  % element.zenith_angle <<  boost::format("%-10.2f")  % element.solar_elevation;
				std::cout << std::endl;
			}
		
			sun_info_vec.clear();
			std::cout << std::endl;
		}
			
	} while (0);
	
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Seasons ************************************************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	/***************/
	zoned_sun_time shanghai1 = date::make_zoned("Asia/Shanghai", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time losangeles1 = date::make_zoned("America/Los_Angeles", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time sydney1 = date::make_zoned("Australia/Sydney", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time newyork1 = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time moscow1 = date::make_zoned("Europe/Moscow", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time chicago1 = date::make_zoned("America/Chicago", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time newzealand1 = date::make_zoned("Pacific/Auckland", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time quito1 = date::make_zoned("America/Guayaquil", date::local_days{ date::January / 01 / 2018 });
	
	std::vector<sun> sun_info_vec1;
	sun sun_element1("Shanghai", 31.22222, 121.45806, shanghai1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Los Angeles", 34.052235, -118.243683, losangeles1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Sydney", -33.865143, 151.209900, sydney1);
	sun_info_vec1.push_back(sun_element1);
	sun sun_element2("Chelmsford,MA", 42.5998, -71.3673, newyork1);
	sun_info_vec1.push_back(sun_element2);
	sun_element1.set("Moscow", 55.751244, 37.618423, moscow1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Chicago", 41.881832, -87.623177, chicago1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Auckland,NZ", -36.848461, 174.763336, newzealand1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Quito, Ecuador", -0.22985, -78.52495, quito1);
	sun_info_vec1.push_back(sun_element1);
	
	std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << boost::format("%-16s")  % "Location" <<  boost::format("%-32s")  % "Vernal Equinox" <<  boost::format("%-32s")  % "Summer Solstice" <<  boost::format("%-32s")  % "Fall Equinox" <<  boost::format("%-32s")  % "Winter Solstice" <<  boost::format("%-32s")  % "Total";
	std::cout << std::endl;
		
	for (sun element : sun_info_vec1)
	{
		
		element.set_length_of_seasons(element.zone_time);
		std::string latlon = "(" + std::to_string(element.observer_latitude) + "," + std::to_string(element.observer_longitude) + ")";
		std::cout << boost::format("%-16s")  % element.name <<  boost::format("%-32s")  % element.seasons.julian_nw_equinox <<  boost::format("%-32s")  % element.seasons.julian_n_solstice <<  boost::format("%-32s")  % element.seasons.julian_sw_equinox <<  boost::format("%-32s")  % element.seasons.julian_s_solstice;
		std::cout << std::endl;
	}
	
	std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << boost::format("%-16s")  % "Location" <<  boost::format("%-32s")  % "Length of Spring" <<  boost::format("%-32s")  % "Length of Summer" <<  boost::format("%-32s")  % "Length of Fall" <<  boost::format("%-32s")  % "Length of Winter";
	std::cout << std::endl;
		
	for (sun element : sun_info_vec1)
	{
		element.set_length_of_seasons(element.zone_time);
		std::string latlon = "(" + std::to_string(element.observer_latitude) + "," + std::to_string(element.observer_longitude) + ")";
		std::cout << boost::format("%-16s")  % element.name <<  boost::format("%-32s")  % element.seasons.LengthOfSpring <<  boost::format("%-32s")  % element.seasons.LengthOfSummer <<  boost::format("%-32s")  % element.seasons.LengthOfAutumn <<  boost::format("%-32s")  % element.seasons.LengthOfWinter;
		std::cout << std::endl;
	}
	sun_info_vec1.clear();
	std::cout << std::endl;
	
}


void test_sun_tests()
{
	
	/**********************/
	/* Sun tracking tests */
	
	//	std::stringstream str("01.01.2018 00:00:01.0000");
	//	//str.imbue(std::locale());
	//	std::chrono::time_point< std::chrono::system_clock, std::chrono::milliseconds > result;
	//	date::from_stream(str, "%d.%m.%Y %H:%M:%S", result);
	//	std::cout << result.time_since_epoch().count() << std::endl;
	//	zoned_sun_time newyork = date::make_zoned("America/New_York", result);
	//	std::cout << newyork << '\n' << std::endl;
	//	zoned_sun_time chicago = date::make_zoned("America/Chicago", result);
	//	std::cout << chicago << '\n' << std::endl;
	//	chicago = date::make_zoned("America/Chicago", date::local_time<date::days>{ date::January / 01 / 2018 });
	//	std::cout << chicago << '\n' << std::endl;
	
		//zoned_sun_time newyork = date::make_zoned("America/New_York", date::sys_time{ date::January / 01 / 2018 } );
		//zoned_sun_time newyork = date::make_zoned("America/New_York", date::local_time<date::days>{ date::January / 01 / 2018 });
		//zoned_sun_time newyork = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 });
		//zoned_sun_time newyork = date::make_zoned("America/New_York", std::chrono::system_clock::now() + std::chrono::system_clock::now());
	
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Daylight hours *****************************************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	/* Calculate and plot the daylight hours over the course of a year for New York, find the minimum and maximum daylight hours. */
	zoned_sun_time newyork_area = date::make_zoned("America/New_York", date::local_time<date::days>{ date::January / 01 / 2018 });

	sun sun_element_newyork;
	std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
	double daymax, daymax_copy, daymin_copy, daymin = 1.0;
	int day_stride = 4;
	
	for (int day = 1; day < 365; day += day_stride)
	{
		/* Find the day with the maximum and minimum amounts of daylight. */
		sun_element_newyork.set("New York", 40.730610, -73.935242, newyork_area);
		double daylength = sun_element_newyork.daylength();
        
		if (daylength > daymax) daymax = daylength;
		if (daylength < daymin) daymin = daylength;
		
		rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, daylength, newyork_area));
        
		newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
	}
    
	daymax_copy = daymax;
	daymax *= 60.0;
	int daymax_ceil = ceil(daymax);
	daymin_copy = daymin;
	daymin *= 60.0;
	int daymin_floor = floor(daymin);	
	double chart_x_quant = 96 / (daymax_ceil - daymin_floor);

	/* Plot the chart */
	
	for (std::tuple<double, double, zoned_sun_time> element : rad_map)
	{
		int day = std::get<0>(element);
		double daylength = std::get<1>(element);
		newyork_area = std::get<2>(element);
        
		//if ((daylength) >= (daymax_copy) || (daylength) <= (daymin_copy) /*|| (day % day_stride == 0)*/)
		if(1)
		{
			if ((daylength * 60) > 14)
			{
				std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_GREEN << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*') << FG_DEFAULT;
			}
			else if ((daylength * 60) > 12)
			{
				std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_YELLOW << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*') << FG_DEFAULT;
			}
			else if ((daylength * 60) > 10)
			{
				std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_RED << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*') << FG_DEFAULT;
			}
			else
			{
				std::cout << date::format("%b %d %Y", newyork_area) << ": " << std::string(round(((daylength * 60.0) - daymin)*chart_x_quant), '*');
			}
        
			if ((daylength) >= (daymax_copy))
			{
				length_of_day length(daylength);
				std::cout << " <-max- " << length;
			}
            
			if ((daylength) <= (daymin_copy))
			{
				length_of_day length(daylength);
				std::cout << " <-min- " << length;
			}
        
			std::cout << std::endl;
		}	    
        
		newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
	}
	std::cout << std::endl;
    
	
	
	
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Earth distance from the sun ****************************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	do
	{

		/********************/
		/* Calculate and plot the distance over the course of a year for New York, find the minimum and maximum distance. */
		zoned_sun_time newyork_area = date::make_zoned("America/New_York", date::local_time<date::days>{ date::January / 01 / 2018 });
		std::cout << newyork_area << '\n' << std::endl;

		sun sun_element_newyork;
		std::list<std::tuple<double, double, zoned_sun_time>> rad_map;
		double distmax, distmax_copy, distmin_copy, distmin = 1.0;
		int day_stride = 4;
		
		for (int day = 1; day < 365; day += day_stride)
		{
			/* Find the day with the maximum and minimum amounts of daylight. */
			sun_element_newyork.set("New York", 40.730610, -73.935242, newyork_area);
			double distance = sun_element_newyork.rad_vector;
			rad_map.push_back(std::tuple<double, double, zoned_sun_time>((double)day, distance, newyork_area));
			
			if (distance > distmax) distmax = distance;
			if (distance < distmin) distmin = distance;
        
			newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
		}
    
		distmax_copy = distmax;
		distmax *= (AU_KM);
		int distmax_ceil = ceil(distmax);
		distmin_copy = distmin;
		distmin *= (AU_KM);
		int distmin_floor = floor(distmin);	
		double chart_x_quant = 96.0 / (distmax_ceil - distmin_floor);

		/* Plot the chart */
		
		for (std::tuple<double, double, zoned_sun_time> element : rad_map)
		{
			//newyork_area = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 });
			//for (int day = 1; day < 365; day += 1)
			//{
				//sun_element_newyork.set("New York", 40.730610, -73.935242, newyork_area);
				//double distance = sun_element_newyork.rad_vector;
			
			int day = std::get<0>(element);
			double distance = std::get<1>(element);
			newyork_area = std::get<2>(element);
        
			//if ((distance) >= (distmax_copy) || (distance) <= (distmin_copy) /*|| (day % day_stride == 0)*/)
			if(1)
			{

				std::cout << date::format("%b %d %Y", newyork_area) << ": " << FG_YELLOW << std::string(round(((distance * (AU_KM)) - distmin)*chart_x_quant), '*') << FG_DEFAULT << " :" << distance;
        
				if ((distance) >= (distmax_copy))
				{
					std::cout << " <-max- " << distance * (AU_KM) << " kilometers";
				}
            
				if ((distance) <= (distmin_copy))
				{
					std::cout << " <-min- " << distance * (AU_KM) << " kilometers";
				}
        
				std::cout << std::endl;
			}	    
        
			newyork_area = newyork_area.get_local_time() + date::days{ day_stride };
		}
		std::cout << std::endl;
	
	} while (0);
		
	
	
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Sunrise, Sunset, Daylength, Zeniths ********************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	/***************/
	zoned_sun_time shanghai = date::make_zoned("Asia/Shanghai", date::local_days{ date::December / 01 / 2017 });
	zoned_sun_time losangeles = date::make_zoned("America/Los_Angeles", date::local_days{ date::December / 01 / 2017 });
	zoned_sun_time sydney = date::make_zoned("Australia/Sydney", date::local_days{ date::December / 01 / 2017 });
	zoned_sun_time newyork = date::make_zoned("America/New_York", date::local_days{ date::December / 01 / 2017 });
	zoned_sun_time moscow = date::make_zoned("Europe/Moscow", date::local_days{ date::December / 01 / 2017 });
	zoned_sun_time chicago = date::make_zoned("America/Chicago", date::local_days{ date::December / 01 / 2017 });
	zoned_sun_time newzealand = date::make_zoned("Pacific/Auckland", date::local_days{ date::December / 01 / 2017 });

	std::time_t t = std::time(nullptr);
	std::tm timeinfo = *std::localtime(&t);
	
	std::vector<sun> sun_info_vec;
	sun sun_element;
	std::string months_of_year[] = { "December", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	for (int month = 1; month < 13; month++)
	{
		shanghai = shanghai.get_local_time() + date::months{ 1 };
		losangeles = losangeles.get_local_time() + date::months{ 1 };
		sydney = sydney.get_local_time() + date::months{ 1 };
		newyork = newyork.get_local_time() + date::months{ 1 };
		moscow = moscow.get_local_time() + date::months{ 1 };
		chicago = chicago.get_local_time() + date::months{ 1 };
		newzealand = newzealand.get_local_time() + date::months{ 1 };
		
		sun sun_element("Shanghai", 31.22222, 121.45806, shanghai);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Los Angeles", 34.052235, -118.243683, losangeles);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Sydney", -33.865143, 151.209900, sydney);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Chelmsford, MA", 42.5998, -71.3673, newyork);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Moscow", 55.751244, 37.618423, moscow);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Chicago", 41.881832, -87.623177, chicago);
		sun_info_vec.push_back(sun_element);
		sun_element.set("Auckland,NZ", -36.848461, 174.763336, newzealand);
		sun_info_vec.push_back(sun_element);

		std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << months_of_year[month] << std::endl;
		std::cout << boost::format("%-16s")  % "Location" <<  boost::format("%-24s")  % "Lat/Lon" <<  boost::format("%-24s")  % "Sunrise" <<  boost::format("%-24s")  % "Sunset" <<  boost::format("%-32s")  % "Daylength" <<  boost::format("%-10s")  % "Zenith" <<  boost::format("%-10s")  % "Elevation";
		std::cout << std::endl;
		
		for (sun element : sun_info_vec)
		{
			std::string latlon = "(" + std::to_string(element.observer_latitude) + "," + std::to_string(element.observer_longitude) + ")";
			std::cout << boost::format("%-16s")  % element.name <<  boost::format("%-24s")  % latlon <<  boost::format("%-24s")  % to_simple_string(element.sunrise_time) <<  boost::format("%-24s")  % to_simple_string(element.sunset_time) <<  boost::format("%-32s")  % element.daylength <<  boost::format("%-10.2f")  % element.zenith_angle <<  boost::format("%-10.2f")  % element.solar_elevation;
			std::cout << std::endl;
		}
		
		sun_info_vec.clear();
		std::cout << std::endl;
	}
	
	std::cout << "********************************************************************************************************************" << std::endl;
	std::cout << "*********************** Seasons ************************************************************************************" << std::endl;
	std::cout << "********************************************************************************************************************" << std::endl;
	/***************/
	zoned_sun_time shanghai1 = date::make_zoned("Asia/Shanghai", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time losangeles1 = date::make_zoned("America/Los_Angeles", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time sydney1 = date::make_zoned("Australia/Sydney", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time newyork1 = date::make_zoned("America/New_York", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time moscow1 = date::make_zoned("Europe/Moscow", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time chicago1 = date::make_zoned("America/Chicago", date::local_days{ date::January / 01 / 2018 });
	zoned_sun_time newzealand1 = date::make_zoned("Pacific/Auckland", date::local_days{ date::January / 01 / 2018 });
	
	std::vector<sun> sun_info_vec1;
	sun sun_element1("Shanghai", 31.22222, 121.45806, shanghai1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Los Angeles", 34.052235, -118.243683, losangeles1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Sydney", -33.865143, 151.209900, sydney1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Chelmsford, MA", 42.5998, -71.3673, newyork1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Moscow", 55.751244, 37.618423, moscow1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Chicago", 41.881832, -87.623177, chicago1);
	sun_info_vec1.push_back(sun_element1);
	sun_element1.set("Auckland,NZ", -36.848461, 174.763336, newzealand1);
	sun_info_vec1.push_back(sun_element1);
	
	std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << boost::format("%-16s")  % "Location" <<  boost::format("%-32s")  % "Vernal Equinox" <<  boost::format("%-32s")  % "Summer Solstice" <<  boost::format("%-32s")  % "Fall Equinox" <<  boost::format("%-32s")  % "Winter Solstice" <<  boost::format("%-32s")  % "Total";
	std::cout << std::endl;
		
	for (sun element : sun_info_vec1)
	{
		
		element.set_length_of_seasons(element.zone_time);
		std::string latlon = "(" + std::to_string(element.observer_latitude) + "," + std::to_string(element.observer_longitude) + ")";
		std::cout << boost::format("%-16s")  % element.name <<  boost::format("%-32s")  % element.seasons.julian_nw_equinox <<  boost::format("%-32s")  % element.seasons.julian_n_solstice <<  boost::format("%-32s")  % element.seasons.julian_sw_equinox <<  boost::format("%-32s")  % element.seasons.julian_s_solstice;
		std::cout << std::endl;
	}
	
	std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << boost::format("%-16s")  % "Location" <<  boost::format("%-32s")  % "Length of Spring" <<  boost::format("%-32s")  % "Length of Summer" <<  boost::format("%-32s")  % "Length of Fall" <<  boost::format("%-32s")  % "Length of Winter";
	std::cout << std::endl;
		
	for (sun element : sun_info_vec1)
	{
		element.set_length_of_seasons(element.zone_time);
		std::string latlon = "(" + std::to_string(element.observer_latitude) + "," + std::to_string(element.observer_longitude) + ")";
		std::cout << boost::format("%-16s")  % element.name <<  boost::format("%-32s")  % element.seasons.LengthOfSpring <<  boost::format("%-32s")  % element.seasons.LengthOfSummer <<  boost::format("%-32s")  % element.seasons.LengthOfAutumn <<  boost::format("%-32s")  % element.seasons.LengthOfWinter;
		std::cout << std::endl;
	}
	sun_info_vec1.clear();
	std::cout << std::endl;
	
}



