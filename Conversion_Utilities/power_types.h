//
// power_types.h
// Version timestamp: 10-25-2018, 6:55 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
// Power is defined as the amount of work over a specific amount of time.
// The conversions here should use the same time scales when performing the conversion. For instance,
// if you want to convert from Watts to BTUs, then the value for Watts must be the same time scale as BTUs.
// If the value for watts is based in seconds then the output to BTUs will also be in seconds.
// Likewise, if the value for watts is based on hours then the output to BTUs will also be BTUs per hour.
//
// Some usage examples: 
//
//{
//	/* Conversion test. */
//	footpound work_footpounds(1130.1);
//	
//	erg work_erg(work_footpounds);
//	watt work_watts(work_erg);
//	btu work_btu(work_watts);
//	horsepower work_horsepower(work_watts);
//	tons_refrigeration work_tons_refrigeration(work_horsepower);
//	
//	std::cout << "Footpound/sec: " << work_footpounds << std::endl;
//	std::cout << "Ergs/sec: " << work_erg << std::endl;
//	std::cout << "Watt/sec: " << work_watts << std::endl;
//	std::cout << "BTU/sec: " << work_btu << std::endl;
//	std::cout << "Horsepower/sec: " << work_horsepower << std::endl;
//	std::cout << "tons_refrigeration/sec: " << work_tons_refrigeration << std::endl << std::endl;
//}
//{
//	/* Conversion test. */
//	footpound work_footpounds = 5129.77;
//	
//	erg work_erg = (erg) work_footpounds;
//	erg work_erg2 = work_erg;
//	watt work_watts = (watt) work_erg;
//	btu work_btu = (btu) work_watts;
//	horsepower work_horsepower = (horsepower) work_watts;
//	tons_refrigeration work_tons_refrigeration = (tons_refrigeration) work_horsepower;
//	
//	std::cout << "Footpound/sec: " << work_footpounds << std::endl;
//	std::cout << "Ergs/sec: " << work_erg << std::endl;
//	std::cout << "Watt/sec: " << work_watts << std::endl;
//	std::cout << "BTU/sec: " << work_btu << std::endl;
//	std::cout << "Horsepower/sec: " << work_horsepower << std::endl;
//	std::cout << "tons_refrigeration/sec: " << work_tons_refrigeration << std::endl << std::endl;
//}
//	/* Cast test */
//	watt additional_work(1000);
//	
//  std::cout << "Footpound/sec: " << (footpound)additional_work << std::endl;
//  std::cout << "Ergs/sec: " << (erg)additional_work << std::endl;
//  std::cout << "BTU/sec: " << (btu)additional_work << std::endl;
//  std::cout << "Watt/sec: " << additional_work << std::endl;
//  std::cout << "Horsepower/sec: " << (horsepower)additional_work << std::endl;
//  std::cout << "tons_refrigeration/sec: " << (tons_refrigeration)additional_work << std::endl << std::endl;
//	
//{
//	/* Math test. */
//	footpound work_footpounds = 5129.77;
//	
//	erg work_erg = 13558179.48331; /* 1 ftlbs */
//	watt work_watts = 135.5817948331; /* 100 ftlbs */
//	btu work_btu = 1.285067283946; /* 1000 ftlbs */
//	horsepower work_horsepower = 0.01818181818182; /* 10 ftlbs */
//	tons_refrigeration work_tons_refrigeration =  0.00038552022552; /* 1 ftlbs */
//		
//	work_footpounds += work_erg;
//	work_footpounds += work_watts;
//	work_footpounds += work_btu;
//	work_footpounds += work_horsepower;
//	work_footpounds /= work_horsepower;
//	work_footpounds *= work_watts;
//	work_footpounds -= 1001.1;
//	work_footpounds -= work_tons_refrigeration;
//	
//	/* Should be ~= 61405.6 ft.lbs/sec*/
//	std::cout << "Footpounds: " << work_footpounds << std::endl;
//}
#pragma once

#include <string>
#include <sstream>
#include <boost/variant.hpp>
#include <iostream>

#include "Conversion_Constants.h"


/***********************************************************************/
/*                                                                     */
/*                    Conversion Template                              */
/*                                                                     */
/***********************************************************************/
template <class T> class Convert; 
class tbtu_variant; class twatt_variant; class tcalorie_variant; class thorsepower_variant; class thorsepower_electric_variant; class thorsepower_metric_variant; 
class thorsepower_h2o_variant; class tfootpound_variant; class terg_variant; class ttons_refrigeration_variant;
typedef Convert<twatt_variant> watt;
typedef Convert<tcalorie_variant> calorie;
typedef Convert<thorsepower_variant> horsepower;
typedef Convert<thorsepower_electric_variant> horsepower_electric;
typedef Convert<thorsepower_metric_variant> horsepower_metric;
typedef Convert<thorsepower_h2o_variant> horsepower_h2o;
typedef Convert<tfootpound_variant> footpound;
typedef Convert<terg_variant> erg;
typedef Convert<tbtu_variant> btu;
typedef Convert<ttons_refrigeration_variant> tons_refrigeration;

typedef boost::variant<watt, calorie, horsepower, footpound, erg, btu, tons_refrigeration, horsepower_electric, horsepower_metric, horsepower_h2o, double> visitor_variant;
template <class T> 
    class Convert 
    { 
    private: 
        
    public: 
        double power = 0.0;
        Convert(); 
        Convert(double r) { this->power = r; }
        Convert(const visitor_variant &c)
        {
            this->power = boost::apply_visitor(T(), c); 
        }
        void operator=(double c)
        {
            this->power = c;
        }
        void operator=(visitor_variant c)
        {
            this->power = boost::apply_visitor(T(), c); 
        }
        virtual double operator()() {return (this->power);}
        virtual double operator()(visitor_variant temp2) {return (boost::apply_visitor(T(), temp2));}
        virtual double operator-(visitor_variant temp2){return (this->power - boost::apply_visitor(T(), temp2));}
        virtual double operator+(visitor_variant temp2){return (this->power + boost::apply_visitor(T(), temp2));}
        virtual double operator*(visitor_variant temp2){return (this->power * boost::apply_visitor(T(), temp2));}
        virtual double operator/(visitor_variant temp2){return (this->power / boost::apply_visitor(T(), temp2));}
        virtual double operator-=(visitor_variant temp2){this->power -= boost::apply_visitor(T(), temp2); return (this->power);}
        virtual double operator+=(visitor_variant temp2){this->power += boost::apply_visitor(T(), temp2); return (this->power);}
        virtual double operator*=(visitor_variant temp2){this->power *= boost::apply_visitor(T(), temp2); return (this->power);}
        virtual double operator/=(visitor_variant temp2){this->power /= boost::apply_visitor(T(), temp2); return (this->power);}
        virtual double operator>(visitor_variant temp2){if (this->power > boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<(visitor_variant temp2){if (this->power < boost::apply_visitor(T(), temp2)) return (1);return (0);}
        virtual double operator>=(visitor_variant temp2){if (this->power >= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<=(visitor_variant temp2){if (this->power <= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator==(visitor_variant temp2){if (this->power == boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        friend std::ostream& operator<<(std::ostream& lhs, const Convert& rhs)
        {
            return (lhs << rhs.power);
        }
    }; 

/***********************************************************************/
/*                                                                     */
/*                        Watt Conversion                              */
/*                                                                     */
/***********************************************************************/
class twatt_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(watt c) const
    {
        return (c.power);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power * 4.1868;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 745.6998715823;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.0000001;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 1055.056;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 1.355817948331;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 3516.85284;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 746.043;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 746.0;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 735.49875;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*                      Calorie Conversion                             */
/*                                                                     */
/***********************************************************************/
class tcalorie_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(calorie c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.2388458966275;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 178.1073544431;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.00000002388458966275;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 251.9957963122;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.3238315535329;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 839.98586988;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 178.18930926;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 178.17903888;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 175.67085841;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*                    Horsepower Conversion                            */
/*                                                                     */
/***********************************************************************/
class thorsepower_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(horsepower c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.001341022089595;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power * 0.005614591284716;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.0000000001341022089595;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 1.41485340176;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.001818181818182;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 4.7161773543;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 1.0004601449;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 1.000402481;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 0.98632007271;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*                     Foot-pound Conversion                           */
/*                                                                     */
/***********************************************************************/
class tfootpound_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(footpound c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.7375621492773;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power * 3.088025206594;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.00000007375621492773;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 550.0;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 778.1693709679;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 2593.8976318;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 550.25309815;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 550.22138297;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 542.47605818;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*                    Erg Conversion                                   */
/*                                                                     */
/***********************************************************************/
class terg_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(erg c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 10000000.0;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power * 41868000.0;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 7456998715.823;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 10550560000.0;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 13558179.48331;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 35168528400.0;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 7460430000.0;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 7460000000.0;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 7354987500.0;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*                    BTU Conversion                                   */
/*                                                                     */
/***********************************************************************/
class tbtu_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(btu c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.0009478169879134;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power * 0.003968320164996;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 0.7067870061706;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.00000000009478169879134;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.001285067283946;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 3.3333333333;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power *  0.70711232831;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 0.70707157217;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 0.69711830763;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*                    tons_refrigeration Conversion                    */
/*                                                                     */
/***********************************************************************/
class ttons_refrigeration_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(tons_refrigeration c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.00028434513626;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power * 0.0011904962165;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 0.21203613115;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.000000000028434513626;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.00038552022552;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 0.3;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 0.21213369849;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 0.21212147165;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 0.20913549229;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*               Horsepower Electricty Conversion                      */
/*                                                                     */
/***********************************************************************/
class thorsepower_electric_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(horsepower_electric c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.0013404825737;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power *  0.0056123324397;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.00000000013404825737;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 1.4142839839;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.0018174502681;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 4.7142799464;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power *  1.0000576408;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 0.99959768097;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 0.98592325737;
        return (temp);
    }
    
};

/***********************************************************************/
/*                                                                     */
/*               Horsepower Metric Conversion                          */
/*                                                                     */
/***********************************************************************/
class thorsepower_metric_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(horsepower_metric c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power * 0.0013596216173;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power *  0.0056924637873;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.00000000013596216173;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 1.4344767438;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.001843399326;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 4.7815891461;
        return (temp);
    }
    
    double operator()(horsepower_h2o c) const
    {
        double temp = c.power * 1.0143361902;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 1.0142777265;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 1.0138696633;
        return (temp);
    }
    
};


/***********************************************************************/
/*                                                                     */
/*               Horsepower H2O Conversion                             */
/*                                                                     */
/***********************************************************************/
class thorsepower_h2o_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const
    {
        return (c);
    }
    
    double operator()(horsepower_h2o c) const
    {
        return (c.power);
    }
    
    double operator()(watt c) const
    {
        double temp = c.power *  0.0013404053118;
        return (temp);
    }
    
    double operator()(calorie c) const
    {
        double temp = c.power *  0.0056120089593;
        return (temp);
    }
    
    double operator()(erg c) const
    {
        double temp = c.power * 0.00000000013404053118;
        return (temp);
    }
    
    double operator()(btu c) const
    {
        double temp = c.power * 1.4142024682;
        return (temp);
    }
    
    double operator()(footpound c) const
    {
        double temp = c.power * 0.0018173455149;
        return (temp);
    }
    
    double operator()(tons_refrigeration c) const
    {
        double temp = c.power * 4.7140082274;
        return (temp);
    }
    
    double operator()(horsepower c) const
    {
        double temp = c.power * 0.99954006673;
        return (temp);
    }
    
    double operator()(horsepower_electric c) const
    {
        double temp = c.power * 0.99994236257;
        return (temp);
    }
    
    double operator()(horsepower_metric c) const
    {
        double temp = c.power * 0.98586643129;
        return (temp);
    }
    
};
