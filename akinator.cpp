#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<queue>
#include<locale.h>
using namespace std;

#define DATA_FILE "akinator_data.txt"



/* TODO
   Переписать алгоритм заполнения и вывода
   Убрать scanf'ы
*/

struct tree
{
    char* question;
    struct tree* yes;
	struct tree* no;
};

typedef struct tree Tree;

typedef enum{ANSWER, QUESTION, EMPTY} Type_String;
bool IsQuestion(Tree*);
Tree* init_new_part_of_tree(char* added_element);

//чассть кода, отвечающая за хранение и заполнение дерева

void tree_save(Tree* current, FILE* out)
{
	assert(current != NULL);
	assert(out     != NULL);

	bool EndTree = false;
	queue<Tree*> tree_queue;

	tree_queue.push(current);

	int i = 1;
	int count_of_strings = 0;

	fprintf(out, "           \n");
	do
	{
		EndTree = true;
		for(int j=0; j<i; j++)
		{
			current = tree_queue.front();
			tree_queue.pop();
			if(current != NULL)
			{
				if(IsQuestion(current))
				{
					EndTree = false;
					tree_queue.push(current->yes);
					tree_queue.push(current->no);
					fprintf(out, "%s:q ", current->question);
				}
				else
				{
					tree_queue.push(NULL);
					tree_queue.push(NULL);
					fprintf(out, "%s:a ", current->question);
				}
			}
			else
			{
				fprintf(out, ":e ");
				tree_queue.push(NULL);
				tree_queue.push(NULL);
			}
		}
		fprintf(out,"\n");
		i = 2*i;
		count_of_strings++;
	}
	while(!EndTree);

	fseek(out, 0, SEEK_SET);

	fprintf(out, "%d", count_of_strings);
}


void replase_question(Tree* tree, char* new_question)
{
	int i=0;
	while(new_question[i]!='\0')
	{
		tree->question[i] = new_question[i];
		i++;
	}
	tree->question[i]='\0';
}

Type_String get_Type_String(char* added)
{
	int i=0;
	while(added[i]!='\0')
	{
		i++;
	}

	added[i-2] = '\0';

	switch(added[i-1])
	{
		case 'q': return QUESTION;
		case 'a': return ANSWER;
		case 'e': return EMPTY;
	}
}

Tree* tree_init(FILE* in)
{
	Tree *new_tree = init_new_part_of_tree("");;
	Tree *current;

	char* added = new char [1000];

	queue<Tree*> tree_queue;
	tree_queue.push(new_tree);

	int count_of_strings,
	    count_ = 0;

	fscanf(in, "%d\n", &count_of_strings);

	int i = 1;
	while(count_ != count_of_strings)
	{
		for(int j=0; j<i; j++)
		{
			current = tree_queue.front();
			tree_queue.pop();

			fscanf(in, "%s ", added);

			switch(get_Type_String(added)) //возвращает тип строки и удаляет символ, позволяющий распознать строку
			{
				case ANSWER:
					replase_question(current, added);
					tree_queue.push(NULL);
					tree_queue.push(NULL);
					break;
				case QUESTION:
					replase_question(current, added);
					current->yes = init_new_part_of_tree("");
					current->no  = init_new_part_of_tree("");
					tree_queue.push(current->yes);
					tree_queue.push(current->no);
					break;
				case EMPTY:
				    	assert(NULL == current);
				    	tree_queue.push(NULL);
					tree_queue.push(NULL);
					break;
			}
		}
		i = 2*i;
		count_++;
	}

	delete [] added;
	return new_tree;
}

//часть кода, отвечающая за основную чась
void clean_stdin()
{
	while(getchar() != '\n');
}

bool IsQuestion(Tree* current)
{
	assert(current != NULL);
	assert(!((current->no != NULL)&&(current->yes == NULL)));
	assert(!((current->yes!= NULL)&&(current->no  == NULL)));
	return current->yes;
}


Tree* init_new_part_of_tree(char* added_element)
{
	Tree* init_tree = (Tree*)malloc(sizeof(Tree));
	init_tree->question = (char*)malloc(500*sizeof(char));

	if((NULL == init_tree)||(NULL == init_tree->question))
        {
                printf("Memory Error");
                return NULL;
        }
	replase_question(init_tree, added_element);
	init_tree->no  = NULL;
	init_tree->yes = NULL;

	return init_tree;
}


Tree* copy(Tree* current)
{
	assert(current != NULL);
	Tree* copy_tree = (Tree*)malloc(sizeof(Tree));

	if(NULL == copy_tree)
	{
		printf("Memory Error");
		return NULL;
	}

	copy_tree->question = current->question;
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

	current->question = added_question;
	current->no  = new_no;
	current->yes = new_yes;
}


void akinator(Tree* current)
{
	setlocale(0, "RUS");

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
			scanf("%s", added_element);
			printf("В чём разница между %s и %s?\n", added_element, current->question); //предполагает ответ вида "<описание нового элемента>"
			scanf("%s", added_question);
			add_new_element(current, added_element, added_question);
		}

		if('Y' == answer)
		{
			printf("LOL, UGADAL ZAEBIS\n");
		}
	}
}


int main()
{
	FILE* f = fopen(DATA_FILE, "r");
	Tree* new_tree = tree_init(f);
	fclose(f);

	akinator(new_tree);

	f = fopen(DATA_FILE, "w");
	tree_save(new_tree, f);
	fclose(f);
	return 0;
}
