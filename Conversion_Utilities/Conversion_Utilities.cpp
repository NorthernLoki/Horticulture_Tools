#include "Conversion_Utilities.h"

/*
	To test the library, include "Conversion_Utilities.h" from an application project
	and call Conversion_UtilitiesTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;


void test_routine()
{
	
	ounce my_ounce = 24.5;
	amu my_amu(my_ounce);
	carat my_carat = (carat)my_amu;
	dram my_dram = (dram)my_carat;
	grain my_grain(my_dram);
	gram my_gram(my_grain);
	pound my_pound(my_gram);
	ton my_ton(my_pound);
	tonne my_tonne(my_ton);
	troy_ounce my_troy(my_tonne);
	dalton my_dalton(my_troy);
	ounce my_ounce2(my_dalton);
	
	std::cout << "ounce: " << my_ounce << std::endl;
	std::cout << "amu: " << my_amu << std::endl;
	std::cout << "carat: " << my_carat << std::endl;
	std::cout << "dram: " << my_dram << std::endl;
	std::cout << "grain: " << my_grain << std::endl;
	std::cout << "gram: " << my_gram << std::endl;
	std::cout << "pound: " << my_pound << std::endl;
	std::cout << "ton: " << my_ton << std::endl;
	std::cout << "tonne: " << my_tonne << std::endl;
	std::cout << "troy: " << my_troy << std::endl;
	std::cout << "dalton: " << my_dalton << std::endl;
	std::cout << "ounce: " << my_ounce2 << std::endl;
	

	/* Try some math operations. */
	pound mass_math(1.0);
	mass_math += amu(1.0);
	mass_math += my_carat;
	mass_math -= my_dram;
	mass_math *= my_grain;
	mass_math /= my_gram;
	mass_math += pound(1.0);
	mass_math -= my_ton;
	mass_math += my_tonne;
	mass_math = mass_math / my_troy;
	mass_math = mass_math * my_dalton;
	
	/* Should be ~= 32 oz. */
	std::cout << "Total weight (ounces): " << (ounce)mass_math << std::endl;
	
	
	/* Create example units initialized in a variety of ways */
	atmosphere my_atm(1.01);
	bar my_bar = (bar) my_atm;
	kilogram_meter my_kgm2(my_bar);
	mmHg my_mmHg = (mmHg)my_kgm2;
	kPa my_kPa(my_mmHg);
	psi my_psi(my_kPa);
	psf my_psf(my_psi);
	torr my_torr(my_psf);
	
	std::cout << "atmosphere: " << my_atm << std::endl;
	std::cout << "bar: " << my_bar << std::endl;
	std::cout << "kilogram_meter: " << my_kgm2 << std::endl;
	std::cout << "mmHg: " << my_mmHg << std::endl;
	std::cout << "kPa: " << my_kPa << std::endl;
	std::cout << "psi: " << my_psi << std::endl;
	std::cout << "psf: " << my_psf << std::endl;
	std::cout << "torr: " << my_torr << std::endl;
	std::cout << "atmosphere: " << (atmosphere)my_torr << std::endl;
	
	mmHg pressure_math = 767.6;
	pressure_math += my_atm;
	pressure_math += my_bar;
	pressure_math += my_kgm2;
	pressure_math += my_mmHg;
	pressure_math *= my_kPa;
	pressure_math /= my_psi;
	pressure_math -= my_psf;
	pressure_math += my_psf;
	
	/* Should be ~= 5.05 atm */
	std::cout << "Total atmospheres (atm): " << (atmosphere)pressure_math << std::endl;
	
	cubic_meter this_m3 = 3.5;
	cubic_yard this_yd3(this_m3);
	fluid_dram this_dram = (fluid_dram) this_yd3;
	US_fluid_ounce this_usoz(this_dram);
	UK_fluid_ounce this_ukoz(this_usoz);
	US_fluid_gallon this_usgal = (US_fluid_gallon) this_ukoz;
	UK_fluid_gallon this_ukgal = (UK_fluid_gallon) this_usgal;
	liter this_liter(this_usgal);
	dry_pint this_pint(this_liter);
	dry_quart this_quart(this_pint);
	barrel this_barrel(this_quart);
	US_bushel this_US_bushel(this_barrel);
	UK_bushel this_UK_bushel(this_US_bushel);
	peck this_peck(this_UK_bushel);
	
	std::cout << "cubic_meter: " << this_m3 << std::endl;
	std::cout << "cubic_yard: " << this_yd3 << std::endl;
	std::cout << "fluid_dram: " << this_dram << std::endl;
	std::cout << "US_fluid_ounce: " << this_usoz << std::endl;
	std::cout << "UK_fluid_ounce: " << this_ukoz << std::endl;
	std::cout << "US_fluid_gallon: " << this_usgal << std::endl;
	std::cout << "UK_fluid_gallon: " << this_ukgal << std::endl;
	std::cout << "liter: " << this_liter << std::endl;
	std::cout << "dry_pint: " << this_pint << std::endl;
	std::cout << "dry_quart: " << this_quart << std::endl;
	std::cout << "barrel: " << this_barrel << std::endl;
	std::cout << "US_bushel: " << this_US_bushel << std::endl;
	std::cout << "UK_bushel: " << this_UK_bushel << std::endl;
	std::cout << "peck: " << this_peck << std::endl;	
	
	liter added_volumes = 0.0;
	added_volumes += this_m3;
	added_volumes += this_yd3;
	added_volumes += this_dram;
	added_volumes += this_usoz;
	added_volumes += this_usoz;
	added_volumes += this_ukoz;
	added_volumes += this_usgal;
	added_volumes += this_ukgal;
	added_volumes += this_liter;
	added_volumes += this_pint;
	added_volumes -= this_quart;
	added_volumes *= this_barrel;
	added_volumes /= (barrel)(this_barrel * 2.0);
	added_volumes += this_peck;
	
	/* Should be ~= 19.25 m^3 */
	std::cout << "Total volume (m^3): " << (cubic_meter)added_volumes << std::endl;
	
	watt this_test = 1000.0;
	btu this_btus = 5.0;
	this_btus = this_test;
	this_test = this_btus;
	watt this_test2 = 5000.0;
	this_test2 = (this_test / this_test2);
	btu this_btus2(245.6);
	btu this_btus3(this_test);
	
	std::cout << "test: " << this_btus << std::endl;
	std::cout << "test: " << this_test2 << std::endl;
	std::cout << "test: " << this_btus2 << std::endl;
	std::cout << "test: " << this_btus3 << std::endl;
	std::cout << "test: " << watt(this_btus3) << std::endl;
}


void test_pressure_convert()
{
	{
		/* Conversion test. */
		footpound work_footpounds(1130.1);
	
		erg work_erg(work_footpounds);
		watt work_watts(work_erg);
		btu work_btu(work_watts);
		horsepower work_horsepower(work_watts);
		tons_refrigeration work_tons(work_horsepower);
	
		std::cout << "Footpound/sec: " << work_footpounds << std::endl;
		std::cout << "Ergs/sec: " << work_erg << std::endl;
		std::cout << "Watt/sec: " << work_watts << std::endl;
		std::cout << "BTU/sec: " << work_btu << std::endl;
		std::cout << "Horsepower/sec: " << work_horsepower << std::endl;
		std::cout << "Tons/sec: " << work_tons << std::endl << std::endl;
	}
	
	{
		/* Conversion test. */
		footpound work_footpounds = 5129.77;
	
		erg work_erg = (erg) work_footpounds;
		erg work_erg2 = work_erg;
		watt work_watts = (watt) work_erg;
		btu work_btu = (btu) work_watts;
		horsepower work_horsepower = (horsepower) work_watts;
		tons_refrigeration work_tons = (tons_refrigeration) work_horsepower;
	
		std::cout << "Footpound/sec: " << work_footpounds << std::endl;
		std::cout << "Ergs/sec: " << work_erg << std::endl;
		std::cout << "Watt/sec: " << work_watts << std::endl;
		std::cout << "BTU/sec: " << work_btu << std::endl;
		std::cout << "Horsepower/sec: " << work_horsepower << std::endl;
		std::cout << "Tons/sec: " << work_tons << std::endl << std::endl;
	}
	
	/* Cast test */
	watt additional_work(1000);
	
	std::cout << "Footpound/sec: " << (footpound)additional_work << std::endl;
	std::cout << "Ergs/sec: " << (erg)additional_work << std::endl;
	std::cout << "BTU/sec: " << (btu)additional_work << std::endl;
	std::cout << "Watt/sec: " << additional_work << std::endl;
	std::cout << "Horsepower/sec: " << (horsepower)additional_work << std::endl;
	std::cout << "Tons/sec: " << (tons_refrigeration)additional_work << std::endl << std::endl;
	
	{
		/* Math test. */
		footpound work_footpounds = 5129.77;
	
		erg work_erg = 13558179.48331; /* 1 ftlbs */
		watt work_watts = 135.5817948331; /* 100 ftlbs */
		btu work_btu = 1.285067283946; /* 1000 ftlbs */
		horsepower work_horsepower = 0.01818181818182; /* 10 ftlbs */
		tons_refrigeration work_tons =  0.00038552022552; /* 1 ftlbs */
		
		work_footpounds += work_erg;
		work_footpounds += work_watts;
		work_footpounds += work_btu;
		work_footpounds += work_horsepower;
		work_footpounds /= work_horsepower;
		work_footpounds *= work_watts;
		work_footpounds -= 1001.1;
		work_footpounds -= work_tons;
	
		/* Should be ~= 61405.6 ft.lbs/sec*/
		std::cout << "Footpounds: " << work_footpounds << std::endl;
	}
	
}

void test_temp_function1(celcius temperature)
{
	std::cout << "test_temp_function1 Temperature celcius: " << temperature << std::endl;
	
}

void test_temp_function2(kelvin temperature)
{
	std::cout << "test_temp_function2 Temperature Kelvin: " << temperature << std::endl;
	
}


void test_temp_convert()
{
	//Initialize some temperature variables
	celcius cel_temp = 32.0;
	celcius cel_temp2(31.0);
	kelvin kel_temp(280);
	farenheit far_temp(80);
	kelvin kel_temp2(cel_temp);
	farenheit far_temp2(kel_temp);

	//Print the value in celcius with alternatives
	std::cout << "Temperature celcius(32)" << cel_temp << std::endl;
	std::cout << "Temperature celcius(32): " << cel_temp.degrees_celcius << std::endl;
	std::cout << "Temperature celcius(32): " << cel_temp() << std::endl;
	std::cout << "Temperature F to c: " << (celcius) far_temp << std::endl;
	std::cout << "Temperature K to c: " << (celcius) kel_temp << std::endl;
	std::cout << "Temperature F to K: " << (kelvin) far_temp << std::endl;
	std::cout << "Temperature c to K: " << (kelvin) cel_temp << std::endl;
	std::cout << "Temperature c to F: " << (farenheit) cel_temp << std::endl;
	std::cout << "Temperature kelvin to F: " << (farenheit) kel_temp << std::endl;
	
	printf("Temperature: %8.3f\n", cel_temp());

	//Print the celcius value in kelvin
	std::cout << "Temperature c to K" << (kelvin)cel_temp << std::endl;

	//Print the celcius value in farenheit
	std::cout << "Temperature c to F" << (farenheit)cel_temp << std::endl;

	//Do some math with different units
	celcius cel_temp3 = 32.0;
	cel_temp2 = cel_temp3 + far_temp;
	cel_temp3++;
	cel_temp += 10;
	std::cout << "Temperature celcius (33): " << cel_temp3 << std::endl;
	std::cout << "Temperature celcius (32 + 80F): " << cel_temp2 << std::endl;
	std::cout << "Temperature celcius (42):" << cel_temp << std::endl;
	std::cout << "Temperature celcius + kelvin: " << cel_temp + kel_temp << std::endl;
	
	if (cel_temp > kel_temp) std::cout << "Celcius Temperature is greater" << std::endl;
	else if (cel_temp < kel_temp) std::cout << "Kelvin Temperature is greater" << std::endl;
	else if (cel_temp == kel_temp) std::cout << "Temperatures are equivalent" << std::endl;
	
	test_temp_function1(23.0);
	test_temp_function1((celcius)23.0);
	test_temp_function1((kelvin)276.0);
	test_temp_function1((farenheit)80.0);
	test_temp_function1(celcius(23.0));
	test_temp_function1(kelvin(276.0));
	test_temp_function1(farenheit(80.0));
	
	test_temp_function2(23.0);
	test_temp_function2((celcius)23.0);
	test_temp_function2((kelvin)276.0);
	test_temp_function2((farenheit)80.0);
	test_temp_function2(celcius(23.0));
	test_temp_function2(kelvin(276.0));
	test_temp_function2(farenheit(80.0));
}





int Conversion_UtilitiesTest()
{
	test_routine();
	test_pressure_convert();
	test_temp_convert();
	
	return ++s_Test;
}