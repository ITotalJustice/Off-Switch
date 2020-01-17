#include <stdio.h>
#include <stdint.h>
#include <switch.h>


void init_app(void)
{
    consoleInit(NULL);
}

void exit_app(void)
{
    consoleExit(NULL);
}

void print_display(const char *message)
{
    printf(message);
    consoleUpdate(NULL);
}

int main(int argc, char *argv[])
{
    init_app();

    print_display("Off Switch: Power off the switch without having to press the power button!\n\n\n\n");

    if (appletGetAppletType() != AppletType_Application)
    {
        print_display("This is not a application\n\nPlease re-launch this app with applet override.\n\nThis can be done by holding R whilst launching a game.\n\n");
    }

    print_display("Press (A) to power off the switch\n\n");
    print_display("Press (Y) to reboot the switch\n\n");
    print_display("Press (B) to exit\n\n");

    while (appletMainLoop())
    {
        hidScanInput();
        uint64_t k = hidKeysDown(CONTROLLER_P1_AUTO);

        if (k & KEY_A)
        {
            if (R_FAILED(appletRequestToShutdown()))
            {
                print_display("Failed to start shutdown...\n\n");
            }
        }

        if (k & KEY_Y)
        {
            if (R_FAILED(appletRequestToReboot()))
            {
                print_display("Failed reboot switch\n\n");
            }
        }

        if (k & KEY_B)
        {
            break;
        }
    }

    exit_app();
    return 0;
}