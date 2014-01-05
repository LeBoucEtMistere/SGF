//
//  Singleton.h
//  SGF
//
//  Created by DEPASSE Arthur on 05/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Singleton__
#define __SGF__Singleton__
#include <memory>

namespace sgf
{

template<class T>
class Singleton
{
private:
    Singleton(void) { }
    ~Singleton(void) { }
    Singleton( const Singleton& rhs );
    Singleton& operator=( const Singleton& rhs);
    static std::shared_ptr<T> mInstance;
public:
    template<typename ... Args>
    static std::shared_ptr<T> Instance(Args & ... arguments)
    {
        if (mInstance == nullptr)
            mInstance.reset(new T(arguments ...));
        return mInstance;
    }
};
}

#endif /* defined(__SGF__Singleton__) */
