#pragma once

namespace nsTerrain {

	static const int NEAR_VERT_COUNT = 4;

	//地形オブジェクト。
	class Terrain :public DestructibleObject
	{
	public:
		Terrain();
		~Terrain()  override final;

		/// <summary>
		/// 座標を設定。
		/// </summary>
		void SetPosition(const Vector3& pos);

	private:


	private:
		int m_terrainId = -1;		//地形id番号。
		float m_scale = 1.0f;		//スケール。
	};

}
