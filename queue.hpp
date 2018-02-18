#include<stdlib.h>
#include<iostream>

template <typename T>
class Queue
{
	private:
		typedef struct list
		{
			struct list *before;
			T Data;
		}List;	
		
		List *first,
		     *last;
		
		bool _empty;

	public:
		Queue();
		~Queue();
		void push(const T);
		T pop();
		bool is_empty()
		{
			return _empty;
		}
};


template<typename T>
Queue<T>::Queue()
{
	first = NULL;
	last  = NULL;
	_empty= true;
}

template<typename T>
Queue<T>::~Queue()
{
	while(!_empty)
		pop();
}

template <typename T>
void Queue<T>::push(T added)
{
	List* added_list = new List [1];
	
	added_list->Data = added;
	added_list->before = NULL;
	if(_empty)
	{
		first = added_list;
		last  = added_list;
		_empty = false; 	
	}
	else
	{
	
		last->before = added_list;
		last = added_list;
	}
}

template <typename T>
T Queue<T>::pop()
{
	if(_empty)
	{
	}
	else
	{	
		if(first->before == NULL) _empty = true;
	
		T returned = first->Data;
		List *new_first = first->before;
		delete [] first;
		first = new_first;
		return returned;
	}
}

