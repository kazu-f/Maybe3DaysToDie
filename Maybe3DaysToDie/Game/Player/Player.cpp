#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"
#include "GameCamera.h"
#include "AccessObject/AccessObject.h"
#include "Player/State/PlayerDead.h"
#include "Player/State/IPlayerState.h"

namespace {
	const float MoveDistance = 1000.0f;			//1フレームに動く距離
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
	const float NeckLimitY = 10.0f;				//上や下を向ける限界
}

bool Player::Start()
{
	//Hpを作る
	m_Hp = NewGO<PlayerHp>(0, "playerHp");

	//スタミナを作る
	m_Stamina = NewGO<PlayerStamina>(0, "playerStamina");

	//空腹度を作る
	m_Hunger = NewGO<PlayerHunger>(0, "playerHunger");
	m_Hunger->SetPlayer(this);

	//水分を作る
	m_Water = NewGO<PlayerWater>(0, "playerWater");
	m_Water->SetPlayer(this);

	ModelInitData PlayerModel;
	PlayerModel.m_tkmFilePath = "Assets/modelData/Player.tkm";

	AnimClipInitData AnInitData[State::Num];
	AnInitData[State::Idle].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Idle].isLoop = true;
	AnInitData[State::Walk].tkaFilePath = "Assets/animData/PlayerWalk.tka";
	AnInitData[State::Walk].isLoop = true;
	AnInitData[State::Attack].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Jump].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Run].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	//m_Model = NewGO<prefab::ModelRender>(0);
	//m_Model->Init(PlayerModel, AnInitData,State::Num);
	//m_Model->SetPosition(m_Pos);
	//m_Model->SetRotation(m_Rot);
	//m_Model->SetScale(m_Scale);
	m_Characon.Init(50.0f, 90.0f, m_Pos);

	return true;
}

void Player::Update()
{
	//ステートを更新
	StateUpdate();

	switch (m_CurrentState)
	{
	case State::Menu:
		m_Camera->SetMovingMouse(true);
		break;
	case State::Dead:
		PlayerState = &m_Dead;
		PlayerState->Enter();
		m_Camera->SetMovingMouse(true);
		break;
	case State::Run:
		m_mulSpeed = 1.0f;
		//移動処理
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	case Debug:
		m_mulSpeed = 2.0f;
		//移動処理
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	default:
		//移動処理
		Move();
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	}
	if (PlayerState != nullptr) {
	PlayerState->Update();

	}
	if (GetAsyncKeyState('e')) {
		m_AccessObject->Access();
	}
	if (GetAsyncKeyState('r')) {
		m_AccessObject->EndAccess();
	}
	//時間経過による回復
	PeriodicUpdate();
	//カメラにポジションを渡す
	m_Camera->SetPosition(m_Pos);
	//モデル情報を更新
	ModelUpdate();

	m_LoadingByChunk->SetPlayerPos(m_Pos);
}

void Player::OnDestroy()
{
	//モデルを削除
	//DeleteGO(m_Model);
	//Hpを削除
	DeleteGO(m_Hp);
	//スタミナを削除
	DeleteGO(m_Stamina);
}

void Player::ReStart()
{
	m_Pos = Vector3::Zero;
	m_Hp->Reset();
	m_Stamina->Reset();
	m_Hunger->Reset();
	m_Water->Reset();
}

void Player::PeriodicUpdate()
{
	//ステータス減少時間を数える
	m_DeltaTime += GameTime().GetFrameDeltaTime();
}

void Player::StateUpdate()
{
	ChangeState();
}

void Player::ChangeState()
{
	m_CurrentState = m_NextState;
}

void Player::Move()
{
	Vector3 Forward = MainCamera().GetForward();
	Forward.y = 0.0f;

	Vector3 MoveSpeed = Vector3::Zero;
	//Wキーが押されたら
	if (GetAsyncKeyState('W')) {
		if (IsDubug()) {
			MoveSpeed += MainCamera().GetForward();
		}
		else {
			MoveSpeed += Forward;
		}
	}
	//Sキーが押されたら
	if (GetAsyncKeyState('S')) {
		if (IsDubug()) {
			MoveSpeed -= MainCamera().GetForward();
		}
		else {
			MoveSpeed -= Forward;
		}
	}

	Vector3 RightMoveSpeed= MainCamera().GetRight();
	RightMoveSpeed.y = 0.0f;
	//Aキーが押されたら
	if (GetAsyncKeyState('A')) {
		if (IsDubug()) {
			MoveSpeed -= MainCamera().GetRight();
		}
		else {
			MoveSpeed -= RightMoveSpeed;
		}
	}
	//Dキーが押されたら
	if (GetAsyncKeyState('D')) {
		if (IsDubug()) {
			MoveSpeed += MainCamera().GetRight();
		}
		else {
			MoveSpeed += RightMoveSpeed;
		}
	}
	
	//////移動速度//////////////////////////
	{
		m_mulSpeed = 0.5f;
		///ダッシュ機能////////////////////////
		if (GetAsyncKeyState(VK_LSHIFT) &&
			MoveSpeed.Length() > 0.5f &&
			m_Stamina->IsUseStamina(1))
		{
			m_NextState = State::Run;
		}
	}
	///////////////////////////////////////////////
	
	/////重力処理////////////////////////
	{
		static float gravity = 0.0f;
		gravity -= GameTime().GetFrameDeltaTime();
		if (IsDubug()) {
			gravity = 0.0f;
		}

		/////////ジャンプ処理/////////////////////////////////////////////
		{
			if (GetAsyncKeyState(VK_SPACE)) {
				//地面に設置しているときだけ
				//ジャンプする
				if (m_Characon.IsOnGround())
				{
					IsJump = true;
				}
				//神視点の時はジャンプし続ける
				if (IsDubug()) {
					IsJump = false;
					MoveSpeed.y += 1.0f;
				}
				//if (m_IsChasePlayer) {
				//	if (m_Characon.IsOnGround()) {
				//		MoveSpeed.y = 10.0f;
				//	}
				//}
				//else {
				//	MoveSpeed.y = 10.0f;
				//}
			}
		}
		if (IsJump)
		{
			NowTime += GameTime().GetFrameDeltaTime();
			const float JumpTime = 0.3f;
			float f = NowTime - JumpTime;
			const float JumpPower = 0.8f;
			MoveSpeed.y = ((gravity)*pow(f, 2.0f)) + JumpPower;
			if (IsJumping && m_Characon.IsOnGround())
			{
				//ジャンプ中に地面についたのでジャンプ終了
				IsJump = false;
				IsJumping = false;
				NowTime = 0.0f;
				MoveSpeed.y = 0.0f;
			}
			else
			{
				IsJumping = true;
			}
		}

		/////////////////////
		if (m_Characon.IsOnGround()) {
			gravity = 0.0f;
		}
		MoveSpeed.y += gravity;
	}
	////////////////////////////////////////


	MoveSpeed *= MoveDistance * m_mulSpeed;
	m_Pos = m_Characon.Execute(MoveSpeed);

	//m_Model->SetPosition(Vector3::Zero);
}

void Player::Rotation()
{
}

void Player::ModelUpdate()
{
	//回転
	Rotation();
	//m_Model->PlayAnimation(State::Idle,GameTime().GetFrameDeltaTime());
}

void Player::SwichDebugMode()
{
	static bool IsPush = false;
	if (GetAsyncKeyState('G')) {
		if (!IsPush) {
			static State BuckUpState=State::Idle;
			if (m_CurrentState == State::Debug) {
				m_NextState = BuckUpState;
			}
			else {
				m_NextState = State::Debug;
				BuckUpState = m_CurrentState;
			}
		}
		IsPush = true;
	}
	else {
		IsPush = false;
	}
}

const bool Player::IsDubug() const
{
	if (m_CurrentState == State::Debug) {
		return true;
	}
	return false;
}

void Player::HitDamage(float damage) {
	float PlayerHp = m_Hp->GetHp() - damage;
	if (PlayerHp < 0) {
		m_NextState = State::Dead;
	}
	m_Hp->HitDamage(PlayerHp);
}

void Player::OpenInventory()
{
	if (State::Dead != m_CurrentState) {
		m_NextState = State::Menu;
	}
}

void Player::CloseInventory()
{
	m_NextState = State::Idle;
}