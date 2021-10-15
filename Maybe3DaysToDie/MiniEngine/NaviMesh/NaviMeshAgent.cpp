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
            //目的地に到着しているためA*を更新する。
            if (m_isPathMove) {
                //パス移動を行う。
                if (m_isPathMoveRandom && m_paths.size() > 2) {
                    //パスをランダム移動。
                    //前フレームに選ばれたパスを保存。
                    int savePath = m_pathIndex;
                    while (savePath == m_pathIndex) {
                        //ここフレーム切れの原因になりそう....。大丈夫なのかな。
                        //前フレームと選んだパスが一緒のため選び直し。
                        m_pathIndex = rand() % m_paths.size();
                    }
                }
                else {
                    //パスを順番どおりに移動。
                    if (m_pathIndex != m_paths.size() - 1) {
                        //次パスへ。
                        m_pathIndex++;
                    }
                    else {
                        //最初に戻す。
                        m_pathIndex = 0;
                    }
                }
                //パス移動なので指定パスにターゲットを設定。
                m_targetPos = m_paths[m_pathIndex];
            }
            //更新必要。
            m_nodeList = m_astar.Search(m_modelRender->GetPosition(), m_targetPos, m_naviMesh->GetCellList());
            m_isPathMove = true;
            m_isArrive = false;
        }

        printf("");

        //ここから移動処理。
        //次のセルに向かうベクトル。
        if (m_nodeList.size() != 0) {
            m_toNextCell = m_nodeList.front()->m_CenterPos - m_modelRender->GetPosition();
            //方位化する前に、距離取っとく。
            float dist = m_toNextCell.Length();
            //方位ベクトル化。
            m_toNextCell.Normalize();
            //動かす。
            m_agentPos = m_modelRender->GetPosition() + m_toNextCell * m_speed;
            //回転計算。
            m_agentRot.SetRotation(Vector3::AxisY, atan2f(m_toNextCell.x * 1.0f, m_toNextCell.z * 1.0f));

            //ノードに到達したか判定。
            if (dist < 5) {
                m_nodeList.erase(m_nodeList.begin());
            }
        }
        else {
            //到着。
            m_isArrive = true;
        }

        //if (m_modelRender->GetAnimLoop() || !m_modelRender->isPlayAnim()) {
        //    m_modelRender->PlayAnimation(0, 0.1f);
        //}
    }
}
