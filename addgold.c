#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()//testing
{
	 char* input=  (getenv("QUERY_STRING"));
	 char* token = strtok(input, "=&");
	 char * field[4];
	 int i=0;
	 int counter;
	 int goldA=10;
	 while (token!=NULL){
	     		        field[i]=token;
	     		        counter++;
	     		        token=strtok(NULL,"=&");
	     		        if((i>=1) && (strcmp(field[0],"gold")==0)){
	     		        	goldA=atoi(field[1]);
	     		        }
	     		        i++;
	     		    }
	 /*if(strcmp(field[2],"gold")==0){
		 goldA=atoi(field[3]);
	 }*/

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
		 	     if((strstr(buffer,"</form>")!=NULL)){
		 	    	printf("<input type=\"hidden\" name=\"gold\" value=\"%d\">", goldA);
		 	    	//printf("gold is %d", goldA);
		 	     }
		 	     printf("%s", buffer);
		 	     memset(buffer, '\0', sizeof(buffer));
		 	 }
		  }

	 }

 fclose(m);
 return 0;
}
