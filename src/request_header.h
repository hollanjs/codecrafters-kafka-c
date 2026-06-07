#pragma once

#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_DATA_SIZE 1024

typedef enum
{
    LITTLE,
    BIG
} HeaderEndianness;

#pragma region RESPONSE_HEADER_V0
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

response_header_v0_t v0_response_header_new(uint32_t message_size,
                                            uint32_t correlation_id);

response_header_v0_t v0_response_header_from_64byte_request(uint64_t request);

void v0_response_header_hton(response_header_v0_t *header);
void v0_response_header_ntoh(response_header_v0_t *header);
uint64_t v0_response_get_header(response_header_v0_t *header);
uint32_t v0_response_get_correlation_id(response_header_v0_t *header);
uint32_t v0_response_get_message_size(response_header_v0_t *header);
#pragma endregion RESPONSE_HEADER_V0

#pragma region RESPONSE_HEADER_V2
typedef struct
{
    uint32_t message_size;
    uint32_t correlation_id;
    uint16_t request_api_key;
    uint16_t request_api_version;
    HeaderEndianness _endianness;
} response_header_v2_t;

response_header_v2_t v2_response_header_new(uint32_t message_size,
                                            uint32_t correlation_id,
                                            uint16_t request_api_key,
                                            uint16_t request_api_version);

response_header_v2_t v2_response_header_from_64byte_request(uint8_t *request);

void v2_response_header_hton(response_header_v2_t *header);
void v2_response_header_ntoh(response_header_v2_t *header);
#pragma endregion RESPONSE_HEADER_V2