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
	Terrain = 0,		//�n�`
	Block = 1<<0,		//�u���b�N
};

//�A�N�Z�X�ł���I�u�W�F�N�g�̎��
enum class AccessTag {
	NonAccess = 0,		//�A�N�Z�X�ł��Ȃ�
	Root = 1 << 0,		//���[�g
};

#include "DestructibleObject/DestructibleObject.h"
#include "nlohmann/json.hpp"						//json�t�@�C�����������߂̃w�b�_�B

//�`�����N�̃T�C�Y
const int ChunkWidth = 16;		//����
const int ChunkHeight = 8;		//����

const int GroundSurface = 3;		//�n�\

const int MAX_CHUNK_SIDE = 64;		//���[���h�S�̂̈�ӂɂ����`�����N�����邩

const float SetRange = 500.0f;		//�v���C���[���͂��͈�

static const int BlockKinds = 5;		//�u���b�N�̎��

static const int Inventory_X = 7;
static const int Inventory_Y = 6;

//�Q�[�����Ƀ��[�h���Ă���`�����N�͈̔�
static const int LoadingChunkCols = 3;
static const int LoadingChunks = 3;

using namespace Engine;

#include "MauseInfo.h"