#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <cstdint>
#include <print>

namespace murmur {

class Package {
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    Package() = default;
    Package(std::string sender, std::string body) :
        sender_(std::move(sender)), body_(std::move(body)) {}
    Package(std::string sender, std::string body, TimePoint timestamp) :
        sender_(std::move(sender)), body_(std::move(body)), timestamp_(timestamp) {}


    const std::string& sender() const noexcept { return sender_; }

    const std::string& body() const noexcept { return body_; }

    TimePoint timeStamp() const noexcept { return timestamp_; }

    void stamp() { timestamp_ = Clock::now(); }

    void printPackage() { println("{}", sender_); println("{}", body_); }

private:
    TimePoint timestamp_;
    std::string sender_;
    std::string body_;
};

} // namespace murmur
