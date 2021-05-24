#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"

Using std..
Using mojo..
Using pyro.framework..

Function Main()

	Local highScore:=New HighScoreManager											' Create a high score table.

	' Add some names and scores to the  high score table:
	highScore.Add( "Tony",654 )
	highScore.Add( "Peter",67542 )
	highScore.Add( "Reyn",17542 )
	highScore.Add( "Crit",3342 )
	highScore.Add( "Maria",312 )
	highScore.Add( "Ben",62422 )
	highScore.Add( "Els",1111 )
	highScore.Add( "Bas",57346 )
	highScore.Add( "Crit",435 )
	highScore.Add( "Dana",5533 )
	highScore.Add( "Tanya",4112 )
	highScore.Add( "Val",9965 )
	
	Print highScore.ToString()														' Show the high score table ( for debugging purposes ).

	Print "The high score table has "+highScore.Count()+" entries."
	
	If highScore.IsNewEntry( 30002 ) Print "30002 would be a new entry!"			' You can use this to decide to show your highscore input or not


End
