//
// Parse_Spectrum_CSV.h
// Version timestamp: 12-11-2018, 4:27 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <fstream>      
#include <vector>
#include <string>
#include <map>
#include <iostream>  
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>
#include "spectral_data.h"

class Parse_Spectrum_CSV : public spectral_data
{
public:
	Parse_Spectrum_CSV();
	Parse_Spectrum_CSV(std::string &filepath);
	~Parse_Spectrum_CSV();
    
	void set(std::string &filepath);
	float get_intensity(float wavelength);
	std::pair<float, float> get_max_intensity();
	std::pair<float, float> get_min_intensity();
	std::pair<float, float> get_range();
	unsigned int size();
	std::map<float, float>::iterator begin();
	std::map<float, float>::iterator end();
	virtual void operator()(std::string &filepath);
	
	spectral_data ordered_spectra;
};

