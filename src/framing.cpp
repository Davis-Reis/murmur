#include "framing.hpp"

namespace murmur {

    void write_framed(Socket& sock, const void* data, std::size_t size) {
        size_t len = size - 4;
        int header = htonl(len);
        try {
            Socket::write_all(sock, &header, size);
            Socket::write_all(sock, data, len);
        } catch (err) {
            std::cerr << "write_framed failed at Socket::write_all: " << err << std::endl;
        }
    }
}
