#include <stdio.h>
#include <stdlib.h>
#include "modbus.h"
#include "uart_functions.h"
#include "string.h"
#include "crc16.h"
#include "uart_config.h"
#include "utils.h"

unsigned char MATRICULA[] = {0, 3, 4, 1}; 
MODBUS_MESSAGE format_request_message(char subcode){
    int bufferSize = 9; 
    int pos = 0; 
    unsigned char* cmd_buffer = (unsigned char*)malloc(bufferSize);
    cmd_buffer[pos++] =  DEVICE_ADDRESS;
    cmd_buffer[pos++] =  REQUEST_DATA;
    cmd_buffer[pos++] =  subcode;
    
    memcpy(&cmd_buffer[pos], MATRICULA, sizeof(MATRICULA)); 
    pos += sizeof(MATRICULA);

    short crc = calcula_CRC(cmd_buffer, pos);
    memcpy(&cmd_buffer[pos], &crc, sizeof(crc)); 
    pos+=sizeof(crc);

    MODBUS_MESSAGE message; 
    message.buffer = cmd_buffer; 
    message.size = pos; 

    return message; 
}

MODBUS_MESSAGE format_send_message(char subcode, unsigned char* data, int dataSize) {
    int pos = 0; 
    int headerSize = 3;
    int crcSize = 2; 
    int matricula_size = 4;
    int total_size = headerSize + matricula_size + dataSize +  crcSize;

    unsigned char* cmd_buffer = (unsigned char*)malloc(total_size);
    cmd_buffer[pos++] =  DEVICE_ADDRESS;
    cmd_buffer[pos++] =  SEND_DATA;
    cmd_buffer[pos++] =  subcode;

    memcpy(&cmd_buffer[pos], MATRICULA, sizeof(MATRICULA)); 
    pos += sizeof(MATRICULA);

    memcpy(&cmd_buffer[pos], data, dataSize);
    pos += dataSize;
   
    short crc = calcula_CRC(cmd_buffer, pos);
    memcpy(&cmd_buffer[pos], &crc, sizeof(crc)); 
    pos+=sizeof(crc);

    MODBUS_MESSAGE message; 
    message.buffer = cmd_buffer; 
    message.size = pos; 

    return message;
}


