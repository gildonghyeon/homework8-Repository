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
	if(h->rlink == h) //h노드가 비어있는 경우
	{
		free(h); //메모리 해제
		return 1;
	}

	listNode* p = h->rlink; //p노드를 헤더의 rlink로 설정

	listNode* prev = NULL; 
	while(p != NULL && p != h) { //p가 비어있지 않고 p가 h가 아닐동안 반복
		prev = p; //prev에 p 할당
		p = p->rlink; //p를 p의 오른쪽 링크로 설정
 		free(prev); //prev 해제
	}
	free(h); //h해제
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
	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key; //node의 key에 key할당
	node->rlink = NULL; //node의 rlink를 비움
	node->llink = NULL; //node의 llink를 비움

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; //h의 rlink를 새로운 노드로 설정
		h->llink = node; //h의 llink를 새로운 노드로 설정
		node->rlink = h; //node의 rlink를 헤더로 설정
		node->llink = h; //node의 llink를 헤더로 설정
	} else {
		h->llink->rlink = node; //h의 llink가 가리키는 rlink를 새로운 노드로 설정
		node->llink = h->llink; //node의 llink를 헤더의 llink로 설정
		h->llink = node; //h의 llink를 node로 설정
		node->rlink = h; //node의 rlink를정헤더로 설정
	}

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode *h)
{
	if (h->llink == h || h == NULL) //h의 llink가 h를 가리키거나 h가 비어있을때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //nodetoremove를 헤더노드의 llink로 설정

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove가 가리키는 llink가 가리키는 rlink를 헤더노드로 설정
	h->llink = nodetoremove->llink; //헤드노드의 llink를 nodetoremove의 llink로 설정

	free(nodetoremove); //메모리 해제

	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode *h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //node의 key에 key할당
	node->rlink = NULL; //node의 rlink를 비움
	node->llink = NULL; //node의 llink를 비움
	
	node->rlink = h->rlink; //node의 rlink를 헤드노드의의 rilink로 
	h->rlink->llink = node; //h의 rlink가 가리키는 llink를 새로운 노드로 설정
	node->llink = h; //node의 llink를 헤드노드로 설정
	h->rlink = node; //헤드노드의 rlink를 새로운 노드로 설정
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode *h)
{
	if (h == NULL || h->rlink == h) //헤더가 비어있거나 헤더의 rlink가 헤더일때 
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //nodetoremove를 헤더의 rlink로 설정

	/* link 정리 */
	nodetoremove->rlink->llink = h; //nodetoremove의 rlink가 가리키는 llink를 헤더로 설정
	h->rlink = nodetoremove->rlink; //헤더의 rlink를 nodetoremove의 rlink로 설정

	free(nodetoremove); /메모리 해제
	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode *h)
{
	if(h->rlink == h || h == NULL) { //헤더의 rlink가 헤더이거나 헤더가 비어있을때
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //포인터 n을 h의 rlink로 설정
	listNode *trail = h; //포인터 trail을 헤더로 설정
	listNode *middle = h; //포인터 middle을 헤더로 설정

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //헤더의 llink를 헤더의 rlink로 설정

	while(n != NULL && n != h){ //n이 비어있거나 n이 헤더가 아닐동안 반복
		trail = middle; //
		middle = n;
		n = n->rlink; //n을 n의 rlink로 설정
		middle->rlink = trail; //middle의 rlink를 trail로 설정
		middle->llink = n; //middle의 llink를 n으로 설정
	}

	h->rlink = middle; //h의 rlink를 middle로 
	return 1;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode *h, int key)
{
	if(h == NULL) return -1; //헤더가 비어있을때 -1 리턴

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL; //노드의 llink를 노드의 rlink로 설정

	if (h->rlink == h) //헤더의 rlink가 헤더일때
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink; //포인터n을 헤더의 rlink로 정설정

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //노드의 rlink를 n으로 설정
				node->llink = n->llink; //노드의 llink를 n의 llink로 설정 
				n->llink->rlink = node; //n의 llink의 rlink를 node로 설정
				n->llink = node; //n의 llink를 노드로 설정
			}
			return 0;
		}

		n = n->rlink; //n을 n의 rlink로설정
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode *h, int key)
{
	if (h->rlink == h || h == NULL) //헤더의 rlink가 헤더이거나 헤더가 비어있을때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //포인터n을 헤더의 rlink로 설정

	while(n != NULL && n != h) { //n이 비어있지 않고 n이 헤더가 아닐동안 반복
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 llink의 rlink를 n의 rlink로 설정
				n->rlink->llink = n->llink; //n의 rlink의 llink를 n의 llink로 
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
