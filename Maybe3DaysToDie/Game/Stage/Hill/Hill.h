#pragma once
#include "Stage/IStage.h"
const int tableSize = 255;

class Hill:public IStage
{
public:
	Hill();
	~Hill() override final {}

	void OnDestroy();
	void CreateStage()override final;
	//�������Z�b�g����
	void SetHeight(Vector3& pos);

private:
	//�p�[�����m�C�Y�֐�
	float PerlinNoize(float x,float y);

	//���z�x�N�g�������߂�
	Vector2 grad(int x, int y);

	void SetupRandomTable();

	float fade(float t);

	//float���m�̐��`�⊮�֐�
	float lerpf(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	
	//�z����V���b�t������
	void shuffle(int* array, int size);

private:
	const int MaxHeight = 1000;		// �ő�̍���
	const int Relief = 15;		//�N���̌�����
	//�V�[�h�l
	float SeedX = 0.0f;
	float SeedZ = 0.0f;
	const bool easeFlg = false;
	Vector2 randomTable[tableSize] = { Vector2::Zero };
	int permX[tableSize] = { 0 };
	int permY[tableSize] = { 0 };
};

