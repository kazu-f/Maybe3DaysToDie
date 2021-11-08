#pragma once

#include "MiniEngine/MiniEngine.h"

//�c�[���̎��
enum ToolKinds {
	hand = 0,		//�f��
	axe = 1 << 0,		//��
	Pickaxe = 1 << 1,		//�c���n�V
	shovel = 1 << 2,		//�V���x��
	others = 1 << 3,		//���̑�
	DebugTool = 0xffffffff,		//�f�o�b�O�p�c�[��
};

#include "DestructibleObject/DestructibleObject.h"

//�`�����N�̃T�C�Y
const int ChunkWidth = 16;		//����
const int ChunkHeight = 8;		//����

const float SetRange = 500.0f;		//�v���C���[���͂��͈�


using namespace Engine;
