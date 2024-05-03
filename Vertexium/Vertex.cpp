#include "Vertex.hpp"


void myVertex::translate(float x, float y, float z)
{
    v_x += x;
    v_y += y;
    v_z += z;
}
void myTriangle::translate(float x, float y, float z)
{
    for (int i = 0; i < 3; i++)
    {
        m_vertices[i].translate(x, y, z);
    }
}
void myMesh::addTriangle(myTriangle _triangle)
{
    if (m_triangles == nullptr)
        m_triangles = new MESH; 

    m_triangles->push_back(_triangle);
}
void myMesh::translate(float x, float y, float z)
{
    if (m_triangles == nullptr || sizeof(m_triangles) < 1)
        return;

    for (auto& triangle : *m_triangles)
    {
        triangle.translate(x, y, z);
    }
}