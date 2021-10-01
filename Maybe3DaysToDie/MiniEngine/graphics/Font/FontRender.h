/// <summary>
/// �t�H���g�����_�[�B
/// </summary>
/// <remarks>
/// GameObjectManager���ŊǗ�����A�t�H���g�̃��b�p�[�N���X�B
/// ���[�U�[��`�̃^�C�~���O�ŕ`�������ۂ́AFont�N���X�ōs�����ƁB
/// </remarks>

#pragma once

#include "Font.h"

namespace Engine {
	class CFontRender : public IGameObject
	{
	public:
		/// <summary>
		/// �e�L�X�g��ݒ�B
		/// ������R�s�[�����邽�ߑ��x�x�߁B�p�r�ɍ��킹�Ďg�p���邱�ƁB
		/// </summary>
		/// <param name="text">�e�L�X�g�B</param>
		void SetText(const wchar_t* text)
		{
			if (wcscmp(m_text.c_str(), text) != 0) {
				//������ɕύX���������B
				//�����ŃR�s�[����������H
				m_text = text;
			}
		}
		/// <summary>
		/// �A���Z�[�t�ŁASetText�B
		/// <para>���ڐ��|�C���^�����ăe�L�X�g��ݒ肷�邽�߁A�����̖��ɒ��ӁB</para>
		/// <para>��{�I�ɂ͐ݒ茳�̕�������A�����o�ϐ��ɂ����Ďg�p����Ȃǂ̑Ώ����Ƃ邱�ƁB</para>
		/// </summary>
		/// <param name="text"></param>
		void SetTextUnsafe(const wchar_t* text)
		{
			//�R�s�[���������Ȃ��B
			m_textUnsafe = text;
		}
		/// <summary>
		/// �t�H���g��\��������W�ݒ�B
		/// <para>��ʒ�����0,0</para>
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const Vector2& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// �t�H���g�̐F��ݒ�B
		/// </summary>
		/// <param name="color">�J���[</param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// �t�H���g�̐F��ݒ�B
		/// <para>���ݒ�ł�����B</para>
		/// </summary>
		/// <param name="color">�J���[</param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot">��]�B</param>
		void SetRotation(float rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// �g�嗦�B
		/// </summary>
		/// <param name="scale">�X�P�[���B</param>
		void SetScale(float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �s�{�b�g�̐ݒ�B
		/// </summary>
		/// <param name="pivot">�s�{�b�g�B</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// �V���h�E�̃p�����[�^�[��ݒ�B
		/// </summary>
		/// <param name="isDrawShadow">�V���h�E��`�悷�邩</param>
		/// <param name="shadowOffset">�V���h�E�I�t�Z�b�g�B</param>
		/// <param name="shadowColor">�V���h�E�J���[�B</param>
		void SetShadowParam(const bool& isDrawShadow, const float& shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}
	private:
		void PostRender(RenderContext& rc) override;
	private:
		CFont			m_font;								//�t�H���g�B
		std::wstring	m_text;								//�e�L�X�g�B
		const wchar_t*	m_textUnsafe;						//�A���Z�[�t�e�L�X�g�B
		Vector2			m_position = Vector2::Zero;			//���W�B(0.0f,0.0f)�Ő^�񒆁B
		Vector4			m_color = Vector4::White;			//�J���[�B
		float			m_rotation = 0.0f;					//��]�B
		float			m_scale = 1.0f;						//�X�P�[���B
		Vector2			m_pivot = {0.5f, 0.5f};				//�s�{�b�g�B
	};
}
