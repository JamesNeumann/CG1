#include "CgPolyline.h"

CgPolyline::CgPolyline()
{

}

CgPolyline::CgPolyline(std::vector<glm::vec3> args_verticies, int id):
    m_type(Cg::Polyline),
    m_id(id)
{
    m_verticies = args_verticies;
    m_lineWidth = 1;
    m_color = Cg::BASECOLOR;
}

void CgPolyline::setColor(Cg::Color color, int value) {
    if (color == Cg::Red) m_color.x = value / 255.0f;
    else if (color == Cg::Green) m_color.y = value / 255.0f;
    else if (color == Cg::Blue) m_color.z = value / 255.0f;
}

CgPolyline::~CgPolyline() {

}
