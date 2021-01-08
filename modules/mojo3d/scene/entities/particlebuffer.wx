
Namespace mojo3d

Class ParticleBuffer

	Method New( length:Int=15000 )
	
		_length=length

		_vbuffer=New VertexBuffer( Vertex3f.Format,_length )
		
		_uniforms=New UniformBlock( 4,true )
		
		Local vertices:=_vbuffer.Lock()
		libc.memset( vertices,0,_vbuffer.Length*_vbuffer.Pitch)
		_vbuffer.Invalidate()
		_vbuffer.Unlock()

		Gravity=New Vec3f( 0,-9.81,0 )
		Duration=5.0
		Fade=0.0			
		Colors=New Color[]( Color.White )		
		ConeAngle=30		
		MinVelocity=20.0	
		MinVelocity=24.0	
		MinSize=8.0			
		MaxSize=12.0		
	End

	Property Length:Int()
	
		Return _length
	End

	Property Gravity:Vec3f()
	
		Return _uniforms.GetVec3f( "Gravity" )
	
	Setter( gravity:Vec3f )
	
		_uniforms.SetVec3f( "Gravity",gravity )
	End
	
	Property Duration:Float()
	
		Return _duration
	
	Setter( duration:Float )
	
		_uniforms.SetFloat( "Duration",duration )
		
		_duration=duration
	End
	
	Property Fade:Float ()
	
		Return _uniforms.GetFloat( "Fade" )
		
	Setter( fade:Float )
	
		_uniforms.SetFloat( "Fade",fade )
	End
	
	Property Colors:Color[]()

		Return _colors
		
	Setter( colors:Color[] )
	
		If Not colors colors=New Color[]( Color.White )
	
		_colors=colors
	End
	
	Property ConeAngle:Float()
	
		Return _coneAngle
	
	Setter( angle:Float )
		Assert( angle>0 And angle<180,"Cone angle must be in the range (0,180)" )
	
		_coneAngle=angle
	End
	
	Property MinVelocity:Float()
	
		Return _minVelocity
	
	Setter( velocity:Float )
	
		_minVelocity=velocity
	End
	
	Property MaxVelocity:Float()
	
		Return _maxVelocity
	
	Setter( velocity:Float )
	
		_maxVelocity=velocity
	End
	
	Property MinSize:Float()
	
		Return _minSize
	
	Setter( size:Float )
	
		_minSize=size
	End
	
	Property MaxSize:Float()
	
		Return _maxSize
	
	Setter( size:Float )
	
		_maxSize=size
	End
	
	
	Internal
	
	Method OnRender( rq:RenderQueue,material:Material,instance:Entity )
	
		Local time:=rq.Time

		If Not _time
			_time=time
			Return
		Endif
		
		Local frames:=Int( (time-_time) * 60 )
		
		If frames

			Local n:=Min( Int( Float(_length)/60.0/_duration * frames ),_length )
			
			local timeStep:=frames * (1.0/60.0) / n
			
			Local vertices:=Cast<Vertex3f Ptr>( _vbuffer.Lock() )
			
			For Local i:=0 Until n
			
				AddParticle( vertices,_time )
				
				_time+=timeStep
				
			Next
			
			_vbuffer.Invalidate()
			
			_vbuffer.Unlock()

		Endif
		
		rq.AddRenderOp( material,_uniforms,instance,_vbuffer,Null,Boxf.FullBounds,1,_length,0 )
	End		
	
	Private
	
	Field _length:Int
	Field _vbuffer:VertexBuffer
	Field _uniforms:UniformBlock
	Field _duration:Float
	
	Field _colors:Color[]
	Field _coneAngle:Float
	Field _minVelocity:Float
	Field _maxVelocity:Float
	Field _minSize:Float
	Field _maxSize:Float
	
	Field _time:Float
	Field _index:Int

	Method AddParticle( vertices:Vertex3f Ptr,time:Float )
	
		Local vertex:=vertices+_index
		
		_index=(_index+1) Mod _length
		
		Local r:=Rnd( -Pi,Pi )
		Local d:=Rnd( 0,Tan( _coneAngle*.5*TwoPi/360.0 ) )
		
		Local dir:=New Vec3f( Cos( r ) * d,Sin( r ) * d,1.0 ).Normalize()
		
		Local velocity:=dir * Rnd( _minVelocity,_maxVelocity )

		vertex->position=velocity											'velocity
		vertex->texCoord0=New Vec2f( time,Rnd( _minSize,_maxSize ) )		'time, size
		vertex->tangent=_colors[ Rnd( _colors.Length ) ]					'color
	End
	
End

