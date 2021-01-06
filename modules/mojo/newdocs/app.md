
@manpage Application framework

### Application framework

@#### Initialization and the event loop

To initialize mojo, you need to do at least 3 things:

* Create an [[AppInstance]] using 'New AppInstance'. This will automatically initialize the [[App]] global variable.
* Create a [[Window]]. You will generally create a subclass of window you have defined yourself, eg: 'New MyWindow'.
* Start the app using [[AppInstance.Run|App.Run]].

This can all be done inside Main().

Once the app is running, mojo runs a simple event loop that looks like this:

* Get OS events and dispatch corresponding mojo events if necessary.
* Once there are no OS events left to process, any custom [[AppInstance.Idle|App.Idle]] handlers are called.
* If the application has called [[AppInstance.RequestRender|App.RequestRender]], the app is then rendered.

The app will continue executing the event loop until [[AppInstance.Terminate|App.Terminate]] is called.

@#### Subclassing Window

Subclassing the app Window class is easy - just extend the [[Window]] class.

To render to the window, you will also need to override the [[View.OnRender]] method. 

The OnRender method is called when the app needs to be rendered, and is passed a [[Canvas|Canvas]] instance for window rendering code to use.

In addition, you may also want to override the [[Window.OnWindowEvent]] method to handle window close, resize etc events.

@#### Handling user input

There are 2 main ways to handle user input, via the [[View.OnKeyEvent]] and [[View.OnMouseEvent]] event handlers or using the
[[input.Keyboard]] and [[input.Mouse]] devices.

Key and mouse events are sent to your app as soon they are processed by the event loop, while the keyboard and mouse devices may be 'polled' at
any time.


@#### A minimal mojo app.

Ok, time to put it all together!

@example

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Windows

	Method OnRender( canvas:Canvas ) Override

		canvas.DrawText( "Hello World",Width/2,Height/2,.5,.5 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

@end
