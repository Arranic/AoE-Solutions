#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned char crc8(const unsigned char *pc_block, unsigned int len); /* this function is already implemented, use it */

int compose_packet(unsigned char *packet, unsigned int id_number, unsigned char state,
                   unsigned long long int scenario_mask, unsigned int volume, unsigned int status)
{
    printf("\nid: %X state: %X scenario mask: %llX volume: %u status: %X\n", id_number, state, scenario_mask, volume, status);

    // Check the various sizes of the inputs as notated in the instructions table.
    // If any are out of bounds, store the boolean.
    bool sizeCheck = id_number < 0x0000 || id_number > 0xFFFF ||
                     state < 0x00 || state > 0x7F ||
                     scenario_mask < 0x000000000000 || scenario_mask > 0xFFFFFFFFFFFF ||
                     volume < 000000 || volume > 999999 ||
                     status < 0x00FF || status > 0xFFFF;

    // If any passed-in values are out-of-bounds, return -1.
    if (sizeCheck)
    {
        return -1;
    }

    unsigned char crc = '\0';                         // initialize variable to store crc value
    char *crcArr = (char *)malloc(sizeof(char) * 28); // init array to calculate crc
    char *buffer = (char *)malloc(sizeof(char) * 31); // init array to store full buffer
    strcpy((char *)packet, buffer);                   // for safety purposes, overwrite the packet pointer with nothingness

    // Use the snprintf() function to build the crc array
    snprintf(crcArr, 29, "%04X%02X%012llX%06u%04X", id_number, state, scenario_mask, volume, status);
    crc = crc8((unsigned char *)crcArr, 28); // calculate the crc value passing in the crc array and the byte size
    // for whatever reason, if the crc value is out-of-bounds, return -1
    if (crc < 0x0 || crc > 0xFF)
    {
        return -1;
    }

    // Now we know the inputs and crc values are correct, so build the buffer array
    snprintf(buffer, 32, "%c%04X%02X%012llX%06u%04X%c%c", 0x2, id_number, state, scenario_mask, volume, status, 0x3, crc);

    if (strlen(buffer) * sizeof(*buffer) == 31)
    {
        // Copy the buffer array elements into packet, BUT drop the inherent '\0' character
        strncpy((char *)packet, buffer, strlen(buffer));
    }
    else
    {
        // if we get here, the buffer is overloaded somehow. Return -1
        return -1; /* if failure (out of range) */
    }

    free(buffer); // free up the buffer memory
    return 1;     /* success */
}
