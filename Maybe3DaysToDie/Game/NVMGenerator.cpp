#include "stdafx.h"
#include "NVMGenerator.h"
#include "DestructibleObject/Terrain/Terrain.h"

bool NVMGenerator::isInstantiate = false;

NVMGenerator::NVMGenerator()
{
	//シングルトン。
	assert(!isInstantiate);
	isInstantiate = true;
}

NVMGenerator::~NVMGenerator()
{
}

void NVMGenerator::CreateNVM(nsTerrain::TerrainRender* terrain)
{
	//ブロック数分回す。
	{
		//重点の数はメッシュの数。
		int meshCount = terrain->GetCenterArray().size();

		for (int mesh = 0; mesh < meshCount; mesh++) {
			//メッシュの数分
		}
		


		//重点座標を参照してブロックのAABBを計算する。

		//算出したAABBより、セルを２個作成する。

		//頂点座標よりセルの隣接セルを計算する。

		//
	}
}

void NVMGenerator::UpdateNVM(nsTerrain::TerrainRender* terrain)
{
}

void NVMGenerator::DebugDraw(bool& isEnableDebug)
{

}
