#pragma once
//todo プレイヤー側から呼ぶようになったらIGameObjectを継承しないように
class DestroyObject:public IGameObject
{
public:
	DestroyObject();
	~DestroyObject();

};

