#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

#include"Akinator_Data/akinator_data.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

static Tree* init_new_part_of_tree(char* added_element);
static bool IsQuestion(Tree* current);
static Tree* copy_leaf(Tree* current);
static void add_new_element(Tree* current,char* added_element, char* added_question);
bool get_answer(char* answer);
void akinator(Tree* current);

#endif // AKINATOR_HPP_INCLUDED
