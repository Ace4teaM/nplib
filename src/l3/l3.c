
struct _NP_RESOURCE
{
	NP_IDENTIFIER name;
}NP_RESOURCE;


int npCreateRessource(char* name)
{
	NP_RESOURCE* res = (NP_RESOURCE*)npLockHandle(0,sizeof(NP_RESOURCE));
	if(res==0)
		return 0;

	npMakeIdentifier(&res->id,name);

	return npUnlockHandle(0,sizeof(NP_RESOURCE));
}
