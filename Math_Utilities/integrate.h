//
// integrate.h
// Version timestamp: 9-26-2018, 10:56 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <boost/container/flat_set.hpp>

class integrate
{
public:
	integrate();
	integrate(boost::container::flat_set<std::pair<double, double>> *by_point);
	~integrate();
	void clear();
	void integrate_by_point(boost::container::flat_set<std::pair<double, double>> *by_point);
	void running_trapezodal_integral(double x1, double y1, double x2, double y2);
	void operator()(boost::container::flat_set<std::pair<double, double>> *by_point);
	
	double integral;
};

