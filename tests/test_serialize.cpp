#include "serialize.hpp"
#include "package.hpp"

#include <cassert>
#include <iostream>
#include <print>

int main() {

    using Clock = std::chrono::system_clock;

    std::string testSender = "testUser";
    std::string testBody = "Hello, World!";
    murmur::Package testPack = murmur::Package(testSender, testBody);

    // Serialize testing

    auto serialized = murmur::serialize(testPack);
    murmur::Package deserialized = murmur::deserialize(serialized);
    assert(testPack.sender() == deserialized.sender());
    assert(testPack.body() == deserialized.body());
    assert(testPack.timeStamp() == deserialized.timeStamp());

    // Raw append testing

    std::vector<std::uint8_t> bufa_32;
    murmur::append_u32(bufa_32, 0x12345678);
    assert(bufa_32.size() == 4);
    assert(bufa_32[0] == 0x12 && bufa_32[1] == 0x34 && bufa_32[2] == 0x56 && bufa_32[3] == 0x78);

    std::vector<std::uint8_t> bufa_64;
    murmur::append_u64(bufa_64, 0x0123456789ABCDEF);
    assert(bufa_64.size() == 8);
    assert(bufa_64[0] == 0x01 && bufa_64[1] == 0x23 && bufa_64[2] == 0x45 && bufa_64[3] == 0x67 && bufa_64[4] == 0x89 && bufa_64[5] == 0xAB && bufa_64[6] == 0xCD && bufa_64[7] == 0xEF);

    // Round trip

    std::span<const std::uint8_t> span_32{bufa_32};
    std::uint32_t out_32 = murmur::read_u32(span_32);
    assert(out_32 = 0x12345678);
    assert(span_32.empty());

    std::span<const std::uint8_t> span_64{bufa_64};
    std::uint64_t out_64 = murmur::read_u64(span_64);
    assert(out_64 = 0x0123456789ABCDEF);
    assert(span_64.empty());

    return 0;
}

