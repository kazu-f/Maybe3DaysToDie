#pragma once
#include "DestructibleObject/Block/Block.h"
#include "MiniEngine/physics/CollisionAttr.h"

class BlockManager;
class LoadingByChunk;
class SaveDataFile;
//todo プレイヤー側から呼ぶようになったらIGameObjectを継承しないように
class PlacementObject:public IGameObject
{
private:
	struct RayResult :public btCollisionWorld::RayResultCallback
	{
		bool isHit = false;		//衝突フラグ
		Vector3 hitNormal = Vector3::Zero;
		Vector3 hitColPos = Vector3::Zero;
		const btCollisionObject* ColObj = nullptr;
		//衝突したときに呼ばれる関数
		virtual btScalar addSingleResult(
			btCollisionWorld::LocalRayResult& convexResult,
			bool /*normalInWorldSpace*/
		)
		{
			if (convexResult.m_collisionObject->getUserIndex() & ColliderUserIndex::enCollisionAttr_RayBlock)
			{
				btVector3 colPos = convexResult.m_collisionObject->getWorldTransform().getOrigin();
				isHit = true;
				hitNormal.Set(convexResult.m_hitNormalLocal);
				hitColPos.Set(colPos);
				//距離が近いほうに更新
				if (m_closestHitFraction > convexResult.m_hitFraction)
				{
					m_closestHitFraction = convexResult.m_hitFraction;
				}
				ColObj = convexResult.m_collisionObject;
				return m_closestHitFraction;
			}
			return 0.0f;
		}
	};
public:
	PlacementObject();
	~PlacementObject();

	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

	/// <summary>
	/// オブジェクトを設置
	/// </summary>
	void PlaceObject(ObjectParams& params);

	/// <summary>
	/// 設置するオブジェクトの位置を計算
	/// </summary>
	void CalcObjectPos();

	/// <summary>
	/// ブロックマネージャーをセット
	/// </summary>
	void SetBlockManager(BlockManager*manager)
	{
		m_BlockManager = manager;
	}

	/// <summary>
	/// チャンク読み込み処理をセット
	/// </summary>
	void SetLoadingChunk(LoadingByChunk* lbc)
	{
		m_LoadingChunk = lbc;
	}

	/// <summary>
	/// セーブデータファイルをセット
	/// </summary>
	void SetSaveData(SaveDataFile* sdf)
	{
		m_SaveData = sdf;
	}

private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//オブジェクトモデル
	Vector3 m_pos = Vector3::Zero;		//モデルのポジション
	Vector3 m_scale = Vector3::One;		//モデルのスケール
	Quaternion m_qrot = Quaternion::Identity;		//モデルの回転
	std::vector<Block*> m_model;
	bool CanPlace = false;
	BlockManager* m_BlockManager = nullptr;
	DestructibleObject* m_hitObj = nullptr;
	LoadingByChunk* m_LoadingChunk = nullptr;
	SaveDataFile* m_SaveData = nullptr;
};

