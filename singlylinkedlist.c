/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;   //자기참조형구조체(자신과 동일한 구조체에 대한 포인터)
} listNode;  //노드 구조

typedef struct Head {
	struct Node* first;   //listNode* first;  //제출하기 전 나중에 삭제하기!!
}headNode;  //헤드노드


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;  //NULL로 초기화
	printf("[----- [jinyounglee] [2020039063] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//반복 조건

	return 1;		//정상종료
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));  
	temp->first = NULL;  //NULL로 초기화 
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;  //이전 노드를 NULL로 초기화 
	while(p != NULL) {		//헤드노드가 가리키는 first가 NULL이 아니라면
		prev = p;			
		p = p->link;
		free(prev);			//이전 노드 동적할당 해제
	}
	free(h);	//헤드노드 동적할당 해제
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
//처음노드에 추가 
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //key에 대한 노드하나 추가를 위한 동적할당 
	node->key = key; //node에 key값 대입

	node->link = h->first;  //노드의 link에 헤드노드가 가리키는 주소 대입   //Q.확인 
	h->first = node;  //head노드를 node로 변경  

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
//중간에 삽입--> 순차적으로!(오름차순으로 입력)
int insertNode(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode));   //새로운 노드 생성(동적할당)
    node->key=key;
    node->link=NULL;    //초기화

    //리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	    

    //리스트에 노드가 존재하지 않을 때
    if(h->first==NULL)  
    {
        h->first=node;      //첫번째 노드를 node로 설정   //Q. 맞나?  
        return 0;
    }
    //리스트에 노드가 존재할 때
    while(1)
    {
        if(key<=(cur->key))		//Q. 등호 맞나?
            break;
        //삽입할 위치 찾지 못할 때 prev, cur 위치 변경
        prev=cur;
		cur=cur->link;
    }
    //삽입할 위치를 찾을 때 -> cur 위치에 삽입
	node->link=cur;	    //cur의 위치를 node->link에 대입
	prev->link=node;	//node의 위치를 prev->link에 대입
	
	return 0;
}




/**
 * list에 key에 대한 노드하나를 추가
 */
//마지막에 삽입
int insertLast(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode));   //새로운 노드 생성(동적할당)
    node->key=key;
    node->link=NULL;    //초기화

    //리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	 

    //리스트에 노드가 존재하지 않을 때
    if(h->first==NULL)
    {
        h->first=node;  //Q.
        return 0;
    }

    //리스트에 노드가 1개 이상 존재할 때
    while(cur!=NULL)
    {
        prev=cur; //prev는 cur 노드로 변경   
		cur=cur->link;	//cur은 cur의 link가 가리키는 노드로 변경
    }
    //cur=NULL일 때(마지막 노드일 때)
	prev->link=node;  //마지막 노드의 link에 생성한 node 연결(주소 대입)
	
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) 
{
	//전처리기 함수작성하기
	//첫번째 노드=NULL이라면, ~~한다
	if(h->first==NULL)
	{
		printf("제거할 노드가 없습니다.\n");
		return -1;
	}
	//첫번째 노드가 NULL이 아닐 때
	listNode* prev=NULL;  //이전 노드 
	listNode* cur=h->first;	 //현재 노드 
	prev=cur->link;
	free(cur);
	//혹시 cur도 설정해줘야 하나요? 안 해도 될거 같은데, 
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
//해당되는 key에 대한 노드 삭제 (처음에 만나는 원소만 삭제)
int deleteNode(headNode* h, int key) 
{
	listNode* prev=NULL;  //이전 노드 
	listNode* cur=h->first;	 //현재 노드 
	if((cur->key)==key)	//해당 key를 갖고 있다면, 삭제
	{	
		prev=cur->link;
		free(cur);
	}
	else
	{
		prev=cur;
		cur=cur->link;
	}
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) 
{
	//Q. 마지막 노드는 어떻게 찾을까?
	listNode* prev=NULL;  //이전 노드 
	listNode* cur=h->first;	 //현재 노드 
	if(cur->link==NULL)	//마지막 노드일 때
	{
		prev->link=NULL;
		free(cur);   //Q. 가능?
	}
	else	//마지막 노드가 아닐 때 다음 노드로 이동
	{
		prev=cur;
		cur=cur->link;
	}
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) 
{


	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}