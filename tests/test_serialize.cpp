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

    std::vector<std::uint8_t> buf;
    murmur::append_u32(buf, 0x12345678);
    assert(buf.size() == 4);
    assert(buf[0] == 0x12 && buf[1] == 0x34 && buf[2] == 0x56 && buf[3] == 0x78);

    return 0;
}

