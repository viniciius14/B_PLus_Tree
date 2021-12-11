#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//All Warnings Syntax
//gcc -Wall -Wextra -Wpedantic -ansi -std=c99 -g b_plus.c -o b_plus
//.\b_plus.exe C:\\Users\\rodri\\Documents\\GitHub\\B-Plus-Tree\\teste.txt





//this is a test


typedef struct record_st {
    int32_t key;
    char name[100];
    char birthdate[12];
    char prize[100];
    int32_t year;
    char country[100];
    char comment[80];
} record_st;


typedef struct tree_node {
    tree_node* parent;
    tree_node* child;
    tree_node* next;//maybe not
    record_st* information;
}tree_node;


typedef struct list_node {//if we do a linked list
    list_node* next;
    list_node* prev;
    record_st* contents;
}list_node;



int char_to_num(char arr[]) {
    int32_t num = 0;

    for (int32_t x = 0; arr[x] != '\0'; x++) {
        num = 10 * num + (arr[x] - '0');
    }

    return num;
}



record_st* read_line(int argc, char* argv[]) {

    if (argc != 2) {
        printf("You called to many or to few argumetns!");
        return NULL;
    }

    FILE* fp = fopen(argv[1], "r+");

    if (fp == NULL) {
        printf("Error opening your file!");
        return NULL;
    }

    record_st* test = malloc(sizeof(*test));
    char* temp_key = malloc(sizeof(char) * 10);//max 10 digits
    char* temp_year = malloc(sizeof(char) * 10);

    fscanf(fp, " %[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", temp_key, test->name, test->birthdate, test->prize, temp_year, test->country, test->comment);

    test->key = char_to_num(temp_key);
    test->year = char_to_num(temp_year);

    fclose(fp);
    return test;
}



int main(int argc, char* argv[]) {

    read_line(argc, argv);



    return 0;
}