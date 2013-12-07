#include <l1/desc.h>

//calcule la taille d'un texte
void* strLength( char* up, char* down, size_t* psize )
{
	size_t size = 0;

	while(*up!=0 && up<down)
	{
		size++;
		up++;
	}
	
	*psize = size;

	if(*up!=0)
		return 0;

	return up;
}

void* strWriteInteger( void* up, void* down, int data)
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
	if(data < 0)
	{
		*self++ = '-';
		data = -data;
	}

	/* compte les chiffres */
	tmp = data;
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
		/* decale la dixaine du nombre */
		div      = data / 10;
		/* calcule la dixaine restante */
		arrondie = div * 10;
		c = '0' + (data - arrondie);
		/* passe a la valeur suivante */
		data     = div;

		*self++ = c;
		size--;
	}
	
	/* espace suffisant ? */
	if(self+1 >= (char*)down)
		return 0;

	*self++ = ';';

	return self;
}

void* strReadInteger( void* up, void* down, int* data)
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
		//printf("read %c ",*self);
			//printf("%d*%d (%d) ",mul,((int)*self)-'0',(((int)*self)-'0') * mul);
			value += (((int)*self)-'0') * mul;
			mul *= 10;
		//size--;
		*self++;
		//printf("\n");
	}
	
	/* negative ? */
	if((*self) != ';')
		return 0;

	/* negative ? */
	if(*(char*)up == '-')
		value = -value;

	/* copie la valeur */
	*data = value;

	return self;
}

void* strCopy( char* up, char* down, char* str )
{
	while(up<down && *str!=0)
		*up++ = *str++;
	if(*str!=0)
		return 0;
	return up;
}
