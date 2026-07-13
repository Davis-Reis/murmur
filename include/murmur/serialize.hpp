#pragma once

#include "package.hpp"

namespace murmur {

// Serializes a package into a vector to send over a connection
// Params:
//          package: pointer to a package
// Returns vector of serialized bytes
std::vector<std::uint8_t> serialize(const Package& package);

// Deserializes a stream of bytes into a package
// Params:
//          data: raw stream of bytes
// Returns data deserialized into a package object
Package deserialize(std::span<const std::uint8_t> data);

void append_u32(std::vector<uint8_t>& out, uint32_t x);

void append_u64(std::vector<uint8_t>& out, uint64_t x);

std::uint32_t read_u32(std::span<const std::uint8_t>& buf);

std::uint64_t read_u64(std::span<const std::uint8_t>& buf);

} // namespace
