#include "serialize.hpp"
#include <span>
#include <cstint>
#include <stdexcept>

namespace murmur {

// Pkg format
// [ 64 int timestamp ]                         | 8 bytes
// [ uint32 sender 1byte <= len <= 16bytes ]    | 4 bytes
// [ sender bytes ]                             | len bytes
// [ uint32 message len ]                       | 4 bytes
// [ message bytes ]                            | len bytes

// Package to bytes
std::vector<std::uint8_t> serialize(const Package& package) {
    std::vector<std::uint8_t> out;

    // Store the timepoint
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            package.timestamp().time_since_epoch()).count();
    append_u64(out, static_cast<std::uint64_t>(ms));

    // Store the sender str len then str
    const std::string& sender = package.sender();
    append_u32(out, static_cast<std::uint32_t>(sender.size()));
    out.insert(out.end(), sender.begin(), sender.end());

    // Store the body str len then str
    const std::string& body = package.body();
    append_u32(out, static_cast<std::uint32_t>(body.size()));
    out.insert(out.end(), body.begin(), body.end());

    return out;
}

Package deserialize(std::span<uint8_t> data) {
    int offset = 0;
    Timepoint time = (read_u64(data), offset);
    offset += sizeof(time);

    int senderlen = (read_u32(data), offset);
    offset += sizeof(senderlen);

    std::string sender = data.subspan(offset, offset + senderlen);
    offset += sizeof(sender);

    int bodylen = (read_u32(data), offset);
    offset += sizeof(bodylen);

    std::string body = data.subspan(offset, offset + bodylen);
    offset += sizeof(body);

    Package package(sender, body, time);

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

// Helper function to translate uint8 vector from network to host bytes
std::uint32_t read_u32(std::vector<std::uint8_t> buf, std::size_t& offset) {
    if (buf.size() < 4) {
        throw std::runtime_error("read_u32: buffer underrun");
    }
    std::uint32_t result = (static_cast<std::uint32_t>(buf[0]) << 24)
        | (static_cast<std::uint32_t>(buf[1]) << 16)
        | (static_cast<std::uint32_t>(buf[2]) << 8 )
        | (static_cast<std::uint32_t>(buf[3]) << 0 );
    buf = buf.subspan(4);
    return result;
}

// Helper function to translate uint8 vector from network to host bytes
std::uint64_t read_u64(std::vector<std::uint8_t> buf, std::size_t& offset) {
    if (buf.size() < 4) {
        throw std::runtime_error("read_u64: buffer underrun");
    }
    std::uint32_t result = (static_cast<std::uint32_t>(buf[0]) << 56)
    | (static_cast<std::uint32_t>(buf[1]) << 48)
    | (static_cast<std::uint32_t>(buf[2]) << 40)
    | (static_cast<std::uint32_t>(buf[3]) << 32)
    | (static_cast<std::uint32_t>(buf[4]) << 24)
    | (static_cast<std::uint32_t>(buf[5]) << 16)
    | (static_cast<std::uint32_t>(buf[6]) << 8 )
    | (static_cast<std::uint32_t>(buf[7]) << 0 );
    buf = buf.subspan(8);
    return result;
}
    
} // namespace
