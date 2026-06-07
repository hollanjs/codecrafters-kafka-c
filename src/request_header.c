#include "request_header.h"

#include <stdio.h>

#pragma region RESPONSE_HEADER_V0
response_header_v0_t v0_response_header_new(uint32_t message_size, uint32_t correlation_id)
{
    response_header_v0_t _new_v0_response_header;
    _new_v0_response_header.header_v0.parts.message_size = message_size;
    _new_v0_response_header.header_v0.parts.correlation_id = correlation_id;
    _new_v0_response_header._endianness = LITTLE;
    return _new_v0_response_header;
}

response_header_v0_t v0_response_header_from_64byte_request(uint64_t request)
{
    response_header_v0_t v0_response_header;
    v0_response_header.header_v0.message_header = request;
    v0_response_header_ntoh(&v0_response_header);
    return v0_response_header;
}

void v0_response_header_hton(response_header_v0_t *header)
{
    uint32_t message_size_le = header->header_v0.parts.message_size;
    uint32_t correlation_id_le = header->header_v0.parts.correlation_id;
    header->header_v0.parts.message_size = htonl(message_size_le);
    header->header_v0.parts.correlation_id = htonl(correlation_id_le);
    header->_endianness = BIG;
}

void v0_response_header_ntoh(response_header_v0_t *header)
{
    uint32_t message_size_le = header->header_v0.parts.message_size;
    uint32_t correlation_id_le = header->header_v0.parts.correlation_id;
    header->header_v0.parts.message_size = ntohl(message_size_le);
    header->header_v0.parts.correlation_id = ntohl(correlation_id_le);
    header->_endianness = LITTLE;
}

uint64_t v0_response_get_header(response_header_v0_t *header)
{
    return header->header_v0.message_header;
}

uint32_t v0_response_get_correlation_id(response_header_v0_t *header)
{
    return header->header_v0.parts.correlation_id;
}

uint32_t v0_response_get_message_size(response_header_v0_t *header)
{
    return header->header_v0.parts.message_size;
}
#pragma endregion RESPONSE_HEADER_V0

response_header_v0_t v2_response_header_to_v0(response_header_v2_t v2response)
{
    response_header_v0_t v0response = v0_response_header_new(v2response.message_size,
                                                             v2response.correlation_id);
    return v0response;
}

#pragma region RESPONSE_HEADER_V2
response_header_v2_t v2_response_header_new(uint32_t message_size,
                                            uint32_t correlation_id,
                                            uint16_t request_api_key,
                                            uint16_t request_api_version)
{
    response_header_v2_t v2_response_header;
    v2_response_header.message_size = message_size;
    v2_response_header.correlation_id = correlation_id;
    v2_response_header.request_api_key = request_api_key;
    v2_response_header.request_api_version = request_api_version;
    v2_response_header._endianness = LITTLE;
    return v2_response_header;
}

// void *memcpy(void dest[restrict .n], const void src[restrict .n],size_t n);
response_header_v2_t v2_response_header_from_64byte_request(const uint8_t *request)
{
    response_header_v2_t v2_response_header;
    uint32_t message_size;
    uint32_t correlation_id;
    uint16_t request_api_key;
    uint16_t request_api_version;

    int _offset = 0;

    memcpy(&message_size, &request[_offset], sizeof(v2_response_header.message_size));
    _offset += sizeof(v2_response_header.message_size);

    memcpy(&request_api_key, &request[_offset], sizeof(v2_response_header.request_api_key));
    _offset += sizeof(v2_response_header.request_api_key);

    memcpy(&request_api_version, &request[_offset], sizeof(v2_response_header.request_api_version));
    _offset += sizeof(v2_response_header.request_api_version);

    memcpy(&correlation_id, &request[_offset], sizeof(v2_response_header.correlation_id));

    v2_response_header = v2_response_header_new(message_size, correlation_id, request_api_key, request_api_version);

    v2_response_header_ntoh(&v2_response_header);

    return v2_response_header;
}

void v2_response_header_hton(response_header_v2_t *header)
{
    uint32_t message_size = header->message_size;
    uint32_t correlation_id = header->correlation_id;
    uint16_t request_api_key = header->request_api_key;
    uint16_t request_api_version = header->request_api_version;
    header->message_size = htonl(message_size);
    header->correlation_id = htonl(correlation_id);
    header->request_api_key = htons(request_api_key);
    header->request_api_version = htons(request_api_version);
    header->_endianness = BIG;
}
void v2_response_header_ntoh(response_header_v2_t *header)
{
    uint32_t message_size = header->message_size;
    uint32_t correlation_id = header->correlation_id;
    uint16_t request_api_key = header->request_api_key;
    uint16_t request_api_version = header->request_api_version;
    header->message_size = ntohl(message_size);
    header->correlation_id = ntohl(correlation_id);
    header->request_api_key = ntohs(request_api_key);
    header->request_api_version = ntohs(request_api_version);
    header->_endianness = LITTLE;
}
#pragma endregion RESPONSE_HEADER_V2
