#pragma once

#include "socpp.hpp"

namespace murmur {

// Serializes a package into a vector to send over a connection
// Params:
//          package: pointer to a package
// Returns vector of serialized bytes
std::vector<std::uint8_t> serialize(const &Package package);

// Deserializes a stream of bytes into a package
// Params:
//          data: raw stream of bytes
// Returns data deserialized into a package object
Package deserialize(std::span<uint8_t> data);
