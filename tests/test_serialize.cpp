#include "serialize.hpp"
#include "package.hpp"

#include <cassert>

namespace murmur {

int main() {

    using Clock = std::chrono::system_clock;

    std::string testSender = "testUser";
    std::string testBody = "Hello, World!";
    Package testPack = Package(testSender, testBody);

    // Serialize testing

    auto serialized = serialize(&testPack);
    Package deserialized = deserialize(serialized);

    assert(testPack.sender() == deserialized.sender());
    assert(testPack.body() == deserialized.body());
    assert(testPack.timeStramp() == deserialized.timeStamp());

    // Raw append testing

    std::vector<std::uint32_t> buf;
    u32_append(buf, 0x12345678);
    assert(buf.size == 4);
    assert(buf[0] == 0x12 && buf[1] == 0x34 && buf[2] == 0x56 && buf[3] == 0x78);
}

} // namespace murmur
