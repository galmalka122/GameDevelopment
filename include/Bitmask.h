#ifndef Bitmask_h
#define Bitmask_h

#include <stdint.h>


class Bitmask {

public:

    Bitmask();

    // Overwrite this bitmask
    void SetMask(Bitmask& other);

    // Returns binary representation of the mask
    uint32_t GetMask() const;

    // Returns true if the bit at 'pos' equal 1, else false
    bool GetBit(int pos) const;

    // Sets the bit at 'pos' to 'on'
    void SetBit(int pos, bool on);

    // Sets the bit at 'pos' to 1
    void SetBit(int pos);

    // Sets the bit at 'pos' to 0
    void ClearBit(int pos);

    // Sets all bits to 0
    void Clear();

private:

    uint32_t bits;

};


#endif //Bitmask_h
