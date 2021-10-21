#pragma once
#include "Stage/IStage.h"

class Hill:public IStage
{
public:
	Hill() {}
	~Hill() override final {}

	void OnDestroy();
	void CreateStage()override final;
	//�������Z�b�g����
	void SetHeight(Vector3 pos);

private:
	//�p�[�����m�C�Y�֐�
	void PerlinNoize(float x,float y);

	//���z�x�N�g�������߂�
	Vector2 grad(int x, int y);
private:
	const int MaxHeight = 10;		// �ő�̍���
	const int Relief = 15;		//�N���̌�����
	//�V�[�h�l
	float SeedX = 0.0f;
	float SeedZ = 0.0f;
};

