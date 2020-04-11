#include <iostream>

class Float {
	float *m_value;
public:
	Float() {
		m_value = new float(0.0);
	}
	Float(float value) {
		m_value = new float(value);
	}
	~Float() {
		delete m_value;
	}
	// copy constructor
	Float(const Float & obj) {
		m_value = new float (*obj.m_value);
	}

	// move constructor
	Float(Float && obj) {
		m_value = obj.m_value;
		obj.m_value = nullptr;
	}

	// copy assignment operator overload
	Float & operator = (const Float & obj) {
		if (this != &obj) {
			delete m_value;
			m_value = new float (*obj.m_value);
		}
		return (*this);
	}

	// move assignment operator overload
	Float & operator = (Float && obj) {
		if (this != &obj) {
			delete m_value;
			m_value = obj.m_value;
		}
		return (*this);
	}

	// post-increment operator overload
	Float operator ++ (int) {
		Float temp(*m_value);
		++(*m_value);
		return temp;
	}

	// pre-increment operator overload
	Float & operator ++ () {
		++(*m_value);
		return (*this);
	}

	float GetValue() {
		return *m_value;
	}

	void SetValue(float value) {
		*m_value = value;
	}
};

// overloading stream operators
std::ostream & operator << (std::ostream & output, Float & obj) {
	output << obj.GetValue();
	return output;
}

std::istream & operator >> (std::istream & input, Float & obj) {
	float x;
	input >> x;
	obj.SetValue(x);
	return input; 
} 


int main() {
	Float f1(1.1), f2(2.2), f3(3.3);
	Float f4(std::move(f1));
	std::cout << "Before assignment: " << f2.GetValue() << std::endl;
	f2 = f3;
	std::cout << "After assignment: " << f2.GetValue() << std::endl;
	
	f3++;
	std::cout << "f3++ = " << f3.GetValue() << std::endl;
	++f3;
	std::cout << "++f3 = " << f3.GetValue() << std::endl;

	std::cout << "Testing overloading of stream operator, input a float: " << std::endl;

	std::cin >> f2;
	std::cout << f2 << std::endl;
	return 0;
}
