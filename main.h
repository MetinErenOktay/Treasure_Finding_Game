#ifndef BBM201_FINDTREASURE_H
#define BBM201_FINDTREASURE_H
// Create and open an output file
std::string map_size_str;
std::string map_str;
std::string key_str;

std::string output_str;

std::ofstream output_file;
static int curr_row_of_key_center;
static int current_column_of_key_center;
static int curr_row_of_submatrix_center;
static int current_column_of_submatrix_center;
static int dot_product = -1;
int row_size_of_map;
int column_size_of_map;
int size_of_key;
static int** map_pointer;
static int** key_pointer;

int submatrix_row_counter = 0;
int submatrix_column_counter = 0;
static int** submatrix_pointer = new int *[size_of_key];
static int* arg_pointer;
#endif //BBM201_FINDTREASURE_H

