#pragma once

#include <stdint.h>
#include <arpa/inet.h>

#define MAX_DATA_SIZE 1024

typedef enum
{
    LITTLE,
    BIG
} HeaderEndianness;

typedef struct
{
    union
    {
        struct
        {
            uint32_t message_size;
            uint32_t correlation_id;
        } parts;
        uint64_t message_header;
    } header_v0;

    HeaderEndianness _endianness;
} response_header_v0_t;

response_header_v0_t __new_v0_response_header__(uint32_t message_size, uint32_t correlation_id);
#define v0_response_header_new(...) __new_v0_response_header__(0, 0);
void v0_response_header_to_network(response_header_v0_t *header);
void v0_response_header_from_network(response_header_v0_t *header);