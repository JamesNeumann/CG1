#include "CgRenderObjectEvent.h"

CgRenderObjectEvent::CgRenderObjectEvent(Cg::EventType type, int buttonNumber)
{
    m_type = type;
    m_buttomNumber = buttonNumber;
}

CgBaseEvent* CgRenderObjectEvent::clone()
{
    return new CgRenderObjectEvent(m_type, m_buttomNumber);
}


Cg::EventType CgRenderObjectEvent::getType()
{
    return m_type;
}

int CgRenderObjectEvent::getButtonNumber() {
    return m_buttomNumber;
}
std::ostream& operator << (std::ostream& os, const CgRenderObjectEvent& e)
{
    os << e.m_buttomNumber << " wurde geändert";
    return os;
}
CgRenderObjectEvent::~CgRenderObjectEvent(){}
