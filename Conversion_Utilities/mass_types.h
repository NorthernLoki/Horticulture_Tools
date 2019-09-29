//
// mass_types.h
// Version timestamp: 10-26-2018, 11:25 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
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
template <class T> class Mass_Convert; 
class tatomic_mass_variant; class tcarat_variant; class tdram_variant; class tgrain_variant; class tgram_variant; class tnewton_variant; 
class tounce_variant; class tpound_variant; class tton_variant; class ttonne_variant; class ttroy_ounce_variant; class tdalton_variant;
typedef Mass_Convert<tatomic_mass_variant> amu; /* Atomic mass units, based on carbon-12 */
typedef Mass_Convert<tcarat_variant> carat;
typedef Mass_Convert<tdram_variant> dram; /* Not that same unit as apothecaries */
typedef Mass_Convert<tgrain_variant> grain;
typedef Mass_Convert<tgram_variant> gram;
typedef Mass_Convert<tpound_variant> pound;
typedef Mass_Convert<tton_variant> ton; /* UK long ton */
typedef Mass_Convert<ttonne_variant> tonne;
typedef Mass_Convert<ttroy_ounce_variant> troy_ounce;
typedef Mass_Convert<tdalton_variant> dalton;
typedef Mass_Convert<tounce_variant> ounce;

typedef boost::variant<amu, carat, dram, grain, gram, pound, ton, tonne, troy_ounce, dalton, ounce, double> mass_variant;

template <class T> 
    class Mass_Convert 
    { 
    private: 
        
    public: 
        double mass = 0.0;
        Mass_Convert(); 
        Mass_Convert(double r) { this->mass = r; }
        Mass_Convert(const mass_variant &c)
        {
            this->mass = boost::apply_visitor(T(), c); 
        }
        void operator=(double c)
        {
            this->mass = c;
        }
        void operator=(mass_variant c)
        {
            this->mass = boost::apply_visitor(T(), c); 
        }
        virtual double operator()() {return (this->mass);}
        virtual double operator()(mass_variant temp2) {return (boost::apply_visitor(T(), temp2));}
        virtual double operator-(mass_variant temp2){return (this->mass - boost::apply_visitor(T(), temp2));}
        virtual double operator+(mass_variant temp2){return (this->mass + boost::apply_visitor(T(), temp2));}
        virtual double operator*(mass_variant temp2){return (this->mass * boost::apply_visitor(T(), temp2));}
        virtual double operator/(mass_variant temp2){return (this->mass / boost::apply_visitor(T(), temp2));}
        virtual double operator-=(mass_variant temp2){this->mass -= boost::apply_visitor(T(), temp2); return (this->mass);}
        virtual double operator+=(mass_variant temp2){this->mass += boost::apply_visitor(T(), temp2); return (this->mass);}
        virtual double operator*=(mass_variant temp2){this->mass *= boost::apply_visitor(T(), temp2); return (this->mass);}
        virtual double operator/=(mass_variant temp2){this->mass /= boost::apply_visitor(T(), temp2); return (this->mass);}
        virtual double operator>(mass_variant temp2){if (this->mass > boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<(mass_variant temp2){if (this->mass < boost::apply_visitor(T(), temp2)) return (1);return (0);}
        virtual double operator>=(mass_variant temp2){if (this->mass >= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<=(mass_variant temp2){if (this->mass <= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator==(mass_variant temp2){if (this->mass == boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        friend std::ostream& operator<<(std::ostream& lhs, const Mass_Convert& rhs)
        {
            return (lhs << rhs.mass);
        }
    }; 


/***********************************************************************/
/*                                                                     */
/*                   Atomic Mass Unit Conversion                       */
/*                                                                     */
/***********************************************************************/
class tatomic_mass_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(amu c) const { return (c.mass); }
    double operator()(carat c) const { double temp = c.mass * 1.204427330335* pow(10, 23); return (temp); } 
    double operator()(dram c) const { double temp = c.mass *  1.067029389179* pow(10, 24); return (temp);}
    double operator()(grain c) const { double temp = c.mass * 3.902278908996* pow(10, 22); return (temp);}
    double operator()(gram c) const { double temp = c.mass *  6.022136651675* pow(10, 23); return (temp); }
    double operator()(pound c) const { double temp = c.mass * 2.731595236297* pow(10, 26); return (temp); }
    double operator()(ton c) const { double temp = c.mass *   6.118773329306* pow(10, 29); return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 6.022136651675* pow(10, 29); return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 1.873093876318* pow(10, 25); return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 1.707247022686 * pow(10, 25); return (temp); }
    double operator()(dalton c) const { double temp = c.mass * 1.0; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                       Carat Unit Conversion                         */
/*                                                                     */
/***********************************************************************/
class tcarat_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(carat c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 8.302701 * pow(10, -24); return (temp); } 
    double operator()(dram c) const { double temp = c.mass *  8.859225976562; return (temp);}
    double operator()(grain c) const { double temp = c.mass * 0.32399455; return (temp);}
    double operator()(gram c) const { double temp = c.mass *  5.0; return (temp); }
    double operator()(pound c) const { double temp = c.mass * 2267.96185; return (temp); }
    double operator()(ton c) const { double temp = c.mass *   5080234.544; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 5000000.0; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 155.517384; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 141.747615625; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  8.302701 * pow(10, -24); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                       Dram Unit Conversion                          */
/*                                                                     */
/***********************************************************************/
class tdram_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(dram c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 9.371813093 * pow(10, -25); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  0.1128766782387; return (temp);}
    double operator()(grain c) const { double temp = c.mass * 0.03657142857143; return (temp);}
    double operator()(gram c) const { double temp = c.mass *  0.5643833911933; return (temp); }
    double operator()(pound c) const { double temp = c.mass * 256.0; return (temp); }
    double operator()(ton c) const { double temp = c.mass *   573440.0; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 564383.3911933; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 17.55428571429; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 16.0; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  9.371813093 * pow(10, -25); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Grain Unit Conversion                        */
/*                                                                     */
/***********************************************************************/
class tgrain_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(grain c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 2.562605142586 * pow(10, -23); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  3.086471670588; return (temp);}
    double operator()(dram c) const { double temp = c.mass * 27.34375; return (temp);}
    double operator()(gram c) const { double temp = c.mass *  15.43235835294; return (temp); }
    double operator()(pound c) const { double temp = c.mass * 7000.0; return (temp); }
    double operator()(ton c) const { double temp = c.mass *   15680000.0; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 15432358.35294; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 480.0; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 437.5; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  2.5626051426 * pow(10, -23); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Gram Unit Conversion                         */
/*                                                                     */
/***********************************************************************/
class tgram_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(gram c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 1.6605402* pow(10, -24); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  0.2; return (temp);}
    double operator()(dram c) const { double temp = c.mass * 1.771845195312; return (temp);}
    double operator()(grain c) const { double temp = c.mass *  0.06479891; return (temp); }
    double operator()(pound c) const { double temp = c.mass * 453.59237; return (temp); }
    double operator()(ton c) const { double temp = c.mass *   1016046.9088; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 1000000.0; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 31.1034768; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 28.349523125; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  1.6605402* pow(10, -24); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Pound Unit Conversion                        */
/*                                                                     */
/***********************************************************************/
class tpound_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(pound c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 3.660864489409 * pow(10, -27); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  0.0004409245243698; return (temp);}
    double operator()(dram c) const { double temp = c.mass * 0.00390625; return (temp);}
    double operator()(grain c) const { double temp = c.mass *  0.0001428571428571; return (temp); }
    double operator()(gram c) const { double temp = c.mass * 0.002204622621849; return (temp); }
    double operator()(ton c) const { double temp = c.mass *   2240.0; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 2204.622621849; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 0.06857142857143; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 0.0625; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  3.660864489409 * pow(10, -27); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Ton Unit Conversion                          */
/*                                                                     */
/***********************************************************************/
class tton_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(ton c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 1.634314504201 * pow(10, -30); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  0.0000001968413055222; return (temp);}
    double operator()(dram c) const { double temp = c.mass * 0.000001743861607143; return (temp);}
    double operator()(grain c) const { double temp = c.mass *  0.00000006377551020408; return (temp); }
    double operator()(gram c) const { double temp = c.mass * 0.0000009842065276111; return (temp); }
    double operator()(pound c) const { double temp = c.mass *   0.0004464285714286; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 0.9842065276111; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 0.00003061224489796; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 0.00002790178571429; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  1.634314504201 * pow(10, -30); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                       Tonne Unit Conversion                         */
/*                                                                     */
/***********************************************************************/
class ttonne_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(tonne c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 1.6605402 * pow(10, -30); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  0.0000002; return (temp);}
    double operator()(dram c) const { double temp = c.mass * 0.000001771845195312; return (temp);}
    double operator()(grain c) const { double temp = c.mass *  0.00000006479891; return (temp); }
    double operator()(gram c) const { double temp = c.mass * 0.000001; return (temp); }
    double operator()(pound c) const { double temp = c.mass * 0.00045359237; return (temp); }
    double operator()(ton c) const { double temp = c.mass * 1.0160469088; return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 0.0000311034768; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 0.000028349523125; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  1.6605402 * pow(10, -30); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                    Troy Ounce Unit Conversion                       */
/*                                                                     */
/***********************************************************************/
class ttroy_ounce_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(troy_ounce c) const { return (c.mass); }
    double operator()(amu c) const { double temp = c.mass * 5.338760713722 * pow(10, -26); return (temp); } 
    double operator()(carat c) const { double temp = c.mass *  0.006430149313726; return (temp);}
    double operator()(dram c) const { double temp = c.mass * 0.05696614583333; return (temp);}
    double operator()(grain c) const { double temp = c.mass *  0.002083333333333; return (temp); }
    double operator()(gram c) const { double temp = c.mass * 0.03215074656863; return (temp); }
    double operator()(pound c) const { double temp = c.mass * 14.58333333333; return (temp); }
    double operator()(ton c) const { double temp = c.mass * 32666.66666667; return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 32150.74656863; return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 0.9114583333333; return (temp); }
    double operator()(dalton c) const { double temp = c.mass *  5.338760713722 * pow(10, -26); return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Dalton Conversion                            */
/*                                                                     */
/***********************************************************************/
class tdalton_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(dalton c) const { return (c.mass); }
    double operator()(carat c) const { double temp = c.mass * 1.204427330335 * pow(10, 23); return (temp); } 
    double operator()(dram c) const { double temp = c.mass *  1.067029389179 * pow(10, 24); return (temp);}
    double operator()(grain c) const { double temp = c.mass * 3.902278908996 * pow(10, 22); return (temp);}
    double operator()(gram c) const { double temp = c.mass *  6.022136651675 * pow(10, 23); return (temp); }
    double operator()(pound c) const { double temp = c.mass * 2.731595236297 * pow(10, 26); return (temp); }
    double operator()(ton c) const { double temp = c.mass *   6.118773329306 * pow(10, 29); return (temp); }
    double operator()(tonne c) const { double temp = c.mass * 6.022136651675 * pow(10, 29); return (temp); }
    double operator()(troy_ounce c) const { double temp = c.mass * 1.873093876318 * pow(10, 25); return (temp); }
	double operator()(ounce c) const { double temp = c.mass * 1.7072470227 * pow(10, 25); return (temp); }
    double operator()(amu c) const { double temp = c.mass * 1.0; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Ounce Conversion                             */
/*                                                                     */
/***********************************************************************/
class tounce_variant : public boost::static_visitor<double>
{
public:
	double operator()(double c) const { return (c); }
	double operator()(ounce c) const { return (c.mass); }
	double operator()(carat c) const { double temp = c.mass * 0.007054792389916; return (temp); } 
	double operator()(dram c) const { double temp = c.mass *  0.0625; return (temp);}
	double operator()(grain c) const { double temp = c.mass * 0.002285714285714; return (temp);}
	double operator()(gram c) const { double temp = c.mass *  0.03527396194958; return (temp); }
	double operator()(pound c) const { double temp = c.mass * 16.0; return (temp); }
	double operator()(ton c) const { double temp = c.mass *   35840.0; return (temp); }
	double operator()(tonne c) const { double temp = c.mass * 35273.96194958; return (temp); }
	double operator()(troy_ounce c) const { double temp = c.mass * 1.097142857143; return (temp); }
	double operator()(dalton c) const { double temp = c.mass * 5.857383183055 * pow(10, -26); return (temp); }
	double operator()(amu c) const { double temp = c.mass * 5.857383183055 * pow(10, -26); return (temp); }
};
