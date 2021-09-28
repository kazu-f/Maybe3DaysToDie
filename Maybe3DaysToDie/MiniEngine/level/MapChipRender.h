#pragma once

#include "Level.h"
#include "prefab/ModelRender.h"

namespace Engine {
	struct SLevelObjectData;
	/// <summary>
	/// �}�b�v�`�b�v�����_�[�B
	/// </summary>
	class CMapChipRender  :public IGameObject
	{
	public:
		CMapChipRender();
		~CMapChipRender();
		void OnDestroy() override;	//DeleteGO�����Ƃ��ɌĂяo�����֐��B
		void Update() override;		//�X�V�����B

		/// <summary>
		/// �`�悷��I�u�W�F�N�g�̐���ǉ��B
		/// </summary>
		void AddRenderObject(const SLevelObjectData& objData)
		{
			m_renderObjDatas.push_back(objData);
		}
		/// <summary>
		/// �����������B�S�Ă̕`��I�u�W�F�N�g�̒ǉ����I�������ŌĂяo���K�v������B
		/// </summary>
		void InitAfterAddAllRenderObjects();
		/// <summary>
		/// �X�L�����f�������_�[���擾�B
		/// </summary>
		prefab::ModelRender* GetModelRender()
		{
			return m_modelRender;
		}
		/// <summary>
		/// �`��I�u�W�F�N�g�f�[�^�ɃN�G�����s���B
		/// </summary>
		/// <param name="queryFunc">�N�G���֐��B</param>
		void QueryRenderObjDatas(std::function<void(const SLevelObjectData& objData)> queryFunc)
		{
			for (const auto& renderObjData : m_renderObjDatas)
			{
				queryFunc(renderObjData);
			}
		}

	private:
		int m_numRenderObject = 0;							//�`�悷��I�u�W�F�N�g�̐��B
		std::vector<SLevelObjectData> m_renderObjDatas;		//�`�悷��I�u�W�F�N�g�̃f�[�^�z��B
		prefab::ModelRender* m_modelRender = nullptr;		//���f�������_�[�B
	};		//class CMapChipRender
}	//namespace Engine

