#include"akinator.hpp"
#include"Akinator_Data/akinator_data.hpp"
#include"Scanf_Tree/Akinator_Parser.hpp"

#define DATA_FILE "akinator_data.txt"

int main()
{
    FILE* f = fopen(DATA_FILE, "r");
    Akinator_Parser pars(f);
    Tree* tree = pars.Get_Tree();
    fclose(f);

    bool quite = false;
    char answer[5];

    while(!quite)
    {
        do
        {
            printf("\nНовая игра?:Yes/No\n");

            if(!get_answer(answer))
                printf("\nНекорректный ответ\n");
            else
                break;
        }while(1);

        if(answer[0]=='Y')
            akinator(tree);

        if(answer[0]=='N')
            quite = true;
    }


    f = fopen(DATA_FILE, "w");
    Tree_Save(tree, f);
    fclose(f);

    Tree_Destroy(tree);
    return 0;
}
