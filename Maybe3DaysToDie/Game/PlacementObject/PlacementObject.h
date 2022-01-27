#pragma once
#include "DestructibleObject/Block/Block.h"
#include "MiniEngine/physics/CollisionAttr.h"

class LoadingByChunk;
class SaveDataFile;
//todo プレイヤー側から呼ぶようになったらIGameObjectを継承しないように
class PlacementObject:public IGameObject
{
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
	DestructibleObject* m_hitObj = nullptr;
	LoadingByChunk* m_LoadingChunk = nullptr;
	SaveDataFile* m_SaveData = nullptr;
};

