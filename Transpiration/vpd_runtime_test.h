//
// vpd_runtime_test.h
// Version timestamp: 9-4-2018, 4:24 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <ostream>
#include <boost/format.hpp>
#include "vpd.h"
class vpd_runtime_test : public vpd, celcius
{
public:
	vpd_runtime_test();
	~vpd_runtime_test();
	void print_table(celcius temperature, float actual_humidity, float temperature_difference, float min, float max);
	float print_status(float vapor_pressure_deficit, float min_vpd, float max_vpd);
	float check_vpd(celcius temperature, float humidity, float min_vpd, float max_vpd);
	float check_vpd(vpd vapor_pressure, float min_vpd, float max_vpd);
	float check_vpd(celcius temperature, celcius leaf_temperature, float humidity, float min_vpd, float max_vpd);
	float check_vpd_and_print(celcius temperature, float humidity, float min_vpd, float max_vpd);
	float check_vpd_and_print(vpd vapor_pressure, float min_vpd, float max_vpd);
	float check_vpd_and_print(celcius temperature, celcius leaf_temperature, float humidity, float min_vpd, float max_vpd);
	double calc_boundary(celcius temperature, celcius leaf_temperature, float humidity);
};

