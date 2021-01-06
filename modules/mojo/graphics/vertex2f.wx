
Namespace mojo.graphics

Struct Vertex2f
	
	Const Format:=New Vertex2fFormat
	
	Const Pitch:=28

	Field position:Vec2f
	Field texCoord0:Vec2f
	Field texCoord1:Vec2f
	Field color:UInt
	
	Method New()
	End
	
	Method New( x:Float,y:Float,s0:Float=0,t0:Float=0,s1:Float=0,t1:Float=0,color:UInt=~0 )
		position.x=x
		position.y=y
		texCoord0.x=s0
		texCoord0.y=t0
		texCoord1.x=s1
		texCoord1.y=t1
		Self.color=color
	End
	
	Method New( position:Vec2f,texCoord0:Vec2f=Null,texCoord1:Vec2f=Null,color:UInt=~0 )
		Self.position=position
		Self.texCoord0=texCoord0
		Self.texCoord1=texCoord1
		Self.color=color
	End
	
	Operator To:String()
		Return "Vertex2f("+position+")"
	End
	
End

Class Vertex2fFormat Extends VertexFormat
	
	Property Pitch:Int() Override
		
		Return Vertex2f.Pitch
	End

	Method UpdateGLAttribs() Override
		glEnableVertexAttribArray( A_POSITION ) ; glVertexAttribPointer( A_POSITION,2,GL_FLOAT,False,Pitch,Cast<Void Ptr>( 0 ) )
		glEnableVertexAttribArray( A_TEXCOORD0 ) ; glVertexAttribPointer( A_TEXCOORD0,2,GL_FLOAT,False,Pitch,Cast<Void Ptr>( 8 ) )
		glEnableVertexAttribArray( A_TEXCOORD1 ) ; glVertexAttribPointer( A_TEXCOORD1,2,GL_FLOAT,False,Pitch,Cast<Void Ptr>( 16 ) )
		glEnableVertexAttribArray( A_COLOR ) ; glVertexAttribPointer( A_COLOR,4,GL_UNSIGNED_BYTE,True,Pitch,Cast<Void Ptr>( 24 ) )
		'Need these to shut up android emulator.
		glDisableVertexAttribArray( A_NORMAL )
		glDisableVertexAttribArray( A_TANGENT )
		glDisableVertexAttribArray( A_WEIGHTS )
		glDisableVertexAttribArray( A_BONES )
	End
	
End
