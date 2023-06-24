#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "sigterm.h"

volatile sig_atomic_t done = 0;
 
void term(int signum)
{
    done = signum;
}
 
void sigterm_init()
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    if (sigaction(SIGTERM, &action, NULL) == -1)
    {
        printf("error setting handler\n");
        return;
    }
    if (sigaction(SIGINT, &action, NULL) == -1) 
    {
        printf("error setting handler\n");
        return;
    }
}

bool sigterm_is_done(void)
{
    return done!=0;
}