
class C;

struct S{
	int x,y,z;
};

typedef S MS;

typedef int Myint;

enum E{
	x,y,z;
};

void Update( float f );

void Update( float *p );

void update2( const S *s );

void update3( const MS *s );

class C{
	public:
	
	C();
	
	C( int x );
	
	int x,y,z;
	
	virtual void update( float t );

	void render();
};

class D : public C{
	public:
	
	int d,e,f;
	
	virtual void update( float t );
};

float A,B,C;

