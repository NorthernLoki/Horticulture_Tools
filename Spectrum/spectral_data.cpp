//
// spectral_data.cpp
// Version timestamp: 9-28-2019, 10:56 AM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "spectral_data.h"

/* Constructor */
spectral_data::spectral_data()
{
}

/* Copy constructor */
spectral_data::spectral_data(const spectral_data &p)
{
    this->ordered_spectra = p.ordered_spectra;
}

/* Copy constructor */
spectral_data::spectral_data(std::map<float, float> map)
{
    this->ordered_spectra = map;
}

spectral_data::~spectral_data()
{
}


bool spectral_data::map_value_comparator(std::pair<float, float> i, std::pair<float, float> j)
{
    if (isnanf(i.second)) i.second = 0.0;
    if (isnanf(j.second)) j.second = 0.0;
    return (i.second < j.second);
}

/* Find the maximum intensity and return the intensity and wavelength pair. */
std::pair<float, float> spectral_data::max()
{
    return (*std::max_element(this->ordered_spectra.begin(), this->ordered_spectra.end(), spectral_data::map_value_comparator));
}

/* Find the maximum intensity in a range and return the intensity and wavelength pair. */
std::pair<float, float> spectral_data::max(float wavelength_min, float wavelength_max)
{
    std::map<float, float>::iterator low = this->ordered_spectra.lower_bound(wavelength_min);
    std::map<float, float>::iterator high = this->ordered_spectra.upper_bound(wavelength_max);
    
    return (*std::max_element(low, high, spectral_data::map_value_comparator));
}

/* Find the minimum intensity and return the intensity and wavelength pair. */
std::pair<float, float> spectral_data::min()
{
    return (*std::min_element(this->ordered_spectra.begin(), this->ordered_spectra.end(), spectral_data::map_value_comparator));
}

/* Find the minimum intensity in a range and return the intensity and wavelength pair. */
std::pair<float, float> spectral_data::min(float wavelength_min, float wavelength_max)
{
    std::map<float, float>::iterator low = this->ordered_spectra.lower_bound(wavelength_min);
    std::map<float, float>::iterator high = this->ordered_spectra.upper_bound(wavelength_max);
    
    return (*std::min_element(low, high, spectral_data::map_value_comparator));
}

/* Return the wavelength range. */
std::pair<float, float> spectral_data::range()
{
    return (std::pair<float, float> (this->ordered_spectra.begin()->first, this->ordered_spectra.rbegin()->first));
}

/* Return the number of elements. */
unsigned int spectral_data::size()
{
    return (this->ordered_spectra.size());
}

void spectral_data::insert(std::pair<float, float> pair)
{
    this->ordered_spectra.insert(pair);
}

void spectral_data::insert(std::string wavelength, std::string intensity)
{
    float first_value = atof(wavelength.c_str());
    
    if (first_value > 0)
    {
        float second_value = atof(intensity.c_str());
        this->ordered_spectra.insert(std::pair<float, float> (first_value, second_value));
    }
}

std::pair<float, float> spectral_data::current(float wavelength)
{
    float current_value = 0.0;
    
    try
    {
        current_value = this->ordered_spectra.at(wavelength);
    }
    catch (const std::out_of_range& oor) 
    {
        wavelength = 0.0;
    }
    
    return (std::pair<float, float> (wavelength, current_value));
}

std::pair<float, float> spectral_data::lower_bound(float wavelength)
{
    std::map<float, float>::iterator low = this->ordered_spectra.lower_bound(wavelength);
    
    if (low == this->ordered_spectra.end()) 
    {
        // No values.
    }
    else if (low == this->ordered_spectra.begin()) 
    {
        // No other value prior to this value.
    }
    else 
    {
        low = std::prev(low);
    }
    
    return (std::pair<float, float> (low->first, low->second));
}

std::pair<float, float> spectral_data::upper_bound(float wavelength)
{
    std::map<float, float>::iterator high = this->ordered_spectra.upper_bound(wavelength);
    
    return (std::pair<float, float> (high->first, high->second));
}

std::map<float, float>::iterator spectral_data::begin()
{
    return (this->ordered_spectra.begin());
}

std::map<float, float>::iterator spectral_data::end()
{
    return (this->ordered_spectra.end());
}

/* The following returns the data value for an input wavelength. The value is */
/* interpolated using a straight line approximation if an exact wavelength is not in the dataset. */
float spectral_data::get_intensity(float wavelength)
{
    float result = 0.0;

    if (this->ordered_spectra.size() > 0)
    {
        std::pair<float, float> current, low, high, prev;
        
        /* Find the current value, if it exists. */
        current = this->current(wavelength);
    
        if (current.first == wavelength)
        {
            result = current.second;
        }
        else
        {
            /* Otherwise, we attempt to interpolate the value. */
            
            /* Find nearest lower bound. */
            low = this->lower_bound(wavelength);
            
            /* Find nearest upper bound. */
            high = this->upper_bound(wavelength);

            if (low.first == wavelength)
            {
                result = low.second;
            }
            else if (high.first == wavelength)
            {
                result = high.second;
            }
            else if (high.first == this->ordered_spectra.end()->first)
            {
                /* end of data */
            }
            else
            {
                /* Striaght line interpolation. */
                double d_x = high.first  - low.first; 
                double d_y = high.second  - low.second;
                double slope = (d_y / d_x);
                double b = high.second - slope*high.first;
        
                result = slope*(wavelength) + b;	
            }
        } 	

    }
    
    return (result);
}

spectral_data spectral_data::operator-(spectral_data temp2)
{
    spectral_data data; 
    for (std::pair<float, float> element : this->ordered_spectra)
    {
        element.second = element.second - temp2.get_intensity(element.first);
        data.insert(element);
    }
    
    return (data);
}

spectral_data spectral_data::operator-=(spectral_data temp2)
{
    spectral_data data; 
    for (std::pair<float, float> element : this->ordered_spectra)
    {
        element.second = element.second - temp2.get_intensity(element.first);
        data.insert(element);
    }
    
    this->ordered_spectra = data.ordered_spectra;
    
    return (*this);
}

spectral_data spectral_data::operator*(float temp2)
{
    spectral_data data; 
    for (std::pair<float, float> element : this->ordered_spectra)
    {
        element.second = element.second * temp2;
        data.insert(element);
    }
    
    return (data);
}


spectral_data spectral_data::operator*=(spectral_data &temp2)
{
    spectral_data data; 
    for (std::pair<float, float> element : this->ordered_spectra)
    {
        element.second = element.second * temp2.get_intensity(element.first);
        data.insert(element);
    }
    
    this->ordered_spectra = data.ordered_spectra;
    
    return (data);
}

spectral_data spectral_data::operator*=(float temp2)
{
    spectral_data data; 
    for (std::pair<float, float> element : this->ordered_spectra)
    {
        element.second = element.second * temp2;
        data.insert(element);
    }
    
    this->ordered_spectra = data.ordered_spectra;
    
    return (data);
}

spectral_data spectral_data::operator=(spectral_data temp2)
{
    spectral_data data; 
        
    data.ordered_spectra = temp2.ordered_spectra;

    return (data);
}
