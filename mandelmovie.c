/*
* Program: mandelmivie.c
* Author: Brody Hyland
* Date:
* Description:
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define image 50

int main(int argc, char *argv[])
{
    
    int child = 0;
    int c;
    while((c = getopt(argc,argv,"n:"))!=-1) {
        switch(c)
        {
            case 'n':
                child = atoi(optarg);
                break;
        }
    }
    //figure out number of children 
    int base_images = image / child;
    int remainder = image % child;

    //create child
    for (int i = 0; i < child; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            printf("Child %d created\n", i + 1);

            // Child will generate its assigned images
           int start_image = (i * base_images) + (i < remainder ? i : remainder) + 1;
           int images_for_child = base_images + (i < remainder ? 1 : 0);
           int end_image = start_image + images_for_child - 1;
            
            double scale = 4.0;
            for (int j = 1; j < start_image; j++)
            {
                scale = scale * 0.95;
            }

            char start[12];
            char end[12];
            char scale_string[30];
            
            snprintf(start, sizeof(start), "%d", start_image);
            snprintf(end, sizeof(end), "%d", end_image);
            snprintf(scale_string, sizeof(scale_string), "%f", scale);

            printf("Child %d: images %d-%d, starting scale = %f\n", i + 1, start_image, end_image, scale);
            fflush(stdout);
            execl("./mandel", "mandel", "-b", start, "-e", end, "-s", scale_string, (char *)NULL);

            perror("execl");
            exit(1);
        }
        else if (pid < 0)
        {
            // Fork failed
            perror("fork");
            return 1;
        }
    }

    // Parent process 
    printf("Parent process\n");

    for (int i = 0; i < child; i++)
    {
        wait(NULL);
    }
    printf("All images generated!\n");
    //clean up 

}
