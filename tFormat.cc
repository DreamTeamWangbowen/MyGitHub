#include "tFormat.hh"

namespace bvc {
namespace base {

uint32_t tFormat::format_chars(const char * const first, const char * const last)
{
    if (first >= last) {
        return 0;
    }

    register char * next = first;

    register uint32_t value = 0;
    do {
        value = static_cast<uint32_t>((value << 3) + (value << 1) + _Digit_from_char(*next));
        ++next;
    } while(next != last);

    return value;
}

char* tFormat::format_uint(register uint32_t value)
{
    char _buffer[BUFFER_SIZE];
    bzero(_buffer, BUFFER_SIZE);
    register char* ptr = _buffer + (BUFFER_SIZE - 1);
    register unsigned index;
    while (value >= 100) {
      index = static_cast<unsigned>((value % 100) << 1);
      value /= 100;
      *--ptr = DIGITS[index + 1]; // "--ptr" this promise the last char is '\0'
      *--ptr = DIGITS[index];
    }
    if (value < 10) {
      *--ptr = static_cast<char>('0' + value);
      return ptr;
    }
    index = static_cast<unsigned>(value << 1);
    *--ptr = DIGITS[index + 1];
    *--ptr = DIGITS[index];
    return ptr;
}

std::string tFormat::format_uint_to_string(register uint32_t value)
{
    return std::move(std::string(format_uint(value)));
}

}// base
}// bvc
