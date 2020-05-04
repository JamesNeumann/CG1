#include "CgRenderObjectEvent.h"

CgRenderObjectEvent::CgRenderObjectEvent(Cg::EventType type, int buttonNumber)
{
    m_type = type;
    m_buttomNumber = buttonNumber;
}

CgBaseEvent* CgRenderObjectEvent::clone()
{
    return new CgRenderObjectEvent(m_type, m_color, m_value);
}


Cg::EventType CgRenderObjectEvent::getType()
{
    return m_type;
}

int CgRenderObjectEvent::getValue()
{
    return CgRenderObjectEvent;
}

std::ostream& operator << (std::ostream& os, const CgRenderObjectEvent& e)
{
    os << e.m_buttomNumber << " wurde geändert";
    return os;
}
