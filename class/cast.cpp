#include <iostream>

class Integer {
	int * m_value;
public:
	Integer() {
		m_value = new int(0);
	}
	// parameterized constructor - called when primative type needs to be converted into user define type.
	// if `explict` is added in front of the parameterized constructor, it will not automatically convert primative type to user defined type.
	Integer(int i) {
		m_value = new int(i);
	}
	~Integer() {
		delete m_value;
	}
	// convert user type to primative type
	// `explict` can be ignored if implict type convertion is not desired
	explicit operator int() {
		return *m_value;
	}
};

int main() {
	int a = 5, b = 2;
	const int c = 5;
	// c-style casting does not check for validity or qualifiers
	float f1 = (float)(c) / b;	// buggy c-style casting
	float f2 = static_cast<float> (a) / 2;
	std::cout << "static_cast result: " << f2 << std::endl;
	
	// reinterpret_cast allows casting between different pointer type objects
	char *p2 = reinterpret_cast<char *>(&a);
	std::cout << "reinterpret_cast result: " << *p2 << std::endl;
	
	const int x = 1;
	int *int_ptr = const_cast<int *>(&x);
	std::cout << "const_cast result: " << *int_ptr << std::endl;


	// primative -> user define type convertions
	Integer i1{ 5 };

	// user -> primative type
	// int d = i1;  // this is valid if the `explicit` keyboard is not added for the typer convertion operator
	int d = static_cast<int>(i1);
	std::cout << "user->primative type : " << d << std::endl;
	return 0;
}
