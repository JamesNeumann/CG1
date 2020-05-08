#include "CgSolidOfRevolution.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <iostream>

CgSolidOfRevolution::CgSolidOfRevolution()
{
    m_rotationSteps = 1;
}

//void CgSolidOfRevolution::createRotationBody() {

//    m_vertices.clear();
//    m_triangle_indices.clear();

//    int curveSize = m_rotationCurve.size();
//    double stepSize = (2.0 * M_PI) / m_rotationSteps;
//    glm::mat3x3 yAxisRotation = glm::mat3x3(
//                    glm::vec3(0.0, 0.0, 0.0),
//                    glm::vec3(0.0, 1.0, 0.0),
//                    glm::vec3(0.0, 0.0, 0.0)
//                    );

//    for(int i = 0; i < curveSize; i++) {
//        for (int j = 0; j < m_rotationSteps; j++) {
//            yAxisRotation[0].x = glm::cos(stepSize*j);
//            yAxisRotation[0].z = -glm::sin(stepSize*j);
//            yAxisRotation[2].x = glm::sin(stepSize*j);
//            yAxisRotation[2].z = glm::cos(stepSize*j);
//            m_vertices.push_back(yAxisRotation * m_rotationCurve.at(i));
//        }
//    }

//    for (auto& temp : m_vertices) {
//        std::cout << glm::to_string(temp) << std::endl;

//    }

//    m_face_normals.clear();
//    m_vertex_normals.clear();
//    // calculateNormals();
//}

void CgSolidOfRevolution::createRotationBody() {

    m_vertices.clear();
    m_triangle_indices.clear();

    float PI = 3.14159265359;
    float alpha = 0;
    float step = (2 * PI) / m_rotationSteps;
    float curveSize = m_rotationCurve.size();


    glm::mat3x3 yAxisRotation = glm::mat3x3(
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(0.0, 0.0, 0.0)
                );

    for(int i = 0; i < curveSize; i++) {
        for (int j = 0; j < m_rotationSteps; j++) {
            yAxisRotation[0].x = glm::cos(step*j);
            yAxisRotation[0].z = -glm::sin(step*j);
            yAxisRotation[2].x = glm::sin(step*j);
            yAxisRotation[2].z = glm::cos(step*j);
            m_vertices.push_back(yAxisRotation * m_rotationCurve.at(i));
        }
    }

    float verticesSize = m_vertices.size();
    float verticesPerLevel = verticesSize / curveSize;
    std::cout << verticesSize << std::endl;
    for (int i = 0; i < curveSize* (verticesPerLevel) - verticesPerLevel; i = i + verticesPerLevel) {
        for (int j = 0; j < m_rotationSteps - 1; j++) {
            m_triangle_indices.push_back(i + j);
            m_triangle_indices.push_back(i + verticesPerLevel + j);
            m_triangle_indices.push_back(i + verticesPerLevel+ 1 + j);

            m_triangle_indices.push_back(i + verticesPerLevel + 1 + j);

            m_triangle_indices.push_back(i + 1 + j);
            m_triangle_indices.push_back(i + j);
        }
    }
       std::cout << m_triangle_indices.size() << std::endl;
    for (int i = 0; i < m_triangle_indices.size(); i = i + 3) {
        glm::vec3 a = m_vertices.at(m_triangle_indices.at(i)) - m_vertices.at(m_triangle_indices.at(i + 1));
        glm::vec3 b = m_vertices.at(m_triangle_indices.at(i)) - m_vertices.at(m_triangle_indices.at(i + 2));
        glm::vec3 normal = glm::normalize(
                    glm::cross(
                        a,
                        b
                        ));
        m_face_normals.push_back(normal);
        std::cout << glm::to_string(normal) << std::endl;
    }

    for (int i = 0; i < verticesSize  ; i++) {

    }

    for (int i = 0; i < m_rotationCurve.size() - 1; i++) {
        m_triangle_indices.push_back(i * verticesPerLevel);
        m_triangle_indices.push_back((i+1) * verticesPerLevel);
        m_triangle_indices.push_back((i+1) * verticesPerLevel - 1);
        m_triangle_indices.push_back((i+1) * verticesPerLevel - 1);
        m_triangle_indices.push_back((i+2) * verticesPerLevel - 1);
        m_triangle_indices.push_back((i+1) * verticesPerLevel);
    }

    m_vertices.push_back(glm::vec3(0.0, m_rotationCurve.at(0).y, 0.0));
    m_vertices.push_back(glm::vec3(0.0, m_rotationCurve.at(curveSize - 1).y, 0.0));
    verticesSize = m_vertices.size() - 2;
    verticesPerLevel = verticesSize / curveSize;

    for (int k = 0; k <  verticesPerLevel - 1; k++) {
        m_triangle_indices.push_back(k);
        m_triangle_indices.push_back(k + 1);
        m_triangle_indices.push_back(verticesSize);
    }
    m_triangle_indices.push_back(verticesPerLevel - 1);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(verticesSize);

    for (int k = 0; k <  verticesPerLevel - 1; k++) {
        m_triangle_indices.push_back(k + verticesSize - verticesPerLevel);
        m_triangle_indices.push_back(k + verticesSize - verticesPerLevel + 1);
        m_triangle_indices.push_back(m_vertices.size()-1);
    }
    m_triangle_indices.push_back(verticesSize-1);
    m_triangle_indices.push_back(verticesSize - verticesPerLevel);
    m_triangle_indices.push_back(verticesSize+1);
    calculateNormals();
}
void CgSolidOfRevolution::setRotationCurve(std::vector<glm::vec3> curve) {
    m_rotationCurve = curve;
}

void CgSolidOfRevolution::setRotationSteps(int rotationSteps) {
    m_rotationSteps = rotationSteps;
}

