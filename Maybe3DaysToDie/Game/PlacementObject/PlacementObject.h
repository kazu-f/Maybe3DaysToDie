#pragma once
#include "DestructibleObject/Block/Block.h"
#include "MiniEngine/physics/CollisionAttr.h"

class LoadingByChunk;
class SaveDataFile;
namespace nsTerrain {
	class TerrainManager;
}

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
	void PlaceObject();

	/// <summary>
	/// 設置するオブジェクトの情報
	/// </summary>
	/// <param name="params">パラメータ</param>
	void SetParams(const ObjectParams& params)
	{
		if (ObjID == params.BlockID)
		{
			//変更なし
			return;
		}
		objParam = params;
		if (SetModelParams())
		{
			m_ObjectModel->SetActiveFlag(true);
			m_ObjectModel->Init(m_modelInitData);
		}
		else
		{
			m_ObjectModel->SetActiveFlag(false);
		}
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
	/// <summary>
	/// 設置するオブジェクトの位置を計算
	/// </summary>
	void CalcObjectPos();

	/// <summary>
	/// モデルを現在の情報で初期化する
	/// </summary>
	bool SetModelParams();

private:
	prefab::ModelRender* m_ObjectModel = nullptr;		//オブジェクトモデル
	Vector3 m_pos = Vector3::Zero;		//モデルのポジション
	Vector3 m_scale = Vector3::One;		//モデルのスケール
	Quaternion m_qrot = Quaternion::Identity;		//モデルの回転
	std::vector<Block*> m_model;
	bool CanPlace = false;
	DestructibleObject* m_hitObj = nullptr;
	LoadingByChunk* m_LoadingChunk = nullptr;
	nsTerrain::TerrainManager* m_TerrainManager = nullptr;		//テラインマネージャー
	SaveDataFile* m_SaveData = nullptr;
	ObjectParams objParam;
	ModelInitData m_modelInitData;
	bool Enable = false;
	int ObjID = -1;
};

