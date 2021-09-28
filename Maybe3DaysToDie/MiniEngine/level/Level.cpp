#include "MiniEngine.h"
#include "Level.h"
#include "MapChip.h"
#include "MapChipRender.h"

namespace Engine {
	CLevel::CLevel()
	{
	}
	CLevel::~CLevel()
	{
		for (auto mapChipRender : m_mapChipRenderPtrs) {
			DeleteGO(mapChipRender.second);
		}
	}
	void CLevel::CreateMapChipRenderOrAddRenderObject(const SLevelObjectData& objData)
	{
		WNameKey nameKey(objData.name);

		auto itFind = m_mapChipRenderPtrs.find(nameKey.GetHashCode());
		CMapChipRender* pMapChipRender = nullptr;
		if (itFind == m_mapChipRenderPtrs.end()){
			//�o�^����Ă��Ȃ��B
			auto mapChipRender = NewGO <CMapChipRender>(0);
			pMapChipRender = mapChipRender;
			m_mapChipRenderPtrs.insert({ nameKey.GetHashCode(),mapChipRender });
		}
		else {
			//���ɂ���B
			pMapChipRender = itFind->second;
		}
		pMapChipRender->AddRenderObject(objData);
	}
	void CLevel::Init(
		const char* filePath,
		std::function<bool(SLevelObjectData& objData)> hookFunc
	){
		//���x�������[�h�B
		m_tklFile.Load(filePath);
		BuildBoneMatrices();
		//���x���f�[�^���擾�B
		struct SParams
		{
			bool isShadowCaster;
			bool isShadowReceiver;
		};
		std::vector<SParams> Params;
		m_tklFile.QueryObject([&](auto& tklObj) {
			SParams objParam;
			objParam.isShadowCaster = tklObj.isShadowCaster;
			objParam.isShadowReceiver = tklObj.isShadowReceiver;
			Params.push_back(objParam);
			});

		for (int i = 1; i < m_bones.size(); i++) {
			auto bone = m_bones[i].get();
			if (bone->GetParentBoneNo() == 0) {	//�e�����[�g�̏ꍇ�̂݃}�b�v�`�b�v�����B
				SLevelObjectData objData;
				bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);
				//3dsMax�Ǝ����Ⴄ���߁A�␳������B
				//���W�B
				auto t = objData.position.y;
				objData.position.y = objData.position.z;
				objData.position.z = -t;
				//��]�B
				t = objData.rotation.y;
				objData.rotation.y = objData.rotation.z;
				objData.rotation.z = -t;

				objData.name = bone->GetName();
				objData.isShadowCaster = Params.at(i).isShadowCaster;
				objData.isShadowReceiver = Params.at(i).isShadowReceiver;

				bool isHook = false;
				if (hookFunc != nullptr) {
					//�t�b�N�֐����w�肳��Ă��邽�ߌĂяo���B
					isHook = hookFunc(objData);
				}
				if (isHook == false) {
					//�}�b�v�`�b�v�����_�[���쐬����B
					CreateMapChipRenderOrAddRenderObject(objData);
				}
			}
		}
		//�}�b�v�`�b�v�����_�[������������B
		for (auto& mapChipRender : m_mapChipRenderPtrs) {
			mapChipRender.second->InitAfterAddAllRenderObjects();
			mapChipRender.second->QueryRenderObjDatas([&](const SLevelObjectData& objData) {
				//�t�b�N����Ȃ�������A�}�b�v�`�b�v�쐬�B
				auto mapChip = std::make_unique<CMapChip>(objData, mapChipRender.second);
				m_mapChipPtrs.push_back(std::move(mapChip));
				});
		}
	}
	void CLevel::BuildBoneMatrices()
	{
		m_tklFile.QueryObject([&](auto& tklObj) {
			//�o�C���h�|�[�Y�B
			Matrix bindPoseMatrix;
			memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
			memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
			memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
			memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
			bindPoseMatrix.m[0][3] = 0.0f;
			bindPoseMatrix.m[1][3] = 0.0f;
			bindPoseMatrix.m[2][3] = 0.0f;
			bindPoseMatrix.m[3][3] = 0.0f;
			
			//�o�C���h�|�[�Y�̋t�s��B
			Matrix invBindPoseMatrix;
			memcpy(invBindPoseMatrix.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
			memcpy(invBindPoseMatrix.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
			memcpy(invBindPoseMatrix.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
			memcpy(invBindPoseMatrix.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
			invBindPoseMatrix.m[0][3] = 0.0f;
			invBindPoseMatrix.m[1][3] = 0.0f;
			invBindPoseMatrix.m[2][3] = 0.0f;
			invBindPoseMatrix.m[3][3] = 0.0f;
			//���C�h�����ɕϊ��B
			wchar_t boneName[256];
			mbstowcs(boneName, tklObj.name.get(), 256);
			BonePtr bone = std::make_unique<Bone>(
				boneName,
				bindPoseMatrix,
				invBindPoseMatrix,
				tklObj.parentNo,
				tklObj.no
				);

			m_bones.push_back(std::move(bone));
			});

		for (auto& bone : m_bones) {
			if (bone->GetParentBoneNo() != -1) {
				m_bones.at(bone->GetParentBoneNo())->AddChild(bone.get());
				//���[�J���}�g���N�X���v�Z�B
				const Matrix& parentMatrix = m_bones.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
				Matrix localMatrix;
				localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
				bone->SetLocalMatrix(localMatrix);
			}
			else {
				bone->SetLocalMatrix(bone->GetBindPoseMatrix());
			}
		}

		//�{�[���s����m��
		m_boneMatrixs = std::make_unique<Matrix[]>(m_bones.size());
		m_isInited = true;
	}
}