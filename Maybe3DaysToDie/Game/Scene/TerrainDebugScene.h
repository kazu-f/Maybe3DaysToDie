#pragma once

#include "Navigation/NVMGenerator.h"

class TerrainDebugScene : public IGameObject
{
public:
	//最初の関数。
	bool Start()override final;
	//更新関数。
	void Update()override final;
private:
	void CamMove();
	void CamUpDown();
	void CamRot();

private:
	Vector3 m_camPos = Vector3::Zero;
	Vector3 m_targetDir = Vector3::AxisZ;
	const float CAM_TO_TARGET_LEN = 200.0f;
};

