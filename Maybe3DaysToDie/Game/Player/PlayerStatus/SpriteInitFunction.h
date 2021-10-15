#pragma once
/// <summary>
/// SpriteInitData�Ƀ|�W�V������X�P�[�����܂߂�����
/// </summary>
struct SpriteData {
	SpriteInitData sid;
	Vector2 pos = Vector2::Zero;
	Vector2 pivot = Vector2::Zero;
	int prio = 0;
};

/// <summary>
/// �X�v���C�g������������Ƃ��Ɏg�p����
/// SpriteData�ŏ���������
/// </summary>
/// <param name="sd">�������������f�[�^</param>
/// <returns>�X�v���C�g�����_�[�̃|�C���^</returns>
static prefab::CSpriteRender* SpriteInit(SpriteData& sd)
{
	//Hp�X�v���C�g��������
	prefab::CSpriteRender* sp = NewGO<prefab::CSpriteRender>(sd.prio);
	char filePath[256] = "Assets/sprite/";
	strcat_s(filePath, sd.sid.m_ddsFilePath[0]);
	//�V�F�[�_�[�̃t�@�C���p�X
	sd.sid.m_fxFilePath = "Assets/shader/sprite.fx";
	sd.sid.m_ddsFilePath[0] = filePath;
	sp->Init(sd.sid);
	sp->SetPosition(sd.pos);
	sp->SetPivot(sd.pivot);
	return sp;
}