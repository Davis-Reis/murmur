#include "framing.hpp"
#include <stdexcept>

namespace murmur {

    void write_framed(Socket& sock, const void* data, std::size_t size) {
        if (size > MAX_MESSAGE) {
            throw std::length_error("write_framed: message exceeds MAX_MESSAGE");
        }
        std::uint32_t len = static_cast<const std::uint32_t>size;
        std::uint32_t header = htonl(len);
        sock.write_all(&header, sizeof(header));
        sock.write_all(data, len);
}

} // namespace
