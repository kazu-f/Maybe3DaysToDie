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
class IPlayerState;
class Player : public IGameObject
{
public :
	Player(){}
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
	//�v���C���[�����X�e�[�g�̎��
	enum State {
		Idle,			//�ҋ@
		Walk,			//����
		Run,			//����
		Jump,			//�W�����v
		Attack,			//�U��
		Menu,			//���j���[��ʒ�
		//Damage,			//�U���ɓ�������
		Dead,			//���ɂ܂���
		Debug,			//�f�o�b�O���[�h
		Num				//�X�e�[�g��
	};
	const Vector3 GetPosition() const {
		return m_Pos;
	}

	void SetCameraPtr(GameCamera* ptr)
	{
		m_Camera = ptr;
	}

	/// <summary>
	/// �ړ����x��ύX����֐�
	/// �_�b�V���Ƃ��f�o�t�Ƃ��Ɏg��
	/// </summary>
	/// <param name="mulSp">���x�Ɋ|�������l</param>
	void SetMulSpeed(const float mulSp) {
		m_mulSpeed = mulSp;
	}

	void SetLoadingByChunk(LoadingByChunk* lbc)
	{
		m_LoadingByChunk = lbc;
	}

	void SetItemBar(ItemBar* itemBar) {
		m_ItemBar = itemBar;
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
	void OpenInventory();

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

	void ReStart();
private:
	/// <summary>
	/// ���Ԃɂ��X�e�[�^�X�̍X�V
	/// </summary>
	void PeriodicUpdate();

	/// <summary>
	/// IPlayerState��Update���Ă�
	/// </summary>
	void StateUpdate();

	/// <summary>
	/// IPlayerState���X�V
	/// </summary>
	void ChangeState();

	/// <summary>
	/// ���f���̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// ���f���̉�]����
	/// </summary>
	void Rotation();

	/// <summary>
	/// ���f�����X�V
	/// </summary>
	void ModelUpdate();

	/// <summary>
	/// �f�o�b�O���[�h��؂�ւ���֐�
	/// </summary>
	void SwichDebugMode();

	/// <summary>
	/// �f�o�b�O���[�h���𔻒肷��
	/// </summary>
	/// <returns>�f�o�b�O���[�h�Ȃ�true</returns>
	const bool IsDubug()const ;
private:
	////////////���f��/////////////////////////////////////////////
	//prefab::ModelRender* m_Model = nullptr;		//�v���C���[���f��
	Vector3 m_Pos = { 0.0f,500.0f,500.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector3 m_Scale = Vector3::One;
	CCharacterController m_Characon;
	///////////////////////////////////////////////////////////////

	/////�̗�//////////////////////////////////////////////////////
	PlayerHp* m_Hp = nullptr;
	///////////////////////////////////////////////////////////////

	/////�X�^�~�i/////////////////////////////////////////////////
	PlayerStamina* m_Stamina = nullptr;
	///////////////////////////////////////////////////////////////

	/////��//////////////////////////////////////////////////////
	PlayerHunger* m_Hunger = nullptr;
	///////////////////////////////////////////////////////////////

	/////����//////////////////////////////////////////////////////
	PlayerWater* m_Water = nullptr;
	///////////////////////////////////////////////////////////////

	/////�z�b�g�o�[//////////////////////////////////////////////
	ItemBar* m_ItemBar = nullptr;
	/// ////////////////////////////////////////////////////////
	State m_CurrentState = State::Idle;				//���݂̃X�e�[�g
	State m_NextState = State::Idle;				//���ɕς��X�e�[�g
	float m_DeltaTime = 0.0f;

	GameCamera* m_Camera = nullptr;
	bool IsJump = false;
	bool IsJumping = false;
	float NowTime = 0.0f;
	float m_mulSpeed = 1.0f;			//�ړ����x(�o�t�A�f�o�t�p�j

	LoadingByChunk* m_LoadingByChunk = nullptr; 

	bool m_IsUseItem = true;
	AccessObject* m_AccessObject = nullptr;

	IPlayerState* PlayerState = nullptr;
	PlayerDead m_Dead;
};

