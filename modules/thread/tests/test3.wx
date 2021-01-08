
#Rem

Little demo showing how to add things to a queue for a thread to process.

#End

Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<thread>"

Using std..
Using mojo..

Class MyWindow Extends Window
	
	Field _queue:=New IntDeque
	Field _mutex:=New Mutex
	Field _sema:=New Semaphore
	
	Field _sent:Int
	Field _recv:Int

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		'Create background thread and detach it.
		New Thread( Lambda()
		
			Repeat 
				'Wait for something to be added to queue.
				_sema.Wait()

				'Remove next item from the queue - the mutex protects against concurrent modification.
				_mutex.Lock()
				Local item:=_queue.RemoveFirst()
				_mutex.Unlock()

				_recv+=item
			Forever
		
		End ).Detach()
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		'Adds a random number of items to the queue.
		For Local i:=0 Until Int( Rnd(5)+5 )

			'Each item is just a random int.
			Local item:=Int( Rnd( 5 ) )
			
			_sent+=item
			
			'Add item to the queue - the mutex protects against concurrent modification.
			_mutex.Lock()
			_queue.AddLast( item )
			_mutex.Unlock()
			
			'Signal thread there's something new to be removed.
			_sema.Signal()
		Next
		
		'Easier to check difference - recv should equal sent but with a lag.
		Local diff:=_sent-_recv
		
		canvas.DrawText( "Sent="+_sent+", Received="+_recv+", Difference="+diff,Width/2,Height/2,.5,.5 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
