#pragma once
#include "Stage/IStage.h"

class SuperFlat:public IStage
{
public:
	SuperFlat() {}
	~SuperFlat() override final {}

	void OnDestroy();
	void CreateStage()override final;
	void ReCreate();
private:
};

