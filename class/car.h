#pragma once

class Car {
private:
	float speed = 0;
	float fuel = 0;
	int passengers = 0;
	static int total_car_num;
public:
	Car();
	~Car();
	void Accelerate();
	void Brake();
	void FillFuel(float amount);
	void Dashboard() const;	// prints all member variables, does not modify the state of the object
	static void ShowNum();
};
