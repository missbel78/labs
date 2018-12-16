#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

//Структура бинарного дерева
struct Node {
	int item;
	Node *left;
	Node *right;
	Node(int a) {
		item = a;
		left = NULL;
		right = NULL;
	}
};

//добавление нового элемента в дерево
Node* Add(Node* head, int item) {
	if (!head) {
		head = new Node(item);
	}
	else
		if (head->item > item) {
			head->left = Add(head->left, item);
		}
		else {
			head->right = Add(head->right, item);
		}
	return head;
}

//функция которую передаем в traverse
void f(int* item, int depth) {
	*item += depth;
}

//префиксный вывод дерева
void traverse(Node* head, void(*f)(int*,int),int lvl = 0) {
	if (!head) return;
	else {
		f(&head->item, lvl); //прибавляем к элементу его глубину
		traverse(head->left, f, lvl + 1);
		traverse(head->right, f, lvl + 1);
	}
}

//печать дерева в префиксном виде
void print(Node* head, int lvl = 0) {
	if (!head) return;
	else {
		for (int i = 0; i < lvl; i++) printf("  ");
		printf("%d\n", head->item);
		print(head->left, lvl + 1);
		print(head->right, lvl + 1);
	}
}

//главный поток исполнения
int main() {
	
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);

	int n = 0;
	printf("Укажите кол-во элементов в дереве -> ");
	scanf("%d", &n);
	Node* head = NULL;

	//рандомно заполняем
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		head = Add(head, rand()%10);
	}

	printf("\nДерево до изменения:\n");
	print(head);

	traverse(head, f);

	printf("\nПосле:\n");
	print(head);


	system("pause"); //чтобы консоль сразу не закрывалась
	return 0;
}
