#include <iostream>
#include "car.h"

int main() {
	Car car1 = Car();
	
	car1.FillFuel(100.0);
	car1.Accelerate();
	car1.Accelerate();
	car1.Brake();

	car1.Dashboard();
	
	Car car2 = Car();
	Car car3 = Car();

	std::cout << "After init 2 more cars:" << std::endl;
	car1.Dashboard();

	
	std::cout << "Printing total_car_num: " << std::endl;
	Car::ShowNum();
	return 0;
}
