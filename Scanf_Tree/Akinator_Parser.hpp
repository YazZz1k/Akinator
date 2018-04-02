#ifndef __AKINATOR__PARSER__
#define __AKINATOR__PARSER__


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"../Akinator_Data/akinator_data.hpp"

Tree* Create_Tree(char* queston, Tree* left, Tree* right);


class Akinator_Parser
{
    private:
        FILE* file;
        bool  Get_Error;
    public:
        Akinator_Parser(FILE* _file);
        Akinator_Parser(const char* adress_file);
        ~Akinator_Parser();
        Tree* Get_Tree();
    public:
        int scanf_string(char* str);
        char* Get_String();
        Tree* Get_Child();
        void Error();
};

#endif



