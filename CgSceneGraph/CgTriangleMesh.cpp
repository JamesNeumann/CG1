#include "CgTriangleMesh.h"
#include "CgUtils/IdGenerator.h"
#include "CgUtils/ObjLoader.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <iostream>

CgTriangleMesh::CgTriangleMesh() : m_type(Cg::TriangleMesh), m_id(IdGenerator::getId())
{

}
CgTriangleMesh::~CgTriangleMesh()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgTriangleMesh::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgTriangleMesh::init( std::string filename)
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

void CgTriangleMesh::calculateNormals() {
    m_vertex_normals.clear();
    m_face_normals.clear();
    m_vertex_normals.resize(m_vertices.size());
    for (int i = 0; i < m_triangle_indices.size(); i = i+3) {
        unsigned int first = m_triangle_indices.at(i);
        unsigned int secound = m_triangle_indices.at(i+1);
        unsigned int third = m_triangle_indices.at(i+2);

        glm::vec3 v1 = m_vertices.at(first);
        glm::vec3 v2 = m_vertices.at(secound);
        glm::vec3 v3 = m_vertices.at(third);
        glm::vec3 normal = calculateFaceNormal(v1, v2, v3);
        glm::vec3 schwerpunkt = calculateSchwerpunkt(v1, v2, v3);
        m_face_normals.push_back(normal);
        m_face_polylines.push_back(
                    new CgPolyline(std::vector<glm::vec3> {schwerpunkt, schwerpunkt + normal})
                    );
        m_vertex_normals.at(first) += normal;
        m_vertex_normals.at(secound) += normal;
        m_vertex_normals.at(third) += normal;
    }
    for (int i = 0; i < m_vertices.size(); i++) {
        m_vertex_normals.at(i) = glm::normalize(m_vertex_normals.at(i));
        std::cout << glm::to_string(m_vertex_normals.at(i)) << "    " << glm::to_string(m_vertices.at(i)) << std::endl;
        m_vertex_polylines.push_back(new CgPolyline(
                                         std::vector<glm::vec3> {m_vertices.at(i), m_vertices.at(i) + m_vertex_normals.at(i)}
                                         )
                                     );
    }
}

glm::vec3 CgTriangleMesh::calculateFaceNormal(glm::vec3 &vertex1, glm::vec3 &vertex2, glm::vec3 &vertex3) {
    return glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
}

glm::vec3 CgTriangleMesh::calculateSchwerpunkt(glm::vec3 &vertex1, glm::vec3 &vertex2, glm::vec3 &vertex3) {
    return (vertex1 + vertex2 + vertex3) * (1/3.0f);
}



const std::vector<CgPolyline*>& CgTriangleMesh::getFaceNormalPolylines() const {
    return m_face_polylines;
}
const std::vector<CgPolyline*>& CgTriangleMesh::getVertexNormalPolylines() const {
    return m_vertex_polylines;
}




const std::vector<glm::vec3>& CgTriangleMesh::getVertices() const
{
    return m_vertices;
}
const std::vector<glm::vec3>& CgTriangleMesh::getVertexNormals() const
{
    return m_vertex_normals;
}
const std::vector<glm::vec3>& CgTriangleMesh::getVertexColors() const
{
    return m_vertex_colors;
}
const std::vector<glm::vec2>& CgTriangleMesh:: getVertexTexCoords() const
{
    return m_tex_coords;
}
const std::vector<unsigned int>& CgTriangleMesh::getTriangleIndices() const
{
    return m_triangle_indices;
}
const std::vector<glm::vec3>& CgTriangleMesh::getFaceNormals() const
{
    return m_face_normals;
}
const std::vector<glm::vec3>& CgTriangleMesh::getFaceColors() const
{
    return m_face_colors;
}
