//
// integrate.cpp
// Version timestamp: 9-26-2018, 10:56 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "integrate.h"

using namespace boost::container;

integrate::integrate()
{
}

/* In this case, a user supplies a set of unique (x,y) values to integrate. */
integrate::integrate(flat_set<std::pair<double, double>> *by_point)
{
	integrate_by_point(by_point);
}

integrate::~integrate()
{
}

void integrate::integrate_by_point(flat_set<std::pair<double, double>> *by_point)
{
	/* Integrate the current set of values */
	if (by_point->size() > 1)
	{
		bool first = true;
		
		double x1, x2, y1, y2;
		for (std::pair<double, double> element : *by_point)
		{
			if (first)
			{
				first = false;
				x2 = element.first;
				y2 = element.second;
			}
			else
			{
				x1 = x2;
				y1 = y2;
				x2 = element.first;
				y2 = element.second;
				running_trapezodal_integral(x1, y1, x2, y2);
			}

		}
	}
	else
	{
		this->integral = 0.0;
	}
}

void integrate::operator()(flat_set<std::pair<double, double>> *by_point)
{
	this->integral = 0.0;
	integrate_by_point(by_point);
}

void integrate::clear()
{
	this->integral = 0.0;
}

void integrate::running_trapezodal_integral(double x1, double y1, double x2, double y2)
{
	/* Trapazodal integration. */
	double dt = (x2 - x1);
	this->integral += ((y2 + y1)*dt) * 0.5;
}