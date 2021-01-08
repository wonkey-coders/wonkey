
#rem

Quick guide to writing UDP client/server apps:

* Server:

1) Create server socket using Socket.Bind (not Listen!).

2) Wait for client messages using Socket.ReceiveFrom.

3) Use the SocketAddress filled in by ReceiveFrom to determine the client the message is from.

4) Use the same SocketAddress with Socket.SendTo to reply to the client.


* Client:

1) Connect to server using Socket.Connect with SocketType.Stream as the last parameter.

2) Communicate with the server using Socket.Send and Socket.Receive.

#end

#Import "<mojox>"
#Import "<mojo>"
#Import "<std>"

Using mojox..
Using mojo..
Using std..

Const HOST:="localhost"	'Note: Use "" for 'public' host.
Const PORT:=40123

Class MyWindow Extends Window

	Method New()
	
		New Fiber( Server )
		
		
		For Local i:=0 Until 5
			New Fiber( Client )
		Next
	End
	
	Method Server()
	
		Local server:=Socket.Bind( PORT )
		If Not server print "Server: Failed to create server" ; Return
		
		Print "Server @"+server.Address+" ready"
		
		server.SetOption( "SO_REUSEADDR",1 )
		
		'To keep track of connected clients...
		Local clients:=New Map<SocketAddress,Int>
		
		Local addr:=New SocketAddress
				
		Repeat
		
			Local data:Int
			
			If server.ReceiveFrom( Varptr data,4,addr )<>4 Exit
			
			Print "Server received msg:"+data+" from client @"+addr
			
			'check if client exists
			If Not clients[addr]
				Local id:=clients.Count()+1
				clients[ New SocketAddress( addr ) ]=id
				Print "New Client! id="+id
			Endif
			
			data=-data
				
			server.SendTo( Varptr data,4,addr )

		Forever
		
		server.Close()
		
	End
	
	Method Client()
	
		Global _id:Int
		
		_id+=1
		
		Local id:=_id
	
		Fiber.Sleep( .5 )	'wait a bit for server to start
		
		Local client:=Socket.Connect( HOST,PORT,SocketType.Datagram )
		If Not client Print "Client("+id+"): Couldn't connect to server" ; Return
		
		Print "Client("+id+") @"+client.Address+" connected to @"+client.PeerAddress
		
		Local address:=New SocketAddress
		
		For Local i:=0 Until 10
		
			Fiber.Sleep( Rnd( .2,.4 ) )
		
			Local data:Int=i*10
			
			client.Send( Varptr data,4 )
			
			If client.Receive( Varptr data,4 )<>4 Exit
			
			Print "Client("+id+") received reply:"+data+" from server"
			
		Next
		
		Print "Client("+id+") finished!"
		
	End
	
	Method OnRender( canvas:Canvas ) Override
	
'		App.RequestRender()
		
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
