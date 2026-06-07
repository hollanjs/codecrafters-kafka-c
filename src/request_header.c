#include "request_header.h"

response_header_v0_t __new_v0_response_header__(uint32_t message_size, uint32_t correlation_id)
{
    response_header_v0_t _new_v0_response_header;
    _new_v0_response_header.header_v0.parts.message_size = message_size;
    _new_v0_response_header.header_v0.parts.correlation_id = correlation_id;
    _new_v0_response_header._endianness = LITTLE;
    return _new_v0_response_header;
}

// #define v0_response_header_new (message_size, correlation_id) __new_v0_response_header__(0, 0)

void v0_response_header_to_network(response_header_v0_t *header)
{
    uint32_t message_size_le = header->header_v0.parts.message_size;
    uint32_t correlation_id_le = header->header_v0.parts.correlation_id;
    header->header_v0.parts.message_size = htonl(message_size_le);
    header->header_v0.parts.correlation_id = htonl(correlation_id_le);
    header->_endianness = BIG;
}

void v0_response_header_from_network(response_header_v0_t *header)
{
    uint32_t message_size_le = header->header_v0.parts.message_size;
    uint32_t correlation_id_le = header->header_v0.parts.correlation_id;
    header->header_v0.parts.message_size = ntohl(message_size_le);
    header->header_v0.parts.correlation_id = ntohl(correlation_id_le);
    header->_endianness = LITTLE;
}
