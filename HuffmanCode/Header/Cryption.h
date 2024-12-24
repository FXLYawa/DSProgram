/********************************/
/* Created by FXLY, with VSCode */
/********************************/

#ifndef CRYPTION_CRYPTION_FXLY
#define CRYPTION_CRYPTION_FXLY

#include <random>

// 加密类与解密类
namespace Cryption {
    const unsigned long long key = 0x1F351F35;
    typedef unsigned char info;
    class EnCryption {
    private:
        std::mt19937_64 rnd;
        bool a[8];
        int pos;

    public:
        EnCryption() {
            rnd.seed(key);
            pos = 0;
        }
        bool push(bool c) {
            a[pos++] = c;
            return pos == 8;
        }
        info get() {
            info res = pos = 0;
            for (int i = 0; i < 8; i++) res = (res << 1) | a[i];
            return res ^ (info)rnd();
        }
    };
    
    class DeCryption {
    private:
        std::mt19937_64 rnd;

    public:
        DeCryption() { rnd.seed(key); }
        info get(info c) { return c ^ (info)rnd(); }
    };
};  // namespace Cryption

#endif  // CRYPTION_CRYPTION_FXLY
