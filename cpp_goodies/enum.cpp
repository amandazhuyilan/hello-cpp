#include <iostream>

enum class Color{Red, Blue, Green};
void FillColor(Color color) {
	if (color == Color::Red) {
		std::cout << "RED" << std::endl;
	}

	if (color == Color::Blue) {
		std::cout << "BLUE" << std::endl;
	}

	if (color == Color::Green) {
		std::cout << "GREEN" << std::endl;
	}
}

int main() {
	Color c = Color::Red;
	FillColor(c);
	FillColor(Color::Blue);
	FillColor(static_cast<Color>(2));
	
}
