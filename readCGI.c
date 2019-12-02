#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//I have changed the aim of this tutorial to make it more extensive as a more profound review
// on cgi,c and to help with the last assignment + finals prep.

// Instead of getting 1 word from the the user, we will get two inputs, one being his name,
// the other being the message. Note that these are assumed to be single-word inputs for convenience
// Moreover, we will add a timestamp in cgi.txt for each message received from the users as review of the time.h library
// We will also provide the user with an hyperlink to go back to original page where data entry was possible

//IMPORTANT (DIRECTORY STRUCTURE)
/*
yourUsername
    public_html
        index.html
        cgi-bin
            readCGI.c
            a.cgi  
            cgi.txt

(Compile using "gcc -o a.cgi ReadCGI.c".The executable a.cgi SHOULD HAVE .cgi as EXTENSION AND NOT .out ELSE YOU WILL END UP DOWNLOLADING
THE FILE EACH TIME YOU CLICK SUBMIT ON THE ORIGINAL WEBPAGE. That's the point of using CGI.)
cgi.txt will be created automatically (after first data entry on webpage) if it doesnt already exist. You can manually add it if you want too.
*/

int main(){

    //I am transmitting data using "get" hence
    //the input from the user will be in the QUERY_STRING environment variable 
    // in the format "name_input=nameofuser&message_input=messagefromuser"
    printf("<input type='hidden' name='gold' value='10'>");
    char* input=  (getenv("QUERY_STRING")); 
    //since it follows a format conveniently delimited by "&" and "=", we will make use
    //of strtok to extract the fields
    char* token = strtok(input, "=&");
    char * field[4];
    int i=0;
    //int coins=10;
    while (token!= NULL){
        field[i]=token;
        token=strtok(NULL,"=&");
        i++;
    }
    //at this point, 
    // field[4] = {"name_input","actualnameofuser","message_input","actualmessagefromuser"}

    //Note that STDOUT is directed to the webpage. Here anything that printed using printf is sent to the webpage.
    printf("Content-Type:text/html\n\n");
    printf("<html>");
    printf("<body><center>");

    //Opening the file
    FILE *fp = fopen("cgi.txt","a");
    if (fp == NULL){
        // if an error occurs
        printf("Error: Could not save your input to database<br/>");

    } else {

        //this is a standard way to get the current timestamp
        time_t current_time;
        char * timeinfo;
        current_time = time(NULL);  //set the time_t struct to the current time
        timeinfo = ctime(&current_time); //generate a textual representation from time_t as a string (char *)

        //Appending the record to the textfile cgi.txt
        fprintf(fp,"%s has sent you the message '%s' on %s", field[1],field[3], timeinfo);
        fclose(fp);

        //printing back to the browser that addition of the record to the database has been successful
        printf("Successfully saved your input to database<br/>");

    }
    

    //Printing back the data input back to the user
    if(strcmp(field[1],"206")==0){// && coins==90
    	printf("<h1>Correct answer</h1>");
    	printf("<h1>You Won !</h1>");
    }
    else if(strcmp(field[1],"206")==0){
    	printf("%s", field[1]);
    	printf("<h1>Correct answer</h1>");
    	//coins=coins+10;
    	printf("<br/>You receive 10 gold. But your journey is not over!");
    	printf("<br/><a href='..'>Click Here to go back</a>");
    }
    else if (strcmp(field[1],"NORTH")==0){
    	printf("<br/><a href='https://www.cs.mcgill.ca/~lmolli/cgi-bin/addgold.cgi?gold=%d'>Click Here to go NORTH</a>",coins);

    }
    else if (strcmp(field[1],"SOUTH")==0){
    	printf("<br/><a href='https://www.cs.mcgill.ca/~ababs/cgi-bin/addgold.cgi?gold=%d'>Click Here to go SOUTH</a>",coins);

    }
    else if (strcmp(field[1],"EAST")==0){
    	printf("<br/><a href='https://www.cs.mcgill.ca/~afranc40/cgi-bin/addgold.cgi?gold=%d'>Click Here to go EAST</a>",coins);

    }
    else if (strcmp(field[1],"WEST")==0){
    	printf("<br/><a href='https://cs.mcgill.ca/~yteng1/cgi-bin/addgold.cgi?gold=%d'>Click Here to go WEST</a>",coins);

    }
    else if(strcmp(field[1],"GOLD")==0){
    	printf("<br/>You have %d gold coins.",coins);
    	printf("<br/><a href='https://cs.mcgill.ca/~ohussa/cgi-bin/addgold.cgi?gold=%d'>Click Here to go back</a>",coins);
    }
    else{
    	/*if(coins==5){

    		printf("<h1>Incorrect answer YOU LOST</h1>");
    		coins=coins-5;
    		printf("<br/>You have lost 5 gold coins."); 
    	//printf("<br/><a href='..'>Click Here to go back</a>");

    	}*/
    	//else{
    		
    		printf("<h1>Incorrect answer</h1>");
    	    //coins=coins-5;
    		printf("<br/>You have lost 5 gold coins. But you have not lost yet1");
    		//printf("<br/><a href='https://cs.mcgill.ca/~ohussa/cgi-bin/addgold.cgi?gold=%d''>Click Here to go back</a>",coins);
    		printf("<br/><a href='..'>Click Here to go back</a>",coins);

    	//}
    	

    }
    //printf("Your name is %s. Your message is %s",field[1],field[3]);

    //Providing an hyperlink to go back the original data-entry page.
    // Note that since this file is accessed from the browser through this path (with my parameters substituted in it)
    // "https://www.cs.mcgill.ca/~rkurma1/cgi-bin/a.cgi?name_input=Ridwan&message_input=HelloWorld",
    // then we are in the directory cgi-bin and we only need to go back to the parent to reach the original page
    // "https://www.cs.mcgill.ca/~rkurma1"
    // Hence the hyperlink is just ".."
    printf("<br/><a href='..'>Click Here to go back</a>");
    printf("</center></body>");
    printf("</html>");
    return 0;
}


