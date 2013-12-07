
char* filedata = 0;


/*
 definitions des formes
*/

typedef struct 
{
	int left;
	int right;
	int top;
	int bottom;
}MAP;

/* 2D */
typedef struct 
{
	int x;
	int y;
}POSITION;

typedef struct 
{
	int radius;
}CIRCLE;

typedef struct 
{
	int width;
	int height;
}RECTANGLE;

typedef struct 
{
	int length;
}SQUARE;

/* 3D */

typedef struct 
{
	int x;
	int y;
	int z;
}POINT;

typedef struct 
{
	int radius;
}SPHERE;

typedef struct 
{
	int width;
	int height;
	int depth;
}BOX;

typedef struct 
{
	int length;
}CUBE;

typedef struct DESC
{
		unsigned char type;
		char* name;
}DESC;

typedef struct 
{
		void* func;
		char* name;
}FUNC;

/* interface definition */
typedef struct INTERFACE
{
	char* name;
	struct {
		DESC desc;
	}*desc;
	struct func{
		void* func;
		char* name;
	}func[1];
}INTERFACE;

int map_draw(MAP* map);

/* src */
int toTop(void* args)
{
	struct ARGS
	{
		int y;
	}*self=(ARGS*)args;

	self->y = 0;
}


int map_draw(MAP* map)
{
	return 0;
}

int main()
{
	return 0;
}
