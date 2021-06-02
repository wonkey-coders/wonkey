#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Field mapw:Int,maph:Int
	Field map:Int[,]
	Field sx:Int,sy:Int,ex:Int,ey:Int
	Field find:Bool=True
	Field findstate:String="start"
	Field findsubstate:String=""
	Field nomoreflood:Bool=False
	Field findsx:Int,findsy:Int,findex:Int,findey:Int
	Field findcurx:Int,findcury:Int
	Field findcnum:Int
	Field scale:Float=26
	Method New()
		mapw = 16
		maph = 16
		sx = 5 ; sy = 5 ; ex = 12 ; ey = 12
		map = New Int[mapw,maph]
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		If find = True Then findpath()
		
		' draw the numbers of the currently flooded area
		For Local y:Int=0 Until maph
		For Local x:Int=0 Until mapw
			If map[x,y] > 0
				canvas.Color=Color.White
				canvas.DrawText(map[x,y],x*scale,y*scale)
			End If
		Next
		Next
		' draw the edges of the flood area
		canvas.DrawLine(findsx*scale,findsy*scale,findex*scale+scale,findsy*scale)
		canvas.DrawLine(findsx*scale,findey*scale+scale,findex*scale+scale,findey*scale+scale)
		canvas.DrawLine(findsx*scale,findsy*scale,findsx*scale,findey*scale+scale)
		canvas.DrawLine(findex*scale+scale,findsy*scale,findex*scale+scale,findey*scale+scale)
		
		'draw start and end
		canvas.Color = Color.Red
		canvas.DrawCircle(sx*scale,sy*scale,scale/3)
		canvas.DrawCircle(ex*scale,ey*scale,scale/3)
		
		
		' draw the cursor
		canvas.Color = Color.Blue
		canvas.DrawRect(findcurx*scale,findcury*scale,scale,scale)
		
		' Draw the info
		canvas.Color = Color.White
		canvas.DrawText(findstate,0,0)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	'
	Method findpath()
		If findstate="start"
			map[ex,ey] = 1
			findcnum = 1
			findsx = ex-1 ; findsy = ey-1 ; findex = ex+1 ; findey = ey+1
			findcurx = ex-1 ; findcury = ey-1
			findstate="flood"
			findsubstate=""
			nomoreflood=False
			Return
		End If


		If findstate="flood"

		Local tmp:Int = map[findcurx,findcury]
		If  tmp = findcnum								
			If findcurx>0 And findcurx<mapw-1 And findcury>0 And findcury<maph-1
				If map[findcurx,findcury-1] = 0  Then map[findcurx,findcury-1] = tmp+1;nomoreflood=False
				If map[findcurx-1,findcury] = 0  Then map[findcurx-1,findcury] = tmp+1;nomoreflood=false
				If map[findcurx+1,findcury] = 0  Then map[findcurx+1,findcury] = tmp+1;nomoreflood=false
				If map[findcurx,findcury+1] = 0  Then map[findcurx,findcury+1] = tmp+1;nomoreflood=false
			End If
		End If

						
			findcurx += 1
			If findcurx = findex Then 
				If findcury = findey Then 
					
					If nomoreflood = True
						findstate="Done.."
						Return
					End If
					nomoreflood=True
					
					If findsubstate=""
						findsx-=1;findsy-=1;findex+=1;findey+=1
						If findsx<0 Then findsx=0
						If findsy<0 Then findsy=0					
						If findex>=mapw Then findex = mapw
						If findey>=maph Then findey = maph					
					End If
					findcurx = findsx
					findcury = findsy
					findcnum+=1
					If findsx=0 And findsy=0 And findex=mapw And findey=maph Then 
						findsubstate = "finish off"
					End If
					Return
				End If
				findcurx = findsx
				findcury += 1				
			End If
		End If
	End Method
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
