#include "CgSolidOfRevolution.h"
#include "CgExampleTriangle.h"
#include "CgUtils/ObjLoader.h"

CgSolidOfRevolution::CgSolidOfRevolution(int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{

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
