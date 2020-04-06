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
}

CgPolyline::~CgPolyline() {

}
