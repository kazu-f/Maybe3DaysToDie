#include "MiniEngine.h"
#include "TklFile.h"

namespace Engine {
	void CTklFile::Load(const char* filePath)
	{
		auto fp = fopen(filePath, "rb");
		if (fp == nullptr)
		{
			ENGINE_MESSAGE_BOX(
				"tkl�t�@�C�����ǂݍ��߂܂���ł����B\n"
				"�t�@�C���p�X���m�F���Ă��������B\n"
			);
			return;
		}
		//tkl�t�@�C���̃o�[�W������ǂݍ��݁B
		fread(&m_tklVersion, sizeof(m_tklVersion), 1, fp);
		//�I�u�W�F�N�g�̐����擾�B
		fread(&m_numObject, sizeof(m_numObject), 1, fp);
		m_objects.resize(m_numObject);
		for (int i = 0; i < m_numObject; i++) {
			auto& obj = m_objects.at(i);
			size_t nameCount = 0;
			//�I�u�W�F�N�g�̖��O�擾�B
			fread(&nameCount, 1, 1, fp);
			obj.name = std::make_unique<char[]>(nameCount + 1);
			fread(obj.name.get(), nameCount + 1, 1, fp);
			//�e��ID���擾�B
			fread(&obj.parentNo, sizeof(obj.parentNo), 1, fp);
			//�o�C���h�|�[�Y���擾�B
			fread(&obj.bindPose, sizeof(obj.bindPose), 1, fp);
			//�o�C���h�|�[�Y�̋t�����擾�B
			fread(&obj.invBindPose, sizeof(obj.invBindPose), 1, fp);
			//�I�u�W�F�N�g�̔ԍ����L�^�B
			obj.no = i;
			//�V���h�E�L���X�^�[�t���O�B
			fread(&obj.isShadowCaster, sizeof(obj.isShadowCaster), 1, fp);
			//�V���h�E���V�[�o�[�t���O�B
			fread(&obj.isShadowReceiver, sizeof(obj.isShadowReceiver), 1, fp);
			//int�p�����[�^�B
			int numIntData;
			fread(&numIntData, sizeof(numIntData), 1, fp);
			for (int i = 0; i < numIntData; i++) {
				int val = 0;
				fread(&val, sizeof(val), 1, fp);
				obj.intDatas.push_back(val);
			}
			//float�p���[�^�B
			int numFloatData;
			fread(&numFloatData, sizeof(numFloatData), 1, fp);
			for (int i = 0; i < numFloatData; i++) {
				float val = 0;
				fread(&val, sizeof(val), 1, fp);
				obj.floatDatas.push_back(val);
			}
			//string�p�����[�^�B
			int numStringData;
			fread(&numStringData, sizeof(numStringData), 1, fp);
			obj.charsDatas.resize(numStringData);
			for (int i = 0; i < numStringData; i++) {
				size_t numChara;
				fread(&numChara, sizeof(numChara), 1, fp);
				obj.charsDatas[i] = std::make_unique<char[]>(numChara + 1);
				fread(obj.charsDatas[i].get(), numChara + 1, 1, fp);
			}
			//vector3�p�����[�^�B
			int numVec3Data;
			fread(&numVec3Data, sizeof(numVec3Data), 1, fp);
			for (int i = 0; i < numVec3Data; i++) {
				float x, y, z;
				fread(&x, sizeof(x), 1, fp);
				fread(&y, sizeof(y), 1, fp);
				fread(&z, sizeof(z), 1, fp);
				obj.vec3Datas.push_back(Vector3(x, y, z));
			}
		}

		fclose(fp);
		//�ǂݍ��݊����̈�B
		m_isLoaded = true;
	}
}