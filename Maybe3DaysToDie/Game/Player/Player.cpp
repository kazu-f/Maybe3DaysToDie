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
#include "ItemBar/ItemBar.h"
#include "Inventory/Inventory.h"

#include "PlacementObject/PlacementObject.h"
#include "DestroyObject/DestroyObject.h"
#include "Tool/Tool.h"

namespace {
	const float CameraTargetDistance = 500.0f;	//プレイヤーからのターゲット距離
	const float NeckLimitY = 10.0f;				//上や下を向ける限界
	const float radius = 50.0f;
	const float hight = 90.0f;
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

	m_ItemBar = NewGO<ItemBar>(3);
	m_ItemBar->SetPlayer(this);

	m_Inventory = NewGO<Inventory>(0);
	m_Inventory->SetPlayer(this);

	//todo プレイヤーの処理等に置くようにしてください
	m_PlacementObject = NewGO<PlacementObject>(0);
	m_DestroyObject = NewGO<DestroyObject>(0);
	tool = new Tool;
	m_DestroyObject->SetTool(tool);
	m_PlacementObject->SetLoadingChunk(m_LoadingByChunk);
	m_ItemBar->SetWorldData(
		m_PlacementObject, m_DestroyObject
		, m_SaveData, tool, m_LoadingByChunk, m_Stage);
	m_PlacementObject->SetSaveData(m_SaveData);
	m_DestroyObject->SetSaveData(m_SaveData);

	ModelInitData PlayerModel;
	PlayerModel.m_tkmFilePath = "Assets/modelData/Player.tkm";

	AnimClipInitData AnInitData[State::Num];
	AnInitData[State::Idle].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	AnInitData[State::Idle].isLoop = true;
	AnInitData[State::Walk].tkaFilePath = "Assets/animData/PlayerWalk.tka";
	AnInitData[State::Walk].isLoop = true;
	AnInitData[State::Attack].tkaFilePath = "Assets/animData/PlayerIdle.tka";
	//m_Model = NewGO<prefab::ModelRender>(0);
	//m_Model->Init(PlayerModel, AnInitData,State::Num);
	//m_Model->SetPosition(m_Pos);
	//m_Model->SetRotation(m_Rot);
	//m_Model->SetScale(m_Scale);
	m_Pos = m_RespownPoint;
	m_Characon.Init(radius, hight, m_Pos);
	m_Characon.GetBody()->GetBody()->setUserPointer(this);
	m_NextState = State::Idle;
	return true;
}

void Player::Update()
{
	//ステートを更新
	ChangeState();

	if (m_PlayerState != nullptr) {
		m_PlayerState->Update();
	}
	if (MauseInfo::GetInstance()->GetMauseState() ==
		MauseInfo::State::MauseLClick) {
		m_AccessObject->Access();
	}
	if (MauseInfo::GetInstance()->GetMauseState() ==
		MauseInfo::State::MauseRClick ) {
		m_AccessObject->EndAccess();
	}
	if (m_AccessObject->IsAccess()) {
		m_NextState = State::Menu;
	}
	if (MauseInfo::GetInstance()->GetMauseState()==
		MauseInfo::State::MauseRClick&&
		m_CurrentState!=State::Menu) {
		//レイテストで使用するベクトルを作成
		btVector3 start, end;
		Vector3 PlayerPos = m_Pos;
		PlayerPos.y += 90.0f;
		start.setValue(PlayerPos.x, PlayerPos.y, PlayerPos.z);
		Vector3 RayEnd = PlayerPos;
		RayEnd += MainCamera().GetForward() * PlayerRange * OBJECT_UNIT;
		end.setValue(RayEnd.x, RayEnd.y, RayEnd.z);

		//レイテスト
		CharactorRayResult callback;
		callback.ExclusionPointer = this;
		PhysicsWorld().RayTest(start, end, callback);
		//レイが衝突しているとき
		if (callback.isHit)
		{
			m_Enemy = ((IEnemy*)callback.ColObj->getUserPointer());
			//オブジェクトのIDから適切なアクションを起こす
			int Attck = 105;
			m_Enemy->HitDamage(Attck);
		}
	}
	//時間経過による回復
	PeriodicUpdate();
	//カメラにポジションを渡す
	m_Camera->SetPosition(m_Pos);

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
	if (m_PlacementObject != nullptr)
	{
		DeleteGO(m_PlacementObject);
		m_PlacementObject = nullptr;
	}
	if (m_DestroyObject != nullptr)
	{
		DeleteGO(m_DestroyObject);
		m_DestroyObject = nullptr;
	}
	if (tool != nullptr)
	{
		delete tool;
		tool = nullptr;
	}

}

void Player::ReStart()
{
	m_Characon.SetPosition(m_RespownPoint);
	m_Hp->Reset();
	m_Stamina->Reset();
	m_Hunger->Reset();
	m_Water->Reset();
	m_PlayerState->Leave();
	m_PlayerState = nullptr;
	m_Gravity = 0.0f;
	m_NextState = State::Idle;
	while (true) {
		int returnNo = ShowCursor(false);
		if (returnNo <= 0) {
			break;
		}
	}
}

bool Player::UseStamina(int useCost)
{
	return m_Stamina->IsUseStamina(useCost);
}

void Player::SetMoveMause(bool isMove)
{
	m_Camera->SetMovingMouse(isMove);
}

void Player::ItemDetaInit(SaveDataFile* Sf, Stage* s)
{
	m_SaveData = Sf;
	m_Stage = s;
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
		if (m_PlayerState != nullptr) {
			m_PlayerState->Leave();
		}
		switch (m_CurrentState)
		{
		case State::Idle:
			m_PlayerState = &m_Idle;
			m_PlayerState->Enter();
			break;
		case State::Menu:
			m_PlayerState = &m_Menu;
			m_PlayerState->Enter();
			break;
		case State::Dead:
			m_PlayerState = &m_Dead;
			m_PlayerState->Enter();
			break;
		case State::Walk:
			m_PlayerState = &m_Walk;
			m_PlayerState->Enter();
			break;
		default:
			break;
		}
	}

}

void Player::Jump()
{
	m_Gravity -= GameTime().GetFrameDeltaTime();

	if (GetAsyncKeyState(VK_SPACE)) {
		//地面に設置しているときだけ
		//ジャンプする
		if (m_Characon.IsOnGround())
		{
			IsJump = true;
		}
		//神視点の時はジャンプし続ける
		if (IsDubug()) {
			m_PlayerState->SetMoveSpeedY(m_PlayerState->GetMoveSpeed().y + 1.0f);
		}
	}
	m_PlayerState->SetMoveSpeedY(m_PlayerState->GetMoveSpeed().y + m_Gravity );
	if (IsJump)
	{
		NowTime += GameTime().GetFrameDeltaTime();
		const float JumpTime = 0.1f;
		float f = NowTime - JumpTime;
		const float JumpPower = 0.6f;
		float Jump = m_Gravity * pow(f, 2.0f) + JumpPower;
		m_PlayerState->SetMoveSpeedY(Jump);
	}
	m_PlayerState->ExcuteMove();
	if (m_Characon.IsOnGround() ||
		m_IsDebugMode) {
		m_Gravity = 0.0f;
	}
	if (IsJumping && m_Characon.IsOnGround())
	{
		//ジャンプ中に地面についたのでジャンプ終了
		IsJump = false;
		IsJumping = false;
		NowTime = 0.0f;
		m_PlayerState->SetMoveSpeedY(0.0f);
	}
	else
	{
		IsJumping = true;
	}
}

const bool Player::IsDubug() const
{
	return m_IsDebugMode;
}

void Player::SetMulSpeed(const float mulSp)
{
	m_PlayerState->SetMulSpeed(mulSp);
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
	MauseInfo::GetInstance()->SetMauseCursor(MauseInfo::GetInstance()->IntialMausePos());
}