#pragma once

#define DECLARE_PROPERTY(propertyType, propertyName) \
private:\
	propertyType m_##propertyName;\
public: \
	void Set##propertyName(propertyType value) \
	{\
		m_##propertyName = value;\
	}