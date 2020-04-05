#ifndef CGCOLORCHANGEVENT_H
#define CGCOLORCHANGEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include <iostream>>

class CgColorChangeEvent : public CgBaseEvent
{
public:
    CgColorChangeEvent();
    CgColorChangeEvent(Cg::EventType type, Cg::Color color, int value);

    //inherited
    Cg::EventType getType();
    CgBaseEvent* clone();

    Cg::Color getColor();
    int getValue();

    friend std::ostream& operator << (std::ostream& os, const CgColorChangeEvent& e);


private:
    Cg::EventType m_type;
    Cg::Color m_color;
    int m_value;
};

inline CgColorChangeEvent::CgColorChangeEvent(){};

#endif // CGCOLORCHANGEEVENT_H
