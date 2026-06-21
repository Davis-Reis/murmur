#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <cstdint>

namespace murmur {

class Package {
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    Package() = default;
    Package(std::string sender, std::string body);
    Package(std::string sender, std::string body, TimePoint timestamp);

    const std:string& sender() const noexcept;

    const std::string& body() const noexcept;

    TimePoint timestamp() const noexcept;

    std::vector<std::uint8_t> serialize() const;

    static Package deserialize(const std::uint8_t* data, std::size_t size);

private:
    std::string sender_;
    std::string body_;
    TimePoint timestamp_{Clock::now()};
};

} // namespace murmur
