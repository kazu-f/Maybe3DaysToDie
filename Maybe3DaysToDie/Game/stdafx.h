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
enum class ObjectType {
	Type = 0,
	Terrain = 1 << 0,
	Block = 1 << 1,
};

#include "DestructibleObject/DestructibleObject.h"
#include "nlohmann/json.hpp"						//json�t�@�C�����������߂̃w�b�_�B

//�`�����N�̃T�C�Y
const int ChunkWidth = 16;		//����
const int ChunkHeight = 8;		//����

const int MAX_CHUNK_SIDE = 64;		//���[���h�S�̂̈�ӂɂ����`�����N�����邩

const float SetRange = 500.0f;		//�v���C���[���͂��͈�

static const int BlockKinds = 4;		//�u���b�N�̎��

using namespace Engine;
