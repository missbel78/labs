// notebook.cpp: ���������� ����� ����� ��� ����������� ����������.
//

// #include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

// ���������� �������� � ������� � hsize  ��� ������, ��� ��� ������ � ������� �������� (��� � ����� �������).
// ��� ��������� � � �������, � � ������.

// ������� ������
struct TNode
{
	char name[100], val[100];

	TNode *next;

	TNode( char* _n, char* _v )
	{
		strcpy_s( name, _n );
		strcpy_s( val, _v );

		next = NULL;
	}
};

// �����
class TList
{
public:
	// ������ � ����� ������
	TNode *root, *last;

	TList()
	{
		root = NULL;
		last = NULL;
	}

	// �������� � �����
	void add( char *name, char *val )
	{
		TNode *node = new TNode( name, val );

		if (root == NULL)
			root = node;
		else
			last->next = node; // */

		last = node;
	}
	
	// ����� ������ �� �����
	void print()
	{
		printf( "  List:\n" );

		TNode *n = root;
		while (n != NULL)
		{
			printf( "    %s: %s\n", n->name, n->val );

			n = n->next;
		}
	}

	// ����� �� ���� name
	TNode* findbyname( char* v )
	{
	  TNode *n = root;

	  while (n != NULL)
	  {
		  if (strcmp( n->name, v ) == 0) return n;
		// c++;
		n = n->next;
	  }
	  return NULL;
	}
};

int calcHash( char *s )
{
	int i, sum = 0;

	// ������ ��������� ��� ����� �� ������ 100
	for( i = 0; s[i] != 0; i++ )
		sum = (sum * 2 + (unsigned char) s[i]) % 100;

	return sum;
}

const int hsize = 10;

int main(void)
{
	char buf[100];
	int i, h;
	TList* lists[hsize];

	for( i = 0; i < hsize; i++ )
		lists[i] = new TList();

	while (true)
	{
		printf( "Enter: " );
		gets_s( buf );

		char* p[10], *t;
	
		// ��������� ������� ����� �� �����
		p[0] = strtok_s( buf, " \n", &t );
		p[1] = strtok_s( NULL, " \n", &t );
		p[2] = strtok_s( NULL, " \n", &t );

		// �����
		if (strcmp( p[0], "exit" ) == 0)
			break;

		// ���������� ��� ����
		if (strcmp( p[0], "printall" ) == 0)
		{
			for( i = 0; i < hsize; i++ )
				if (lists[i]->root != 0)
				{
					printf( "Hash %d\n", i );
					lists[i]->print();
				}
			continue;
		}
		
		if (p[1] == NULL) continue;

		// ��������� ���
		h = calcHash( p[1] ) % hsize;
		TNode *n = lists[h]->findbyname( p[1] );

		// �������
		if (strcmp( p[0], "insert" ) == 0)
		{
			if (n == NULL)
			{
				lists[h]->add( p[1], p[2] );
				printf( "OK\n" );
			}
			else
			{
				printf( "Changed. Old value = %s\n", n->val );
				strcpy_s( n->val, p[2] );
			}
		}
		
		// �����
		if (strcmp( p[0], "find" ) == 0)
		{
			if (n == NULL)
				printf( "NO\n" );
			else
				printf( "%s\n", n->val );
		}
	}

	return 0;
}

