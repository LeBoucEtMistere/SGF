//
//  Utils.h
//  SGF
//
//  Created by DEPASSE Arthur on 02/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_Utils_h
#define SGF_Utils_h

#include <string>
#include <ctime>
#include <time.h>
#include <SFML/System.hpp>

namespace sgf
{
    
    // return the date under the format :
    // year-month-day hour:minutes:second
    enum TimeFormat
    {
        AMERICAN = 0,
        FRENCH = 1,
    };
    
    inline std::string dateToString(TimeFormat const& timeFormat = AMERICAN)
    {
        const std::tm* tm; // Time structure pointer
        std::time_t now;
        
        // Get current timestamp
        now = std::time(NULL);
        
        // Convert current time to local time
        tm = std::localtime(&now);
        
        std::string date, year, month, day, hour, min, sec;
        
        year = std::to_string(tm->tm_year + 1900);
        
        if ((tm->tm_mon + 1) < 10) month +="0";
        month += std::to_string(tm->tm_mon + 1);
        
        if ((tm->tm_mday) < 10) day +="0";
        day += std::to_string(tm->tm_mday);
        
        if ((tm->tm_hour + 1) < 10) hour +="0";
        hour += std::to_string(tm->tm_hour + 1);
        
        if ((tm->tm_min) < 10) min +="0";
        min += std::to_string(tm->tm_min);
        
        if ((tm->tm_sec) < 10) sec +="0";
        sec += std::to_string(tm->tm_sec);
        
        switch (timeFormat) {
            case AMERICAN:
                date = year + "-"+ month + "-"+ day + " "+ hour + ":"+ min + ":"+ sec + " ";
                break;
            case FRENCH:
                date = day + "/"+ month + "/"+ year + " "+ hour + ":"+ min + ":"+ sec + " ";
                break;
                
            default:
                break;
        }
        
        return date;

    }
    
    inline std::chrono::nanoseconds SfTimeToStd(sf::Time const& time)
    {
        return std::chrono::nanoseconds(time.asMicroseconds()*1000);
    }
    
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif
