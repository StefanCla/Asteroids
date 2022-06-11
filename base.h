#pragma once

namespace Tmpl8 {

	class Base
	{
	public:
		virtual void Draw(Surface* screen) = 0;
		virtual void Update(float deltaTime) = 0;
		vec2 Rotate(const vec2& m_BasePos, float m_Radius) const;
		Base(vec2 basePos, float radius, int size);
		virtual void ScreenWrap();
		int m_Size;

	protected:
		float m_Radius;
		vec2 m_BasePos;
	};

}; // namespace Tmpl8