
#include "NexButton.h"

NexButton b0 = NexButton(0, 2, "b0");


char buffer[10] = {0};

NexTouch *nex_Listen_List[] = 
{
    &b0,
    NULL
};

/**
 * Button to return the response.
 * 
 * @param ptr - the parameter was transmitted to pop event function pointer. 
 * 
 */
void b0PopCallback(void *ptr)
{
    NexButton *btn = (NexButton *)ptr;
    memset(buffer, 0, sizeof(buffer));
    btn->getText(buffer, sizeof(buffer));
    if (strcmp(buffer,"ON"))
    {
        digitalWrite(10, HIGH);
        strcpy(buffer, "ON");
    }
    else
    {
        digitalWrite(10, LOW);
        strcpy(buffer, "OFF");
    }
    btn->setText(buffer);
   
}

    

void setup(void)
{
    nexInit();
    b0.attachPop(b0PopCallback, &b0);
//setting port OUTPUT
    pinMode(10, OUTPUT);
//initializing  port 
    digitalWrite(10, LOW);
}

void loop(void)
{
    nexLoop(nex_Listen_List);
}

