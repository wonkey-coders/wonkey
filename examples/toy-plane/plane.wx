Namespace plane

#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"

#Import "source/PlaneControl"

#Import "textures/"
#Import "models/"

Using std..
Using mojo..
Using mojo3d..

Class MyWindow Extends Window
	
	Field _res :Vec2i
	
	Field _scene:Scene
	Field _camera:Camera
	Field _light:Light
'	Field _fog:FogEffect
	
	Field _water:Model
	Field _plane:Model
	Field _pivot:Model		'Needs to be a Model instead of Entity otherwise the plane isn't rendered!
		
	Field _camTarget:Entity
	Field test:Model
	
	
	Method New()
		Super.New( "Toy Plane", 1280, 720, WindowFlags.Resizable )' | WindowFlags.HighDPI  )
		_res = New Vec2i( Width, Height )
		Print _res
		Layout = "fill"
		
		_scene=New Scene
		_scene.SkyTexture=Texture.Load( "asset::miramar-skybox.jpg",TextureFlags.FilterMipmap|TextureFlags.Cubemap )
		_scene.EnvTexture = _scene.SkyTexture
		_scene.FogColor = New Color(0.69, 0.78, 0.82, 0.3 )
		_scene.FogFar = 5000
		_scene.FogNear = 1
		
		'create light
		_light=New Light
		_light.Rotate( 45, 45, 0 )
		_light.CastsShadow = True
		
		'create water material
		Local waterMaterial:=New WaterMaterial
		
		waterMaterial.ScaleTextureMatrix( 300,300 )
		waterMaterial.ColorFactor=New Color( 0.025, 0.125, 0.15 )
		waterMaterial.Roughness=0
		
		waterMaterial.NormalTextures=New Texture[]( 
			Texture.Load( "asset::water_normal0.png",TextureFlags.WrapST | TextureFlags.FilterMipmap ),
			Texture.Load( "asset::water_normal1.png",TextureFlags.WrapST | TextureFlags.FilterMipmap ) )
		
		waterMaterial.Velocities=New Vec2f[]( 
			New Vec2f( .01,.03 ),
			New Vec2f( .02,.05 ) )
		
		'create water
		_water=Model.CreateBox( New Boxf( -10000,-1,-10000,10000,0,10000 ),1,1,1,waterMaterial )
		
		'create bloom
		Local _bloom := New BloomEffect( 2 )
		_scene.AddPostEffect( _bloom )
		
		'create main pivot
		_pivot = New Model
		
		'create airplane
		_plane = Model.LoadBoned( "asset::plane/plane.gltf" )
		_plane.Animator.Animate( 0 )
		_plane.Parent = _pivot
		_plane.Position = New Vec3f
		
'		Local matrix := New AffineMat4<Float>
'		_plane.Rotate( 0, 180, 0)
'		_plane.Mesh.TransformVertices( matrix )
		
'		Local mat := Cast<PbrMaterial>( _plane.Material )
'		Local mat := New PbrMaterial( Color.LightGrey, 0.1, 0.1, True )
'		Local tex := Texture.Load( "asset::plane_Oc.png", TextureFlags.FilterMipmap )
'		mat.OcclusionTexture = tex
		
		Print _plane.Materials.Length
		Print ( _plane.Material? "true" Else "False" )
'		_plane.Material = mat
		
		'create camera target
		_camTarget = New Pivot( _pivot )
'		_camTarget = Model.CreateSphere( 0.25, 12, 12, New PbrMaterial( Color.Red ) )
'		_camTarget.Parent = _plane
		_camTarget.Position = New Vec3f( 0, 0, -10 )

		'create camera
		_camera=New Camera( _pivot )
		_camera.View = Self
		_camera.Near=.1
		_camera.Far=10000
		_camera.FOV = 75
		_camera.Move( 0,3,8 )
		
		'Control component
		Local control := _pivot.AddComponent<PlaneControl>()
		control.plane = _plane
		control.camera = _camera
		control.target = _camTarget

		_pivot.Position = New Vec3f( 0, 6, 0 )
		
'		Local ball := Model.CreateSphere( 2, 24, 24, New PbrMaterial( Color.Red, 0.1, 0.25 ) )
'		ball.Move( 0, 4, 0)
	End
	
	
	Method OnRender( canvas:Canvas ) Override
		RequestRender()
		_water.Position=New Vec3f( Round(_camera.Position.x/2000)*2000,0,Round(_camera.Position.z/2000)*2000 )
		_camera.PointAt( _camTarget.Position )
		_scene.Update()
		_camera.Render( canvas )
		canvas.DrawText( "Width="+Width+", Height="+Height+", FPS="+App.FPS + "    Aspect=" + _camera.Aspect,0,0 )
	End
	
	
	Method OnMeasure:Vec2i() Override
		Return _res
	End
	
End

Function Main()
	New AppInstance
	New MyWindow
	App.Run()
End
