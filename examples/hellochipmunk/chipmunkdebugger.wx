
#Import "<std>"
#Import "<mojo>"
#Import "<chipmunk>"

Using std..
Using mojo..
Using chipmunk..

Class ChipmunkDebugger

	Method New()
		_options.drawCircle=DrawCircle
		_options.drawSegment=DrawSegment
		_options.drawFatSegment=DrawFatSegment
		_options.drawPolygon=DrawPolygon
		_options.drawDot=DrawDot
		_options.colorForShape=ColorForShape
		_options.flags=CP_SPACE_DEBUG_DRAW_SHAPES '|CP_SPACE_DEBUG_DRAW_CONSTRAINTS|CP_SPACE_DEBUG_DRAW_COLLISION_POINTS
	End
	
	Method DebugDraw( canvas:Canvas,space:cpSpace )
	
		_canvas=canvas
		
		canvas.OutlineMode=OutlineMode.Smooth
		
		canvas.OutlineWidth=3
	
		cpSpaceDebugDraw( space,_options )
	End
	
	Protected
	
	Method DrawCircle( pos:cpVect,angle:cpFloat,radius:cpFloat,outlineColor:cpSpaceDebugColor,fillColor:cpSpaceDebugColor,data:cpDataPointer )
	
		_canvas.OutlineColor=New Color( outlineColor.r,outlineColor.g,outlineColor.b )
		
		_canvas.Color=New Color( fillColor.r,fillColor.g,fillColor.b )

		_canvas.DrawCircle( pos.x,pos.y,radius )
		
		_canvas.Color=Color.Black
		
		_canvas.DrawLine( pos.x,pos.y,pos.x+Cos( angle )*radius,pos.y+Sin( angle )*radius )
	End
	
	Method DrawSegment( a:cpVect,b:cpVect,color:cpSpaceDebugColor,data:cpDataPointer )

		_canvas.Color=New Color( color.r,color.g,color.b )

		_canvas.LineWidth=1
				
		_canvas.DrawLine( a.x,a.y,b.x,b.y )
	End
	
	Method DrawFatSegment( a:cpVect,b:cpVect,radius:cpFloat,outlineColor:cpSpaceDebugColor,fillColor:cpSpaceDebugColor,data:cpDataPointer )

		_canvas.OutlineColor=New Color( outlineColor.r,outlineColor.g,outlineColor.b )
		
		_canvas.Color=New Color( fillColor.r,fillColor.g,fillColor.b )

		_canvas.LineWidth=radius
		
		_canvas.DrawLine( a.x,a.y,b.x,b.y )
	End
	
	Method DrawPolygon( count:Int,verts:cpVect Ptr,radius:cpFloat,outlineColor:cpSpaceDebugColor,fillColor:cpSpaceDebugColor,data:cpDataPointer )
	
		Local vs:=New Float[count*2]
		For Local i:=0 Until count
			vs[i*2]=verts[i].x
			vs[i*2+1]=verts[i].y
		Next
		
		_canvas.OutlineColor=New Color( outlineColor.r,outlineColor.g,outlineColor.b )
		
		_canvas.Color=New Color( fillColor.r,fillColor.g,fillColor.b )
		
		_canvas.DrawPolys( count,1,vs )
	End
	
	Method DrawDot( size:cpFloat,pos:cpVect,color:cpSpaceDebugColor,data:cpDataPointer )

		_canvas.Color=New Color( color.r,color.g,color.b )

		_canvas.PointSize=size
		
		_canvas.DrawPoint( pos.x,pos.y )
	End
	
	Method ColorForShape:cpSpaceDebugColor( shape:cpShape,data:cpDataPointer )
	
		Local color:=_colors[shape]
		If color.a Return color
		
		color.r=Rnd( 1 )
		color.g=Rnd( 1-color.r )
		color.b=Rnd( 1-color.r-color.g )
		color.a=1
		
		_colors[shape]=color
		Return color
	End
	
	Private
	
	Field _options:=New cpSpaceDebugDrawOptions
	
	Field _colors:=New Map<cpShape,cpSpaceDebugColor>

	Field _canvas:Canvas
	
End
