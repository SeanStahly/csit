#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <curl/curl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  CURL *curl;
  char url[256];
  CURLcode res;
  FILE *bodyfile;

  // strcpy(url, "https://raw.githubusercontent.com/SeanStahly/spring2017Research/master/mkfile.c");
  strcpy(url, "https://raw.githubusercontent.com/SeanStahly/csit/master/112/inClass/wordNumber.out");

  curl = curl_easy_init();

  char *fileLocation = (char*) malloc(120 * sizeof(char));
  strcpy(fileLocation,"/home/stahlysr/test/");

  char *execFile = (char *) malloc(40 * sizeof(char));
  strcpy(execFile,"test-1.out");

  strcat(fileLocation, execFile);

  printf("%s\n", fileLocation);

  // bodyfile = fopen("/home/sean/test/test.out", "wb");
  bodyfile = fopen(fileLocation, "wb");
  if(!bodyfile) {
    printf("blarg");
    curl_easy_cleanup(curl);
    return -1;
  }

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, bodyfile);

    res = curl_easy_perform(curl);

    fclose(bodyfile);

    curl_easy_cleanup(curl);
  }

  /*Spawn a child to run the program.*/
    pid_t pid=fork();
    if (pid==0) { /* child process */
        static char *argv1[]={"chmod", "700", "/home/stahlysr/test/test-1.out",NULL};
        execv("/bin/chmod",argv1);

        // static char *argv2[]={"./test.out",NULL};
        // // execv("/home/sean/test/test.out",argv2);
        // execv(fileLocation,argv2);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }

    /*Spawn a child to run the program.*/
    pid=fork();
    if (pid==0) { /* child process */
        // static char *argv1[]={"chmod", "700", "/home/sean/test/test-1.out",NULL};
        // execv("/bin/chmod",argv1);

        static char *argv2[]={"./test.out",NULL};
        // // execv("/home/sean/test/test.out",argv2);
        execv(fileLocation,argv2);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }

    free(fileLocation);
    free(execFile);
}
