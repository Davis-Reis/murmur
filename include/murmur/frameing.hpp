#pragma once

#include "socpp.hpp"

void write_framed(Socket& sock, const void* data, std::size_t size);

std::vector<std::uint8_t> read_framed(Socket& sock);
