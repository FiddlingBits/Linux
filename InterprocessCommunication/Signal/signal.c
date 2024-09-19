/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/****************************************************************************************************
 * Variable
 ****************************************************************************************************/

static volatile sig_atomic_t count = 0;

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

static void signal_handler(int sig);

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Main ***/
int main(void)
{
    /*** Variable ***/
    struct sigaction sa =
    {
        .sa_flags = SA_RESTART,
        .sa_handler = signal_handler,
        .sa_mask = 0
    };
    
    /*** Change Signal Action ***/
    if(sigaction(SIGINT, &sa, NULL) == -1)
    {
        (void)printf("sigaction Failed\n");
        exit(EXIT_FAILURE);
    }
    
    /*** Wait ***/
    (void)printf("Press [CTRL+C] Or Send Command \"kill -INT %d\" In Another Terminal To Test Signal Handler Or [ENTER] To Exit...\n", getpid());
    (void)getchar();
    (void)printf("Exiting...\n");
    (void)printf("  Count: %d\n", count);

    /*** Exit ***/
    exit(EXIT_SUCCESS);
}

/*** Signal Handler ***/
void signal_handler(int sig)
{
    if(sig == SIGINT)
    {
        const char * const String = "\b\bRefusing To Exit!\n"; // \b\b To Erase ^C In Terminal
        (void)write(STDOUT_FILENO, String, strlen(String)); // POSIX Says That write Is Async-Safe (So Is Safe To Call From Within The Signal Handler), While printf() Is Not
        count++;
    }
}
