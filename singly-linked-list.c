#include<stdio.h>
#include<stdlib.h>


typedef struct Node { // 리스트노드
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // 헤드노드
	struct Node* first;
}headNode;


headNode* initialize(headNode* h); // 
int freeList(headNode* h); // 연결리스트 메모리 할당 해제

int insertFirst(headNode* h, int key); // 맨 앞에 노드 삽입
int insertNode(headNode* h, int key); // 연결리스트의 값들 중에서 입력값보다 큰 수 바로 앞에 노드 삽입
int insertLast(headNode* h, int key); // 맨 마지막에 노드 삽입

int deleteFirst(headNode* h); // 맨 앞의 노드 삭제
int deleteNode(headNode* h, int key); // 입력받은 값의 노드를 삭제
int deleteLast(headNode* h); // 맨 마지막 노드 삭제
int invertList(headNode* h); // 연결리스트를 역순으로 재배치

void printList(headNode* h); // 연결리스트 출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{ // 메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		// 명령키 선택
		printf("Command = ");
		scanf(" %c", &command);
		// 명령키에 따른 동작 수행
		switch(command) {
		case 'z': case 'Z': // 명령키 z, Z 선택 시, headnode 초기화
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': // 명령키 p, P 선택 시, 리스트 출력
			printList(headnode);
			break;
		case 'i': case 'I': // 명령키 i, I 선택 시, 입력값을 받아 노드를 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':	// 명령키 d, D 선택 시, 입력받은 값을 갖는 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // 명령키 n, N 선택 시, 맨 마지막에 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // 명령키 e, E 선택 시, 맨 마지막 노드 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': // 명령키 f, F 선택 시, 맨 앞에 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // 명령키 t, T 선택 시, 맨 앞의 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // 명령키 r, R 선택 시, 연결리스트의 노드들을 역순으로 재배치
			invertList(headnode);
			break;
		case 'q': case 'Q': // 명령키 q, Q 선택 시, 연결리스트 메모리 할당을 해제
			freeList(headnode);
			break;
		default: // 그 이외의 명령키 입력 시, 오류 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 명령키 q, Q 선택 시에만 프로그램 종료

	return 1; // 정상 종료 확인 반환
}

headNode* initialize(headNode* h) { // headNode를 초기화하는 함수

	// headNode가 NULL이 아닐 때에는 연결리스트를 free
	if(h != NULL)
		freeList(h);

	// headNode를 만들어 first를 초기화한 후 주소값 반환
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){ // 연결리스트 메모리 할당 해제 함수
	
	listNode* p = h->first;
	listNode* prev = NULL;

	// 노드 부분을 모두 free 하고, headNode 또한 free
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

int insertFirst(headNode* h, int key) { // 맨 앞에 노드를 삽입하는 함수

	// 삽입할 노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	// 맨 앞에 노드를 삽입
	node->link = h->first;
	h->first = node;

	return 0;
}

int insertNode(headNode* h, int key) { 
	// 연결리스트 노드의 key값 중에서 입력값보다 큰 값을 가진 노드 바로 앞에 해당 노드를 삽입하는 함수

	if(h->first==NULL) // 삽입한 노드가 없을 경우
	{
		insertFirst(h, key); // 맨 앞에 노드 삽입
	}
	else // 삽입한 노드가 있을 경우
	{	
		if(h->first->key >= key) // 맨 앞에 삽입하는 경우
		{
			insertFirst(h, key); // 맨 앞에 노드 삽입
		}
		else // 중간 또는 마지막에 삽입하는 경우
		{	
			listNode* SearchNode_B = NULL;
			listNode* SearchNode_N = h->first;
		
			// 입력받은 값보다 큰 수를 갖는 노드나 마지막 노드를 찾을 때까지 노드 탐색 
			while(SearchNode_N->key <= key && SearchNode_N->link!=NULL)
			{
				SearchNode_B = SearchNode_N;
				SearchNode_N = SearchNode_N->link;	
			}

			// 마지막 노드이지만 입력값보다 큰 값을 가진 노드가 없을 경우
			if(SearchNode_N->link ==NULL && SearchNode_N->key < key)
			{
				insertLast(h, key); // 맨 마지막에 노드 삽입
			}
			else // 입력값보다 큰 값을 가진 노드가 마지막 노드이거나 중간 노드일 경우
			{
				// 삽입할 노드 생성
				listNode* temp =(listNode*)malloc(sizeof(listNode));
				temp->key = key;

				// 해당 노드 앞에 삽입할 노드 삽입
				temp-> link = SearchNode_N;
				SearchNode_B->link = temp;
			}
		}	
		
	}
	

	return 0;
}

int insertLast(headNode* h, int key) { // 맨 마지막 노드 뒤에 노드 삽입하는 함수
	// 삽입할 노드 생성 및 값 저장
	listNode* temp = (listNode*)malloc(sizeof(listNode)); 
	temp->key = key;

	// 맨 마지막 노드 찾기
	listNode* LastNode = h->first;
	while(LastNode->link != NULL)
	{
		LastNode = LastNode->link;
	}

	// 맨 마지막 노드 뒤에 노드 삽입
	temp->link = LastNode->link;
	LastNode->link = temp;

	return 0;
}

int deleteFirst(headNode* h) { // 맨 앞의 노드 삭제하는 함수

	if(h->first ==NULL) // list에 아무 노드도 없을 때
	{
		printf("There's Nothing.\n\n"); // 메시지 출력
	}else{ // list에 노드가 있을 때

		// 2번째 노드를 1번째 노드로 변경하고 1번째 노드는 free로 삭제
		listNode* temp = h->first;
		h->first = h->first->link;
		temp->link = NULL;
		free(temp);
	}
	return 0;
}

int deleteNode(headNode* h, int key) { // 연결리스트 노드들 중 입력값에 해당하는 값을 갖는 노드를 삭제하는 함수 

	if(h->first == NULL) // 아무 노드도 없을 경우
	{
		printf("There's Nothing.\n\n");
	}else{ // 노드가 존재할 경우
		listNode* SearchNode_B = NULL;
		listNode* SearchNode = h->first;

		if(SearchNode->key == key) // 1번째 노드가 입력값과 같을 경우
		{
			deleteFirst(h); // 맨 앞의 노드 삭제
		}
		else{ // 1번째 노드가 입력값과 같지 않다면
			// 입력값과 같은 값을 갖는 노드나 마지막 노드를 탐색
			while(SearchNode->key != key && SearchNode->link != NULL)
			{
				SearchNode_B = SearchNode;
				SearchNode = SearchNode->link;
			}
			// 마지막 노드일 경우
			if(SearchNode->link == NULL)
			{	
				// 마지막 노드이면서 노드의 값이 입력값과 같다면
				if(SearchNode->key==key)
				{
					deleteLast(h); // 마지막 노드 삭제
				}else printf("Nothing to delete.\n\n"); // 그렇지 않다면 오류 메시지 출력
			}
			else{ // 마지막 노드가 아닐 경우, 즉 입력값과 같은 값을 갖는 노드일 경우
				// 해당 노드 앞과 뒤의 노드들을 연결하고 해당 노드는 free로 삭제
				SearchNode_B->link = SearchNode->link;
				SearchNode->link = NULL;
				
				free(SearchNode);
			}
		}
	}
	return 0;
}

int deleteLast(headNode* h) {

	if(h->first ==NULL) // list에 아무 노드도 없을 때
	{
		printf("There's Nothing.\n\n"); // 메시지 출력
	}else{ // list에 노드가 있을 때
		listNode* LastNode = h->first;
		listNode* LastNode_B = NULL ;
		
		// 맨 마지막 노드를 탐색
		while(LastNode->link != NULL)
		{	
			LastNode_B = LastNode;
			LastNode = LastNode->link;
		}
		// 마지막 노드의 link(NULL)을 맨 마지막의 이전 노드에 할당
		LastNode_B->link = LastNode->link;
		// 마지막 노드를 free로 삭제
		free(LastNode);
	}
	return 0;
}

int invertList(headNode* h) { // 연결리스트의 노드들을 역순으로 재배치하는 함수

	listNode* temp_invert = NULL;
	listNode* temp_invert_LN = NULL;
	listNode* temp_Search_LN = h->first;
	listNode* temp_Search_LN_B = NULL;

	// 노드가 하나 남을 때까지 노드들을 떼어 재배치해 임시적으로 저장
	while(h->first->link != NULL)
	{
		temp_Search_LN = h->first;
		temp_Search_LN_B=NULL;

		// 마지막 노드를 탐색
		while(temp_Search_LN->link!=NULL)
		{
		temp_Search_LN_B = temp_Search_LN;
		temp_Search_LN = temp_Search_LN->link;
		}
		
		if(temp_invert==NULL) // temp_invert(재배치한 노드들을 임시 저장할 곳)에 아무 노드도 없다면
		{
		// 마지막 노드를 temp_invert에 저장하고 temp_invert의 마지막 노드임을 temp_invert_LN으로 가리킨다.
		temp_invert = temp_Search_LN;
		temp_invert_LN = temp_invert;
		}
		else // temp_invert에 노드가 있다면
		{	// temp_invert의 마지막 노드 뒤에 재배치할 마지막 노드들을 이어 붙인다.
			temp_invert_LN->link = temp_Search_LN;
			temp_invert_LN = temp_invert_LN->link;
		}
		temp_Search_LN_B->link =NULL; // 재배치한 마지막 노드를 가리키는 이전 포인터값을 NULL로 변경
	}
	/* h->first에 노드가 하나 남았다면, 남은 노드를 temp_invert의 마지막 노드에
	 이어 붙이고, 역순으로 재배치된 연결리스트를 h->first에 넘겨준다 */
	temp_invert_LN->link = h->first;
	h->first = temp_invert;

	return 0;
}


void printList(headNode* h) { // 연결리스트를 출력하는 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // headNode가 생성되지 않았다면 
		printf("Nothing to print....\n"); // 메시지 출력
		return;
	}

	p = h->first;

	while(p != NULL) { // 마지막 노드까지 연결리스트를 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}
	// 연결리스트의 노드 수를 출력
	printf("  items = %d\n", i);
}

