#include <iostream>
#include <string.h>

void New() {
	int *p = new int(5);	// new can both allocate and initialize the memory
	std::cout << *p << std::endl;
	delete p;
	p = nullptr;
}

void NewArr() {
	int *arr_ptr = new int[3] {1, 2, 3};
	std::cout << arr_ptr << std::endl;
	delete []arr_ptr;
	
}

void NewStr() {
	char *str_ptr = new char[4];
	strcpy(str_ptr,"ABC");
	std::cout << str_ptr << std::endl;
	delete []str_ptr;
}

void NewMatrix() {
	int *row1_ptr = new int[5];
	int *row2_ptr = new int[5];

	int **matrix_ptr = new int *[2];
	matrix_ptr[0] = row1_ptr;
	matrix_ptr[1] = row2_ptr;

	int i = 0;
	for (int col = 0; col < 5; col++) {
		for (int row = 0; row < 2; row++) {
			matrix_ptr[row][col] = i;
			i ++;
			std::cout << "matrix[" << row << "][" << col << "] = " << i << std::endl;
		}
	}

	// deallocate the pointers in the same order as it was initialized.
	delete[] row1_ptr;
	delete[] row2_ptr;
	delete[] matrix_ptr;

}


int main() {
	void(*new_fptr) () = New;
	(*new_fptr)();

	void(*newarr_fptr) () = NewArr;
	(*newarr_fptr)();

	void(*newstr_fptr) () = NewStr;
	(*newstr_fptr)();

	void(*newmatrix_fptr) () = NewMatrix;
	(*newmatrix_fptr)();

	return 0;
}
