#pragma once
#include "Load/TerrainLoad/LoadingByChunk.h"

class PlayerHp;
class PlayerStamina;
class PlayerHunger;
class PlayerWater;
class GameCamera;
class ItemBar;
class AccessObject;
#include "state/PlayerDead.h"
#include "state/PlayerIdle.h"
#include "state/PlayerWalk.h"
#include "state/PlayerMenu.h"
class IPlayerState;
class IEnemy;
class Inventory;
class Stage;
class PlacementObject;
class DestroyObject;
class Tool;
class SaveDataFile;
class Player : public IGameObject
{
public :
	//�v���C���[�����X�e�[�g�̎��
	enum State {
		Idle,			//�ҋ@
		Walk,			//����
		Attack,			//�U��
		Menu,			//���j���[��ʒ�
		//Damage,			//�U���ɓ�������
		Dead,			//���ɂ܂���
		Num				//�X�e�[�g��
	};
	/// <summary>
	/// �R���X�g���N�^
	/// �X�e�[�g�p�^�[���Ŏg�p����ϐ��̃R���X�g���N�^�ׂ̈ɂ���
	/// </summary>
	Player():
		m_Dead(this),
		m_Idle(this),
		m_Walk(this),
		m_Menu(this)
	{}
private:
	//�z��p�̒萔
	//�Ȃ�ƂȂ��}�W�b�N�i���o�[�����������̂Œ萔��
	enum Vector {
		X, Y, Z
	};

private:
	/// <summary>
	/// GameObject�ɐς܂��ƈ�x�����Ă΂�鏉�����֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start()override final;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override final;

	/// <summary>
	/// delete�����ƌĂ΂��֐�
	/// </summary>
	void OnDestroy()override final;

public:
	/// <summary>
	/// �v���C���[�̈ʒu���擾
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition() const {
		return m_Pos;
	}

	/// <summary>
	/// �J�����̃|�C���^��ݒ肷��
	/// </summary>
	/// <param name="ptr">�J�����̃|�C���^</param>
	void SetCameraPtr(GameCamera* ptr)
	{
		m_Camera = ptr;
	}

	/// <summary>
	/// �ړ����x��ύX����֐�
	/// �_�b�V���Ƃ��f�o�t�Ƃ��Ɏg��
	/// </summary>
	/// <param name="mulSp">���x�Ɋ|�������l</param>
	void SetMulSpeed(const float mulSp);

	void SetLoadingByChunk(LoadingByChunk* lbc)
	{
		m_LoadingByChunk = lbc;
	}

	/// <summary>
	/// �v���C���[���U������������ۂɓ���֐��B
	/// �v���C���[�ւ̓����蔻��͂��ĂȂ��ł��B
	/// </summary>
	/// <param name="Damage">�_���[�W��</param>
	void HitDamage(const float Damage);

	/// <summary>
	/// �C���x���g����\������
	/// </summary>
	bool OpenInventory();

	/// <summary>
	/// �C���x���g�������
	/// </summary>
	void CloseInventory();

	/// <summary>
	/// ���݂̃X�e�[�g���擾
	/// </summary>
	/// <returns>���݂̃X�e�[�g</returns>
	State GetState() const {
		return m_CurrentState;
	}

	void SetAccessObject(AccessObject* AOp) {
		m_AccessObject = AOp;
	}

	/// <summary>
	/// ���񂾎��ɌĂ΂��֐�
	///	�X�e�[�^�X�����݂̍ő�l�ɐݒ肵�Ȃ���
	/// </summary>
	void ReStart();

	/// <summary>
	/// �f�o�b�O���[�h���𔻒肷��
	/// </summary>
	/// <returns>�f�o�b�O���[�h�Ȃ�true</returns>
	const bool IsDubug()const;

	/// <summary>
	/// �v���C���[�������֐�
	/// </summary>
	/// <param name="move">�ړ���</param>
	void CharaMove(Vector3& move) {
		m_Pos = m_Characon.Execute(move);
	}

	/// <summary>
	/// �X�e�[�g��ύX����Ƃ��ɌĂԊ֐�
	/// </summary>
	/// <param name="nextState">���̃X�e�[�g</param>
	void ChengeState(State nextState) {
		m_NextState = nextState;
	}

	/// <summary>
	/// ���݂̃X�e�[�g���擾
	/// </summary>
	/// <returns>���݂̃X�e�[�g</returns>
	State GetCurrentState() const {
		return m_CurrentState;
	}

	/// <summary>
	/// �v���C���[���X�^�~�i���g���Ƃ��ɌĂԊ֐�
	/// </summary>
	/// <param name="usenum">�g�p�����</param>
	bool UseStamina(int useCost);

	/// <summary>
	/// ���_�𓮂������ǂ��������߂�֐�
	/// </summary>
	/// <param name="isMove">�������Ȃ�false</param>
	void SetMoveMause(bool isMove);

	/// <summary>
	/// �f�o�b�O���[�h���ǂ������擾����֐�
	/// </summary>
	/// <returns></returns>
	bool IsDebugMode()const {
		return m_IsDebugMode;
	}

	/// <summary>
	/// �f�o�b�O���[�h��ݒ肷��֐�
	/// </summary>
	/// <param name="mode"></param>
	void SetDebugMode(bool mode) {
		m_IsDebugMode = mode;
	}

	/// <summary>
	/// �d�͏���
	/// </summary>
	void Jump();

	/// <summary>
	/// Hp�̃|�C���^���擾
	/// </summary>
	/// <returns>Hp�|�C���^</returns>
	PlayerHp* GetHp() const {
		return m_Hp;
	}

	/// <summary>
	/// �X�^�~�i�̃|�C���^���擾
	/// </summary>
	/// <returns>�X�^�~�i�|�C���^</returns>
	PlayerStamina* GetStamina() const {
		return m_Stamina;
	}

	/// <summary>
	/// �󕠓x�̃|�C���^���擾
	/// </summary>
	/// <returns>�󕠓x�̂ۂ���</returns>
	PlayerHunger* GetHunger()const {
		return m_Hunger;
	}

	/// <summary>
	/// �����̃|�C���^���擾
	/// </summary>
	/// <returns>�����̃|�C���^</returns>
	PlayerWater* GetWater()const {
		return m_Water;
	}

	Inventory* GetInventory() {
		return m_Inventory;
	}

	void ItemDetaInit(
		SaveDataFile* Sf,
		Stage* s);
private:
	/// <summary>
	/// ���Ԃɂ��X�e�[�^�X�̍X�V
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// IPlayerState���X�V
	/// </summary>
	void ChangeState();

private:
	////////////���f��/////////////////////////////////////////////
	Vector3 m_Pos = { 500.0f,500.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	CCharacterController m_Characon;
	///////////////////////////////////////////////////////////////

	/////�X�e�[�^�X//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	PlayerStamina* m_Stamina = nullptr;
	PlayerHunger* m_Hunger = nullptr;
	PlayerWater* m_Water = nullptr;
	///////////////////////////////////////////////////////////////

	/////UI//////////////////////////////////////////////
	ItemBar* m_ItemBar = nullptr;
	Inventory* m_Inventory = nullptr;
	/// ////////////////////////////////////////////////////////
	float m_DeltaTime = 0.0f;

	GameCamera* m_Camera = nullptr;			//�J�����̃|�C���^
	bool IsJump = false;
	bool IsJumping = false;

	float NowTime = 0.0f;
	LoadingByChunk* m_LoadingByChunk = nullptr; 

	bool m_IsUseItem = true;
	AccessObject* m_AccessObject = nullptr;

	/////�X�e�[�g//////////////////////////////////
	State m_CurrentState = State::Num;				//���݂̃X�e�[�g
	State m_NextState = State::Num;				//���ɕς��X�e�[�g
	IPlayerState* m_PlayerState = nullptr;
	PlayerIdle m_Idle;
	PlayerDead m_Dead;
	PlayerWalk m_Walk;
	PlayerMenu m_Menu;
	////////////////////////////////////////////////

	Vector3 m_RespownPoint = { 100.0f,100.0f,100.0f };
	IEnemy* m_Enemy = nullptr;

	bool m_IsDebugMode = false;
	float m_Gravity = 0.0f;

	//todo ��قǃv���C���[���ɂ����Ă�������
	PlacementObject* m_PlacementObject = nullptr;		//�ݒu�I�u�W�F�N�g
	DestroyObject* m_DestroyObject = nullptr;		//�I�u�W�F�N�g�j��
	Tool* tool = nullptr;

	SaveDataFile* m_SaveData;
	Stage* m_Stage;
};

