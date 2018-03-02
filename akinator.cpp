#include"akinator_data.hpp"

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stack>
using namespace std;

#define DATA_FILE "akinator_data.txt"


/*typedef struct tree
{
    struct tree *no,
                *yes;
    char* question;
} Tree;*/


Tree* init_new_part_of_tree(char* added_element)
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


bool IsQuestion(Tree* current)
{
	assert(current != NULL);
	assert(!((current->no != NULL)&&(current->yes == NULL)));
	assert(!((current->yes!= NULL)&&(current->no  == NULL)));
	return current->yes;
}


Tree* copy_leaf(Tree* current)
{
	assert(current != NULL);
	Tree* copy_tree = new Tree;

	if(NULL == copy_tree)
	{
		printf("Memory Error");
		return NULL;
	}

	copy_tree->question = new char [100];
	strcpy(copy_tree->question,current->question);
	copy_tree->no  = NULL;
	copy_tree->yes = NULL;

	return copy_tree;
}


void add_new_element(Tree* current,char* added_element, char* added_question)
{
	assert(current != NULL);

	Tree *new_yes,
	     *new_no;

	new_no  = copy_leaf(current);
	new_yes = init_new_part_of_tree(added_element);

	strcpy(current->question, added_question);
	current->no  = new_no;
	current->yes = new_yes;
}


void clean_stdin()
{
	while(getchar() != '\n');
}


void akinator(Tree* current)
{
	char answer,
	     added_element[1000],
	     added_question[1000];

	if(IsQuestion(current))
	{
		do
		{
			printf("%s?\n", current->question);
			printf("Ответ: Y/N\n");
			answer = getchar();
			clean_stdin();
		}
		while(((answer != 'Y')&&(answer != 'N')));

		current = (answer == 'Y')?(current->yes):(current->no);
		akinator(current);
	}
	else
	{
		printf("Это %s?: Y/N\n", current->question);
		answer = getchar();
		clean_stdin();

		if('N' == answer)
		{
			printf("Что же это?\n");
			scanf("%[^\n]", added_element);
			clean_stdin();
			printf("В чём разница между %s и %s?\n", added_element, current->question); //предполагает ответ вида "<описание нового элемента>"
			scanf("%[^\n]", added_question);
			clean_stdin();
			add_new_element(current, added_element, added_question);
		}

		if('Y' == answer)
		{
			printf("LOL, UGADAL\n");
		}
	}
}

int main()
{
	FILE* f = fopen(DATA_FILE, "r");
    Tree* tree = Tree_Read(f);
    fclose(f);

    bool quite = false;
    char answer;

    while(!quite)
	{
	    do
        {
            printf("\nNEW GAME?:Y/N\n");

            answer = getchar();

            clean_stdin();
        }
        while((answer!='Y')&&(answer!='N'));

        if(answer=='Y')
            akinator(tree);

        if(answer=='N')
            quite = true;
    }


	f = fopen(DATA_FILE, "w");
	Tree_Save(tree, f);
    fclose(f);

	//Tree_Destroy(tree);
	return 0;
}

