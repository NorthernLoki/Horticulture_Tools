//
// vpd_text_table.h
// Version timestamp: 9-4-2018, 4:24 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <ostream>
#include <boost/format.hpp>
#include "vpd.h"

class vpd_text_table : public vpd, celcius
{
public:
	vpd_text_table();
	vpd_text_table(float leaf_temperature_differential);
	~vpd_text_table();
	void print_table(float temperature_difference, float min, float max);
};


