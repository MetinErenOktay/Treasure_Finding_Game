#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "main.h"

//this function stores content of map matrix txt file in map_pointer
void configure_map_array(){
    std::ifstream map_input_file(map_str);
    //creates a 2D array which have content of map with dynamic memory allocation
    map_pointer=NULL;
    map_pointer = new int*[row_size_of_map];

    for(int i=0;i<row_size_of_map;i++){
        map_pointer[i] = new int[column_size_of_map];
        for (int j = 0; j < column_size_of_map; j++) {
            //writes content of map matrix txt file into map array
            map_input_file >> map_pointer[i][j];
        }
    }
}

//this function stores content of key matrix txt file in key_pointer
void configure_key_array(){
    std::ifstream key_input_file(key_str);
    //creates a 2D array which have content of key with dynamic memory allocation
    key_pointer=NULL;
    key_pointer = new int*[size_of_key];

    for(int i2=0; i2<size_of_key; i2++){
        key_pointer[i2] = new int[size_of_key];
        for (int j2 = 0; j2 < size_of_key; j2++) {
            //writes content of key matrix txt file into key array
            key_input_file >> key_pointer[i2][j2];
        }
    }
}
//this recursive function adds 5 to dot product if it is a negative number until its value become a non-negative number
void dot_product_denegativator(){
    if(dot_product >= 0) {//do nothing if dot product is a non-negative number
    }
    else{
        dot_product += 5;
        dot_product_denegativator();
    }
}

//this recursive functions checks if current sub-matrix has the treasure or not by calculating dot product of key-matrix and sub-matrix
void search_treasure() {
    
    if (dot_product%5 == 0) {//base case
        //do nothing if dot product equals to 0

    } else {//recursive case
        //creates a 2D array which have content of sub-matrix with dynamic memory allocation
        dot_product = 0;
        for (int i = curr_row_of_submatrix_center - ((size_of_key-1)/2); i < curr_row_of_submatrix_center + size_of_key - ((size_of_key-1)/2) ; i++) {
            submatrix_pointer[i] = new int[size_of_key];
            for (int j = current_column_of_submatrix_center - ((size_of_key-1)/2); j < current_column_of_submatrix_center + size_of_key - ((size_of_key-1)/2); j++) {
                //find sub-matrix on map and writes content of sub-matrix into sub-matrix array
                submatrix_pointer[i - curr_row_of_submatrix_center + ((size_of_key-1)/2)][j - current_column_of_submatrix_center + ((size_of_key-1)/2)] = map_pointer[i][j];
            }
        }

        //calculates dot product of key and sub-matrix
        for (int dot_prod_row_index = 0; dot_prod_row_index < size_of_key; dot_prod_row_index++) {
            for (int dot_prod_column_index = 0; dot_prod_column_index < size_of_key; dot_prod_column_index++) {
                //adds 1 to set 0 to initial value of dot_product
                dot_product += key_pointer[dot_prod_row_index][dot_prod_column_index] *
                               submatrix_pointer[dot_prod_row_index][dot_prod_column_index];
            }
        }

        //adds 5 to dot product until it become a non-negative number
        dot_product_denegativator();

        // Write to the output file
        output_file << curr_row_of_submatrix_center << "," << current_column_of_submatrix_center << ":" << dot_product << std::endl;

        //this part determines the next move of the key-matrix on map-matrix
        if(dot_product%5 == 1){
            //if estimated direction will exceed borders
            if(curr_row_of_submatrix_center == (size_of_key-1)/2){
                curr_row_of_submatrix_center += size_of_key;
            }else{//if estimated direction will not exceed borders
                curr_row_of_submatrix_center -= size_of_key;
            }
        }
        else if(dot_product%5 == 2){
            //if estimated direction will exceed borders
            if(curr_row_of_submatrix_center == row_size_of_map - 1 - (size_of_key-1)/2){
                curr_row_of_submatrix_center -= size_of_key;
            }else{//if estimated direction will not exceed borders
                curr_row_of_submatrix_center += size_of_key;
            }
        }
        else if(dot_product%5 == 3){
            //if estimated direction will exceed borders
            if(current_column_of_submatrix_center == column_size_of_map - 1 - (size_of_key-1)/2){
                current_column_of_submatrix_center -= size_of_key;
            }else{//if estimated direction will not exceed borders
                current_column_of_submatrix_center += size_of_key;
            }
        }
        else if(dot_product%5 == 4){
            //if estimated direction will exceed borders
            if(current_column_of_submatrix_center == (size_of_key-1)/2){
                current_column_of_submatrix_center += size_of_key;
            }else{//if estimated direction will not exceed borders
                current_column_of_submatrix_center -= size_of_key;
            }
        }
        if(dot_product%5 != 0)
            dot_product = -1;

        search_treasure();//calls the function itself
    }
}
int main(int argc, char** argv) {
      
	
    int arg_parser_integer[2];
    int i =0;
    char *arg_parser_pointer = strtok(argv[1], "x");
    while(arg_parser_pointer){
        arg_parser_integer[i] = std::stoi(arg_parser_pointer);
        i++;
        arg_parser_pointer = strtok(NULL,"x");
    }
    row_size_of_map = arg_parser_integer[0];
    column_size_of_map = arg_parser_integer[1];

    size_of_key = atoi(argv[2]);//atoi converts command-line argument to int
    map_str=argv[3];	
    key_str=argv[4];
    output_str=argv[5];




    //determine initial center index of key-matrix and sub-matrix
    curr_row_of_key_center=(size_of_key-1)/2;
    current_column_of_key_center=(size_of_key-1)/2;
    curr_row_of_submatrix_center=(size_of_key-1)/2;
    current_column_of_submatrix_center=(size_of_key-1)/2;

    //write content of map matrix txt and key matrix files in map_pointer and key_pointer
    configure_map_array();
    configure_key_array();

    //search treasure location on map matrix
    output_file.open(output_str);
    search_treasure();
    output_file.close();    
}