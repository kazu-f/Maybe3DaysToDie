#pragma once

struct SPlaceObjCollectData
{
	int collectID = -1;		//�̎�A�C�e����ID�B
	int collectNum = 1;		//�̎�ł���ʁB
};

using ObjectCollectItemData = std::vector<SPlaceObjCollectData>;
