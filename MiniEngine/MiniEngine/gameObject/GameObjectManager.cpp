/// <summary>
/// �Q�[���I�u�W�F�N�g�}�l�[�W���[�B
/// </summary>

#include "stdafx.h"
#include "GameObjectManager.h"

namespace Engine {
	void CGameObjectManager::Start()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
	}

	void CGameObjectManager::PreUpdate()
	{
		for (auto objList : m_gameObjectListArray) {
			for (auto& obj : objList) {
				obj->PreUpdateWrapper();
			}
		}
	}

	void CGameObjectManager::Update()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
	}

	void CGameObjectManager::PostUpdate()
	{
		for (auto objList : m_gameObjectListArray) {
			for (auto& obj : objList) {
				obj->PostUpdateWrapper();
			}
		}
	}

	void CGameObjectManager::ForwardRender(RenderContext& rc)
	{
		for (auto objList : m_gameObjectListArray) {
			for (auto& obj : objList) {
				obj->ForwardRenderWrapper(rc);
			}
		}
	}

	void CGameObjectManager::PostRender(RenderContext& rc)
	{
		for (auto objList : m_gameObjectListArray) {
			for (auto& obj : objList) {
				obj->PostRenderWrapper(rc);
			}
		}
	}

	void CGameObjectManager::PreRender(RenderContext& rc)
	{
		for (auto objList : m_gameObjectListArray) {
			for (auto& obj : objList) {
				obj->PreRenderWrapper(rc);
			}
		}
	}

	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//�o�b�t�@�؂�ւ��B
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for (GameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
			for (IGameObject* go : goList) {
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_gameObjectListArray.at(prio);	//�폜����I�u�W�F�N�g�̗D��x�̃��X�g�擾�B
				auto it = std::find(goExecList.begin(), goExecList.end(), go);	//���X�g����I�u�W�F�N�g�̃C�e���[�^���擾�B
				if (it != goExecList.end()) {		//���X�g�ɂ���B
					//�폜���X�g���珜�O���ꂽ�B
					(*it)->m_isRegistDeadList = false;
					if ((*it)->IsNewFromGameObjectManager()) {	//GameObjectManajer�œo�^�����Ȃ�B
						delete (*it);
					}
				}
				goExecList.erase(it);	//�}�l�[�W���[�̃��X�g���珜�O�B
			}
			goList.clear();		//�폜���I���������폜���X�g���܂�����ɂ���B
		}
	}

	void CGameObjectManager::ExecuteFromGameThread()
	{
		//�X�V�n�̏����B
		{
			Start();		//�������B
			PreUpdate();	//���O�A�b�v�f�[�g�B
			Update();		//�X�V�����B
			PostUpdate();	//�x���A�b�v�f�[�g�B
		}
		//�`��n�̏����B
		{
			GraphicsEngine()->PreRenderUpdate();
			GraphicsEngine()->Render(this);
		}

		ExecuteDeleteGameObjects();		//�폜�����B
	}

	void CGameObjectManager::Init(int gameObjectPrioMax)
	{
		if (gameObjectPrioMax >= GAME_OBJECT_PRIO_MAX) {
			//�ő吔���������B
			std::abort();		//�Ƃ肠�����ُ�I�������Ă����B
		}
		m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray[0].resize(gameObjectPrioMax);
		m_deleteObjectArray[1].resize(gameObjectPrioMax);
	}

}	//!<namespace Engine
