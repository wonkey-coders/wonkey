
@manpage Graphics

### Graphics and Rendering

@#### Canvases

All rendering in mojo is performed using [[Canvas]] objects.

To render to a canvas you use one of the drawing operations including:

* [[Canvas.DrawImage]] to draw an image to a canvas.

* [[Canvas.DrawPoint]], [[Canvas.DrawLine]], [[Canvas.DrawTriangle]], [[Canvas.DrawPoly]] to draw primitive shapes to a canvas.

You can also clear a canvas to a solid color using [[Canvas.Clear]].

Drawing operations aren't rendered immediately. They are queued so that as many as possible can be rendered at once. You can force any queued drawing operations to be rendered immediately using [[Canvas.Flush]].

A canvas also maintains a number of pieces of rendering state including:

* A viewport and scissor rect. See [[Canvas.Viewport]], [[Canvas.Scissor]].

* A transformation matrix. See: [[Canvas.Matrix]], [[Canvas.Translate]], [[Canvas.Scale]] and [[Canvas.Rotate]].

* A drawing color and alpha level. See: [[Canvas.Color]] and [[Canvas.Alpha]].

* A blend mode. See [[Canvas.BlendMode]].

This canvas state is applied to all drawing operations.

There are 2 ways to obtain a canvas object:

* You get passed a canvas object when a View's [[View.OnRender]] method is invoked. This canvas should be treated as temporary and is only valid until the OnRender method returns. The canvas is automatically flushed when OnRender returns so you don't have to do this yourself.

* You can also create a canvas for rendering directly to an image. In this case, it is important to flush the canvas once you have finished drawing to it.


@#### Images

An [[Image]] is a rectangular region of pixels that can be drawn to a canvas.

An image can be loaded from a file using the [[Image.Load]] function or constructed from a [[std:std.graphics.Pixmap|Pixmap]] object.

You can also render to an image using a canvas object.


@#### Fullscreen mode

To render fullscreen, you must place your apps main window into fullscreen mode. Use [[Window.BeginFullscreen]] to enter fullscreen mode and [[Window.EndFullscreen]] to leave fullscreen mode.


@#### Virtual resolution

You can also render at a fixed virtual (or 'logical') resolution, and allow mojo to scale up rendering operations to the actual resolution.

To do this, you need to change the window's [[View.Layout|layout mode]] to 'letterbox' and override the window's [[View.OnMeasure|OnMeasure]] method. For example:

```
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	'The resolution we want to use
	Const VirtualResolution:=New Vec2i( 256,128 )

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		Layout="letterbox"
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
	
		canvas.DrawText( "Chunky graphics!",Width/2,Height/2,.5,.5 )
	End
	
	Method OnMeasure:Vec2i() Override
		
		Return VirtualResolution
	End
	
End

Function Main()
	New AppInstance
	New MyWindow
	App.Run()
End
```


@#### 2D Lighting

A canvas also supports 2d lighting with bumpmapping and specular effects.

Light are 'drawn' using the [[Canvas.AddLight]] method, which can only be used when the canvas is in 'lighting mode'.

To put the canvas into lighting mode, use the [[Canvas.BeginLighting]] method. To end lighting mode, use the [[Canvas.EndLighting]] method. EndLighting is what actually renders the lighting, and will add lighting to any graphics rendered between BeginLighting and EndLighting.

AddLight takes an image parameter and is used in a very similar way to DrawImage. Light images can contain arbitrary colors and can be scaled, rotated etc. when drawn. However, images used for lighting should be loaded using the [[Image.LoadLight]] method.

You can not change the canvas viewport or scissor rect while the canvas is in lighting mode.
