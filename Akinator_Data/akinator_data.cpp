#include"akinator_data.hpp"

#include<stdio.h>

static Tree* init_new_part_of_tree(char* added_element)
{
	Tree* init_tree = new tree;
	init_tree->question = new char [100];

	if((NULL == init_tree)||(NULL == init_tree->question))
    {
            printf("Memory Error");
            return NULL;
    }

	strcpy(init_tree->question, added_element);

	init_tree->no  = NULL;
	init_tree->yes = NULL;
	return init_tree;
}


static bool IsQuestion(Tree* current)
{
	assert(current != NULL);
	assert(!((current->no != NULL)&&(current->yes == NULL)));
	assert(!((current->yes!= NULL)&&(current->no  == NULL)));
	return current->yes;
}


void Tree_Save(Tree* current, FILE* file)
{
    assert(current != NULL);

    fprintf(file, "%s", current->question);

    if(IsQuestion(current))
    {
        fprintf(file, "(");
        Tree_Save(current->yes, file);
        fprintf(file, ")(");
        Tree_Save(current->no, file);
        fprintf(file, ")");
    }
}


void Tree_Destroy(Tree* current)
{
    if(IsQuestion(current))
    {
        Tree_Destroy(current->no);
        Tree_Destroy(current->yes);
    }

    assert(current->question!=NULL);
    delete [] current->question;
    assert(current!=NULL);
    delete current ;
}

