#pragma once

namespace Terrain {

	enum EnTerrainRelated
	{
		en_terrainOnUp,		//��ɗאځB
		en_terrainOnDown,	//���ɗאځB
		en_terrainOnLeft,	//���ɗאځB
		en_terrainOnRight,	//�E�ɗאځB
		en_terrainOnFront,	//�O�ɗאځB
		en_terrainOnBack,	//��ɗאځB
		en_terrainOnNum		//�אڂ���ʂ̐��B
	};

	struct TerrainVertex {
		Vector3 vertPos;	//���_���W�B
		int vertNo = 0;			//���_�ԍ��B
		TerrainVertex* nearVert[4] = { nullptr };	//�אڒ��_�̃A�h���X�B
	};

	//�n�`�I�u�W�F�N�g�B
	class Terrain :public DestructibleObject
	{
	public:
		Terrain() {}
		~Terrain()  override final {}

		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		void SetPosition(const Vector3& pos);

		/// <summary>
		/// ���_�̃f�[�^���\�z���Ă����B
		/// </summary>
		void BuildVertex();

	private:
		const Vector3 VERTEX_CONST[en_terrainOnNum] = {
			{0.0f,100.0f,0.0f},		//��B
			{0.0f,0.0f,0.0f},		//���B
			{-100.0f,50.0f,0.0f},		//���B
			{100.0f,50.0f,0.0f},		//�E�B
			{0.0f,50.0f,100.0f},		//�O�B
			{0.0f,50.0f,-100.0f}		//��B
		};

	private:
		TerrainVertex m_vertex[en_terrainOnNum];	//�n�`�̒��_�B
		int m_terrainId = -1;		//�n�`id�ԍ��B
		float m_scale = 1.0f;		//�X�P�[���B
	};

}
