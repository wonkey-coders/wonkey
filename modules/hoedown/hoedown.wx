
Namespace hoedown

#Import "hoedown/src/document.h"
#Import "hoedown/src/html.h"

#Import "hoedown/src/autolink.c"
#Import "hoedown/src/buffer.c"
#Import "hoedown/src/document.c"
#Import "hoedown/src/escape.c"
#Import "hoedown/src/html_blocks.c"
#Import "hoedown/src/html_smartypants.c"
#Import "hoedown/src/html.c"
#Import "hoedown/src/stack.c"
#Import "hoedown/src/version.c"

Extern

'buffer

Struct hoedown_buffer
End

Function hoedown_buffer_new:hoedown_buffer Ptr( unit:Int )

Function hoedown_buffer_reset( buf:hoedown_buffer Ptr )

Function hoedown_buffer_free( buf:hoedown_buffer Ptr )

Function hoedown_buffer_put( buf:hoedown_buffer Ptr,data:UByte Ptr,size:Int )

Function hoedown_buffer_cstr:Void Ptr( buf:hoedown_buffer Ptr )

'renderer

Struct hoedown_renderer
End

Enum hoedown_html_flags
End

Const HOEDOWN_HTML_NONE:hoedown_html_flags="(hoedown_html_flags)0"

Const HOEDOWN_HTML_SKIP_HTML:hoedown_html_flags
Const HOEDOWN_HTML_ESCAPE:hoedown_html_flags
Const HOEDOWN_HTML_HARD_WRAP:hoedown_html_flags
Const HOEDOWN_HTML_USE_XHTML:hoedown_html_flags

Function hoedown_html_renderer_new:hoedown_renderer Ptr( render_flags:hoedown_html_flags,nesting_level:Int )

Function hoedown_html_toc_renderer_new:hoedown_renderer Ptr( nesting_level:Int )

Function hoedown_html_renderer_free( renderer:hoedown_renderer Ptr )

'document

Struct hoedown_document
End

Enum hoedown_extensions
End

Const HOEDOWN_EXT_NONE:hoedown_extensions="(hoedown_extensions)0"

Const HOEDOWN_EXT_TABLES:hoedown_extensions
Const HOEDOWN_EXT_FENCED_CODE:hoedown_extensions
Const HOEDOWN_EXT_FOOTNOTES:hoedown_extensions

Const HOEDOWN_EXT_AUTOLINK:hoedown_extensions
Const HOEDOWN_EXT_STRIKETHROUGH:hoedown_extensions
Const HOEDOWN_EXT_UNDERLINE:hoedown_extensions
Const HOEDOWN_EXT_HIGHLIGHT:hoedown_extensions
Const HOEDOWN_EXT_QUOTE:hoedown_extensions
Const HOEDOWN_EXT_SUPERSCRIPT:hoedown_extensions
Const HOEDOWN_EXT_MATH:hoedown_extensions

Const HOEDOWN_EXT_NO_INTRA_EMPHASIS:hoedown_extensions
Const HOEDOWN_EXT_SPACE_HEADERS:hoedown_extensions
Const HOEDOWN_EXT_MATH_EXPLICIT:hoedown_extensions

Const HOEDOWN_EXT_DISABLE_INDENTED_CODE:hoedown_extensions

#rem
Enum hoedown_extensions

	HOEDOWN_EXT_TABLES
	HOEDOWN_EXT_FENCED_CODE
	HOEDOWN_EXT_FOOTNOTES
	
	HOEDOWN_EXT_AUTOLINK
	HOEDOWN_EXT_STRIKETHROUGH
	HOEDOWN_EXT_UNDERLINE
	HOEDOWN_EXT_HIGHLIGHT
	HOEDOWN_EXT_QUOTE
	HOEDOWN_EXT_SUPERSCRIPT
	HOEDOWN_EXT_MATH
	
	HOEDOWN_EXT_NO_INTRA_EMPHASIS
	HOEDOWN_EXT_SPACE_HEADERS
	HOEDOWN_EXT_MATH_EXPLICIT
	
	HOEDOWN_EXT_DISABLE_INDENTED_CODE
End
#end

Function hoedown_document_new:hoedown_document Ptr( renderer:hoedown_renderer Ptr,extensions:hoedown_extensions,max_nesting:Int )

Function hoedown_document_render( doc:hoedown_document Ptr,ob:hoedown_buffer Ptr,data:CString,size:Int )

Function hoedown_document_render_inline( doc:hoedown_document Ptr,ob:hoedown_buffer Ptr,data:CString,size:Int )

Function hoedown_document_free( doc:hoedown_document Ptr )

Public

Function MarkdownToHtml:String( markdown:String,toc:Bool=False )

	Local ob:=hoedown_buffer_new( 4096 )
	
	Local r:hoedown_renderer Ptr
	
	If toc
		r=hoedown_html_toc_renderer_new( 10 )
	Else
		r=hoedown_html_renderer_new( HOEDOWN_HTML_NONE,10 )
	Endif
	
	Local doc:=hoedown_document_new( r,HOEDOWN_EXT_TABLES|HOEDOWN_EXT_FENCED_CODE,10 )
		
	hoedown_document_render( doc,ob,markdown,markdown.Utf8Length )
	
	Local html:=String.FromCString( hoedown_buffer_cstr( ob ) )
	
	hoedown_document_free( doc )
	
	hoedown_html_renderer_free( r )
	
	hoedown_buffer_free( ob )
	
	Return html

End
