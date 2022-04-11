void update_glue(S * s){
	return update(*s);
}
void C_update_glue(C * _this,S * s){
	return _this->update(*s);
}