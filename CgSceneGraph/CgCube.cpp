#include "CgCube.h"
#include "CgUtils/ObjLoader.h"
#include <iostream>
CgCube::CgCube()
{
    m_vertices.push_back(glm::vec3(1.0,-1.0,1.0)); // 0
    m_vertices.push_back(glm::vec3(1.0,-1.0,-1.0)); // 1
    m_vertices.push_back(glm::vec3(1.0,1.0,-1.0)); // 2
    m_vertices.push_back(glm::vec3(1.0,1.0,1.0)); // 3
    m_vertices.push_back(glm::vec3(-1.0,-1.0,1.0)); // 4
    m_vertices.push_back(glm::vec3(-1.0,-1.0,-1.0)); // 5
    m_vertices.push_back(glm::vec3(-1.0,1.0,-1.0)); // 6
    m_vertices.push_back(glm::vec3(-1.0,1.0,1.0)); // 7

//    m_vertices.push_back(glm::vec3(-0.5,0.0,-0.5));
//    m_vertices.push_back(glm::vec3(0.0,-0.5,-0.5));
//    m_vertices.push_back(glm::vec3(0.0,0.5,-0.5));
//    m_vertices.push_back(glm::vec3(0.5,0.0,-0.5));

//    m_vertices.push_back(glm::vec3(-0.5,0.0,0.5));
//    m_vertices.push_back(glm::vec3(0.0,-0.5,0.5));
//    m_vertices.push_back(glm::vec3(0.0,0.5,0.5));
//    m_vertices.push_back(glm::vec3(0.5,0.0,0.5));

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(3);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);

    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(6);


    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(7);

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);

    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(1);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);

//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(3);
//    m_triangle_indices.push_back(0);

//    m_triangle_indices.push_back(3);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(0);

//    m_triangle_indices.push_back(4);
//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(6);

//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(7);
//    m_triangle_indices.push_back(6);

//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(4);

//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(4);

//    m_triangle_indices.push_back(6);
//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(4);

//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(4);

//    m_triangle_indices.push_back(7);
//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(3);

//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(3);

//    m_triangle_indices.push_back(6);
//    m_triangle_indices.push_back(7);
//    m_triangle_indices.push_back(2);

//    m_triangle_indices.push_back(7);
//    m_triangle_indices.push_back(3);
//    m_triangle_indices.push_back(2);

    calculateNormals();
}
