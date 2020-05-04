#include "CgSolidOfRevolution.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <iostream>

CgSolidOfRevolution::CgSolidOfRevolution()
{
    m_rotationSteps = 1;
}

void CgSolidOfRevolution::createRotationBody() {

    m_vertices.clear();
    m_triangle_indices.clear();

    int curveSize = m_rotationCurve.size();
    double stepSize = (2.0 * M_PI) / m_rotationSteps;
    glm::mat3x3 yAxisRotation = glm::mat3x3(
                    glm::vec3(0.0, 0.0, 0.0),
                    glm::vec3(0.0, 1.0, 0.0),
                    glm::vec3(0.0, 0.0, 0.0)
                    );

    for(int i = 0; i < curveSize; i++) {
        for (int j = 0; j < m_rotationSteps; j++) {
            yAxisRotation[0].x = glm::cos(stepSize*j);
            yAxisRotation[0].z = -glm::sin(stepSize*j);
            yAxisRotation[2].x = glm::sin(stepSize*j);
            yAxisRotation[2].z = glm::cos(stepSize*j);
            m_vertices.push_back(yAxisRotation * m_rotationCurve.at(i));
        }
    }

    for (auto& temp : m_vertices) {
        std::cout << glm::to_string(temp) << std::endl;

    }

    m_face_normals.clear();
    m_vertex_normals.clear();
    // calculateNormals();
}

void CgSolidOfRevolution::setRotationCurve(std::vector<glm::vec3> curve) {
    m_rotationCurve = curve;
}

void CgSolidOfRevolution::setRotationSteps(int rotationSteps) {
    m_rotationSteps = rotationSteps;
}

