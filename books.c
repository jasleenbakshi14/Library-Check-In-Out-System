#include "defs.h"

/* 
  Function: initList
  Purpose: initializes the required fields of a given book list
  
*/

void initList(BookListType*list)
{
  list -> head = NULL;
  list -> tail= NULL;
}
/* 
  Function: initBook
  Purpose: initialize the new book’s id,  title, author, year, and availability status from the parameters
  in: id, title, author, year, status
  out: new book
  return: nothing
  
*/
void initBook(int i, char *t, char *a, int y, BookStatusType st, BookType **book) {
 BookType *new =(BookType*) malloc(sizeof(BookType));
 (new) -> id = i;
 strcpy((new) -> title, t);
 strcpy((new) -> author,a);
 (new) -> year = y;
 (new) -> status = st;
 *book = new;
 }
/* Function: addBook
   Purpose: adds new book to the collection in an alphabetical order by the book's title
   in: collection of book and books
   out: nothing

*/

void addBook(BookListType *list, BookType *b){
	NodeType *currNode;
	NodeType *prevNode;
	NodeType *newNode;
	
	currNode = list -> head;
	prevNode = NULL;
	while (currNode != NULL) {
		if (strcmp(b ->title, currNode ->data ->title) < 0){
		break;
	}
	prevNode = currNode;
	currNode = currNode ->next;
	}
	newNode = malloc(sizeof(NodeType));
	newNode ->data = b;
	newNode ->next = NULL;
	
	if (prevNode == NULL){
		list ->head = newNode;
	} else {
		prevNode ->next = newNode;
	}
	newNode ->next= currNode;
	if(currNode == NULL){
		list ->tail = newNode;
}
}
/* Function: findBook
   Purpose: traverses the given book collection to find the book with the given id
   in: 
   out:
   Parameters: b
   returns: C_NOK or C_OK

*/
int findBook(BookListType *list, int id, BookType **b) {
	NodeType *currNode = list ->head;
	while (currNode != NULL){
		if (currNode ->data ->id == id){
		*b = currNode ->data;
		return C_OK;
	}
	currNode = currNode ->next;
}
return C_NOK;
}
/* Function: changeStats
   Purpose: to change the enum value to a string 
   in: the string value
   out: status string
   return: n/a
*/

void changeStats(BookStatusType status, char *chgstatus){
	if(status == CHECKED_IN){
		strcpy(chgstatus, "Checked in");
	}
	
	if(status == CHECKED_OUT){
		strcpy(chgstatus, "Checked out");
	}
	
	if(status == UNDER_REPAIR){
		strcpy(chgstatus, "Under Repair");
	}
	
	if(status == LOST){
		strcpy(chgstatus, "Lost");
	}
}
/* Function: formatBook
   Purpose: formats a string for single books
   in: book
   out: the book string
   return: n/a
*/
void formatBook(BookType *b, char *outStr){
	char statusstr[MAX_STR];
	char singlebook[MAX_BUFF] = {0};
	changeStats(b ->status, statusstr);
	sprintf(singlebook, "%-5d : %-40s : %-20s : %-5d : %-15s\n", b->id, b->title, b->author, b->year, statusstr);
		strcpy(outStr, singlebook);
}
/* Function: changeStats
   Purpose: to change the enum value to a string 
   in: the string value
   out: status string
   return: n/a
*/
void formatBooks(BookListType *list, char *outStr){
	char temp[MAX_ARR];
	char totalbooks[MAX_BUFF] = {0};
	NodeType *currNode = list ->head;
	while(currNode != NULL){
		formatBook(currNode ->data, temp);
		strcat(totalbooks, temp);
		currNode = currNode ->next;
	}
	strcpy(outStr, totalbooks);
}

/*
  Function:  cleanupList
  Purpose:   frees the memory associated with the nodes in the list
  Parameters:
    out:     list
    return:  n/a
*/
    void cleanupList(BookListType *list){
	NodeType *currNode, *nextNode;
        currNode = list->head;
 
  while (currNode != NULL) {
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
}


