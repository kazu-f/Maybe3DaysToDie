#pragma once

class PlacementObject;
class DestroyObject;
class LoadingByChunk;
class Stage;
class Tool;
class SaveDataFile;
class TerrainSave;
class TerrainLoad;
class Stage;
class Player;
class Mause;

namespace {
	const int SelectNum = 8;	//�A�C�e���o�[�̐�
}
class ItemBar : public IGameObject
{
public:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	float GetItemSize()const {
		return ItemOneBoxSize;
	}
	void SetWorldData(
		PlacementObject* Po,
		DestroyObject* Do,
		SaveDataFile* Sf,
		Tool* T,
		LoadingByChunk* Lc,
		TerrainSave* Ts,
		TerrainLoad* Tl,
		Stage* s) {
		m_PlacementObject = Po;
		m_DestroyObject = Do;
		m_SaveDataFile = Sf;
		m_Tool = T;
		m_LoadingByChunk = Lc;
		m_TerrainSave = Ts;
		m_TerrainLoad = Tl;
		m_Stage = s;
	}

	void SetPlayer(Player* pl) {
		m_Player = pl;
	}
private:
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
	void ItemSlotKey(int vKey,int slot);
private:
	prefab::CSpriteRender* m_ItemIcon = nullptr;
	prefab::CSpriteRender* m_SelectItemIcon = nullptr;
	const float ItemOneBoxSize = 75.0f;			//�A�C�e���P�̃T�C�Y
	Vector2 m_SelectPos[SelectNum] = {};	//�I�𒆂̃A�C�e���o�[�̈ʒu
	int m_SelectNum = 0;						//���I�����Ă���A�C�e���o�[�̃X���b�gNo
	PlacementObject* m_PlacementObject = nullptr;
	DestroyObject* m_DestroyObject = nullptr;
	SaveDataFile* m_SaveDataFile = nullptr;
	Tool* m_Tool = nullptr;
	LoadingByChunk* m_LoadingByChunk = nullptr;
	TerrainSave* m_TerrainSave = nullptr;		//�n�`�Z�[�u�p�̃N���X
	TerrainLoad* m_TerrainLoad = nullptr;
	Stage* m_Stage = nullptr;
	Player* m_Player=nullptr;

	float m_InstallTime = 0.0f;		//�ݒu�ł��鎞��
	float m_DeleteTime = 0.0f;
};

