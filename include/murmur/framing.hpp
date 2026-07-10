#pragma once

#include "socpp.hpp"

namespace murmur {

// Writes a databuffer to a socket
// Params:
//          sock: socket to be writing to
//          data: vector of bytes
// Returns void
void write_framed(Socket& sock, std::span<std::uint8_t> data);

// Reads all bytes available in socket
// Params:
//          sock: socket to read from
// Returns vector containing bytes read
std::vector<std::uint8_t> read_framed(Socket& sock);

} // name space
