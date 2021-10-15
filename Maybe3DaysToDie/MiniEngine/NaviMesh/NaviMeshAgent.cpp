#include "MiniEngine.h"
#include "NaviMeshAgent.h"
#include "NaviMesh.h"
#include "AStar.h"
#include "prefab/ModelRender.h"

namespace Engine {
    void NaviMeshAgent::Init(prefab::ModelRender* m_render, NaviMesh* mesh, const bool& randMove)
    {
        m_modelRender = m_render;
        m_naviMesh = mesh;
        m_isPathMoveRandom = randMove;
    }

    void NaviMeshAgent::Move()
    {
        if (m_isArrive == true) {
            //�ړI�n�ɓ������Ă��邽��A*���X�V����B
            if (m_isPathMove) {
                //�p�X�ړ����s���B
                if (m_isPathMoveRandom && m_paths.size() > 2) {
                    //�p�X�������_���ړ��B
                    //�O�t���[���ɑI�΂ꂽ�p�X��ۑ��B
                    int savePath = m_pathIndex;
                    while (savePath == m_pathIndex) {
                        //�����t���[���؂�̌����ɂȂ肻��....�B���v�Ȃ̂��ȁB
                        //�O�t���[���ƑI�񂾃p�X���ꏏ�̂��ߑI�ђ����B
                        m_pathIndex = rand() % m_paths.size();
                    }
                }
                else {
                    //�p�X�����Ԃǂ���Ɉړ��B
                    if (m_pathIndex != m_paths.size() - 1) {
                        //���p�X�ցB
                        m_pathIndex++;
                    }
                    else {
                        //�ŏ��ɖ߂��B
                        m_pathIndex = 0;
                    }
                }
                //�p�X�ړ��Ȃ̂Ŏw��p�X�Ƀ^�[�Q�b�g��ݒ�B
                m_targetPos = m_paths[m_pathIndex];
            }
            //�X�V�K�v�B
            m_nodeList = m_astar.Search(m_modelRender->GetPosition(), m_targetPos, m_naviMesh->GetCellList());
            m_isPathMove = true;
            m_isArrive = false;
        }

        printf("");

        //��������ړ������B
        //���̃Z���Ɍ������x�N�g���B
        if (m_nodeList.size() != 0) {
            m_toNextCell = m_nodeList.front()->m_CenterPos - m_modelRender->GetPosition();
            //���ʉ�����O�ɁA��������Ƃ��B
            float dist = m_toNextCell.Length();
            //���ʃx�N�g�����B
            m_toNextCell.Normalize();
            //�������B
            m_agentPos = m_modelRender->GetPosition() + m_toNextCell * m_speed;
            //��]�v�Z�B
            m_agentRot.SetRotation(Vector3::AxisY, atan2f(m_toNextCell.x * 1.0f, m_toNextCell.z * 1.0f));

            //�m�[�h�ɓ��B����������B
            if (dist < 5) {
                m_nodeList.erase(m_nodeList.begin());
            }
        }
        else {
            //�����B
            m_isArrive = true;
        }

        //if (m_modelRender->GetAnimLoop() || !m_modelRender->isPlayAnim()) {
        //    m_modelRender->PlayAnimation(0, 0.1f);
        //}
    }
}
