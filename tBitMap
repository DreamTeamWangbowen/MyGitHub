#ifndef _T_BITMAP_HH_
#define _T_BITMAP_HH_
#include <iostream>
#include <strings.h>

namespace bvc {
namespace base {

    // only support 512M
    // address range [0, 4G)
    class tBitMap {
    public:
        tBitMap():_bitmap(nullptr),_up_bound(0){}
        tBitMap(const uint32_t len):_bitmap(nullptr),_up_bound(0)
        {
            init(len);
        };
        bool init(const uint32_t len)
        {
            if (len > 512 * 1024 * 1024) {
                return false;
            }
            _bitmap = new(std::nothrow) uint8_t[len];
            if (_bitmap == nullptr) {
                return false;
            }
            _up_bound = len;
            bzero(_bitmap, len);
            return true;
        }
        ~tBitMap()
        {
            if (_bitmap) {
                delete [] _bitmap;
            }
        }
    public:
        void add(const uint32_t key);
        bool match(const uint32_t key);
        void reset();
    private:
        uint8_t* _bitmap;
        uint32_t _up_bound;

    };

}// base
}// bvc

#endif
