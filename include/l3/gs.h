/*
--------------------------------------------------------------------------------------------
	2D types
--------------------------------------------------------------------------------------------
*/
typedef struct _gsPosOffset
{
	int x,y;
}gsPosOffset;

LDESC gsPosOffset_t[]={
	{LDESC_INT, "x"},
	{LDESC_INT, "y"},
};

typedef struct _gsPos
{
	float x,y;
}gsPos;

LDESC gsPos_t[]={
	{LDESC_FLOAT, "x"},
	{LDESC_FLOAT, "y"},
};

/*
--------------------------------------------------------------------------------------------
	3D types
--------------------------------------------------------------------------------------------
*/

typedef struct _gsPointOffset
{
	int x,y,z;
}gsPointOffset;

LDESC gsPointOffset_t[]={
	{LDESC_INT, "x"},
	{LDESC_INT, "y"},
	{LDESC_INT, "z"},
};

typedef struct _gsPoint3
{
	float x,y,z;
}gsPoint;

LDESC gsPoint_t[]={
	{LDESC_FLOAT, "x"},
	{LDESC_FLOAT, "y"},
	{LDESC_FLOAT, "z"},
};

/*
--------------------------------------------------------------------------------------------
	Image types
--------------------------------------------------------------------------------------------
*/

typedef struct _gsColor
{
	float r,g,b;
}gsColor;

LDESC gsColor_t[]={
	{LDESC_FLOAT, "r"},
	{LDESC_FLOAT, "g"},
	{LDESC_FLOAT, "b"},
};

typedef struct _gsColorIntensity
{
	float i;
}gsColorIntensity;

LDESC gsColorIntensity_t[]={
	{LDESC_FLOAT, "i"},
};

/*
--------------------------------------------------------------------------------------------
	Objects
--------------------------------------------------------------------------------------------
*/

typedef struct _gsMesh
{
	int vertices_count;
	int hVerticesList;
}gsMesh;

typedef struct _gsImage
{
	int width;
	int height;
	int hPixelsList;
}gsImage;
