/*
 * This is task about: Double-linked list
 * Author: Белоусова Ольга
 * Computational complexity: 0(n)
 * Memory usage: 0(1)
 */

#include <stdio.h>
#include <stdlib.h>

//Объявляем структуру элемента двусвязного элемента
typedef struct Node
{
	struct Node* next; //Указатель на следующий элемент
	struct Node* prev; //Указатель на предыдущий
	int value; //Значение
} Node;

//Функция выделет память под элемент массива
Node* GetNewNode(int value)
{
	Node* newNode = (Node*)(malloc(sizeof(Node)));
	if (newNode == NULL)
		return NULL;

	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->value = value;

	return newNode;
}

//Функция создаёт новый пустой список
Node* list_new()
{
	return NULL;
}

/*Если любая из функций ниже возвращает 0, то этого говорит о том, что произошла ошибка 1 - работа выполнена успешно*/

//Добавляет элемент в конец списка
int push(Node** list, int value)
{
	if (*list == NULL) {
		*list = GetNewNode(value);
		if (*list == NULL)
			return 0;
		else
			return 1;
	}

	Node* ptr = *list;
	while (ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = GetNewNode(value);
	if (ptr->next == NULL)
		return 0;

	ptr->next->prev = ptr;

	return 1;
}

//Функция удаляет полседний элемент из списка
int pop(Node** list, int* value)
{
	if (*list == NULL)
		return 0;

	if ((*list)->next == NULL) {
		if ((*list)->prev == NULL) {
			*value = (*list)->value;
			*list = NULL;
		}
		else {
			Node* ptr = (*list)->prev;
			ptr->next = NULL;

			*value = (*list)->value;
			free(*list);
			*list = ptr;
		}
		return 1;
	}

	Node* ptr = *list;
	while (ptr->next != NULL)
		ptr = ptr->next;

	*value = ptr->value;

	free(ptr);

	return 1;
}

//Добавить в начало списка 1 элемент
int unshift(Node** list, int value)
{
	if (*list == NULL) {
		*list = GetNewNode(value);
		if (*list == NULL)
			return 0;
		else
			return 1;
	}

	Node* ptr = *list;
	while (ptr->prev != NULL)
		ptr = ptr->prev;

	ptr->prev = GetNewNode(value);
	if (ptr->prev == NULL)
		return 0;

	ptr->prev->next = ptr;

	return 1;
}


//Удалить из начала списка элемент
int shift(Node** list, int* value)
{
	if (*list == NULL)
		return 0;

	if ((*list)->prev == NULL) {
		if ((*list)->next == NULL) {
			*value = (*list)->value;
			free(*list);
			*list = NULL;
		}
		else {
			Node* ptr = (*list)->next;
			ptr->prev = NULL;

			*value = (*list)->value;
			free(*list);

			*list = ptr;
		}
		return 1;
	}

	Node* ptr = *list;
	while (ptr->prev != NULL)
		ptr = ptr->prev;

	ptr->next->prev = NULL;

	*value = ptr->value;

	free(ptr);

	return 1;
}

//Инвертрировать список
int reverse(Node** list)
{
	if (*list == NULL)
		return 0;
	//Если в списке всего 1 елемент, то его перевернуть(инвертировать)
	if ((*list)->prev == NULL && (*list)->next == NULL)
		return 0;

	Node* begin = *list;
	while (begin->prev != NULL)
		begin = begin->prev;

	Node* end = *list;
	while (end->next != NULL)
		end = end->next;

	while (end != begin)
	{
		int buffer = begin->value;
		begin->value = end->value;
		end->value = buffer;

		if (begin->next == end || end->prev == begin)
			break;

		begin = begin->next;
		end = end->prev;
	}

	return 1;
}

//Функция удаляет существующий список
int list_delete(Node** list)
{
	if (*list == NULL)
		return 0;

	Node* ptr = *list;
	while (ptr->prev != NULL)
		ptr = ptr->prev;

	while (ptr != NULL)
	{
		*list = ptr;
		ptr = ptr->next;
		free(*list);
	}

	*list = NULL;

	return 1;
}


int main(int argc, char** argv)
{
	Node* list = list_new();

	for (int i = 0; i < 9; i++)
		push(&list, i);

	reverse(&list);

	int buffer;

	//while (list != NULL) {
	//	shift(&list, &buffer);
	//	printf("%d ", buffer);
	//}

	Node* ptr = list;
	while (ptr != NULL)
	{
		printf("%d ", ptr->value);
		ptr = ptr->next;
	}

	list_delete(&list);

	getchar();

	return 0;
}


