//
// pressure_types.h
// Version timestamp: 10-25-2018, 11:42 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//

//
//
// Some usage examples: 
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
template <class T> class Pressure_Convert; 
class tatmosphere_variant; class tbar_variant; class tkilogram_meter_variant; class tmmHg_variant; class tkPa_variant; class tpsi_variant; class tpsf_variant; class ttorr_variant;
typedef Pressure_Convert<tatmosphere_variant> atmosphere;
typedef Pressure_Convert<tbar_variant> bar;
typedef Pressure_Convert<tkilogram_meter_variant> kilogram_meter;
typedef Pressure_Convert<tmmHg_variant> mmHg;
typedef Pressure_Convert<tkPa_variant> kPa;
typedef Pressure_Convert<tpsi_variant> psi;
typedef Pressure_Convert<tpsf_variant> psf;
typedef Pressure_Convert<ttorr_variant> torr;


typedef boost::variant<atmosphere, bar, kilogram_meter, mmHg, kPa, psi, psf, torr, double> pressure_variant;

template <class T> 
    class Pressure_Convert 
    { 
    private: 
        
    public: 
        double pressure = 0.0;
        Pressure_Convert(); 
        Pressure_Convert(double r) { this->pressure = r; }
        Pressure_Convert(const pressure_variant &c)
        {
            this->pressure = boost::apply_visitor(T(), c); 
        }
        void operator=(double c)
        {
            this->pressure = c;
        }
        void operator=(pressure_variant c)
        {
            this->pressure = boost::apply_visitor(T(), c); 
        }
        virtual double operator()() {return (this->pressure);}
        virtual double operator()(pressure_variant temp2) {return (boost::apply_visitor(T(), temp2));}
        virtual double operator-(pressure_variant temp2){return (this->pressure - boost::apply_visitor(T(), temp2));}
        virtual double operator+(pressure_variant temp2){return (this->pressure + boost::apply_visitor(T(), temp2));}
        virtual double operator*(pressure_variant temp2){return (this->pressure * boost::apply_visitor(T(), temp2));}
        virtual double operator/(pressure_variant temp2){return (this->pressure / boost::apply_visitor(T(), temp2));}
        virtual double operator-=(pressure_variant temp2){this->pressure -= boost::apply_visitor(T(), temp2); return (this->pressure);}
        virtual double operator+=(pressure_variant temp2){this->pressure += boost::apply_visitor(T(), temp2); return (this->pressure);}
        virtual double operator*=(pressure_variant temp2){this->pressure *= boost::apply_visitor(T(), temp2); return (this->pressure);}
        virtual double operator/=(pressure_variant temp2){this->pressure /= boost::apply_visitor(T(), temp2); return (this->pressure);}
        virtual double operator>(pressure_variant temp2){if (this->pressure > boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<(pressure_variant temp2){if (this->pressure < boost::apply_visitor(T(), temp2)) return (1);return (0);}
        virtual double operator>=(pressure_variant temp2){if (this->pressure >= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<=(pressure_variant temp2){if (this->pressure <= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator==(pressure_variant temp2){if (this->pressure == boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        friend std::ostream& operator<<(std::ostream& lhs, const Pressure_Convert& rhs)
        {
            return (lhs << rhs.pressure);
        }
    }; 


/***********************************************************************/
/*                                                                     */
/*                      Atmosphere Conversion                          */
/*                                                                     */
/***********************************************************************/
class tatmosphere_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(atmosphere c) const { return (c.pressure); }
    double operator()(bar c) const { double temp = c.pressure * 0.986923266716; return (temp); } 
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.00009678411053541; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 0.001315789473684; return (temp);}
    double operator()(kPa c) const { double temp = c.pressure * 0.00986923266716; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 0.0680458919319; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 0.0004725409161938; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 0.001315789473684; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                         Bar Conversion                              */
/*                                                                     */
/***********************************************************************/
class tbar_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(bar c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 1.01325; return (temp); } 
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.0000980665; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 0.001333223684211; return (temp);}
    double operator()(kPa c) const { double temp = c.pressure * 0.01; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 0.0689475; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 0.0004788020833333; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 0.001333223684211; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                    kilogram_meter Conversion                        */
/*                                                                     */
/***********************************************************************/
class tkilogram_meter_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(kilogram_meter c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 10332.274528; return (temp); } 
    double operator()(bar c) const { double temp = c.pressure * 10197.16212978; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 13.59509806316; return (temp);}
    double operator()(kPa c) const { double temp = c.pressure * 101.9716212978; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 703.068835943; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 4.882422471826; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 13.59509806316; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                         mmHg Conversion                             */
/*                                                                     */
/***********************************************************************/
class tmmHg_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(mmHg c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 760.0; return (temp); } 
    double operator()(bar c) const { double temp = c.pressure * 750.0616827042; return (temp);}
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.07355592400691; return (temp);}
    double operator()(kPa c) const { double temp = c.pressure * 7.500616827042; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 51.71487786825; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 0.3591310963073; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 1.0; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                         kPa Conversion                             */
/*                                                                     */
/***********************************************************************/
class tkPa_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(kPa c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 101.325; return (temp); } 
    double operator()(bar c) const { double temp = c.pressure * 100.0; return (temp);}
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.00980665; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 0.1333223684211; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 6.89475; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 0.04788020833333; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 0.1333223684211; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                         PSI Conversion                             */
/*                                                                     */
/***********************************************************************/
class tpsi_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(psi c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 14.69596432068; return (temp); } 
    double operator()(bar c) const { double temp = c.pressure * 14.50378911491; return (temp);}
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.001422335835237; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 0.01933679515879; return (temp); }
    double operator()(kPa c) const { double temp = c.pressure * 0.1450378911491; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 0.006944444444444; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 0.01933679515879; return (temp); }
};


/***********************************************************************/
/*                                                                     */
/*                         PSF Conversion                             */
/*                                                                     */
/***********************************************************************/
class tpsf_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(psf c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 2116.218862178; return (temp); } 
    double operator()(bar c) const { double temp = c.pressure * 2088.545632547; return (temp);}
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.2048163602741; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 2.784498502865; return (temp); }
    double operator()(kPa c) const { double temp = c.pressure * 20.88545632547; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 144.0; return (temp); }
    double operator()(torr c) const { double temp = c.pressure * 2.784498502865; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                         torr Conversion                             */
/*                                                                     */
/***********************************************************************/
class ttorr_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(torr c) const { return (c.pressure); }
    double operator()(atmosphere c) const { double temp = c.pressure * 760.0; return (temp); } 
    double operator()(bar c) const { double temp = c.pressure * 750.0616827042; return (temp);}
    double operator()(kilogram_meter c) const { double temp = c.pressure * 0.07355592400691; return (temp);}
    double operator()(mmHg c) const { double temp = c.pressure * 1.0; return (temp); }
    double operator()(kPa c) const { double temp = c.pressure * 7.500616827042; return (temp); }
    double operator()(psi c) const { double temp = c.pressure * 51.71487786825; return (temp); }
    double operator()(psf c) const { double temp = c.pressure * 0.3591310963073; return (temp); }
};
