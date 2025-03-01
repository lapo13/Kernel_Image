#include <cstdint>
#include <limits>
#include <type_traits>

// Type traits for pixel data types
template<typename T>
struct PixelTraits {
    static constexpr bool is_valid = false;
};

// Specializations for supported types
template<>
struct PixelTraits<uint8_t> {
    static constexpr bool is_valid = true;
    static constexpr uint8_t min_value = 0;
    static constexpr uint8_t max_value = 255;
    static constexpr const char* name = "UINT8";
};