#include "Math_Utilities.h"

/*
	To test the library, include "Math_Utilities.h" from an application project
	and call Math_UtilitiesTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

int Math_UtilitiesTest()
{
	test_integration_tests();
	return ++s_Test;
}

void test_integration_tests()
{
	
	/*******************/
    /* Integrate tests */
	std::pair<double, double> element;
	boost::container::flat_set<std::pair<double, double>> the_set;
	
	std::cout << "----Xdx----" << std::endl;
	element = { 4.0, 4.0 };
	the_set.insert(element);
	
	element = { 2.0, 2.0 };
	the_set.insert(element);
	
	element = { 3.0, 3.0 };
	the_set.insert(element);
	
	element = { 1.0, 1.0 };
	the_set.insert(element);
	
	element = { 0.0, 0.0 };
	the_set.insert(element);
	
	element = { 5.0, 5.0 };
	the_set.insert(element);
	
	element = { 6.0, 6.0 };
	the_set.insert(element);
	
	element = { 7.0, 7.0 };
	the_set.insert(element);
	
	element = { 8.0, 8.0 };
	the_set.insert(element);
	
	element = { 9.0, 9.0 };
	the_set.insert(element);
	
	integrate integral(&the_set);
	if (integral.integral == 40.5) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;
	
	std::cout << "----X*Xdx----" << std::endl;
	the_set.clear();
	int x = 0;
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	element = { x, (x*x) };
	x++;	
	the_set.insert(element);
	integrate integral3(&the_set);
	if (integral3.integral == 244.5) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;
	
	
	std::cout << "----X*(X-3)dx----" << std::endl;
	the_set.clear();
	integral3.clear();
	x = 0;
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x - 3)) };
	x++;	
	the_set.insert(element);
	integral3(&the_set);
	if (integral3.integral == 123.0) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;
	
	
	std::cout << "----X*(X*3)dx----" << std::endl;
	the_set.clear();
	integral3.clear();
	x = 0;
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	integral3(&the_set);
	if (integral3.integral == 28.5) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;

	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	integral3(&the_set);
	if (integral3.integral == 66.0) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;

	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	element = { x, (x*(x * 3)) };
	x++;	
	the_set.insert(element);
	integral3(&the_set);
	if (integral3.integral == 733.5) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;
	
	
	std::cout << "--------" << std::endl;
	the_set.clear();
	element = { 10.0, 5.1 };
	the_set.insert(element);
	
	element = { 1.0, 10.3 };
	the_set.insert(element);
	
	element = { 5.0, 5.5 };
	the_set.insert(element);
	
	element = { 3.0, 15.0 };
	the_set.insert(element);
	
	element = { 0.0, 2.9 };
	the_set.insert(element);
	
	integrate integral2(&the_set);
	if (integral2.integral == 78.9) std::cout << "Correct." << std::endl;
	else std::cout << "Incorrect!" << std::endl;

}