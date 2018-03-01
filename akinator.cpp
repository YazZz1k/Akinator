#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stack>
using namespace std;

#define DATA_FILE "akinator_data.txt"

typedef struct tree
{
    struct tree *no,
                *yes;
    char* question;
} Tree;

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

void skip_words(FILE* file)
{
    char str[100];
    fscanf(file, "%[^()]", str);
}

void skip_brackets(FILE* file)
{
    char c = getc(file);

    assert(c=='(');

    int brace = 1;
    while(brace)
    {
        c = getc(file);
        if(c == '(') brace++;
        if(c == ')') brace--;
    }
}

bool find_new_start_positions(unsigned long int *left_start_position, unsigned long int *right_start_position, unsigned long int start_position, FILE* file)
{
    fseek(file, start_position, SEEK_SET);

    skip_words(file);

    if(getc(file) != '(')
        return false;
    else
    {
        ungetc('(', file);

        *left_start_position = ftell(file)+1;

        skip_brackets(file);

        *right_start_position = ftell(file)+1;
        return true;
    }
}

Tree* _Tree_Read(unsigned long int start_position, FILE* file)
{
    char question[100];
    unsigned long int left_start_position = 0,
                     right_start_position = 0;

    fseek(file, start_position, SEEK_SET);

    fscanf(file, "%[^()]", question);

    Tree* ret = init_new_part_of_tree(question);

    if(find_new_start_positions(&left_start_position, &right_start_position, start_position, file))
    {
        ret->yes = _Tree_Read( left_start_position, file);
        ret->no  = _Tree_Read(right_start_position, file);
    }

    return ret;
}

Tree* Tree_Read(FILE* file)
{
    unsigned long int start_position = 0;

    return _Tree_Read(start_position, file);
}

void Tree_Save(Tree* current, FILE* file) //сначала левое, потом - правое
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

Tree* copy(Tree* current)
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

	new_no  = copy(current);
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

	Tree_Destroy(tree);
	return 0;
}

