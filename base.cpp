#include "precomp.h"
#include "base.h"
#include "game.h"

namespace Tmpl8 {

	Base::Base(vec2 basePos, float radius, int size) :
		m_BasePos(basePos),
		m_Radius(radius),
		m_Size(size)
	{}

	vec2 Base::Rotate(const vec2& m_BasePos, float m_Radius) const
	{
		//Note to self:
		//position must be length from [0,0]
		//Since it will rotate around [0,0]. [10,0] with PI radius will result in [-10,0]
		//https://matthew-brett.github.io/teaching/rotation_2d.html explanation and formula on how to rotate the line.
		vec2 pos;
		pos.x = m_BasePos.x * cos(m_Radius) - m_BasePos.y * sin(m_Radius);
		pos.y = m_BasePos.x * sin(m_Radius) + m_BasePos.y * cos(m_Radius);

		return pos;
	}

	void Base::ScreenWrap()
	{
		//Thanks to Brian and Rubun for give me the idea on how to create this

		if (m_BasePos.x > 805 && m_BasePos.y < 517)
		{
			m_BasePos.x = -9;
		}
		else if (m_BasePos.x > 805 && m_BasePos.y > 517)
		{
			m_BasePos.x = -9;
			m_BasePos.y = -9;
		}
		else if (m_BasePos.x < 805 && m_BasePos.y > 517)
		{
			m_BasePos.y = -9;
		}
		else if (m_BasePos.x < -10 && m_BasePos.y > -10)
		{
			m_BasePos.x = 804;
		}
		else if (m_BasePos.x < -10 && m_BasePos.y < -10)
		{
			m_BasePos.x = 804;
			m_BasePos.y = 516;
		}
		else if (m_BasePos.x > -10 && m_BasePos.y < -10)
		{
			m_BasePos.y = 516;
		}
	}
};