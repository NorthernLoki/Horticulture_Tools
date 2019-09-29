//
// Parse_Spectrum_CSV.cpp
// Version timestamp: 12-11-2018, 4:26 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "Parse_Spectrum_CSV.h"


/* This class is a simple class to read and parse spectrum data as delimeted Microsoft Excel CSV formatted files. */
/* First column is the wavelength. */
/* Second column is the data associated with the wavelength column in an ordered fashion. */
/* That is, each row of the data in the remaining columns is associated with the wavelength on the same row. */
/* For example, a csv containing the wavelength and the "counts" file may be formatted as follows: */
/* , Live Spectrum 8 / 25 / 2018 9 : 11 : 41 PM, */
/* Wavelength[nm], Intensity, */
/* 222.167, 5.4694, */
/* 222.599, 8.6868, */
/* 223.031, 5.8164, */
/* 223.464, 2.8493, */
/* 223.896, 1.9258, */
/* ... continued ... */
/* This is the Spectrawiz CSV export format for spectral captures. */

/* Constructor. */
Parse_Spectrum_CSV::Parse_Spectrum_CSV()
{
    
}

/* filepath is the operating system path to the CSV file. */
Parse_Spectrum_CSV::Parse_Spectrum_CSV(std::string &filepath)
{
	this->set(filepath);
}


Parse_Spectrum_CSV::~Parse_Spectrum_CSV()
{
}

void Parse_Spectrum_CSV::operator()(std::string &filepath)
{
	this->set(filepath);
}

void Parse_Spectrum_CSV::set(std::string &filepath)
{
	if (!filepath.empty())
	{
		boost::escaped_list_separator<char> separators('\\', ',', '\"');
		std::ifstream csv_input(filepath.c_str());
    
		if (csv_input.is_open())
		{
			std::vector<std::string> vec;
			std::string line;
			std::string buffer;
			bool inside_quotes(false);
			size_t last_quote(0);
			float first_value = 0.0;
			float second_value = 0.0;
        
			/* Read and parse the CSV file. */
			while (getline(csv_input, buffer))
			{
				line.append(buffer);

				boost::tokenizer< boost::escaped_list_separator<char> > tok(line, separators);
				vec.assign(tok.begin(), tok.end());
            
				this->ordered_spectra.insert(vec[0], vec[1]);
            
				line.clear(); 
			}
        
			csv_input.close();
		}
		else
		{
			std::cout << "Could not open file :" << filepath << std::endl;
		}
	}
	else
	{
		std::cout << "Filepath NULL." << std::endl;
	}
}

/* Get the itensity value at specified wavelength. */
float Parse_Spectrum_CSV::get_intensity(float wavelength)
{
	float result = 0.0;

	result = this->ordered_spectra.get_intensity(wavelength);
    
	return (result);
}

/* Find the maximum intensity and return the intensity and wavelength pair. */
std::pair<float, float> Parse_Spectrum_CSV::get_max_intensity()
{
	return (this->max());
}

/* Find the minimum intensity and return the intensity and wavelength pair. */
std::pair<float, float> Parse_Spectrum_CSV::get_min_intensity()
{
	return (this->min());
}

/* Return the wavelength range contained in the dataset. */
std::pair<float, float> Parse_Spectrum_CSV::get_range()
{
	return (this->range());
}

/* Return the number of elements in the dataset. */
unsigned int Parse_Spectrum_CSV::size()
{
	return (this->ordered_spectra.size());
}

/* Iterator support */
std::map<float, float>::iterator Parse_Spectrum_CSV::begin()
{
	return (this->ordered_spectra.ordered_spectra.begin());
}

/* Iterator support */
std::map<float, float>::iterator Parse_Spectrum_CSV::end()
{
	return (this->ordered_spectra.ordered_spectra.end());
}
