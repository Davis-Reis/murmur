#include "framing.hpp"

namespace murmur {

    void write_framed(Socket& sock, const void* data, std::size_t size) {
        size_t len = size - 4;
        int header = htonl(len);
        Socket::write_all(sock, &header, size);
        Socket::write_all(sock, data, len);
}
