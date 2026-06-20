#include "framing.hpp"
#include <stdexcept>
#include <vector>


namespace murmur {

    void write_framed(Socket& sock, std::span<const std::uint8_t> data){
        if (data.size() > MAX_MESSAGE) {
            throw std::length_error("write_framed: message exceeds MAX_MESSAGE");
        }
        std::uint32_t len = static_cast<std::uint32_t>(data.size());
        std::uint32_t header = htonl(len);
        sock.write_all(&header, sizeof(header));
        sock.write_all(data.data(), data.size());
    }

    std::vector<std::uint8_t> read_framed(Socket& sock) {
        // Read the header to see how big the next message is
        std::uint32_t header;
        sock.read_exact(&header, sizeof(header));
        std::uint32_t len = ntohl(header);

        if (len > MAX_MESSAGE) {
            throw std::length_error("read_framed: incoming message exceeds MAX_MESSAGE");
        }

        // Store message after header with size specified in header
        std::vector<std::uint8_t> buffer(len);
        sock.read_exact(buffer.data(), len);

        return buffer;
    }


} // namespace
