/* Tiny command line util to prevent your Mac from sleeping/screen saving.
 * Use however you like.
 */

#include <stdio.h>
#include <IOKit/pwr_mgt/IOPMLib.h>

static IOPMAssertionID assertion_id = 0;
static int sleeping = 0;

int disable_screen_sleep()
{
    if (sleeping)
        return 0;

    IOReturn res;
    res = IOPMAssertionCreateWithName(
        kIOPMAssertPreventUserIdleDisplaySleep,
        kIOPMAssertionLevelOn,
        CFSTR("red eyes are beautiful"),
        &assertion_id);
    sleeping = res == kIOReturnSuccess;
    return sleeping;
}

int enable_screen_sleep()
{
    if (!sleeping)
        return 0;

    IOReturn res;
    res = IOPMAssertionRelease(assertion_id);
    sleeping = !(res == kIOReturnSuccess);
    return !sleeping;
}

void sigint_handler()
{
    enable_screen_sleep();
    printf("red eyes\n");

    _exit(0);
}

int main()
{
    setbuf(stdout, NULL);
    signal(SIGINT, sigint_handler);

    if (disable_screen_sleep())
    {
        printf("no sleep till... ");
        for (;;) sleep(60000);
    }

    return 0;
}
