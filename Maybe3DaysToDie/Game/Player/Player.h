#pragma once
#include "Load/TerrainLoad/LoadingByChunk.h"

class PlayerHp;
class PlayerStamina;
class PlayerHunger;
class PlayerWater;
class GameCamera;
class Player : public IGameObject
{
	//�z��p�̒萔
	//�Ȃ�ƂȂ��}�W�b�N�i���o�[�����������̂Œ萔��
	enum Vector {
		X, Y, Z
	};
	//�v���C���[�����X�e�[�g�̎��
	enum State {
		Idle,			//�ҋ@
		Walk,			//����
		Run,			//����
		Jump,			//�W�����v
		Attack,			//�U��
		Inventry,		//�C���x���g�����J��
		Num				//�X�e�[�g��
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
	const Vector3 GetPosition() const {
		return m_Pos;
	}

	void SetCameraPtr(GameCamera* ptr)
	{
		cameraptr = ptr;
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
	State m_State = State::Idle;
	float m_DeltaTime = 0.0f;

	bool m_IsChasePlayer = false;
	GameCamera* cameraptr = nullptr;

	float m_mulSpeed = 1.0f;			//�X�s�[�h�Ɋ|����l

	CFontRender* m_Font = nullptr;
	LoadingByChunk* m_LoadingByChunk = nullptr;
};

