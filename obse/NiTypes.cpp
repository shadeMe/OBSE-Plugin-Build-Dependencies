#include "NiTypes.h"
#include "NiMath.inl"

void NiTransform::ExtractAngleAndAxis(float& fAngle, float& fX, float& fY, float& fZ) const
{
	// Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
	// The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
	// I is the identity and
	//
	//       +-        -+
	//   P = |  0 +z -y |
	//       | -z  0 +x |
	//       | +y -x  0 |
	//       +-        -+
	//
	// Some algebra will show that
	//
	//   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P

	float fTrace = rotate.m[0][0] + rotate.m[1][1] + rotate.m[2][2];
	fAngle = NiACos(0.5f*(fTrace - 1.0f));

	fX = rotate.m[1][2] - rotate.m[2][1];
	fY = rotate.m[2][0] - rotate.m[0][2];
	fZ = rotate.m[0][1] - rotate.m[1][0];
	float fLength = NiSqrt(fX*fX + fY*fY + fZ*fZ);
	const float fEpsilon = 1e-06f;
	if (fLength > fEpsilon)
	{
		float fInvLength = 1.0f / fLength;
		fX *= fInvLength;
		fY *= fInvLength;
		fZ *= fInvLength;
	}
	else  // angle is 0 or pi
	{
		if (fAngle > 1.0f)  // any number strictly between 0 and pi works
		{
			// angle must be pi
			fX = NiSqrt(0.5f*(1.0f + rotate.m[0][0]));
			fY = NiSqrt(0.5f*(1.0f + rotate.m[1][1]));
			fZ = NiSqrt(0.5f*(1.0f + rotate.m[2][2]));

			// determine signs of axis components
			float tx, ty, tz;
			tx = rotate.m[0][0] * fX + rotate.m[0][1] * fY + rotate.m[0][2] * fZ - fX;
			ty = rotate.m[1][0] * fX + rotate.m[1][1] * fY + rotate.m[1][2] * fZ - fY;
			tz = rotate.m[2][0] * fX + rotate.m[2][1] * fY + rotate.m[2][2] * fZ - fZ;
			fLength = tx*tx + ty*ty + tz*tz;
			if (fLength < fEpsilon)
				return;

			fZ = -fZ;
			tx = rotate.m[0][0] * fX + rotate.m[0][1] * fY + rotate.m[0][2] * fZ - fX;
			ty = rotate.m[1][0] * fX + rotate.m[1][1] * fY + rotate.m[1][2] * fZ - fY;
			tz = rotate.m[2][0] * fX + rotate.m[2][1] * fY + rotate.m[2][2] * fZ - fZ;
			fLength = tx*tx + ty*ty + tz*tz;
			if (fLength < fEpsilon)
				return;

			fY = -fY;
			tx = rotate.m[0][0] * fX + rotate.m[0][1] * fY + rotate.m[0][2] * fZ - fX;
			ty = rotate.m[1][0] * fX + rotate.m[1][1] * fY + rotate.m[1][2] * fZ - fY;
			tz = rotate.m[2][0] * fX + rotate.m[2][1] * fY + rotate.m[2][2] * fZ - fZ;
			fLength = tx*tx + ty*ty + tz*tz;
			if (fLength < fEpsilon)
				return;
		}
		else
		{
			// Angle is zero, matrix is the identity, no unique axis, so
			// return (1,0,0) for as good a guess as any.
			fX = 1.0f;
			fY = 0.0f;
			fZ = 0.0f;
		}
	}
}

void GetD3DFromNi(D3DMATRIX& kD3D, const NiMatrix33& kNiRot, const NiVector3& kNiTrans, float fNiScale)
{
	kD3D._11 = kNiRot.GetEntry(0, 0) * fNiScale;
	kD3D._12 = kNiRot.GetEntry(1, 0) * fNiScale;
	kD3D._13 = kNiRot.GetEntry(2, 0) * fNiScale;
	kD3D._14 = 0.0f;
	kD3D._21 = kNiRot.GetEntry(0, 1) * fNiScale;
	kD3D._22 = kNiRot.GetEntry(1, 1) * fNiScale;
	kD3D._23 = kNiRot.GetEntry(2, 1) * fNiScale;
	kD3D._24 = 0.0f;
	kD3D._31 = kNiRot.GetEntry(0, 2) * fNiScale;
	kD3D._32 = kNiRot.GetEntry(1, 2) * fNiScale;
	kD3D._33 = kNiRot.GetEntry(2, 2) * fNiScale;
	kD3D._34 = 0.0f;
	kD3D._41 = kNiTrans.x;
	kD3D._42 = kNiTrans.y;
	kD3D._43 = kNiTrans.z;
	kD3D._44 = 1.0f;
}

void GetD3DFromNiTranspose(D3DMATRIX& kD3D, const NiMatrix33& kNiRot, const NiVector3& kNiTrans, float fNiScale)
{
	kD3D._11 = kNiRot.GetEntry(0, 0) * fNiScale;
	kD3D._12 = kNiRot.GetEntry(0, 1) * fNiScale;
	kD3D._13 = kNiRot.GetEntry(0, 2) * fNiScale;
	kD3D._14 = kNiTrans.x;
	kD3D._21 = kNiRot.GetEntry(1, 0) * fNiScale;
	kD3D._22 = kNiRot.GetEntry(1, 1) * fNiScale;
	kD3D._23 = kNiRot.GetEntry(1, 2) * fNiScale;
	kD3D._24 = kNiTrans.y;
	kD3D._31 = kNiRot.GetEntry(2, 0) * fNiScale;
	kD3D._32 = kNiRot.GetEntry(2, 1) * fNiScale;
	kD3D._33 = kNiRot.GetEntry(2, 2) * fNiScale;
	kD3D._34 = kNiTrans.z;
	kD3D._41 = 0.0f;
	kD3D._42 = 0.0f;
	kD3D._43 = 0.0f;
	kD3D._44 = 1.0f;
}

void NiTransform::GetD3D(D3DMATRIX& out) const
{
	GetD3DFromNi(out, rotate, translate, scale);
}

void NiTransform::GetD3DTranspose(D3DMATRIX& out) const
{
	GetD3DFromNiTranspose(out, rotate, translate, scale);
}

float NiMatrix33::GetEntry(unsigned int uiRow, unsigned int uiCol) const
{
	return m[uiRow][uiCol];
}

void NiMatrix33::GetCol(unsigned int uiCol, NiVector3& col) const
{
	col.x = m[0][uiCol];
	col.y = m[1][uiCol];
	col.z = m[2][uiCol];
}

void NiVector3::Cross(const NiVector3& v1, const NiVector3& v2, NiVector3& out)
{
	out.x = v1.y * v2.z - v1.z * v2.y;
	out.y = v1.z * v2.x - v1.x * v2.z;
	out.z = v1.x * v2.y - v1.y * v2.x;
}

NiVector3& NiVector3::operator=(const Vector3& RHS)
{
	x = RHS.x;
	y = RHS.y;
	z = RHS.z;
	return *this;
}
