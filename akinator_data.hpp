#ifndef AKINATOR_DATA_HPP_INCLUDED
#define AKINATOR_DATA_HPP_INCLUDED

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>

typedef struct tree
{
    struct tree *no,
                *yes;
    char* question;
} Tree;

static Tree* init_new_part_of_tree(char* added_element);
static bool IsQuestion(Tree* current);
void Tree_Save(Tree* current, FILE* file);
void skip_words(FILE* file);
void skip_brackets(FILE* file);
bool find_new_start_positions(unsigned long int *left_start_position, unsigned long int *right_start_position, unsigned long int start_position, FILE* file);
Tree* _Tree_Read(unsigned long int start_position, FILE* file);
Tree* Tree_Read(FILE* file);

#endif // AKINATOR_DATA_HPP_INCLUDED
