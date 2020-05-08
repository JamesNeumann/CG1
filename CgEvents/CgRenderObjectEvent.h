#ifndef CGRENDEROBJECTEVENT_H
#define CGRENDEROBJECTEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include <iostream>

class CgRenderObjectEvent : public CgBaseEvent
{
public:
    CgRenderObjectEvent();
    CgRenderObjectEvent(Cg::EventType type, int buttonNumber);


    Cg::EventType getType();
    CgBaseEvent* clone();

    int getButtonNumber();
    friend std::ostream& operator << (std::ostream& os, const CgRenderObjectEvent& e);

    ~CgRenderObjectEvent();

private:
    Cg::EventType m_type;
    int m_buttomNumber;
};

inline CgRenderObjectEvent::CgRenderObjectEvent(){};

#endif // CGRENDEROBJECTEVENT_H
