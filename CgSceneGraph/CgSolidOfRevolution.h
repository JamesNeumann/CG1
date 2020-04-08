#ifndef CGSOLIDOFREVOLUTION_H
#define CGSOLIDOFREVOLUTION_H

#include "CgBase/CgBaseTriangleMesh.h"

class CgSolidOfRevolution : public CgBaseTriangleMesh
{
public:
    CgSolidOfRevolution();
    CgSolidOfRevolution(int id);

    ~CgSolidOfRevolution();

    Cg::ObjectType getType() const;
    unsigned int getID() const;

    void init (std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices);
    void init( std::string filename);

    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
};

inline Cg::ObjectType  CgExampleTriangle::getType() const {return m_type;}
inline unsigned int CgExampleTriangle::getID() const {return m_id;}

#endif // CGSOLIDOFREVOLUTION_H
