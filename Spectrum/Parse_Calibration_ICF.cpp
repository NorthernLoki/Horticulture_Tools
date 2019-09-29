//
// Parse_Calibration_ICF.cpp
// Version timestamp: 12-11-2018, 4:26 PM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "Parse_Calibration_ICF.h"

/* This class is a simple class to read and parse spectrometer ICF calibration files. */
/* First column is the wavelength. */
/* Second column is the data associated with the wavelength column in an ordered fashion. */
/* That is, each row of the data in the remaining columns is associated with the wavelength on the same row. */
/* For example, an ICF containing the wavelength and the "counts" file may be formatted as follows: */
/* , Live Spectrum 8 / 25 / 2018 9 : 11 : 41 PM, */
/* Wavelength[nm], Intensity, */
/* " File: SW1.icf
215.17  0.0000E+000
215.71  0.0000E+000
216.25  0.0000E+000
216.79  0.0000E+000
217.32  0.0000E+000
217.86  0.0000E+000
218.40  0.0000E+000
218.94  0.0000E+000
219.48  0.0000E+000
220.02  0.0000E+000 */
/* ... continued ... */
/* This is the Spectrawiz ICF format for calibration data. */

/* Constructor. */
Parse_Calibration_ICF::Parse_Calibration_ICF()
{
    
}

/* filepath is the operating system path to the CSV file. */
Parse_Calibration_ICF::Parse_Calibration_ICF(std::string &filepath)
{
	this->set(filepath);
}


Parse_Calibration_ICF::~Parse_Calibration_ICF()
{
}

void Parse_Calibration_ICF::operator()(std::string &filepath)
{
	this->set(filepath);
}

void Parse_Calibration_ICF::set(std::string &filepath)
{
	if (!filepath.empty())
	{
		boost::escaped_list_separator<char> separators('\\', ' ', '\"');
		boost::char_separator<char> sep(" ");
    
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

				boost::tokenizer< boost::char_separator<char> > tok(line, sep);
				vec.assign(tok.begin(), tok.end());
				if (vec.size() < 2) continue;
            
				this->ordered_spectra.insert(vec[0], vec[1]);
            
				line.clear(); // clear here, next check could fail

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
float Parse_Calibration_ICF::get_intensity(float wavelength)
{
	float result = 0.0;

	result = this->ordered_spectra.get_intensity(wavelength);
    
	return (result);
}

/* Find the maximum intensity and return the intensity and wavelength pair. */
std::pair<float, float> Parse_Calibration_ICF::get_max_intensity()
{
	return (this->max());
}

/* Find the minimum intensity and return the intensity and wavelength pair. */
std::pair<float, float> Parse_Calibration_ICF::get_min_intensity()
{
	return (this->min());
}

/* Return the wavelength range contained in the dataset. */
std::pair<float, float> Parse_Calibration_ICF::get_range()
{
	return (this->range());
}

/* Return the number of elements in the dataset. */
unsigned int Parse_Calibration_ICF::size()
{
	return (this->ordered_spectra.size());
}

/* Iterator support. */
std::map<float, float>::iterator Parse_Calibration_ICF::begin()
{
	return (this->ordered_spectra.ordered_spectra.begin());
}

/* Iterator support. */
std::map<float, float>::iterator Parse_Calibration_ICF::end()
{
	return (this->ordered_spectra.ordered_spectra.end());
}
