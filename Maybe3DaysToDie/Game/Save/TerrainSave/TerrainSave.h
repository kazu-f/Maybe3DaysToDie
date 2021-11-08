#pragma once
class TerrainSave
{
public:
	TerrainSave() {}
	~TerrainSave() {}

private:
	int TerrainDurable[ChunkWidth][ChunkHeight][ChunkWidth] = { 0 };
};