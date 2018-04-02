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
void Tree_Destroy(Tree* current);

#endif // AKINATOR_DATA_HPP_INCLUDED
