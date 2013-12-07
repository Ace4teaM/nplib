#include <stdio.h>
#include <np.h>

int main()
{
	int wnd = npCreateObject();

	SetColor(wnd,"bg",255,255,0);
	SetColor(wnd,"border",0,0,0);
	SetAttribute(wnd,"borderRadius","10px");

	npObject* obj = LockObject(wnd,"bg border");
	makeRGB(obj->att[0].data,obj->att[0].data+sizeof(RGB),0,0,0);
	makeRGB(obj->att[1].data,obj->att[1].data+sizeof(RGB),0,0,0);

	return 0;
}
