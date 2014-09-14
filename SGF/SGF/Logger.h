//
//  Logger.h
//  SGF
//
//  Created by DEPASSE Arthur on 29/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Logger__
#define __SGF__Logger__

#include "Config.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include "Exception.h"

namespace sgf
{
    class Logger
    {
        
    private:
        
        Logger(): _err_stream(nullptr), _log_stream(nullptr), _previous_cerr(nullptr), _previous_clog(nullptr)
        {
            
        #ifdef ERR_TO_FILE
            
            #ifdef ERR_FILE
            _err_stream = new std::ofstream(ERR_FILE);
            #else
            _err_stream = new std::ofstream("err.txt");
            #endif
            
            _previous_cerr = std::cerr.rdbuf();
            
            if(*_err_stream)
            {
                std::cerr.rdbuf(_err_stream->rdbuf());
            }
            else
            {
                std::cerr << "Unexpected error : unable to open the err file and redirect the error stream";
            }
            
        #endif
            
            
        #ifdef LOG_TO_FILE
            
            #ifdef LOG_FILE
            _log_stream = new std::ofstream(LOG_FILE);
            #else
            _log_stream = new std::ofstream("log.txt");
            #endif
            
            _previous_clog = std::clog.rdbuf();
            
            if(*_log_stream)
            {
                std::clog.rdbuf(_log_stream->rdbuf());
            }
            else
            {
                std::cerr << "Unexpected error : unable to open the log file and redirect the log stream";
            }
            
        #endif

        }
        
        Logger(Logger const&);
        void operator=(Logger const&);
        
    public:
        
        enum OS
        {
            LOG = 0,
            ERR = 1
        };
        
        ~Logger()
        {
            if (_previous_cerr != nullptr){
                std::cerr.rdbuf(_previous_cerr);
            }
            if (_previous_clog != nullptr){
                std::clog.rdbuf(_previous_clog);
            }
            if (_err_stream != nullptr){
                _err_stream->close();
                delete _err_stream;
            }
            if (_log_stream != nullptr){
                _log_stream->close();
                delete _log_stream;
            }
        }
        
        void stream(const char* msg, OS const& os = OS::ERR )
        {
            if (os == OS::ERR)
            {
                #ifdef ERR_TO_FILE
                    #ifdef LANGUAGE
                std::cerr << sgf::dateToString(sgf::LANGUAGE).c_str();
                    #endif
                #endif
                std::cerr << "[ERROR]" << msg << std::endl;
            
            }
            else if (os == OS::LOG)
            {
                #ifdef LOG_TO_FILE
                    #ifdef LANGUAGE
                std::clog << sgf::dateToString(sgf::LANGUAGE).c_str();
                    #endif                
                #endif
                std::clog << "[LOG]" << msg << std::endl;
            }

        }
        static std::shared_ptr<Logger> getLogger()
        {
            if (_singleton == nullptr)
                _singleton.reset(new Logger);
            return _singleton;
        }
        
    private:

        std::ofstream* _err_stream;
        std::ofstream* _log_stream;
        std::streambuf* _previous_cerr;
        std::streambuf* _previous_clog;

        static std::shared_ptr<Logger> _singleton;
    
    };
        
#ifdef SGF_LOGGER
    #ifdef ENABLE_ONLY_IN_DEBUG
        #ifdef DEBUG
            #define LOG(x) sgf::Logger::getLogger()->stream(x,sgf::Logger::OS::LOG);
            #define ERR(x) sgf::Logger::getLogger()->stream(x,sgf::Logger::OS::ERR);
        #else
            #define LOG(x)
            #define ERR(x)
        #endif
    #else
        #define LOG(x) sgf::Logger::getLogger()->stream(x,sgf::Logger::OS::LOG);
        #define ERR(x) sgf::Logger::getLogger()->stream(x,sgf::Logger::OS::ERR);
    #endif
#else
    #define LOG(x)
    #define ERR(x)    
#endif
    
}
#endif /* defined(__SGF__Logger__) */
