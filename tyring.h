#include <stdio.h>
// ---------- Структуры ----------

typedef struct IntNode {
    int data;
    struct IntNode* prev;
    struct IntNode* next;
} IntNode;

typedef struct IntList {
    IntNode* head;
    IntNode* tail;
} IntList;


// ---------- Создание ----------

IntList* createIntList() {
    IntList* list = (IntList*) malloc(sizeof(IntList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}


// ---------- Добавление ----------

int add_int_to_end(IntList* list, int item) {
    if (list == NULL) return -1;

    IntNode* newNode = (IntNode*) malloc(sizeof(IntNode));
    if (newNode == NULL) return -2;

    newNode->prev = newNode->next = NULL;
    newNode->data = item;

    if (list->tail) {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    } else {
        list->head = list->tail = newNode;
    }
    return 0;
}

int add_int_to_begin(IntList* list, int item) {
    if (list == NULL) return -1;

    IntNode* newNode = (IntNode*) malloc(sizeof(IntNode));
    if (newNode == NULL) return -2;

    newNode->prev = newNode->next = NULL;
    newNode->data = item;

    if (list->head) {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
    } else {
        list->head = list->tail = newNode;
    }
    return 0;
}


// ---------- Удаление ----------

int delete_int_item(IntList* list, IntNode* node) {
    if (node == NULL) return -1;
    if (list == NULL) return -2;

    if (node->prev) node->prev->next = node->next;
    else            list->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else            list->tail = node->prev;

    free(node);
    return 0;
}

int delete_int_first(IntList* list) {
    if (list == NULL) return -1;
    if (list->head == NULL) return -2;

    IntNode* target = list->head;
    list->head = target->next;

    if (list->head != NULL) list->head->prev = NULL;
    else                    list->tail = NULL;

    free(target);
    return 0;
}

int delete_int_last(IntList* list) {
    if (list == NULL) return -1;
    if (list->tail == NULL) return -2;

    IntNode* target = list->tail;
    list->tail = target->prev;

    if (list->tail != NULL) list->tail->next = NULL;
    else                    list->head = NULL;

    free(target);
    return 0;
}

int delete_int_by_value(IntList* list, int item) {
    if (list == NULL) return -1;

    IntNode* current = list->head;
    while (current != NULL) {
        if (current->data == item) {
            return delete_int_item(list, current);
        }
        current = current->next;
    }
    return -2;
}

int delete_int_at(IntList* list, int index) {
    if (list == NULL || index < 0) return -1;

    IntNode* current = list->head;
    int i = 0;
    while (current != NULL && i != index) {
        current = current->next;
        i++;
    }
    if (current == NULL) return -2;
    return delete_int_item(list, current);
}


// ---------- Доступ ----------

int lengIntList(IntList* list) {
    IntNode* current = list->head;
    int i = 0;
    while (current) {
        i++;
        current = current->next;
    }
    return i;
}

int getIntItem(IntList* list, int n) {
    IntNode* current = list->head;
    int i = 0;
    while (current) {
        if (i == n) return current->data;
        current = current->next;
        i++;
    }
    return 1;   // или любое «дефолтное» значение, если n вне границ
}

IntNode* getIntItemLink(IntList* list, int n) {
    IntNode* current = list->head;
    int i = 0;
    while (current) {
        if (i == n) return current;
        current = current->next;
        i++;
    }
    return NULL;
}

int find_int_itemNum(IntList* list, int item) {
    IntNode* current = list->head;
    int i = 0;
    while (current) {
        if (current->data == item) return i;
        current = current->next;
        i++;
    }
    return -1;
}

IntNode* find_int_item(IntList* list, int item) {
    IntNode* current = list->head;
    while (current) {
        if (current->data == item) return current;
        current = current->next;
    }
    return NULL;
}


// ---------- Очистка ----------

void freeIntList(IntList* list) {
    if (list == NULL) return;

    IntNode* current = list->head;
    while (current != NULL) {
        IntNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void freeIntListAndSelf(IntList* list) {
    if (list == NULL) return;

    IntNode* current = list->head;
    while (current != NULL) {
        IntNode* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}


// ---------- Преобразование в массив (аналог convertList) ----------

int* convertIntList(IntList* list) {
    int len = lengIntList(list);
    int* arr = (int*) malloc(len * sizeof(int));
    IntNode* current = list->head;
    for (int i = 0; i < len; i++) {
        arr[i] = current->data;
        current = current->next;
    }
    return arr;
}


// ---------- Печать (для отладки) ----------

void printIntList(IntList* list) {
    IntNode* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
typedef struct List2d3 {
     char** data;
     int* dataInt;
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
        newList->data[i]=(char*) malloc(2*sizeof(char));
        for(int j=0; j<2; j++) {
			newList->data[i][j]='\0';
		}
    }
	newList->dataInt= (int*) malloc(sizeof(int)*count);
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
int saveShema(List2d3* shema, IntList* sost, char* alfavit, int count, FILE* fn) {
	fprintf(fn, "THIS IS SXEMA\n");
	fprintf(fn, "%d\n", count);
	fprintf(fn, "|qqq|");
	for (int i = 0; i<count; i++) {
		fprintf(fn, "%c  |", alfavit[i]);
	}
	IntNode* current = sost->head;
	int c=0;
	while (current) {
		fprintf(fn, "\n|q%d |", current->data);
		List2d3* tmp=getLing(shema, c);
		for(int i=0; i<shema->count; i++){
			fprintf(fn, "%c%c%d|", tmp->data[i][0], tmp->data[i][1], tmp->dataInt[i]);
		}
		c++;
		current=current->next;
	}
}
int printShema(List2d3* shema, IntList* sost, char* alfavit, int count) {
	printf("\n|qqq|");
	for (int i = 0; i < count; i++) {
		printf("%c  |", alfavit[i]);
	}
	IntNode *current = sost->head;
	int c=0;
	printf("\n|q");
	while (current)
	{
		List2d3* tmp=getLing(shema, c);
		printf("%d |", current->data);
		for(int i=0; i<shema->count; i++) {
			if(tmp->data[i][0]=='\0') {
				return 0;
			}
			for(int j=0; j<2; j++) {
				printf("%c", tmp->data[i][j]);
			}
			printf("%d|", tmp->dataInt[i]);
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
	free(last->dataInt);
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
	free(target->dataInt);
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
		free(current->dataInt);
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
	int len =lengList(list);
	char* str = (char*) malloc(lengList(list)+1*sizeof(char));
	for(int i=0; i<len; i++) {
		str[i]=current->data;
		current=current->next;
	}
	str[len]='\0';
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

char** splitString(const char* str, char delim, int* outCount) {
    *outCount = 0;
    if (str == NULL) return NULL;

    // 1. Находим первое и последнее вхождение разделителя
    const char* first = strchr(str, delim);
    if (first == NULL) return NULL;              // разделителя нет вообще

    const char* last = strrchr(str, delim);
    if (last == first) return NULL;              // только один разделитель — нечего делить

    // 2. Идём между first+1 и last, считая разделители
    const char* p = first + 1;
    int count = 1;                               // минимум одна подстрока между first и last
    while (p < last) {
        if (*p == delim) count++;
        p++;
    }

    // 3. Выделяем массив указателей
    char** parts = (char**) malloc(count * sizeof(char*));
    if (parts == NULL) return NULL;

    // 4. Заполняем подстроки
    int idx = 0;
    p = first + 1;
    const char* start = p;
    while (p <= last) {
        if (p == last || *p == delim) {
            int len = (int)(p - start);
            parts[idx] = (char*) malloc((len + 1) * sizeof(char));
            for (int i = 0; i < len; i++) {
                parts[idx][i] = start[i];
            }
            parts[idx][len] = '\0';
            idx++;
            start = p + 1;
        }
        p++;
    }

    *outCount = count;
    return parts;
}
void freeSplit(char** parts, int count) {
    if (parts == NULL) return;
    for (int i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

// ============================================================
// Vyrazhenia (односвязный узел)
// ============================================================

typedef struct Vyrazhenia {
    int mnozhitel;
    int slogaemoe;
    struct Vyrazhenia* link;
} Vyrazhenia;

// ============================================================
// QueueVyrazh (очередь на основе односвязного списка)
// ============================================================

typedef struct QueueVyrazh {
    Vyrazhenia* head;   // извлекаем отсюда
    Vyrazhenia* tail;   // добавляем сюда
    int size;
} QueueVyrazh;

// ---------- Геторы для полей Vyrazhenia ----------

int getMnozhitel(Vyrazhenia* v) {
    if (v == NULL) return 0;
    return v->mnozhitel;
}

int getSlogaemoe(Vyrazhenia* v) {
    if (v == NULL) return 0;
    return v->slogaemoe;
}

Vyrazhenia* getLink(Vyrazhenia* v) {
    if (v == NULL) return NULL;
    return v->link;
}

// ---------- Создание ----------

QueueVyrazh* createQueueVyrazh() {
    QueueVyrazh* q = (QueueVyrazh*) malloc(sizeof(QueueVyrazh));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

// ---------- Проверки ----------

int isEmptyQueueVyrazh(QueueVyrazh* q) {
    return (q == NULL || q->head == NULL);
}

int lengQueueVyrazh(QueueVyrazh* q) {
    if (q == NULL) return 0;
    return q->size;
}

Vyrazhenia* getHeadQueueVyrazh(QueueVyrazh* q) {
    if (q == NULL) return NULL;
    return q->head;
}

Vyrazhenia* getTailQueueVyrazh(QueueVyrazh* q) {
    if (q == NULL) return NULL;
    return q->tail;
}

// ---------- Добавление в хвост (enqueue) ----------

int enqueueVyrazh(QueueVyrazh* q, int mnozhitel, int slogaemoe) {
    if (q == NULL) return -1;

    Vyrazhenia* node = (Vyrazhenia*) malloc(sizeof(Vyrazhenia));
    if (node == NULL) return -2;

    node->mnozhitel = mnozhitel;
    node->slogaemoe = slogaemoe;
    node->link = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = node;
    } else {
        q->tail->link = node;
        q->tail = node;
    }
    q->size++;
    return 0;
}

// ---------- Извлечение из головы (dequeue) ----------

Vyrazhenia* dequeueVyrazh(QueueVyrazh* q) {
    if (q == NULL || q->head == NULL) return NULL;

    Vyrazhenia* node = q->head;
    q->head = node->link;
    if (q->head == NULL) q->tail = NULL;
    q->size--;

    node->link = NULL;   // отвязать от очереди
    return node;         // вызывающий освобождает через free()
}

Vyrazhenia* peekQueueVyrazh(QueueVyrazh* q) {
    if (q == NULL || q->head == NULL) return NULL;
    return q->head;
}

// ---------- Поиск по slogaemoe ----------

Vyrazhenia* findQueueVyrazhBySlogaemoe(QueueVyrazh* q, int slogaemoe) {
    if (q == NULL) return NULL;

    Vyrazhenia* current = q->head;
    while (current != NULL) {
        if (current->slogaemoe == slogaemoe) return current;
        current = current->link;
    }
    return NULL;
}

int findQueueVyrazhIndexBySlogaemoe(QueueVyrazh* q, int slogaemoe) {
    if (q == NULL) return -1;

    Vyrazhenia* current = q->head;
    int i = 0;
    while (current != NULL) {
        if (current->slogaemoe == slogaemoe) return i;
        current = current->link;
        i++;
    }
    return -1;
}

// ---------- Удаление по slogaemoe ----------

int deleteQueueVyrazhBySlogaemoe(QueueVyrazh* q, int slogaemoe) {
    if (q == NULL || q->head == NULL) return -1;

    Vyrazhenia* current = q->head;
    Vyrazhenia* prev = NULL;

    while (current != NULL) {
        if (current->slogaemoe == slogaemoe) {
            if (prev == NULL) {
                q->head = current->link;
                if (q->head == NULL) q->tail = NULL;
            } else {
                prev->link = current->link;
                if (current == q->tail) q->tail = prev;
            }
            free(current);
            q->size--;
            return 0;
        }
        prev = current;
        current = current->link;
    }
    return -2;
}

int deleteAllQueueVyrazhBySlogaemoe(QueueVyrazh* q, int slogaemoe) {
    if (q == NULL || q->head == NULL) return 0;

    int removed = 0;
    Vyrazhenia* current = q->head;
    Vyrazhenia* prev = NULL;

    while (current != NULL) {
        if (current->slogaemoe == slogaemoe) {
            Vyrazhenia* toFree = current;
            if (prev == NULL) {
                q->head = current->link;
                if (q->head == NULL) q->tail = NULL;
                current = q->head;
            } else {
                prev->link = current->link;
                if (current == q->tail) q->tail = prev;
                current = prev->link;
            }
            free(toFree);
            q->size--;
            removed++;
        } else {
            prev = current;
            current = current->link;
        }
    }
    return removed;
}

// ---------- Очистка ----------

void freeQueueVyrazh(QueueVyrazh* q) {
    if (q == NULL) return;

    Vyrazhenia* current = q->head;
    while (current != NULL) {
        Vyrazhenia* next = current->link;
        free(current);
        current = next;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void freeQueueVyrazhAndSelf(QueueVyrazh* q) {
    if (q == NULL) return;
    freeQueueVyrazh(q);
    free(q);
}

// ---------- Печать (для отладки) ----------

void printQueueVyrazh(QueueVyrazh* q) {
    if (q == NULL) return;
    Vyrazhenia* current = q->head;
    while (current != NULL) {
        printf("[m=%d, s=%d] ", current->mnozhitel, current->slogaemoe);
        current = current->link;
    }
    printf("\n");
}
int getMnozhitelAt(QueueVyrazh* q, int index) {
    if (q == NULL || index < 0) return -1;
    Vyrazhenia* current = q->head;
    int i = 0;
    while (current != NULL) {
        if (i == index) return current->mnozhitel;
        current = current->link;
        i++;
    }
    return -1;   // индекс за границей
}

int getSlogaemoeAt(QueueVyrazh* q, int index) {
    if (q == NULL || index < 0) return -1;
    Vyrazhenia* current = q->head;
    int i = 0;
    while (current != NULL) {
        if (i == index) return current->slogaemoe;
        current = current->link;
        i++;
    }
    return -1;   // индекс за границей
}
