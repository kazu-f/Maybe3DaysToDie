#include "stdafx.h"
#include "Player.h"
#include "PlayerStatus/PlayerHp.h"
#include "PlayerStatus/PlayerStamina.h"
#include "PlayerStatus/PlayerHunger.h"
#include "PlayerStatus/PlayerWater.h"
#include "GameCamera.h"
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

	//水分を作る
	m_Water = NewGO<PlayerWater>(0, "playerWater");

	m_Font = NewGO<CFontRender>(0);
	m_Font->SetText(L"Press'G' MoveMode Chenge\nPress'1' Fly");
	m_Font->SetPosition({ -640.0f,100.0f });
	m_Font->SetColor(Vector4::Red);
	m_Font->SetScale(0.6f);
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
	if (m_CurrentState != State::Inventry) {
		static bool IsPush = false;
		if (GetAsyncKeyState('G')) {
			if (!IsPush) {
				m_IsChasePlayer = !m_IsChasePlayer;
			}
			IsPush = true;
		}
		else {
			IsPush = false;
		}
		//時間経過による回復
		PeriodicUpdate();
		//移動処理
		Move();
		m_Camera->SetMovingMouse(false);
	}
	else
	{
		m_Camera->SetMovingMouse(true);
	}
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
		if (m_IsChasePlayer) {
			MoveSpeed += Forward;
		}
		else {
			MoveSpeed += MainCamera().GetForward();
		}
	}
	//Sキーが押されたら
	if (GetAsyncKeyState('S')) {
		if (m_IsChasePlayer) {
			MoveSpeed -= Forward;
		}
		else {
			MoveSpeed -= MainCamera().GetForward();
		}
	}
	//Aキーが押されたら
	if (GetAsyncKeyState('A')) {
		MoveSpeed -= MainCamera().GetRight();
	}
	//Dキーが押されたら
	if (GetAsyncKeyState('D')) {
		MoveSpeed += MainCamera().GetRight();
	}

	m_mulSpeed = 1.0f;
	if (GetAsyncKeyState(VK_LSHIFT) &&
		MoveSpeed.Length() > 0.5f &&
		m_Stamina->IsUseStamina(1))
	{

		m_mulSpeed = 2.0f;
	}
	/////重力処理////////////////////////
	{
		static float gravity = 0.0f;
		gravity -= 0.7;
		if (!m_IsChasePlayer) {
			gravity = 0.0f;
		}

		/////////ジャンプ処理/////////////////////////////////////////////
		{
			if (GetAsyncKeyState(VK_SPACE)) {
				//神視点の時はジャンプし続ける
				if (m_IsChasePlayer) {
					if (m_Characon.IsOnGround()) {
						MoveSpeed.y = 5.0f;
					}
				}
				else {
					MoveSpeed.y = 5.0f;
				}
			}
		}
		/////////////////////
		if (m_Characon.IsOnGround()) {
			gravity = 0.0f;
		}
		MoveSpeed.y += gravity;
	}
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

void Player::HitDamage(float damage) {
	float PlayerHp = m_Hp->GetHp() - damage;
	if (PlayerHp < 0) {
		m_NextState = State::Dead;
	}
	else {
		m_NextState = State::Damage;
	}
}

void Player::OpenInventory()
{
	if (State::Dead != m_CurrentState) {
		m_NextState = State::Inventry;
	}
}

void Player::CloseInventory()
{
	m_NextState = State::Idle;
}