#pragma once
/// <summary>
/// �X�v���C�g�̏������𕪂���₷�������w�b�_�[�t�@�C��
/// </summary>

/// <summary>
/// SpriteInitData�Ƀ|�W�V������X�P�[�����܂߂�����
/// </summary>
struct SpriteData {
	SpriteInitData sid;
	Vector2 pos = Vector2::Zero;
	Vector2 pivot = Vector2::Zero;
	int prio = 0;
};

static prefab::CSpriteRender* SpriteInit(SpriteData& sd)
{
	//Hp�X�v���C�g��������
	auto sp = NewGO<prefab::CSpriteRender>(sd.prio);
	char filePath[256] = "Assets/sprite/";
	strcat_s(filePath, sd.sid.m_ddsFilePath[0]);
	sd.sid.m_ddsFilePath[0] = filePath;
	sp->Init(sd.sid);
	sp->SetPosition(sd.pos);
	sp->SetPivot(sd.pivot);
	return sp;
}