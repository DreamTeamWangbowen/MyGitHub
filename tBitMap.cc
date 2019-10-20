#include "tBitMap.hh"

using namespace bvc::base;

void tBitMap::add(const uint32_t key) {
    if (!_bitmap) {
        return;
    }
    const uint32_t index = (key >> 3);
    if (index >= _up_bound) {
        return;
    }
    _bitmap[index] |= (0x01 << (key & 0x07));
    return; 
}    
    
bool tBitMap::match(const uint32_t key) {
    if (!_bitmap) {
        return false;
    }
    const uint32_t index = (key >> 3);
    if (index >= _up_bound) {
        return  false;
    }
    return (_bitmap[index] >> (key & 0x07)) & 0x01; 
}

void tBitMap::reset()
{
    if (!_bitmap) {
        return;
    }
    bzero(_bitmap, _up_bound);
    return;
}
