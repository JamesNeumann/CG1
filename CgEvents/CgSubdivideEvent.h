#ifndef CGSUBDIVIDEEVENT_H
#define CGSUBDIVIDEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include <iostream>

class CgSubdivideEvent : public CgBaseEvent
{
public:
    CgSubdivideEvent();
    CgSubdivideEvent(Cg::EventType type, int value);

    Cg::EventType getType();
    CgBaseEvent* clone();

    int getValue();

    friend std::ostream& operator << (std::ostream& os, const CgSubdivideEvent& e);

private:
    Cg::EventType m_type;
    int m_value;
};

inline CgSubdivideEvent::CgSubdivideEvent(){};


#endif // CGSUBDIVIDEEVENT_H
