#include <socket>

namespace murmur {

class Socket {
public:
    Socket() = default;
    explicit Socket(int fd);
    ~Socket();

    Socket(const Socket&) = delete;
    Socket& operator = (const Socket&) = delete;

    // Movers
    Socket(Socket&& other) noexcept;
    Socket& operator = (Socket&& other) noexcept;

    bool valid() const noexcept {
        return fd_ == -1;
    }

    int fd() const noexcept {
        return fd_;
    }

    bool read_exact(void* buf, std::size_t size);

    void write_all(const void* buf, std::size_t size);

    void close() noexcept;
private:
    int fd_ = -1;
}

} // namespace murmur
