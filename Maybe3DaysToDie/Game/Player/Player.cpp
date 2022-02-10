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
#include "RayTest.h"
#include "Enemy/IEnemy.h"

namespace {
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
	ChangeState();

	if (PlayerState != nullptr) {
		PlayerState->Update();

	}
	if (GetAsyncKeyState('e')) {
		m_AccessObject->Access();
	}
	if (GetAsyncKeyState('r')) {
		m_AccessObject->EndAccess();
	}
	//レイテストで使用するベクトルを作成
	btVector3 start, end;
	Vector3 PlayerPos = m_Pos;
	PlayerPos.y += 90.0f;
	start.setValue(PlayerPos.x, PlayerPos.y + 90.0f, PlayerPos.z);
	float Range = 50.0f;
	Vector3 RayEnd = PlayerPos;
	RayEnd += MainCamera().GetForward()* Range;
	end.setValue(RayEnd.x, RayEnd.y + 90.0f, RayEnd.z);

	//レイテスト
	CharactorRayResult callback;
	PhysicsWorld().RayTest(start, end, callback);
	//レイが衝突しているとき
	if (callback.isHit)
	{
		m_Enemy = ((IEnemy*)callback.ColObj->getUserPointer());
		//オブジェクトのIDから適切なアクションを起こす
		auto& param = m_Enemy->();
	}
	//走る？
	Dash();

	//ジャンプ
	Jump();

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
	m_Characon.SetPosition(m_RespownPoint);
	m_Hp->Reset();
	m_Stamina->Reset();
	m_Hunger->Reset();
	m_Water->Reset();
	PlayerState->Leave();
	PlayerState = nullptr;
	m_NextState = State::Idle;
	while (true) {
		int returnNo = ShowCursor(false);
		if (returnNo <= 0) {
			break;
		}
	}
}

void Player::PeriodicUpdate()
{
	//ステータス減少時間を数える
	m_DeltaTime += GameTime().GetFrameDeltaTime();
}

void Player::ChangeState()
{
	if (m_CurrentState != m_NextState) {
		m_CurrentState = m_NextState;
	}
	
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
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	case Debug:
		m_mulSpeed = 2.0f;
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	default:
		SwichDebugMode();
		m_Camera->SetMovingMouse(false);
		break;
	}
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
			static State BuckUpState = State::Idle;
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

void Player::Dash()
{
	{
		if (GetAsyncKeyState(VK_LSHIFT) &&
			PlayerState->GetMoveSpeed().Length() > 0.5f &&
			m_Stamina->IsUseStamina(1))
		{
			m_NextState = State::Run;
		}
	}
}

void Player::Jump()
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
				PlayerState->SetMoveSpeedY(PlayerState->GetMoveSpeed().y + 1.0f);
			}
		}
	}
	if (IsJump)
	{
		NowTime += GameTime().GetFrameDeltaTime();
		const float JumpTime = 0.3f;
		float f = NowTime - JumpTime;
		const float JumpPower = 0.8f;
		PlayerState->SetMoveSpeedY(gravity * pow(f, 2.0f) + JumpPower);
		if (IsJumping && m_Characon.IsOnGround())
		{
			//ジャンプ中に地面についたのでジャンプ終了
			IsJump = false;
			IsJumping = false;
			NowTime = 0.0f;
			PlayerState->SetMoveSpeedY(0.0f);
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
	PlayerState->SetMoveSpeedY(PlayerState->GetMoveSpeed().y + gravity);
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
	if (PlayerHp <= 0) {
		m_NextState = State::Dead;
	}
	m_Hp->HitDamage(damage);
}

bool Player::OpenInventory()
{
	if (State::Dead != m_CurrentState) {
		m_NextState = State::Menu;
		return true;
	}
	return false;
}

void Player::CloseInventory()
{
	m_NextState = State::Idle;
}