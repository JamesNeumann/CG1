#include "CgPolyline.h"
#include <iostream>
CgPolyline::CgPolyline()
{

}

CgPolyline::CgPolyline(std::vector<glm::vec3> args_verticies, int id):
    m_type(Cg::Polyline),
    m_id(id)
{
    m_verticies = args_verticies;
    m_lineWidth = 3;
    m_color = Cg::BASECOLOR;
}

void CgPolyline::setColor(Cg::Color color, int value) {
    if (color == Cg::Red) m_color.x = value / 255.0f;
    else if (color == Cg::Green) m_color.y = value / 255.0f;
    else if (color == Cg::Blue) m_color.z = value / 255.0f;
}

void CgPolyline::setVertices(std::vector<glm::vec3> newVertices) {
    m_verticies = newVertices;
}

void CgPolyline::setMaxSubdivision(int value) {
    maxSubdivision = value;
}
void CgPolyline::applyLaneRiesenfeld(int steps) {
    if (subdivided == 1) back_up_vertices = m_verticies;
    if (subdivided < maxSubdivision) {
        for (int i = 0; i < steps; i++) {
            std::vector<glm::vec3> temp (m_verticies.size());
            temp.insert(temp.begin(), m_verticies.begin(), m_verticies.end());

            for (int i = temp.size() - (temp.size() / 2) - 1; i >= 0; i--) {
                temp.at(2 * i + 1) = temp.at(i);
                temp.at(2 * i) =  temp.at(i);
            }

            for (int j = 0; j < temp.size() - 1; j++) {
                temp.at(j) = ((temp.at(j) + temp.at(j + 1)) * 0.5f);
            }
            for (int j = 0; j < temp.size() - 1; j++) {
                temp.at(j) = ((temp.at(j) + temp.at(j + 1)) * 0.5f);
            }
            if (m_verticies.at(0) == m_verticies.at(m_verticies.size() - 1)) {
                m_verticies = temp;
                m_verticies.pop_back();
                m_verticies.at(m_verticies.size() - 1)  = temp.at(0);
            } else {
                m_verticies = temp;
            }

        }
        subdivided++;
    }
}

void CgPolyline::reset() {
    m_verticies = back_up_vertices;
    subdivided = 1;
}

CgPolyline::~CgPolyline() {

}
