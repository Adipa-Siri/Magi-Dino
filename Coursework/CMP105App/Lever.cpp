#include "Lever.h"

Lever::Lever()
{
	m_used = false;
	setTextureRect(m_leverRight);
	setTag(Tag::Enemy);
}

void Lever::update(float dt)
{
	if (m_used && getTextureRect() == m_leverRight)
		setTextureRect(m_leverLeft);
	
	if (!m_used && getTextureRect() == m_leverLeft)
		setTextureRect(m_leverRight);
}
