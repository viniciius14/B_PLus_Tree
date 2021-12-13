
#define _CRT_SECURE_NO_DEPRECATE //done so microsoft visual studio lets me using fscanf and fopen_s instead of fscanf_s and fopen_s respectively

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


//All Warnings Syntax
//gcc -Wall -Wextra -Wpedantic -ansi -std=c99 -g b_plus.c -o b_plus
//.\b_plus.exe C:\\Users\\Rodrigo\\Documents\\GitHub\\B_Plus_Tree\\teste.txt

// L = 5 because 4KB / 708 B = 5.66, each block can store 5 records
// M = 500  because block size = 4KB, id size = 4B, pointers = 4B,  4KB/(4B+4B) = 500


typedef struct record_st {
    uint32_t id;
    char firstname[100];
    char surname[100];
    char birthdate[11];
    char country[50];
    char countryCode[3];
    char city[50];
    char died[11];
    char gender[7];
    uint32_t year;
    char category[12];
    uint32_t share;
    char motivation[350];
} record_st;

typedef struct tree_node {
    struct tree_node* child;
    uint32_t id;
    //struct tree_node* parent;//maybe not
    //struct tree_node* next;//WHATS IS NEXT??
    //record_st* information;//only if its a leaf node
}tree_node;

typedef struct list_node {
    struct list_node* next;
    struct list_node* prev;//maybe not needed
    record_st* contents;
}list_node;

int char_to_num(char arr[]) {
    uint32_t num = 0;

    for (uint32_t x = 0; arr[x] != '\0'; x++) {
        num = 10 * num + (arr[x] - '0');
    }

    return num;
}

record_st* read_line(int argc, char* argv[]) {

    if (argc != 2) {
        printf("You called to many or to few arguments!");
        return NULL;
    }
    
    FILE* fp = fopen(argv[1],"r+");//may need change

    if (fp == NULL) {
        printf("Error opening your file!");
        return NULL;
    }

    record_st* test = malloc(sizeof(*test));
    char* temp_id = malloc(sizeof(char) * 10);//max 10 digits
    char* temp_year = malloc(sizeof(char) * 10);
    char* temp_share = malloc(sizeof(char) * 10);

    fscanf(fp, " %[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", temp_id, test->firstname, test->surname, test->birthdate, test->country, test->countryCode, test->city, test->died, test->gender, temp_year, test->category, temp_share, test->motivation);

    test->id = char_to_num(temp_id);
    test->year = char_to_num(temp_year);
    test->share = char_to_num(temp_share);

    return test;
}



int main(int argc, char* argv[]) {

    read_line(argc, argv);



    return 0;
}