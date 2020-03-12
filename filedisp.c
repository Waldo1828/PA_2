//Oswaldo Alvarado
//oxa170003
/*filedisp receives text (multiple lines) from standard input, accepts one of the three options: -d, -f and -b, and displays one line from the input accordingly to the given option.
If the option was -d it displays the input line that has the word 'directories'.
If the option was -f it displays the input line that has the word 'files'.
If the option was -b it displays the input line that has the word 'bytes'.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	//output given from filecnt
    char input[5096]; 
    int iter = 0;
    char f[] = "-f";
    char d[] = "-d";
    char b[] = "-b";
    char *str = argv[1];
	//looking if it conatins the string
    char *ptr = strstr(str, d);     
        if(ptr != NULL){
            iter = 1;
        }
    ptr = strstr(str, f);
        if(ptr != NULL){
            iter = 2;
        }
    ptr = strstr(str, b);
        if(ptr != NULL){
            iter = 3;
        }//determines which if statement to run later on
    char search[] = "directories";
    char search2[] = "files";
    char search3[] = "bytes";
    //This loop will go through
    for(int i =0; i < 3; i++){ 
        fgets(input,sizeof(input),stdin);
            char *str = input;
            if(iter == 1){
                 char *ptr = strstr(str, search);
                    if(ptr != NULL){
                        printf("%s", input);
                        break;
                   }        
            }
            else if(iter == 2){
                char *ptr = strstr(str, search2);
                    if(ptr != NULL){
                        printf("%s", input);
                        break;
                    }
            }
            else if(iter == 3){
                char *ptr = strstr(str, search3);
                    if(ptr != NULL){
                        printf("%s", input);
                        break;
                    }
            }
            else{
                continue;                
            }
    } 
  return 0;
}
