#include "settings.h"

typedef struct eeprom_content_t {
    uint8_t start_byte;
    settings_t settings;
    uint32_t checksum;
    uint8_t end_byte;
} eeprom_content_t;

extern settings_t settings;


void Apply_Default_Settings(void)
{
    settings.KP = 4.4;
    settings.KI = 0.9;
    settings.KD = 0.05;

    settings.TC_A = 0;
    settings.TC_B = 1;
    settings.TC_C = 0;

    settings.SLEEP_DELAY = 1.5 * 60;
    settings.SLEEP_TEMP = 150;
    settings.HIBERNATE_DELAY = 3 * 60;
    settings.HIBERNATE_TEMP = 0; 
}


uint32_t Calculate_Checksum(uint8_t *ptr, uint32_t size)
{
    uint32_t checksum = 0;
    for (int i = 0; i < size; i++)
    {
        checksum += ptr[i];
    }
    return checksum;
}


void Commit_to_EEPROM(void)
{
    eeprom_content_t eeprom_content;

    eeprom_content.start_byte = 0x55;
    eeprom_content.settings = settings;
    eeprom_content.checksum = Calculate_Checksum((uint8_t *)&eeprom_content.settings, sizeof(settings_t));
    eeprom_content.end_byte = 0xAA;

    EEPROM_Write(0, sizeof(eeprom_content_t), (uint8_t *)&eeprom_content);
}


void Recover_from_EEPROM(void)
{
    eeprom_content_t eeprom_content;
    EEPROM_Read(0, sizeof(eeprom_content_t), (uint8_t *)&eeprom_content);

    if (eeprom_content.start_byte == 0x55 && eeprom_content.end_byte == 0xAA)
    {
        uint32_t checksum = Calculate_Checksum((uint8_t *)&eeprom_content.settings, sizeof(settings_t));
        if (checksum == eeprom_content.checksum)
        {
            settings = eeprom_content.settings;
        }
        else
        {
            Apply_Default_Settings();
            Commit_to_EEPROM();
        }
    }
    else
    {
        Apply_Default_Settings();
        Commit_to_EEPROM();
    }
}
