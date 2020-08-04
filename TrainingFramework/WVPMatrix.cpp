#include "stdafx.h"
#include "WVPMatrix.h"



void WVPMatrix::Update(float deltaTime, Matrix projection, Matrix view)
{
	WVP = W*view*projection;
}



WVPMatrix::WVPMatrix()
{
	WVP.SetIdentity();
	W.SetIdentity(); 
		T.SetIdentity();
		R.SetIdentity(); 
			Rx.SetIdentity();
			Ry.SetIdentity();
			Rz.SetIdentity();
		S.SetIdentity();
	V.SetIdentity();
	P.SetIdentity();
	WVP = W*V*P;
}


WVPMatrix::~WVPMatrix()
{
}
