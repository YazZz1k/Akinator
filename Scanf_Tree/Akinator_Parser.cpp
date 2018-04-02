#include"Akinator_Parser.hpp"

Tree* Create_Tree(char* str, Tree* yes, Tree* no)
{
    Tree* ret = new Tree;
    ret->question = str;
    ret->yes = yes;
    ret->no  = no;
}

//Ch->S(Ch)(Ch)
//S->string

Akinator_Parser::Akinator_Parser(FILE* _file)
{
    assert(file!=NULL);

    file = _file;
    Get_Error = false;
}


Akinator_Parser::~Akinator_Parser()
{

}

void Akinator_Parser::Error()
{
    Get_Error = true;
    printf("Error\n");
    assert(0);
}


Tree* Akinator_Parser::Get_Tree()
{
    return Get_Child();
}

Tree* Akinator_Parser::Get_Child()
{
    if(Get_Error) return NULL;

    char* str = Get_String();

    if(getc(file) == '(')
    {
        Tree* left = Get_Child();
        char sym = getc(file);

        if(sym == ')')
        {
            if(getc(file) == '(')
            {
                Tree* right = Get_Child();
                if(getc(file) == ')')
                    return Create_Tree(str, left, right);
                else Error();
            }
            else Error();
        }
        else Error();
    }
    else
    {
        ungetc(')', file);
        return Create_Tree(str, NULL, NULL);
    }
    return NULL;
}


int Akinator_Parser::scanf_string(char* ret_str)
{
    int i=0;

    char sym;

    sym = getc(file);
    while( (sym!= '(') && (sym!= ')') )
    {
        ret_str[i] = sym;
        sym = getc(file);
        if(i==99)
        {
            printf("Слишком большой вопрос\n");
            Error();
            return 0;
        }
        i++;
    }
    ungetc(sym, file);
    ret_str[i] = '\0';

    return i;
}


char* Akinator_Parser::Get_String()
{
    if(Get_Error) return NULL;

    char* ret_str = new char[100];
    if(!ret_str) printf("Memmory Error\n");

    int len = scanf_string(ret_str);

    if(!len)
        Error();
    else
        return ret_str;

    return NULL;
}

