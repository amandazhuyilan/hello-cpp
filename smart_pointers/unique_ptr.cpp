#include <iostream>
#include <memory>

class Integer {
	int *m_value;
public:
	Integer() {
		m_value = new int (0);
	}

	Integer(int value) {
		m_value = new int (value);
	}

	~Integer() {
		delete m_value;
	}

	int GetValue() {
		return *m_value;	
	}
};

void Display_with_pointer(Integer *p) {
	std::cout << "unique ptr value via pointer: " << p->GetValue() << std::endl;
}

void Display_with_ref(std::unique_ptr<Integer> &p) {
	std::cout << "unique ptr value via reference: " << p->GetValue() << std::endl;
}

int main() {
	std::unique_ptr<Integer> unique_p(new Integer(100));
	if (unique_p == nullptr) {
		unique_p.reset(new Integer(100));
	}
	Display_with_pointer(unique_p.get());
	Display_with_ref(unique_p);

	std::unique_ptr<int> int_ptr(new int(11));
	std::cout << "access int ptr: " << *(int_ptr.get()) << std::endl;

	int_ptr.reset(new int (22));
	std::cout << "updated int ptr: " << *(int_ptr.get()) << std::endl;
	return 0;
}
