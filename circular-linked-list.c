/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node
{
	int key;
	struct Node *llink;
	struct Node *rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode **h);
int freeList(listNode *h);
int insertLast(listNode *h, int key);
int deleteLast(listNode *h);
int insertFirst(listNode *h, int key);
int deleteFirst(listNode *h);
int invertList(listNode *h);

int insertNode(listNode *h, int key);
int deleteNode(listNode *h, int key);

void printList(listNode *h);

int main()
{
	char command;
	int key;
	listNode *headnode = NULL;
	printf("----2022041025 길동현----");

	do
	{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z':
			initialize(&headnode);
			break;
		case 'p':
		case 'P':
			printList(headnode);
			break;
		case 'i':
		case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e':
		case 'E':
			deleteLast(headnode);
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't':
		case 'T':
			deleteFirst(headnode);
			break;
		case 'r':
		case 'R':
			invertList(headnode);
			break;
		case 'q':
		case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(listNode **h)
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode *)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode *h)
{
	listNode *prev = h;
	listNode *curr = h->rlink;

	while (curr != h)
	{						// h가 현재 노드에서 나갈때까지 반복
		free(prev);			// 전 노드를 메모리 해제
		prev = curr;		// 현재 노드를 이전 노드로 옮김
		curr = curr->rlink; // 현재 노드에 rlink를 불러옴
	}

	free(prev); // 전 노드 메모리 해제

	return 0;
}

void printList(listNode *h)
{
	int i = 0;
	listNode *p;

	printf("\n---PRINT\n");

	if (h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h)
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h)
	{
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode *h, int key)
{
	listNode *newNode = (listNode *)malloc(sizeof(listNode)); // newNodes 동적메모리 할당
	newNode->key = key;
	if (h->rlink == h)
	{						// 리스트가 비어있을때
		h->rlink = newNode; // newNode로 변경
		h->llink = newNode;
		newNode->rlink = h; // 노드가 h를
		newNode->llink = h;
	}
	else
	{
		listNode *lastNode = h->llink; // lastNode에 h의 왼쪽링크를 할당
		lastNode->rlink = newNode;	   // lastNode의 오른쪽 링크가 newNode로 업데이트
		newNode->llink = lastNode;	   // newNode의 왼쪽 링크가 lastNode를 가리킴
		newNode->rlink = h;			   // newNode의 오른쪽 링크가 h를 가리킴
		h->llink = newNode;			   // h의 왼쪽링크가 newNode를 가리킴
	}

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode *h)
{
	if (h->rlink == h)
	{ // 리스트가 비어있을때
		printf("List is empty. Cannot delete.\n");
		return 0;
	}

	listNode *lastNode = h->llink;		  // lastNode에 h의 왼쪽링크 할당
	listNode *prevNode = lastNode->llink; // prevNode에  lastNode의 왼쪽링크 할당

	prevNode->rlink = h; // prevNode의 오른쪽 링크가 h를 가리킴
	h->llink = prevNode; // h의 왼쪽링크가 prevNode를 가리킴
	free(lastNode);		 // lastNode의 메모리 해제

	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode *h, int key)
{
	listNode *newNode = (listNode *)malloc(sizeof(listNode));
	newNode->key = key;

	if (h->rlink == h)
	{						// 리스트가 비어있을때
		h->rlink = newNode; // h의 오른쪽 링크가 newNode를 가리킴
		h->llink = newNode; // h의 왼쪽 링크가 newNode를 가리킴
		newNode->rlink = h; // newNode의 오른쪽 링크가 h를 가리킴
		newNode->llink = h; // newNode의 왼쪽링크가 h를 가리킴
	}
	else
	{
		listNode *firstNode = h->rlink; // firstNode에 h의 오른쪽링크 할당
		firstNode->llink = newNode;		// firstNode의 왼쪽링크가 newNode를 가리킴
		newNode->rlink = firstNode;		// newNode의 rlink가 firstNode를 가리킴
		newNode->llink = h;				// newNode의 llink가 h를 가리킴
		h->rlink = newNode;				// h의 rlink가 newNode를 가리킴
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode *h)
{
	if (h->rlink == h)
	{ // 리스트가 비어있을때
		printf("List is empty. Cannot delete.\n");
		return 0;
	}

	listNode *firstNode = h->rlink;		   // firstNode에 h의 rlink 할당
	listNode *nextNode = firstNode->rlink; // nextNode에 firstNode의 rlink값 할당

	nextNode->llink = h; // nextNode의 llink가 h를 가리킴
	h->rlink = nextNode; // h의 rlink가 nextNode를 가리킴
	free(firstNode);	 // firstNode의 메모리 해제

	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode *h)
{
	if (h->rlink == h)
	{ // List is empty or has only one node
		printf("List is empty or has only one node. Cannot invert.\n");
		return 0;
	}

	listNode *currNode = h;
	listNode *nextNode;
	do
	{
		nextNode = currNode->rlink;		   // nextNode에 currNode의 rlink 할당
		currNode->rlink = currNode->llink; // currNode의 rlink에 currNode의 llink 할당
		currNode->llink = nextNode;		   // currNode의 llink가 nextNode를 가리킴
		currNode = nextNode;			   // currNode에 nextNode할당
	} while (currNode != h);
	h->rlink = h->llink; // h의 rlink에 h의 llink 할당
	h->llink = currNode; // h의 llink가 currNode 가리킴

	return 1;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode *h, int key)
{
	listNode *newNode = (listNode *)malloc(sizeof(listNode));
	newNode->key = key; // newNode의 key를 비움
	if (h->rlink == h)
	{						// 리스트가 비어있다면
		h->rlink = newNode; // h의 rlink가 newNode 가리키게 함
		h->llink = newNode; // h의 llink가 newNode 가리키게 함
		newNode->rlink = h; // newNode의 rlink가 h를 가리킴
		newNode->llink = h; // newNode의 llink가 h를 가리킴
		return 1;
	}
	listNode *currNode = h->rlink; // currNode에 h의 rlink 할당
	listNode *prevNode = h;		   // prevNode에 h 할당
	while (currNode != h && currNode->key < key)
	{
		prevNode = currNode;
		currNode = currNode->rlink; // currNode에 rlink할당
	}

	prevNode->rlink = newNode; // prevNode의 rlink가 newNode를 가리킴
	newNode->llink = prevNode; // newNode의 llink가 prevNode를 가리킴
	newNode->rlink = currNode; // newNode의 rlink가 currNode 가리킴
	currNode->llink = newNode; // currNode의 llink가 newNode를 가리킴

	return 1;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode *h, int key)
{
	if (h->rlink == h)
	{ // 리스트가 비어있을때
		printf("List is empty. Cannot delete.\n");
		return 0;
	}

	listNode *currNode = h->rlink;
	listNode *prevNode = h;

	while (currNode != h)
	{
		if (currNode->key == key)
		{
			prevNode->rlink = currNode->rlink; //prevNode의 rlink가 currNode의 rlink를 할당
			currNode->rlink->llink = prevNode; //currNode의 rlink가 llink를 가리키고 prevNode 할당
			free(currNode); //currNode 메모리 해제
			return 1;
		}
	    prevNode = currNode;
        currNode = currNode->rlink;
	}
	printf("Node with key %d not found.\n", key);
	return 0;
}