
Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
Using opengl..

Class MyWindow Extends GLWindow

	Method New()
		Super.New( "GL Window",640,480,WindowFlags.Resizable )

		'Disable default window clearing - we're clearing ourselves.
		'
		'This is necessary if you're using a depth/stencil buffer. If not, you can just
		'use normal ClearColor property.
		'
		ClearEnabled=False
		
	End
	
	Protected
	
	'You don't need to implement this, but it allows you to combine opengl/mojo rendering.
	'
	Method OnRender( canvas:Canvas ) Override

		'Can move this to OnRenderGL if you want.
		'
		App.RequestRender()

		'This will result in OnRenderGL being called.
		'
		Super.OnRender( canvas )
		
		'Do some mojo rendering!
		'
		canvas.DrawText( "FPS="+App.FPS,Width,0,1,0 )
		canvas.DrawText( "Mojo Rendering+OpenGL rendering!",Width/2,Height/2,.5,.5 )
	End

	'GL rendering code goes here...
	'
	Method OnRenderGL() Override

		'Clear window ourselves...
		'	
		glClearColor( 0,0,1,1 )
		
		glClearDepth( 0 )
		
		glClearStencil( 0 )
		
		glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT )


		'Drawing area. You're always drawing to the entire window in GL regardless of Layout.
		'
		'Don't really need this for this example is it only affects glDrawBlah, but nice to know...
		'
		glViewport( 0,0,Frame.Width,Frame.Height )

		
		'Shader-less rect
		'
		glEnable( GL_SCISSOR_TEST )

		glScissor( Mouse.X-32,Frame.Height-Mouse.Y-32,64,64 )

		glClearColor( 1,0,0,1 )

		glClear( GL_COLOR_BUFFER_BIT )

		glDisable( GL_SCISSOR_TEST )
		
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
