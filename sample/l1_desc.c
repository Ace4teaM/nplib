
#include <np.h>
#include <string.h>

/* local strucutre */
typedef struct _Point3
{
	int x,z,y;
}Point3;

typedef struct _Point4
{
	int x,y,z;
	float w;
}Point4;

LDESC Point3_t[]={
	{LDESC_INT, "x"},
	{LDESC_INT, "z"},
	{LDESC_INT, "y"},
};

LDESC Point4_t[]={
	{LDESC_INT, "x"},
	{LDESC_INT, "y"},
	{LDESC_INT, "z"},
	{LDESC_FLOAT, "w"},
};

void test2()
{
	char data[200];
	void* cur = data;
	void* end = data+sizeof(data);
	Point4 pnt = {1,2,3,123.123f};
	Point3 pnt3;

	//ecrit
	cur = data;
	cur = descWriteStruct(cur,end,Point4_t,sizeof(Point4_t)/sizeof(Point4_t[0]),&pnt);
	fileWrite("point.pf",0,data,(char*)cur);

	//lit
	cur = data;
	memset(&pnt,0,sizeof(pnt));
	descReadStruct(cur,end,Point3_t,sizeof(Point3_t)/sizeof(Point3_t[0]),&pnt3);
	printf("point3 = %d %d %d\n",pnt3.x,pnt3.y,pnt3.z);
}

void test1()
{
	char data[200];
	void* cur = data;
	void* end = data+sizeof(data);
	LDESC desc;
	int iv;
	float fv;

	/* ecrit le descripteur portable */
	cur = descWriteByte( cur,end, DESC_INT );
	cur = descWriteText( cur,end, "x" );
	cur = descWriteByte( cur,end, DESC_INT );
	cur = descWriteText( cur,end, "y" );
	cur = descWriteByte( cur,end, DESC_INT );
	cur = descWriteText( cur,end, "z" );
	cur = descWriteByte( cur,end, DESC_REAL );
	cur = descWriteText( cur,end, "w" );
	cur = descWriteByte( cur,end, 0xff );
	
	/* ecrit les donnees de la structure */
	cur = ldescIntToNumber(cur,end,1200);
	cur = ldescIntToNumber(cur,end,1020);
	cur = ldescIntToNumber(cur,end,1002);
	cur = ldescFloatToNumber(cur,end,-14.123456789f,10);
	
	/* ecrit les donnees de la structure */
	fileWrite("test.pf",0,data,(char*)cur);
	
	/*
		relit la structure
	*/
	cur = data;

	/* descripteurs */
	while( *(unsigned char*)cur != 0xff )
	{
		cur = descReadByte( cur,end, &desc.type );
		desc.name = (char*)cur;
		cur = descReadText( cur,end, 0, 0 );

		printf("read %s (%d)\n",desc.name,desc.type);
	}
	cur = ((char*)cur)+1;
	printf("end of desc.\n");
	
	/* ecrit les donnees de la structure */
	cur = descNumberToInt(cur,end,&iv);
	printf("int = %d\n",iv);
	cur = descNumberToInt(cur,end,&iv);
	printf("int = %d\n",iv);
	cur = descNumberToInt(cur,end,&iv);
	printf("int = %d\n",iv);
	cur = descNumberToFloat(cur,end,&fv);
	printf("float = %f\n",fv);
	
}

void test3()
{
	char data[200];
	void* cur = data;
	void* end = data+sizeof(data);

	cur = strParse(cur,end,"hello to NoyauPortable %i %a %s %c.",(int)456,"coucou",(short)456,(char)120);
	*(char*)cur=0;
	puts(data);
}

int main()
{
	NP_LOG("hello to NoyauPortable");
	test2();
	
	return 0;
}
