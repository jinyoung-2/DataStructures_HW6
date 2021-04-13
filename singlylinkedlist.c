/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
	int key;			//노드의 데이터
	struct Node* link;  //자기참조형구조체(자신과 동일한 구조체에 대한 포인터)
} listNode;  			//노드의 구조

typedef struct Head {
	struct Node* first; //헤드노드를 가리키는 포인터  
}headNode;  			


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

/* 헤드노드 초기화 함수 */
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
	/* 헤드노드가 존재하면, p->link는 NULL이라는 점 이용  */
	while(p != NULL) {		
		prev = p;			
		p = p->link;		//p를 NULL로 설정 
		free(prev);			//이전 노드의 메모리 해제
	}
	free(h);	//헤드노드 메모리 해제   
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
//첫번째 노드에 추가 
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //key에 대한 노드하나 추가를 위해 메모리할당
	node->key = key;		//node의 데이터부분에 key 대입

	node->link = h->first;  //노드의 link가, 이전에 헤드노드가 가리키는 노드의 주소 가리키도록 설정   
	h->first = node;  		//헤드노드를 node로 변경  

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
//중간에 삽입--> 순차적으로!(오름차순으로 입력)
int insertNode(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode));   //새로운 노드 생성(동적할당)
	/*node노드의 data,link 초기화*/
    node->key=key;
    node->link=NULL;   

    //리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	    

    //노드가 존재하지 않을 때
    if(h->first==NULL)  
    {
        h->first=node;      //헤드노드를 node로 설정 
        return 0;
    }

	//노드가 1개일 때
	else if(h->first->link==NULL)
	{
		if(key<(h->first->key))	//입력받은 key보다 노드의 데이터가 클 때(헤드노드 바로 앞에 위치)
		{
			node->link=h->first;
		 	h->first=node;		//헤드노드를 node로 설정
		}
		else					//헤드노드 바로 뒤에 위치
		{
			h->first->link=node;
		}
		return 0;
	}

	//노드가 2개 이상일 때
	else
	{
		if(key<(cur->key)) //key가 헤드노드의 데이터보다 작을 때
		{
			node->link=h->first;
			h->first=node;
			return 0;
		}

		prev=cur;
		cur=cur->link;

		while(cur!=NULL)
   		{
			//삽입할 위치를 찾을 때 -> prev와 cur 사이에 삽입
        	if(key<(cur->key))		
            {
				node->link=cur;	 	//cur의 위치를 node->link에 대입
				prev->link=node;	//node의 위치를 prev->link에 대입
				return 0;
			}	
        	//삽입할 위치 찾지 못할 때 prev, cur 위치 변경
			else
			{
				prev=cur;
				cur=cur->link;
			}
    	}
		//prev가 마지막 노드일 때(=key값이 가장 클 때)
		prev->link=node;
		return 0;
	}
}


/**
 * list에 key에 대한 노드하나를 추가
 */
//마지막에 삽입
int insertLast(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode));   //새로운 노드 생성(동적할당)
	/*node노드의 data,link 초기화*/
    node->key=key;
    node->link=NULL;    

    //리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	 

    //노드가 존재하지 않을 때
    if(h->first==NULL)
    {
		h->first=node;	//node를 헤드노드로 설정
		return 0;
    }

    //노드가 1개일 때
	else if(h->first->link==NULL)
	{
		cur->link=node;
		return 0;	
	}

	//노드가 2개 이상일 때
	else
	{
		while((cur->link)!=NULL)
		{
			prev=cur;		//prev는 cur노드로 변경 
			cur=cur->link;	//cur은 cur의 link가 가리키는 노드로 변경
		}
		//cur이 마지막 노드일 때 node 추가 
		cur->link=node;
		return 0;
	}
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) 
{   
    //리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	 

	//노드가 없을 때(삭제할 노드가 없음)
	if((h->first)==NULL)
	{
		printf("ERROR: There are no nodes to remove.\n");
		return -1;  
	}

	//노드가 1개만 있을 때(헤드노드 삭제)
    else if(h->first->link==NULL)
    {
        free(h->first);   //메모리 해제                
        h->first=NULL;    //노드 제거로 헤드노드는 존재하지 않으므로, 헤드노드를 NULL로 초기화 
		return 0;
    }

    //노드가 2개 이상 있을 때 
	else
    {
		prev=cur;		
		cur=cur->link;
        free(prev);		//메모리할당 해제   
        h->first=cur;	//헤드노드를 cur로 설정 
		return 0;
    }
}


/**
 * list에서 key에 대한 노드 삭제
 */
//해당되는 key에 대한 노드 삭제 (처음 만나는 원소만 삭제)
int deleteNode(headNode* h, int key) 
{
	//리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	 

	//노드가 없을 때
	if((h->first)==NULL)
	{
		printf("ERROR: There are no nodes to remove.\n");
		return -1;
	}
	//노드가 1개일 때 - 해당되는 key가 존재할 때와 존재하지 않을 때로 2가지 case 나뉨 
	else if(h->first->link==NULL)
	{
		if(key==(cur->key))	//해당되는 key가 존재할 때, 노드 삭제 
		{
			free(h->first);	//할당된 메모리 해제 
			h->first=NULL;	//헤드노드를 NULL로 설정 
			return 0;
		}
		else //해당되는 key가 존재하지 않을 때
		{
			printf("ERROR: There are no nodes to remove.\n");
			return -1;
		}
	}

	//노드가 2개 이상일 때 
	else{
        while(cur){
			//해당 key를 갖고 있다면, 노드 삭제
            if((cur->key)==key){
				if(cur==h->first) //헤드노드의 데이터와 key가 동일할 때 
				{
					cur=cur->link;
					free(h->first);	//할당된 메모리 해제
					h->first=cur;	//헤드노드를 cur로 설정 
					return 0;
				}
				//그 외의 노드 데이터와 key가 동일할 때
				else
				{
                	prev->link=cur->link;
               	 	free(cur);    //할당된 메모리 해제            
                	return 0;
				}
            }

			//해당 key를 갖고 있지 않을 때 -> cur노드의 데이터가 key가 아닐 때
            else{
				prev=cur; 		//prev는 cur 노드로 변경   
		    	cur=cur->link;	//cur은 cur의 link가 가리키는 노드로 변경		   
            }
        }
		//cur이 NULL일때 = 해당 key가 노드에 전혀 존재하지 않을 때
		printf("ERROR: There are no nodes to remove.\n");
		return -1;
    }
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) 
{
    //리스트 탐색을 위한 노드 포인터들 선언 
	listNode* prev=NULL;        
	listNode* cur=h->first;	 

	//노드가 없을 때(=삭제할 노드가 없음)
	if((h->first)==NULL)
	{
		printf("ERROR: There are no nodes to remove.\n");
		return -1;
	}
	 
	//노드가 1개일 때
	else if(h->first->link==NULL)
	{
		free(h->first);
		h->first=NULL;
		return 0;
	}

	//노드가 2개 이상일 때
	else
	{
		while(cur->link!=NULL)
		{
			prev=cur;
			cur=cur->link;
		}
		//cur이 마지막 노드일 때(=cur을 삭제해야 함)
		prev->link=NULL;
		free(cur);
		return 0;

		// while(cur!=NULL)
		// {
		// 	prev=cur;
		// 	cur=cur->link;
		// }
		// //prev가 마지막 노드일 때
		// prev=NULL;     
		// free(prev);
		// return 0;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) 
{
	/* 리스트 탐색을 위한 노드 포인터 3개 선언 -> 이유: 노드포인터 2개만 선언시 연속적으로 역순으로 재배치 불가능함. 
		예를 들어 prev와 cur 노드 포인터가 있다고 하자. cur->link=prev로 하면, 기존에 cur->link가 가리키는 노드의 연결을 제거하여 연속적으로 연속으로 재배치가 불가능하다.*/
	listNode* trail=NULL;		//NULL로 초기화
	listNode* middle=NULL;		//NULL로 초기화
	listNode* lead=h->first;	//헤드노드를 가리키도록 초기화

	//노드가 없을 때와 노드가 1개일 때는 역순으로 재배치할 노드가 없음(기존과 동일한 순서)
	if(((h->first)==NULL)||((h->first->link)==NULL))
	{
		return -1;
	}

	//노드가 2개 이상일 때
	else
	{
		while(lead)				//lead가 NULL이기 전까지 반복
		{
			trail=middle;		//trail위치를 middle 위치로 설정
			middle=lead;		//middle위치를 lead 위치로 설정
			lead=lead->link;	//lead위치를 lead의 link가 가리키는 위치로 설정 
			middle->link=trail;	//middle의 link는 trail을 가리키도록 설정 (역순 재배치)
		}
		//lead가 NULL일 때(middle->link가 NULL일 때)
		h->first=middle;		//헤드노드를 middle로 설정 
		return 0;
	}
}

/* 리스트 출력하는 함수 */
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {   //리스트에 노드가 존재하지 않을 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {	//p가 NULL이기 전까지 반복
		printf("[ [%d]=%d ] ", i, p->key);  //각각의 노드의 데이터 출력
		p = p->link;	//노드 이동
		i++;
	}

	printf("  items = %d\n", i);	//리스트에 있는 노드의 총 개수 출력 
}