#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <tuple>

#pragma warning(disable: 26495)

#define DEFAULT_RGBA 0.0f
typedef std::tuple<float, float, float, float> RGBA;

struct myVertex;
class myTriangle;
class myMesh;

struct myVertex
{
    float v_x;
    float v_y;
    float v_z;

    RGBA myColors = std::make_tuple(DEFAULT_RGBA, DEFAULT_RGBA, DEFAULT_RGBA, 1.0f);

    explicit myVertex(float _v_x, float _v_y, float _v_z) : v_x(_v_x), v_y(_v_y), v_z(_v_z) {}
    myVertex() {}
    ~myVertex() {}

    void translate(float x, float y, float z);
    friend class myTriangle;
};
class myTriangle
{
private:
    myVertex m_vertices[3];
public:
    explicit myTriangle(const myVertex& verx, const myVertex& very, const myVertex& verz) : m_vertices{ verx, very, verz } {}

    void translate(float x, float y, float z);
    friend struct myVertex;
};
class myMesh
{
private:
    wchar_t m_name[100] = L"none";
    typedef std::vector<myTriangle> MESH;
    MESH* m_triangles = nullptr;
    bool m_empty = false;

public:
    myMesh(wchar_t name[100])
    {
        wcsncpy_s(m_name, name, 100);
        m_empty = true;
    }

    myMesh() {}

    ~myMesh() {}

    void addTriangle(myTriangle _triangle);
    void translate(float x, float y, float z);
    void rotate(float rotation);

    friend class myTriangle;
};

#endif