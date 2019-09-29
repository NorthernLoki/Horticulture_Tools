//
// spectrum.h
// Version timestamp: 9-28-2019, 10:58 AM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#pragma once
#include <math.h>
#include "Conversion_Constants.h"
#include "Parse_Spectrum_CSV.h"
#include "Parse_Calibration_ICF.h"

typedef struct Spectrum_Region
{
    std::string name;
    float starting_wavelength;
    float ending_wavelength;
    float value;
} Spectrum_Region_t, *Spectrum_Region_p;

typedef struct PAR_Regions
{
    const float spectrum_min = 400.0;
    const float spectrum_max = 700.0;
    Spectrum_Region_t region[4] = 
    {
        { "Blue", 400.0, 500.0, 0.0 }, 
        { "Green", 500.0, 600.0, 0.0 }, 
        { "Red", 600.0, 700.0, 0.0 }, 
        { "", 0.0, 0.0, 0.0 }
    }; 
} PAR_Regions_t, *PAR_Regions_p;

typedef struct PAR_Regions_Bugbee
{
    const float spectrum_min = 287.0;
    const float spectrum_max = 850.0;
    Spectrum_Region_t region[7] = 
    {
        { "UVB", 287.0, 320.0, 0.0 }, 
        { "UVA", 320.0, 400, 0.0 }, 
        { "Violet_Blue", 400.0, 475.0, 0.0 }, 
        { "Cyan_Green", 475.0, 550.0, 0.0 }, 
        { "Green_Yellow_Red", 550.0, 700.0, 0.0 }, 
        { "FarRed_NearIR", 700.0, 850.0, 0.0 }, 
        { "", 0.0, 0.0, 0.0 }
    }; 
} PAR_Regions_Bugbee_t, *PAR_Regions_Bugbee_p;

typedef struct YPF_Regions
{
    const float spectrum_min = 360.0;
    const float spectrum_max = 760.0;
    Spectrum_Region_t region[4] = 
    {
        { "Blue", 400.0, 500.0, 0.0 }, 
        { "Green", 500.0, 600.0, 0.0 }, 
        { "Red", 600.0, 700.0, 0.0 }, 
        { "", 0.0, 0.0, 0.0 }
    }; 
} YPF_Regions_t, *YPF_Regions_p;

typedef struct YPF_Regions_Bugbee
{
    const float spectrum_min = 287.0;
    const float spectrum_max = 850.0;
    Spectrum_Region_t region[7] = 
    {
        { "UVB", 287.0, 320.0, 0.0 }, 
        { "UVA", 320.0, 400, 0.0 }, 
        { "Violet_Blue", 400.0, 475.0, 0.0 }, 
        { "Cyan_Green", 475.0, 550.0, 0.0 }, 
        { "Green_Yellow_Red", 550.0, 700.0, 0.0 }, 
        { "FarRed_NearIR", 700.0, 850.0, 0.0 }, 
        { "", 0.0, 0.0, 0.0 }
    }; 
} YPF_Regions_Bugbee_t, *YPF_Regions_Bugbee_p;

typedef struct PPS_Regions
{
    const float spectrum_min = 300.0;
    const float spectrum_max = 800.0;
    float value;
} PPS_Regions_t, *PPS_Regions_p;

typedef struct BLHF_Regions
{
    const float spectrum_min = 300.0;
    const float spectrum_max = 1400.0;
    float value;
} BLHF_Regions_t, *BLHF_Regions_p;

typedef struct AHF_Regions
{
    const float spectrum_min = 300.0;
    const float spectrum_max = 1400.0;
    float value;
} AHF_Regions_t, *AHF_Regions_p;

typedef struct RTHF_Regions
{
    const float spectrum_min = 300.0;
    const float spectrum_max = 1400.0;
    float value;
} RTHF_Regions_t, *RTHF_Regions_p;

class spectrum
{
public:
    spectrum();
    spectrum(std::string filename, std::string cal_filename, std::string dark_filename);
    ~spectrum();
    
    spectrum set(std::string filename, std::string cal_filename, std::string dark_filename);
    //void spectrum_calculate(float ICF_integration_time, float Sample_integration_time, const Parse_Spectrum_CSV *csv, Parse_Calibration_ICF *cal_icf, Parse_Spectrum_CSV *dark_csv, Parse_Spectrum_CSV *RQE, Parse_Spectrum_CSV *sigmaR, Parse_Spectrum_CSV *sigmaFR);
    void spectrum_calculate(float ICF_integration_time, float Sample_integration_time);
    double calculate_rayleigh_scattering(double wavelength);
    double calculate_komhyr_action_spectra(double wavelength);
    double calculate_diffey_action_spectra(double wavelength);
    double calculate_mckinlay_action_spectra(double wavelength);
    double calculate_flint_action_spectra(double wavelength);
    double calculate_caldwell_action_spectra(double wavelength);
    
    virtual spectrum operator()(std::string filename, std::string cal_filename, std::string dark_filename);
    
    spectral_data irradiance_energy;
    spectral_data par_energy;
    spectral_data ypf_energy;
    float irradiance = 0.0;
    float par = 0.0;
    float par_287_850 = 0.0;
    PAR_Regions_t par_regions;
    PAR_Regions_Bugbee_t par_regions_bugbee;
    PPS_Regions_t sigmaR_energy;
    PPS_Regions_t sigmaFR_energy;
    BLHF_Regions_t blhf_regions;
    AHF_Regions_t ahf_regions;
    RTHF_Regions_t rthf_regions;
    float blhf = 0.0;
    float ahf = 0.0;
    float rthf = 0.0;
    float ypf = 0.0;
    float ypf_287_850 = 0.0;
    YPF_Regions_t ypf_regions;
    YPF_Regions_Bugbee_t ypf_regions_bugbee;
    Parse_Spectrum_CSV csv;
    Parse_Calibration_ICF cal_icf;
    Parse_Spectrum_CSV dark_csv;
    Parse_Spectrum_CSV RQE; /* Relative quantum efficiency */
    Parse_Spectrum_CSV BLHF; /* Blue light hazard function */
    Parse_Spectrum_CSV AHF; /* Aphakic hazard function */    
    Parse_Spectrum_CSV RTHF; /* Retinal thermal hazard function */        
    Parse_Spectrum_CSV sigmaR;
    Parse_Spectrum_CSV sigmaFR;
};
