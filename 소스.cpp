/*
*
*			소속		: 전북대학교 공과대학 소프트웨어 공학과
*			학번		: 201010624
*			이름		: 장영균
*			과제명		: 연결 리스트로 구현된 리스트 ADT 테스트 프로그램 작성
*
*/

//Headers
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

//Preprocessors
#define FALSE 0
#define TRUE 1


typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode *link;
} ListNode;

typedef struct
{
	ListNode *head;
	int length;
} LinkedListType;

//에러출력
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
}

//노드삽입
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL)
	{
		new_node->link = NULL;
		*phead = new_node;
	}

	else if (p == NULL)
	{
		new_node->link = *phead;
		*phead = new_node;
	} 
	
	else
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

//노드삭제
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if (p == NULL)
	{
		*phead = (*phead)->link;
	}

	else
	{
		p->link = removed->link;
	}

	free(removed);
}

//list에서 pos에 위치하는 노드반환
ListNode *get_node_at(LinkedListType *list, int pos)
{
	ListNode *tmp_node = list->head;

	if (pos < 0)
	{
		return NULL;
	}
	
	for (int i = 0; i < pos; i++)
	{
		tmp_node = tmp_node->link;
	}

	return tmp_node;
}

//list 길이 반환
int get_length(LinkedListType *list)
{
	return list->length;
}

//주어진 위치에 데이터 삽입
void add(LinkedListType *list, int position, element data)
{
	ListNode *p;
	if ((position >= 0) && position <= list->length)
	{
		ListNode *node = (ListNode*)malloc(sizeof(ListNode));

		if (node == NULL)
		{
			error("메모리 할당 에러");
		}
		node->data = data;
		p = get_node_at(list, position - 1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}

//list끝에 데이터 삽입
void add_last(LinkedListType *list, element data)
{
	add(list, get_length(list), data);
}

//list 처음에 데이터 삽입
void add_first(LinkedListType *list, element data)
{
	add(list, 0, data);
}

//list가 비었는지 확인
int is_empty(LinkedListType *list)
{
	if (list == NULL)
	{
		return 1;
	}
	else return 0;
}

//list에서 pos에 위치하는 데이터 삭제
void delete1(LinkedListType *list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length))
	{
		ListNode *p = get_node_at(list, pos - 1);
		
		remove_node(&(list->head), p, (p!=NULL) ? p->link:NULL);
		list->length--;
	}
}

//list에서 pos에 위치하는 데이터를 반환
element get_entry(LinkedListType *list, int pos)
{
	ListNode *p;

	if (pos >= list->length)
	{
		error("위치 오류");
	}
	p = get_node_at(list, pos);
	
	return p->data;
}

// list 비우기
void clear(LinkedListType *list)
{
	for (int i = 0; i < list->length; i++)
	{
		delete1(list, i);
	}
}

// 버퍼를 출력
void display(LinkedListType *list)
{
	ListNode *node = list->head;
	
	printf("( ");

	for (int i = 0; i < list->length; i++)
	{
		printf("%d ", node->data);
		node = node->link;
	}
	printf(" )\n");
}

// item인 노드를 찾기
int is_in_list(LinkedListType *list, element item)
{
	ListNode *p;
	p = list->head;

	while ((p!=NULL))
	{
		if (p->data == item)
		{
			break;
		}
		p = p->link;
	}

	if (p == NULL)
	{
		return FALSE;
	} 
	else return TRUE;
}

// list 초기화
void init(LinkedListType *list)
{
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}

int main()
{
	LinkedListType list1;

	init(&list1);
	add(&list1, 0, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);

	// list = (10, 20, 30, 40)
	display(&list1);

	delete1(&list1, 3);
	display(&list1);

	delete1(&list1, 0);
	display(&list1);
	

	printf("%s\n", is_in_list(&list1, 20)==TRUE? "성공":"실패");
	printf("%d\n", get_entry(&list1, 0));

	system("pause");
	return 0;
}