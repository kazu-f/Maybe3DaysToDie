#include "stdafx.h"
#include "NaviMeshManager.h"
#include "Player/Player.h"

NaviMeshManager::~NaviMeshManager()
{
}

bool NaviMeshManager::Start()
{
	//�悭�Ȃ���Find����񂾂��g����Ȃ��I�H
	m_playerPtr = FindGO<Player>("player");



	//�ŏ���NVM�����������y�сA�`�����N�̏������������Ăяo���B
	return true;
}

void NaviMeshManager::Update()
{
	if (!m_isUpdateNVM)
	{
		//�n�`�̍X�V���Ȃ��B
		return;
	}

	//NVM���X�V���Ă����B

}

void NaviMeshManager::CalcPlayerGrid()
{
	if (m_playerPtr == nullptr)
	{
		//�ړ����Ă���I�u�W�F�N�g���Ȃ����ߍX�V�͕K�v�Ȃ��B
		return;
	}

	//player�̈ʒu�B
	Vector3 playerPos = m_playerPtr->GetPosition();

	//�v���C���[�̈ʒu���O���b�h���B
	m_playerGrid[0] = static_cast<int>(std::floor((playerPos.x / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[1] = static_cast<int>(std::floor((playerPos.z / OBJECT_UNIT) / ChunkWidth));// +MAX_CHUNK_SIDE / 2;
	m_playerGrid[0] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[0]), 1);
	m_playerGrid[1] = max(min(MAX_CHUNK_SIDE - 1, m_playerGrid[1]), 1);
}