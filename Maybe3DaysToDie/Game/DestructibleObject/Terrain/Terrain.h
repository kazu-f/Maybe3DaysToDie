#pragma once

struct ToolInfo;
namespace nsTerrain {
	class TerrainChunkData;

	static const int NEAR_CHUNK_MAXCOUNT = 4;


	//地形オブジェクト。
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;
		/// <summary>
		/// ワールドをセット。
		/// </summary>
		void AddTerrainChunk(TerrainChunkData* world);

		/// <summary>
		/// コライダーの登録を解除するかどうかを計算。
		/// </summary>
		bool IsTerrainEnabled()
		{
			return (m_voxel > 0.0f);
		}

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
			m_params = params;
		}

	private:
		void CalcVoxel();

	private:


	private:
		TerrainChunkData* m_chunkData[NEAR_CHUNK_MAXCOUNT] = { nullptr };		//チャンク情報。
		char m_terrainChunkDataSize = 0;											//チャンク情報の保持数。

		int m_terrainId = -1;		//地形id番号。
		float m_voxel = 1.0f;		//ボクセル値。

		//bool m_registColider = false;
	};

}
