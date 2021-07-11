Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<timelinefx>"
#Import "assets/toonCloud.png"

Using std..
Using mojo..
Using timelinefx..

Class MyWindow Extends Window

	Field GameObject:tlGameObject
	Field ChildObject:tlGameObject

	Method New( title:String="tlGameObject example",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		'Create a couple of new game objects
		GameObject = New tlGameObject
		ChildObject = New tlGameObject
		
		'Assign images using LoadShape
		GameObject.Image = LoadShape("asset::toonCloud.png")
		ChildObject.Image = LoadShape("asset::toonCloud.png")
		
		'Position the child object. This will be relative to the parent object.
		ChildObject.SetPosition(0, 200)
		'Scale it down a bit
		ChildObject.SetScale(0.5)
		
		'Add the child object to the parent object
		GameObject.AddChild(ChildObject)
		'Set the parent position 
		GameObject.SetPosition(width/2, height/2)
		'Update the gameobject to make sure everything is initialised in the correct positions
		GameObject.Update()
		
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		canvas.Clear( New Color(0,0,0,1) )
		
		'Rotate the parent object to show that the child stays relative
		GameObject.Rotate(0.05)
		'Update the game object
		GameObject.Update()
		'Render the game object
		GameObject.Render(canvas)
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
