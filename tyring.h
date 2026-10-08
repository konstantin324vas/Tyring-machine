#include <stdio.h>
typedef struct List2d3 {
     char** data;
     int count;
     struct List2d3* link;
} List2d3;
typedef struct Node {
    char data;
    struct Node* prev;
    struct Node* next;
} Node;
typedef struct List {
    Node* head;
    Node* tail;
} List;

List* createList() {
    List* list = (List*) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

List2d3* createList2d3(int count) {
    List2d3* newList = (List2d3 *) malloc(sizeof(List2d3));
    newList->link=NULL;
    newList->data= (char**) malloc(count*sizeof(char *));
    for(int i=0; i<count; i++) {
        newList->data[i]=(char*) malloc(3*sizeof(char));
        for(int j=0; j<3; j++) {
			newList->data[i][j]='\0';
		}
    }
    newList->count=count;
    return newList;
}
List2d3* getLing(List2d3* list, int n) {
	int i = 0;
    List2d3* tmp = list;
    while (tmp != NULL && i != n) {
        tmp = tmp->link;
        i++;
    }
    return tmp;   // NULL, если n больше длины
}
int saveShema(List2d3* shema, List* sost, char* alfavit, int count, FILE* fn) {
	fprintf(fn, "THIS IS SXEMA\n");
	fprintf(fn, "%d\n", count);
	fprintf(fn, "|qqq|");
	for (int i = 0; i<count; i++) {
		fprintf(fn, "%c  |", alfavit[i]);
	}
	Node* current = sost->head;
	int c=0;
	while (current) {
		fprintf(fn, "\n|q%c |", current->data);
		List2d3* tmp=getLing(shema, c);
		for(int i=0; i<shema->count; i++){
			fprintf(fn, "%c%c%c|", tmp->data[i][0], tmp->data[i][1], tmp->data[i][2]);
		}
		c++;
		current=current->next;
	}
}
int printShema(List2d3* shema, List* sost, char* alfavit, int count) {
	printf("\n|qqq|");
	for (int i = 0; i < count; i++) {
		printf("%c  |", alfavit[i]);
	}
	Node *current = sost->head;
	int c=0;
	printf("\n|q");
	while (current)
	{
		List2d3* tmp=getLing(shema, c);
		printf("%c |", current->data);
		for(int i=0; i<shema->count; i++) {
			if(tmp->data[i][0]=='\0') {
				return 0;
			}
			for(int j=0; j<3; j++) {
				printf("%c", tmp->data[i][j]);
			}
			printf("|");
		}
		c++;
		current = current->next;
		printf("\n|q");
	}
	return 0;
}
void addList(List2d3* list) {
	List2d3* last = list;
	while(last->link != NULL) {
		last=last->link;
	}
	last->link=createList2d3(list->count);
}
int subList(List2d3** headRef) {
    if (headRef == NULL || *headRef == NULL) return -1;

    List2d3* head = *headRef;

    if (head->link == NULL) {
        for (int i = 0; i < head->count; i++) free(head->data[i]);
        free(head->data);
        free(head);
        *headRef = NULL;
        return 0;
    }

    List2d3* prev = head;
    while (prev->link->link != NULL) prev = prev->link;

    List2d3* last = prev->link;
    prev->link = NULL;

    for (int i = 0; i < last->count; i++) free(last->data[i]);
    free(last->data);
    free(last);

    return 0;
}

int subListIn(List2d3** headRef, int n) {
    if (headRef == NULL || &headRef == NULL || n < 0) return -1;

    List2d3* head = *headRef;

    if (n == 0) {
        *headRef = head->link;
        for (int i = 0; i < head->count; i++) free(head->data[i]);
        free(head->data);
        free(head);
        return 0;
    }

    List2d3* prev = head;
    for (int i = 0; i < n - 1; i++) {
        if (prev->link == NULL) return -2;
        prev = prev->link;
    }

    if (prev->link == NULL) return -2;

    List2d3* target = prev->link;
    prev->link = target->link;

    for (int i = 0; i < target->count; i++) free(target->data[i]);
    free(target->data);
    free(target);

    return 0;
}

void freeList2d3(List2d3** headRef) {
    if (headRef == NULL) return;

    List2d3* current = *headRef;
    while (current != NULL) {
        List2d3* next = current->link;

        if (current->data != NULL) {
            for (int i = 0; i < current->count; i++) {
                free(current->data[i]);
            }
            free(current->data);
        }
        free(current);

        current = next;
    }

    *headRef = NULL;
}

int add_item_to_end(List *list, char item)
{
  if (list == NULL) return -1;

  Node *newNode = (Node *) malloc(sizeof(Node));
  if (newNode == NULL) return -2;
  
  newNode->prev = newNode->next = NULL;
  newNode->data = item;
  
  if (list->tail)
  {
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
  }
  else
  {
    list->head = list->tail = newNode;
  }

  return 0;
}

int add_item_to_begin(List *list, char item)
{
  if (list == NULL) return -1;

  Node *newNode = (Node*) malloc(sizeof(Node));
  if (newNode == NULL) return -2;

  newNode->prev = newNode->next = NULL;
  newNode->data = item;
  if (list->head)
  {
    list->head->prev = newNode;
    newNode->next = list->head;
    list->head = newNode;
  }
  else 
  {
    list->head = list->tail = newNode;
  }
  return 0;
}

int delete_item(List *list, Node *node)
{
  if (node == NULL) return -1;
  if (list == NULL) return -2;

  if (node->prev)
  {
    node->prev->next = node->next;
  }
  else
  {
    list->head = node->next;
  }
  
  if (node->next)
  {
    node->next->prev = node->prev;
  }
  else
  {
    list->tail = node->prev;
  }

  free(node);
  return 0;
}

int lengList(List *list) {
	Node *current = list->head;
	int i=0;
	while (current)
  {
    i++;
    current=current->next;
  }
  return i;
}

char* convertList (List *list) {
	Node *current = list->head;
	char* str = (char*) malloc(lengList(list)+1*sizeof(char));
	for(int i=0; i<lengList(list); i++) {
		str[i]=current->data;
		current=current->next;
	}
	str[lengList(list)]='\0';
	return str;
}

char getItem(List* list, int n) {
	Node *current = list->head;
	int i=0;
  while (current)
  {
    if (i==n)
    {
      return current->data;
    }
    current = current->next;
    i++;
  }
  return '\0';
}

Node* getItemLink(List* list, int n) {
	Node *current = list->head;
	int i=0;
  while (current)
  {
    if (i==n)
    {
      return current;
    }
    current = current->next;
    i++;
  }
  return '\0';
}



int find_itemNum(List* list, char item)
{
  Node *current = list->head;
	int i=0;
  while (current)
  {
    if (current->data == item)
    {
      return i;
    }
    current = current->next;
    i++;
  }

  return -1;
}
Node* find_item(List*  list, char item)
{
  Node *current = list->head;

  while (current)
  {
    if (current->data == item)
    {
      return current;
    }
    current = current->next;
  }

  return NULL;
}
void freeListAndSelf(List* list) {
    if (list == NULL) return;

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void freeList(List* list) {
    if (list == NULL) return;

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

int deleteFirst(List* list) {
    if (list == NULL) return -1;
    if (list->head == NULL) return -2;    // список пуст

    Node* target = list->head;
    list->head = target->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;                // был единственный узел
    }

    free(target);
    return 0;
}

int deleteLast(List* list) {
    if (list == NULL) return -1;
    if (list->tail == NULL) return -2;    // список пуст

    Node* target = list->tail;
    list->tail = target->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;                // был единственный узел
    }

    free(target);
    return 0;
}

int indexOfChar(const char* str, char c) {
    if (str == NULL) return -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) return i;
    }
    return -1;
}

char inputChar() {
    char buffer[100];
    if (!fgets(buffer, sizeof(buffer), stdin)) return '\0';
    if (buffer[0] == '\n') return '\0';
    return buffer[0];
}
char answer(char *massage) {
	snova:
    printf("%s", massage);
    char buffer[5000];
    //getchar();
    fgets(buffer,4999, stdin);
    if (buffer[0]!='y' && buffer[0]!='n') {
		printf("Вводите только y или n\n");
		goto snova;
	}
    return buffer[0];
}
char* inputComand() {
    char buffer[100];
    if (!fgets(buffer, sizeof(buffer), stdin)) return NULL;

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[--len] = '\0';
    }
    if (len < 3) return NULL;   // короткая команда

    char* com = (char*) malloc(3 * sizeof(char));
    com[0] = buffer[0];
    com[1] = buffer[1];
    com[2] = buffer[2];
    return com;
}

