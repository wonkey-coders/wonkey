
#ifndef WX_MOJO_INPUT_KEYINFO_H
#define WX_MOJO_INPUT_KEYINFO_H

struct wxKeyInfo{
	const char *name;
	int scanCode;
	int keyCode;
};

extern wxKeyInfo wxKeyInfos[];

#endif
