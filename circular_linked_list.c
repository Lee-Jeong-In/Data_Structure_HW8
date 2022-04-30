/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */


#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;							// 맨처음의 HeadNode를 잡아준다.	(listNode*인 주소 1개 들어갈 크기)

	printf("[----- [이정인] [2019038015] -----]\n");

	do{
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

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);				// 새로운 HeadNode만들기
			break;
		case 'p': case 'P':
			printList(headnode);				// 여태까지 만든 list 화면에 출력하기
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);			// Node 추가하기
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);			// 사용자가 원하는 key를 가진 노드를 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);			// 마지막에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);				// 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);			// 맨 앞에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);				// 맨 앞 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);				// circular이지만 rlink로 이전 노드를 잡고, llink로 다음 노드를 잡아 내면서 역순으로 배치된 list를 만든다.
			break;
		case 'q': case 'Q':
			freeList(headnode);					// 종료시 메모리 해제하고 나가기
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h)						// HeadNode의 주소를 보내고 더블 포인터를 사용해 간접접근한다. (h==&HeadNode)
{

	if(*h != NULL)									// *h == HeadNode에 있는 값 (즉, NULL이 아니면 HeadNode를 한번 사용했다는 뜻)
		freeList(*h);								// 따라서, HeadNode의 값을 초기화(NULL)로 만들어준다.
													// 또한 포인터는 NULL로 초기화 해야 안전하게 사용할 수 있다.

	*h = (listNode*)malloc(sizeof(listNode));		// 초기화 검사 끝난후 새로 사용할 HeadNode 생성
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;								// 임시 키값 생성 (왜 -9999로 했는지는 모르겠다...)
	return 1;
}

int freeList(listNode* h)							// 동적할당된 list의 메모리를 해제하기 (h는 *h를 받았으므로 HeadNode에 있는 값)
{
	printf("Free Circular linked list...\n");

	if(h->rlink == h)								// initialize함수에서 HeadNode를 만들때 *h->rlink = *h 로 초기화를 했기 때문에, 조건식을 h->rlink ==h로 쓴거 같다.
													// 어쨎든 조건식의 의미는 HeadNode가 존재할 때 라고 해석된다. ( 이때는 HeadNode 1개만 존재 할 때...)
	{
		free(h);									// HeadNode이 있다는 것을 찾았으므로 메모리 해제(아예 다시 만들기 위함)
		return 1;									// HeadNode해제 했기 때문에 freelist()함수 종료.
	}

	listNode* p = h->rlink;							// 임시 노드 p를 HeadNode가 rlink로 가리키는 노드로 저장

	listNode* prev = NULL;							// prev 노드 생성
	while(p != NULL && p != h)						// P가 NULL도 아니고 h도 아니면(==HeadNode의 rlink에 다른 무언가가 있으면)
	{	
		prev = p;									// 임시 prev노드에 p를 복사
		p = p->rlink;								// p는 p->rlink로 이동
		free(prev);									// prev 해제(== HeadNode뒤에 있는 Node 1개 제거)
													// HeadNode다음에 아무것도 없을 때까지 반복
	}

	free(h);										// HeadNode 제거
	return 0;										// freelist()종료.
}



void printList(listNode* h)							// 여태까지 만든 list 화면에 출력하기
{
	int i = 0;										// 노드 갯수 세어줄 i 생성
	listNode* p;									// 임의의 노드 p 생성

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");			// 출력할 노드 없음
		return;
	}

	p = h->rlink;									// 첫번째 노드로 이동

	while(p != NULL && p != h)						// 노드가 있으면 출력하고 다음 노드로 이동
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;										// 거처간 노드 갯수 세기
	}
	printf("  items = %d\n", i);


	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);		// HeadNode를 확인

	i = 0;
	p = h->rlink;

	while(p != NULL && p != h)																// 각 노드의 정보를 확인한다.
	{
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}


int insertLast(listNode* h, int key)								// 마지막에 노드 넣기
																	// h==HeadNode의 값 , key == 사용자가 입력한 값
{

	if (h == NULL) return -1;										// HeadNode없을 때
		
	listNode* node = (listNode*)malloc(sizeof(listNode));			// 새로운 노드 생성
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h)												// 새로운 노드가 처음이자 마지막일 때...
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} 

	else															// 진짜 맨 마지막에 넣을 때
	{
		h->llink->rlink = node;										// 이미 존재한 마지막 노드와 새로운 노드를 연결
		node->llink = h->llink;										// 새로운 노드와 기존에 존재한 마지막 노드를 연결 (doubly linked)
		h->llink = node;											// HeadNode와 새로만들 노드를 doubly linked로 연결
		node->rlink = h;											// HeadNode와 새로만들 노드를 doubly linked로 연결
	}

	return 1;
}


int deleteLast(listNode* h)											// 마지막 노드 삭제
{

	if (h->llink == h || h == NULL)									// 노드 없음
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;								// HeadNode의 왼쪽은 맨 마지막 노드임( 왜냐면 circular 니까)
		
	nodetoremove->llink->rlink = h;									// 기존 노드의 마지막에서 두번째 노드가 HeadNode를 연결
	h->llink = nodetoremove->llink;									// HeadNode도 마지막에서 두번째 노드와 연결

	free(nodetoremove);												// 맨 마지막 노드 삭제

	return 1;
}


int insertFirst(listNode* h, int key)						// h == HeadNode(노드가 있는 주소값), key == 사용자가 넣은 값
{

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 새로운 노드 생성
	node->key = key;										// 초기화
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;									// node->rlink에 h->rlink의 값(주소값) 넣는다.
	h->rlink->llink = node;									// HeadNode의 llink에 새로만든 node를 연결한다. (이건 아마 맨처음 노드 앞에 새로운 노드를 생성해야 할때 사용하는 것 같다.)
	node->llink = h;										// node의 llink에 HeadNode를 연결한다. (doubly linked list)
	h->rlink = node;										// HeadNode의 rlink에 Node를 연결한다.

	return 1;
}

int deleteFirst(listNode* h)								// 맨처음 삭제
{

	if (h == NULL || h->rlink == h)							// 노드 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;						// 임시 노드 생성

	nodetoremove->rlink->llink = h;							// 기존은 두번째 노드를 HeadNode와 연결
	h->rlink = nodetoremove->rlink;							// HeadNode도 기존의 두번째 노드와 연결 (doubly linked)

	free(nodetoremove);										// 맨 처음 노드 삭제
		
	return 1;
}


int invertList(listNode* h)									// 역순으로..
{

	if(h->rlink == h || h == NULL) {						// 역순으로 할 list 없을 때
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->rlink;									// 앞에서 하나씩 읽어갈 n 노드
	listNode *trail = h;									// 앞의 노드 뒤에서 쫓아갈 trail 노드
	listNode *middle = h;									// 바꾸기 위해 임시 저장할 middle 노드

	h->llink = h->rlink;									// 원형이기도 하고, 이미 n으로 첫번째 노드를 잡아놔서 상관없음

	while(n != NULL && n != h)								// 본격적으로 바꾸기
	{
		trail = middle;										// 1. trail과 middle을 같게 만들기
		middle = n;											// 2. n노드를 middle에 임시저장
		n = n->rlink;										// 3. n노드는 다음 노드로 가있기
		middle->rlink = trail;								// 4. 임시노드에 있는 거가 p번째 노드이면 trail은 p-1번째 노드이다..
		middle->llink = n;									// 5. 임시노드와 그 다음 노드를 연결해 준다.
	}

	h->rlink = middle;										// 그리고 HeadNode의 rlink와 middle을 연결해야 마무리 된다.

	return 0;
}


int insertNode(listNode* h, int key)							// 새로운 Node생성 + 노드를 sorting 하면서 생성
																// h==HeadNode(노드가 있는 주소값) , key == 사용자가 넣은 값
{

	if (h == NULL)												// h(노드가 있는 주소값)==NULL 인 경우는 ==>> HeadNode가 없을 때
	{
		printf("There is no HeadNode.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));		// 새로운 노드 메모리 할당
	node->key = key;
	node->llink = node->rlink = NULL;							// 결국 link와 rlink에 NULL

	if (h->rlink == h)											// HeadNode를 봤는데 아무런 노드와 연결이 되어 있지 않을 때 ==>> 맨처음으로 노드를 삽일 해야 할 때
	{
		insertFirst(h, key);									// 맨처음으로 Node삽입
		return 1;
	}

	listNode* n = h->rlink;										// HeadNode에 어떤 노드가 있을 때, key를 비교하기 위해 임시의 n노드를 만들고 rlink로 옆으로 옮긴다.

	while(n != NULL && n != h)									// HeadNode에 어떤 노드가 있을 때,
	{
		if(n->key >= key)										// 기존 노드의 key가 새로운 key보다 클때
		{
			
			if(n == h->rlink)									// 그 기존 노드 n이 맨 처음일 때,,,
			{
				insertFirst(h, key);
			} 
			
			else												// 처음이 아닌 경우
			{ 
				node->rlink = n;								// 새로운 노드 다음으로 기존 노드n를 연결
				node->llink = n->llink;							// 기존노드 n의 이전 노드는 새로운 노드와 연결
				n->llink->rlink = node;							// 기존노드 n의 이전 노드와 새로운 노드의 doubly linked
				n->llink = node;								// 기존노드 n의 이전 노드와 새로운 노드의 doubly linked
			}
			return 0;
		}

		n = n->rlink;											// n을 계속 이동
	}

	insertLast(h, key);											// key가 기존 Node의 key보다 모두 클때
	return 0;
}


int deleteNode(listNode* h, int key)							// 사용자가 원하는 노드 삭제하기
																// h == HeadNode, key == 사용자 입력
{

	if (h->rlink == h || h == NULL)								// 노드 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;										// 임시 노드 n 을 이동

	while(n != NULL && n != h)									
	{
		if(n->key == key)										// 삭제하고 싶은 노드를 찾음!!
		{
			if(n == h->rlink)									// 그게 맨 처음 노드 일때..
			{ /* 첫 노드째 노드 인경우 */
				deleteFirst(h);									// 맨처음 삭제
			} 

			else if (n->rlink == h)								// 맨 마지막 삭제
			{ 
				deleteLast(h);
			} 

			else												// 임시노드 기준으로 양 옆의 노드를 연결시킨다.
			{ 
				n->llink->rlink = n->rlink;	
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;											// 찾을 때 까지 이동한다.
	}

	printf("cannot find the node for key = %d\n", key);			// 못찾음(삭제할 거 없음)
	return 0;
}
