#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <tuple>

#define DEFAULT_RGBA 0.0f
typedef std::vector<myTriangle> MESH;
typedef std::tuple<float, float, float, float> RGBA;

struct myVertex
{
	float v_x;
	float v_y;
	float v_z;

	RGBA myColors = std::make_tuple(DEFAULT_RGBA, DEFAULT_RGBA, DEFAULT_RGBA, 1.0f);

	explicit myVertex(float v_x, float v_y, float v_z) : v_x(v_x), v_y(v_y), v_z(v_z){};
	~myVertex() {};
};
class myTriangle
{
private:
	myVertex m_vertices[3];
public:
	explicit myTriangle(const myVertex& verx, const myVertex& very, const myVertex& verz) : m_vertices{ verx, very, verz } {};
};
class myMesh
{
	private:
		MESH m_triangles;

	public:

		myMesh(){};
		~myMesh(){};

		void translate(float x, float y, float z)
		{
			for (auto& triangle : m_triangles)
			{
				for (int i = 0; i < 3; ++i)
				{
					triangle.m_vertices[i].v_x += x;
					triangle.m_vertices[i].v_y += y;
					triangle.m_vertices[i].v_z += z;
				}
			}
		}
		void rotate(float rotation)
		{
			float cosine_rotation = cos(rotation);
			float sine_rotation = sin(rotation);

			for (auto& triangle : m_triangles)
			{
				for (int i = 0; i < 3; ++i)
				{
					float x = triangle.m_vertices[i].v_x;
					float y = triangle.m_vertices[i].v_y;
					triangle.m_vertices[i].v_x = (x * cosine_rotation) - (y * sine_rotation);
					triangle.m_vertices[i].v_y = (x * cosine_rotation) + (y * sine_rotation);
				}
			}
		}
};


#endif