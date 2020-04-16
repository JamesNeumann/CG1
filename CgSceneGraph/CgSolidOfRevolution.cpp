#include "CgSolidOfRevolution.h"
#include "CgExampleTriangle.h"
#include "CgUtils/ObjLoader.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <glm/gtx/normal.hpp>

CgSolidOfRevolution::CgSolidOfRevolution():m_type(Cg::TriangleMesh),m_id(203)
{

}
CgSolidOfRevolution::CgSolidOfRevolution(std::vector<glm::vec3> curve, int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    m_curve = curve;
}

void CgSolidOfRevolution::calculateVertices()
{
    m_vertices.clear();
    m_triangle_indices.clear();
    float PI = 3.14159265359;
    float alpha = 0;
    float step = (2 * PI) / m_rotationSegments;
    float curveSize = m_curve.size();


    glm::mat3x3 yAxisRotation = glm::mat3x3(
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(0.0, 0.0, 0.0)
                );

    for(int i = 0; i < curveSize; i++) {
        for (int j = 0; j < m_rotationSegments; j++) {
            yAxisRotation[0].x = glm::cos(step*j);
            yAxisRotation[0].z = -glm::sin(step*j);
            yAxisRotation[2].x = glm::sin(step*j);
            yAxisRotation[2].z = glm::cos(step*j);
            m_vertices.push_back(yAxisRotation * m_curve.at(i));
        }
    }

    float verticesSize = m_vertices.size();
    float verticesPerLevel = verticesSize / curveSize;
    std::cout << verticesSize << std::endl;
    for (int i = 0; i < curveSize* (verticesPerLevel) - verticesPerLevel; i = i + verticesPerLevel) {
        for (int j = 0; j < m_rotationSegments - 1; j++) {
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

    for (int i = 0; i < m_curve.size() - 1; i++) {
        m_triangle_indices.push_back(i * verticesPerLevel);
        m_triangle_indices.push_back((i+1) * verticesPerLevel);
        m_triangle_indices.push_back((i+1) * verticesPerLevel - 1);
        m_triangle_indices.push_back((i+1) * verticesPerLevel - 1);
        m_triangle_indices.push_back((i+2) * verticesPerLevel - 1);
        m_triangle_indices.push_back((i+1) * verticesPerLevel);
    }

    m_vertices.push_back(glm::vec3(0.0, m_curve.at(0).y, 0.0));
    m_vertices.push_back(glm::vec3(0.0, m_curve.at(curveSize - 1).y, 0.0));
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
}
CgSolidOfRevolution::~CgSolidOfRevolution()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgSolidOfRevolution::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgSolidOfRevolution::init( std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
}

const std::vector<glm::vec3>& CgSolidOfRevolution::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgSolidOfRevolution::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgSolidOfRevolution::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2>& CgSolidOfRevolution:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgSolidOfRevolution::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgSolidOfRevolution::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgSolidOfRevolution::getFaceColors() const
{
    return m_face_colors;
}

void CgSolidOfRevolution::setRotationSegments(int value) {
    m_rotationSegments = value;
}

void CgSolidOfRevolution::setCurve(std::vector<glm::vec3> curve)
{
    m_curve = curve;

}
