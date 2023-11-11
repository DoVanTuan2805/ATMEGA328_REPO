#include "init.h"
void write_flash(const char *toStore, int startAddr)
{
    int i = 0;
    for (; i < strlen(toStore); i++)
    {
        EEPROM.write(startAddr + i, toStore[i]);
    }
    EEPROM.write(startAddr + i, '\0');
}
String read_flash(int startAddr)
{
    char in[128];
    int i = 0;
    for (; i < 128; i++)
    {
        in[i] = EEPROM.read(startAddr + i);
    }
    return String(in);
}