#pragma once

struct ToolInfo;
namespace nsTerrain {
	class TerrainWorld;

	static const int NEAR_VERT_COUNT = 4;


	//地形オブジェクト。
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;
		/// <summary>
		/// ワールドをセット。
		/// </summary>
		void SetTerrainWorld(TerrainWorld* world)
		{
			m_world = world;
		}
		/// <summary>
		/// コライダーの初期化。
		/// </summary>
		void InitRayCollider();
		/// <summary>
		/// コライダーの登録、解除。
		/// </summary>
		void SetColliderEnable(bool flag);

		/// <summary>
		/// コライダーの登録を解除するかどうかを計算。
		/// </summary>
		void CalcColliderEnable();


		/// <summary>
		/// 地形のスケールをセット。
		/// </summary>
		/// <param name="scale"></param>
		void SetVoxel(float scale)
		{
			m_voxel = scale;
		}
		/// <summary>
		/// ボクセル値を取得。
		/// </summary>
		float GetVoxel()
		{
			return m_voxel;
		}
		/// <summary>
		/// ダメージを与える。
		/// </summary>
		void Damage(const ToolInfo& tool)override final;

		/// <summary>
	/// ブロックを追加
	/// </summary>
	/// <param name="params">パラメータ</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
		void AddBlock(ObjectParams& params, Vector3& pos, Quaternion& rot, Vector3& scale)override final
		{

		}

	private:
		void CalcVoxel();

	private:


	private:
		TerrainWorld* m_world = nullptr;		//地形ワールド。
		
		int m_terrainId = -1;		//地形id番号。
		float m_voxel = 1.0f;		//ボクセル値。

		bool m_registColider = false;
	};

}
