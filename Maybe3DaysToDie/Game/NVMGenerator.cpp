#include "stdafx.h"
#include "NVMGenerator.h"
#include "DestructibleObject/Terrain/Terrain.h"

bool NVMGenerator::isInstantiate = false;

NVMGenerator::NVMGenerator()
{
	//�V���O���g���B
	assert(!isInstantiate);
	isInstantiate = true;
}

NVMGenerator::~NVMGenerator()
{
}

void NVMGenerator::CreateNVM(nsTerrain::TerrainRender* terrain)
{
	//�u���b�N�����񂷁B
	{
		//�u���b�N�̏d�_���W�������Ă���B
		//terrain.ge

		//�d�_���W���Q�Ƃ��ău���b�N��AABB���v�Z����B

		//�Z�o����AABB���A�Z�����Q�쐬����B

		//���_���W���Z���̗אڃZ�����v�Z����B

		//
	}
}

void NVMGenerator::UpdateNVM(nsTerrain::TerrainRender* terrain)
{
}

void NVMGenerator::DebugDraw(bool& isEnableDebug)
{

}
