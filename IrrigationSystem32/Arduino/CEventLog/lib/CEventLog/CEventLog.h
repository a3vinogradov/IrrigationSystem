#pragma once

#include "cbuffer.h"

enum EventType {
    LoadSystem = 0,
    IrrigateStart,
};

struct EventLogType
{ 
    unsigned long Millis;
    EventType eventType;
    union 
    {
        struct 
        {
            int currentMoisture;   
            int targetMoisture;
            int count;
        };

    };
};

class CEventLog
{
private:
    CBuffer<EventLogType> _buffer;
public:
    CEventLog(const unsigned int capacity);

    bool Empty();
    unsigned int Size();
    unsigned int Capacity();

    void Write(EventLogType event);
    EventLogType Read(const unsigned int index);

};