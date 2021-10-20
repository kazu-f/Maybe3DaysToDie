#pragma once
class TerrainWorld : public IGameObject
{
public:

private:
	static const int width = 32;
	static const int height = 8;
	float terrainSurface = 0.5f;

	float terrainMap[width][height][width];
	CNoise m_perlinNoise;
	std::vector<Vector3> m_vertices;
	std::vector<int> m_triangles;


};

