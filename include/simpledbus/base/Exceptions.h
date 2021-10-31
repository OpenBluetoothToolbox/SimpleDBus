#pragma once

#include <stdexcept>
#include <string>

namespace SimpleDBus {

namespace Exception {

class BaseException : public std::runtime_error {
  public:
    BaseException(const std::string& __arg) : std::runtime_error(__arg) {}
};

class ConnectionException : public BaseException {
  public:
    ConnectionException(const std::string& __arg) : BaseException(__arg) {}
};

}  // namespace Exception

}  // namespace SimpleDBus
