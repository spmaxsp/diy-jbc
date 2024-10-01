#include "ser_ui.h"

#include <string.h>

const char cmd_set[] = "SET ";
const char cmd_temp[] = "TEMP ";
const char cmd_pid_p[] = "KP ";
const char cmd_pid_i[] = "KI ";
const char cmd_pid_d[] = "KD ";
const char cmd_tc_a[] = "TC_A ";
const char cmd_tc_b[] = "TC_B ";
const char cmd_tc_c[] = "TC_C ";
const char cmd_s_time[] = "T_SLEEP ";
const char cmd_h_time[] = "T_HIBERNATE ";
const char cmd_s_tmp[] = "TMP_SLEEP ";
const char cmd_h_tmp[] = "TMP_HIBERNATE "; 

const char cmd_enable[] = "ENABLE";

const char cmd_disable[] = "DISABLE";

const char cmd_set_eeprom[] = "SAVE";

const char cmd_print_settings[] = "SETTINGS";  

const char cmd_start_graph[] = "START"; 

const char cmd_stop_graph[] = "STOP"; 

int teststr(uint8_t *input, uint32_t in_length, uint8_t *test, uint32_t test_length, uint32_t offset)
{
    // Check if the input buffer is long enough to contain the test string
    if (in_length < test_length + offset)
    {
        return 0;
    }
    // Check if the input buffer contains the test string
    if (strncmp((char*)input + offset, (char*)test, test_length) == 0)
    {
        return 1;
    }
    return 0;
}

void Ser_Ui_Process_Command(uint8_t *command, uint8_t length)
{
    int offset = 0;

    if (teststr(command, length, (uint8_t *)cmd_set, sizeof(cmd_set) - 1, offset))
    {
        offset += sizeof(cmd_set) - 1;
        if (teststr(command, length, (uint8_t *)cmd_temp, sizeof(cmd_temp) - 1, offset))
        {
            offset += sizeof(cmd_temp) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set temperature\n", 16);
            // Set temperature
        }
        else if (teststr(command, length, (uint8_t *)cmd_pid_p, sizeof(cmd_pid_p) - 1, offset))
        {
            offset += sizeof(cmd_pid_p) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set PID P\n", 10); 
            // Set PID P
        }
        else if (teststr(command, length, (uint8_t *)cmd_pid_i, sizeof(cmd_pid_i) - 1, offset))
        {
            offset += sizeof(cmd_pid_i) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set PID I\n", 10);
            // Set PID I
        }
        else if (teststr(command, length, (uint8_t *)cmd_pid_d, sizeof(cmd_pid_d) - 1, offset))
        {
            offset += sizeof(cmd_pid_d) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set PID D\n", 10);
            // Set PID D
        }
        else if (teststr(command, length, (uint8_t *)cmd_tc_a, sizeof(cmd_tc_a) - 1, offset))
        {
            offset += sizeof(cmd_tc_a) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set TC A\n", 9);
            // Set TC A
        }
        else if (teststr(command, length, (uint8_t *)cmd_tc_b, sizeof(cmd_tc_b) - 1, offset))
        {
            offset += sizeof(cmd_tc_b) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set TC B\n", 9);
            // Set TC B
        }
        else if (teststr(command, length, (uint8_t *)cmd_tc_c, sizeof(cmd_tc_c) - 1, offset))
        {
            offset += sizeof(cmd_tc_c) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set TC C\n", 9);
            // Set TC C
        }
        else if (teststr(command, length, (uint8_t *)cmd_s_time, sizeof(cmd_s_time) - 1, offset))
        {
            offset += sizeof(cmd_s_time) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set sleep time\n", 15);
            // Set sleep time
        }
        else if (teststr(command, length, (uint8_t *)cmd_h_time, sizeof(cmd_h_time) - 1, offset))
        {
            offset += sizeof(cmd_h_time) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set hibernate time\n", 19);
            // Set hibernate time
        }
        else if (teststr(command, length, (uint8_t *)cmd_s_tmp, sizeof(cmd_s_tmp) - 1, offset))
        {
            offset += sizeof(cmd_s_tmp) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set sleep temperature\n", 22);
            // Set sleep temperature
        }
        else if (teststr(command, length, (uint8_t *)cmd_h_tmp, sizeof(cmd_h_tmp) - 1, offset))
        {
            offset += sizeof(cmd_h_tmp) - 1;
            USART_Ser_Ui__Tx_Blocking((uint8_t *)"Set hibernate temperature\n", 26);
            // Set hibernate temperature
        }
    }
    else if (teststr(command, length, (uint8_t *)cmd_enable, sizeof(cmd_enable) - 1, offset))
    {
        offset += sizeof(cmd_enable) - 1;
        USART_Ser_Ui__Tx_Blocking((uint8_t *)"Enable\n", 7);
        // Enable
    }
    else if (teststr(command, length, (uint8_t *)cmd_disable, sizeof(cmd_disable) - 1, offset))
    {
        offset += sizeof(cmd_disable) - 1;
        USART_Ser_Ui__Tx_Blocking((uint8_t *)"Disable\n", 8);
        // Disable
    }
    else if (teststr(command, length, (uint8_t *)cmd_set_eeprom, sizeof(cmd_set_eeprom) - 1, offset))
    {
        offset += sizeof(cmd_set_eeprom) - 1;
        USART_Ser_Ui__Tx_Blocking((uint8_t *)"Save to EEPROM\n", 15);
        // Save to EEPROM
    }
    else if (teststr(command, length, (uint8_t *)cmd_print_settings, sizeof(cmd_print_settings) - 1, offset))
    {
        offset += sizeof(cmd_print_settings) - 1;
        USART_Ser_Ui__Tx_Blocking((uint8_t *)"Print settings\n", 15);
        // Print settings
    }
    else if (teststr(command, length, (uint8_t *)cmd_start_graph, sizeof(cmd_start_graph) - 1, offset))
    {
        offset += sizeof(cmd_start_graph) - 1;
        USART_Ser_Ui__Tx_Blocking((uint8_t *)"Start graph\n", 12);
        // Start graph
    }
    else if (teststr(command, length, (uint8_t *)cmd_stop_graph, sizeof(cmd_stop_graph) - 1, offset))
    {
        offset += sizeof(cmd_stop_graph) - 1;
        USART_Ser_Ui__Tx_Blocking((uint8_t *)"Stop graph\n", 11);
        // Stop graph
    }
}




