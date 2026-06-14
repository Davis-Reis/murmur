#pragma once

#include "socpp.hpp"

namespace murmur {

// Writes a databuffer to a socket
// Params:
//          sock: socket to be writing to
//          data: void pointer to data
//          size: size in bytes of the payload
// Returns void
void write_framed(Socket& sock, const void* data, std::size_t size);

// Reads all bytes available in socket
// Params:
//          sock: socket to read from
// Returns vector containing bytes read
std::vector<std::uint8_t> read_framed(Socket& sock);

} // name space
