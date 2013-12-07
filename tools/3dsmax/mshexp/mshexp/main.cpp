
#include "main.h"

/*---------------------------------------------------------------------------------------------------
	Entry point
---------------------------------------------------------------------------------------------------*/
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			controlsInit=FALSE;

			hInstance = hinstDLL;

			// Initialise les custom controls
			if (!controlsInit) {
				controlsInit = TRUE;
				InitCommonControls();
			}

			// Initialise la console de debuguage
			winlogInit();
			NP_LOG("--= Mesh Export Log =--");
			break;

		case DLL_PROCESS_DETACH:
			NP_LOG("unload plugin");
			// Libere la console de debuguage
			winlogFree();
			break;
	}

	return TRUE;
}


/*---------------------------------------------------------------------------------------------------
	Max Fonctions
---------------------------------------------------------------------------------------------------*/

ClassDesc* GetMshExpDesc()
{
	return &MshExpCD;
}

// Description de la librairie
__declspec(dllexport) const TCHAR *LibDescription()
{
	return _T("NP Mesh Export");
}

// Retourne le nombre de classes pour cette librairie
__declspec(dllexport) int LibNumberClasses()
{
	return 1;
}

// Retourne les descripteurs des classes pour cette librairie
__declspec(dllexport) ClassDesc *LibClassDesc(int i)
{
	switch(i) {
	case 0:
		return GetMshExpDesc();
	default:
	  return 0;
	}
}

// Version de 3DStudioMax utilise par le plugin
__declspec(dllexport) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

// chargement differe ?
__declspec(dllexport) ULONG CanAutoDefer()
{
	return 1;
}

/*---------------------------------------------------------------------------------------------------
	Max Plugin descriptor
---------------------------------------------------------------------------------------------------*/
int           MshExpClassDesc::IsPublic()                 { return TRUE; }
void*         MshExpClassDesc::Create(BOOL loading)       { return new MshExp; }
const TCHAR*  MshExpClassDesc::ClassName()                { return _T("NP Mesh Export"); }
SClass_ID     MshExpClassDesc::SuperClassID()             { return SCENE_EXPORT_CLASS_ID; }
Class_ID      MshExpClassDesc::ClassID()                  { return MSHEXP_CLASS_ID; }
const TCHAR*  MshExpClassDesc::Category()                 { return _T("File Export"); }
const TCHAR*  MshExpClassDesc::InternalName()             { return _T("MshExp"); }
HINSTANCE     MshExpClassDesc::HInstance()                { return hInstance; } 

/*---------------------------------------------------------------------------------------------------
	MshExp Class
---------------------------------------------------------------------------------------------------*/

// Constructeur
MshExp::MshExp()
{
	this->ip              = 0;
	this->exportTransform = TN_AFTER_WORLD|TN_NO_TRANSLATION;
	this->exportTime      = -1;
}

// Destructeur
MshExp::~MshExp()
{
}

// Autre message 1
const TCHAR * MshExp::OtherMessage1()
{
	return _T("");
}

// Autre message 2
const TCHAR * MshExp::OtherMessage2()
{
	return _T("");
}

// A propos
void MshExp::ShowAbout(HWND hWnd)
{
}

// Options suplementaire par extention
BOOL MshExp::SupportsOptions(int ext, DWORD options)
{
	return 0;
}

// Retourne le nombre d'extention supporter par le type de fichier
int MshExp::ExtCount()
{
	return 1;
}

// Retourne le texte des extentions supporter par le type de fichier
const TCHAR * MshExp::Ext(int n)
{
	switch(n) {
	case 0:
		return _T("msh");
	}
	return _T("");
}

// Description long
const TCHAR * MshExp::LongDesc()
{
	return _T("NoyauPortable Mesh File Exporter");
}

// Description court
const TCHAR * MshExp::ShortDesc()
{
	return _T("NoyauPortable Mesh");
}

// Nom de l'auteur
const TCHAR * MshExp::AuthorName() 
{
	return _T("Thomas Auguey");
}

// Copyright
const TCHAR * MshExp::CopyrightMessage() 
{
	return _T("Copyright 2011 - ID-Informatik, all right reserved.");
}

// Version du plugin
unsigned int MshExp::Version()
{
	return MSHEXP_VERSION;
}

// Exporte le fichier
int MshExp::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts/*=FALSE*/, DWORD options/*=0*/)
{
	this->ip = i;//pointeur sur l'interface

	if(DialogBoxParam(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),ip->GetMAXHWnd(),DlgProc_ExportOptions, (LPARAM)this))
	{
		//Ecrit le fichier
		this->ExportMesh(name,this->ip,this->exportNode);
	}
	return 1;
}

Matrix3 MshExp::TransformNode(INode* pNode,TimeValue CurTime, int TransformType){
	Matrix3 mat;

	switch((TransformType&0xff))
	{
		case TN_AFTER_WORLD://After World
			mat = pNode->GetObjTMAfterWSM(CurTime);
			break;
		case TN_BEFORE_WORLD://Before World
			mat = pNode->GetObjTMBeforeWSM(CurTime);
			break;
		case TN_TRANSFORM:
			mat = pNode->GetNodeTM(CurTime);
			break;
		default:
			mat = Matrix3(1);
			break;
	}

	if(TransformType&TN_NO_TRANSLATION)
		mat.NoTrans();
	if(TransformType&TN_NO_ROTATION)
		mat.NoRot();
	if(TransformType&TN_NO_SCALE)
		mat.NoScale();

	return mat;
}

// Retourne un pointeur TriObject du INode ou retourne NULL
// si le node ne peut pas etre convertie en TriObject
TriObject* MshExp::GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt)
{
	deleteIt = FALSE;
	Object *obj = node->EvalWorldState(t).obj;
	if(obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
	{
		TriObject *tri = (TriObject *) obj->ConvertToType(t,Class_ID(TRIOBJ_CLASS_ID, 0));
		// Note that the TriObject should only be deleted
		// if the pointer to it is not equal to the object
		// pointer that called ConvertToType()
		if (obj != tri)
			deleteIt = TRUE;
		return tri;
	}
	else
	{
		return NULL;
	}
}

Point3 MshExp::GetVertexNormal(Mesh* mesh, Face* f, RVertex* rv)
{
//	Face* f = &mesh->faces[faceNo];
	DWORD smGroup = f->smGroup;
	int numNormals;
	Point3 vertexNormal;
	
	// Is normal specified
	// SPCIFIED is not currently used, but may be used in future versions.
	if (rv->rFlags & SPECIFIED_NORMAL) {
		vertexNormal = rv->rn.getNormal();
	}
	// If normal is not specified it's only available if the face belongs
	// to a smoothing group
	else if ((numNormals = rv->rFlags) & NORCT_MASK && smGroup) {
		// If there is only one vertex is found in the rn member.
		if (numNormals == 1) {
			vertexNormal = rv->rn.getNormal();
		}
		else {
			// If two or more vertices are there you need to step through them
			// and find the vertex with the same smoothing group as the current face.
			// You will find multiple normals in the ern member.
			for (int i = 0; i < numNormals; i++) {
				if (rv->ern[i].getSmGroup() & smGroup) {
					vertexNormal = rv->ern[i].getNormal();
				}
			}
		}
	}
	else {
		// Get the normal from the Face if no smoothing groups are there
		vertexNormal = mesh->getFaceNormal(0);//!
	}
	
	return vertexNormal;
}

DWORD MshExp::EnumObjects(HWND hDlg, UINT message, INode* pNode,SClass_ID sid,DLGPROC callback)
{
	DWORD count = 0;
	ObjectState os;
	TimeValue curTime = this->ip->GetTime();
	
	if(pNode==0)
		pNode = this->ip->GetRootNode();

	//base
	os = pNode->EvalWorldState(curTime);
	if((os.obj) && (os.obj->SuperClassID() == sid))
	{
		callback(hDlg,message,(LPARAM)count,(WPARAM)pNode);
		count++;
	}
	//enfants
	for(int i=0;i<pNode->NumberOfChildren();i++)
	{
		count += this->EnumObjects(hDlg,message,pNode->GetChildNode(i),sid,callback);
	}
	return count;
}

static INT_PTR CALLBACK DlgProc_ExportOptions(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static MshExp *pMshExp;
	
	/* controls */
	static HWND hcombobox_objet;
	static HWND hcheckMatTranslate;
	static HWND hcheckMatRotate;
	static HWND hcheckMatScale;
	
	static INode* pSelNode;
	static int nSelNode;//numero de l'objet selectionne dans le comboBox

	switch(message)
	{
	case WM_INITDIALOG:
		{
			pMshExp = (MshExp *)lParam;
			
			hcombobox_objet     = GetDlgItem(hDlg,IDC_COMBO_GEOM_OBJECT);
			hcheckMatTranslate  = GetDlgItem(hDlg,IDC_CHECK4);
			hcheckMatRotate     = GetDlgItem(hDlg,IDC_CHECK5);
			hcheckMatScale      = GetDlgItem(hDlg,IDC_CHECK3);

			/*
				Obtient la selection
			*/
			pSelNode = pMshExp->ip->GetSelNode(0);
			nSelNode = 0;//numero de l'objet selectionne dans le comboBox

			/*
				Initialise la liste des objets exportable
			*/
			NP_LOG("initialise la liste des objets exportable...");
			if(!pMshExp->EnumObjects(hDlg,UM_INITDIALOG_ADDOBJECT,NULL,GEOMOBJECT_CLASS_ID,DlgProc_ExportOptions))
			{
				MessageBox(hDlg,"No object geometric object for export !","Warning",0);
				return EndDialog(hDlg, 1);
			}

			/*
				Initialise les controles
			*/
			//assigne l'objet selectionne au combo box
			SendMessage(hcombobox_objet, CB_SETCURSEL, nSelNode, NULL);
			
			//Active les divers composant de la transformation 
			SendMessage(hcheckMatTranslate, BM_SETCHECK, (WPARAM)BST_UNCHECKED, NULL);
			SendMessage(hcheckMatRotate, BM_SETCHECK, (WPARAM)BST_CHECKED, NULL);
			SendMessage(hcheckMatScale, BM_SETCHECK, (WPARAM)BST_CHECKED, NULL);

			//initialise le dialogue
			CenterWindow(hDlg,GetParent(hDlg));
			SetFocus(hDlg); // For some reason this was necessary.  DS-3/4/96
		}
		return FALSE;

		/*
			Insert un objet a la liste des 
		*/
	case UM_INITDIALOG_ADDOBJECT:
		{
			NP_LOG("UM_ADDOBJECT");
			DWORD count  = (DWORD)wParam;
			INode* pNode = (INode*)lParam;
			int nItem = (int)SendMessage(hcombobox_objet, CB_ADDSTRING, 0, (LPARAM)pNode->GetName());
			if(pSelNode == pNode)
				nSelNode = nItem;
		}
		break;

	case WM_DESTROY:
		return FALSE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			{
				char buf[1024];
				INode* exportNode;

				//node
				unsigned int cursel = SendMessage(hcombobox_objet, CB_GETCURSEL, 0, (LPARAM)0);
				SendMessage(hcombobox_objet,CB_GETLBTEXT,(WPARAM)cursel,(LPARAM)buf);
				exportNode = pMshExp->ip->GetINodeByName(buf);
				if(!exportNode){
					MessageBox(hDlg,"Please select object for export !","Warning",0);
					return 0;
				}
				
				pMshExp->exportNode = exportNode;

				/* Transformation Type
				pMshExp->m_TransformType = SendMessage(hcbTransformType, CB_GETCURSEL, 0, 0);
				sprintf(buf,"%s",str_transform_type[pMshExp->m_TransformType]);
				npDebugMsg("TransformType",buf);*/
				//Composant de la transformation 
				/*if(SendMessage(hcheckMatTranslate, BM_GETCHECK, NULL, NULL)==BST_CHECKED)
					pMshExp->m_UseMatrix_Trans = 1;
				else pMshExp->m_UseMatrix_Trans = 0;
				if(SendMessage(hcheckMatRotate, BM_GETCHECK, NULL, NULL)==BST_CHECKED)
					pMshExp->m_UseMatrix_Rotate = 1;
				else pMshExp->m_UseMatrix_Rotate = 0;
				if(SendMessage(hcheckMatScale, BM_GETCHECK, NULL, NULL)==BST_CHECKED)
					pMshExp->m_UseMatrix_Scale = 1;
				else pMshExp->m_UseMatrix_Scale = 0;*/

				EndDialog(hDlg, 1);
			}
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
	}
	return FALSE;
}
/*
int MshExp::ExportMeshTiles(Interface* ip,INode* node,TimeValue t_start,TimeValue t_end,int tiles_count)
{
	// Get animation range
	Interval animRange = ip->GetAnimRange();

	TimeValue curtime;

	curtime = animRange.Start();
}
*/
int MshExp::ExportMesh(const TCHAR *filename,Interface* i,INode* node,TimeValue curtime)
{
	char buf[4096];
	void* cur=buf;
	void* end=buf+sizeof(buf);

	// Verifie les arguments
	if(node==0){
		NP_LOG("ExportMesh: !node");
		return 0;
	}
	
	/*-----------------------------------------------------
		Obtient l'objet Mesh
	-----------------------------------------------------*/

	// Frame a exporter
	if(curtime<0)
		curtime = i->GetTime();
	
	// Obtient la matrice de transformation
	Matrix3 tm = TransformNode(node,curtime,this->exportTransform);

	// Evalue l'objet a partir du noeud
	ObjectState os = node->EvalWorldState(curtime);
	if(!os.obj || os.obj->SuperClassID()!=GEOMOBJECT_CLASS_ID){
		NP_LOG("ExportMesh: !ObjectState");
		return 0;
	}
	Interval objRange = os.obj->ObjectValidity(curtime);

	// convertie l'objet en Tiangles
	BOOL needDel;
	TriObject* tri = GetTriObjectFromNode(node, curtime, needDel);
	if (!tri) {
		NP_LOG("ExportMesh: !TriObject");
		return 0;
	}
	// obtient le maillage
	Mesh* mesh = &tri->GetMesh();

	// obtient le nombre de points
	uint npoint=(uint)mesh->getNumVerts();

	// construit les normals
	mesh->buildNormals();

	// obtient le nombre de faces
	uint nfaces=(uint)mesh->getNumFaces();
	
	//Supprime l'objet TriObject, si necessaire
	if(needDel) {
		delete tri;
	}

	/*-----------------------------------------------------
		Exporte les triangles
	-----------------------------------------------------*/
	
	//Obtient la matrice de transformation
	tm = TransformNode(node,curtime,this->exportTransform);

	// Evalue l'objet a partir du node
	os = node->EvalWorldState(curtime);
	objRange = os.obj->ObjectValidity(curtime);

	// convertie l'objet en Tiangles
	tri = GetTriObjectFromNode(node, curtime, needDel);
	if (!tri) {
		NP_LOG("ExportMesh: !TriObject");
		return 0;
	}
	// obtient le maillage
	mesh = &tri->GetMesh();
	// construit les normals
	mesh->buildNormals();

	// copie les faces
	for(uint y=0; y<nfaces; y++)
	{
		Face* face;
		uint facenumber=0;//numero de la face dans l'index du maillage 3DS

		//obtient la face en cours
		face = &mesh->faces[y];
		facenumber = y;
		
		//////////////////////////////////////////////
		// Definit les 3 points de la face
		//////////////////////////////////////////////
		for(uint w=0;w<3;w++)
		{
			if((cur = descWriteText(cur,end,"point")==0)
				return 0;

			Point3 pos;
			Point3 nml;
			Point3 clr;
			UVVert tex;
			uint nvertex;

			// obtient le point
			nvertex = face->v[w];
			pos = tm * mesh->verts[nvertex];
			float point[3]={pos.x,pos.y,pos.z};
			if((cur = descWriteStruct(cur,end,Point3_t,sizeof(Point3_t)/sizeof(Point3_t[0]),&point))==0)
				return 0;

			// obtient les normals
			nvertex = face->getVert(w);
			nml = GetVertexNormal(mesh, face, mesh->getRVertPtr(nvertex));
			float normal[3]={nml.x,nml.y,nml.z};
			if((cur = descWriteStruct(cur,end,Normal_t,sizeof(Normal_t)/sizeof(Normal_t[0]),&normal))==0)
				return 0;

			// obtient les coordonnees de texture
			if(mesh->tvFace){
				nvertex = mesh->tvFace[facenumber].t[w];
				tex = mesh->tVerts[nvertex];
				float textureMap[3]={tex.x,tex.y,tex.z};
				if((cur = descWriteStruct(cur,end,TextureMap_t,sizeof(TextureMap_t)/sizeof(TextureMap_t[0]),&textureMap))==0)
					return 0;
			}

			// obtient la couleur
			if(mesh->vcFace){
				nvertex = mesh->vcFace[facenumber].t[w];
				clr = mesh->vertCol[nvertex];
				float color[3]={clr.x,clr.y,clr.z};
				if((cur = descWriteStruct(cur,end,Color_t,sizeof(Color_t)/sizeof(Color_t[0]),&color))==0)
					return 0;
			}
		}
	}

	//Supprime l'objet TriObject, si necessaire
	if(needDel) {
		delete tri;
	}
	
	/* ecrit les donnees de la structure */
	if(!fileWrite(filename,0,buf,(char*)cur))
		return 0;
	
	NP_LOG("done");

	return 1;
}
