#include"akinator_data.hpp"

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



