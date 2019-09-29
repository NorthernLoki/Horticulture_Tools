//
// spectral_data.h
// Version timestamp: 9-28-2019, 10:58 AM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once     
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <boost/unordered_map.hpp>

class spectral_data
{
public:
    spectral_data();
    spectral_data(const spectral_data &p);
    spectral_data(std::map<float, float> map);
    ~spectral_data();
    
    static bool map_value_comparator(std::pair<float, float> i, std::pair<float, float> j);
    std::pair<float, float> max();
    std::pair<float, float> max(float wavelength_min, float wavelength_max);
    std::pair<float, float> min();
    std::pair<float, float> min(float wavelength_min, float wavelength_max);
    std::pair<float, float> range();
    unsigned int size();
    void insert(std::pair<float, float> pair);
    void insert(std::string wavelength, std::string intensity);
    std::pair<float, float> current(float wavelength);
    std::pair<float, float> lower_bound(float wavelength);
    std::pair<float, float> upper_bound(float wavelength);
    float get_intensity(float wavelength);
    std::map<float, float>::iterator begin();
    std::map<float, float>::iterator end();
    
    virtual spectral_data operator-(spectral_data temp2);
    virtual spectral_data operator=(spectral_data temp2);
    virtual spectral_data operator-=(spectral_data temp2);
    virtual spectral_data operator*(float temp2);
    virtual spectral_data operator*=(spectral_data &temp2);
    virtual spectral_data operator*=(float temp2);
    
    std::map<float, float> ordered_spectra;
    boost::unordered::unordered_map<float, float> spectra;
}



