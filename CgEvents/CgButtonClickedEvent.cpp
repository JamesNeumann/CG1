#include "CgButtonClickedEvent.h"

CgButtonClickedEvent::CgButtonClickedEvent(Cg::EventType type, Cg::ButtonEventType buttonEventType)
{
    m_type = type;
    m_buttonEventType = buttonEventType;

}

CgBaseEvent* CgButtonClickedEvent::clone()
{
    return new CgButtonClickedEvent(m_type, m_buttonEventType);
}

Cg::EventType CgButtonClickedEvent::getType()
{
    return m_type;
}

Cg::ButtonEventType CgButtonClickedEvent::getButtonEventType() {
    return m_buttonEventType;
}


std::ostream& operator << (std::ostream& os, const CgButtonClickedEvent& e)
{
    os << "Button clicked";
    return os;
}
