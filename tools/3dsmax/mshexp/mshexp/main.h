#ifndef _MAIN_H
#define _MAIN_H

#include "resource.h"
#include <Max.h>
#include <np.h>
#include <l3/gs.h>
#include <wincsl.h>

/*
	Max Plugin Class
*/
#define MSHEXP_VERSION   100 // 1.00
#define MSHEXP_CLASS_ID  Class_ID(0x57a01582, 0x1dfe55d2)

/*
	MshExp::TransformType
*/
#define TN_AFTER_WORLD    0x01
#define TN_BEFORE_WORLD   0x02
#define TN_TRANSFORM      0x03
#define TN_DEFAULT        0x04
#define TN_NO_TRANSLATION 0x100
#define TN_NO_ROTATION    0x200
#define TN_NO_SCALE       0x400

#define TN_DEFAULT        (TN_AFTER_WORLD|TN_NO_ROTATION)

/*
	DlgProc_ExportOptions messages
*/
#define UM_INITDIALOG_ADDOBJECT ((UINT)(WM_APP+1))

/*
	Windows fonctions
*/
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved);
INT_PTR CALLBACK DlgProc_ExportOptions(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

/*
	Max fonctions
*/
ClassDesc* GetMshExpDesc();
__declspec(dllexport) const TCHAR *LibDescription();
__declspec(dllexport) int LibNumberClasses();
__declspec(dllexport) ClassDesc *LibClassDesc(int i);
__declspec(dllexport) ULONG LibVersion();
__declspec(dllexport) ULONG CanAutoDefer();

/*
	Max Plugin descriptor
*/
class MshExpClassDesc : public ClassDesc
{
public:
    int           IsPublic();
	void*         Create(BOOL loading=FALSE);
	const TCHAR*  ClassName();
	SClass_ID     SuperClassID();
	Class_ID      ClassID();
	const TCHAR*  Category();
	const TCHAR*  InternalName();
	HINSTANCE     HInstance();
};

/*
	Max Plugin Class
*/
class MshExp : public SceneExport
{
	friend INT_PTR CALLBACK DlgProc_ExportOptions(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
public:
	MshExp();
	~MshExp();
	int           ExtCount();
	const TCHAR * Ext(int n);
	const TCHAR * LongDesc(); 
	const TCHAR * ShortDesc();
	const TCHAR * AuthorName();
	const TCHAR * CopyrightMessage(); 
	unsigned int  Version();
	int           DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
	const TCHAR * OtherMessage1();   // Other message #1
	const TCHAR * OtherMessage2();   // Other message #2
	void	      ShowAbout(HWND hWnd);  // Show DLL's "About..." box
	BOOL	      SupportsOptions(int ext, DWORD options);
	/* utils */
	TriObject*    GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt);
	Point3        GetVertexNormal(Mesh* mesh, Face* f, RVertex* rv);
	Matrix3       TransformNode(INode* pNode,TimeValue CurTime, int TransformType);//retourne la matrice utiliser pour la transformation en cours (m_TransformType)
	/* NP */
	int           ExportMesh(const TCHAR *filename,Interface* i,INode* node,TimeValue curtime=-1);
	DWORD         EnumObjects(HWND hDlg, UINT message, INode* pNode,SClass_ID sid,DLGPROC callback);
private:
	Interface *ip;//Interface en cours
	INode* exportNode;//noeud a exporter
	TimeValue exportTime;//frame a exporter
	int exportTransform;//transformation a effectuer sur l'objet
};

/*
	Globales
*/
BOOL controlsInit;
HINSTANCE hInstance;
static MshExpClassDesc MshExpCD;

/*
	3DS types
*/
LDESC Point3_t[]={
	{LDESC_FLOAT, "x"},
	{LDESC_FLOAT, "y"},
	{LDESC_FLOAT, "z"},
};

LDESC Normal_t[]={
	{LDESC_FLOAT, "nx"},
	{LDESC_FLOAT, "ny"},
	{LDESC_FLOAT, "nz"},
};

LDESC Face_t[]={
	{LDESC_INT, "a"},
	{LDESC_INT, "b"},
	{LDESC_INT, "c"},
};

LDESC TextureMap_t[]={
	{LDESC_FLOAT, "u"},
	{LDESC_FLOAT, "v"},
	{LDESC_FLOAT, "w"},
};

LDESC Color_t[]={
	{LDESC_FLOAT, "r"},
	{LDESC_FLOAT, "g"},
	{LDESC_FLOAT, "b"},
};

#endif
