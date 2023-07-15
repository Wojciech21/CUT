#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "sigterm.h"

static volatile sig_atomic_t done = 0;
 
static void term(int signum)
{
    done = signum;
}
 
int sigterm_init(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    if (sigaction(SIGTERM, &action, NULL) == -1)
    {
        printf("error setting handler\n");
        return -1;
    }
    if (sigaction(SIGINT, &action, NULL) == -1) 
    {
        printf("error setting handler\n");
        return -1;
    }
    return 0;
}

bool sigterm_is_done(void)
{
    return done!=0;
}
