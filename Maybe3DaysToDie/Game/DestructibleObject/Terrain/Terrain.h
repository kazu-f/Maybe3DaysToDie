#pragma once

namespace nsTerrain {

	static const int NEAR_VERT_COUNT = 4;

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

	private:


	private:
		int m_terrainId = -1;		//�n�`id�ԍ��B
		float m_scale = 1.0f;		//�X�P�[���B
	};

}
