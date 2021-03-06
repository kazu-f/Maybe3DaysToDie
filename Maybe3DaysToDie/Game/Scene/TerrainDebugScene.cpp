#include "stdafx.h"
#include "TerrainDebugScene.h"
#include "DestructibleObject/Terrain/Terrain.h"
#include "terrainManager/TerrainManager.h"
#include "terrainManager/TerrainWorld.h"

namespace {
	const float MOVE_SPEED = 200.0f * 5.0f;
	const float UP_SPEED = 80.0f * 5.0f;
	const float ROT_SPEED = 90.0f;
}

bool TerrainDebugScene::Start()
{
	NewGO<nsTerrain::TerrainWorld>(0,"world");
	prefab::CDirectionLight* lig = NewGO<prefab::CDirectionLight>(0);
	lig->SetColor({ 5.0f,5.0f,5.0f,1.0f });
	lig->SetDirection({ 1.0f,-1.0f,0.0f });

	return true;
}

void TerrainDebugScene::Update()
{
	CamMove();
	CamUpDown();
	CamRot();

	Vector3 targetPos = m_camPos + m_targetDir * CAM_TO_TARGET_LEN;

	MainCamera().SetPosition(m_camPos);
	MainCamera().SetTarget(targetPos);
}

void TerrainDebugScene::CamMove()
{
	const float LStickX = Pad(0).GetLStickXF();
	const float LStickY = Pad(0).GetLStickYF();

	const float moveSpeed = MOVE_SPEED * GameTime().GetFrameDeltaTime();

	Vector3 vForward = MainCamera().GetForward();
	Vector3 vRight = MainCamera().GetRight();
	vForward.y = 0.0f;
	vRight.y = 0.0f;
	vForward.Normalize();
	vRight.Normalize();

	m_camPos += vForward * LStickY * moveSpeed;
	m_camPos += vRight * LStickX * moveSpeed;
}

void TerrainDebugScene::CamUpDown()
{
	const float upSpeed = UP_SPEED * GameTime().GetFrameDeltaTime();
	Vector3 upDownVec = Vector3::Zero;
	if (Pad(0).IsPress(enButtonA))
	{
		upDownVec += Vector3::AxisY * upSpeed;
	}
	if (Pad(0).IsPress(enButtonB))
	{
		upDownVec += Vector3::AxisY * -upSpeed;
	}

	m_camPos += upDownVec;
}

void TerrainDebugScene::CamRot()
{
	const float RStickX = Pad(0).GetRStickXF();
	const float RStickY = Pad(0).GetRStickYF();

	const float rotSpeed = ROT_SPEED * GameTime().GetFrameDeltaTime();

	//Y???????̉??]?B
	Quaternion yRot;
	yRot.SetRotationDegY(RStickX * rotSpeed);
	yRot.Apply(m_targetDir);

	m_targetDir.Normalize();

	//?^?[?Q?b?g???????L?^?B
	Vector3 oldDir = m_targetDir;

	//?????v?Z?B
	Vector3 vAxis;
	vAxis.Cross(m_targetDir, Vector3::AxisY);
	vAxis.Normalize();

	//?????????̉??]?B
	Quaternion qRot;
	qRot.SetRotation(vAxis, Math::DegToRad(RStickY * rotSpeed));
	qRot.Apply(m_targetDir);

	m_targetDir.Normalize();

	if (fabsf(m_targetDir.Dot(Vector3::AxisY)) > 0.98f)
	{
		m_targetDir = oldDir;
	}


}


