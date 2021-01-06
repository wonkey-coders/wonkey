
#include <std/filesystem/native/filesystem.h>

namespace wxMusic{

	int playMusic( FILE *file,int callback,int source );
	
	int getBuffersProcessed( int source );
	
	void endMusic( int source );
	
}
