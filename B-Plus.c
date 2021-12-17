#define _CRT_SECURE_NO_DEPRECATE //done so microsoft visual studio lets me use fscanf and fopen instead of fscanf_s and fopen_s respectively
#define M 5//is for size of the tree arrays
#define L 5//is for linked list size
// L = 5 because 4KB / 708 B = 5.66, each block can store 5 records
// M = 512  because block size = 4KB, id size = 4B, pointers = 4B,  4KB/(4B+4B) = 512

// M / 2 = index wich will get promoted   ---  5/2 = 2  --- nodes to the right will be heavier

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//All Warnings Syntax
//gcc -Wall -Wextra -Wpedantic -ansi -std=c99 -g b_plus.c -o b_plus

//.\b_plus.exe C:\\Users\\Rodrigo\\Documents\\GitHub\\B_Plus_Tree\\nobel_prize_winners.csv





//
//Descend to the leaf where the key fits.
//1 - If the node has an empty space, insert the key / reference pair into the node.
//2 - If the node is already full, split it into two nodes, distributing the keys evenly between the two nodes.
//      If the node is a leaf, take a copy of the minimum value in the second of these two nodesand repeat this insertion algorithm to insert it into the parent node.
//      If the node is a non - leaf, exclude the middle value during the splitand repeat this insertion algorithm to insert this excluded value into the parent node.
//

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

typedef struct list_node {
    struct list_node* next;
    record_st* contents;

    struct list_node* prev;//maybe not needed
    uint32_t is_leaf; // if it stays it will always equal to 0
}list_node;

typedef struct tree_node {
    uint32_t id;
    struct tree_node* child;//will either have a child pointer or a list pointer equal to NULL
    list_node* list;//will point  to first element of the linked list
    //struct tree_node* parent;//maybe not
    //struct tree_node* next;//WHATS IS NEXT??
    //record_st* information;//only if its a leaf node
}tree_node;



uint32_t char_to_num(char arr[]) {
    uint32_t num = 0;

    for (uint32_t x = 0; arr[x] != '\0'; x++) {
        num = 10 * num + (arr[x] - '0');
    }

    return num;
}

record_st* read_line(uint32_t argc, char* argv[], FILE* fp) {

    if (argc != 2) {
        printf("You called to many or to few arguments!");
        return NULL;
    }

    if (fp == NULL) {
        printf("Error acessing your file!");
        return NULL;
    }

    record_st* node = (record_st*)calloc(1, sizeof(record_st));//using calloc so all values are initialized as 0
    char* temp_id = (char*)calloc(10, sizeof(char));//max 10 digits
    char* temp_year = (char*)calloc(10, sizeof(char));
    char* temp_share = (char*)calloc(10, sizeof(char));

    if (node != NULL) {
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
    return node;
}

uint32_t is_full(list_node* list_position) {
    
    uint32_t size = 0;
    while (list_position->next != NULL) {
        size++;
    }
    size++;
    if (size == L) {
        return 1;
    }
    return 0;
}

void add_node(record_st* node,list_node* list_position, list_node* node_position) {
    //wil check if list is full
    if (is_full(list_position) == 1) {//1 for full 0 for any other state

        //complicou

    }
    else {
        //n complicou tanto
    }
}


uint32_t insert_node(record_st* node, tree_node arr[]) {
    if (node == NULL) { //we are at the end of the file
        return 0;    
    }
    uint32_t idx;
    if ((&arr[0])->child == NULL) {//is leaf?
        //checking last tree node, this will point  to linked lists
        for (uint32_t i = 0; i != M; i++) {//iterate trough linked list with the ids of the actual information
            if (node->id < (&arr[i])->list->contents->id) {//if the nodes id wich we wanna insert is smaller then the i element of the list
                idx = i - 1;
                break;
            }
            else {
                idx = i;//no break because it will be the last option either way
            }
        }

        list_node* list_position = (&arr)[idx]->list;//will indicate where list is in the tree
        list_node* node_position = (&arr)[idx]->list;//will indicate where node will go in the list

        for (; node_position->next != NULL; node_position = node_position->next) {
            if (node->id < node_position->next->contents->id) {
                add_node(node,list_position, node_position);
                //if true we know that current list node is the correct one
                //else its gonna be the last
                return 1;//anything different then 0 will work as a return value
            }
        }
        //since we know the last node is the one we're searching for
        //for last node elem
        //no need to check last elem cause we know it will be the one we want
        node_position = node_position->next;
        add_node(node,list_position, node_position);

    }
    else {
        for (uint32_t i = 0; i != M; i++) {
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
    //gotta had a return here
    return 0;   //doesnt actually do anything
}





//will receive node and location
//will check if current list is full
//incase not full will have to handle separation of next node



uint32_t main(uint32_t argc, char* argv[]) {  //fazer ficheiro de saida com os nodes organizados desde o menor ate ao maior

    tree_node* root_arr = (tree_node*)calloc(5, sizeof(tree_node));
    FILE* fp = fopen(argv[1], "r+");//may need change

    //first fill the initial array and its leaf nodes
    //then complete the more complex mid tree arrays and leaf nodes

    uint32_t output = -1;
    while (output != 0) {
        output = insert_node(read_line(argc, argv, fp), root_arr);
    }
    //print_results();


    return 0;
}
