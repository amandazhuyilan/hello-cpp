#include <iostream>

template<typename T, int size>
class Stack {
	T buffer_[size];
	int top_ = -1;

public:
	Stack() = default;
	// copy constructor
	Stack(const Stack &obj) {
		top_ = obj.top_;
	
		for (int i = 0; i <= top_; ++i) {
			buffer_[i] = obj.buffer_[i];
		}
	}

	void Push(T elem) {
		buffer_[++top_] = elem;
	}	

	void Pop () {
		--top_;
	}
		
	int Top() const {
		return buffer_[top_];
	}

	bool isEmpty() {
		return top_ == -1; 
	}

	static Stack Create();
};


// implementation of template class functions outside class definition.
template<typename T, int size>
Stack<T, size> Stack<T, size>::Create() {
	return Stack<T, size>();
}

int main() {
	Stack<int, 100> stack1;
	stack1.Push(1);
	stack1.Push(2);
	stack1.Push(3);

	while (!stack1.isEmpty()) {
		std::cout << stack1.Top() << ", ";
		stack1.Pop();
	}
	// test copy constructor
	auto stack2(stack1); 
		
}
