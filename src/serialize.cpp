#include "serialize.hpp"

namespace murmur {

// Pkg format
// [ 64 int timestamp ]                         | 8 bytes
// [ uint32 sender 1byte <= len <= 16bytes ]    | 4 bytes
// [ sender bytes ]                             | len bytes
// [ uint32 message len ]                       | 4 bytes
// [ message bytes ]                            | len bytes


std::vector<std::uint8_t> serialize(const &Package package) {
    std::vector<std::uint8_t> serialized;
    std::uint64_t timestamp = package.timestamp();

    std::uint32_t senderLen = sizeof(package.sender());
    std::string sender = package.sender();

    std::uint32_t messageLen = sizeof(package.body());
    std::string body = package.body();


}

Package deserialize(std::span<uint8_t> data) {
    return Package package;
}

// Helper function to translate 32 bit into big endian and push onto out vector
void append_u32(std::vector<std::uint8_t>& out, uint32_t x) {
    out.push_back(static_cast<std::uint8_t>((x >> 24) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 16) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 8 ) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 0 ) & 0xFF));
}

// Helper function to translate 64 bit into big endian and push onto out vector
void append_u64(std::vector<std::uint8_t>& out, uint64_t x) {
    out.push_back(static_cast<std::uint8_t>((x >> 56) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 48) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 40) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 32) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 24) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 16) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 8 ) & 0xFF));
    out.push_back(static_cast<std::uint8_t>((x >> 0 ) & 0xFF));
}
} // namespace
