
'Based on C code at: http://zetcode.com/db/sqlitec/
'
#Import "<sqlite>"

Using sqlite..

Function Main()

	Print sqlite3_version

	Print sqlite3_libversion()
	
	Local rc:Int
	Local db:sqlite3 Ptr
	Local res:sqlite3_stmt Ptr

	rc=sqlite3_open( ":memory:",Varptr db )
	If rc<>SQLITE_OK
    	Print "Failed to open DB: "+sqlite3_errmsg( db )
        sqlite3_close( db )
		Return
	Endif
	
    rc=sqlite3_prepare_v2( db,"SELECT SQLITE_VERSION()",-1,Varptr res,Null )
    If rc<>SQLITE_OK
    	Print "Failed to fetch data: "+sqlite3_errmsg( db )
        sqlite3_close( db )
    	Return
    Endif
    
    rc=sqlite3_step( res )
    If rc=SQLITE_ROW Print sqlite3_column_text( res,0 )
    
    sqlite3_finalize( res )
    sqlite3_close( db )
    
End
