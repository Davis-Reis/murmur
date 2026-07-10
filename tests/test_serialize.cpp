#include "serialize.hpp"
#include "package.hpp"

#include <cassert>

namespace murmur {

int main() {

    using Clock = std::chrono::system_clock;

    std::string testSender = "testUser";
    std::string testBody = "Hello, World!";
    Clock::time_point timeStamp = Clock::now();
    Package testPack = Package(testSender, testBody, timeStamp);

    // Serialize testing

    std::vector<std::uint8_t> serialized = serialize(&testPack);
    Package deserialized = deserialize(serialized);

    assert(testSender == deserialized.sender());
    assert(testBody == deserialized.body());
    assert(timeStamp == deserialized.timeStamp());

    // 
}

} // namespace murmur
