#include <iostream>
#include "car.h"

int Car::total_car_num = 0;

Car::Car():Car(0) {
	std::cout << "Car()" << std::endl;
}

Car::Car(float fuel_amount):Car(fuel_amount, 0) {
	std::cout << "Car(float)" << std::endl;
}
Car::Car(float fuel, int passeneger) {
	total_car_num += 1;
	std::cout << "Car(float, int)" << std::endl;
	this->speed = 0.0;
	this->fuel = fuel;
	this->passengers = passengers;
}

Car::~Car() {
	total_car_num -= 1;
}

void Car::FillFuel(float amount) {
	this->fuel = this->fuel + amount;
}

void Car::Accelerate() {
	this->speed += 5.0f;
	this->fuel -= 0.5f;
}

void Car::Brake() {
	this->speed -= 5.0f;
}

void Car::Dashboard() const {
	std::cout << "Speed: " << this->speed << std::endl;
	std::cout << "Fuel: " << this->fuel << std::endl;
	std::cout << "Passengers: " << this->passengers << std::endl;
	std::cout << "Total number of cars: " << this->total_car_num << std::endl;
}

void Car::ShowNum() {
	std::cout << total_car_num << std::endl;
}
