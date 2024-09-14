/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Main ***/
int main(void)
{
    /*** Variable (Each Process Has Its Own Copy Of All Variables) ***/
    pid_t pid;
    int rv;
    
    /*** Set Up ***/
    srand(time(NULL));

    /*** Fork ***/
    switch(pid = fork())
    {
        case -1:
            /*** Failure ***/
            (void)printf("fork Failed\n");
            exit(EXIT_FAILURE);
            break;
        case 0:
            /*** Child ***/
            (void)printf("Child:\n");
            (void)printf("  PID:\n");
            (void)printf("    Parent: %d\n", getppid());
            (void)printf("    Self: %d\n", getpid());
            rv = rand() % 256;
            (void)printf("  Return Value:\n");
            (void)printf("    Self: %d\n", rv);
            exit(rv); // Child Exit
            break;
        default:
            /*** Parent ***/
            (void)usleep(500000); // Let Child Print Info First
            (void)printf("Parent:\n");
            (void)printf("  PID:\n");
            (void)printf("    Child: %d\n", pid);
            (void)printf("    Self: %d\n", getpid());
            (void)wait(&rv); // Wait For Child To Exit
            (void)printf("  Return Value:\n");
            (void)printf("    Child: %d\n", WEXITSTATUS(rv));
            break;
    }

    /*** Parent Exit ***/
    exit(EXIT_SUCCESS);
}
