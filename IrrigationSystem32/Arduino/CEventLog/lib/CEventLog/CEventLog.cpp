#include "CEventLog.h"

CEventLog::CEventLog(const unsigned int capacity):
    _buffer(capacity)
{
}

bool CEventLog::Empty()
{
    return _buffer.Empty();
}

unsigned int CEventLog::Size()
{
    return _buffer.Size();
}

unsigned int CEventLog::Capacity()
{
    return _buffer.Capacity();
}

void CEventLog::Write(EventLogType event)
{
    _buffer.Push(event);
}

EventLogType CEventLog::Read(const unsigned int index)
{
    return _buffer[0];
}
