#ifndef CGBUTTONCLICKEDEVENT_H
#define CGBUTTONCLICKEDEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include <iostream>

class CgButtonClickedEvent : public CgBaseEvent
{
public:
    CgButtonClickedEvent();
    CgButtonClickedEvent(Cg::EventType type, Cg::ButtonEventType);

    Cg::EventType getType();
    CgBaseEvent* clone();

    Cg::ButtonEventType getButtonEventType();

    friend std::ostream& operator << (std::ostream& os, const CgButtonClickedEvent& e);

private:
    Cg::EventType m_type;
    Cg::ButtonEventType m_buttonEventType;
};

inline CgButtonClickedEvent::CgButtonClickedEvent(){};

#endif // CGBUTTONCLICKEDEVENT_H
