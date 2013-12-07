#include <l1/desc.h>
#include <l1/str.h>
#include <math.h>
#include <float.h>
#include <string.h>

void* descMake(void* begin, void* end, ...)
{
	void* cur = begin;
	va_list list;
	/* element */
	unsigned char type;
	size_t length;
	const char* name;

	va_start(list, end );
	
	/* lit les elements */
	while( (name = va_arg(list, const char*)) != 0 )
	{
		type   = va_arg(list, unsigned char);
		length = va_arg(list, size_t);
		
		/* nom */
		if((cur = descWriteText(cur,end,"hello world")) == 0)
			return 0;

		/* type */
		if((cur = descWriteByte(cur,end,DESC_INT)) == 0)
			return 0;
		
		/* taille */
		if((cur = descWriteSize(cur,end,length)) == 0)
			return 0;
	}
	va_end(list);
	
	return cur;
}

//ecrit un texte
void* descWriteText( void* up, void* down, const char* text )
{
	char* self = (char*)up;

	/* nom */
	while((self < (char*)down) && (*text!=0))
	{
		*self++ = *text++;
	}
	
	/* tampon insuffisant pr contenir le texte */
	if(*text!=0)
		return 0;

	*self++ = 0;

	return self;
}

//ecrit un texte
void* descReadText( void* up, void* down, char* text, size_t size )
{
	char* self = (char*)up;

	/* lit l'integralite du texte */
	while((self < (char*)down) && (*self!=0))
	{
		/* copie si possible */
		if(size){
			*text++ = *self++;
			size--;
		}
		else
			self++;
	}

	/* fin de tampon */
	if(text!=0)
		*text = 0;
	
	return ++self;
}

//ecrit des donnees 
void* descWriteRaw( void* up, void* down, const unsigned char* raw, size_t size )
{
	unsigned char* self = (unsigned char*)up;
	
	if(!size)
		return 0;

	/* nom */
	while((self < (unsigned char*)down) && size)
	{
		*self++ = *raw++;
		size--;
	}

	if(size!=0)
		return 0;
	
	return self;
}

//ecrit des donnees 
void* descWriteByte( void* up, void* down, unsigned char byte )
{
	char* self = (char*)up;
	
	if(self >= (char*)down)
		return 0;

	/* nom */
	*self++ = byte;

	return self;
}

//ecrit des donnees 
void* descReadByte( void* up, void* down, unsigned char* byte )
{
	char* self = (char*)up;
	
	if(self >= (char*)down)
		return 0;

	/* nom */
	*byte = *self++;

	return self;
}

//ecrit des donnees 
void* descReadRaw( void* up, void* down, unsigned char* out, size_t size )
{
	unsigned char* self = (unsigned char*)up;
	
	if(!size)
		return 0;

	/* nom */
	while((self < (unsigned char*)down) && size)
	{
		*out++ = *self++;
		size--;
	}

	if(size!=0)
		return 0;
	
	return self;
}

//taille en bytes
void* descWriteSize(void* up, void* down,size_t size/*,size_t* bytes_count*/)
{
	unsigned char* bytes = (char*)up;

	// ecrit les bytes
	while(size>=255 &&  (bytes<(char*)down))
	{
		*bytes++ = 0xff;
		size -= 0xff;
	}
	
	// ajoute le reste
	if(bytes>=(char*)down)
		return 0;
	*bytes++ = (unsigned char)size;

	return bytes;
}

//bytes en taille
void* descReadSize(void* up, void* down,size_t* psize)
{
	unsigned char* bytes = (char*)up;
	size_t size = 0;
	
	// additionne les bytes
	while((bytes<(char*)down) && ((*bytes) == 0xff))
	{
		bytes++;
		size+=0xff;
	}
	
	// ajoute le reste
	if(bytes>=(char*)down)
		return 0;
	size += (*bytes);

	//retourne la taille 
	*psize = size;
	
	return bytes+1;
}

void* descReadNumber( void* up, void* down, int* pvalue)
{
	char* self = (char*)up;
	int mul = 1;
	int value = 0;
	
	/* negative ? */
	if(*self == '-')
		self++;

	/* convertie la valeur */
	while((*self >= '0' && *self <= '9') && self<(char*)down)
	{
//		printf("read %c ",*self);
//		printf("%d*%d (%d) ",mul,((int)*self)-'0',(((int)*self)-'0') * mul);
		value += (((int)*self)-'0') * mul;
		mul *= 10;
		//size--;
		*self++;
//		printf("\n");
	}
	
	/* negative ? */
	if(*(char*)up == '-')
		value = -value;

	/* copie la valeur */
	*pvalue = value;

	return self;
}

void* descWriteNumber( void* up, void* down, int value)
{
	char* self = (char*)up;
	int div,arrondie;
	int size = 1; /* nombre de caracteres */
	int tmp;
	char c;

	/* espace suffisant ? */
	if(! (self < (char*)down))
		return 0;

	/* nombre negatif ? */
	if(value < 0)
	{
		*self++ = '-';
		value = -value;
	}

	/* compte les chiffres */
	tmp = value;
	while(tmp >= 10)
	{
		tmp /= 10;
		size++;
	}
	
	/* espace suffisant ? */
	if(self+size >= (char*)down)
		return 0;

	/* convertie la valeur */
	while(size && self<(char*)down)
	{
		/* decale d'une dixaine */
		div      = value / 10;
		/* calcule la dixaine restante */
		arrondie = div * 10;
		c = '0' + (value - arrondie);
		/* passe a la valeur suivante */
		value    = div;

		*self++ = c;
		size--;
	}
	
	/* espace suffisant ? */
	if(self+1 >= (char*)down)
		return 0;

	return self;
}

void* descWriteInteger( void* up, void* down, char* data, size_t size)
{
	char* self = (char*)up;
	
	/* espace suffisant ? */
	if(self+size >= (char*)down)
		return 0;
	
	/* copie les donnees */
	switch(ENDIAN_THIS)
	{
		case ENDIAN_LITTLE:
			while(size)
			{
				*self++ = *data++;
				size--;
			}
			break;

		case ENDIAN_BIG:
			data+=size-1;
			while(size)
			{
				*self++ = *data--;
				size--;
			}
			break;

		case ENDIAN_MIDDLE:
			return 0;
	}

	return self;
}

void* descReadInteger( void* up, void* down, char* data, size_t size)
{
	char* self = (char*)up;
	
	/* espace suffisant ? */
	if(self+size >= (char*)down)
		return 0;

	/* copie les donnees */
	switch(ENDIAN_THIS)
	{
		case ENDIAN_LITTLE:
			while(size)
			{
				*data++ = *self++;
				size--;
			}
			break;

		case ENDIAN_BIG:
			data+=size-1;
			while(size)
			{
				*data-- = *self++;
				size--;
			}
			break;

		case ENDIAN_MIDDLE:
			return 0;
	}

	return self;
}

void* descWriteInt( void* up, void* down, int value)
{
	return descWriteInteger(up,down,(char*)&value,sizeof(value));
}

void* descWriteUInt( void* up, void* down, unsigned int value)
{
	return descWriteInteger(up,down,(char*)&value,sizeof(value));
}

void* descReadInt( void* up, void* down, int* value)
{
	return descWriteInteger(up,down,(char*)value,sizeof(int));
}

void* descReadUInt( void* up, void* down, unsigned int* value)
{
	return descWriteInteger(up,down,(char*)value,sizeof(unsigned int));
}

/*
	local descriptor
	
	Convertion du format standard => portable
*/

void* ldescIntToNumber( void* up, void* down, int value)
{
	char* self = (char*)descWriteNumber( up, down, value);
	*self++ = 0;//fin de nombre

	return self;
}

void* descNumberToInt( void* up, void* down, int* pvalue)
{
	char* self = (char*)descReadNumber( up, down, pvalue);
	*self++;//fin de nombre

	return self;
}

void* ldescFloatToNumber( void* up, void* down, float value, int precision)
{
	char* self = (char*)up;
	float low,high;

	if(!precision)
		precision=FLT_DIG;

	high = (float)(int)value;
	low  = (float)value-high;
	//printf("high/low=%f/%f\n",high,low);
	//low = modf((double)value,&high); //modff bug

	while(precision--)
	{
		low *= 10.0;
	}

	if(low<0.0)
		low = -low;//_chgsign(low);

	//printf("ldescFloatToNumber=%d.%d\n",(int)high,(int)low);

	self = (char*)descWriteNumber( up, down, (int)high);
	*self++ = '.';//separateur
	self = (char*)descWriteNumber( self, down, (int)low);
	*self++ = 0;//fin de nombre

	return self;
}
/*
void* ldescFloatToNumber( void* up, void* down, float value, int precision)
{
	char* self = (char*)up;
	int dec,sign;
	char* buf;

	buf=_ecvt(value,DBL_DIG,&dec,&sign);
	if(sign)
		*self++ = '-';
	while(dec--)
		*self++ = *buf++;
	*self++ = '.';
	while(*buf!=0)
		*self++ = *buf++;

	return self;
}*/

void* descNumberToFloat( void* up, void* down, float* pvalue)
{
	char* self = (char*)up;
	int low,high,precision;

	self = (char*)descReadNumber( self, down, &high);
	*self++;//separateur
	precision = (int)self;
	self = (char*)descReadNumber( self, down, &low);
	precision = (int)self-precision;
	*self++;//fin de nombre
	
	if(high<0)
		*pvalue = (float)((float)high-((float)low/(float)pow(10,precision)));
	else
		*pvalue = (float)((float)high+((float)low/(float)pow(10,precision)));

	/*printf("descNumberToFloat=%d.%d=>%d (%f)\n",high,low,precision,*pvalue);*/

	
	return self;
}

void* descWriteStruct(void* up,void* down,LDESC* desc,int count,void* _structData)
{
	char* structData=(char*)_structData;
	while(count--)
	{
		switch(desc->type)
		{
			/*case LDESC_CHAR:
				up = descWriteByte(up,down, DESC_INT);
				up = ldescCharToNumber(up,down,*(char*)structData);
				structData+=sizeof(int);
				break;
			case LDESC_LONG:
				up = descWriteByte(up,down, DESC_INT);
				up = ldescLongToNumber(up,down,*(long*)structData);
				structData+=sizeof(int);
				break;*/
			case LDESC_INT:
				up = descWriteByte(up,down, DESC_NUMBER);
				up = descWriteText(up,down, desc->name);
				up = descWriteSize(up,down, 0);
				up = ldescIntToNumber(up,down,*(int*)structData);
				structData+=sizeof(int);
				break;
			case LDESC_FLOAT:
				up = descWriteByte(up,down, DESC_REAL);
				up = descWriteText(up,down, desc->name);
				up = descWriteSize(up,down, 0);
				up = ldescFloatToNumber(up,down,*(float*)structData,0);
				structData+=sizeof(float);
				break;
		}

		desc++;
	}

	return up;
}

int descReadStruct(void* up,void* down,LDESC* ldesc,int count,void* _structData)
{
	char* structData=(char*)_structData;
	void* cur;
	int findDesc;
	DESC desc;
	while(count--)
	{
		cur = up;
		findDesc = 0;

		while((cur = descReadByte(cur,down, &desc.type))!=0 && desc.type!=DESC_END && !findDesc)
		{
			desc.name = (char*)cur;
			cur = descReadText(cur,down, 0,0);
			cur = descReadSize(cur,down, &desc.size);
			//charge les donnees?
			if(strcmp(ldesc->name,desc.name)==0)
			{
				switch(ldesc->type)
				{
					case LDESC_INT:
						if(desc.type == DESC_NUMBER)
							descNumberToInt(cur,down,(int*)structData);
						else
							return 0;
						structData+=sizeof(int);
						break;
					case LDESC_FLOAT:
						if(desc.type == DESC_REAL)
							descNumberToFloat(cur,down,(float*)structData);
						else
							return 0;
						structData+=sizeof(float);
						break;
				}

				//ok
				findDesc=1;
				continue;
			}
			//saute les donnees
			if(desc.size==0)//text
				cur = descReadText(cur,down, 0,0);
			else
				cur = (char*)cur + desc.size;
		}

		if(!findDesc)
			return 0;

		//suivant
		ldesc++;
	}

	return 1;
}
