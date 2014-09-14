//
//  Hash.h
//  SGF
//
//  Created by DEPASSE Arthur on 23/02/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_Hash_h
#define SGF_Hash_h

#include "Config.h"

#ifdef SGF_HASHTYPE_FNV
constexpr uint64_t Hash(const char *str, std::size_t sz) {
    return sz == 0 ? 0xcbf29ce484222325 : (str[0] ^ Hash(str + 1, sz - 1)) * 0x100000001b3;
}

constexpr uint64_t operator"" _hash(const char *str, std::size_t sz) {
    return Hash(str, sz);
}

#else

constexpr uint64_t Hash(const char *str, std::size_t sz) {
    return sz == 0 ? 0xcbf29ce484222325 : (str[0] ^ Hash(str + 1, sz - 1)) * 0x100000001b3;
}

constexpr uint64_t operator"" _hash(const char *str, std::size_t sz) {
    return Hash(str, sz);
}

#endif


#endif
