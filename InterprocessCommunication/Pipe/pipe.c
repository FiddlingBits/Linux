/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Main ***/
int main(void)
{
    /*** Variable ***/
    char buffer[16], *string = "Hello";
    int pfds[2];

    /*** Pipe ***/
    if(pipe(pfds) < 0)
    {
        (void)printf("pipe Failed\n");
        exit(EXIT_FAILURE);
    }
    
    /*** Fork ***/
    switch(fork())
    {
        case -1:
            /*** Failure ***/
            (void)printf("fork Failed\n");
            exit(EXIT_FAILURE);
            break;
        case 0:
            /*** Child ***/
            (void)write(pfds[1], string, strlen(string));
            (void)printf("Child: Write To Pipe: \"%s\"\n", string);
            exit(EXIT_SUCCESS); // Child Exit
            break;
        default:
            /*** Parent ***/
            (void)read(pfds[0], buffer, strlen(string));
            (void)printf("Parent: Read From Pipe: \"%s\"\n", buffer);
            (void)wait(NULL); // Wait For Child To Exit
            break;
    }

    /*** Parent Exit ***/
    exit(EXIT_SUCCESS);
}
