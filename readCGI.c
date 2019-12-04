#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main(void) {
	int gold=10;//will reset later (if query string doesnt have gold leave as it is else update)

	    char* input=  (getenv("QUERY_STRING"));
	    //since it follows a format conveniently delimited by "&" and "=", we will make use
	    //of strtok to extract the fields
	    char* token = strtok(input, "=&");
	    char * field[4];
	    int i=0;
	    int counter;

	    while (token!= NULL){
	        field[i]=token;
	        counter++;
	        token=strtok(NULL,"=&");
	        i++;
	    }
	    if(counter>2){
	    	if(field[2]=="gold"){
	    		gold=atoi(field[3]);
	    	}


	    }
	    FILE *fp = fopen("cgi.txt","a");
	    if (fp == NULL){
	        printf("Error: Could not save your input to database<br/>");

	    }
	    else {
	        time_t current_time;
	        char * timeinfo;
	        current_time = time(NULL);
	        timeinfo = ctime(&current_time);
	        fprintf(fp,"%s has sent you the message '%s' on %s", field[1],field[3], timeinfo);

	        fclose(fp);
	    }



	    printf("Content-Type:text/html\n\n");
	    printf("<html>");
	    printf("<body><center>");
	    printf("<form name=\"input\" action=\"https://www.cs.mcgill.ca/~ohussa/cgi-bin/addgold.cgi\" method=\"get\">");
	    printf("Successfully saved your input to database<br/>");
	    for (int i = 0; i <counter-1; i++)
	        {
	        	printf("field[%d] is %s", i,field[i]);
	        }
	    printf("counter -2 is %d",(counter));
	    if(counter-2>=2){
	    	//printf("entered gold if");
	        if(strstr(field[2],"gold")!=NULL){

	        		gold=atoi(field[3]);
	    		if((strcmp(field[1],"206")==0) && (gold==90)){// && coins==90
	    	    printf("<h1>Correct answer</h1>");
	    	gold=gold+10;
	    	//printf("<br/><a href='./addgold.cgi'>Click Here to go back</a>");//change to submit button
	    	printf("<h1>You Won !</h1>");
	    }
	    else if((strstr(field[1],"206")!=NULL) && (gold<90)){
	    	printf("<h1>Correct answer</h1>");
	    	gold=gold+10;
	    	printf("<input type='hidden' name='gold' value='%d'>", gold);
	    	printf("<input type=\"submit\" value=\"Press Here to go back\">");
	    }
	    else if (strcmp(field[1],"NORTH")==0){
	    	printf("<br/><a href='https://www.cs.mcgill.ca/~lmolli/cgi-bin/addgold.cgi?gold=%d'>Click Here to go NORTH</a>",gold);


	    }
	    else if (strcmp(field[1],"SOUTH")==0){
	    	printf("<br/><a href='https://www.cs.mcgill.ca/~ababs/'>Click Here to go SOUTH</a>");

	    }
	    else if (strcmp(field[1],"EAST")==0){
	    	printf("<br/><a href='https://www.cs.mcgill.ca/~afranc40/'>Click Here to go EAST</a>");

	    }
	    else if (strcmp(field[1],"WEST")==0){
	    	printf("<br/><a href='https://cs.mcgill.ca/~yteng1/'>Click Here to go WEST</a>");

	    }
	    else if(strcmp(field[1],"GOLD")==0){
	    	printf("<input type='hidden' name='gold' value='10'>");
	    	printf("<br/>You have  gold coins.");
	    	printf("<br/><a href='..'>Click Here to go back</a>");
	    }
	    else{
	    		printf("<h1>Incorrect answer</h1>");
	    		printf("<br/>You have lost 5 gold coins. But you have not lost yet1");
	    		printf("<br/><a href='..'>Click Here to go back</a>");
	    }

	        	}
	        }
	        else{
	        	printf("in else hooray");
	        	if((strcmp(field[1],"206")==0) && (gold==90)){

	        		printf("<h1>Correct answer</h1>");
	        		printf("<h1>You Won !</h1>");
	        	}
	        	else if((strstr(field[1],"206")!=NULL) && (gold<90)){
	        		printf("<h1>Correct answer</h1>");
	        		gold=gold+10;
	        		printf("<input type='hidden' name='gold' value='10'>");
	        		printf("<input type=\"submit\" value=\"Press Here to go back\">");
	        	}
				else if(strcmp(field[1],"NORTH")==0){
				printf("<br/><a href='https://www.cs.mcgill.ca/~lmolli/'>Click Here to go NORTH</a>");
				}
				else if(strcmp(field[1],"SOUTH")==0){
				printf("<br/><a href='https://www.cs.mcgill.ca/~ababs/'>Click Here to go SOUTH</a>");
				}
				else if(strcmp(field[1],"EAST")==0){
				printf("<br/><a href='https://www.cs.mcgill.ca/~afranc40/'>Click Here to go EAST</a>");
				}
				else if(strcmp(field[1],"WEST")==0){
					printf("<br/><a href='https://cs.mcgill.ca/~yteng1/'>Click Here to go WEST</a>");
				}
				else if(strcmp(field[1],"GOLD")==0){
					printf("<input type='hidden' name='gold' value='10'>");
					printf("<br/>You have  gold coins.");
					printf("<br/><a href='..'>Click Here to go back</a>");
				}
				else{
					printf("<h1>Incorrect answer</h1>");
					printf("<br/>You have lost 5 gold coins. But you have not lost yet1");
					gold=gold-5;
					printf("<br/><a href='..'>Click Here to go back</a>");
				}
				//printf("<form name=\"input\" action=\"https://www.cs.mcgill.ca/~ohussa/cgi-bin/addgold.cgi?%d\" method=\"get\">",gold);

	        }
			printf("</form>");
			printf("</center></body>");
			printf("</html>");
	        return 0;
}
