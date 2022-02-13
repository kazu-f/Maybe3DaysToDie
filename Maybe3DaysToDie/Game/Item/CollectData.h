#pragma once

struct SPlaceObjCollectData
{
	int collectID = -1;		//採取アイテムのID。
	int collectNum = 1;		//採取できる量。
};

using ObjectCollectItemData = std::vector<SPlaceObjCollectData>;

