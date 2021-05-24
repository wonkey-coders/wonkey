#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"

Using std..
Using mojo..
Using pyro.framework..

Function Main()

	Local highScore:=New HighScoreManager																			' Create a high score table.
	highScore.MaxEntries=5																							' Limit the high score table to 5 entries ( default is 10 ).

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
	
	Print "The lowest score is "+highScore.Lowest.Name+" with "+highScore.Lowest.Score+" points."					' Gets the lowest score from the high score table.
	Print "The highest score is "+highScore.Highest.Name+" with "+highScore.Highest.Score+" points."				' Gets the highest score from the high score table.
	Print highScore.Get( 4 ).Name+" has a score of "+highScore.Get( 4 ).Score+" points."							' Gets the score from the 4th position of the high score table.
	Print ""
	Print highScore.ToString()																						' Show the high score table ( for debugging purposes ).

End
