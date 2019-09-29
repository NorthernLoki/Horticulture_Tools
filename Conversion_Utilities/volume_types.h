//
// volume_types.h
// Version timestamp: 10-25-2018, 7:19 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//

//
//
// Some usage examples: 
//
//cubic_meter this_m3 = 3.5;
//cubic_yard this_yd3(this_m3);
//fluid_dram this_dram = (fluid_dram) this_yd3;
//US_fluid_ounce this_usoz(this_dram);
//UK_fluid_ounce this_ukoz(this_usoz);
//US_fluid_gallon this_usgal = (US_fluid_gallon) this_ukoz;
//UK_fluid_gallon this_ukgal = (UK_fluid_gallon) this_usgal;
//liter this_liter(this_usgal);
//dry_pint this_pint(this_liter);
//dry_quart this_quart(this_pint);
//barrel this_barrel(this_quart);
//US_bushel this_US_bushel(this_barrel);
//UK_bushel this_UK_bushel(this_US_bushel);
//peck this_peck(this_UK_bushel);
//	
//std::cout << "cubic_meter: " << this_m3 << std::endl;
//std::cout << "cubic_yard: " << this_yd3 << std::endl;
//std::cout << "fluid_dram: " << this_dram << std::endl;
//std::cout << "US_fluid_ounce: " << this_usoz << std::endl;
//std::cout << "UK_fluid_ounce: " << this_ukoz << std::endl;
//std::cout << "US_fluid_gallon: " << this_usgal << std::endl;
//std::cout << "UK_fluid_gallon: " << this_ukgal << std::endl;
//std::cout << "liter: " << this_liter << std::endl;
//std::cout << "dry_pint: " << this_pint << std::endl;
//std::cout << "dry_quart: " << this_quart << std::endl;
//std::cout << "barrel: " << this_barrel << std::endl;
//std::cout << "US_bushel: " << this_US_bushel << std::endl;
//std::cout << "UK_bushel: " << this_UK_bushel << std::endl;
//std::cout << "peck: " << this_peck << std::endl;	
//	
//liter added_volumes = 0.0;
//added_volumes += this_m3;
//added_volumes += this_yd3;
//added_volumes += this_dram;
//added_volumes += this_usoz;
//added_volumes += this_usoz;
//added_volumes += this_ukoz;
//added_volumes += this_usgal;
//added_volumes += this_ukgal;
//added_volumes += this_liter;
//added_volumes += this_pint;
//added_volumes -= this_quart;
//added_volumes *= this_barrel;
//added_volumes /= (barrel)(this_barrel * 2.0);
//added_volumes += this_peck;
//	
///* Should be ~= 19.25 m^3 */
//std::cout << "Total volume (m^3): " << (cubic_meter)added_volumes << std::endl;
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
template <class T> class Volume_Convert; 
class tcubic_meter_variant; class tcubic_yard_variant; class tfluid_dram_variant; class tUS_fluid_ounce_variant; class tUK_fluid_ounce_variant; class tUS_fluid_gallon_variant; class tUK_fluid_gallon_variant;
class tliter_variant; class tdry_pint_variant; class tdry_quart_variant; class tbarrel_variant; class tUS_bushel_variant; class tUK_bushel_variant; class tpeck_variant;
typedef Volume_Convert<tcubic_meter_variant> cubic_meter;
typedef Volume_Convert<tcubic_yard_variant> cubic_yard;
typedef Volume_Convert<tfluid_dram_variant> fluid_dram;
typedef Volume_Convert<tUS_fluid_ounce_variant> US_fluid_ounce;
typedef Volume_Convert<tUK_fluid_ounce_variant> UK_fluid_ounce;
typedef Volume_Convert<tUS_fluid_gallon_variant> US_fluid_gallon;
typedef Volume_Convert<tUK_fluid_gallon_variant> UK_fluid_gallon;
typedef Volume_Convert<tliter_variant> liter;
typedef Volume_Convert<tdry_pint_variant> dry_pint;
typedef Volume_Convert<tdry_quart_variant> dry_quart;
typedef Volume_Convert<tbarrel_variant> barrel;
typedef Volume_Convert<tUS_bushel_variant> US_bushel;
typedef Volume_Convert<tUK_bushel_variant> UK_bushel;
typedef Volume_Convert<tpeck_variant> peck;

typedef boost::variant<cubic_meter, cubic_yard, fluid_dram, US_fluid_ounce, UK_fluid_ounce, US_fluid_gallon, 
    UK_fluid_gallon, liter, dry_pint, dry_quart, barrel, US_bushel, UK_bushel, peck, double> volume_variant;

template <class T> 
    class Volume_Convert 
    { 
    private: 
        
    public: 
        double volume = 0.0;
        Volume_Convert(); 
        Volume_Convert(double r) { this->volume = r; }
        Volume_Convert(const volume_variant &c)
        {
            this->volume = boost::apply_visitor(T(), c); 
        }
        void operator=(double c)
        {
            this->volume = c;
        }
        void operator=(volume_variant c)
        {
            this->volume = boost::apply_visitor(T(), c); 
        }
        virtual double operator()() {return (this->volume);}
        virtual double operator()(volume_variant temp2) {return (boost::apply_visitor(T(), temp2));}
        virtual double operator-(volume_variant temp2){return (this->volume - boost::apply_visitor(T(), temp2));}
        virtual double operator+(volume_variant temp2){return (this->volume + boost::apply_visitor(T(), temp2));}
        virtual double operator*(volume_variant temp2){return (this->volume * boost::apply_visitor(T(), temp2));}
        virtual double operator/(volume_variant temp2){return (this->volume / boost::apply_visitor(T(), temp2));}
        virtual double operator-=(volume_variant temp2){this->volume -= boost::apply_visitor(T(), temp2); return (this->volume);}
        virtual double operator+=(volume_variant temp2){this->volume += boost::apply_visitor(T(), temp2); return (this->volume);}
        virtual double operator*=(volume_variant temp2){this->volume *= boost::apply_visitor(T(), temp2); return (this->volume);}
        virtual double operator/=(volume_variant temp2){this->volume /= boost::apply_visitor(T(), temp2); return (this->volume);}
        virtual double operator>(volume_variant temp2){if (this->volume > boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<(volume_variant temp2){if (this->volume < boost::apply_visitor(T(), temp2)) return (1);return (0);}
        virtual double operator>=(volume_variant temp2){if (this->volume >= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator<=(volume_variant temp2){if (this->volume <= boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        virtual double operator==(volume_variant temp2){if (this->volume == boost::apply_visitor(T(), temp2)) return (1);return (0);} 
        friend std::ostream& operator<<(std::ostream& lhs, const Volume_Convert& rhs)
        {
            return (lhs << rhs.volume);
        }
    }; 


/***********************************************************************/
/*                                                                     */
/*                      cubic_meter Conversion                         */
/*                                                                     */
/***********************************************************************/
class tcubic_meter_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(cubic_meter c) const { return (c.volume); }
    double operator()(cubic_yard c) const { double temp = c.volume * 0.764554857984; return (temp); } 
    double operator()(fluid_dram c) const { double temp = c.volume * 0.000003696691195313; return (temp);}
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.0000295735295625; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.0000284130625; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.003785411784; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 0.00454609; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 0.001; return (temp); }   
    double operator()(dry_pint c) const{ double temp = c.volume * 0.0005506104713575; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 0.001101220942715; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 0.158987294928; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 0.03523907016688; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 0.03636872; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 0.00880976754172; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                      cubic_yard Conversion                          */
/*                                                                     */
/***********************************************************************/
class tcubic_yard_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(cubic_yard c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 1.307950619314; return (temp); } 
    double operator()(fluid_dram c) const { double temp = c.volume * 0.000004835089538323; return (temp);}
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.00003868071630658; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.00003716288269349; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.004951131687243; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 0.005946061230959; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 0.001307950619314; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 0.000720171307013; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 0.001440342614026; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 0.2079475308642; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 0.04609096364883; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 0.04756848984767; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 0.01152274091221; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                      fluid_dram Conversion                          */
/*                                                                     */
/***********************************************************************/
class tfluid_dram_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(fluid_dram c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 270512.1816147; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 206821.4025974; return (temp);}
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 8.0; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 7.686079523231; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 1024.0; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 1229.772723717; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 270.5121816147; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 148.9468398268; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 297.8936796537; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 43008.0; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 9532.597748918; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 9838.181789736; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 2383.149437229; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                      US_fluid_ounce Conversion                      */
/*                                                                     */
/***********************************************************************/
class tUS_fluid_ounce_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(US_fluid_ounce c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 33814.02270184; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 25852.67532468; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.125; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.9607599404039; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 128.0; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 153.7215904646; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 33.81402270184; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 18.61835497836; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 37.23670995671; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 5376.0; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 1191.574718615; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 1229.772723717; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 297.8936796537; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                      UK_fluid_ounce Conversion                      */
/*                                                                     */
/***********************************************************************/
class tUK_fluid_ounce_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(UK_fluid_ounce c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 35195.07972785; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 26908.56918306; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.1301053413483; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 1.040842730786; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 133.2278695406; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 160.0; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 35.19507972785; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 19.37877943842; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 38.75755887684; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 5595.570520707; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 1240.241884059; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 1280.0; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 310.0604710147; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                     US_fluid_gallon Conversion                      */
/*                                                                     */
/***********************************************************************/
class tUS_fluid_gallon_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(US_fluid_gallon c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 264.1720523581; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 201.974025974; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.0009765625; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.0078125; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.007505937034405; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 1.200949925505; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 0.2641720523582; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 0.1454558982684; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 0.2909117965368; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 42.0; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 9.309177489177; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 9.607599404039; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 2.327294372294; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                     UK_fluid_gallon Conversion                      */
/*                                                                     */
/***********************************************************************/
class tUK_fluid_gallon_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(UK_fluid_gallon c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 219.9692482991; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 168.1785573942; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.0008131583834268; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.006505267067414; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.00625; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.832674184629; return (temp); }
    double operator()(liter c) const { double temp = c.volume * 0.2199692482991; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 0.1211173714901; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 0.2422347429802; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 34.97231575442; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 7.751511775367; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 8.0; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 1.937877943842; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        liter Conversion                             */
/*                                                                     */
/***********************************************************************/
class tliter_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(liter c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 1000.0; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 764.554857984; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.003696691195313; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.0295735295625; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.0284130625; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 3.785411784; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 4.54609; return (temp); } 
    double operator()(dry_pint c) const{ double temp = c.volume * 0.5506104713575; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 1.101220942715; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 158.987294928; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 35.23907016688; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 36.36872; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 8.80976754172; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Dry pint Conversion                          */
/*                                                                     */
/***********************************************************************/
class tdry_pint_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(dry_pint c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 1816.165968538; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 1388.558514151; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.00671380474512; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.05371043796096; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.05160283717443; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 6.874936059002; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 8.256453947909; return (temp); } 
    double operator()(liter c) const{ double temp = c.volume * 1.816165968538; return (temp); }  
    double operator()(dry_quart c) const{ double temp = c.volume * 2.0; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 288.7473144781; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 64.0; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 66.05163158328; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 16.0; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        Dry quart Conversion                         */
/*                                                                     */
/***********************************************************************/
class tdry_quart_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(dry_quart c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 908.0829842689; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 694.2792570754; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.00335690237256; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.02685521898048; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.02580141858722; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 3.437468029501; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 4.128226973955; return (temp); } 
    double operator()(liter c) const{ double temp = c.volume * 0.9080829842689; return (temp); }  
    double operator()(dry_pint c) const{ double temp = c.volume * 0.5; return (temp); } 
    double operator()(barrel c) const{ double temp = c.volume * 144.3736572391; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 32.0; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 33.02581579164; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 8.0; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                          Barrel Conversion                          */
/*                                                                     */
/***********************************************************************/
class tbarrel_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(barrel c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 6.289810770432; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 4.808905380334; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.00002325148809524; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.0001860119047619; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.0001787127865335; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.02380952380952; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 0.02859404584535; return (temp); } 
    double operator()(liter c) const{ double temp = c.volume * 0.006289810770432; return (temp); }  
    double operator()(dry_pint c) const{ double temp = c.volume * 0.003463235673057; return (temp); } 
    double operator()(dry_quart c) const{ double temp = c.volume * 0.006926471346114; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 0.2216470830757; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 0.2287523667628; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 0.05541177076891; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        US Bushel Conversion                         */
/*                                                                     */
/***********************************************************************/
class tUS_bushel_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(US_bushel c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 28.3775932584; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 21.69622678361; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.0001049031991425; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.00083922559314; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.0008062943308506; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.1074208759219; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 0.1290070929361; return (temp); } 
    double operator()(liter c) const{ double temp = c.volume * 0.0283775932584; return (temp); }  
    double operator()(dry_pint c) const{ double temp = c.volume * 0.015625; return (temp); } 
    double operator()(dry_quart c) const{ double temp = c.volume * 0.03125; return (temp); }
    double operator()(barrel c) const { double temp = c.volume * 4.51167678872; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 1.032056743489; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 0.25; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                        UK Bushel Conversion                         */
/*                                                                     */
/***********************************************************************/
class tUK_bushel_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(UK_bushel c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 27.49615603739; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 21.02231967427; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.0001016447979283; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.0008131583834267; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.00078125; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.1040842730786; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 0.125; return (temp); } 
    double operator()(liter c) const{ double temp = c.volume * 0.02749615603739; return (temp); }  
    double operator()(dry_pint c) const{ double temp = c.volume * 0.01513967143626; return (temp); } 
    double operator()(dry_quart c) const{ double temp = c.volume * 0.03027934287253; return (temp); }
    double operator()(barrel c) const { double temp = c.volume * 4.371539469302; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 0.9689389719209; return (temp); }
    double operator()(peck c) const { double temp = c.volume * 0.2422347429802; return (temp); }
};

/***********************************************************************/
/*                                                                     */
/*                           Peck Conversion                           */
/*                                                                     */
/***********************************************************************/
class tpeck_variant : public boost::static_visitor<double>
{
public:
    double operator()(double c) const { return (c); }
    double operator()(peck c) const { return (c.volume); }
    double operator()(cubic_meter c) const { double temp = c.volume * 113.5103730336; return (temp); } 
    double operator()(cubic_yard c) const { double temp = c.volume * 86.78490713442; return (temp);}
    double operator()(fluid_dram c) const { double temp = c.volume * 0.00041961279657; return (temp); }
    double operator()(US_fluid_ounce c) const { double temp = c.volume * 0.00335690237256; return (temp); }
    double operator()(UK_fluid_ounce c) const { double temp = c.volume * 0.003225177323402; return (temp); }
    double operator()(US_fluid_gallon c) const { double temp = c.volume * 0.4296835036877; return (temp); }
    double operator()(UK_fluid_gallon c) const { double temp = c.volume * 0.5160283717444; return (temp); } 
    double operator()(liter c) const{ double temp = c.volume * 0.1135103730336; return (temp); }  
    double operator()(dry_pint c) const{ double temp = c.volume * 0.0625; return (temp); } 
    double operator()(dry_quart c) const{ double temp = c.volume * 0.125; return (temp); }
    double operator()(barrel c) const { double temp = c.volume * 18.04670715488; return (temp); }
    double operator()(US_bushel c) const { double temp = c.volume * 4.0; return (temp); }
    double operator()(UK_bushel c) const { double temp = c.volume * 4.128226973955; return (temp); }
};