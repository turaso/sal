#ifndef SAL_UTIL_HH_
#define SAL_UTIL_HH_

namespace sal::util {

template<typename T>
constexpr T & as_mutable(T const & value) noexcept {
  return const_cast<T &>(value);
}

template<typename T>
constexpr T * as_mutable(T const * value) noexcept {
  return const_cast<T *>(value);
}

template<typename T>
constexpr T * as_mutable(T * value) noexcept {
  return value;
}

template<typename T>
void as_mutable(T const &&) = delete;

} /// namesapce sal::util

#endif /// SAL_UTIL_HH_
