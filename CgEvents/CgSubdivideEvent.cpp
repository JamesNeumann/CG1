#include "CgSubdivideEvent.h"

CgSubdivideEvent::CgSubdivideEvent(Cg::EventType type, int value) {
    m_type = type;
    m_value = value;
}

CgBaseEvent* CgSubdivideEvent::clone()
{
    return new CgSubdivideEvent(m_type, m_value);
}

std::ostream& operator << (std::ostream& os, const CgSubdivideEvent& e)
{
    os << "Subdivide-Steps: " << e.m_value;
    return os;
}
Cg::EventType CgSubdivideEvent::getType()
{
    return m_type;
}

int CgSubdivideEvent::getValue() {return m_value;}
