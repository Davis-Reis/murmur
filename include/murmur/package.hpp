#pragma once

#include <string>
#include <chrono>

namespace murmur {

struct Package {
    std::string body;
    std::chrono::system_clock::time_point timestamp;

    Package() = default;
    explicit Package(std::string msg)
        : body(std::move(msg)),
        timestamp(std::chrono::system_clock::now()) {}
};

// TODO: Termporary, will eventually need its own class wrapper with a mutex
using PackageQueue = std::queue<std::unique_pointer<Package>>;

} // namespace murmur
