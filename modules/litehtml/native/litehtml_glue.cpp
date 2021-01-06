
#include "litehtml_glue.h"

//**** *wx_litehtml_document_container *****

litehtml::uint_ptr wx_litehtml_document_container::create_font( const litehtml::tchar_t *faceName,int size,int weight,litehtml::font_style style,unsigned int decoration,litehtml::font_metrics *fm ){

	wxObject *font=_create_font( faceName,size,weight,style,decoration,fm );
	return font;
}

void wx_litehtml_document_container::delete_font( litehtml::uint_ptr hFont ){

	wxObject *font=(wxObject*)hFont;
	_delete_font( font );
}

int	wx_litehtml_document_container::text_width( const litehtml::tchar_t *text,litehtml::uint_ptr hFont ){

	wxObject *font=(wxObject*)hFont;
	return _text_width( text,font );
}

void wx_litehtml_document_container::draw_text( litehtml::uint_ptr hHdc,const litehtml::tchar_t *text,litehtml::uint_ptr hFont,litehtml::web_color color,const litehtml::position &pos ){

	wxObject *hdc=(wxObject*)hHdc;
	wxObject *font=(wxObject*)hFont;
	_draw_text( hdc,text,font,&color,(litehtml::position*)&pos );
}

int wx_litehtml_document_container::pt_to_px( int pt ){

	return _pt_to_px( pt );
}

int	wx_litehtml_document_container::get_default_font_size()const{

	return ((wx_litehtml_document_container*)this)->_get_default_font_size();
}

const litehtml::tchar_t *wx_litehtml_document_container::get_default_font_name()const{

	wxString name=((wx_litehtml_document_container*)this)->_get_default_font_name();
	return name.c_str();//<litehtml::tchar_t>();
}

void wx_litehtml_document_container::draw_list_marker( litehtml::uint_ptr hHdc,const litehtml::list_marker &marker ){

	wxObject *hdc=(wxObject*)hHdc;
	_draw_list_marker( hdc,(litehtml::list_marker*)&marker );
}

void wx_litehtml_document_container::load_image( const litehtml::tchar_t *src,const litehtml::tchar_t *baseurl,bool redraw_on_ready ){

	_load_image( src,"",redraw_on_ready );//baseurl,redraw_on_ready );
}

void wx_litehtml_document_container::get_image_size( const litehtml::tchar_t *src,const litehtml::tchar_t *baseurl,litehtml::size &sz ){

	_get_image_size( src,"",&sz );//baseurl,&sz );
}

void wx_litehtml_document_container::draw_background( litehtml::uint_ptr hHdc,const litehtml::background_paint &bg ){

	wxObject *hdc=(wxObject*)hHdc;
	_draw_background( hdc,bg.image.c_str(),"",(litehtml::background_paint*)&bg );
}

void wx_litehtml_document_container::draw_borders( litehtml::uint_ptr hHdc,const litehtml::borders &borders,const litehtml::position &draw_pos,bool root ){

	wxObject *hdc=(wxObject*)hHdc;
	_draw_borders( hdc,(litehtml::borders*)&borders,(litehtml::position*)&draw_pos,root );
}

void wx_litehtml_document_container::set_caption( const litehtml::tchar_t *caption ){
	_set_caption( caption );
}

void wx_litehtml_document_container::set_base_url( const litehtml::tchar_t *base_url ){
	_set_base_url( base_url );
}

void wx_litehtml_document_container::link( const std::shared_ptr<litehtml::document> &doc,const litehtml::element::ptr &el ){
}

void wx_litehtml_document_container::on_anchor_click( const litehtml::tchar_t *url,const litehtml::element::ptr &el ){
	_on_anchor_click( url );
}

void wx_litehtml_document_container::set_cursor( const litehtml::tchar_t *cursor ){
	_set_cursor( cursor );
}

void wx_litehtml_document_container::transform_text( litehtml::tstring &text,litehtml::text_transform tt ){

//	_transform_text( text,tt );
}

void wx_litehtml_document_container::import_css( litehtml::tstring &text,const litehtml::tstring &url,litehtml::tstring &baseurl ){

	wxString css=_import_css( url.c_str(),"" );
	
	text=css.c_str();
//	text=static_cast<const litehtml::tchar_t*>( css );

	baseurl="";
}

void wx_litehtml_document_container::set_clip( const litehtml::position &pos,const litehtml::border_radiuses &bdr_radius,bool valid_x,bool valid_y ){

	_set_clip( (litehtml::position*)&pos,(litehtml::border_radiuses*)&bdr_radius );
}

void wx_litehtml_document_container::del_clip(){

	_del_clip();
}

void wx_litehtml_document_container::get_client_rect( litehtml::position &client )const{

	((wx_litehtml_document_container*)this)->_get_client_rect( &client );
}

std::shared_ptr<litehtml::element>	wx_litehtml_document_container::create_element( 
const litehtml::tchar_t *tag_name,
const litehtml::string_map &attributes,
const std::shared_ptr<litehtml::document> &doc ){
															 
	return nullptr;
}

void wx_litehtml_document_container::get_media_features( litehtml::media_features &media )const{

	((wx_litehtml_document_container*)this)->_get_media_features( &media );
}

void wx_litehtml_document_container::get_language( litehtml::tstring &language,litehtml::tstring &culture )const{
	((wx_litehtml_document_container*)this)->_get_language();
	((wx_litehtml_document_container*)this)->_get_culture();
}

//**** *wx_litehtml_context ****

wx_litehtml_context::wx_litehtml_context(){
}

void wx_litehtml_context::load_master_stylesheet( wxString master_css ){

	litehtml::context::load_master_stylesheet( wxCString( master_css ) );
}

//**** *wx_litehtml_document *****

wx_litehtml_document::wx_litehtml_document( wxString source,wx_litehtml_document_container *container,wx_litehtml_context *context ){

	_document=litehtml::document::createFromUTF8( wxCString( source ),container,context );
	
	_container=container;
	_context=context;
}

wx_litehtml_document::~wx_litehtml_document(){
}
	
void wx_litehtml_document::render( int max_width ){
	_document->render( max_width );
}

void wx_litehtml_document::draw( wxObject *hdc,int x,int y,litehtml::position *clip ){
	_drawing=hdc;
	_document->draw( (litehtml::uint_ptr)hdc,x,y,clip );
	_drawing=nullptr;
}

int wx_litehtml_document::width(){
	return _document->width();
}

int wx_litehtml_document::height(){
	return _document->height();
}

void wx_litehtml_document::gcMark(){
	wxGCMark( _container );
	wxGCMark( _context );
	wxGCMark( _drawing );
}

void wx_litehtml_document::media_changed(){

	_document->media_changed();
}

void wx_litehtml_document::on_mouse_over( int x,int y,int client_x,int client_y ){
	
	litehtml::position::vector redraw_boxes;

	_document->on_mouse_over( x,y,client_x,client_y,redraw_boxes );
}
	
void wx_litehtml_document::on_lbutton_down( int x,int y,int client_x,int client_y ){
	
	litehtml::position::vector redraw_boxes;

	_document->on_lbutton_down( x,y,client_x,client_y,redraw_boxes );
}

void wx_litehtml_document::on_lbutton_up( int x,int y,int client_x,int client_y ){
	
	litehtml::position::vector redraw_boxes;

	_document->on_lbutton_up( x,y,client_x,client_y,redraw_boxes );
}

void wx_litehtml_document::on_mouse_leave(){

	litehtml::position::vector redraw_boxes;

	_document->on_mouse_leave( redraw_boxes );
}
