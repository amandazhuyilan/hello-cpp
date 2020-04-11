#include <iostream>
#include <memory>   // used for smart-pointer related calls

class Integer {
	int *m_value;
public:
	Integer() {
		std::cout << "Integer()" << std::endl;
		m_value = new int(0);
	}
	Integer(int value) {
		std::cout << "Integer(int)" << std::endl;
		m_value = new int (value);
	}
	~Integer() {
		std::cout << "~Integer()" << std::endl;
		delete m_value;
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

	// overloading operator +
	Integer operator +(const Integer & obj) const {
		Integer temp;
		*temp.m_value = *(this->m_value) + *obj.m_value;
		return temp;
	} 

	// overloading operator pre-increment ++x
	// more efficient than post-increment because post-increment needs to create a temporal object.
	Integer & operator ++ () {
		++(*m_value);
		return (*this);
	}

	// overloading operator post-increment x++
	// original object is returned first then the value is incremented
	Integer operator ++ (int) {
		Integer temp(*this);
		++(*m_value);
		return temp;
	}

	// overloading assignment operator
	Integer & operator = (const Integer & obj){
		// check for self-assignment
		if (this != &obj) {
			delete m_value;
			m_value = new int (*obj.m_value);
		}
		return *this;
	}

	// overloading move assignment operator
	Integer & operator = (Integer &&  obj ){
		if (this != &obj) {
			delete m_value;
			m_value = obj.m_value;
			obj.m_value = nullptr;
		}
		std::cout << "using move assignment operator" << std::endl;
		return *this;
	}	

	// overloading function call operator - to just print value
	Integer & operator ()() const {
		std::cout << *(m_value) << std::endl;
	}

	void SetValue(int value) {
		*m_value = value;
	}

	int GetValue() const {
		return *m_value;
	}

};

// smart pointer implementation for Integer class obj
class IntPtr {
	Integer *m_ptr;

public:
	IntPtr(Integer *p):m_ptr(p) {
	}

	~IntPtr(){
		delete m_ptr;
	}

	Integer * operator ->() const {
		return m_ptr;
	}

	Integer & operator *() const {
		return *m_ptr;
	}
};

// overloading insertion operation as global function
std::ostream & operator << (std::ostream & out, const Integer & obj){
	out << obj.GetValue();
	return out;
	}

std::istream & operator >> (std::istream & input, Integer & obj) {
		int x;
		input >> x;
		obj.SetValue(x);
		return input;
	}

Integer Add(const Integer &a, const Integer &b) {
	Integer temp;
	temp.SetValue(a.GetValue() + b.GetValue());
	return temp;
}	

void print_unique_ptr(std::unique_ptr<Integer> p) {
	std::cout << "value of unique ptr: " << *p << std::endl;
}

void print_shared_ptr(std::shared_ptr<Integer> p) {
	std::cout << "value of shared ptr: " << *p << std::endl;
}

void CreateInteger() {
	// Testing the above smart pointer class that we created with IntPtr
	IntPtr p_int_ptr = new Integer;
	// using unique pointers - cannot create copies with unique pointers. Use when do not want to share underlying resources.
	// unique_ptr's copy constructor is a deleted function.
	std::unique_ptr<Integer> p_unique_ptr(new Integer);
	(*p_unique_ptr).SetValue(100);
	// when need to pass unique_ptrs, use std::move
	// note that original unique_ptr should not be used after moved
	print_unique_ptr(std::move(p_unique_ptr));	

	// shared_ptr
	// used when need to share resources - has a reference counter
	std::shared_ptr<Integer> p_shared_ptr(new Integer);
	(*p_shared_ptr).SetValue(200);
	print_shared_ptr(p_shared_ptr); // this is okay
}	

int main() {
	Integer i1(2), i2(3);
	/*
	Integer i3(std::move(i1));

	// test overloaded operators
	Integer sum = i3 + i2;
	std::cout << "Result of overloaded operator +: " << sum.GetValue() << std::endl;
	sum++;
	std::cout << "Pre-increment overload: " << sum.GetValue() << std::endl;
	++sum;
	std::cout << "Post-increment overload: " << sum.GetValue() << std::endl;
	i2 = i2;
	i2 = sum;
	std::cout << "Assignment operator overloaded: " << i2.GetValue() << std::endl; 
	std::cout << "Testing overloaded insertion operator: " <<sum << std::endl;
	
	std::cout << "Testing overwritting >> insertion operator - input int : " << std::endl;
	
	Integer i4;
	std::cin >> i4;
	std::cout << i4 << std::endl;
	
	std::cout << "Testing overwritting function call operator: ";
	i4();
	*/
	
	// testing smart pointer related functions below
	CreateInteger();
	return 0;
}

