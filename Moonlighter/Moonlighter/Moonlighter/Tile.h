#pragma once
#include"Obj.h"

class CTile : public CObj
{
public:
	CTile();
	CTile(ETileType _tileType , float _x, float _y, float _sizeX, float sizeY);
	virtual ~CTile();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hDC);
	virtual void LateUpdate();
	virtual void Release() override;

	void OnCollide(CObj* _pObj);

public:
	ETileType	GetTileType() { return m_eTileType; }
	void		SetTileType(ETileType _newType) { m_eTileType = _newType; }
	string		GetImgKey() { return m_strImgKey; }
	void		SetImgKey(string _newKey) { m_strImgKey = _newKey; }
	void		SetImgKeyInt(int _keyNum);
	int			GetTileNum() { return m_iTileNum; }

protected:
	ETileType m_eTileType = ETileType::ENUM_END;
	string m_strImgKey = "";
	int		m_iTileNum = 0;

	CComponent* m_pComponent;

};

