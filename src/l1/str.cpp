/*
    ---------------------------------------------------------------------------------------------------------------------------------------
    (C)2013 Thomas AUGUEY <contact@aceteam.org>
    ---------------------------------------------------------------------------------------------------------------------------------------
    This file is part of WebFrameWork.

    WebFrameWork is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WebFrameWork is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WebFrameWork.  If not, see <http://www.gnu.org/licenses/>.
    ---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "str.h"

/**
	@brief Rogne les caractères d'espacements et de saut de ligne (gauche et droite)
	@param up Pointeur sur le début de la chaine
	@param down Pointeur sur le début de la fin de chaine
	@remarks La chaine n'est pas modifiée, seul les pointeurs sont ajustés
*/
char* str_trimz( char* up  )
{
	PTR ptr = {up,up+strlen(up),up};
	str_trimz( &ptr  );
	return ptr.up;
}

/**
	@brief Rogne les caractères d'espacements et de saut de ligne (gauche et droite)
	@param up Pointeur sur le début de la chaine
	@param down Pointeur sur le début de la fin de chaine
	@remarks La chaine n'est pas modifiée, seul les pointeurs sont ajustés
*/
void str_trimz( PTR* ptr  )
{
	str_ltrim( ptr );
	*str_rtrim( ptr )='\0';
}

/**
	@brief Rogne les caractères d'espacements et de saut de ligne (gauche et droite)
	@param up Pointeur sur le début de la chaine
	@param down Pointeur sur le début de la fin de chaine
	@remarks La chaine n'est pas modifiée, seul les pointeurs sont ajustés
*/
void str_trim( PTR* ptr )
{
	str_ltrim( ptr );
	str_rtrim( ptr );
}

/**
	@brief Rogne les caractères d'espacements et de saut de ligne (gauche)
	@param up Pointeur sur le début de la chaine
	@param down Pointeur sur le début de la fin de chaine
	@return Pointeur sur le premier caractère "lisible" de la chaine
	@remarks La chaine n'est pas modifiée, seul le pointeur est ajusté
*/
char* str_ltrim( PTR* mem )
{
	//gauche
	while(*mem->up != 0 && mem->up < mem->down)
	{
		switch(*mem->up){
			case '\n':
			case '\r':
			case ' ':
			case '\t':
				break;
			default:
				if(mem->ptr<mem->up) mem->ptr = mem->up;
				return mem->up;
		}
		mem->up++;
	}
	
	return mem->up;
}

/**
	@brief Rogne les caractères d'espacements et de saut de ligne (droite)
	@param up Pointeur sur le début de la chaine
	@param down Pointeur sur le début de la fin de chaine
	@return Pointeur sur le dernier caractère "lisible" de la chaine
	@remarks La chaine n'est pas modifiée, seul le pointeur est ajusté
*/
char* str_rtrim( PTR* mem )
{
	//droite
	while(mem->down > mem->ptr)
	{
		switch(*(mem->down-1)){
			case '\n':
			case '\r':
			case ' ':
			case '\t':
			case '\0':
				mem->down--;
				break;
			default:
				if(mem->ptr>mem->down) mem->ptr = mem->down-1;
				return mem->down;
		}
	}
	
	return mem->down;
}

int strlen( char* up  ){
	int size=0;
	while(*up++!='\0')
		size++;
	return size;
}

/*calcule la taille d'un texte
char* strLength( char* up, char* down, size_t* psize )
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
}*/

/*
char* strWriteUInteger( char* up, char* down, unsigned int data)
{
	char* self = (char*)up;
	char* ptr;
	int div,arrondie;
	int size = 1; // nombre de caracteres
	int tmp;
	char c;

	// espace suffisant ?
	if(! (self < (char*)down))
		return 0;

	// compte les chiffres
	tmp = data;
	while(tmp >= 10)
	{
		tmp /= 10;
		size++;
	}
	
	// espace suffisant ?
	if(self+size >= (char*)down)
		return 0;

	// convertie la valeur
	ptr=self+size-1;
	self+=size;
	while(size && self<(char*)down)
	{
		// decale d'une dixaine
		div      = data / 10;
		// calcule la dixaine restante
		arrondie = div * 10;
		c = '0' + (data - arrondie);
		// passe a la valeur suivante
		data     = div;

//		*self++ = c;
		*ptr-- = c;
		size--;
	}
	
	// espace suffisant ?
	if(self+1 >= (char*)down)
		return 0;

	return self;
}
*/

/*
const char* strReadUInteger( const char* up, const char* down, unsigned int* data)
{
	const char* self = up;
	const char* ptr;
	int mul = 1;
	int value = 0;
	int size = 1; // nombre de caracteres
	
	// compte les chiffres
	size = 0;
	while((self[size] >= '0' && self[size] <= '9') && (self+size)<down)
	{
		size++;
	}

	// convertie la valeur
	ptr=self+size-1;
	self+=size;
	while(size)
	{
//		printf("read %c ",*self);
//		printf("%d*%d (%d) ",mul,((int)*self)-'0',(((int)*self)-'0') * mul);
		value += (((int)*ptr)-'0') * mul;
		mul *= 10;
		size--;
		*ptr--;
//		printf("\n");
	}
	
	// copie la valeur
	*data = value;

	return self;
}*/

/*
char* strWriteInteger( char* up, char* down, int data)
{
	char* self = (char*)up;
	char* ptr;
	int div,arrondie;
	int size = 1; // nombre de caracteres
	int tmp;
	char c;

	// espace suffisant ?
	if(! (self < (char*)down))
		return 0;

	// nombre negatif ?
	if(data < 0)
	{
		*self++ = '-';
		data = -data;
	}

	// compte les chiffres
	tmp = data;
	while(tmp >= 10)
	{
		tmp /= 10;
		size++;
	}
	
	// espace suffisant ?
	if(self+size >= (char*)down)
		return 0;

	// convertie la valeur
	ptr=self+size-1;
	self+=size;
	while(size && self<(char*)down)
	{
		// decale d'une dixaine
		div      = data / 10;
		// calcule la dixaine restante
		arrondie = div * 10;
		c = '0' + (data - arrondie);
		// passe a la valeur suivante
		data     = div;

//		*self++ = c;
		*ptr-- = c;
		size--;
	}

	// espace suffisant ?
	if(self+1 >= (char*)down)
		return 0;

//	*self++ = ';';

	return self;
}*/


/*
const char* strReadInteger( const char* up, const char* down, int* data)
{
	const char* self = up;
	const char* ptr;
	int mul = 1;
	int value = 0;
	int size = 1; // nombre de caracteres
	
	// negative ?
	if(*self == '-')
		self++;
	
	// compte les chiffres
	size = 0;
	while((self[size] >= '0' && self[size] <= '9') && (self+size)<down)
	{
		size++;
	}

	// convertie la valeur
	ptr=self+size-1;
	self+=size;
	while(size)
	{
//		printf("read %c ",*self);
//		printf("%d*%d (%d) ",mul,((int)*self)-'0',(((int)*self)-'0') * mul);
		value += (((int)*ptr)-'0') * mul;
		mul *= 10;
		size--;
		*ptr--;
//		printf("\n");
	}
	
	// negative ?
	//if((*self) != ';')
	//	return 0;

	// negative ?
	if(*up == '-')
		value = -value;

	// copie la valeur
	*data = value;

	return self;
}*/

/*
	strCopy
		Copie une chaine de caracteres

	Remaques:
		strCopy ne copie pas le caractere de terminaison '\0'

char* strCopy( char* up, char* down, const char* str )
{
	while(up<down && *str!=0)
		*up++ = *str++;
	if(*str!=0)
		return 0;
	return up;
}*/

/*
	strParse
		Parse la valeur des types C dans une chaine de caracteres

	Parametres:
		begin,end : plage memoire a initialiser
		txt       : chaine de format
		...       : arguments du format

	Arguments types:
		%i = int                  mot
		%d = unsigned int         mot non signe
		%s = short                mot court non signe
		%w = unsigned short       mot court
		%c = char                 byte non signe
		%b = unsigned char        byte
		%r = char*                bytes
		%a = char*                ascii string zero
		%p = void*                pointeur

char* strParse(char* begin,char* end,const char* txt,...)
{
	va_list list;
	int c = 0;
	uint uivalue;
	ushort usvalue;
	uchar ucvalue;
	int ivalue;
	short svalue;
	char cvalue;
	char* avalue;

	va_start(list, txt );

	while(*txt!=0 && begin<end)
	{
		// argument ?
		if(*txt == '%')
		{
			c = (int)*++txt;
			txt++;

			switch(c)
			{
				// string
				case 'a':
					avalue = va_arg(list, char*);
					begin = strCopy(begin,end,avalue);
					break;
				// unsigned integer
				case 'd':
					uivalue = va_arg(list, uint);
					begin = strWriteUInteger(begin,end,uivalue);
					break;
				// integer
				case 'i':
					ivalue = va_arg(list, int);
					begin = strWriteInteger(begin,end,ivalue);
					break;
				// unsigned short
				case 'w':
					usvalue = va_arg(list, uint);
					begin = strWriteUInteger(begin,end,(uint)usvalue);
					break;
				// short
				case 's':
					svalue = va_arg(list, short);
					begin = strWriteInteger(begin,end,(int)svalue);
					break;
				// unsigned char
				case 'b':
					ucvalue = va_arg(list, uchar);
					begin = strWriteUInteger(begin,end,(uint)ucvalue);
					break;
				// char
				case 'c':
					cvalue = va_arg(list, char);
					begin = strWriteInteger(begin,end,(int)cvalue);
					break;
				// bytes
				case 'r':
					begin = strCopy(begin,end,"[!b]");
					break;
				// pointeur
				case 'p':
					begin = strCopy(begin,end,"[!p]");
					break;
				default:
					begin = strCopy(begin,end,"[?]");
					break;
			}
			if(begin == 0)
			{
				*begin++ = '!';
				return 0;
			}
		}
		//sinon, copie le texte
		else
		{
			*begin++ = *txt++;
		}
	}
	
	va_end(list);

	return begin;
}
*/

/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(str, str_ltrim) {
    char value[] = " \n\r\tHello World";
	//BPTR(ptr,value,sizeof(value));
	PTR ptr={value,value+sizeof(value),value};

    char* ofs = str_ltrim(&ptr);
    ASSERT_STREQ("Hello World", ofs) << "str_ltrim";
}

TEST(str, str_rtrim) {
    char value[] = "Hello World \n\r\t";
	PTR ptr={value,value+sizeof(value),value};

    *str_rtrim(&ptr) = '\0'; // tronque definitivement
    ASSERT_STREQ("Hello World", value) << "str_rtrim";
}

TEST(str, str_trim) {
    char value[] = " \n\r\tHello World \n\r\t";
	PTR ptr={value,value+sizeof(value),value};

    str_trim(&ptr);
	*ptr.down = '\0';
    ASSERT_STREQ("Hello World", ptr.ptr) << "Should be equal";
}

TEST(str, str_trimz) {
    char value[] = " \n\r\tHello World \n\r\t";
	PTR ptr={value,value+sizeof(value),value};

    str_trimz(&ptr);
    ASSERT_STREQ("Hello World", ptr.up) << "Should be equal";
}
#endif
