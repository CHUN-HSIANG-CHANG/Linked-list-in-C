/* 
編譯器版本: TDM-GCC 4.9.2 64-bit Release
*/ 

#include <stdio.h>
#include <stdlib.h>
/*定義資料結構*/
typedef struct node* node_pointer;
typedef struct node node;
typedef struct list list;

struct node{
	int data;
	node_pointer link;
};

struct list{
    int count;
    node_pointer pos;
    node_pointer rear;
    node_pointer head;
};

/*函數原型*/
void createList(list* list);
int insertNode(list* list, node_pointer pPre, int dataIn);
void deleteNode(list* list, node_pointer pPre, node_pointer pLoc, int* dataOut);
int searchList(list list, node_pointer* pPre, node_pointer* pLoc, int target);
int getNext(list* list, int fromWhere, int* dataOut);
void destroyList(list* list);
void addNode(list* list, int dataIn);
void removeNode(list* list, int key);
char menu();
void printList(list list);
int getData();

int main(){
    printf("Welcome to Student ID Management System.\n");
    
    list List;
    
    int dataIn;
    int key;
    char option;
    
    createList(&List);
       
    while(option != 'Q' && option != 'q'){
        option = menu();
        
        //add Node
        if(option == 'A' || option == 'a'){
           dataIn = getData();
           addNode(&List, dataIn);
        }        
        
        //remove Node
        else if(option=='D' || option=='d'){
           printf("Enter the student ID to be deleted: ");
           scanf("%d",&key);
           removeNode(&List, key);
        }     
        
        //print List
        else if(option=='P' || option=='p'){
           printList(List); 
        }               
    }
    
    destroyList(&List);
    
    printf("Exploration complete. Thank you.\n");
    
    system("pause");
    return 0;
}

int getData(){
    int dataIn;
    
    printf("Enter the student ID you want add: ");
    scanf("%d",&dataIn);
    
    return dataIn;
}

int insertNode(list* list, node_pointer pPre, int dataIn){
    node_pointer pNew;
    pNew = malloc(sizeof(node));
    
    if(pNew == NULL){
        fprintf(stderr,"The memory is full.\n");
        return 0;
    }
    
    pNew->data = dataIn;
    pNew->link = NULL;
    
    if(pPre == NULL){
        pNew->link = list->head;
        list->head = pNew;
    }
    else{
        pNew->link = pPre->link;
        pPre->link = pNew;
    }
    
    if(pNew->link == NULL){
        list->rear = pNew;
    }
    
    list->count++;
    return 1;
}

void deleteNode(list* list,node_pointer pPre, node_pointer pLoc,int* dataOut){
	
	*dataOut = pLoc->data;
	if(pPre == NULL)//要刪除的是第一個節點 
	{
		list->head = pLoc->link;
		//要將第二個節點設為 head(第一個節點) 
	}
	else
	{
		pPre->link = pLoc->link;
		//前一個節點接到下一個位置 
	}
	
	
	if(pLoc->link == NULL)	//如果要刪除的節點是最後一個節點 
	{
		list->rear = pPre;
		//要將前一個節點設定為 rear(最後一個節點)
	} 
	
	free(pLoc);
	list->count--;	//節點總數量減少 
    
}

int searchList(list list, node_pointer* pPre, node_pointer* pLoc, int target){
		
    *pPre = NULL;
    *pLoc = list.head;
    
	if(list.count==0){
		//printf("The list is empty.\n");
		return 0;
	}	
    
    if(target > list.rear->data){
        *pPre=list.rear;
        *pLoc=NULL;
        //printf("Error:Target is greater than the last node.\n");
        return 0;
    }
	
	while(target > (*pLoc)->data){
		*pPre=*pLoc;
		*pLoc=(*pLoc)->link;
	}

	if(target == (*pLoc)->data){
    	//printf("Found");
		return 1;
    }
	else{
		//printf("Not Found");
		return 0;
    }
}

int getNext(list* list, int fromWhere, int* dataOut){
    int success = 0;
    if(fromWhere==0){
        if(list->count==0){
            success = 0;
        }else{
            list->pos=list->head;
            *dataOut=list->pos->data;
            success = 1;
        }
    }else{
        if(list->pos->link==NULL){
            success = 0;
        }else{
            list->pos=list->pos->link;
            *dataOut=list->pos->data;
            success = 1;
        }    
    }
    return success;	  	
}

void createList(list* list){
    list->head = NULL;
    list->pos = NULL;
    list->rear = NULL;
    list->count = 0;
}

void destroyList(list* list){
    node_pointer deletePtr;
    deletePtr = malloc(sizeof(node));
    
    if(list->head){
        while(list->count > 0){
            deletePtr = list->head;
            list->head = list->head->link;
            list->count -=1;
            free(deletePtr);
        }
    }
}

char menu(){
  int valid=0;
  char choice;
  printf("\n......MENU......\n");
  printf("A:add new data\n");
  printf("D:delete data\n");
  printf("P:print list\n");
  printf("Q:quit\n");
  printf("Enter your choice: ");
  while(valid==0){

	fflush(stdin);
  	scanf(" %c",&choice);
  	
	switch(choice){
	    case 'A':
		case 'D':
		case 'P':	
		case 'Q':
		case 'a': 
		case 'd':
		case 'p':	
		case 'q':
			valid=1;
			break;
		default:
			printf("Invalid choice, Choices are <A,D,P,Q>");
	}
  }
  printf("................\n\n");
  return choice;
}

void addNode(list* list, int dataIn){
    node_pointer pPre;
    node_pointer pLoc;
    int found,success;
    found=searchList(*list, &pPre, &pLoc,dataIn);
    if(found==1){
        printf("Error:Data already in list. Not added.\n");
    }
    else{
        success=insertNode(list, pPre,dataIn);
        if(success==0){
        	printf("Error:Out of memory.Program quitting.\n");
        }else{
        	printf("Data added successfully!\n");
		}
    }
}

void removeNode(list* list, int key){
    int found ;    
    int dataOut;
    node_pointer pPre;
	node_pointer pLoc;
    
    found = searchList(*list,&pPre,&pLoc,key);
    
    if(found==1){
    	deleteNode(list,pPre,pLoc, &dataOut);
    	printf("Data deleted successfully!\n");
    }else{
    	printf("Error: Key not in list.\n");
	}
}

void printList(list list){
    int count = 0;
    int moreData;
    int data;
	
    if(list.count == 0){
    	printf("No data in list.\n");
    }else{
        printf("**** Begin Data Print ****\n");
        count = 0;
        moreData = getNext(&list, 0, &data);
        while(moreData == 1){
            count++;
            printf("student[%d]: %d\n", count, data);
            moreData = getNext(&list, 1, &data);
        }
        printf("**** End Data Print ****\n");
    }
}
