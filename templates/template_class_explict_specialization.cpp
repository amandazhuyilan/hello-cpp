// Explict Specialization for Template classes.

#include<iostream>
#include<vector>

template<typename T>
class PrettyPrinter{
	T * pData_;
public:
	PrettyPrinter(T *data): pData_(data) {};

	void Print() {
		std::cout << "{" << *pData_ << "}" << std::endl;
	}
	
	T GetData() {
		return *pData_;
	}
};

// specialize the entire class
template<>
class PrettyPrinter<char *> {
	char* pData_; 
public:
	PrettyPrinter(char* data) : pData_(data) {};
	void Print() {
		std::cout << "{" << pData_ << "}" << std::endl; 
	}

	char* GetData() {
		return pData_;
	}
};

// specialize for just one function - must be outside of the class!
template<>
void PrettyPrinter<std::vector<int>>::Print() {
	std::cout << "{";
	for (const auto &i: *pData_ ) {
		std::cout << i;
	}
	std::cout << "}" << std::endl;
}

int main() {
	int i1 = 10;
	float f1 = 12.3;
	char *c1 = "Hello world";
	std::vector<int> v1 {1, 2, 3, 4};
	PrettyPrinter<int> p1(&i1);
	p1.Print();
	PrettyPrinter<float> p2(&f1);
	p2.Print();
	PrettyPrinter<char *> p3(c1);
	p3.Print();
	PrettyPrinter<std::vector<int>> p4(&v1);
	p4.Print();
}
