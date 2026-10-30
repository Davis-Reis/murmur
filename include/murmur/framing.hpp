#pragma once

#include <socpp/socket.hpp>
#include <optional>
#include <span>
#include <vector>
#include <limits>
#include <cstdint>
#include <cstddef>

namespace murmur {

inline constexpr std::size_t MAX_MESSAGE = 64 * 1024;
static_assert(MAX_MESSAGE <= std::numeric_limits<std::uint32_t>::max(),
              "MAX_MESSAGE must fit in the uint32 length header");
// Writes a databuffer to a socket
// Params:
//          sock: socket to be writing to
//          data: vector of bytes
// Returns void
void write_framed(socpp::Socket& sock, std::span<const std::uint8_t> data);

// Reads all bytes available in socket
// Params:
//          sock: socket to read from
// Returns vector containing bytes read
std::optional<std::vector<std::uint8_t>> read_framed(socpp::Socket& sock);

} // name space
