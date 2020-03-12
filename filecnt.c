//Oswaldo Alvarado
//oxa170003
/*The program then recursively explores (traverses) the given directory and counts 1) the total number of directories, 2) the total number of plain files (i.e. not directory), and 3) the total number of bytes occupied by those plain files.  If an entry in a directory is not accessible (no permission to access), or an entry is a link to another location of the file system, the program should skip (i.e. do not count) that entry.
After processing the given directory, the program should output the following text to the standard output:
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include<sys/wait.h>
#include <unistd.h>

#define PREAD 0
#define PWRITE 1
int f =0, d =0;
long int b = 0;

void list_dir(const char* path){
  int  file_count = 0, directory_count = 0;
  long int bytes = 0;
    DIR *dir;

        dir = opendir(path);

        if(dir == NULL || !dir){
            printf("Error! Unable to open directory.\n");
            exit(1);
        }
    
        while(1){
            struct dirent *sd;
            const char *d_name;
            
            sd=readdir(dir);
            if(!sd){//there are no more entries in this directory, so break out of the while loop.
                break;
            }

            d_name = sd->d_name;


            if (sd->d_type == DT_REG) { // If the entry is a regular file
                file_count++;
                // opening the file in read mode 
                FILE* fp = fopen(d_name, "r"); 
  
                // checking if the file exist or not 
                if (fp == NULL) { 
                //printf("File Not Found!\n"); 
                break;    
                } 
  
                fseek(fp, 0L, SEEK_END); 
                // calculating the size of the file 
                bytes = ftell(fp); 
                // closing the file 
                fclose(fp);                
            }
            if (sd->d_type == DT_DIR){ // If the entry is a regular file
                directory_count++; 
                
                FILE* fp = fopen(d_name, "r"); 
  
                // checking if file exist or not 
                if (fp == NULL) { 
                break;    
                } 
  
                fseek(fp, 0L, SEEK_END); 
  
                // calculating the size of the file 
                bytes += ftell(fp); 
  
                // closing the file 
                fclose(fp); 
            }
            
        
            if (sd->d_type & DT_DIR) {
            // Check that the directory is not "d" or d's parent.
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char newPath[PATH_MAX];
 
                path_length = snprintf (newPath, PATH_MAX,
                                        "%s/%s", path, d_name);
                //printf ("%s\n", newPath);
                    if (path_length >= PATH_MAX) {
                        fprintf (stderr, "Path length has got too long.\n");
                        exit (EXIT_FAILURE);
                    }
                    // Recursively call "list_dir" with the new path.
                    list_dir (newPath);
            }
	        }
        }  
        closedir(dir);
        f = file_count;
        d = directory_count;
        b = bytes;      
}

int main(int argc, char *argv[])
{
    int files = 0, directory = 0;
    long int bytes = 0;
    const char *path = argv[1];
    
    list_dir(argv[1]);
    files = f;
    directory = d;
    bytes = b;

         printf("%s%s%s%d","The total number of directories in directory ", path, " is:",directory);                    
        printf("\n");      
        printf("%s%s%s%d", "The total number of files in directory " , path, " is:", files);
        printf("\n"); 
        printf("%s%s%s%ld", "The total number of bytes in directory " , path, " is:", bytes);
        printf("\n");    


 
        int pIn[2];
        int pOut[2]; 
        pid_t pid;
        char str[256];
        char input[1024] = "";
        int status;

        char *file = argv[1];
        char buf;
            
        while (fgets(input,sizeof(input),stdin)) {

            char nChar;
            int nResult;

            if (pipe(pIn) < 0) {
                perror("allocating pipe for child input redirect");
                return -1;
            }
            if (pipe(pOut) < 0) {
                close(pIn[PREAD]);
                close(pIn[PWRITE]);
                perror("allocating pipe for child output redirect");
                return -1;
            }

            pid = fork();
            if ( pid==0) {
                // child continues here

                //will redirect stdin
                if (dup2(pIn[PREAD], 0) == -1) {
                    perror("stdin");
                    return -1;
                }

                //will redirect stdout
                if (dup2(pOut[PWRITE], 1) == -1) {
                    perror("stdout");
                    return -1;
                }

                //will redirect stderr
                if (dup2(pOut[PWRITE], 2) == -1) {
                    perror("stderr");
                    return -1;
                }

                //for use by parent only
                close(pIn[PREAD]);
                close(pIn[PWRITE]);
                close(pOut[PREAD]);
                close(pOut[PWRITE]);

                //child process image
                nResult = execl("filedisp",file,NULL);

                exit(nResult);
            } else if (pid > 0) {
                //parent continues

                //close unused file descriptors
                close(pIn[PREAD]);
                close(pOut[PWRITE]);

                write(pIn[PWRITE], input, strlen(input));

                //char by char read
                while (read(pOut[PREAD], &nChar, 1) == 1) {
                    write(STDOUT_FILENO, &nChar, 1);
                }
                //close, done
                close(pIn[PWRITE]);
                close(pOut[PREAD]);
            }        
        }

    return 0;
}
