#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tyring.h"

int main()
{
	char option;
	int alfabethExC;
	nachalo:
	do {
		printf("Что вы хотите сделать?\n\t1 - Создать новую машину Тьюринга\n\t2 - Загрузить существующую машину Тьюринга\n\t3 - Сгенерировать машину Тьюринга\n");
		option= inputChar();
	} while(option!='1' &&  option!='2' &&  option!='3');
	char buffer[5000];
	FILE* fn1;
	switch(option) {
		case '1':
			printf("Введите внешний алфавит (все символы (кроме символа пустой ячейки @) без пробелов и запятых: ");
			fgets(buffer, sizeof(buffer), stdin);
			// убираем перевод строки, если он есть
			size_t len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';
				len--;
			}
			alfabethExC = len + 1;              // +1 под '@'
		break;
		case '2':
			char filename[100];
			printf("Введите имя файла со схемой: ");
			fgets(filename, sizeof(filename), stdin);
			filename[strlen(filename)-1]='\0';
			fn1= fopen(filename, "r");
			if(fn1) {
				fgets(buffer, sizeof(buffer), fn1);
				if(strcmp(buffer, "THIS IS SXEMA\n")==0) {
					fgets(buffer, sizeof(buffer), fn1);
					alfabethExC=atoi(buffer);
					if (alfabethExC==0) {
						printf("Количество символов внешнего алфавита, не может быть 0, вероятно файл %s порченый\n", filename);
						fclose(fn1);
						goto nachalo;
					}
				} else {
					printf("Файл %s не содержит сигнатуру файла схемы\n");
					fclose(fn1);
					goto nachalo;
				}
			} else {
				printf("Файл %s не удалось открыть\n", filename);
				goto nachalo;
			}
		break;
		case '3':
			
		break;
	}
	char alfabethEx[alfabethExC+1];
	int c=0;
	List* sost=createList();
	List2d3* shema = createList2d3(alfabethExC);
	switch(option) {
		case '1':
			alfabethEx[0] = '@';
			for (int i = 1; i < alfabethExC; i++) {
				alfabethEx[i] = buffer[i - 1];
			}
			alfabethEx[alfabethExC] = '\0';
			do {
				printShema(shema, sost, alfabethEx, alfabethExC);
				char cod=inputChar();
				if (cod == '\0') {
    					printf("Состояние не введено, попробуйте снова\n");
    					continue;
				}
				if(find_itemNum(sost,cod)!=-1) {
					printf("\nНельзя создавать состояния с одинаковыми кодами\n");
					continue;
				}
				add_item_to_end(sost,cod);
				for (int i = 0; i < alfabethExC; i++) {
    					printShema(shema, sost, alfabethEx, alfabethExC);
    					char* str = inputComand();
    					if (str == NULL) {
        					i--;
        					printf("\nКоманда должна состоять из 3 символов\n");
        					continue;
    					}

    					char* proverka = "LlRrSs";

    					if (strchr(alfabethEx, str[0]) == NULL) {
        					free(str);
        					i--;
        					printf("\nСимвол '%c' не входит во внешний алфавит\n", str[0]);
        					continue;
    					}
    					if (strchr(proverka, str[1]) == NULL) {
        					free(str);
        					i--;
        					printf("\nДвижение '%c' недопустимо (LlRrSsЛлПпНн)\n", str[1]);
        					continue;
    					}

    					List2d3* tmp = getLing(shema, c);
    					if (tmp == NULL) {
        					free(str);
        					printf("\nВнутренняя ошибка: строка %d не найдена\n", c);
        					break;
    					}

    					tmp->data[i][0] = str[0];
    					tmp->data[i][1] = str[1];
    					tmp->data[i][2] = str[2];
    					free(str);
				}
				addList(shema);
				c++;
				dobavitstroku:
			} while(answer("Еще одна строка [y/n]? ")=='y');
			vtoroyraz:
			if (answer("Хотите удалить какую либо строку [y/n]? ")=='y') {
				printf("Введите код состочния строку котрого хотите удалить: ");
				char rmCod = inputChar();
				int codN = find_itemNum(sost, rmCod);
				if(codN==-1) {
					printf("Нет такого состочния\n");
					goto vtoroyraz;
				}
				subListIn(&shema,codN);
				delete_item(sost, find_item(sost, rmCod));
				printShema(shema, sost, alfabethEx, alfabethExC);
				goto dobavitstroku;
		}
			save:
			if (answer("Хотите сохранить машину Тьюринга [y/n]? ")=='y') {
				printf("Введите имя файла для сохранеия (существующий файл будет перезаписан): ");
				char filename[100];
				fgets(filename, sizeof(filename)-5, stdin);
				for(int i=0; i<strlen(filename); i++) {
					if(filename[i]==' ' || filename[i]=='\n') {
						filename[i]='\0';
						break;
					}
				}
				strcat(filename, ".sxe");
				//printf("%s\n", filename);
				FILE * fn = fopen(filename, "w");
				if (fn) {
					saveShema(shema, sost, alfabethEx, alfabethExC, fn);
					fclose(fn);
					printf("Схема записана в файл %s\n", filename);
				} else {
					printf("Файл  %s не удалось создать или открыть\n", filename); 
					goto save;
				}
			}
		break;
		case '2':
			int g=0;
			fgets(buffer, sizeof(buffer), fn1);
			for(int i=0; i<strlen(buffer); i++){
				printf("%c", buffer[i]);
				if(i>0 && buffer[i-1]=='|' && buffer[i]!='\n' && buffer[i+1]!='q') {
					alfabethEx[g]=buffer[i];
					g++;
				}
			}
			alfabethEx[alfabethExC]='\0';
			while(fgets(buffer, sizeof(buffer), fn1)) {
				add_item_to_end(sost, buffer[2]);
				List2d3* tmp=getLing(shema,c);
				g=0;
				for(int i=0; i<strlen(buffer); i++){
					printf("%c",buffer[i]);
					char* prof= "LlRrSs";

					if(strchr(prof, buffer[i])!=NULL) {
						tmp->data[g][0]=buffer[i-1];
						tmp->data[g][1]=buffer[i];
						tmp->data[g][2]=buffer[i+1];
						g++;
					}
				}
				c++;
				addList(shema);
			}
			fclose(fn1);
			printf("\n");
			if(answer("Хотите отредактировать схему [y/n]? ")=='y') {
				goto dobavitstroku;
			}
		break;
		case '3':
			
		break;
	}
	List* lenta=createList();
	add_item_to_begin(lenta, '@');
	printf("Введите начальное слово(без символов пустого символа в начале и конце: ");
	fgets(buffer, sizeof(buffer), stdin);
	for(int i=0; i<strlen(buffer)-1; i++) {
		if(strchr(alfabethEx, buffer[i])!=NULL) {
			add_item_to_end(lenta, buffer[i]);
		}
	}
	add_item_to_end(lenta, '@');
	qwer:
	printf("Определите начальное положение и состояние записав его код под одним из символов\n");
	char* lentaStr=convertList(lenta);
	printf("%s\n",lentaStr);
	free(lentaStr);
	fgets(buffer, sizeof(buffer), stdin);
	int pos = -1;            // позиция в ленте
	int col = 0;             // текущая колонка
	for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
		if (buffer[i] == ' ') {
			col++;
		} else if (find_itemNum(sost,buffer[i])!=-1) {
			pos = col;
			break;
		}
	}
	if (pos==-1) {
		printf("\nНе найденно состояние с таким кодом\n");
		goto qwer;
	}
	c=find_itemNum(sost, buffer[col]);
	//printf("Позиция = %d, состояние = %c %d\n", pos, buffer[col], c);
	do {
		List2d3 * tmp = getLing(shema, c);
		Node * sim = getItemLink(lenta,pos);
		if (sim == NULL) {
            printf("Ошибка: позиция %d вне ленты (длина %d)\n", pos, lengList(lenta));
            break;
        }
		char oldSim=sim->data;
		int idx = indexOfChar(alfabethEx,oldSim);
		if (idx<0) idx=0;
		sim->data=tmp->data[idx][0];
		printf("Выполнена команда: %c%c%c\n", tmp->data[idx][0],tmp->data[idx][1],tmp->data[idx][2]);
		char nextCod=tmp->data[idx][2];
		if(find_itemNum(sost,nextCod)!=-1) {
			c=find_itemNum(sost, tmp->data[idx][2]);
		} else {
			if(pos!=0) {
		Node* kray1=getItemLink(lenta,0);
		if(kray1->data=='@' && kray1->next->data=='@') {
			deleteFirst(lenta);
			pos--;
		}
	}
		if(pos!=lengList(lenta)-1) {
		Node* kray2=getItemLink(lenta,lengList(lenta)-1);
		if(kray2->data=='@' && kray2->prev->data=='@') {
			deleteLast(lenta);
		}
	}
		printf("Машина завершила работу\n");
		lentaStr=convertList(lenta);
		printf("%s\n",lentaStr);
		free(lentaStr);
		for(int k=0; k<pos; k++) {
			printf(" ");
		}
		printf("%c\n",nextCod);
			break;
		}
		char* proverca1 ="Ll";
		if(strchr(proverca1, tmp->data[idx][1])!=NULL) {
			//printf("-\n");
			pos--;
			if(pos<0) {
				pos=0;
				add_item_to_begin(lenta, '@');
			}
		}
		char* proverca2 ="Rr";
		if(strchr(proverca2, tmp->data[idx][1])!=NULL) {
			pos++;
			if(pos>=lengList(lenta)) {
				add_item_to_end(lenta, '@');
			}
		}
		if(pos!=0) {
		Node* kray1=getItemLink(lenta,0);
		if(kray1->data=='@' && kray1->next->data=='@') {
			deleteFirst(lenta);
			pos--;
			//printf("-\n");
		}
	}
		if(pos!=lengList(lenta)-1) {
		Node* kray2=getItemLink(lenta,lengList(lenta)-1);
		if(kray2->data=='@' && kray2->prev->data=='@') {
			deleteLast(lenta);
		}
	}
		printf("Новое стотояние машины\n");
		lentaStr=convertList(lenta);
		printf("%s\n",lentaStr);
		free(lentaStr);
		for(int k=0; k<pos; k++) {
			printf(" ");
		}
		printf("%c\n",nextCod);
		//rintf("Позиция = %d, состояние = %c %d\n", pos, buffer[col], c);
	} while(answer("Завершить работу [y/n]? ")=='n');
	freeListAndSelf(lenta);
	freeListAndSelf(sost);
	freeList2d3(&shema);
    return 0;
}
