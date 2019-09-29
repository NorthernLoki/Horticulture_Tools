//
// spectrum.cpp
// Version timestamp: 9-28-2019, 10:57 AM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "spectrum.h"

//Radiant flux 	W(J/s) The amount of radiant energy emitted, transmitted or received per unit time 
//Radiant flux density 	(W / m^2) Radiant flux per unit area of a surface traversed by the radiation 
//Irradiance(or emittance) 	(W / m^2) Radiant flux density incident on(or emitted by) a surface 
//Spectral irradiance(or emittance) (W m^2 / µm) The radiant flux density incident on(or emitted by) a surface per unit wavelength interval 
//Radiant intensity (W/sr) Radiant flux emanating from a surface per unit solid angle 
//Radiance (W m^2/sr1) The radiant flux density emanating from a surface per unit solid angle 
//Spectral radiance (W / m^2 / sr µm) The radiant flux density emanating from a surface per unit solid angle per unit wavelength interval 
//Photon flux density (µmol / m^2 s) Number of micromoles of photons emitted, transmitted or received per unit area per unit time(usually within a specified wavelength such as the photosynthetically active region(400–700 nm)) 
//Emissivity – The ratio of the thermally generated radiance emitted by a body to the radiance that would be emitted by a black body(or perfect emitter) at the same temperature 

/* Constructor. */
spectrum::spectrum()
{
}

/* Constructor. */
/* filename is the path of the CSV formatted spectrometer data. */
/* cal_filename is the path of the ICF formatted spectrometer calibration data. */
/* dark_filename is the path of the CSV formatted dark spectrometer data. */
spectrum::spectrum(std::string filename, std::string cal_filename, std::string dark_filename)
{
    //	float ICF_integration_time = 46.0;
    //	float Sample_integration_time = 12.0;
    
        float ICF_integration_time = 44.0;
    float Sample_integration_time = 44.0;
    
    std::string RQE_filename("../Spectrums/RQE.csv"); /* Relative quantum efficiency */
    std::string BLHF_filename("../Spectrums/BLHF.csv"); /* Blue light hazard function */
    std::string AHF_filename("../Spectrums/AHF.csv"); /* Aphakic hazard function */
    std::string RTHF_filename("../Spectrums/RTHF.csv"); /* Retinal thermal hazard function */
    std::string sigmaR_filename("../Spectrums/sigmaR.csv"); /* Red phytochrome conversion */
    std::string sigmaFR_filename("../Spectrums/sigmaFR.csv"); /* Far red phytochrome conversion */
    
    csv(filename);
    cal_icf(cal_filename);
    dark_csv(dark_filename);
    RQE(RQE_filename);
    BLHF(BLHF_filename);
    AHF(BLHF_filename);
    RTHF(RTHF_filename);
    sigmaR(sigmaR_filename);
    sigmaFR(sigmaFR_filename);
    
    spectrum_calculate(ICF_integration_time, Sample_integration_time);
}


spectrum::~spectrum()
{
}

void spectrum::spectrum_calculate(float ICF_integration_time, float Sample_integration_time)
{
    /* Derives umols of irradiant photons from irradiant watts */
    double NAhc = (1.0 / ((NA) * (SPEED_LIGHT) * (PLANKS_CONSTANT))) / 1000.0;
    
    /* Derives radiance from irradiance using the maximum solid angle of 0.1 radians, for estimating maximum eye biological exposure */
    /* See, http://www.olino.org/blog/us/articles/2011/09/13/blue-light-hazard-for-the-human-eye */
    /* See, https://www.icnirp.org/cms/upload/publications/ICNIRPVisible_Infrared2013.pdf */
    double L = (4 / (M_PI)) * (1 / 0.1);
    
    this->sigmaR_energy.value = 0.0;
    this->sigmaFR_energy.value = 0.0;
    
    /* Calculate the actual reading by removing the dark offset. */
    /* Dark offset is the spectrometer reading with no incident light energy on the sensor. */
    spectral_data corrected_spectra = this->csv.ordered_spectra;
    spectral_data dark_spectra = this->dark_csv.ordered_spectra;
    corrected_spectra -= dark_spectra;			
    
    /* Correct the readings according to the calibration factors. */
    float ICF_calibration_ratio = ICF_integration_time / Sample_integration_time;
    spectral_data icf_spectra = this->cal_icf.ordered_spectra;
    corrected_spectra *= ICF_calibration_ratio;
    corrected_spectra *= icf_spectra;	
    
    /* Calculate the spectral irradiance. */
    float previous_wavelength, previous_intensity;
    for (std::pair<float, float> element : corrected_spectra)
    {
        static bool initial = true;
        
        if (initial)
        {
            previous_wavelength = element.first;
            previous_intensity = element.second;
            initial = false;
            continue;
        }
        
        float delta_wavelength = element.first - previous_wavelength; 
        float irradiant_energy = delta_wavelength * ((previous_intensity + element.second) / 2);
        
        irradiance_energy.insert(std::pair<float, float>(previous_wavelength + (delta_wavelength / 2), irradiant_energy)); 
        
        if ((element.first <= 700) && (element.first >= 400))
        {
            irradiance += delta_wavelength * ((previous_intensity + element.second) / 2);
        }
        
        previous_wavelength = element.first;
        previous_intensity = element.second;	
    }
    
    
    /* Calculate irradiation PAR in umols */	
    for (std::pair<float, float> element : irradiance_energy)
    {	
        float local_PAR = element.first * element.second * (NAhc);
        par_energy.insert(std::pair<float, float>(element.first, local_PAR)); 
        
        float local_ypf = local_PAR * this->RQE.get_intensity(element.first);
        ypf_energy.insert(std::pair<float, float>(element.first, local_ypf)); 
        
        float local_blhf = L * element.second * this->BLHF.get_intensity(element.first);
        float local_ahf = L * element.second * this->AHF.get_intensity(element.first);
        float local_rthf = L * element.second * this->RTHF.get_intensity(element.first);
        
        if ((element.first <= this->par_regions_bugbee.spectrum_max) && (element.first >= this->par_regions_bugbee.spectrum_min))
        {
            /* Standard PAR regions. */
            int i = 0;
            while (!this->par_regions.region[i].name.empty())
            {
                if ((element.first >= par_regions.region[i].starting_wavelength) && (element.first < par_regions.region[i].ending_wavelength))
                {
                    this->par_regions.region[i].value += local_PAR;
                    break;
                } 
                i++;
            }
            
            /* Standard YPF regions. */
            i = 0;
            while (!this->ypf_regions.region[i].name.empty())
            {
                if ((element.first >= ypf_regions.region[i].starting_wavelength) && (element.first < ypf_regions.region[i].ending_wavelength))
                {
                    this->ypf_regions.region[i].value += local_ypf;
                    break;
                } 
                i++;
            }
            
            /* Bugbee defined PAR regions. */
            i = 0;
            while (!this->par_regions_bugbee.region[i].name.empty())
            {
                if ((element.first >= par_regions_bugbee.region[i].starting_wavelength) && (element.first < par_regions_bugbee.region[i].ending_wavelength))
                {
                    this->par_regions_bugbee.region[i].value += local_PAR;
                    break;
                } 
                i++;
            }
            
            /* YPF over Bugbee defined PAR regions. */
            i = 0;
            while (!this->ypf_regions_bugbee.region[i].name.empty())
            {
                if ((element.first >= ypf_regions_bugbee.region[i].starting_wavelength) && (element.first < ypf_regions_bugbee.region[i].ending_wavelength))
                {
                    this->ypf_regions_bugbee.region[i].value += local_ypf;
                    break;
                } 
                i++;
            }
            
            if ((element.first <= this->par_regions.spectrum_max) && (element.first >= this->par_regions.spectrum_min))
            {
                this->par += local_PAR;
            }
            
            if ((element.first <= this->ypf_regions.spectrum_max) && (element.first >= this->ypf_regions.spectrum_min))
            {
                this->ypf += local_ypf;
            }
            
            if ((element.first <= this->sigmaFR_energy.spectrum_max) && (element.first >= this->sigmaFR_energy.spectrum_min))
            {
                this->sigmaR_energy.value += local_PAR * this->sigmaR.get_intensity(element.first);
                this->sigmaFR_energy.value += local_PAR * this->sigmaFR.get_intensity(element.first);
            }
            
            if ((element.first <= this->blhf_regions.spectrum_max) && (element.first >= this->blhf_regions.spectrum_min))
            {
                this->blhf += local_blhf;
            }
            
            if ((element.first <= this->ahf_regions.spectrum_max) && (element.first >= this->ahf_regions.spectrum_min))
            {
                this->ahf += local_ahf;
            }
            
            if ((element.first <= this->rthf_regions.spectrum_max) && (element.first >= this->rthf_regions.spectrum_min))
            {
                this->rthf += local_rthf;
            }
            
            /* Total PAR from 287-850nm */
            this->par_287_850 += local_PAR;
            /* Total ypf from 287-850nm */
            this->ypf_287_850 += local_ypf;
        }
    }
}

spectrum spectrum::set(std::string filename, std::string cal_filename, std::string dark_filename)
{
    float ICF_integration_time = 46.0;
    float Sample_integration_time = 12.0;
    
    std::string RQE_filename("../Spectrums/RQE.csv");
    std::string sigmaR_filename("../Spectrums/sigmaR.csv");
    std::string sigmaFR_filename("../Spectrums/sigmaFR.csv");
    
    csv(filename);
    cal_icf(cal_filename);
    dark_csv(dark_filename);
    RQE(RQE_filename);
    sigmaR(sigmaR_filename);
    sigmaFR(sigmaFR_filename);
    
    spectrum_calculate(ICF_integration_time, Sample_integration_time);
    
    return (*this);
}


spectrum spectrum::operator()(std::string filename, std::string cal_filename, std::string dark_filename)
{

    this->set(filename, cal_filename, dark_filename);
    
    return (*this);
}


double spectrum::calculate_rayleigh_scattering(double wavelength)
{

}

/* Erythema action spectrum */
/* Komhyr, W.D. and L. Machta, "The relative response of erythema",
 * in: The Perturbed Troposphere of 1990 and 2020 Vol. IV. CIAP, Dept. of Transportation, 
 * Washington. DC., 1973. 
 * # Parameterization by A.E.S. Green, T. Sawada, and E.P Shettle, 
 * The middle ultraviolet reaching the ground, Photochemistry and Photobiology, 19, 251-259, 1974.
 * */
/* https://www.esrl.noaa.gov/gmd/grad/antuv/docs/version2/descVersion2Database3.html */
/* Integration range: 286 - 400 nm */
/* Output units : µW/cm2 */
double spectrum::calculate_komhyr_action_spectra(double wavelength)
{
    double exp1 = exp((wavelength - 296.5) / 2.692);
    double exp2 = exp((wavelength - 311.4) / 3.13);
    double exp3 = (1.0 + exp1) * (1.0 + exp1);
    
    double action = (0.04485 /  (1 + exp2)) +  ((4 * 0.9949*exp1) / exp3);
    
    return (action);
}

/* Erythema action spectrum */
/* B.L. Diffey, "A comparison of dosimeters used for solar ultraviolet radiometry", Photochemistry and Photobiology, 46, 55-60, 1987. */
/* https://www.esrl.noaa.gov/gmd/grad/antuv/docs/version2/descVersion2Database3.html */
/* Integration range: 286 - 400 nm */
/* Output units : µW/cm2 */
double spectrum::calculate_diffey_action_spectra(double wavelength)
{

}

/* Erythema action spectrum */
/* A.F. McKinlay, A.F. and B.L. Diffey, "A reference action spectrum for ultraviolet induced erythema in human skin", CIE Research Note, 6(1), 17-22, 1987 */
/* https://www.esrl.noaa.gov/gmd/grad/antuv/docs/version2/descVersion2Database3.html */
/* Integration range: 286 - 400 nm */
/* Output units : UV Index, see http://uv.biospherical.com/Solar_Index_Guide.pdf */
double spectrum::calculate_mckinlay_action_spectra(double wavelength)
{
    double action;
    if (wavelength < 298.0)
    {
        action = 1.0;
    }
    else if (wavelength < 328.0)
    {
        action = pow(10, (0.094 * (298.0 - wavelength)));
    }
    else
    {
        action = pow(10, (0.015 * (139.0 - wavelength)));
    }
    
    
    return (action);
}

/* Action spectrum for growth responses of plants */
/* S. D. Flint and M. M. Caldwell
 * "A biological spectral weighting function for ozone depletion research with higher plants", Physiologia Plantarum, 2003 */
/* https://www.esrl.noaa.gov/gmd/grad/antuv/docs/version2/descVersion2Database3.html */
/* Integration range: 286 - 390 nm. Wavelength in nm. */
/* Output units : µW/cm2 */
double spectrum::calculate_flint_action_spectra(double wavelength)
{
    double exp1 = -1.0 * exp((0.1703411)*(wavelength - 307.867) / 1.15);
    double exp2 = 4.688272 * exp(exp1);
    
    double action = exp(exp2 + ((390.0 - wavelength) / 121.7557 - 4.183832));
    
    return (action);
}

/* Generalized plant action spectrum  */
/* M.M. Caldwell,
 * "Solar UV irradiation and the growth and development of higher plants",Photophysiology, 
 * edited by A.C. Giese, Volume 6, Chapter 4, pp. 131 - 177, 1971 */
/* https://www.esrl.noaa.gov/gmd/grad/antuv/docs/version2/descVersion2Database3.html */
/* Integration range: 286 - 313 nm */
/* Output units : µW/cm2 */
double spectrum::calculate_caldwell_action_spectra(double wavelength)
{
    double exp1 = exp((300.0 - wavelength) / 31.08);
    double pow2 = 1.0 - ((wavelength / 313.3) * (wavelength / 313.3));
    
    double action = 2.618*exp1*pow2;
    
    return (action);
}
