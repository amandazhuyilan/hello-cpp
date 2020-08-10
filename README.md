# hello-cpp 
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

#### RRTI (Run-Time Type Information)
There are serveral ways to determine the variable type at compile/run time:
1. `typeinfo` - `typeid` operator returns information of the type as an object of the `typeinfo` class. 
```cpp
#include <typeinfo>

int main() {
	int i;
	const std::typeinfo &ti = typeid(i);
	std::cout << ti.name() << std::endl;	// will print 'int' 
}
```
- When `typeid` is used on non-polymorphic types, it will run at compile time; if used on polymorphic type, it will run at runtime. 
- "_A class that declares or inherits a virtual function is called a polymorphic class._"

2. Using `dynamic_cast` operator - it will check if the typecast can be performed or not. If can be performed it will return the typecasted pointer, otherwise return `NULL`.
``cpp
Checking *pChecking = dynamic_cast<Checking*>(pAccount);
if (pChecking != nullptr) {
	// std::cout << "cast performed successfully!" << std::endl;
	}
```

Ideally, we should avoid using `typeid` and `dynmaic_casts`, as it creates overhead at compile time:
 - when using `typeid`, during compile time, the compiler creates the type information, such as a `type_info` object, stored with the class vtable. This information will be later queried during runtime.
- `dynamic_cast` is slower than `typeid` as it will require the compiler to run through the class hierachy to determine if the typecast can be performed or not. 
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


## Smart Pointers
### `unique_ptr`
 - use `get()` to access the underlying pointer.
 - use `set()` to delete the current existing pointer and take ownership of new pointer.
 - `copy()` constructor is `delete`d in `unique_ptr`s
 - pass the smart pointer via reference or `std::move()` in cases where the unique pointer object needs to be passed around.

```cpp
#include <memory>

int main() {
	std::unique_ptr<int> unique_int_ptr{new int(10)};
	
	// use get() to access to the data that the unique_ptr points at
	int b = unique_int_ptr.get();
	
	// reset() does 2 things - if smart pointer already holds an existing pointer, the existing pointer will be deleted and the smart pointer will take ownership of the new pointer.
	unique_int_ptr.reset(new int (12));
	
}
```

### `shared_ptr`
 - `shared_ptr` is twice the size of a raw pointer, as it holds a pointer to the reference counter.
 - used for pointers which will be accessing shared resources.

### `weak_ptr`
 - a smart pointer that holds a non-owning ("weak") reference to an object managed by `shared_ptr`, is always created with a shared pointer.
```cpp
	std::shared_ptr<int> p(new int(5));
	std::weak_ptr<int> wk_p = p;
```
- `weak_ptr` models temporary ownership: when an object needs to be accessed only if it exists, and it may be deleted at any time by someone else, `weak_ptr` is used to track the object, and it is converted to `shared_ptr` to assume temporary ownership. If the original `shared_ptr` is destroyed at this time, the object's lifetime is extended until the temporary `shared_ptr` is destroyed as well. To access the original object that `shared_ptr` was pointing to, one would need to use `lock()`.


### `enums`
 - Enumerators (or symbolic constants) are internally represented as undefined integer types.
 - Can implicitly convert to an integer but not the other way round.
 - Default value starts at 0 but users can define starting value.
 - Visible in scopes that they are defined in.

```cpp
enum Color{Red, Green, Blue};
Color c = Red;
c = 1; // compiler will tell you to use static_cast to convert
int x = Green; // x will contain 1
```
Scoped `enum` with defined type:
```cpp
enum class Color : char{Red='c', Blue, Green} // Blue will be of value 'd'
char c = static_cast<char>(Color::Red); // must use static_cast
```

### `std::string`

#### Problem with c-style strings:
 - c-strings are called 'string laterals' - `const char * str = "hello world"` and a null character is appended at the end. Standard C-string functions (`strlen`, `strcp`, `strcat` etc) require the strings to be terminated with a null character to function correctly.
 - C arrays do not track their own size. You must keep up with size on your own or rely on the linear-time strlen function to determine the size of each string during runtime.
 - The null character that marks the end of a C-string requires a byte of storage in the char array. This means that a string of length 24 needs to be stored in a 25-byte char array. However, the strlen function returns the length of the string without the null character.

#### `std::string` functions
```cpp
	// declaration and assignment
	std::string my_str;
	std::string name1("mandi");
	std::string name2(name1);
	//populate the buffer with a repeated series of characters
	std::string filled(16, 'A');

	// comparison
	if (name1 != name2){
		std::cout << "name1 != name2" << std::endl;
	}
	 
	// concatation
	std::string name3 = name1 + name2;
	name1 += name2;

	// storage related functions
	name1.size(); 	// returns number of characters in the string
	name2.length(); // same as size()
	name3.clear();  // resets the string as an empty string
	name3.empty();  // returns true if string is currently empty

	// substring related functions
	name3.find('wh'); // returns the position within a string where the specified character or substring can be found.
```

### `constexpr`
 - Can be used for functions or variables, computed at compile time.
 - `constexpr` functions have to be literal types (`void`, scalar types, references etc)
 - `constexpr` functions consist of a single line, return statement. (This rule is relaxed in C++14).
 - `const` vs `constexpr`:
  - initialization of `const` variables can be deferred until runtime, `constexpr` variable must be initialized at compile time.
  - all `constexpr` variables are `const`, not the other way round,
  - Use `const` keyword for variables whose values cannot be changed, use `constexpr` for expressions that can be evaluated at compile time.

```cpp
constexpr int Max(int x, int y) {
	return x > y ? x : y;
};
int a = 1, b = 2;
int x = Max(a, b); // behaves like a normal function

constexpr y = Max(4, 5); // correct
constexpr y1 = Max(x, 5); // x is a literal but not a compile time constant
```

### `std::initializer_list
 - Lightweight proxy object that represents an array of objects.
 - Constructed automatically from a braced list of objects.
 - Provides access to its elements through iterators.
 - Need to `#include <initializer_list>` header
```cpp
void Print(std::initializer_list<int> values) {
	// access elements of initializer lists with an iterator
	auto it = values.begin();
	while (it != values.end()) {
		std::cout << *it++ << std::endl;
	}

	for (auto x : values) {
		std::cout << x << " ";
	}
}
```

### Unions
- Represents members in the same memory - memory size determined by the largest member size.
 - No way to know which are the types the union holds, can be confusing which is the current active union member.
 - Can only initializa one member within the union.
 - Cannot assign user-defined types to a union member directly, need to use placement `new` operator (only intializes the memory but does not allocate).
```cpp
union ABC {
	A a;
	B b;
	C c;
	std::string str;
	ABC() {};
	~ABC() {};
}

int main() {
	ABC abc_1;
	
	new(&abc_1.str) std::string("abc");
	new(&abc_1.a) A{};
	// have to manually call destructor for user-defined types in unions
	abc_1.a.~A();
}
```

 - User-defined type within an union are not destroyed implictly, need to manually call user-defined type member's destructor. 
 - Cannot have a base class, cannot derive from another union.

### Templates
- Generalizes software components that are reused in different situations, for any kind of data.
- These components are generated at _compile time_, usually used for high performance algorithms and classes.
```cpp
	template<typename T>
	T function(T arg) {
	}
```
#### Template Argument Deduction
Compiler will perform argument deduction in compile time, by examining the function arguments, then instantiate a function of that particular type.

#### Template Instantiaion
- Happens when the compiler generates code from template function or class at compile time.
- Occurs implicitly when:
 - a function template is invoked,
 - taking address of a template function,
 - using explicit instantiation
 - creating explicit specialization 
- Full definition of template should be available to the compiler - template definitions should be in header files.

```cpp
	template <typename T>
	T Max(T X, T y) {
		return x > y ? x : y;
	}

	// explicitly instantiate function template
	template char Max(char x, char y);

	int main() {
		int x = 1.1, y = 2.2;
		// invoke template function with specific type
		Max<double>(x, y);

		// using explicit instatiation
		int (*f_ptr)(int, int) = Max;
	}
```

#### Explicit Specialization
 - Template specialization for a certain type, example: implememnt algorithm explicitly for a specific data type,
 - Explicit specialized function must be defined in a `.cpp` file
 - Primary template definition should occur before template explicit specialization
 - Need a `<>` after `template` keyword to differenciate from explicit instantiation:
```cpp
	// explicit initialization
	template char Max(char x, char y);
	// explicit specialization
	template<> const char * Max<const char *>(const char * x, const char *y) {
		return strcmp(x,y) > 0 ? x : y;
	}
```

#### Nontype Template Arguments
- Constant expressions (address, reference, `int`, `nullptr`, `enums`) that are computed at compile time, in template argument list.
- syntax: `template<typename T, int size>`


#### Variadic Templates
- Functions and classes that accepts arbitary number and types of arguments.
```cpp
// template parameter pack
// 'Params' does not represent a typename, it is an alias to the list of typenames
template<typename...Params>	// '...' = ellipses
// Function parameter pack - this function can accept any number and any type of arguments
void Print(const T &a, const Params&... args) {	// we need an extra argument a here for the base case function to stop the recursion
	// find out number of parameters in function parameter pack and template parameters in template parameter pack
	// std::cout << sizeof...(args);
	// std;;cout << sizeof...(Params);
	// accessing the args individually via recursion and base case function.
	std::cout << a;
	if (sizeof(args) != 0) {
		std::cout << ","; // print out a comma between the elements
	}
	Print(args...);		// number of arguments will reduce by 1
}
 
// base case function
void Print() {};

int main() {
	Print(1, 2.5, "3");
/* here's what happen when the above Print() is called:
1. Print(1, 2.5, "3");
2. Print(2.5, "3");
3. Print("3");
4. Print();	<- base case function is called here.
*/
}
```

#### Type Definition (`typedef`)
 - Introduces a new (shorter, more meaningful) name for an existing type, this new name becomes a synonym of that type.
 - Implementation details that might change can be encapsulated.
 - Does not include new type, only introduces a new name for existing type.

Examples:
```cpp
typedef unsigned int UINT;
UINT val{};

typedef long long LLONG;
LLONG elem{};

typedef std<vector<std::list<Employee>> Teams;
Teams testingTeams;
Teams::iterator it = testingTeams.begin();
 
// function pointers
typedef ErrorFn const char *(*ErrorFn)(int);
ErrorFn pfn = GetErrorMessage;
```

#### Template Type Alias (C++ 11)
 - Simiar to `typedef`, creates a synonym of an existing type,
 - Does not introduce a new type, 
 - Created through `using` keyword: `using identifier = type`:
```cpp
using UINT = unsigned int;
UINT val{};

using LLONG = long long;
LLONG elem{};

using Teams = std<vector<std::list<Employee>>;
Teams testingTeams;
Teams::iterator it = testingTeams.begin();
 
// function pointers
using ErrorFn = const char *(*)(int);
ErrorFn pfn = GetErrorMessage;
```

```cpp
using Names = std::vector<std::list<std::string>>;

int main() {
	Names name1;
}
```
 
 - Compared to `typedef`, aliases has the ability to create the so-called alias template: an alias that keeps an open door to the underlying type. You can have the usual type aliasing and the ability to specify the template parameter(s) in the future:
	```cpp
	template<typename T1, typename T2> using Map = std::map<T1, std::vector<T2>>;

	// Actual type: std::map<std::string, std::vector<std::string>> (as in the original example)
	Map<std::string, std::string> map1;

	// Actual type: std::map<int, std::vector<int>>
	Map<int, int> map2;

	// Actual type: std::map<int, std::vector<float>>
	Map<int, float> map3;
	``` 

#### `static_assert(expression, failure_msg)`
Used to evaluate an expression at compile time. Used to checks for code that you never want to be run.

Example 1: check if we are compiling with 32-bit or 64-bit machine.
	```cpp
	#inclde<iostream>

	int main() {
		static_assert(sizeof(void*) == 4, "The current machine is not 2-bit ");
	}
	```
Example 2: Used together with type traits for type checking in Templates variables at compile time:
	```cpp
	#include<iostream>
	#include<type_traits>

	template<typename T>
	T Divide(T a, T b) {
		static_assert(std::is_floating_point<T>::value, "only floating point type supported!");
		return a / b;
	}
	```

## Object Oriented Programming

### Access modifiers
##### Base class:
- `private`: members are inaccessible outside the class, accessible to members of the class
- `public`: members are accessible even outside of the class
- `protected`: members are accessible within the class and its child classes

##### Child class: (`class Child : access_modifier Base {}`)
- `public` child classes can access `public` and `protected` members of base class.
- `private` child classes will inherit all members from base class as private members. __Base class private members will be inherited but not accessible from the child class.__ `public` and `protected` base class members will be accessible within the child class.  
- `protected` child classes will inherit all members from base class as protected members, the access modifier of base class private members will not be modified, will still be inherited as `private` members in the child class.
- default access modifier for a child class is `private`, for a `struct` is `public`. Does not matter if base class is class or `struct`.

### Polymorphism
- Complie Time Polymorphism (compile time binding) examples: function overloading, overator overloading and templates. The compiler has enough information at compile time to determine which functions to be invoked. 
- Run Time Polymorphism (dynamic binding) implemented via `virtual` mechanism - polymorphism functions. These functions are invoked through a pointer or reference, are re-implemented in child classes with their own implementations.
- "_A class that declares or inherits a virtual function is called a polymorphic class._"

#### How `virtual` function works
When the base class with `virtual` functions is compiled, it would generate an array of function pointers called as virtual table, which contains the addresses of the virtual functions. The starting address of the virtual table is stored in a special member variable called as virtual pointer, which is added by the compiler as the member of the class.

This process will be identical for each child class. The virtual pointer of the base class will inherited and used to initialize the virtual table of the child class.

Here is what happens when a child class `virtual` function is called:
1. Get child class object address
2. Get the virtual pointer
3. Find the position of the `virtual` function in the virtual table
4. Get the address of the function (will need to add offsets incremented by pointer sizes depending on where the functions are located in the virtual table)
5. Invoke the function

Base class should always have `virtual` destructor. Virtual destructors are useful when you might potentially delete an instance of a derived class through a pointer to base class. Here is an example why:

```cpp
class Base 
{
    // some virtual methods
};

class Derived : public Base
{
    ~Derived()
    {
        // Do some important cleanup
    }
};

int main() {
	Base *b = new Derived();
	// use b
	delete b; // Here's the problem!
}
```

Since `Base`'s destructor is not `virtual` and b is a `Base*` pointing to a `Derived` object, `delete b` has _undefined behaviour_:

[In delete b], if the static type of the object to be deleted is different from its dynamic type, the static type shall be a base class of the dynamic type of the object to be deleted and the static type shall have a virtual destructor or the behavior is undefined.

In most implementations, the call to the destructor will be resolved like any non-virtual code, meaning that the destructor of the base class will be called but not the one of the derived class, resulting in a resources leak.

To sum up, always make base classes' destructors virtual when they're meant to be manipulated polymorphically.

If you want to prevent the deletion of an instance through a base class pointer, you can make the base class destructor`protected` and nonvirtual; by doing so, the compiler won't let you call delete on a base class pointer.

### pure `virtual` function(s) and abstract class.
- syntax: `virtual func() = 0`. Child class will have to implement the pure `virtual` function(s). 
- pure `virtual` functions do not have an entry in the class vtable, but exists in child classes vtables to define the layout of class functions.
- The class that contains at least one pure `virtual` functions is an abstract class. Abstract classes cannot be instantiated, but you can create their pointer and references.
- Abstract classes establish a contract with clients, the contract guarantees the implementation of the behavior provided by the child classes - that is why abstract are used to create interfaces.


#### `final`
Used to prevent a class from being inherited: `class last_class final{};`

#### `override`
Used to tell the compiler that a `virtual` function is overridden in the child class with the same function name and signature.
```cpp
class Base {
public:
	virtual void my_function();

};

class Child : public Base {
	void my_function override();
	// void my_function override final (); // mark with `final` if you don't want the child class to override this function
	
};
```

### Upcasting & Downcasting
#### Upcasting
Casting a child class object to base class object. This can only be accomplished using pointer and references, or else object slicing (object slicing occurs when an object of a subclass type is copied to an object of superclass type: the superclass copy will not have any of the member variables defined in the subclass. These variables have, in effect, been "sliced off") will happen.
```cpp
	Child c();
	Base *b = &c;
```

#### Downcasting
Casting a base class object to a child class object, need to manually specify the class:
```cpp
	Base b();
	Child *c = static_cast<Child *>(b);
```

### Exception Handling
1. `try`, `throw` & `catch` example usage:
```cpp
#include <iostream>
#include <limits>

int ProcessRecords(int count) {
    int *pArray = (int*)malloc(count * sizeof(int));
    if (count < 10) {
        throw std::out_of_range("Count should be greater than 10!");
    }
    if (pArray == nullptr) {
        throw std::runtime_error("failed to allocate memory!");
    }
    for (int i = 0; i < count; ++i) {
        pArray[i] = i;
    }

    free(pArray);
    return 0;
}

int main() {
    try {
        // ProcessRecords(std::numeric_limits<int>::max());
        ProcessRecords(5);

    }

    // catch multiple specific exceptions
    catch (std::runtime_error &exc) {
        std::cout << exc.what() << std::endl;
    }
    catch (std::out_of_range &exc) {
        std::cout << exc.what() << std::endl;
    }

    // catch all std:exception
    catch (std::exception &exc) {
        std::cout << "Caught as all exceptions: " << exc.what() << std::endl;
    }

    // all other implicit catches with no specific documentation - should be avoid using this catch pattern
    catch (...) {
        std::cout << "An unexpected error happened!" << std::endl;
    }
}
```

2. Stack Unwinding
When an exception is thrown, the stack will be unwinded to destroy _local_ objects - objects that are created on the heap will not be destroyed and memory will be leaked. 

The solution to this issue is to use smart pointers (`std::unique_ptr`s and `std::shared_ptr`s) and containers (`std::vector`s, `std::string`s).

Destructors should not contain exceptions, as it may be involed during the stack unwinding process, the stack unwinding can be the result of another exception. The program will terminate if the destructor throws an exception.

3. Nested Stack Unwinding
[TODO] Add code here in example where exception is modified and re-`throw`n.

### `noexcept`
- Notifies the compiler that there are no exceptions in the function (both in declaration and definition), so that further optimization can be applied (no need to generate stack unwinding code).
- Function that uses library functions should not be marked as `noexcept(true)`, destructor are marked implictly with `noexcept` keyword. Move operators (constructor /assignment) functions should also be marked with `noexcept(true)`, as some container objects only use move (instead of copy) operators when marked with `noexcept(true)`.
-  Only used for functions given strong guarantee that they do not throw.
- `noexcept(true)` = no exception is thrown; even though the keyword is added to the function declaration, it 
```cpp
void Test(int x) {
	throw x;
}

// compiler will check at compile time the exception specification of Test and pass it to Sum function.
int Sum(int a, int b) noexcept(noexcept(Test(a))) {
	return (a + b);
}
```

### Concurrency
#### `std::thread()`
- used to create a thread, takes in callable function reference as input
- `join()`: waits for a thread to finish its execution
- `detach()` permits the thread to execute independently from the thread handle
- initialize thread with a reference_wrapper `std::ref` as the arguments to the thread function are moved or copied by value:
```cpp
void Download(std::string &file_name) {
	...
}

int main() {
	std::string test_file_name = "test.cpp";
	std::thread download_thread(Download, std::ref(test_file_name));
}
```

#### Synchronization Between Threads
1. `std::mutex()` - a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. 
- Solves __race conditions__.
- A calling thread owns a mutex from the time that it successfully calls either `lock()` or `try_lock()` until it calls `unlock()`.
 - The thread waiting for the mutex to be unlocked will be in sleep mode and put on a queue until its turn comes.
- Can cause __deadlock__: when one thread locks the mutex, then exits without unlocking the mutex, the second thread waiting for the first thread to unlock the mutex will be waiting forever.

2. `std::lock_guard()`
- A mutex wrapper that provides a convenient RAII-style mechanism for owning a mutex for the duration of a scoped block.
- Solves the issue of deadlocking caused by manually `lock()`ing and `unlock()` mutexes:
```cpp
std::mutex g_mutex;

std::lock_guard<std::mutex> mtx(g_mutex);
```

3.Other `std::thread` functions & `this_thread` namespace
- `std::thread::hardware_concurrency()` - number of threads to start to maximize CPU usage.
- `std::this_thread::get_id()` (used in thread callback function) - get thread id.
- `std::this_thread::sleep_for(std::chrono::seconds(1))` - delay 


### Task Based (High Level) Concurrency 
- A task is a function that is automatically executed in a separate thread.

#### `std::async(callable, args)` & `std::async(launch_policym callable, args)`
 - runs a function asynchronously (__potentially in a separate thread which may be part of a thread pool__) and returns a std::future that will eventually hold the result of that function call.
- using `std::thread` to launch a thread forces the creation of a new thread instead of using one from a pool with `std::async()`.
- `args` are always passed by value - need to use `std::ref()` reference wrapper.
- launch policies (if not specified, may not always create a new thread):
 - `std::launch::deferred` - task is executed synchronously
 - `std::launch::async` - task is executed asynchronously - will throw `std::system_error` exception if new thread cannot be created.

#### `std::future`
- used for communication between threads, it has a shared state that can be accessed by threads.
- created through a `std::promise` object, created by `std::async` that directly returns a future object.
- `std::promise` - input channel to task, `std::future` - output channel for task, they allow safe data sharing between threads without requiring explict synchronization.
- shared state: value set by the task, the thread that reads the shared state will wait for the future is ready(task returns the value).
- `wait()` and `get()` will block the calling thread until the shared state is ready. 

#### `std::promise`
- Provides a way to store a value or an exception
- this is a shared state that can be accessed from another thread object `std::future`. One operation stores a value in a `std::promise` and the other operation with retrieve it via a `std::future` asynchronously.
- these operations are synchronized, therefore thread-safe.
- `std::promise` can be only used once. 

#### lambda expressions
 - Lambda is interpreted as an anonymous function object inside the compiler.
```
// '[]' is the lambda introducer
[](<input_args>)<mutable_specification> <exception_specification> <return_type>
{
	// lambda body
}
```
- Capturing  (setting and passing an offset value into a lambda) is implemented via `[]`, where its value(s) will be made a copy. Captures can be made mutable via the `mutable` keyword when captured by value:
```
    result_vector_int_2 = for_each(test_vector_int, [offset](int &x) mutable {
        offset++;
        return x+offset;
    });
```

- Capture List Mode (all "enclosing scope variables" here mean the ones that are previously _declared_)
 - `[var]` - capture `var` by value;
 - `[=]` - capture all enclosing scope variables by value;
 - `[&var]` - capture `var` by reference;
 - `[&]` - capture all enclosing scope variable by reference;
 - `[&, var]` - capture `var` by value and all other scope variables by reference
 - `[=, &var]` - capture `var` by reference and all other scope variables by value
 - `[this]` - capture `this` (used to access all class member variables)

- Lambda within Lambda:
```
    [](int x) {
        x *= 2;
        [](int x) {
            std::cout << "[TestCase4] lambda within lambda: " << x << std::endl;
        }(x);
    }(5);
```

- Generalized Capture (`C++ 14`)

```
// useful for non-copiable objects or if capturing a unique pointer
auto fn = [y = std::move(x)](int arg) {
	return arg + y;
};
```