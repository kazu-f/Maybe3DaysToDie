#pragma once

namespace nsTerrain {

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

	static const int NEAR_VERT_COUNT = 4;

	struct TerrainVertex {
		Vector3 vertPos;	//���_���W�B
		int vertNo = 0;			//���_�ԍ��B
		TerrainVertex* nearVert[NEAR_VERT_COUNT] = { nullptr };	//�אڒ��_�̃A�h���X�B
	};


	//�n�`�I�u�W�F�N�g�B
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;

		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		void SetPosition(const Vector3& pos);

		/// <summary>
		/// ���_�̃f�[�^���\�z���Ă����B
		/// </summary>
		void BuildVertex();
		/// <summary>
		/// ���_�ڑ��B
		/// </summary>
		void ConnectVertex();
		/// <summary>
		/// �אڒn�`��ݒ�B
		/// </summary>
		/// <param name="terrain">�אڒn�`�B</param>
		/// <param name="enRelated">�ǂ̈ʒu���B</param>
		void SetRelatedTerrain(Terrain* terrain,EnTerrainRelated enRelated);

		//���_���擾����B
		TerrainVertex& GetVertex(int index)
		{
			return m_vertex[index];
		}

	private:
		static int GetIndexFromVertexRelated(EnTerrainRelated fromSide, EnTerrainRelated relatedSide);
		static const Vector3 VERTEX_CONST[en_terrainOnNum];
		static const EnTerrainRelated CONECT_VERTEX_LIST[en_terrainOnNum][NEAR_VERT_COUNT];

	private:
		Terrain* m_relatedTerrain[en_terrainOnNum] = { nullptr };	//�אڒn�`�B
		TerrainVertex m_vertex[en_terrainOnNum];	//�n�`�̒��_�B
		int m_terrainId = -1;		//�n�`id�ԍ��B
		float m_scale = 1.0f;		//�X�P�[���B
	};

}
