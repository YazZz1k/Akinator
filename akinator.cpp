#include"akinator.hpp"

#include<string.h>

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


static Tree* copy_leaf(Tree* current)
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


static void add_new_element(Tree* current,char* added_element, char* added_question)
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


bool get_answer(char* answer)
{
    fgets(answer, 6, stdin);

    if((strlen(answer)!=3)&&(strlen(answer)!=4))
    {
        while(getchar() != '\n'){}
        return false;
    }

    //printf("Out of cicle fgets\n");

    if(((answer[0] =='Y')||(answer[0] =='y'))&&((answer[1] =='E')||(answer[1] =='e'))&&((answer[2] =='S')||(answer[2] =='s')))
    {
        answer[0]='Y';
        answer[1]='E';
        answer[2]='S';
        answer[3]='\0';
        return true;
    }

    if(((answer[0] =='N')||(answer[0] =='n'))&&((answer[1] =='O')||(answer[1] =='o'))&&answer[2] == '\n')
    {
        answer[0]='N';
        answer[1]='O';
        answer[2]='\0';
        return true;
    }

    return false;
}


void akinator(Tree* current)
{
    char answer[10],
         added_element[1000],
         added_question[1000];

    if(IsQuestion(current))
    {
        do
        {
            printf("%s?\n", current->question);
            printf("Ответ: Yes/No\n");
        }
        while(!get_answer(answer));

        current = (answer[0] == 'Y')?(current->yes):(current->no);
        akinator(current);
    }
    else
    {
        printf("Это %s?\n", current->question);
        printf("Ответ: Yes/No\n");

        get_answer(answer);

        if('N' == answer[0])
        {
            printf("Что же это?\n");
            scanf("%[^\n]", added_element);
            getchar();

            printf("Чем отличается %s от %s?\n", added_element, current->question);
            scanf("%[^\n]", added_question);
            getchar();

            add_new_element(current, added_element, added_question);
        }

        if('Y' == answer[0])
        {
            printf("Угадано\n");
        }
    }
}


