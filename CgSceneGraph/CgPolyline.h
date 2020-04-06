#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include "CgBase/CgBasePolyline.h"

class CgPolyline : public CgBasePolyline
{
public:
    CgPolyline();
    CgPolyline(std::vector<glm::vec3> args_verticies, int id);

    ~CgPolyline();

    Cg::ObjectType getType() const;
    unsigned int getID() const;

    const std::vector<glm::vec3>& getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;

    void setColor(Cg::Color color, int value);

private:
    Cg::ObjectType m_type;
    unsigned int m_id;

    std::vector<glm::vec3> m_verticies;
    glm::vec3 m_color;
    unsigned int m_lineWidth;
};

inline Cg::ObjectType  CgPolyline::getType() const {return m_type;}
inline unsigned int CgPolyline::getID() const {return m_id;}

inline const std::vector<glm::vec3>& CgPolyline::getVertices() const {return m_verticies;}
inline glm::vec3 CgPolyline::getColor() const {return m_color;}
inline unsigned int CgPolyline::getLineWidth() const {return m_lineWidth;}

#endif // CGPOLYLINE_H
