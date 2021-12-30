#define _CRT_SECURE_NO_DEPRECATE //done so microsoft visual studio lets me use fscanf and fopen instead of fscanf_s and fopen_s respectively
#define M 5//is for size of the tree arrays
#define L 5//is for linked list size
// L = 5 because 4KB / 708 B = 5.66, each block can store 5 records
// M = 512  because block size = 4KB, id size = 4B, pointers = 4B,  4KB/(4B+4B) = 512


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//All Warnings Syntax
// gcc -Wall -Wextra -Wpedantic -ansi -std=c99 -g b_plus.c -o b_plus
//csv file location
// .\b_plus.exe C:\\Users\\Rodrigo\\Documents\\GitHub\\B_Plus_Tree\\Prize_Winners.csv

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
    struct list_node* prev;
    //tree_node* parent;          //only the first elem of the linked list will have this
}list_node;

typedef struct tree_node {
    //uint32_t id;              //can be replaced with    tree_node->list->contents->id
    struct tree_node* child;
    struct tree_node* parent;
    struct tree_node* next;     //will use to determine size
    list_node* list;

}tree_node;


record_st* read_line(int argc, char* argv[], FILE* fp) {

    if (argc != 2) {
        printf("You called to many or to few arguments!");
        return NULL;
    }

    if (fp == NULL) {
        printf("Error acessing your file!");
        return NULL;
    }

    record_st* node = (record_st*)calloc(1, sizeof(record_st));     //using calloc so all values are initialized as 0

    if (node != NULL) {
        if (fscanf(fp, " %d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%d;%[^\n]", &node->id, node->firstname, node->surname, node->birthdate, node->died, node->country, node->countryCode, node->city, node->gender, &node->year, node->category, &node->share, node->motivation) == 0) {
            return NULL;        //if fscanf returns 0 means we are at the end of the file
        }
        else {
            printf("Read node with id = %d.\n", node->id);
            return node;
        }
    }
    printf("Error allocating memory.");
    return NULL;
}

int arr_full(tree_node* arr) {
    int size = 0;

    for (; arr->next != NULL; arr = arr->next) {
        size++;
    }
    size++;

    if (size > M) {
        return 1;
    }
    return 0;
}

int list_full(list_node* list_position) {
    int size = 0;

    while (list_position->next != NULL) {
        size++;
    }

    size++;

    if (size > L) {
        return 1;
    }
    return 0;
}

void arr_divide(tree_node* arr) {//, tree_node* parent
    //max size of arr = 5 (idx = 4)
    //if we have to split, arr = 6, idx of division = 2
    //size of arr / 2  - 1 = idx of division
    //size of arr = M + 1

    int idx = ((M + 1) / 2) - 1;//it will be the next one after the parent DUMBASS

    tree_node* new_arr = (tree_node*)calloc(M, sizeof(tree_node));//change to M+1
    if (new_arr == NULL) {
        printf("Error allocating memory.");
        return;//return NULL or just return?
    }

    (&arr)[idx]->next = NULL;
    (&new_arr)[idx]->next = NULL;

    if (arr->parent == NULL) {//if theres no parent i.e. its the root arr
        tree_node* new_parent = (tree_node*)calloc(M, sizeof(tree_node));//change to M+1
        if (new_parent == NULL) {
            printf("Error allocating memory.");
            return;//return NULL or just return?
        }
        arr->parent = (&new_parent)[0];
        new_arr->parent = (&new_parent)[1];

    }
    else {//if its not the root arr
        tree_node* next_node = (tree_node*)calloc(1, sizeof(tree_node));
        if (next_node == NULL) {
            printf("Error allocating memory.");
            return;
        }
        if (arr->parent->next != NULL) {//still have to account for when this list itself is full
            arr->parent->next = next_node;
            arr->parent->next->child = new_arr;
            new_arr->parent = arr->parent->next;
            new_arr->parent->next = next_node;
        }
        else {//arr->parent->next == NULL
            next_node = arr->parent->next;
            arr->parent->next = new_arr;
            new_arr->next = next_node;
        }
        if (arr_full(arr->parent) == 1) {
            arr_divide(arr->parent);
        }
    }
    return;
}

void list_divide(list_node* list_position, tree_node* arr) {//needs revision
    tree_node* parent = (tree_node*)calloc(1, sizeof(tree_node));

    if (parent == NULL) {
        printf("Error allocating memory.");
        return;
    }

    parent->list = list_position;//this is a new parent to the list not the actual one gotta fix this

    list_node* split_list = list_position;
    //list_node* split_list = list_position->next->next->next;      // 1   ->  2  ->   3   ->    4       5        6

    for (int i = 0; i != ((L + 1) / 2); i++) {
        split_list = split_list->next;
    }

    split_list->prev = NULL;
    //split_list->


    (&list_position)[((L + 1) / 2) - 1]->next = NULL;//6/2  3  -  1    2 idx = 2 so 3 elem                          1   2   3   4   5   6

    tree_node* moved_elem = parent->next;
    parent->next->list = split_list;

    parent->next->next = moved_elem;


    //divide the arr if its full
    if (arr_full(arr) == 1) {
        arr_divide(arr);
    }
    return;
}


void add_node(record_st* node, list_node* list_position, list_node* node_position, tree_node arr[]) {//node position can equal NULL
    //first add node then reorganize
    list_node* new_elem = (list_node*)calloc(1, sizeof(list_node));

    if (new_elem != NULL) {                //           1   2   3    4  new_ndoe  5->ndoe position

        new_elem->contents = node;
        new_elem->prev = node_position->prev;
        new_elem->next = node_position;

        node_position->prev->next = new_elem;
        node_position->prev = new_elem;



        if (list_full(list_position) == 1) {//we will have to divide the list in 2 and then go to the parent and add a new one
            //divide
            //3 will stay in the current node 3 will go to the next available space
            list_divide(list_position, arr);
        }
        return;
    }
    return;
}


int insert_node(record_st* node, tree_node* arr, list_node* list) {
    if (node == NULL) { //we are at the end of the file
        return 0;
    }
    //check how many array ahs so we can add the first few

    int elems_in_arr = 1;
    //tree_node* pt = (&arr)[0]; pt->next != NULL; pt = pt->next
    for (int i = 0; i != L; i++) {
        if ((&arr)[i]->list->contents != NULL) {
            elems_in_arr++;
        }
    }

    if (elems_in_arr == 0) {
        printf("First element added.");
        (&arr)[0]->list = list;
        (&arr)[0]->list->contents = node;
        (&arr)[0]->child = NULL;
        (&arr)[0]->next = NULL;
        (&arr)[0]->parent = NULL;
        return 1;
    }
    else {
        int idx;

        if ((&arr[0])->child == NULL) {//is leaf?
            printf("Found leaf.\n");
            //checking last tree node, this will point  to linked lists
            for (int i = 0; i != M; i++) {//iterate trough linked list with the ids of the actual information
                if ((&arr)[i]->list->contents->id != NULL) {
                    if (node->id < (&arr[i])->list->contents->id) {//if the nodes id wich we wanna insert is smaller then the i element of the list
                        idx = i - 1;
                        break;
                    }
                    else {
                        idx = i;//no break because it will be the last option either way
                    }
                }
                else {
                    idx = i;
                }
            }

            list_node* list_position = (&arr)[idx]->list;//will indicate where list is in the tree
            list_node* node_position = (&arr)[idx]->list;//will indicate where node will go in the list

            for (; node_position->next != NULL; node_position = node_position->next) {
                if (node->id < node_position->next->contents->id) {
                    add_node(node, list_position, node_position, arr);
                    //if true we know that current list node is the correct one
                    //else its gonna be the last
                    return 1;//anything different then 0 will work as a return value
                }
            }
            //           1      2       3       4       5
            node_position = node_position->next;//will equal NULL since its the last elem
            add_node(node, list_position, node_position, arr);
            return 1;
        }
        else {
            printf("Didn't find leaf node\n");
            for (int i = 0; i != M; i++) {
                if (node->id < (&arr[i])->list->contents->id) {
                    idx = i - 1;
                    break;
                }
                else {
                    idx = i;
                }
            }
            arr = (&arr[idx])->child;
            insert_node(node, arr, list);
            return 1;
        }
    }
    return 0;
}


int main(int argc, char* argv[]) {  //fazer ficheiro de saida com os nodes organizados desde o menor ate ao maior

    tree_node* root_arr = (tree_node*)calloc(M, sizeof(tree_node));//might have to be M+1 cause we will add an extra element from time to time
    list_node* root_list = (list_node*)calloc(L, sizeof(list_node));//might have to be L + 1
    FILE* fp = fopen(argv[1], "r+");

    //first fill the initial array and its leaf nodes
    //then complete the more complex mid tree arrays and leaf nodes

    int output = -1;
    while (output != 0) {
        output = insert_node(read_line(argc, argv, fp), root_arr, root_list);
    }

    //print_results();

    return 0;
}