//
//  Exception.h
//  SGF
//
//  Created by DEPASSE Arthur on 11/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_Exception_h
#define SGF_Exception_h

#include <exception>
#include <string>
#include <fstream>
#include <iostream>

namespace sgf
{
    
    
    enum ExceptionLevel
    {
        WARNING = 0,
        ALERT = 1,
        SEVERE = 2,
        FATAL = 3
    };
    enum ExceptionType
    {
        UNKNOW = 0,
        STANDARD = 1,
        LOADER = 2,
        FILE = 3,
        MISSING_FUNCTION_DEF = 4
    };
    

    
    class Exception : public std::exception
    {
        
    public:
        
        // CTOR //
        
        Exception(std::string const& info="No more informations.",
                  sgf::ExceptionLevel level= ExceptionLevel::WARNING,
                  sgf::ExceptionType type = ExceptionType::UNKNOW)throw() : mLevel(level), mType(type), mMsg("")
        {
            std::string levelString = lvlToString(mLevel);
            std::string typeString = typeToString(mType);
            
            mMsg = levelString + " : An exception occured of " + typeString + " type. " + info + "\r";
            
        }
        
        // MAIN METHOD //
        
        virtual const char* what() const throw()
        {
            return mMsg.c_str();
        }
        
        ExceptionLevel const& getLevel() const throw()
        {
            return mLevel;
        }
        ExceptionType const& getType() const throw()
        {
            return mType;
        }
        
        // DTOR //
        
        virtual ~Exception() throw()
        {
            
        }
    
    protected:
        
        std::string lvlToString(sgf::ExceptionLevel const& lvl) const throw()
        {
            std::string lvlStr;
            switch(lvl)
            {
                case ExceptionLevel::WARNING:
                    lvlStr  = "[WARNING]";
                    break;
                case ExceptionLevel::ALERT:
                    lvlStr  = "[ALERT]";
                    break;
                case ExceptionLevel::SEVERE:
                    lvlStr  = "[SEVERE]";
                    break;
                case ExceptionLevel::FATAL:
                    lvlStr  = "[FATAL]";
                    break;
                    
            }
            return lvlStr;
        }
        std::string typeToString(sgf::ExceptionType const& type) const throw()
        {
            std::string typeStr;
            switch(type)
            {
                case ExceptionType::UNKNOW:
                    typeStr  = "unknow";
                    break;
                case ExceptionType::STANDARD:
                    typeStr  = "standard";
                    break;
                case ExceptionType::LOADER:
                    typeStr  = "loader utilisation";
                    break;
                case ExceptionType::FILE:
                    typeStr  = "file loading/unloading";
                    break;
                case ExceptionType::MISSING_FUNCTION_DEF:
                    typeStr  = "missing required function definition";
                    break;
                    
            }
            return typeStr;
        }


        
        sgf::ExceptionLevel mLevel;
        sgf::ExceptionType mType;
        std::string mMsg;

    
    };

    
    
    /////////////////////////////////////////////
    //////////// DERIVED EXCEPTIONS /////////////
    /////////////////////////////////////////////

    
    class LoaderException : public sgf::Exception
    {
    public:
        LoaderException(std::string const& loaderName,
                        std::string const& ressourceID= "",
                        std::string const& info="No more informations.",
                        sgf::ExceptionLevel level=ExceptionLevel::WARNING)throw()
        : sgf::Exception(info, level, ExceptionType::LOADER), mLoaderName(loaderName), mRessourceID(ressourceID)
        {
            std::string levelString = lvlToString(mLevel);
            std::string typeString = typeToString(mType);
            
            mMsg = levelString + " : An exception occured of " + typeString + " type in loader : \"" + loaderName + "\" with the following ressource ID : \"" + ressourceID + "\".\r" + info + "\r";
        }
        
        virtual const char* what() const throw()
        {
            return mMsg.c_str();
        }
        
    protected:
        std::string mFilename;
        std::string mRessourceID;
        std::string mLoaderName;

    };
    
    
    /////////////////////////////////////////////
    
    class FileException : public sgf::Exception
    {
    public:
        FileException(std::string const& filepath,
                      std::string const& info="No more informations.",
                      sgf::ExceptionLevel level = ExceptionLevel::WARNING)throw()
        : sgf::Exception(info, level, ExceptionType::FILE), mFilename(filepath)
        {
            std::string levelString = lvlToString(mLevel);
            std::string typeString = typeToString(mType);
            
            mMsg = levelString + " : An exception occured of " + typeString + " type while loading/unloading the file : \"" + filepath + "\".\r" + info + "\r";
        }
        virtual const char* what() const throw()
        {
            return mMsg.c_str();
        }
        
    protected:
        std::string mFilename;
        
    };
    
}


#endif
