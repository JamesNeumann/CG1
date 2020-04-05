#include "CgColorChangEvent.h"


CgColorChangeEvent::CgColorChangeEvent(Cg::EventType type, Cg::Color color, int value)
{
    m_type = type;
    m_color = color;
    m_value = value;
}

CgBaseEvent* CgColorChangeEvent::clone()
{
    return new CgColorChangeEvent(m_type, m_color, m_value);
}

Cg::EventType CgColorChangeEvent::getType()
{
    return m_type;
}

Cg::Color CgColorChangeEvent::getColor()
{
    return m_color;
}

int CgColorChangeEvent::getValue()
{
    return m_value;
}

std::ostream& operator << (std::ostream& os, const CgColorChangeEvent& e)
{
    os << "Farbe wurde geändert";
    return os;
}
