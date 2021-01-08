
#Import "<std>"
#Import "<assimp>"

#Import "assets/"

Using std..
Using assimp..

Function Main()
	
'	Local flags:UInt=aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
'	Local flags:UInt=aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
	Local flags:UInt=aiProcess_PreTransformVertices | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
	
Local scene:=aiImportFile( AssetsDir()+"turtle1.b3d",flags )

	If scene
		Print "Loaded!"
		
		Print "NumMeshes="+scene.mNumMeshes
		
		Print "NumMaterials="+scene.mNumMaterials
	
		For Local i:=0 Until scene.mNumMeshes
			
			Local mesh:=scene.mMeshes[i]
			
			Local matid:=mesh.mMaterialIndex
			
			Local mat:=scene.mMaterials[matid]
			
			Local n:=aiGetMaterialTextureCount( mat,aiTextureType_DIFFUSE )
			
			If n
				Local color:aiColor4D
				
				Local path:aiString
				
				aiGetMaterialColor( mat,AI_MATKEY_COLOR_DIFFUSE,0,0,Varptr color )
				Print "Mesh "+i+": Diffuse color="+color.r+","+color.g+","+color.b+","+color.a
				
				aiGetMaterialTexture( mat,aiTextureType_DIFFUSE,0,Varptr path )
				Print "Mesh "+i+": Diffuse texture="+path.data
				
			Endif
			
			Print "Mesh "+i+": NumVertices="+mesh.mNumVertices
		Next
	Else
		Print "Error!"
	Endif
		
	aiReleaseImport( scene )
	
	Print "Bye!"
	
End
