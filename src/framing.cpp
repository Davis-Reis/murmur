#include "framing.hpp"

namespace murmur {

    void write_framed(Socket& sock, const void* data, std::size_t size) {
        std::uint32_t len = static_cast<const std::uint32_t>size;
        std::uint32_t header = htonl(len);
        try {
            Socket::write_all(sock, &header, 4);
            Socket::write_all(sock, data, len);
        } catch (err) {
            std::cerr << "write_framed failed at Socket::write_all: " << err << std::endl;
        }
    }
}
