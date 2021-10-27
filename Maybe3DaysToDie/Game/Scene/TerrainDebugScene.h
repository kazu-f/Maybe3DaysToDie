#pragma once

#include "Navigation/NVMGenerator.h"

class TerrainDebugScene : public IGameObject
{
public:
	//�ŏ��̊֐��B
	bool Start()override final;
	//�X�V�֐��B
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

