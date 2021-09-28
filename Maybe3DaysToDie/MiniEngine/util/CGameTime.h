#pragma once

//#include "Stopwatch.h"

namespace Engine {
	/// <summary>
	/// �Q�[���^�C���B
	/// </summary>
	class CGameTime : Noncopyable
	{
	public:
		/// <summary>
		/// 1�t���[���̌o�ߎ��Ԃ��擾(s)
		/// </summary>
		const float GetFrameDeltaTime()const
		{
			//�Œ�FPS
			//return 1.0f / 60.0f;

			//�σt���[�����[�g
			return m_frameDeltaTime;
		}
		/// <summary>
		/// 1�t���[��������̌o�ߎ��Ԃ̕��ς����B
		/// </summary>
		/// <param name="deltaTime">���݃t���[���̌o�ߎ���</param>
		void PushFrameDeltaTime(float deltaTime)
		{
			m_frameDeltaTimeQue.push_back(deltaTime);
			if (m_frameDeltaTimeQue.size() > 30.0f) {
				float totalTime = 0.0f;
				for (auto time : m_frameDeltaTimeQue) {
					//���v���v�Z�B
					totalTime += time;
				}
				//���ϒl�����B
				//�Œ�ł�30fps�͏o��悤�ɂ��Ă���B
				m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
				//��ԌÂ��l�����o���B
				m_frameDeltaTimeQue.pop_front();
			}
		}
	private:
		std::list<float> m_frameDeltaTimeQue;			//�o�ߎ��Ԃ̃��X�g�B
		float			 m_frameDeltaTime = 1.0f / 60.0f;	//1�t���[���̌o�ߎ��ԁB
	};

}
