#include "CgCube.h"
#include "CgUtils/ObjLoader.h"
#include <iostream>
CgCube::CgCube(int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    m_vertices.push_back(glm::vec3(1.0,-1.0,1.0)); // 0
    m_vertices.push_back(glm::vec3(1.0,-1.0,-1.0)); // 1
    m_vertices.push_back(glm::vec3(1.0,1.0,-1.0)); // 2
    m_vertices.push_back(glm::vec3(1.0,1.0,1.0)); // 3
    m_vertices.push_back(glm::vec3(-1.0,-1.0,1.0)); // 4
    m_vertices.push_back(glm::vec3(-1.0,-1.0,-1.0)); // 5
    m_vertices.push_back(glm::vec3(-1.0,1.0,-1.0)); // 6
    m_vertices.push_back(glm::vec3(-1.0,1.0,1.0)); // 7

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(3);
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);
    m_vertex_normals.push_back(glm::vec3(1.0,0.0,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);
    m_vertex_normals.push_back(glm::vec3(1.0,0.0,0.0));

    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(6);
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,-1.0));


    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,-1.0));

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(7);
    m_vertex_normals.push_back(glm::vec3(-1.0,0.0,0.0));

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);
    m_vertex_normals.push_back(glm::vec3(-1.0,0.0,0.0));

    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);
    m_vertex_normals.push_back(glm::vec3(0.0,1.0,0.0));

    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);
    m_vertex_normals.push_back(glm::vec3(0.0,1.0,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(1);
    m_vertex_normals.push_back(glm::vec3(0.0,-1.0,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_vertex_normals.push_back(glm::vec3(0.0,-1.0,0.0));
}

CgCube::~CgCube()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgCube::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgCube::init( std::string filename)
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

void CgCube::calculateFaceNormals() {
    for (int i = 0; i < m_vertex_normals.size(); i++) {
        glm::vec3 schwerpunkt = (m_vertices.at(m_triangle_indices.at(i*3)) +
                                 m_vertices.at(m_triangle_indices.at(i*3+1)) +
                                 m_vertices.at(m_triangle_indices.at(i*3+2))
                                 ) * (1/3.0f);
        m_face_normals.push_back(schwerpunkt);
        m_face_normals.push_back(schwerpunkt + m_vertex_normals.at(i));
    }
}

const std::vector<glm::vec3>& CgCube::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgCube::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgCube::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2>& CgCube:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgCube::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgCube::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgCube::getFaceColors() const
{
    return m_face_colors;
}
