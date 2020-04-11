## hello-cpp 
This repo contains my study notes for C++.

### C++ Build Process - from source code to executable
- Preprocessor
 
expands the source code to include any files specified with the `#include` commands, and to expand any macro, specified with the `#define` declarations.

- Compiler

generates assembly code version of source files (`*.s` files)

- Assembler

converts the assembly code into binary _object-code_ files (`*.o` files)

- Linker

merges the object-code files with the code implementing library functions and generates the final executable code file.


### Reference & Pointer
- Reference
 - No storage required, address of referent is the same address of the referemce
 - Always needs to be initialized (`int &ref = x;` instead of `int &ref;` and `int &ref = 10;`)
 - Cannot be `nullptr`
 - Bound to its referent throughtout its lifetime, without changing the referent
 - No need to dereference to access value
 - When reference is set as `const`, it can be assigned to literal values (`const int &ref = 10;`)


- Pointer
 - Needs storage
 - Initialization need not be necessary.
 - Can be a `nullptr`
 - Can point to other variables
 - Need to dereference operator to access value in the address

#### When to use reference and when to use pointers?
When using pointer as function input arg, one would always have to check if the input is a `nullptr`. However if using a reference as input arg, since it cannot be a `nullptr`, we would not need to check for null.

You do not want to use a reference when you want to indicate some kind of ownership, references cannot be stored in collections and cannot be iterate through like pointers can.

### `auto`
- Will always need an initializer, can be an expression (`auto sum = x + y;` - if the types in the expression is different, the `auto` variable will be the largest type in the expression.
- `auto` will drop the `const` type when assigned to a `const` typed variable. Can be re-`const`ed by `const auto`.

### range-based `for`
```
for (const auto x: arr) {
	std::cout << x;
}
```

### Function Overloading
- Two or more functions declared with the same name, different implementation for the same behavior, where the correct implementation is based on the arguments. Function overloading is also an example for static polymorphism, where the behavior that has to be invoked is known by the compiler at compile time. The main benefit is convenience to for the user of the functions.

#### Name Mangling Process
- Generate unique names by the compiler for the functions.
- Allows linkers to link the call of the correct overloaded functions.
- Name mangling algorithms varies from compiler to compiler.

### `inline` & macros
- inline function is a function that is marked with a `inline` keyword, in the header file. `inline` is used to request the compiler to replace the call of the function to the body of the function. The overhead of the function call, including stack memory for arguments, and saving the return address of the program, is avoided.

Some of the disadvantages using `macro`s include:
- Uses text substitution, difficult to use for functions with multiple lines of code, and cannot be used for member functions of a class.

### function pointers;

syntax:
```
float average(float a, float b) {
	float result = (a + b) / 2;
	return result;
}

int main() {
	float (*fptr)(float, float);
}
```

### Memory Management
- Stack - used for local variables. Memory is allocated at runtime.
- Data section - allocated for static and global data.
- Heap - used for allocating memory at runtime. Allocations on the heap is managed by the programmer.

### Dynamic Memory Allocation in `C`
 - `malloc(size_of_memory) -> ptr_to_allocated_memory` - allocates raw memory on the heap, does not initialize. `malloc` returns a void pointer that would need to be type casted to the source type. Returns `NULL` if allocation unsuccessful.
 - `calloc()` - similar to `malloc`, but initailized the allocated memory to zero. Returns `NULL` if allocation unsuccessful.
 - `realloc()` - allocates larger chuncks of memory for an existing allocation. Returns `NULL` if allocation unsuccessful.
 - `free()` - deallocates/releases the memory that was allocated from the above functions.

#### Heap memory allocation in `C`

```
#include <stdio.h>
#include <stdlib.h>

int main() {
	int *p = malloc(sizeof(int));	// malloc will return a void type pointer by default, then it will be casted into the type of pointer as requested.
	// to type cast the pointer in C++, do the following:
	// int *p = (*int)malloc(sizeof(int));

	// check if memory was allocated correctly
	if (p == NULL) {
		printf("Failed to allocate memory!\n");
		return -1;
	}
	*p = 5;		// malloc does not initialize memory
	printf("%d", *p);
	free(p);
	p = NULL; 	// assign p to NULL or else it would be left as a dangling pointer

	return 0;
}
```

#### Dynamic Memory Allocation in C++
Memory is allocated with operator `new` and deallocated with operator `delete`.
```
<type>*<variable> = new<type> (optional_args);
delete <variable>;
```
```
int *p = new int(10);
delete p;
```

Arrays:
```
<type> *<variable> = new <type> [size];
delete[size] <variable>;

int *new_arr = new int[10];
delete  []new_arr;
```

2D Arrays:
```
void NewMatrix() {
        int *row1_ptr = new int[5];
        int *row2_ptr = new int[5];

        int **matrix_ptr = new int *[2];
        matrix_ptr[0] = row1_ptr;
        matrix_ptr[1] = row2_ptr;
	
	// deallocate in the order that the pointers were initialized.
	delete []row1_ptr;
	delete []row2_ptr;
	delete []matrix_ptr;

}
```

### Object Oriented Programming

#### Inheritance 
 - Represents the hierachy of classes,
 - The classes are related through a 'is a' relationship, for example: 'A `donkey()` is an `Animal()`', where the relation is due to the same behavior of the classes.

#### Polymorphism
 - Represents common behavior of different objects and different implementation.
 - Example: a common behavior `move` - `car.move()`, `dog.move()` and `human.move()` has different implementation.
 - Implemented through function overloading, templates and virtual functions.

### Classes & Struct
#### `pragma once`
A header guard put at the top of a header file to prevent redeclaration errors when a header file is included in the source files more than once.

- `auto` is not allowed when declaring non-static data members

```
class Car {
	private:
		float speed{0};
		int num_of_passengers{4};
		auto vin;	// not allowed! 
		static const auto vin;	// allowed
}
```

#### Initializer List
```cpp
class Numbers {
	const int value1;
	int &value2;
private:
	Numbers (int value1, int value2):value1(value1):value2(value2)
}
```
Initializer list needs to be used when:
 - initializing class member of type non-static `const` and references
 - when member objects do not have a default constructor
 - initializing base class members:
	```cpp

	class A {
		int a;
	public A(int );
	};

	A::A(int arg) {
		a = arg;
	}

	class B:A {
		int b;
	public B(int );
	};

	B::B(int x):A(x) {
		std::cout << "initializer list is used here!" << std::endl;
	}
	};
```
 - performance issues - we can save some memory if temp objects need to be created and freed using the constructor body function.


#### `Struct`
Almost the same as a class, except that the access to the member variables are set as `public` by default.
```cpp
struct Point {
	int x;
	int y;
}
```

#### `this` pointer
 - Contains the address of the object that invokes the member function. It is a constant value, it cannot be assigned.
 - Provided as a keyword that is meaningful only in member functions, is helpful for the compiler when using `this` pointer to distinguish the function member variable and local variable.
 - Used to refer to the class object within the class functions, via dereferencing the `this` pointer: `*this`

- `const` member functions
 - Member functions that do not modify the state of the object should be qualified with the `const` keyword. 

 in `car.h`:

```cpp
void Car::Dashboard() const;
```

 in `car.cpp`:
```cpp
void Car::Dashboard() const {
        std::cout << "Speed: " << this->speed << std::endl;
        std::cout << "Fuel: " << this->fuel << std::endl;
        std::cout << "Passengers: " << this->passengers << std::endl;
}
```

#### Static Member Variables
 - Belongs to the class but not the object, there is only one copy of the static member variable, and is shared between objects.
 - Cannot be initialized inside the class, it is defined outside the class for initailization.
 - Cannot be accessed via `this` since it is not related to the object but the class.

 - example: `static int num_of_cars;`	// used to describe how many car objects were created.

### Shallow and deep copies

```cpp
int *ptr = new int(10);
int *shallow_copy_ptr = ptr;
int *deep_copy_ptr = new int(*ptr); 
```

A copy of the object is created when:
 - the copy constructor is invoked like `Car car2(car1)`
 - an object is passed into a function by value
 - a function returns an object by value
 - an object is assigned to another object

User defined copy constructor:
```cpp
class Integer {
	int *int_ptr;
public:
	Integer();
	Integer(int value) {
		this->value = value;
	};
	Integer(const Integer &obj) {
		int_ptr = new int (*obj.int_ptr);
	};

}
```
User should define their own copy constructor when a class contains a pointer as a member variable. Without user-defined copy constructor, the compiler generated copy constructor will perform a shallow copy that will lead to undefined results.

_Rule of Three_: All should be defined if a user implements any of them:
 - Destructor -> free resource
 - Copy Constructor -> perform deep copy
 - Copy Assignment operator -> perform deep copy

### Delegate Constructors
```cpp
Car::Car():Car(0) {	// This default constructor will be called last
}

Car::Car(float fuel_amount):Car(fuel_amount, 0) {	// This parameterized constructor will be called second
}


Car::Car(float fuel, int passeneger) {	// <- This delegated constructor will be called first
        total_car_num += 1;
        std::cout << "Car(float, int)" << std::endl;
        this->speed = 0.0;
        this->fuel = fuel;
        this->passengers = passengers;
}
```
### Function keywords `default` & `delete` (C++ 11)
- `default` can be used for functions that can be synthesized by the compiler (copy constrctor, destructor and assignment operator), it will create a default function for you. Ex. `Integer(const & Integer) = default`
- `delete` tells the compiler not to synthesize the function, for example, `Integer(const & Integer) = delete` will tell the compiler to not to synthesize a copy constructor.

```cpp
void SetValue(int m) {
	this->m-value = m;
} 

void SetValue(float) = delete; //<-- this will forbid anyone who calls SetValue with a float value.
```
## L-value & R-values & R-value references & L-value references
- L-value:
 - Has a name
 - All variables are L-values, and can be assigned with values.
 - Persists beyond the expression
 - Functions that return by reference return L-values
 
- R-value:
 - Does not have a name
 - Has a temporarily value, cannot be assigned with a value.
 - Does not persist beyond the expression
 - Functions that return by value return R-values

- R-value Reference:
 - Introduced in C++ to implement `move` sementics. Its purpose is to detect temporaries in expressions, so that we can write overload functions based on L-value and R-value references.
 - It is a reference to a temporary value and represents a temporary, cannot bind to L-values
 - Created with `&&` operator
 - Ex. `int && r1 = 10;`, `int && r2 = Add(1, 2);`, `int && r3 = 7+2;`

- L-value References
 - Can bind to a temporary if the reference is a constant. Ex: `const int &ref = 3` is allowed.

### Move semantics
In a move semantic, we allocate a new object with a pointer that points to the same address of the object to be copied. The pointer in the original object will be set as `nullptr`.

`move` semantics are prefered over `copy` for operations that generates temporaries, especially when the class has pointers.

The compiler will generate move operations only when the user has not implemented copy semantics and a destructor.

#### `std::move()`
 - It forces the compiler to perform a `move()` instead of a `copy()` on L-values.
 - The object that was `move()`d will no longer be accessible.

### Operator Overloading
- Custom implementation for primitive operators, can be implemented as global (takes the same number of arguments as the original operands, and will accept primative types as inputs) or member functions (one argument will be passed as an implicit argument through this pointer).

- If an operator is overloaded as a member, it must be member of the operand located left of the operator. For example when overloading `+`, in `a + b`, the `+` operator must be overloaded in a's class or as a global function.
 
- Binary operators takes two arguments, `+` for example, takes two arguments , left and right hand side of the operator.
- Unary operators takes one arugument, `++` used in increment for example, 
```cpp
	<return_type> operator <#> (<arguments>)

	Integer operator+ (const Integer &, const Integer &) // global
	Integer Integer::operator +(const Integer &) // member
```

#### Post-increment `x++` & Pre-increment `++x`
Post-increment returns `x` then adds one to the value, when overloading this operator, when considering memory usage, post-increment can less efficient than pre-increment, as we would need to store and return the original object as a temp. To distinguish between the two `++` operators, a dummy `int` parameter is added into the post-increment operator.
 
```cpp
	Integer operator ++(int) {
		Integer temp(*this);
		++(*m_value);
		return temp;
	}
```
However, in use cases such as walking a string with `char` pointer, post-increment should be used instead, as the first character would be lost if using a pre-increment.


Pre-increment adds one to the value and returns it as is:
``` cpp
	Integer & operator ++() {
		++(*m_value);
		return *this;
	}
```

#### Assignment Operators 
```cpp
	// overload assignment operator
	Integer & operator = (const Integer & obj) {
		// check for self-assignment
		if (this != &obj) {
			delete m_value;
			m_value = new int (*obj.m_value);
			return (*this);	
		}
	}

	// overload move operator
	Integer & operator = (Integer && obj) {
		// check for self-assignment
		if (this != &obj) {
			delete m_value;
			m_value = obj.m_value;
			obj.m_value = nullptr;
		}
	}
```
#### Insertion Operator `<<` & `>>`
-  Must be implemented as a global function as it takes `osstream` type as input as well.

```cpp
std::ostream & operator << (std::osstream & out, Integer & obj) {
	// out not kept as const object as we are inserting contents into out.
	out << obj.GetValue();
	return out;
} 

std::istream & operator >> (std::istream & input, Integer & obj) {
	int x; 
	input >> x;
	obj.SetValue(x);
	return input;	
}	
``` 
### Type Casting
 - Refer to `cast.cpp` for details.
```cpp
	int a = 5, b = 2;
        const int c = 5;
	// c-style casting does not check for validity or qualifiers
        float f1 = (float)(c) / b;      // buggy c-style casting
        float f2 = static_cast<float> (a) / 2;
        std::cout << "static_cast result: " << f2 << std::endl; 

        // reinterpret_cast allows casting between different pointer type ob    jects
        char *p2 = reinterpret_cast<char *>(&a);
        std::cout << "reinterpret_cast result: " << *p2 << std::endl;
 
        const int x = 1;
        int *int_ptr = const_cast<int *>(&x);
        std::cout << "const_cast result: " << *int_ptr << std::endl;
```
 - Parameterized constructors are used by the compiler implictly when converting primative types to user defined types. If this is not desired, add `explict` keyword in front of the class constructor.


### Initialization vs. Assignment

##### Initialization
`Integer i1 (5);`:
 -> `Integer(int)`
 -> `~Integer()`


##### Assignment
`Integer i1; i1 = 5;`
 -> `Integer()`
 -> `Integer(int)`
 -> `operator=(Intger&& int)`
 -> `~Integer()` - destructor for temp object that is created for the assignment operation
-> `~Integer()`

 The overhead of the assignment can be avoided by using the initializer list to initialize the members of the class.





