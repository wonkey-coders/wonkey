
#rem


Quick quide to writing TCP client/server apps:


* Server:

1) Use Socket.Listen to create the server socket.

2) Use Socket.Accept in a loop to accept new clients.

3) Use Socket.Send and Socket.Receive to communicate with clients.


* Client:

1) Use Socket.Connect to connect to the listening server (must already be running!) and create a client socket.

2) Use Socket.Send and Socket.Receive to communicate with the server.


#end

#Import "<mojox>"
#Import "<mojo>"
#Import "<std>"

Using mojox..
Using mojo..
Using std..

Const HOST:="localhost"
Const PORT:=40122

Class MyWindow Extends Window

	Method New()
	
		New Fiber( Server )
		
		New Fiber( Client )
	End
	
	Method Server()
	
		Local server:=Socket.Listen( PORT )
		If Not server print "Server: Failed to create server" ; Return
		
		Print "Server @"+server.Address+" listening"
		
		server.SetOption( "SO_REUSEADDR",1 )

		server.SetOption( "TCP_NODELAY",1 )
		
		Repeat
		
			Local socket:=server.Accept()
			If Not socket Exit
			
			Print "Server accepted client @"+socket.PeerAddress
			
			Print "Server Connected="+Int( socket.Connected )
			
			Local stream:=New SocketStream( socket )
			
			New Fiber( Lambda()
			
				While Not stream.Eof
				
					Local line:=stream.ReadSizedString()
					If Not line Print "empty line!" ; Continue
					
					stream.WriteSizedString( line )

				Wend
				
				Print "Sever Eof"
				
				stream.Close()
				
			End )
		
		Forever
		
		Print "Server:Bye"
		
		server.Close()
	End
	
	Method Client()
	
		Fiber.Sleep( .5 )
	
		Local client:=Socket.Connect( HOST,PORT,SocketType.Stream )
		If Not client Print "Client: Couldn't connect to server" ; Return
		
		Print "Client @"+client.Address+" connected to server @"+client.PeerAddress
		
		Print "Client Connected="+Int(client.Connected)
		
		client.SetOption( "TCP_NODELAY",1 )
		
		Local stream:=New SocketStream( client )

		For Local i:=0 Until 100
		
			stream.WriteSizedString( "This is a number:"+i )
			
			Print "Reply:"+stream.ReadSizedString()
		Next
		
		Print "Client:Bye"
		
		stream.Close()
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		Global ticks:=0
		ticks+=1
		
		canvas.DrawText( ticks,0,0 )
	End
	
End

Function Main()

	New AppInstance
	New MyWindow
	App.Run()

End
