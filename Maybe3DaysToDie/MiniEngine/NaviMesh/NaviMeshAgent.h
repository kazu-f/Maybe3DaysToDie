#pragma once

/// <summary>
/// A*�𗘗p����AI�B
/// </summary>
/// <code>
/// Init();
/// SetPath();
/// Move();
/// </code>

#include "AStar.h"
#include "NaviMesh.h"

namespace Engine {
	class NaviMeshAgent
	{
	public:
		/// <summary>
		/// �G�[�W�F���g���������B
		/// </summary>
		/// <param name="m_render">�Q�ƃ����_�[�B</param>
		/// <param name="mesh">�Q�ƃ��b�V���B</param>
		/// <param name="target">�ڕW�n�_�B</param>
		/// <param name="randomMove">����ׂɈړ��n�_��I�Ԃ��B</param>
		void Init(prefab::ModelRender* m_render, NaviMesh* mesh, const bool& randMove);
		/// <summary>
		/// �G�[�W�F���g�̈ړ����x��ݒ�B
		/// </summary>
		/// <param name="speed"></param>
		void SetAgentSpeed(const float& speed)
		{
			m_speed = speed;
		}
		/// <summary>
		/// �����n�_�̃p�X��o�^�B
		/// </summary>
		/// <param name="pathList">�p�X���X�g�B</param>
		/// <param name="randomMove">�p�X�������_���ňړ����邩�B</param>
		void RegistPath(const Vector3& pos)
		{
			m_paths.push_back(pos);
		}
		/// <summary>
		/// �ڕW�n�_��ݒ�B
		/// </summary>
		/// <param name="target"></param>
		void SetTargetPos(const Vector3& target)
		{
			m_targetPos = target;
			m_isPathMove = false;
			m_isArrive = true;
		}
		/// <summary>
		/// �ړ��������擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetMoveDirection() const
		{
			return m_toNextCell;
		}
		/// <summary>
		/// �ړ������B
		/// <para>�ړ������ɉ����ĉ�]���v�Z���Ă���B</para>
		/// </summary>
		void Move();
		/// <summary>
		/// �G�[�W�F���g�̈ړ����x���擾�B
		/// </summary>
		/// <returns></returns>
		float& GetAgentSpeed()
		{
			return m_speed;
		}

		Vector3& GetAgentPos()
		{
			return m_agentPos;
		}
		Quaternion& GetAgentRot()
		{
			return m_agentRot;
		}
		/// <summary>
		/// �^�[�Q�b�g�Z���܂œ������Ă�H
		/// </summary>
		/// <returns></returns>
		bool& IsArriveTarget()
		{
			return m_isArrive;
		}
	private:
		prefab::ModelRender* m_modelRender = nullptr;	//�Q�ƃ��f���B
		NaviMesh* m_naviMesh = nullptr;		//�i�r���b�V���B
		float							m_speed = 1.0f;				//�G�[�W�F���g�̈ړ����x�B
		AStar							m_astar;					//�o�H�T���B
		NaviMesh::Cell* m_nodeCell = nullptr;		//�m�[�h�Z���B
		bool							m_isArrive = true;			//�X�V�K�v�B
		std::vector<NaviMesh::Cell*>	m_nodeList;					//�m�[�h���X�g�B		
		Vector3							m_targetPos = g_vec3Zero;	//�ړI�n�_�B
		Vector3							m_toNextCell;				//���̃Z���Ɍ��������ʃx�N�g���B
		std::vector<Vector3>			m_paths;					//�T���p�X�Btodo:�z��B
		bool							m_isPathMoveRandom = false;	//�p�X�������_���ňړ�����H
		bool							m_isPathMove = true;		//�p�X�ňړ��B
		int								m_pathIndex = 0;			//�p�X�̓Y���B
		Vector3							m_agentPos;
		Quaternion						m_agentRot;
	};
}

