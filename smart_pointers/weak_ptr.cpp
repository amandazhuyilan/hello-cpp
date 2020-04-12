#include <iostream>
#include <memory>

class PrintInt {
	std::weak_ptr<int> m_value_ptr;
public:
	void SetValue(std::weak_ptr<int> p) {
		m_value_ptr = p;
	}

	void Print() {
		if (m_value_ptr.expired()) {
			std::cout << "shared pointer expired! " << std::endl;
			return 0;
		}
		std::shared_ptr<int> sp = m_value_ptr.lock();
		std::cout << *sp << std::endl;
	}
};

int main() {
	std::shared_ptr<int> int_shared_p (new int (10));
	PrintInt pi_1;
	pi_1.SetValue(int_shared_p);
	
	int_shared_p = nullptr;
	pi_1.Print();
	return 0;
}
