#include"akinator.hpp"
#include"akinator_data.hpp"

#define DATA_FILE "akinator_data.txt"

int main()
{
	FILE* f = fopen(DATA_FILE, "r");
    Tree* tree = Tree_Read(f);
    fclose(f);

    bool quite = false;
    char answer[5];

    while(!quite)
	{
	    do
        {
            printf("\nNEW GAME?:Y/N\n");
        }
        while(!get_answer(answer));

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
