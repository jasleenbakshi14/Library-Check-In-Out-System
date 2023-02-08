#include "defs.h"

/* Function: loadBooks
   Purpose: reads the data from the txt file and adds the book to the given book collection
   in:
   out: 
   return: n/a
*/

void loadBooks(BookListType *books) {
	int id = 1001;
	FILE *bkfile;
	BookType *book;
	char buffer[MAX_BUFF];
	char title[MAX_STR];
	char author[MAX_STR];
	int year;
	int status;
	bkfile = fopen("booksData.txt", "r");
	if(!bkfile) {
		printf("ERROR: could not open file\n");
		exit(1);
	}
	while(1){
	fgets(title, MAX_STR, bkfile);
	title[strlen(title)-1] = '\0';
	fgets(author, MAX_STR, bkfile);
	author[strlen(author) -1] = '\0';
	fgets(buffer, MAX_BUFF, bkfile);
	sscanf(buffer, "%d", &year);
	fgets(buffer, MAX_BUFF, bkfile);
	sscanf(buffer, "%d", &status);
	if(feof(bkfile)){
		break;
}
	initBook(id, title, author, year, status, &book);
	addBook(books,book);
	id++;
	}
	fclose(bkfile);
}
	
/* Function: initLibrary
   Purpose: load book data and store, printing the contents of the book and storing it into a long stong
   in: name of the library
   out: new library
   return: n/a
*/	
void initLibrary(LibraryType **library, char *n) {
	char string[MAX_BUFF];
	char head[MAX_ARR];
	char tail[MAX_ARR];
	
	LibraryType *new = (LibraryType*) malloc(sizeof(LibraryType));
	strcpy((new)->name,n);
	initList(&new->books);
	loadBooks(&new ->books);
	printf("\n%s\n", n);
	printf("\n%-5s : %-40s : %-20s : %-5s : %-50s\n", "ID", "TITLE", "AUTHOR", "YEAR", "STATUS");

printf("------------------------------------------------------------------------------------------------------------------\n");
	formatBooks(&new ->books, string);
	formatBook(new ->books.head ->data, head);
	formatBook(new ->books.tail ->data, tail);
	printf("%s\n", string); 
	printf("--HEAD: %s", head);
	printf("--TAIL: %s\n", tail); 
	*library = new;
}
/* Function: checkOutBook
   Purpose: check that the book is currently checked in
   in: 
   out: 
   return: C_BAD_STATUS or C_BOOK_NOT_FOUND
*/
int checkOutBook(LibraryType *lib, int bookId) {
	BookType *book;
	if(findBook(&lib -> books, bookId, &book) == 0){
		if(book -> status == CHECKED_IN) {
		book ->status = 1;
			return C_OK;
		} else if (book ->status == CHECKED_OUT){
			return C_NOK;
		} else {
			return C_BAD_STATUS;
		}
	}
	return C_BOOK_NOT_FOUND;
}

/* Function: checkInBook
   Purpose: check that the book is currently checked out
   in: 
   out: 
   return: C_BAD_STATUS or C_BOOK_NOT_FOUND
*/
int checkInBook(LibraryType *lib, int bookId) {
	BookType *book;
	if(findBook(&lib -> books, bookId, &book) == 0){
		if(book -> status == CHECKED_OUT) {
		book ->status = 1;
			return C_OK;
		} else if (book ->status == CHECKED_IN){
			return C_NOK;
		} else {
			return C_BAD_STATUS;
		}
	}
	return C_BOOK_NOT_FOUND;
}
/*
  Function:  cleanupLibrary
  Purpose:   frees the memory associated with the books in the list
  Parameters:
    out:     list
    return:  n/a
*/
void cleanupLibrary(LibraryType* list){
	NodeType *currNode, *nextNode;
 
  while (currNode != NULL) {
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
}
