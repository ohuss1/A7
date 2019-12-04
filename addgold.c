#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	 char* input=  (getenv("QUERY_STRING"));
	 char* token = strtok(input, "=&");
	 char * field[4];
	 int i=0;
	 int counter;
	 int goldA=0;
	 while (token!=NULL){
	     		        field[i]=token;
	     		        counter++;
	     		        token=strtok(NULL,"=&");
	     		        i++;
	     		    }
	 if((field[2]=="gold")){
		 goldA=atoi(field[3]);
	 }

	 FILE *m = fopen("../index.html","rt");
	 char buffer[800];
	 char c;
	 if (m == NULL){
		 printf("Error: Could not save your input to database<br/>");
    }
	 else{
		 	 while ( !feof(m)){
		 	 printf("\n");
		 	 if (fgets(buffer,799,m) != NULL && (c!='\n') && (buffer[0]!='\n'))
		 	 {
		 		 int j=0,i=0,k=0;
		 	     int characters1=0;
		 	     if(strstr(buffer,"</form>")!=NULL){
		 	    	 printf("<input type=\"hidden\" name=\"gold\" value=\"10\">");
		 	     }
		 	     printf("%s", buffer);
		 	     memset(buffer, '\0', sizeof(buffer));
		 	 }
		  }

	 }

 fclose(m);
 return 0;
}
