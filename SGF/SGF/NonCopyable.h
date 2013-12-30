//
//  NonCopyable.h
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__NonCopyable__
#define __SGF__NonCopyable__

namespace sgf {
  
    class NonCopyable
    {
    public:
        
        virtual ~NonCopyable() {};
        
    private:
        NonCopyable(NonCopyable const&);
        void operator=(NonCopyable const&);
    };
    
}
#endif /* defined(__SGF__NonCopyable__) */
