#pragma once
#include"Obj.h"

class CCreature : public CObj
{
public:
	CCreature();
	virtual ~CCreature();

private:

	int m_iHp;

};

