#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}

void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release(); //release memory 
	Init();    //reset shape


	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1

	std::vector<vector3> point;
	float theta = 0;
	float steps = 2*PI / static_cast<float>(a_nSubdivisions);

	//base circle
	//make disk center
	point.push_back(vector3(0, 0, 0));

	//generate points along circle for cone base
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta)*a_fRadius, sin(theta)*a_fRadius, 0));
		theta += steps;
	}

	//make base tris
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[1+i]);
	}
	AddTri(point[0], point[a_nSubdivisions], point[1]); //close disk

	//cone tip and sides
	point.push_back(vector3(0, 0, a_fHeight));

	//make side tris
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[a_nSubdivisions+1], point[i], point[1 + i]);
	}
	AddTri(point[a_nSubdivisions + 1], point[a_nSubdivisions], point[1]); //close side


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1

	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	int offset = 1;

	//base circle
	//make bottom disk center
	point.push_back(vector3(0, 0, 0));

	//generate points along circle
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta), sin(theta), 0));
		theta += steps;
	}

	//make base tris
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[1 + i]);
	}
	AddTri(point[0], point[a_nSubdivisions], point[1]); //close disk

	//top disk
	//make bottom disk center
	point.push_back(vector3(0, 0, a_fHeight));
	offset = a_nSubdivisions +1;

	//generate points along circle
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta), sin(theta), a_fHeight));
		theta += steps;
	}

	//make base tris
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[offset], point[i + offset], point[1 + i + offset]);
	}
	AddTri(point[offset], point[a_nSubdivisions+ offset], point[offset+1]); //close disk
	
	//make sides
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddQuad(point[i], point[i +1 ], point[i+ offset], point[i+1+offset]);
	}
	AddQuad(point[1], point[offset+1], point[a_nSubdivisions], point[offset+a_nSubdivisions]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> baseInner;
	std::vector<vector3> baseOuter;
	std::vector<vector3> topInner;
	std::vector<vector3> topOuter;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//INNER CIRCLE
	//generate points along circle
	for (int i = 0; i < a_nSubdivisions; i++) {
		baseInner.push_back(vector3(cos(theta)*a_fInnerRadius, sin(theta)*a_fInnerRadius, 0));
		theta += steps;
	} theta = 0;

	//top inner ring
	//generate points along circle
	for (int i = 0; i < a_nSubdivisions; i++) {
		topInner.push_back(vector3(cos(theta)*a_fInnerRadius, sin(theta)*a_fInnerRadius, a_fHeight));
		theta += steps;
	} theta = 0;

	//weave inner sides
	for (int i = 0; i < a_nSubdivisions-1; i++) {
		AddQuad(topInner[i], topInner[i + 1], baseInner[i], baseInner[i + 1]);
	} AddQuad(baseInner[0], baseInner[a_nSubdivisions-1], topInner[0], topInner[a_nSubdivisions-1]);

	//OUTER CIRCLE
	//generate points along circle
	for (int i = 0; i < a_nSubdivisions; i++) {
		baseOuter.push_back(vector3(cos(theta)*a_fOuterRadius, sin(theta)*a_fOuterRadius, 0));
		theta += steps;
	} theta = 0;

	//top outer ring
	//generate points along circle
	for (int i = 0; i < a_nSubdivisions; i++) {
		topOuter.push_back(vector3(cos(theta)*a_fOuterRadius, sin(theta)*a_fOuterRadius, a_fHeight));
		theta += steps;
	} theta = 0;

	//weave outer sides
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(baseOuter[i], baseOuter[i + 1], topOuter[i], topOuter[i + 1]);
	} AddQuad(topOuter[0], topOuter[a_nSubdivisions - 1], baseOuter[0], baseOuter[a_nSubdivisions - 1]);

	//CAP BASE
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(baseInner[i], baseInner[i + 1], baseOuter[i], baseOuter[i + 1]);
	} AddQuad(baseOuter[0], baseOuter[a_nSubdivisions - 1], baseInner[0], baseInner[a_nSubdivisions - 1]);


	//CAP TOP
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(topOuter[i], topOuter[i + 1], topInner[i], topInner[i + 1]);
	} AddQuad(topInner[0], topInner[a_nSubdivisions - 1], topOuter[0], topOuter[a_nSubdivisions - 1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector< std::vector<vector3> > rings;
	vector3 top;
	vector3 bottom;

	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	float theta2 = steps;
	float heightStep = a_fRadius / static_cast<float>(a_nSubdivisions);
	float height = heightStep;
	float numrings = 1;
	if(a_nSubdivisions > 2)
	numrings = a_nSubdivisions - 1;

	//top and bottom vertecies
	top = vector3(0, 0, a_fRadius / 2);
	bottom = vector3(0, 0, -a_fRadius / 2);

	//generate rings
	//generate points along circle
	for (int i = 0; i < numrings; i++) {
		rings.push_back(std::vector<vector3>());
		for (int j = 0; j < a_nSubdivisions; j++) {
			rings[i].push_back(vector3(cos(theta)*height, sin(theta)*height, height - (a_fRadius / 2.0)));
			theta += steps;
		} height += heightStep; theta2 += steps;
	} theta = 0;

	//weave rings
	for (int i = 0; i < numrings-1; i++) {
		for (int j = 0; j < a_nSubdivisions - 1; j++) {
			AddQuad(rings[i][j], rings[i][j + 1], rings[i+1][j], rings[i+1][j + 1]);
		} AddQuad(rings[i+1][0], rings[i+1][a_nSubdivisions - 1], rings[i][0], rings[i][a_nSubdivisions - 1]);
	}

	//CAP BOTTOM
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddTri(bottom, rings[0][i + 1], rings[0][i]);
	} AddTri(bottom, rings[0][0], rings[0][a_nSubdivisions - 1]);

	//CAP TOP
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddTri(top, rings[numrings-1][i], rings[numrings-1][i+1]);
	} AddTri(top, rings[numrings-1][a_nSubdivisions - 1], rings[numrings-1][0]);


	//Your code ends here
	CompileObject(a_v3Color);
}