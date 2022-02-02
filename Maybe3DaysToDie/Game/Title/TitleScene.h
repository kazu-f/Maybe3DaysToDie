#pragma once
class TitleScene:public IGameObject
{
private:
	TitleScene() {}
	~TitleScene() {}
public:
	bool Start()override final;
	void Update()override final;

private:

};