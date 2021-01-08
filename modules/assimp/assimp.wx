
Namespace assimp

#Import "<libc>"
#Import "<zlib>"

#Import "makefile"

#Import "assimp/include/*.h"

#Import "<assimp/cimport.h>"
#Import "<assimp/scene.h>"
#Import "<assimp/postprocess.h>"

Const AI_MATKEY_NAME:="?mat.name"

Const AI_MATKEY_COLOR_DIFFUSE:="$clr.diffuse"
Const AI_MATKEY_COLOR_AMBIENT:="$clr.ambient"
Const AI_MATKEY_COLOR_SPECULAR:="$clr.specular"
Const AI_MATKEY_COLOR_EMISSIVE:="$clr.emissive"
Const AI_MATKEY_COLOR_TRANSPARENT:="$clr.transparent"
Const AI_MATKEY_COLOR_REFLECTIVE:="$clr.reflective"

Const AI_CONFIG_PP_SBP_REMOVE:="PP_SBP_REMOVE"
Const AI_CONFIG_PP_FD_REMOVE:="PP_FD_REMOVE"
Const AI_CONFIG_PP_SBBC_MAX_BONES:="PP_SBBC_MAX_BONES"

Extern

Const aiProcess_CalcTangentSpace:Uint
Const aiProcess_JoinIdenticalVertices:UInt
Const aiProcess_MakeLeftHanded:UInt
Const aiProcess_Triangulate:UInt
Const aiProcess_RemoveComponent:UInt
Const aiProcess_GenNormals:UInt
Const aiProcess_GenSmoothNormals:UInt
Const aiProcess_SplitLargeMeshes:UInt
Const aiProcess_PreTransformVertices:UInt
Const aiProcess_LimitBoneWeights:UInt
Const aiProcess_ValidateDataStructure:UInt
Const aiProcess_ImproveCacheLocality:UInt
Const aiProcess_RemoveRedundantMaterials:UInt
Const aiProcess_FixInfacingNormals:UInt
Const aiProcess_SortByPType:UInt
Const aiProcess_FindDegenerates:UInt
Const aiProcess_FindInvalidData:UInt
Const aiProcess_GenUVCoords:UInt
Const aiProcess_TransformUVCoords:UInt
Const aiProcess_FindInstances:UInt
Const aiProcess_OptimizeMeshes:UInt
Const aiProcess_OptimizeGraph:UInt
Const aiProcess_FlipUVs:UInt
Const aiProcess_FlipWindingOrder:UInt
Const aiProcess_SplitByBoneCount:UInt
Const aiProcess_Debone:UInt

Const aiTextureType_NONE:UInt
Const aiTextureType_DIFFUSE:UInt
Const aiTextureType_SPECULAR:UInt
Const aiTextureType_AMBIENT:UInt
Const aiTextureType_EMISSIVE:UInt
Const aiTextureType_HEIGHT:UInt
Const aiTextureType_NORMALS:UInt
Const aiTextureType_SHININESS:UInt
Const aiTextureType_OPACITY:UInt
Const aiTextureType_DISPLACEMENT:UInt
Const aiTextureType_LIGHTMAP:UInt
Const aiTextureType_REFLECTION:UInt
Const aiTextureType_UNKNOWN:UInt

Const aiPrimitiveType_POINT:UInt
Const aiPrimitiveType_LINE:Uint
Const aiPrimitiveType_TRIANGLE:Uint
Const aiPrimitiveType_POLYGON:Uint

Struct aiVector3D
	Field x:Float
	Field y:Float
	Field z:Float
End

Struct aiMatrix4x4
	Field a1:Float,a2:Float,a3:Float,a4:float
	Field b1:Float,b2:Float,b3:Float,b4:float
	Field c1:Float,c2:Float,c3:Float,c4:float
	Field d1:Float,d2:Float,d3:Float,d4:Float
End

Struct aiQuaternion
	Field w:Float
	Field x:Float
	Field y:Float
	Field z:Float
End

Struct aiString
	Field data:CString
End

Struct aiColor4D
	Field r:Float
	Field g:Float
	Field b:Float
	Field a:Float
End

Struct aiFace
	Field mIndices:UInt Ptr
	Field mNumIndices:UInt
End

Struct aiVectorKey
	Field mTime:Double
	Field mValue:aiVector3D
End

Struct aiQuatKey
	Field mTime:Double
	Field mValue:aiQuaternion
End

Struct aiVertexWeight
	Field mVertexId:UInt
	Field mWeight:Float
End

Class aiBone Extends void
	
	Field mName:aiString
	Field mOffsetMatrix:aiMatrix4x4
	Field mWeights:aiVertexWeight Ptr
	Field mNumWeights:UInt
End

Class aiNodeAnim Extends Void
	
	Field mNodeName:aiString
	
	Field mPositionKeys:aiVectorKey Ptr
	Field mRotationKeys:aiQuatKey Ptr
	Field mScalingKeys:aiVectorKey Ptr
	
	Field mNumPositionKeys:UInt
	Field mNumRotationKeys:UInt
	Field mNumScalingKeys:UInt
End

Class aiAnimation Extends Void
	
	Field mName:aiString

	Field mDuration:Double
	
	Field mTicksPerSecond:Double

	Field mChannels:aiNodeAnim Ptr
	
	Field mNumChannels:UInt
End

Class aiMaterial Extends Void

End

Class aiMesh Extends Void
	
	Field mVertices:aiVector3D Ptr 
	Field mNormals:aiVector3D Ptr
	Field mTangents:aiVector3D Ptr
	Field mBitangents:aiVector3D Ptr
	Field mColors:aiColor4D Ptr Ptr
	Field mTextureCoords:aiVector3D Ptr Ptr
	Field mBones:aiBone Ptr
	Field mFaces:aiFace Ptr
	
	Field mName:aiString
	Field mMaterialIndex:UInt
	Field mNumVertices:UInt
	Field mPrimitiveTypes:UInt
	Field mNumUVComponents:UInt Ptr
	Field mNumBones:UInt
	Field mNumFaces:UInt
End

Class aiNode Extends Void
	
	Field mName:aiString
	
	Field mTransformation:aiMatrix4x4
	
	Field mParent:aiNode Ptr
	Field mChildren:aiNode Ptr
	Field mMeshes:UInt Ptr
	
	Field mNumChildren:UInt
	Field mNumMeshes:UInt
End

Class aiScene Extends Void="const aiScene"
	
	Field mRootNode:aiNode
	
	Field mAnimations:aiAnimation Ptr
	Field mMaterials:aiMaterial Ptr
	Field mMeshes:aiMesh Ptr

	Field mNumAnimations:uint	
	Field mNumMaterials:UInt
	Field mNumMeshes:UInt
End

Class aiPropertyStore Extends Void
End

Struct aiFileIO
End

Function aiCreatePropertyStore:aiPropertyStore()

Function aiReleasePropertyStore( p:aiPropertyStore )
	
Function aiImportFile:aiScene( pFile:CString,pFlags:UInt )
	
Function aiImportFileEx:aiScene( pFile:CString,pFlags:UInt,pFS:aiFileIO Ptr )

Function aiImportFileExWithProperties:aiScene( pFile:CString,pFlags:UInt,pFS:aiFileIO Ptr,pProps:aiPropertyStore )

Function aiImportFileFromMemory:aiScene( pBuffer:libc.char_t Ptr,pLength:UInt,pFlags:UInt,pHint:CString )

Function aiReleaseImport( scene:aiScene )
	
Function aiGetMaterialString( pMat:aiMaterial,pKey:CString,type:UInt,index:UInt,pOut:aiString Ptr )
	
Function aiGetMaterialTextureCount:UInt( pMat:aiMaterial,type:UInt )
	
Function aiGetMaterialTexture( mat:aiMaterial,type:UInt,index:UInt,path:aiString Ptr )

Function aiGetMaterialColor( pMat:aiMaterial,pKey:CString,type:UInt,index:UInt,pOut:aiColor4D Ptr )
	
Function aiSetImportPropertyFloat( store:aiPropertyStore,szName:CString,value:Float )

Function aiSetImportPropertyInteger( store:aiPropertyStore,szName:CString,value:Int )

Function aiSetImportPropertyString( store:aiPropertyStore,szName:CString,st:CString )
	
Function aiGetErrorString:CString()
