#include "framing.hpp"

#include <cassert>
#include <string_view>

int main() {

    using namespace std::literals;
    
    std::string IP = "127.0.0.1";
    constexpr std::uint16_t port = 8080;

    // write testing
    auto listener = socpp::Socket::listen(port);
    auto sock = socpp::Socket::connect(IP, port);
    auto client = listener.accept();


    auto str = "Hello, World!"sv;
    std::vector<std::uint8_t> buffer(str.begin(), str.end());
    murmur::write_framed(sock, buffer);

    auto got = murmur::read_framed(client);
    assert(got.has_value());
    assert(*got == buffer);

    sock.close();
    assert(!murmur::read_framed(client).has_value());

    return 0;
}
