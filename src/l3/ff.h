/*
--------------------------------------------------------------------------------------------
	Standard header
--------------------------------------------------------------------------------------------
*/
typedef struct _ffHeader
{
	char filetype[64];
	int high_version;
	int lower_version;
	int revision;
}ffHeader;

LDESC ffHeader_t[]={
	{LDESC_TEXT, "filetype"},
	{LDESC_INT, "high_version"},
	{LDESC_INT, "lower_version"},
	{LDESC_INT, "revision"},
};
