#pragma once

namespace nsTerrain {
	class TerrainWorld;

	static const int NEAR_VERT_COUNT = 4;


	//�n�`�I�u�W�F�N�g�B
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;
		/// <summary>
		/// ���[���h���Z�b�g�B
		/// </summary>
		void SetTerrainWorld(TerrainWorld* world)
		{
			m_world = world;
		}
		/// <summary>
		/// �R���C�_�[�̏������B
		/// </summary>
		void InitRayCollider();
		/// <summary>
		/// �R���C�_�[�̓o�^�A�����B
		/// </summary>
		void SetColliderEnable(bool flag);

		/// <summary>
		/// �R���C�_�[�̓o�^���������邩�ǂ������v�Z�B
		/// </summary>
		void CalcColliderEnable();

		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// �n�`�̃X�P�[�����Z�b�g�B
		/// </summary>
		/// <param name="scale"></param>
		void SetVoxel(float scale)
		{
			m_voxel = scale;
		}
		/// <summary>
		/// �{�N�Z���l���擾�B
		/// </summary>
		float GetVoxel()
		{
			return m_voxel;
		}
		/// <summary>
		/// �_���[�W��^����B
		/// </summary>
		void Damage(int damage)
		{
			int durable = max(0, (m_params.Durable - damage));
			if (durable != m_params.Durable)
			{
				m_params.Durable = durable;
				CalcVoxel();
			}
		}
	private:
		void CalcVoxel();

	private:


	private:
		TerrainWorld* m_world = nullptr;		//�n�`���[���h�B
		
		int m_terrainId = -1;		//�n�`id�ԍ��B
		float m_voxel = 1.0f;		//�{�N�Z���l�B

		bool m_registColider = false;
	};

}
