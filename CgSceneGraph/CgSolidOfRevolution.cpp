#include "CgSolidOfRevolution.h"
#include "CgExampleTriangle.h"
#include "CgUtils/ObjLoader.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <iostream>
CgSolidOfRevolution::CgSolidOfRevolution(std::vector<glm::vec3> curve, int rotationSegments, int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    m_curve = curve;
    m_rotationSegments = rotationSegments;
}

void CgSolidOfRevolution::calculateVertices()
{
    float PI = 3.14159265359;
    float alpha = 0;
    float step = (2 * PI) / m_rotationSegments;
    glm::mat3x3 yAxisRotation = glm::mat3x3(
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(0.0, 0.0, 0.0)
                );

    for(int i = 0; i < m_curve.size(); i++) {
        for (int j = 0; j < m_rotationSegments; j++) {
            yAxisRotation[0].x = glm::cos(step*j);
            yAxisRotation[0].z = -glm::sin(step*j);
            yAxisRotation[2].x = glm::sin(step*j);
            yAxisRotation[2].z = glm::cos(step*j);
            m_vertices.push_back(yAxisRotation * m_curve.at(i));
        }
    }

    for (auto& vert : m_vertices) {
        std::cout << glm::to_string(vert) << std::endl;
    }
//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(0 + m_vertices.size() / m_curve.size());
//    m_triangle_indices.push_back(0 + m_vertices.size() / m_curve.size() + 1);
//    m_triangle_indices.push_back(0 + m_vertices.size() / m_curve.size() + 1);
//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(1);

//    m_triangle_indices.push_back(m_vertices.size() / m_curve.size());
//    m_triangle_indices.push_back(m_vertices.size() / m_curve.size() + m_vertices.size() / m_curve.size());
//    m_triangle_indices.push_back(m_vertices.size() / m_curve.size()+ m_vertices.size() / m_curve.size() + 1);
//    m_triangle_indices.push_back(m_vertices.size() / m_curve.size()+ m_vertices.size() / m_curve.size() + 1);
//    m_triangle_indices.push_back(m_vertices.size() / m_curve.size() + 1);
//    m_triangle_indices.push_back(m_vertices.size() / m_curve.size());


    for (int i = 0; i < m_curve.size()* (m_vertices.size() / m_curve.size()) - m_vertices.size() / m_curve.size(); i = i + m_vertices.size() / m_curve.size()) {
        std::cout << i << std::endl;
        for (int j = 0; j < m_rotationSegments - 1; j++) {
            m_triangle_indices.push_back(i + j);
            m_triangle_indices.push_back(i + m_vertices.size() / m_curve.size() + j);
            m_triangle_indices.push_back(i + (m_vertices.size() / m_curve.size()) + 1 + j);
            m_triangle_indices.push_back(i + m_vertices.size() / m_curve.size() + 1 + j);
            m_triangle_indices.push_back(i + 1 + j);
            m_triangle_indices.push_back(i + j);
        }
    }

    for (int i = 0; i < m_curve.size() - 1; i++) {
        m_triangle_indices.push_back(i * m_vertices.size() / m_curve.size());
        m_triangle_indices.push_back((i+1) * m_vertices.size() / m_curve.size());
        m_triangle_indices.push_back((i+1) * m_vertices.size() / m_curve.size() - 1);
        m_triangle_indices.push_back((i+1) * m_vertices.size() / m_curve.size() - 1);
        m_triangle_indices.push_back((i+2) * m_vertices.size() / m_curve.size() - 1);
        m_triangle_indices.push_back((i+1) * m_vertices.size() / m_curve.size());
    }
    m_vertices.push_back(glm::vec3(0.0, m_curve.at(0).y, 0.0));
    m_vertices.push_back(glm::vec3(0.0, m_curve.at(m_curve.size() - 1).y, 0.0));

    for (int k = 0; k <  (m_vertices.size() - 2) / m_curve.size() - 1; k++) {
        m_triangle_indices.push_back(k);
        m_triangle_indices.push_back(k + 1);
        m_triangle_indices.push_back(m_vertices.size()-2);
    }
    m_triangle_indices.push_back((m_vertices.size()-2) / m_curve.size() - 1);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(m_vertices.size()-2);
    for (int k = 0; k <  (m_vertices.size() - 2) / m_curve.size() - 1; k++) {
        m_triangle_indices.push_back(k + (m_vertices.size() - 2) - (m_vertices.size() - 2) / m_curve.size());
        m_triangle_indices.push_back(k + (m_vertices.size() - 2) - (m_vertices.size() - 2) / m_curve.size() + 1);
        m_triangle_indices.push_back(m_vertices.size()-1);
    }
    m_triangle_indices.push_back(m_vertices.size()-3);
    m_triangle_indices.push_back(m_vertices.size()-2 - (m_vertices.size() - 2) / m_curve.size());
    m_triangle_indices.push_back(m_vertices.size()-1);

//    for (int i = 0; i < 3; i++) {
//        std::vector<glm::vec3> temp (m_vertices.size() - 2);
//        temp.insert(temp.begin(), m_vertices.begin(), m_vertices.end() - 2);

//        for (int i = temp.size() - (temp.size() / 2) - 1; i >= 0; i--) {
//            temp.at(2 * i + 1) = temp.at(i);
//            temp.at(2 * i) =  temp.at(i);
//        }

//        for (int j = 0; j < temp.size() - 1; j++) {
//            temp.at(j) = ((temp.at(j) + temp.at(j + 1)) * 0.5f);
//        }
//        for (int j = 0; j < temp.size() - 1; j++) {
//            temp.at(j) = ((temp.at(j) + temp.at(j + 1)) * 0.5f);
//        }
//        if (m_vertices.at(0) == m_vertices.at(m_vertices.size() - 2)) {
//            m_vertices = temp;
//            m_vertices.pop_back();
//            m_vertices.at(m_vertices.size() - 3)  = temp.at(0);
//        } else {
//            m_vertices = temp;
//        }

//    }
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
