#include <iostream>

class Integer {
	int *m_value;
public:
	Integer() {
		m_value = new int(0);
	}
	Integer(int value) {
		m_value = new int (value);
	}

	// copy constructor
	Integer(const Integer & obj) {
		std::cout << "Integer(const Integer &obj)" << std::endl;
		m_value = new int (*obj.m_value);
	}
	// move constructor
	Integer(Integer &&obj) {
		std::cout << "Integer(Integer &&obj)" << std::endl;
		m_value = obj.m_value;
		obj.m_value = nullptr;	
	}
	~Integer() {
		delete m_value;
	}

	void SetValue(int value) {
		*m_value = value;
	}

	int GetValue() const {
		return *m_value;
	}

};


Integer Add(const Integer &a, const Integer &b) {
	Integer temp;
	temp.SetValue(a.GetValue() + b.GetValue());
	return temp;
}	

int main() {
	Integer i1(2), i2(3);
	Integer i3(std::move(i1));

//	i1.SetValue(Add(i1, i2).GetValue());
//	std::cout << "new value of i1 is: " << i1.GetValue() << std::endl;
	return 0;
}

