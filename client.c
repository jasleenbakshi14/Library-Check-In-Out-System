#include "defs.h"


int main()
{
  int  choice = -1;
  int clientSocket;
  setupClientSocket(&clientSocket);
  char req[MAX_STR];
  char resp[MAX_BUFF];
  
  while (1) {

   clientMenu(&choice);

   switch(choice) {

      case 1:   // Print books
	sprintf(req, "%d", REQ_RET_BOOKS);
	sendData(clientSocket, req);
	rcvData(clientSocket, resp);
	printf("%s", resp);
        break;

      case 2:   // Check out a book

        break;

      case 3:   // Check in a book

        break;

      case 0:   // Close everything
      sprintf(req, "%d", REQ_CLOSE);
	sendData(clientSocket, req);
	exit(-1);


        break;

      default:
        printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

