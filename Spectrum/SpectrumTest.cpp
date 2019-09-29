//
// SpectrumTest.cpp
// Version timestamp: 9-28-2019, 10:57 AM
//
// Attribution : Copyright (c) 2018 Northern_Loki (sha256::6F290BF833967127BE26C92C8F6B1C1A3949C55A7EABCEF3ECC785CD2D38D30D)
// License is granted under the Creative Commons Attribution-ShareAlike 4.0 International.  https://creativecommons.org/licenses/by-sa/4.0/
//
#include "SpectrumTest.h"

/*
    To test the library, include "Spectrum.h" from an application project
    and call SpectrumTest().
    
    Do not forget to add the library to Project Dependencies in Visual Studio.
*/

namespace
{
    enum Code
    {
        BOLD             = 1,
        UNDERLINE        = 4,
        NEGATIVE         = 7,
        CONCEAL          = 8,
        STRIKE           = 28,
        FG_BLACK         = 30,
        FG_RED           = 31,
        FG_GREEN         = 32,
        FG_YELLOW        = 33,
        FG_BLUE          = 34,
        FG_MAGENTA       = 35,
        FG_CYAN          = 36,
        FG_WHITE         = 37,
        FG_DARK_GRAY     = 38,
        FG_DEFAULT       = 39,
        FG_LIGHT_BLACK   = 90,
        FG_ORANGE        = 91,
        FG_LIGHT_GREEN   = 92,
        FG_LIGHT_YELLOW  = 93,
        FG_LIGHT_BLUE    = 94,
        FG_LIGHT_MAGENTA = 95,
        FG_LIGHT_CYAN    = 96,
        BG_BLACK         = 40,
        BG_RED           = 41,
        BG_GREEN         = 42,
        BG_YELLOW        = 43,
        BG_BLUE          = 44,
        BG_MAGENTA       = 45,
        BG_CYAN          = 46,
        BG_WHITE         = 47,
        BG_DARK_GRAY     = 48,
        BG_DEFAULT       = 49,
        BG_LIGHT_BLACK   = 100,
        BG_ORANGE        = 101,
        BG_LIGHT_GREEN   = 102,
        BG_LIGHT_YELLOW  = 103,
        BG_LIGHT_BLUE    = 104,
        BG_LIGHT_MAGENTA = 105,
        BG_LIGHT_CYAN    = 106,
        BG_LIGHT_WHITE   = 107	
    };
    
    std::ostream& operator<<(std::ostream& os, Code code) 
    {
        return os << "\033[" << static_cast<int>(code) << "m";
    }
}


static int s_Test = 0;

int SpectrumTest()
{
    std::string filename("../Spectrums/09_21_2019/Mars_SP250_Full_Spectrum.csv");
    std::string cal_filename("../Spectrums/09_21_2019/SW1.icf");
    std::string dark_filename("../Spectrums/09_21_2019/Dark_Spectrum.csv");
    std::string RQE_filename("../Spectrums/RQE.csv");
    std::string sigmaR_filename("../Spectrums/sigmaR.csv");
    std::string sigmaFR_filename("../Spectrums/sigmaFR.csv");
    
    spectrum spectral_results(filename, cal_filename, dark_filename);
    
    plot_spectrum(&spectral_results, 380, 860, 4);
    plot_ypf_spectrum(&spectral_results, 380, 860, 4);
    
    int i = 0;
    float par_total = 0.0; 
    while (!spectral_results.par_regions.region[i].name.empty())
    {
        float par_value_percent = (spectral_results.par_regions.region[i].value / spectral_results.par) * 100.0;
        par_total +=  par_value_percent;
        std::cout << 
            spectral_results.par_regions.region[i].name << 
            "(" << spectral_results.par_regions.region[i].starting_wavelength << " - " << spectral_results.par_regions.region[i].ending_wavelength << "nm)" <<
            ": " <<  par_value_percent << 
            "%" << std::endl;
        i++;
    }
    std::cout << "Total :" << par_total << "%" << std::endl << std::endl;
    
    i = 0;
    par_total = 0.0; 
    while (!spectral_results.par_regions_bugbee.region[i].name.empty())
    {
        float par_value_percent = (spectral_results.par_regions_bugbee.region[i].value / spectral_results.par_287_850) * 100.0;
        par_total +=  par_value_percent;
        std::cout << 
            spectral_results.par_regions_bugbee.region[i].name << 
            "(" << spectral_results.par_regions_bugbee.region[i].starting_wavelength << "-" << spectral_results.par_regions_bugbee.region[i].ending_wavelength << "nm)" <<
            ": " << par_value_percent << 
            "%" << std::endl;
        i++;
    }
    std::cout << "Total :" << par_total << "%" << std::endl << std::endl;
    
    std::cout << " Irradiant Energy : " << spectral_results.irradiance << std::endl;
    std::cout << " PAR Energy (400-700nm): " << spectral_results.par << std::endl;
    std::cout << " PAR Energy (287-850nm): " << spectral_results.par_287_850 << std::endl;
    /* DLI is the number of PAR delivered over the daytime. It is an integral measured in Mmols */
    float DLI = spectral_results.par * 12.0 * (SECONDS_HOUR) / 1000000.0;
    std::cout << " DLI : " << DLI << std::endl;
    std::cout << " YPF Energy (360-760nm): " << spectral_results.ypf << std::endl;
    std::cout << " YPF/PFD: " << spectral_results.ypf / spectral_results.par << std::endl;
    std::cout << " PPS (phytochrome photostationary state): " << spectral_results.sigmaR_energy.value / (spectral_results.sigmaR_energy.value + spectral_results.sigmaFR_energy.value) << std::endl;

    std::cout << " PAR Max :" << spectral_results.par_energy.max().second << " @" << spectral_results.par_energy.max().first << " nm." << std::endl;
    std::cout << " PAR Min :" << spectral_results.par_energy.min().second << " @" << spectral_results.par_energy.min().first << " nm." << std::endl;
    
    std::cout << std::endl << " Blue Light Hazard :" << spectral_results.blhf << " ." << std::endl;
    std::cout << " Aphakic Light Hazard :" << spectral_results.ahf << " ." << std::endl;
    std::cout << " Retinal Thermal Light Hazard :" << spectral_results.rthf << " ." << std::endl;

    return ++s_Test;
}

void SpectrumGraphTest()
{
    std::string filename("../Spectrums/601C_Full_1000_Spectrum.csv");
    std::string cal_filename("../Spectrums/SW1.icf");
    std::string dark_filename("../Spectrums/601C_Full_0_Spectrum.csv");
    std::string RQE_filename("../Spectrums/RQE.csv");
    std::string sigmaR_filename("../Spectrums/sigmaR.csv");
    std::string sigmaFR_filename("../Spectrums/sigmaFR.csv");
    
    spectrum spectral_results(filename, cal_filename, dark_filename);
    
    plot_spectrum(&spectral_results, 380, 860, 1);
    plot_spectrum(&spectral_results, 380, 860, 2);
    plot_spectrum(&spectral_results, 380, 860, 3);
    plot_spectrum(&spectral_results, 380, 860, 4);
    plot_spectrum(&spectral_results, 380, 860, 5);
    
    plot_ypf_spectrum(&spectral_results, 380, 860, 1);
    plot_ypf_spectrum(&spectral_results, 380, 860, 2);
    plot_ypf_spectrum(&spectral_results, 380, 860, 3);
    plot_ypf_spectrum(&spectral_results, 380, 860, 4);
    plot_ypf_spectrum(&spectral_results, 380, 860, 5);
    
}

void SpectrumCalTest()
{
    std::string cal_filename("../Spectrums/SW1.icf");
    std::string dark_filename_601G("../Spectrums/601C_Full_0_Spectrum.csv");
    std::string RQE_filename("../Spectrums/RQE.csv");
    std::string sigmaR_filename("../Spectrums/sigmaR.csv");
    std::string sigmaFR_filename("../Spectrums/sigmaFR.csv");
    spectrum spectral_results[22];
    
    std::vector<std::tuple<int, std::string, spectrum*>> spectra;
    
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601G_FULL_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601G_FULL_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601G_FULL_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601G_FULL_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601G_FULL_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601G_FULL_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601G_FULL_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601G_FULL_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601G_FULL_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601G_FULL_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601G_FULL_0_Spectrum.csv", new spectrum));

    std::cout << "Spectral Intensity for Heliospectra 601G Full" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601G);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    spectra.clear();
    dark_filename_601G = "../Spectrums/601G_450nm_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601G_450nm_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601G_450nm_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601G_450nm_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601G_450nm_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601G_450nm_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601G_450nm_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601G_450nm_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601G_450nm_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601G_450nm_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601G_450nm_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601G_450nm_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601G 450nm" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601G);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;

    spectra.clear();
    dark_filename_601G = "../Spectrums/601G_660nm_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601G_660nm_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601G_660nm_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601G_660nm_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601G_660nm_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601G_660nm_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601G_660nm_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601G_660nm_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601G_660nm_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601G_660nm_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601G_660nm_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601G_660nm_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601G 660nm" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601G);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    spectra.clear();
    dark_filename_601G = "../Spectrums/601G_5700K_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601G_5700K_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601G_5700K_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601G_5700K_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601G_5700K_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601G_5700K_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601G_5700K_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601G_5700K_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601G_5700K_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601G_5700K_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601G_5700K_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601G_5700K_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601G 5700K" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601G);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    spectra.clear();
    std::string dark_filename_601C("../Spectrums/601C_Full_0_Spectrum.csv");
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601C_Full_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601C_Full_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601C_Full_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601C_Full_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601C_Full_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601C_Full_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601C_Full_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601C_Full_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601C_Full_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601C_Full_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601C_Full_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601C Full" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601C);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    spectra.clear();
    dark_filename_601C = "../Spectrums/601C_450nm_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601C_450nm_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601C_450nm_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601C_450nm_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601C_450nm_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601C_450nm_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601C_450nm_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601C_450nm_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601C_450nm_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601C_450nm_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601C_450nm_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601C_450nm_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601C 450nm" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601C);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    std::vector<std::tuple<int, std::string, spectrum*>>::iterator element;
    element = spectra.begin();
    std::tuple<int, std::string, spectrum*> local_spectrum = *element;
    //plot_spectrum(std::get<2>(local_spectrum), 380, 860, 4);
    
    spectra.clear();
    dark_filename_601C = "../Spectrums/601C_660nm_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601C_660nm_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601C_660nm_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601C_660nm_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601C_660nm_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601C_660nm_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601C_660nm_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601C_660nm_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601C_660nm_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601C_660nm_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601C_660nm_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601C_660nm_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601C 660nm" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601C);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    //std::vector<std::tuple<int, std::string, spectrum*>>::iterator element;
    element = spectra.begin();
    local_spectrum = *element;
    //plot_spectrum(std::get<2>(local_spectrum), 380, 860, 4);
    
    spectra.clear();
    dark_filename_601C = "../Spectrums/601C_735nm_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601C_735nm_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601C_735nm_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601C_735nm_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601C_735nm_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601C_735nm_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601C_735nm_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601C_735nm_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601C_735nm_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601C_735nm_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601C_735nm_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601C_735nm_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601C 735nm" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601C);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    //std::vector<std::tuple<int, std::string, spectrum*>>::iterator element;
    element = spectra.begin();
    local_spectrum = *element;
    //plot_spectrum(std::get<2>(local_spectrum), 380, 860, 4);
    
    spectra.clear();
    dark_filename_601C = "../Spectrums/601C_5700K_0_Spectrum.csv";
    spectra.push_back(std::tuple<int, std::string, spectrum*>(1000, "../Spectrums/601C_5700K_1000_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(900, "../Spectrums/601C_5700K_900_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(800, "../Spectrums/601C_5700K_800_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(700, "../Spectrums/601C_5700K_700_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(600, "../Spectrums/601C_5700K_600_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(500, "../Spectrums/601C_5700K_500_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(400, "../Spectrums/601C_5700K_400_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(300, "../Spectrums/601C_5700K_300_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(200, "../Spectrums/601C_5700K_200_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(100, "../Spectrums/601C_5700K_100_Spectrum.csv", new spectrum));
    spectra.push_back(std::tuple<int, std::string, spectrum*>(0, "../Spectrums/601C_5700K_0_Spectrum.csv", new spectrum));
    
    std::cout << "Spectral Intensity for Heliospectra 601C 5700K" << std::endl;
    for (std::tuple<int, std::string, spectrum*> element : spectra)
    {
        spectrum *local_spectrum = std::get<2>(element);
        local_spectrum->set(std::get<1>(element), cal_filename, dark_filename_601C);
        std::cout << "PAR@" << std::get<0>(element) << " :" << local_spectrum->par << " DLI (12 hours) :" << local_spectrum->par * 12.0 * (SECONDS_HOUR) / 1000000.0 << std::endl;
    }
    std::cout << std::endl;
    
    //std::vector<std::tuple<int, std::string, spectrum*>>::iterator element;
    element = spectra.begin();
    local_spectrum = *element;
    //plot_spectrum(std::get<2>(local_spectrum), 380, 860, 4);
}

/* Plot spectra. Stride = the number of wavelength to skip, e.g. every 5th wavelength is plotted with the integrated power for stride = 5. */
/* min and max wavelength is the plot range. */
void plot_spectrum(spectrum *spectral_results, unsigned int min_wavelength, unsigned int max_wavelength, unsigned int wavelength_stride)
{
    int wavelength = 0;
    float total_par = 0.0;
    float integrate_range = 0.0;
    std::cout << "********************************************************************************************************************" << std::endl;
    std::cout << "*********************************** Irradiance Spectrum ************************************************************" << std::endl;
    std::cout << "********************************************************************************************************************" << std::endl;
    
    if ((spectral_results != NULL) && (wavelength_stride > 0))
    {
        std::pair<float, float> wavelength_range = spectral_results->par_energy.range();
    
        /* Sanity, clamp wavelength range to available spectral range. */
        if (wavelength_range.first > min_wavelength) min_wavelength = wavelength_range.first;
        if (wavelength_range.second < max_wavelength) max_wavelength = wavelength_range.second;
    
        std::cout << "Calculating : " << std::endl;
        double distmax = spectral_results->par_energy.max(min_wavelength, max_wavelength).second * wavelength_stride;
        double distmin = spectral_results->par_energy.min(min_wavelength, max_wavelength).second; 
        
        int distmax_ceil = ceil(distmax);
        int distmin_floor = floor(distmin);	
        double chart_x_quant = 120.0 / (distmax_ceil - distmin_floor);
    
        /* Plot the chart */
        for (std::pair<float, float> element : spectral_results->par_energy)
        {
            wavelength++;
            double distance = element.second;

            if (element.first >= min_wavelength && element.first <= max_wavelength)
            {
                integrate_range += distance;
                if (wavelength % wavelength_stride == 0)
                {
                    
                    if ((element.first >= 400) && (element.first <= 700))
                    {
                        total_par += integrate_range;
                    }

                    std::cout << FG_DEFAULT <<  boost::format("%8.2f") % element.first << FG_YELLOW << " : ";
                    
                    if (element.first <= 850)
                    {
                        if (element.first > 700)
                        {
                            std::cout << FG_MAGENTA;
                        }
                        else if (element.first > 614)
                        {
                            std::cout << FG_RED;
                        }
                        else if (element.first > 589)
                        {
                            std::cout << FG_ORANGE;
                        }
                        else if (element.first > 574)
                        {
                            std::cout << FG_YELLOW;
                        }
                        else if (element.first > 564)
                        {
                            std::cout << FG_LIGHT_YELLOW;
                        }
                        else if (element.first > 550)
                        {
                            std::cout << FG_LIGHT_GREEN;
                        }
                        else if (element.first > 517)
                        {
                            std::cout << FG_GREEN;
                        }
                        else if (element.first > 476)
                        {
                            std::cout << FG_CYAN;
                        }
                        else if (element.first > 400)
                        {
                            std::cout << FG_LIGHT_BLUE;
                        }
                        else if (element.first > 321)
                        {
                            std::cout << FG_BLUE;
                        }		
                        else if (element.first > 287)
                        {
                            std::cout << FG_BLUE;
                        }		
                    }
     
                    int dots = ceil(((integrate_range) - distmin)*chart_x_quant);
                    std::cout << std::string(dots, '*') << FG_YELLOW << " : " << FG_DEFAULT << integrate_range << FG_DEFAULT;
            
                    std::cout << std::endl;
                    integrate_range = 0.0;
                }
                else
                {

                }
            }
    
        }
        std::cout << "Total PAR : " <<  total_par << std::endl;	
        std::cout << std::endl;	
    }
    else
    {
        std::cout << "Plot NULL spectra." << std::endl;
    }
}

/* YPF */
/* Plot parameters. Stride = the number of wavelength to skip, e.g. every 5th wavelength is plotted with the integrated power for stride = 5. */
/* min and max wavelength is the plot range. */
void plot_ypf_spectrum(spectrum *spectral_results, unsigned int min_wavelength, unsigned int max_wavelength, unsigned int wavelength_stride)
{
    
    int wavelength = 0;
    float total_par = 0.0;
    float integrate_range = 0.0;
    float ypf_range = 0.0;
    std::cout << "********************************************************************************************************************" << std::endl;
    std::cout << "*********************************** Irradiance Spectrum ************************************************************" << std::endl;
    std::cout << "********************************************************************************************************************" << std::endl;
    
    if ((spectral_results != NULL) && (wavelength_stride > 0))
    {
        std::pair<float, float> wavelength_range = spectral_results->par_energy.range();
    
        /* Sanity, clamp wavelength range to available spectral range. */
        if (wavelength_range.first > min_wavelength) min_wavelength = wavelength_range.first;
        if (wavelength_range.second < max_wavelength) max_wavelength = wavelength_range.second;
        
        std::cout << "Calculating : " << std::endl;
        double distmax = spectral_results->par_energy.max(min_wavelength, max_wavelength).second * wavelength_stride;
        double distmin = spectral_results->par_energy.min(min_wavelength, max_wavelength).second; 
        
        int distmax_ceil = ceil(distmax);
        int distmin_floor = floor(distmin);	
        double chart_x_quant = 120.0 / (distmax_ceil - distmin_floor);

    
        /* Plot the chart */
        std::map<float, float>::iterator ypf_interator = spectral_results->ypf_energy.ordered_spectra.begin();
        for (std::pair<float, float> element : spectral_results->par_energy)
        {
            wavelength++;
            double distance = element.second;
            double ypf_distance = ypf_interator->second;
            ypf_interator++;

            if (element.first >= min_wavelength && element.first <= max_wavelength)
            {
                integrate_range += distance;
                ypf_range += ypf_distance;
                
                if (wavelength % wavelength_stride == 0)
                {
                    
                    if ((element.first >= 400) && (element.first <= 700))
                    {
                        total_par += integrate_range;
                    }

                    std::cout << FG_DEFAULT <<  boost::format("%8.2f") % element.first << FG_YELLOW << " : ";
                    
                    if (element.first <= 850)
                    {
                        if (element.first > 700)
                        {
                            std::cout << FG_MAGENTA;
                        }
                        else if (element.first > 614)
                        {
                            std::cout << FG_RED;
                        }
                        else if (element.first > 589)
                        {
                            std::cout << FG_ORANGE;
                        }
                        else if (element.first > 574)
                        {
                            std::cout << FG_YELLOW;
                        }
                        else if (element.first > 564)
                        {
                            std::cout << FG_LIGHT_YELLOW;
                        }
                        else if (element.first > 550)
                        {
                            std::cout << FG_LIGHT_GREEN;
                        }
                        else if (element.first > 517)
                        {
                            std::cout << FG_GREEN;
                        }
                        else if (element.first > 476)
                        {
                            std::cout << FG_CYAN;
                        }
                        else if (element.first > 400)
                        {
                            std::cout << FG_LIGHT_BLUE;
                        }
                        else if (element.first > 321)
                        {
                            std::cout << FG_BLUE;
                        }		
                        else if (element.first > 287)
                        {
                            std::cout << FG_BLUE;
                        }		
                    }
     
                    std::ostringstream os;
                    os << std::string(round(((ypf_range) - distmin)*chart_x_quant) - 1, '*').c_str() << 'Y' << FG_DEFAULT;
                    os << std::string(round(((integrate_range - ypf_range) - distmin)*chart_x_quant) - 1, ' ').c_str() << '*' << FG_DEFAULT;
                    std::cout << os.str() << std::endl;
                    
                    integrate_range = 0.0;
                    ypf_range = 0.0;
                }
                else
                {

                }
            }
    
        }
        std::cout << "Total PAR : " <<  total_par << std::endl;	
        std::cout << std::endl;	
    }
    else
    {
        std::cout << "Plot NULL spectra." << std::endl;
    }
        
}
