#pragma once
#include <boost/format.hpp>
#include "spectrum.h"

#ifdef __cplusplus
extern "C" {
#endif

void SpectrumGraphTest();	
int SpectrumTest();
void SpectrumCalTest();
void plot_spectrum(spectrum *spectral_results, unsigned int min_wavelength, unsigned int max_wavelength, unsigned int wavelength_stride);
void plot_ypf_spectrum(spectrum *spectral_results, unsigned int min_wavelength, unsigned int max_wavelength, unsigned int wavelength_stride);

#ifdef __cplusplus
}
#endif
