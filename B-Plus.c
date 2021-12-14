
#define _CRT_SECURE_NO_DEPRECATE //done so microsoft visual studio lets me use fscanf and fopen instead of fscanf_s and fopen_s respectively

#define M 5//is for 
#define L 5//might delete later //is for linked list size
//possibilidade de fazer uma conta antes do define M e atribuir o resultado dessa conta ao M

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
    char died[11];
    char country[50];
    char countryCode[3];
    char city[50];
    char gender[7];
    uint32_t year;
    char category[12];
    uint32_t share;
    char motivation[350];
} record_st;

typedef struct tree_node {
    uint32_t id;
    struct tree_node* child;//will either have a child pointer or a list pointer equal to NULL
    list_node* list;//will point to first element of the linked list
    //struct tree_node* parent;//maybe not
    //struct tree_node* next;//WHATS IS NEXT??
    //record_st* information;//only if its a leaf node
}tree_node;

typedef struct list_node {
    struct list_node* next;
    record_st* contents;

    struct list_node* prev;//maybe not needed is_leaf may be deleted too
    int is_leaf; // if it stays it will always equal to 0
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

    FILE* fp = fopen(argv[1], "r+");//may need change

    if (fp == NULL) {
        printf("Error opening your file!");
        return NULL;
    }

    record_st* node = (record_st*)calloc(1, sizeof(record_st));//using calloc so all values are initialized as 0
    char* temp_id = (char*)calloc(10, sizeof(char));//max 10 digits
    char* temp_year = (char*)calloc(10, sizeof(char));
    char* temp_share = (char*)calloc(10, sizeof(char));


    if (fscanf(fp, " %[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", temp_id, node->firstname, node->surname, node->birthdate, node->died, node->country, node->countryCode, node->city, node->gender, temp_year, node->category, temp_share, node->motivation) == 0) {
        return NULL;//if fscanf returns 0 means we are at the end of the file
    }
    else {
        node->id = char_to_num(temp_id);
        node->year = char_to_num(temp_year);
        node->share = char_to_num(temp_share);
    }


    return node;
}

int* insert_node(record_st* node, tree_node arr[]) {
    if (node == NULL) {//we are at the end of the file
        return NULL;
    }
    int idx;
    if ((&arr[0])->child == NULL) {//is leaf?

        for (int i = 0; i != M; i++) {//iterate trough linked list with the ids of the actual information
            if (node->id < (&arr[i])->list->contents->id) {//if the nodes id wich we wanna insert is smaller then the i element of the list
                idx = i - 1;
                break;
            }
            else {
                idx = i;//no break because it will be the last option either way
            }
        }



        list_node* position = (&arr)[idx]->list;
        for (; position->next != NULL; position = position->next) {
            if (node->id < position->next->contents->id){
                add_node(node,position);
                //if true we know that current list node is the correct one
                //else its gonna be the last
                return 1;//anything different then NULL will work as a return value
            }
        }
        //since we know the last node is the one we're searching for
        position = position->next;
        add_node(node, position);
        return 1;
        //for last node elem
        //no need to check last elem cause we know it will be the one we want


    }
    else {
        for (int i = 0; i != M; i++) {
            if (node->id < (&arr[i])->id) {
                idx = i - 1;
                break;
            }
            else {
                idx = i;
            }
        }
        arr = (&arr[idx])->child;
        insert_node(node, arr);
    }
}
                                                //will receive node and location
                                                //will check if current list is full
                                                //incase not full will have to handle separation of next node

add_node(record_st* node, list_node* position) {
    //check if current list is full

            


};   



int main(int argc, char* argv[]) {

    tree_node* root_arr = (tree_node*)calloc(5, sizeof(tree_node));

    //first fill the initial array and its leaf nodes
    //then complete the more complex mid tree arrays and leaf nodes

    void* output;
    while (output != NULL) {
        output = insert_node(read_line(argc, argv), root_arr);
    }


    return 0;
}