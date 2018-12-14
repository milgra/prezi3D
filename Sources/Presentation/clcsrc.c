#include "clcsrc.h"
void* cast_object( void* theId , void* theObject )
{
	void**components;
	components=(((struct Instance*)theObject)->_components);
	while(*components!=NULL)
	{
		if (((struct Instance*)*components)->_class->classId==theId) return((void*)*components);
		components += 1;
	}
	#ifdef DEBUG
	components=(((struct Instance*)theObject)->_components);
	printf("\nClassId : %lx Not Found in ClassInstance : %s" , (long) theObject , ((struct Instance*)*components)->_class->className );

	#endif
	return NULL;
}
void free_object( void* theObject )
{
	struct Instance* instance;
	void*  original;
	void** pointer;
	void** components;
	instance   = theObject;
	original   = instance->_components[ 0 ];
	pointer    = &original;
	components = instance->_components;
	free( original );
	free( components );
	*pointer = NULL;
}
static struct PRController_Class* PRController_ClassInstance = NULL;
static struct CLString_Class* CLString_ClassInstance = NULL;
static struct CLObject_Class* CLObject_ClassInstance = NULL;
static struct CLDataList_Class* CLDataList_ClassInstance = NULL;
static struct PRLifeRoom_Class* PRLifeRoom_ClassInstance = NULL;
static struct PRSettings_Class* PRSettings_ClassInstance = NULL;
static struct PRMeasures_Class* PRMeasures_ClassInstance = NULL;
static struct PRInfoView_Class* PRInfoView_ClassInstance = NULL;
static struct PRFontManager_Class* PRFontManager_ClassInstance = NULL;
static struct GLUIImageArea_Class* GLUIImageArea_ClassInstance = NULL;
static struct GLUIElement_Class* GLUIElement_ClassInstance = NULL;
static struct GLUIController_Class* GLUIController_ClassInstance = NULL;
static struct GLUITrafo_Class* GLUITrafo_ClassInstance = NULL;
static struct PRCodingRoom_Class* PRCodingRoom_ClassInstance = NULL;
static struct PRDesignRoom_Class* PRDesignRoom_ClassInstance = NULL;
static struct PRMusicRoom_Class* PRMusicRoom_ClassInstance = NULL;
static struct PRRoom_Class* PRRoom_ClassInstance = NULL;
static struct GLBitmapRGBA_Class* GLBitmapRGBA_ClassInstance = NULL;
static struct GLTextureSquare_Class* GLTextureSquare_ClassInstance = NULL;
static struct GLBitmapRGBAUtils_Class* GLBitmapRGBAUtils_ClassInstance = NULL;
static struct GLUIModel_Class* GLUIModel_ClassInstance = NULL;
static struct GLUIModelDrawer_Class* GLUIModelDrawer_ClassInstance = NULL;
static struct GLUIParagraph_Class* GLUIParagraph_ClassInstance = NULL;
static struct GLUITrafoAnimator_Class* GLUITrafoAnimator_ClassInstance = NULL;
static struct GLUITrafoAnimation_Class* GLUITrafoAnimation_ClassInstance = NULL;
static struct GLFontTrueType_Class* GLFontTrueType_ClassInstance = NULL;
static struct GLUIShader_Class* GLUIShader_ClassInstance = NULL;
static struct TLPixelFont_Class* TLPixelFont_ClassInstance = NULL;
static struct TLPixelText_Class* TLPixelText_ClassInstance = NULL;
static struct GLUIVertexArray_Class* GLUIVertexArray_ClassInstance = NULL;
static struct GLUICursor_Class* GLUICursor_ClassInstance = NULL;
static struct GLUIGlyph_Class* GLUIGlyph_ClassInstance = NULL;
static struct TLTextMetrics_Class* TLTextMetrics_ClassInstance = NULL;
static struct TLFontMetrics_Class* TLFontMetrics_ClassInstance = NULL;
static struct GLTextureMap_Class* GLTextureMap_ClassInstance = NULL;
static struct GLShader_Class* GLShader_ClassInstance = NULL;
void PRController_CreateClass( )
{
	PRController_ClassInstance=malloc(sizeof(struct PRController_Class));
	PRController_ClassInstance->className="PRController";
	PRController_ClassInstance->classId=&PRController_ClassInstance;
	PRController_ClassInstance->init_width_height_resources_path=PRController_init_width_height_resources_path;
	PRController_ClassInstance->build=PRController_build;
	PRController_ClassInstance->destruct=PRController_destruct;
	PRController_ClassInstance->step_right=PRController_step_right;
	PRController_ClassInstance->step_left=PRController_step_left;
	PRController_ClassInstance->update=PRController_update;
	PRController_ClassInstance->render=PRController_render;
	PRController_ClassInstance->scroll_x_y=PRController_scroll_x_y;
	PRController_ClassInstance->mouse_down_at_x_y=PRController_mouse_down_at_x_y;
	PRController_ClassInstance->mouse_up_at_x_y=PRController_mouse_up_at_x_y;
	PRController_ClassInstance->mouse_move_at_x_y=PRController_mouse_move_at_x_y;
	PRController_ClassInstance->left_pressed=PRController_left_pressed;
	PRController_ClassInstance->right_pressed=PRController_right_pressed;
	PRController_ClassInstance->key_down_characters=PRController_key_down_characters;
	PRController_ClassInstance->className_CLObject="CLObject";
	PRController_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRController_ClassInstance->init=PRController_init;
	PRController_ClassInstance->destruct_CLObject=PRController_destruct;
	PRController_ClassInstance->retain=PRController_retain;
	PRController_ClassInstance->release=PRController_release;
	PRController_ClassInstance->event=PRController_event;
	PRController_ClassInstance->describe=PRController_describe;
	
}
struct PRController* PRController_alloc( )
{
	struct PRController* result;
	if(PRController_ClassInstance==NULL)PRController_CreateClass( );
	result=malloc(sizeof(struct PRController));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PRController_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRController_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PRController_init_width_height_resources_path (struct PRController* self, float the_width , float the_height , char * the_resources_path ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->left_is_pressed=0;
	self->right_is_pressed=0;
	self->width=the_width;
	self->height=the_height;
	self->pressed_key=NULL;
	self->view_index=-1;
	self->info_views=CLDataList_alloc( );
	CLDataList_init(self->info_views );
	self->mouse_down_coords=MLVector3Create(0,0,0);
	self->mouse_move_coords=MLVector3Create(0,0,0);
	self->mouse_up_coords=MLVector3Create(0,0,0);
	self->ui_controller=GLUIController_alloc( );
	GLUIController_init_fov_width_height_nead_far(self->ui_controller, M_PI/4,self->width,self->height,50.0,20000.0);
	self->settings=PRSettings_alloc( );
	PRSettings_init_resources_path(self->settings, the_resources_path);
	self->measures=PRMeasures_alloc( );
	PRMeasures_init_width_height(self->measures, the_width,the_height);
	self->font_manager=PRFontManager_alloc( );
	PRFontManager_init_settings(self->font_manager, self->settings);
	self->info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(self->info_view, "info_view",MLVector4Create(0,0,800,-600),self);
	PRInfoView_set_color(self->info_view, 0,0,0,0);
	PRInfoView_set_level(self->info_view, 0);
	PRInfoView_set_title_label(self->info_view, "Milan Toth");
	PRInfoView_set_subtitle_label(self->info_view, "3D presentation demo and introduction");
	PRInfoView_set_description_label(self->info_view, "This demo uses KineticUI, the OpenGL based, multiplatform UI and Text renderer. Navigate with arrows or clicks. http://milgra.com");
	GLUIController_add_element(self->ui_controller, (cast_object( &GLUIElement_ClassInstance , self->info_view)));
	PRInfoView_show(self->info_view );
	self->zoomed_view=self->info_view;
	self->info_view->info_shown=1;
	self->life_room=PRLifeRoom_alloc( );
	PRLifeRoom_init_name_frame_controller(self->life_room, "room",MLVector4Create(0,0,0,0),self);
	PRLifeRoom_set_trafo(self->life_room, MLMatrix4CreateTranslation(0,-1000,240),0);
	PRLifeRoom_set_level(self->life_room, 2);
	self->music_room=PRMusicRoom_alloc( );
	PRMusicRoom_init_name_frame_controller(self->music_room, "room",MLVector4Create(0,0,0,0),self);
	PRMusicRoom_set_trafo(self->music_room, MLMatrix4CreateTranslation(1500,-1000,240),0);
	PRMusicRoom_set_level(self->music_room, 2);
	self->design_room=PRDesignRoom_alloc( );
	PRDesignRoom_init_name_frame_controller(self->design_room, "room",MLVector4Create(0,0,0,0),self);
	PRDesignRoom_set_trafo(self->design_room, MLMatrix4CreateTranslation(3000,-1000,240),0);
	PRDesignRoom_set_level(self->design_room, 2);
	self->coding_room=PRCodingRoom_alloc( );
	PRCodingRoom_init_name_frame_controller(self->coding_room, "room",MLVector4Create(0,0,0,0),self);
	PRCodingRoom_set_trafo(self->coding_room, MLMatrix4CreateTranslation(4500,-1000,240),0);
	PRCodingRoom_set_level(self->coding_room, 2);
	GLUIController_add_element(self->ui_controller, (cast_object( &GLUIElement_ClassInstance , self->life_room)));
	GLUIController_add_element(self->ui_controller, (cast_object( &GLUIElement_ClassInstance , self->music_room)));
	GLUIController_add_element(self->ui_controller, (cast_object( &GLUIElement_ClassInstance , self->design_room)));
	GLUIController_add_element(self->ui_controller, (cast_object( &GLUIElement_ClassInstance , self->coding_room)));
	self->life_room->next_room=(cast_object( &PRRoom_ClassInstance , self->music_room));
	self->life_room->last_room=(cast_object( &PRRoom_ClassInstance , self->coding_room));
	self->music_room->next_room=(cast_object( &PRRoom_ClassInstance , self->design_room));
	self->music_room->last_room=(cast_object( &PRRoom_ClassInstance , self->life_room));
	self->design_room->next_room=(cast_object( &PRRoom_ClassInstance , self->coding_room));
	self->design_room->last_room=(cast_object( &PRRoom_ClassInstance , self->music_room));
	self->coding_room->next_room=(cast_object( &PRRoom_ClassInstance , self->life_room));
	self->coding_room->last_room=(cast_object( &PRRoom_ClassInstance , self->design_room));
	self->actual_room=(cast_object( &PRRoom_ClassInstance , self->life_room));
}
void PRController_build (struct PRController* self ) 
{
	PRLifeRoom_build(self->life_room );
}
void PRController_destruct (struct PRController* self ) 
{
	constants:PRController_release( self );
	GLUIController_release(self->ui_controller );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void PRController_step_right (struct PRController* self ) 
{
	if(self->view_index==-1)
	{
		self->view_index=0;
		struct PRInfoView*next_info_view=self->life_room->info_views->_class->data_at_index( (void*) self->life_room->info_views->_components[0], 0);
		GLUIController_zoom_to_element(self->ui_controller, (cast_object( &GLUIElement_ClassInstance , next_info_view)),150,kGLUIAnimationEaseIn);
	}
	else
	{
		self->actual_room->_class->step_right( (void*) self->actual_room->_components[0] );
	}
}
void PRController_step_left (struct PRController* self ) 
{
	self->actual_room->_class->step_left( (void*) self->actual_room->_components[0] );
}
void PRController_update (struct PRController* self ) 
{
	GLUIController_update(self->ui_controller );
	if(self->pressed_key!=NULL)
	{
		GLUIController_key_down_characters(self->ui_controller, self->pressed_key);
		self->pressed_key=NULL;
	}
	if(self->left_is_pressed==1)
	{
		self->left_is_pressed=0;
		PRController_step_left( self );
	}
	if(self->right_is_pressed==1)
	{
		self->right_is_pressed=0;
		PRController_step_right( self );
	}
	if(self->mouse_down_coords.z>0.0)
	{
		GLUIController_mouse_down_at_x_y(self->ui_controller, self->mouse_down_coords.x,self->mouse_down_coords.y);
		self->mouse_down_coords.z=0.0;
	}
	if(self->mouse_move_coords.z>0.0)
	{
		GLUIController_mouse_move_at_x_y(self->ui_controller, self->mouse_move_coords.x,self->mouse_move_coords.y);
		self->mouse_move_coords.z=0.0;
	}
	if(self->mouse_up_coords.z>0.0)
	{
		GLUIController_mouse_up_at_x_y(self->ui_controller, self->mouse_up_coords.x,self->mouse_up_coords.y);
		self->mouse_up_coords.z=0.0;
	}
}
void PRController_render (struct PRController* self ) 
{
	GLUIController_render(self->ui_controller );
}
void PRController_scroll_x_y (struct PRController* self, float the_x , float the_y ) 
{
	GLUIController_scroll_x_y(self->ui_controller, the_x,the_y);
}
void PRController_mouse_down_at_x_y (struct PRController* self, float the_x , float the_y ) 
{
	self->mouse_down_coords.x=the_x;
	self->mouse_down_coords.y=the_y;
	self->mouse_down_coords.z=1.0;
}
void PRController_mouse_up_at_x_y (struct PRController* self, float the_x , float the_y ) 
{
	self->mouse_up_coords.x=the_x;
	self->mouse_up_coords.y=the_y;
	self->mouse_up_coords.z=1.0;
}
void PRController_mouse_move_at_x_y (struct PRController* self, float the_x , float the_y ) 
{
	self->mouse_move_coords.x=the_x;
	self->mouse_move_coords.y=the_y;
	self->mouse_move_coords.z=1.0;
}
void PRController_left_pressed (struct PRController* self ) 
{
	self->left_is_pressed=1;
}
void PRController_right_pressed (struct PRController* self ) 
{
	self->right_is_pressed=1;
}
void PRController_key_down_characters (struct PRController* self, char * the_characters ) 
{
	if(self->pressed_key!=NULL)free(self->pressed_key);
	self->pressed_key=malloc(sizeof(char)*strlen(the_characters));
	memcpy(self->pressed_key,the_characters,strlen(the_characters));
}
void PRController_init (struct PRController* self ) 
{
	self->retain_count=1;
}
void PRController_retain (struct PRController* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRController_release (struct PRController* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRController_event (struct PRController* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRController_describe (struct PRController* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void CLString_CreateClass( )
{
	CLString_ClassInstance=malloc(sizeof(struct CLString_Class));
	CLString_ClassInstance->className="CLString";
	CLString_ClassInstance->classId=&CLString_ClassInstance;
	CLString_ClassInstance->init=CLString_init;
	CLString_ClassInstance->init_string=CLString_init_string;
	CLString_ClassInstance->init_cstring=CLString_init_cstring;
	CLString_ClassInstance->destruct=CLString_destruct;
	CLString_ClassInstance->append_character=CLString_append_character;
	CLString_ClassInstance->append_string=CLString_append_string;
	CLString_ClassInstance->append_cstring=CLString_append_cstring;
	CLString_ClassInstance->remove_all_characters=CLString_remove_all_characters;
	CLString_ClassInstance->read_filePath=CLString_read_filePath;
	CLString_ClassInstance->read_file_pointer=CLString_read_file_pointer;
	CLString_ClassInstance->write_file_path=CLString_write_file_path;
	CLString_ClassInstance->write_file_pointer=CLString_write_file_pointer;
	CLString_ClassInstance->string_from_last_component=CLString_string_from_last_component;
	CLString_ClassInstance->substring_from_index=CLString_substring_from_index;
	CLString_ClassInstance->string_by_removing_extension=CLString_string_by_removing_extension;
	CLString_ClassInstance->string_by_removing_last_path_component=CLString_string_by_removing_last_path_component;
	CLString_ClassInstance->contains_string=CLString_contains_string;
	CLString_ClassInstance->index_string=CLString_index_string;
	CLString_ClassInstance->equals_string=CLString_equals_string;
	CLString_ClassInstance->c_string=CLString_c_string;
	CLString_ClassInstance->describe=CLString_describe;
	CLString_ClassInstance->className_CLObject="CLObject";
	CLString_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	CLString_ClassInstance->init_CLObject=CLString_init;
	CLString_ClassInstance->destruct_CLObject=CLString_destruct;
	CLString_ClassInstance->retain=CLString_retain;
	CLString_ClassInstance->release=CLString_release;
	CLString_ClassInstance->event=CLString_event;
	CLString_ClassInstance->describe_CLObject=CLString_describe;
	
}
struct CLString* CLString_alloc( )
{
	struct CLString* result;
	if(CLString_ClassInstance==NULL)CLString_CreateClass( );
	result=malloc(sizeof(struct CLString));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(CLString_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(CLString_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void CLString_init (struct CLString* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLString_init_string (struct CLString* self, struct CLString * the_string ) 
{
	CLString_init( self );
	CLString_append_string( self, the_string);
}
void CLString_init_cstring (struct CLString* self, char * the_string ) 
{
	CLString_init( self );
	CLString_append_cstring( self, the_string);
}
void CLString_destruct (struct CLString* self ) 
{
	CLString_remove_all_characters( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void CLString_append_character (struct CLString* self, char the_character ) 
{
	struct CLChar*new_char;
	new_char=malloc(sizeof(struct CLChar));
	new_char->next=NULL;
	new_char->character=the_character;
	if(self->head==NULL)self->head=new_char;
	else self->last->next=new_char;
	self->last=new_char;
	self->length=self->length+1;
}
void CLString_append_string (struct CLString* self, struct CLString * the_string ) 
{
	struct CLChar*link;
	if(the_string!=NULL&&the_string->length>0)
	{
		link=the_string->head;
		while(link!=NULL)
		{
			CLString_append_character( self, link->character);
			link=link->next;
		}
	}
}
void CLString_append_cstring (struct CLString* self, char * the_string ) 
{
	while(*the_string!='\0')
	{
		CLString_append_character( self, *the_string);
		the_string+=1;
	}
}
void CLString_remove_all_characters (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLChar*prev;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		prev=link;
		link=link->next;
		free(prev);
	}
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLString_read_filePath (struct CLString* self, struct CLString * the_path ) 
{
	char*file_name;
	int character;
	FILE*file_pointer;
	file_name=the_path->_class->c_string( (void*) the_path->_components[0] );
	file_pointer=fopen(file_name,"r");
	if(file_pointer!=NULL)
	{
		character=getc(file_pointer);
		while(character!=EOF)
		{
			CLString_append_character( self, character);
			character=getc(file_pointer);
		}
		fclose(file_pointer);
	}
	free(file_name);
}
void CLString_read_file_pointer (struct CLString* self, FILE * the_pointer ) 
{
	int character;
	character=getc(the_pointer);
	while(character!=EOF)
	{
		CLString_append_character( self, character);
		character=getc(the_pointer);
	}
}
void CLString_write_file_path (struct CLString* self, struct CLString * the_path ) 
{
	char*file_name;
	FILE*file_pointer;
	struct CLChar*link;
	file_name=the_path->_class->c_string( (void*) the_path->_components[0] );
	file_pointer=fopen(file_name,"w");
	link=self->head;
	while(link!=NULL)
	{
		putc(link->character,file_pointer);
		link=link->next;
	}
	fclose(file_pointer);
	free(file_name);
}
void CLString_write_file_pointer (struct CLString* self, FILE * theFilePointer ) 
{
	struct CLChar*link;
	link=self->head;
	while(link!=NULL)
	{
		putc(link->character,theFilePointer);
		link=link->next;
	}
}
struct CLString * CLString_string_from_last_component (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLString*result;
	link=self->head;
	result=CLString_alloc( );
	CLString_init(result );
	while(link!=NULL)
	{
		if(link->character=='/'||link->character=='\\')
		{
			result->_class->release( (void*) result->_components[0] );
			result=CLString_alloc();
			result->_class->init( (void*) result->_components[0] );
		}
		else result->_class->append_character( (void*) result->_components[0], link->character);
		link=link->next;
	}
	return result;
}
struct CLString * CLString_substring_from_index (struct CLString* self, unsigned long the_index ) 
{
	unsigned long index;
	struct CLChar*link;
	struct CLString*result;
	link=self->head;
	index=0;
	result=CLString_alloc( );
	CLString_init(result );
	while(link!=NULL)
	{
		if(index>=the_index)result->_class->append_character( (void*) result->_components[0], link->character);
		index+=1;
		link=link->next;
	}
	return result;
}
struct CLString * CLString_string_by_removing_extension (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLString*part;
	struct CLString*result;
	char in_extension;
	link=self->head;
	in_extension=0;
	part=CLString_alloc( );
	result=CLString_alloc( );
	CLString_init(part );
	CLString_init(result );
	while(link!=NULL)
	{
		if(link->character=='.')
		{
			in_extension=1;
			CLString_append_string(result, part);
			CLString_release(part );
			part=CLString_alloc();
			CLString_init(part );
		}
		else if(in_extension==1)in_extension=0;
		CLString_append_character(part, link->character);
		link=link->next;
	}
	CLString_release(part );
	return result;
}
struct CLString * CLString_string_by_removing_last_path_component (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLString*part;
	struct CLString*result;
	link=self->head;
	result=CLString_alloc( );
	part=CLString_alloc( );
	CLString_init(result );
	CLString_init(part );
	while(link!=NULL)
	{
		CLString_append_character(part, link->character);
		if(link->character=='/'||link->character=='\\')
		{
			CLString_append_string(result, part);
			CLString_release(part );
			part=CLString_alloc();
			CLString_init(part );
		}
		link=link->next;
	}
	if(result->length==0) CLString_append_string(result, part);
	CLString_release(part );
	return result;
}
char CLString_contains_string (struct CLString* self, struct CLString * the_string ) 
{
	struct CLChar*link;
	struct CLChar*search;
	link=self->head;
	search=the_string->head;
	while(link!=NULL)
	{
		if(link->character==search->character)
		{
			search=search->next;
			if(search==NULL)return 1;
		}
		else
		{
			search=the_string->head;
		}
		link=link->next;
	}
	return 0;
}
unsigned long CLString_index_string (struct CLString* self, struct CLString * the_search_string ) 
{
	char found;
	unsigned long result;
	unsigned long index;
	struct CLChar*link;
	struct CLChar*search;
	found=0;
	result=0;
	index=0;
	link=self->head;
	search=the_search_string->head;
	while(link!=NULL)
	{
		if(link->character==search->character)
		{
			if(found==0)
			{
				found=1;
				result=index;
			}
			search=search->next;
			if(search==NULL)return result;
		}
		else
		{
			found=0;
			search=the_search_string->head;
		}
		link=link->next;
		index=index+1;
	}
	return result;
}
char CLString_equals_string (struct CLString* self, struct CLString * the_string_b ) 
{
	struct CLChar*linkA;
	struct CLChar*linkB;
	if(self->length!=the_string_b->length)return 0;
	linkA=self->head;
	linkB=the_string_b->head;
	while(linkA!=NULL&&linkB!=NULL)
	{
		if(linkA->character!=linkB->character)return 0;
		linkA=linkA->next;
		linkB=linkB->next;
	}
	return 1;
}
char * CLString_c_string (struct CLString* self ) 
{
	int index;
	char*result;
	struct CLChar*link;
	if(self->head!=NULL)
	{
		link=self->head;
		index=0;
		result=malloc(sizeof(char)*(self->length+1));
		while(link!=NULL&&link->character!=0)
		{
			result[index++]=link->character;
			link=link->next;
		}
		result[index]=0;
		return result;
	}
	else return NULL;
}
void CLString_describe (struct CLString* self ) 
{
	struct CLChar*link;
	link=self->head;
	while(link!=NULL)
	{
		printf("%c",link->character);
		link=link->next;
	}
}
void CLString_retain (struct CLString* self ) 
{
	self->retain_count=self->retain_count+1;
}
void CLString_release (struct CLString* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLString_event (struct CLString* self, int the_id , void * the_source , void * the_data ) 
{

}
void CLObject_CreateClass( )
{
	CLObject_ClassInstance=malloc(sizeof(struct CLObject_Class));
	CLObject_ClassInstance->className="CLObject";
	CLObject_ClassInstance->classId=&CLObject_ClassInstance;
	CLObject_ClassInstance->init=CLObject_init;
	CLObject_ClassInstance->destruct=CLObject_destruct;
	CLObject_ClassInstance->retain=CLObject_retain;
	CLObject_ClassInstance->release=CLObject_release;
	CLObject_ClassInstance->event=CLObject_event;
	CLObject_ClassInstance->describe=CLObject_describe;
	
}
struct CLObject* CLObject_alloc( )
{
	struct CLObject* result;
	if(CLObject_ClassInstance==NULL)CLObject_CreateClass( );
	result=malloc(sizeof(struct CLObject));
	result->_components=malloc(sizeof(void*)*2);
	result->_class=(void*)&(CLObject_ClassInstance->className);
	result->_components[0]=&(result->_class);
	result->_components[1]=NULL;
	return result;
}
void CLObject_init (struct CLObject* self ) 
{
	self->retain_count=1;
}
void CLObject_destruct (struct CLObject* self ) 
{

}
void CLObject_retain (struct CLObject* self ) 
{
	self->retain_count=self->retain_count+1;
}
void CLObject_release (struct CLObject* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLObject_event (struct CLObject* self, int the_id , void * the_source , void * the_data ) 
{

}
void CLObject_describe (struct CLObject* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void CLDataList_CreateClass( )
{
	CLDataList_ClassInstance=malloc(sizeof(struct CLDataList_Class));
	CLDataList_ClassInstance->className="CLDataList";
	CLDataList_ClassInstance->classId=&CLDataList_ClassInstance;
	CLDataList_ClassInstance->init=CLDataList_init;
	CLDataList_ClassInstance->destruct=CLDataList_destruct;
	CLDataList_ClassInstance->add_data=CLDataList_add_data;
	CLDataList_ClassInstance->add_data_at_index=CLDataList_add_data_at_index;
	CLDataList_ClassInstance->add_data_list=CLDataList_add_data_list;
	CLDataList_ClassInstance->remove_data=CLDataList_remove_data;
	CLDataList_ClassInstance->remove_data_at_index=CLDataList_remove_data_at_index;
	CLDataList_ClassInstance->remove_all_data=CLDataList_remove_all_data;
	CLDataList_ClassInstance->data_at_index=CLDataList_data_at_index;
	CLDataList_ClassInstance->link_at_index=CLDataList_link_at_index;
	CLDataList_ClassInstance->contains_data=CLDataList_contains_data;
	CLDataList_ClassInstance->index_of_data=CLDataList_index_of_data;
	CLDataList_ClassInstance->first_data=CLDataList_first_data;
	CLDataList_ClassInstance->last_data=CLDataList_last_data;
	CLDataList_ClassInstance->clone=CLDataList_clone;
	CLDataList_ClassInstance->describe=CLDataList_describe;
	CLDataList_ClassInstance->className_CLObject="CLObject";
	CLDataList_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	CLDataList_ClassInstance->init_CLObject=CLDataList_init;
	CLDataList_ClassInstance->destruct_CLObject=CLDataList_destruct;
	CLDataList_ClassInstance->retain=CLDataList_retain;
	CLDataList_ClassInstance->release=CLDataList_release;
	CLDataList_ClassInstance->event=CLDataList_event;
	CLDataList_ClassInstance->describe_CLObject=CLDataList_describe;
	
}
struct CLDataList* CLDataList_alloc( )
{
	struct CLDataList* result;
	if(CLDataList_ClassInstance==NULL)CLDataList_CreateClass( );
	result=malloc(sizeof(struct CLDataList));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(CLDataList_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(CLDataList_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void CLDataList_init (struct CLDataList* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLDataList_destruct (struct CLDataList* self ) 
{
	CLDataList_remove_all_data( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void CLDataList_add_data (struct CLDataList* self, void * the_data ) 
{
	struct CLLink*new_link;
	new_link=malloc(sizeof(struct CLLink));
	new_link->data=the_data;
	new_link->next=NULL;
	if(self->head==NULL)self->head=new_link;
	else self->last->next=new_link;
	self->last=new_link;
	self->length=self->length+1;
}
void CLDataList_add_data_at_index (struct CLDataList* self, void * the_data , unsigned long the_index ) 
{
	struct CLLink*link;
	struct CLLink*new_link;
	struct CLLink*last_link;
	unsigned long position;
	link=self->head;
	last_link=NULL;
	position=0;
	while(link!=NULL)
	{
		if(position==the_index)
		{
			new_link=malloc(sizeof(struct CLLink));
			new_link->data=the_data;
			new_link->next=link;
			if(last_link!=NULL)last_link->next=new_link;
			else self->head=new_link;
			self->length=self->length+1;
			return;
		}
		position+=1;
		last_link=link;
		link=link->next;
	}
}
void CLDataList_add_data_list (struct CLDataList* self, struct CLDataList * the_data_list ) 
{
	struct CLLink*link;
	if(the_data_list->length>0)
	{
		link=the_data_list->head;
		while(link!=NULL)
		{
			CLDataList_add_data( self, link->data);
			link=link->next;
		}
	}
}
char CLDataList_remove_data (struct CLDataList* self, void * the_data ) 
{
	struct CLLink*link;
	struct CLLink*prev;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		if(link->data==the_data)
		{
			if(link->next==NULL&&prev!=NULL)
			{
				prev->next=NULL;
				self->last=prev;
			}
			else if(link->next!=NULL&&prev==NULL)
			{
				self->head=link->next;
			}
			else if(link->next!=NULL&&prev!=NULL)
			{
				prev->next=link->next;
			}
			else
			{
				self->head=NULL;
				self->last=NULL;
			}
			free(link);
			self->length-=1;
			return 1;
		}
		prev=link;
		link=link->next;
	}
	return 0;
}
void * CLDataList_remove_data_at_index (struct CLDataList* self, unsigned long the_index ) 
{
	void*data;
	data=CLDataList_data_at_index( self, the_index);
	if(data!=NULL)CLDataList_remove_data( self, data);
	return data;
}
void CLDataList_remove_all_data (struct CLDataList* self ) 
{
	struct CLLink*link;
	struct CLLink*prev;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		prev=link;
		link=link->next;
		free(prev);
	}
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void * CLDataList_data_at_index (struct CLDataList* self, unsigned long the_index ) 
{
	struct CLLink*link;
	unsigned long position;
	link=self->head;
	position=0;
	while(link!=NULL)
	{
		if(position==the_index)return link->data;
		link=link->next;
		position+=1;
	}
	return NULL;
}
struct CLLink * CLDataList_link_at_index (struct CLDataList* self, unsigned long the_index ) 
{
	struct CLLink*link;
	unsigned long position;
	link=self->head;
	position=0;
	while(link!=NULL)
	{
		if(position==the_index)return link;
		link=link->next;
		position+=1;
	}
	return NULL;
}
char CLDataList_contains_data (struct CLDataList* self, void * the_data ) 
{
	struct CLLink*link;
	link=self->head;
	while(link!=NULL)
	{
		if(link->data==the_data)return 1;
		link=link->next;
	}
	return 0;
}
unsigned long CLDataList_index_of_data (struct CLDataList* self, void * the_data ) 
{
	unsigned long index;
	struct CLLink*link;
	index=0;
	link=self->head;
	while(link!=NULL)
	{
		if(link->data==the_data)return index;
		index+=1;
		link=link->next;
	}
	return 0;
}
void * CLDataList_first_data (struct CLDataList* self ) 
{
	if(self->head!=NULL)return self->head->data;
	return NULL;
}
void * CLDataList_last_data (struct CLDataList* self ) 
{
	if(self->last!=NULL)return self->last->data;
	return NULL;
}
struct CLDataList * CLDataList_clone (struct CLDataList* self ) 
{
	struct CLDataList*result;
	result=CLDataList_alloc( );
	CLDataList_init(result );
	CLDataList_add_data_list(result, self);
	return result;
}
void CLDataList_describe (struct CLDataList* self ) 
{
	printf("\nDataList %i length %lu",(int)self,self->length);
}
void CLDataList_retain (struct CLDataList* self ) 
{
	self->retain_count=self->retain_count+1;
}
void CLDataList_release (struct CLDataList* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLDataList_event (struct CLDataList* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRLifeRoom_CreateClass( )
{
	PRLifeRoom_ClassInstance=malloc(sizeof(struct PRLifeRoom_Class));
	PRLifeRoom_ClassInstance->className="PRLifeRoom";
	PRLifeRoom_ClassInstance->classId=&PRLifeRoom_ClassInstance;
	PRLifeRoom_ClassInstance->init_name_frame_controller=PRLifeRoom_init_name_frame_controller;
	PRLifeRoom_ClassInstance->build=PRLifeRoom_build;
	PRLifeRoom_ClassInstance->className_PRRoom="PRRoom";
	PRLifeRoom_ClassInstance->classId_PRRoom=&PRRoom_ClassInstance;
	PRLifeRoom_ClassInstance->init_name_frame_controller_PRRoom=PRLifeRoom_init_name_frame_controller;
	PRLifeRoom_ClassInstance->destruct=PRLifeRoom_destruct;
	PRLifeRoom_ClassInstance->create_info_view=PRLifeRoom_create_info_view;
	PRLifeRoom_ClassInstance->create_empty_view=PRLifeRoom_create_empty_view;
	PRLifeRoom_ClassInstance->create_texture_area=PRLifeRoom_create_texture_area;
	PRLifeRoom_ClassInstance->create_image_area=PRLifeRoom_create_image_area;
	PRLifeRoom_ClassInstance->update=PRLifeRoom_update;
	PRLifeRoom_ClassInstance->step_right=PRLifeRoom_step_right;
	PRLifeRoom_ClassInstance->step_left=PRLifeRoom_step_left;
	PRLifeRoom_ClassInstance->build_PRRoom=PRLifeRoom_build;
	PRLifeRoom_ClassInstance->collapse=PRLifeRoom_collapse;
	PRLifeRoom_ClassInstance->className_GLUIElement="GLUIElement";
	PRLifeRoom_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	PRLifeRoom_ClassInstance->init_name_frame=PRLifeRoom_init_name_frame;
	PRLifeRoom_ClassInstance->destruct_GLUIElement=PRLifeRoom_destruct;
	PRLifeRoom_ClassInstance->set_level=PRLifeRoom_set_level;
	PRLifeRoom_ClassInstance->set_group=PRLifeRoom_set_group;
	PRLifeRoom_ClassInstance->set_texture=PRLifeRoom_set_texture;
	PRLifeRoom_ClassInstance->set_texture_coords=PRLifeRoom_set_texture_coords;
	PRLifeRoom_ClassInstance->set_color=PRLifeRoom_set_color;
	PRLifeRoom_ClassInstance->set_origo=PRLifeRoom_set_origo;
	PRLifeRoom_ClassInstance->set_extent=PRLifeRoom_set_extent;
	PRLifeRoom_ClassInstance->set_trafo=PRLifeRoom_set_trafo;
	PRLifeRoom_ClassInstance->update_GLUIElement=PRLifeRoom_update;
	PRLifeRoom_ClassInstance->update_frame=PRLifeRoom_update_frame;
	PRLifeRoom_ClassInstance->update_trafo=PRLifeRoom_update_trafo;
	PRLifeRoom_ClassInstance->get_absolute_frame=PRLifeRoom_get_absolute_frame;
	PRLifeRoom_ClassInstance->finalize_frame=PRLifeRoom_finalize_frame;
	PRLifeRoom_ClassInstance->add_element=PRLifeRoom_add_element;
	PRLifeRoom_ClassInstance->remove_element=PRLifeRoom_remove_element;
	PRLifeRoom_ClassInstance->attach=PRLifeRoom_attach;
	PRLifeRoom_ClassInstance->detach=PRLifeRoom_detach;
	PRLifeRoom_ClassInstance->get_relative_touch_line_a_line_b=PRLifeRoom_get_relative_touch_line_a_line_b;
	PRLifeRoom_ClassInstance->intersect_line_a_line_b_elements=PRLifeRoom_intersect_line_a_line_b_elements;
	PRLifeRoom_ClassInstance->touch_began=PRLifeRoom_touch_began;
	PRLifeRoom_ClassInstance->touch_moved=PRLifeRoom_touch_moved;
	PRLifeRoom_ClassInstance->touch_ended=PRLifeRoom_touch_ended;
	PRLifeRoom_ClassInstance->key_down_characters=PRLifeRoom_key_down_characters;
	PRLifeRoom_ClassInstance->key_up_characters=PRLifeRoom_key_up_characters;
	PRLifeRoom_ClassInstance->scroll_x_y=PRLifeRoom_scroll_x_y;
	PRLifeRoom_ClassInstance->focus_on=PRLifeRoom_focus_on;
	PRLifeRoom_ClassInstance->focus_off=PRLifeRoom_focus_off;
	PRLifeRoom_ClassInstance->className_CLObject="CLObject";
	PRLifeRoom_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRLifeRoom_ClassInstance->init=PRLifeRoom_init;
	PRLifeRoom_ClassInstance->destruct_CLObject=PRLifeRoom_destruct;
	PRLifeRoom_ClassInstance->retain=PRLifeRoom_retain;
	PRLifeRoom_ClassInstance->release=PRLifeRoom_release;
	PRLifeRoom_ClassInstance->event=PRLifeRoom_event;
	PRLifeRoom_ClassInstance->describe=PRLifeRoom_describe;
	
}
struct PRLifeRoom* PRLifeRoom_alloc( )
{
	struct PRLifeRoom* result;
	if(PRLifeRoom_ClassInstance==NULL)PRLifeRoom_CreateClass( );
	result=malloc(sizeof(struct PRLifeRoom));
	result->_components=malloc(sizeof(void*)*5);
	result->_class=(void*)&(PRLifeRoom_ClassInstance->className);
	result->_components_PRRoom=result->_components;
	result->_class_PRRoom=(void*)&(PRLifeRoom_ClassInstance->className_PRRoom);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(PRLifeRoom_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRLifeRoom_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_PRRoom);
	result->_components[2]=&(result->_class_GLUIElement);
	result->_components[3]=&(result->_class_CLObject);
	result->_components[4]=NULL;
	return result;
}
void PRLifeRoom_init_name_frame_controller (struct PRLifeRoom* self, char * the_name , MLVector4 the_frame , struct PRController * the_controller ) 
{
	PRRoom_init_name_frame_controller(( cast_object( &PRRoom_ClassInstance , self)),the_name,the_frame,the_controller);
	self->my_info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(self->my_info_view, "info_view",MLVector4Create(0,0,800,-600),the_controller);
	PRInfoView_set_color(self->my_info_view, 0,0,0,0);
	PRInfoView_set_level(self->my_info_view, 60);
	PRInfoView_set_title_label(self->my_info_view, "Life and Work");
	PRInfoView_show(self->my_info_view );
	PRLifeRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->my_info_view)));
	CLDataList_add_data(self->info_views, self->my_info_view);
}
void PRLifeRoom_build (struct PRLifeRoom* self ) 
{
	PRLifeRoom_create_image_area( self, "tapeta.png",600,-600,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2.0,0),MLVector3Create(0,0,-200));
	PRLifeRoom_create_image_area( self, "tapeta.png",800,-600,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(0,0,-800));
	PRLifeRoom_create_image_area( self, "floor.png",800,-600,MLVector3Create(1,1,1),MLVector3Create(-M_PI/2.0,0,0),MLVector3Create(0,-600,-800));
	PRLifeRoom_create_image_area( self, "offices.png",600,-300,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(100,-100,-800));
	struct CLString*table_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], "babybed.png");
	char*table_path_c=table_path->_class->c_string( (void*) table_path->_components[0] );
	struct GLBitmapRGBA*table_bitmap=GLBitmapRGBAUtils_create_bitmap_pngpath(NULL,table_path_c);
	self->table_texture=GLTextureSquare_alloc( );
	GLTextureSquare_init_width_height(self->table_texture, table_bitmap->width,table_bitmap->height);
	GLTextureSquare_clone_bitmap(self->table_texture, table_bitmap);
	CLString_release(table_path );
	GLBitmapRGBA_release(table_bitmap );
	free(table_path_c);
	PRLifeRoom_create_texture_area( self, self->table_texture,200,-100,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2,0),MLVector3Create(0,-500,-300));
	PRLifeRoom_create_texture_area( self, self->table_texture,100,-100,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(0,-500,-500));
	PRLifeRoom_create_texture_area( self, self->table_texture,100,-100,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(0,-500,-300));
	PRLifeRoom_create_texture_area( self, self->table_texture,200,-100,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2,0),MLVector3Create(100,-500,-300));
	PRLifeRoom_create_empty_view( self, MLVector3Create(1,1,1),MLVector3Create(0,M_PI/3,0.0),MLVector3Create(0.0,0.0,-200.0));
	PRLifeRoom_create_info_view( self, "en.png","en.png","1979","Birth","I was born in Budapest in the 11th district. I have a brother ( and one half-brother and three half-sisters ).",MLVector3Create(.2,.2,.2),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-350.0,-300.0));
	PRLifeRoom_create_info_view( self, "growing.png","growing.png","1979-1994","Childhood","I spent most of my childhood in Budapest and in the countryside, mainly in Tápiómente and Kóka.",MLVector3Create(.3,.3,.3),MLVector3Create(0,M_PI/2,0.0),MLVector3Create(0.0,-80.0,-300.0));
	PRLifeRoom_create_info_view( self, "gimi.png","gimi.png","1994-1998","Balassi Bálint Gimnázium","A very nice high school in the 17th district.",MLVector3Create(.2,.2,.2),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-100.0,-550.0));
	PRLifeRoom_create_info_view( self, "bme.png","bme.png","1998-2001","BME","Budapest Institute of Technology, information technology. I left the university after three years.",MLVector3Create(.3,.3,.3),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-350.0,-550.0));
	PRLifeRoom_create_empty_view( self, MLVector3Create(1,1,1),MLVector3Create(0,0,0.0),MLVector3Create(0.0,0.0,-800.0));
	PRLifeRoom_create_info_view( self, "small.png","small.png","2001-2005","Freelancer and SME period","I did flash/web programming and 2D/3D/DTP desig for individuals and small, medium enterprises.",MLVector3Create(.16,.16,.16),MLVector3Create(0.0,0.0,0.0),MLVector3Create(150.0,-300.0,-800.0));
	PRLifeRoom_create_info_view( self, "jasmin.png","jasmin.png","2005-2007","livejasmin.com","Lead programmer/Architect at livejasmin.com. During these years livejasmin.com became the biggest adult cam-to-cam site in the world, and we took 60-70 percent of Hungary's international bandwidth :)",MLVector3Create(.15,.15,.15),MLVector3Create(0.0,0.0,0.0),MLVector3Create(250.0,-150.0,-800.0));
	PRLifeRoom_create_info_view( self, "maketv.png","maketv.png","2008","Make.TV","Lead programmer/Architect at Make.Tv Gmbh in Bonn, Germany. It was a very promising startup - combining the functionality of live video, video on demand services and blogging.",MLVector3Create(.2,.2,.2),MLVector3Create(0.0,0.0,0.0),MLVector3Create(400.0,-280.0,-800.0));
	PRLifeRoom_create_info_view( self, "logmein.png","logmein.png","2010-2013","LogMeIn","Senior Software Engineer at the R&D department of Szeged. Worked on almost all products of LogMeIn on the web/iOS/OSX side.",MLVector3Create(.2,.2,.2),MLVector3Create(0,0,0.0),MLVector3Create(550.0,-150.0,-800.0));
}
void PRLifeRoom_destruct (struct PRLifeRoom* self ) 
{
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRLifeRoom_create_info_view (struct PRLifeRoom* self, char * the_image , char * the_large_image , char * the_title_label , char * the_subtitle_label , char * the_description_label , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*small_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_image);
	struct CLString*large_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_large_image);
	char*small_path_c=small_path->_class->c_string( (void*) small_path->_components[0] );
	char*large_path_c=large_path->_class->c_string( (void*) large_path->_components[0] );
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	info_view->small_path=small_path_c;
	info_view->large_path=large_path_c;
	PRInfoView_set_color(info_view, 0,0,0,0);
	PRInfoView_set_level(info_view, 30-(int)self->info_views->length);
	PRInfoView_set_title_label(info_view, the_title_label);
	PRInfoView_set_subtitle_label(info_view, the_subtitle_label);
	PRInfoView_set_description_label(info_view, the_description_label);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	PRInfoView_set_image(info_view, info_view->small_path);
	PRLifeRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLString_release(small_path );
	CLString_release(large_path );
	GLUITrafo_release(local_trafo );
}
void PRLifeRoom_create_empty_view (struct PRLifeRoom* self, MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	PRInfoView_set_color(info_view, 0,0,0,.5);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	info_view->hidden=1;
	PRLifeRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	GLUITrafo_release(local_trafo );
}
void PRLifeRoom_create_texture_area (struct PRLifeRoom* self, struct GLTextureSquare * the_texture , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUIElement*area;
	struct GLUITrafo*area_trafo;
	area_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(area_trafo );
	area_trafo->scale=the_scale;
	area_trafo->rotation=the_rotation;
	area_trafo->translation=the_translation;
	area=GLUIElement_alloc( );
	GLUIElement_init_name_frame(area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height));
	GLUIElement_set_trafo(area, GLUITrafo_matrix(area_trafo ),0);
	GLUIElement_set_texture(area, the_texture->id);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,0,0);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,the_texture->hRatio,1);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,the_texture->hRatio,2);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,0,3);
	PRLifeRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , area)));
	GLUITrafo_release(area_trafo );
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , area)));
}
void PRLifeRoom_create_image_area (struct PRLifeRoom* self, char * the_path , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*image_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_path);
	char*image_path_c=image_path->_class->c_string( (void*) image_path->_components[0] );
	struct GLUITrafo*image_trafo;
	struct GLUIImageArea*image_area;
	image_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(image_trafo );
	image_trafo->scale=the_scale;
	image_trafo->rotation=the_rotation;
	image_trafo->translation=the_translation;
	image_area=GLUIImageArea_alloc( );
	GLUIImageArea_init_name_frame_path(image_area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height),image_path_c);
	GLUIImageArea_set_trafo(image_area, GLUITrafo_matrix(image_trafo ),0);
	PRLifeRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , image_area)));
	GLUITrafo_release(image_trafo );
	CLString_release(image_path );
	free(image_path_c);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , image_area)));
}
void PRLifeRoom_update (struct PRLifeRoom* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	if(self->counter>0)
	{
		self->counter-=1;
		if(self->counter==1)
		{
			self->last_room->_class->collapse( (void*) self->last_room->_components[0] );
			PRLifeRoom_build( self );
		}
	}
}
void PRLifeRoom_step_right (struct PRLifeRoom* self ) 
{
	if(self->counter>0)return;
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==0&&one_view->hidden==0)one_view->_class->show_with_animation( (void*) one_view->_components[0] );
	else
	{
		self->view_index+=1;
		if(self->view_index==self->info_views->length)
		{
			self->view_index=0;
			struct PRInfoView*next_info_view=self->next_room->info_views->_class->data_at_index( (void*) self->next_room->info_views->_components[0], 0);
			self->next_room->counter=151;
			self->controller->actual_room=self->next_room;
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , next_info_view)),150,kGLUIAnimationEaseIn);
		}
		else
		{
			one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRLifeRoom_step_left (struct PRLifeRoom* self ) 
{
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
	else
	{
		self->view_index-=1;
		if(self->view_index<0)self->view_index=0;
		else
		{
			struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRLifeRoom_collapse (struct PRLifeRoom* self ) 
{
	struct CLLink*link0;
	void* kid_data;
	link0=self->removables->head;while( link0!=NULL){kid_data=link0->data; 
	
		struct GLUIElement*kid=kid_data;
		PRLifeRoom_remove_element( self, kid);
		kid->_class->release( (void*) kid->_components[0] );
	link0=link0->next;}
	self->view_index=0;
	self->info_views->_class->remove_all_data( (void*) self->info_views->_components[0] );
	self->removables->_class->remove_all_data( (void*) self->removables->_components[0] );
	self->info_views->_class->add_data( (void*) self->info_views->_components[0], self->my_info_view);
}
void PRLifeRoom_init_name_frame (struct PRLifeRoom* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	PRLifeRoom_update_frame( self );
}
void PRLifeRoom_set_level (struct PRLifeRoom* self, int the_level ) 
{
	self->level=the_level;
}
void PRLifeRoom_set_group (struct PRLifeRoom* self, int the_group ) 
{
	self->group=the_group;
}
void PRLifeRoom_set_texture (struct PRLifeRoom* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void PRLifeRoom_set_texture_coords (struct PRLifeRoom* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void PRLifeRoom_set_color (struct PRLifeRoom* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void PRLifeRoom_set_origo (struct PRLifeRoom* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	PRLifeRoom_update_frame( self );
}
void PRLifeRoom_set_extent (struct PRLifeRoom* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	PRLifeRoom_update_frame( self );
}
void PRLifeRoom_set_trafo (struct PRLifeRoom* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)PRLifeRoom_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)PRLifeRoom_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)PRLifeRoom_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)PRLifeRoom_attach( self, one_drawer);
		}
	}
	PRLifeRoom_update_trafo( self );
}
void PRLifeRoom_update_frame (struct PRLifeRoom* self ) 
{
	struct CLLink*link1;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link1=self->kids->head;while( link1!=NULL){data=link1->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link1=link1->next;}
	}
}
void PRLifeRoom_update_trafo (struct PRLifeRoom* self ) 
{
	struct CLLink*link2;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link2=self->kids->head;while( link2!=NULL){data=link2->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link2=link2->next;}
	}
}
void PRLifeRoom_get_absolute_frame (struct PRLifeRoom* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void PRLifeRoom_finalize_frame (struct PRLifeRoom* self ) 
{
	MLVector3 a,b,c,d;
	PRLifeRoom_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void PRLifeRoom_add_element (struct PRLifeRoom* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void PRLifeRoom_remove_element (struct PRLifeRoom* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void PRLifeRoom_attach (struct PRLifeRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link3;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	PRLifeRoom_update_frame( self );
	PRLifeRoom_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link3=self->kids->head;while( link3!=NULL){data=link3->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link3=link3->next;}
}
void PRLifeRoom_detach (struct PRLifeRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link4;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link4=self->kids->head;while( link4!=NULL){data=link4->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link4=link4->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 PRLifeRoom_get_relative_touch_line_a_line_b (struct PRLifeRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	PRLifeRoom_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void PRLifeRoom_intersect_line_a_line_b_elements (struct PRLifeRoom* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link5;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=PRLifeRoom_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link5=self->kids->head;while( link5!=NULL){data=link5->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link5=link5->next;}
	}
}
void PRLifeRoom_touch_began (struct PRLifeRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRLifeRoom_touch_moved (struct PRLifeRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRLifeRoom_touch_ended (struct PRLifeRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRLifeRoom_key_down_characters (struct PRLifeRoom* self, char * the_characters ) 
{

}
void PRLifeRoom_key_up_characters (struct PRLifeRoom* self, char * the_characters ) 
{

}
void PRLifeRoom_scroll_x_y (struct PRLifeRoom* self, float the_x , float the_y ) 
{

}
void PRLifeRoom_focus_on (struct PRLifeRoom* self ) 
{

}
void PRLifeRoom_focus_off (struct PRLifeRoom* self ) 
{

}
void PRLifeRoom_init (struct PRLifeRoom* self ) 
{
	self->retain_count=1;
}
void PRLifeRoom_retain (struct PRLifeRoom* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRLifeRoom_release (struct PRLifeRoom* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRLifeRoom_event (struct PRLifeRoom* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRLifeRoom_describe (struct PRLifeRoom* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRSettings_CreateClass( )
{
	PRSettings_ClassInstance=malloc(sizeof(struct PRSettings_Class));
	PRSettings_ClassInstance->className="PRSettings";
	PRSettings_ClassInstance->classId=&PRSettings_ClassInstance;
	PRSettings_ClassInstance->init_resources_path=PRSettings_init_resources_path;
	PRSettings_ClassInstance->destruct=PRSettings_destruct;
	PRSettings_ClassInstance->path_for_file=PRSettings_path_for_file;
	PRSettings_ClassInstance->className_CLObject="CLObject";
	PRSettings_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRSettings_ClassInstance->init=PRSettings_init;
	PRSettings_ClassInstance->destruct_CLObject=PRSettings_destruct;
	PRSettings_ClassInstance->retain=PRSettings_retain;
	PRSettings_ClassInstance->release=PRSettings_release;
	PRSettings_ClassInstance->event=PRSettings_event;
	PRSettings_ClassInstance->describe=PRSettings_describe;
	
}
struct PRSettings* PRSettings_alloc( )
{
	struct PRSettings* result;
	if(PRSettings_ClassInstance==NULL)PRSettings_CreateClass( );
	result=malloc(sizeof(struct PRSettings));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PRSettings_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRSettings_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PRSettings_init_resources_path (struct PRSettings* self, char * the_path ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->font_path=CLString_alloc( );
	CLString_init_cstring(self->font_path, the_path);
	CLString_append_cstring(self->font_path, "/Avenir.ttc");
	self->resources_path=CLString_alloc( );
	CLString_init_cstring(self->resources_path, the_path);
}
void PRSettings_destruct (struct PRSettings* self ) 
{
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
struct CLString * PRSettings_path_for_file (struct PRSettings* self, char * the_file ) 
{
	struct CLString*result;
	result=CLString_alloc( );
	CLString_init(result );
	CLString_append_string(result, self->resources_path);
	CLString_append_cstring(result, "/");
	CLString_append_cstring(result, the_file);
	return result;
}
void PRSettings_init (struct PRSettings* self ) 
{
	self->retain_count=1;
}
void PRSettings_retain (struct PRSettings* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRSettings_release (struct PRSettings* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRSettings_event (struct PRSettings* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRSettings_describe (struct PRSettings* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRMeasures_CreateClass( )
{
	PRMeasures_ClassInstance=malloc(sizeof(struct PRMeasures_Class));
	PRMeasures_ClassInstance->className="PRMeasures";
	PRMeasures_ClassInstance->classId=&PRMeasures_ClassInstance;
	PRMeasures_ClassInstance->init_width_height=PRMeasures_init_width_height;
	PRMeasures_ClassInstance->className_CLObject="CLObject";
	PRMeasures_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRMeasures_ClassInstance->init=PRMeasures_init;
	PRMeasures_ClassInstance->destruct=PRMeasures_destruct;
	PRMeasures_ClassInstance->retain=PRMeasures_retain;
	PRMeasures_ClassInstance->release=PRMeasures_release;
	PRMeasures_ClassInstance->event=PRMeasures_event;
	PRMeasures_ClassInstance->describe=PRMeasures_describe;
	
}
struct PRMeasures* PRMeasures_alloc( )
{
	struct PRMeasures* result;
	if(PRMeasures_ClassInstance==NULL)PRMeasures_CreateClass( );
	result=malloc(sizeof(struct PRMeasures));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PRMeasures_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRMeasures_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PRMeasures_init_width_height (struct PRMeasures* self, float the_width , float the_height ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->border=the_width*.05;
	self->vertical_center=the_height/2.0;
	self->horizontal_center=the_width/2.0;
	self->header_height=the_height/10.0;
	self->button_size=the_height/10.0;
	self->header_font_size=self->header_height*.5;
	self->normal_font_size=self->header_height*.5;
	self->centered_width_small=the_width*.6;
	self->centered_width_large=the_width*.9;
	self->centered_width_medium=the_width*.7;
}
void PRMeasures_init (struct PRMeasures* self ) 
{
	self->retain_count=1;
}
void PRMeasures_destruct (struct PRMeasures* self ) 
{

}
void PRMeasures_retain (struct PRMeasures* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRMeasures_release (struct PRMeasures* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRMeasures_event (struct PRMeasures* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRMeasures_describe (struct PRMeasures* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRInfoView_CreateClass( )
{
	PRInfoView_ClassInstance=malloc(sizeof(struct PRInfoView_Class));
	PRInfoView_ClassInstance->className="PRInfoView";
	PRInfoView_ClassInstance->classId=&PRInfoView_ClassInstance;
	PRInfoView_ClassInstance->init_name_frame_controller=PRInfoView_init_name_frame_controller;
	PRInfoView_ClassInstance->destruct=PRInfoView_destruct;
	PRInfoView_ClassInstance->set_title_label=PRInfoView_set_title_label;
	PRInfoView_ClassInstance->set_subtitle_label=PRInfoView_set_subtitle_label;
	PRInfoView_ClassInstance->set_description_label=PRInfoView_set_description_label;
	PRInfoView_ClassInstance->show=PRInfoView_show;
	PRInfoView_ClassInstance->show_with_animation=PRInfoView_show_with_animation;
	PRInfoView_ClassInstance->hide=PRInfoView_hide;
	PRInfoView_ClassInstance->load_large=PRInfoView_load_large;
	PRInfoView_ClassInstance->set_image=PRInfoView_set_image;
	PRInfoView_ClassInstance->update=PRInfoView_update;
	PRInfoView_ClassInstance->event=PRInfoView_event;
	PRInfoView_ClassInstance->className_GLUIElement="GLUIElement";
	PRInfoView_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	PRInfoView_ClassInstance->init_name_frame=PRInfoView_init_name_frame;
	PRInfoView_ClassInstance->destruct_GLUIElement=PRInfoView_destruct;
	PRInfoView_ClassInstance->set_level=PRInfoView_set_level;
	PRInfoView_ClassInstance->set_group=PRInfoView_set_group;
	PRInfoView_ClassInstance->set_texture=PRInfoView_set_texture;
	PRInfoView_ClassInstance->set_texture_coords=PRInfoView_set_texture_coords;
	PRInfoView_ClassInstance->set_color=PRInfoView_set_color;
	PRInfoView_ClassInstance->set_origo=PRInfoView_set_origo;
	PRInfoView_ClassInstance->set_extent=PRInfoView_set_extent;
	PRInfoView_ClassInstance->set_trafo=PRInfoView_set_trafo;
	PRInfoView_ClassInstance->update_GLUIElement=PRInfoView_update;
	PRInfoView_ClassInstance->update_frame=PRInfoView_update_frame;
	PRInfoView_ClassInstance->update_trafo=PRInfoView_update_trafo;
	PRInfoView_ClassInstance->get_absolute_frame=PRInfoView_get_absolute_frame;
	PRInfoView_ClassInstance->finalize_frame=PRInfoView_finalize_frame;
	PRInfoView_ClassInstance->add_element=PRInfoView_add_element;
	PRInfoView_ClassInstance->remove_element=PRInfoView_remove_element;
	PRInfoView_ClassInstance->attach=PRInfoView_attach;
	PRInfoView_ClassInstance->detach=PRInfoView_detach;
	PRInfoView_ClassInstance->get_relative_touch_line_a_line_b=PRInfoView_get_relative_touch_line_a_line_b;
	PRInfoView_ClassInstance->intersect_line_a_line_b_elements=PRInfoView_intersect_line_a_line_b_elements;
	PRInfoView_ClassInstance->touch_began=PRInfoView_touch_began;
	PRInfoView_ClassInstance->touch_moved=PRInfoView_touch_moved;
	PRInfoView_ClassInstance->touch_ended=PRInfoView_touch_ended;
	PRInfoView_ClassInstance->key_down_characters=PRInfoView_key_down_characters;
	PRInfoView_ClassInstance->key_up_characters=PRInfoView_key_up_characters;
	PRInfoView_ClassInstance->scroll_x_y=PRInfoView_scroll_x_y;
	PRInfoView_ClassInstance->focus_on=PRInfoView_focus_on;
	PRInfoView_ClassInstance->focus_off=PRInfoView_focus_off;
	PRInfoView_ClassInstance->className_CLObject="CLObject";
	PRInfoView_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRInfoView_ClassInstance->init=PRInfoView_init;
	PRInfoView_ClassInstance->destruct_CLObject=PRInfoView_destruct;
	PRInfoView_ClassInstance->retain=PRInfoView_retain;
	PRInfoView_ClassInstance->release=PRInfoView_release;
	PRInfoView_ClassInstance->event_CLObject=PRInfoView_event;
	PRInfoView_ClassInstance->describe=PRInfoView_describe;
	
}
struct PRInfoView* PRInfoView_alloc( )
{
	struct PRInfoView* result;
	if(PRInfoView_ClassInstance==NULL)PRInfoView_CreateClass( );
	result=malloc(sizeof(struct PRInfoView));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(PRInfoView_ClassInstance->className);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(PRInfoView_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRInfoView_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLUIElement);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void PRInfoView_init_name_frame_controller (struct PRInfoView* self, char * the_name , MLVector4 the_frame , struct PRController * the_controller ) 
{
	GLUIElement_init_name_frame(( cast_object( &GLUIElement_ClassInstance , self)),the_name,the_frame);
	self->controller=the_controller;
	self->hidden=0;
	self->info_shown=0;
	self->picture=NULL;
	self->small_path=NULL;
	self->large_path=NULL;
	self->animator=GLUITrafoAnimator_alloc( );
	GLUITrafoAnimator_init(self->animator );
	self->background=GLUIElement_alloc( );
	GLUIElement_init_name_frame(self->background, "PRInfoView.background",MLVector4Create(self->controller->measures->border,-self->controller->measures->border,self->extent.x-2*self->controller->measures->border,self->extent.y+2*self->controller->measures->border));
	GLUIElement_set_color(self->background, 0,0,0,.5);
	GLUIElement_set_level(self->background, 1);
	self->title=GLUIParagraph_alloc( );
	GLUIParagraph_init_name_frame_font_type_align_multiline(self->title, "PRInfoView.title",MLVector4Create(self->controller->measures->border,-self->controller->measures->border-self->controller->measures->header_height,self->extent.x-2*self->controller->measures->border,-self->controller->measures->header_height),self->controller->font_manager->_class->font_for_name_size_r_g_b( (void*) self->controller->font_manager->_components[0], "Avenir.ttc",self->controller->measures->header_height,255,255,255),kGLUIParagraphTypeOutput,kTLTextMetricsAlignCenter,1);
	GLUIParagraph_set_color(self->title, 0,0,0,0);
	GLUIParagraph_set_level(self->title, 2);
	self->subtitle=GLUIParagraph_alloc( );
	GLUIParagraph_init_name_frame_font_type_align_multiline(self->subtitle, "PRInfoView.subtitle",MLVector4Create(self->controller->measures->border,-self->controller->measures->border-self->controller->measures->header_height*2,self->extent.x-2*self->controller->measures->border,-self->controller->measures->header_height),self->controller->font_manager->_class->font_for_name_size_r_g_b( (void*) self->controller->font_manager->_components[0], "Avenir.ttc",self->controller->measures->header_font_size,255,255,255),kGLUIParagraphTypeOutput,kTLTextMetricsAlignCenter,1);
	GLUIParagraph_set_color(self->subtitle, 0,0,0,0);
	GLUIParagraph_set_level(self->subtitle, 2);
	self->description=GLUIParagraph_alloc( );
	GLUIParagraph_init_name_frame_font_type_align_multiline(self->description, "PRInfoView.description",MLVector4Create(self->controller->measures->border*2,-self->controller->measures->border-self->controller->measures->header_height*3,self->extent.x-4*self->controller->measures->border,self->extent.y-3*self->controller->measures->header_height),self->controller->font_manager->_class->font_for_name_size_r_g_b( (void*) self->controller->font_manager->_components[0], "Avenir.ttc",self->controller->measures->header_font_size,255,255,255),kGLUIParagraphTypeOutput,kTLTextMetricsAlignCenter,1);
	GLUIParagraph_set_color(self->description, 0,0,0,0);
	GLUIParagraph_set_level(self->description, 2);
}
void PRInfoView_destruct (struct PRInfoView* self ) 
{
	GLUIParagraph_release(self->description );
	GLUIParagraph_release(self->subtitle );
	GLUIParagraph_release(self->title );
	GLUIElement_release(self->background );
	GLUITrafoAnimator_release(self->animator );
	if(self->picture!=NULL) GLUIImageArea_release(self->picture );
	if(self->small_path!=NULL)free(self->small_path);
	if(self->large_path!=NULL)free(self->large_path);
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRInfoView_set_title_label (struct PRInfoView* self, char * the_label ) 
{
	GLUIParagraph_add_text(self->title, the_label);
}
void PRInfoView_set_subtitle_label (struct PRInfoView* self, char * the_label ) 
{
	GLUIParagraph_add_text(self->subtitle, the_label);
}
void PRInfoView_set_description_label (struct PRInfoView* self, char * the_label ) 
{
	GLUIParagraph_add_text(self->description, the_label);
}
void PRInfoView_show (struct PRInfoView* self ) 
{
	if(self->hidden==1)return;
	self->info_shown=1;
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->background)));
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->title)));
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->subtitle)));
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->description)));
}
void PRInfoView_show_with_animation (struct PRInfoView* self ) 
{
	if(self->hidden==1)return;
	self->info_shown=1;
	struct GLUITrafo*old_trafo;
	struct GLUITrafo*new_trafo;
	old_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(old_trafo );
	new_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(new_trafo );
	(old_trafo->scale).x=.1;
	(old_trafo->scale).y=.1;
	struct GLUITrafoAnimation*the_animation;
	the_animation=GLUITrafoAnimation_alloc( );
	GLUITrafoAnimation_init_start_end_steps_easing(the_animation, old_trafo,new_trafo,50,kGLUIAnimationEaseIn);
	the_animation->delegate=(cast_object( &CLObject_ClassInstance , self));
	GLUITrafoAnimator_add_animation(self->animator, the_animation);
	MLMatrix4 matrix=MLMatrix4CreateIdentity();
	matrix=MLMatrix4Translate(matrix,(self->background->combined_origo).x+(self->background->extent).x/2,(self->background->combined_origo).y+(self->background->extent).y/2,0);
	matrix=MLMatrix4Multiply(matrix, GLUITrafo_matrix(old_trafo ));
	matrix=MLMatrix4Translate(matrix,-(self->background->combined_origo).x-(self->background->extent).x/2,-(self->background->combined_origo).y-(self->background->extent).y/2,0);
	GLUIElement_set_trafo(self->background, matrix,0);
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->background)));
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->title)));
	GLUIParagraph_animate_glyphs(self->title );
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->subtitle)));
	GLUIParagraph_animate_glyphs(self->subtitle );
	GLUITrafo_release(old_trafo );
	GLUITrafo_release(new_trafo );
	GLUITrafoAnimation_release(the_animation );
}
void PRInfoView_hide (struct PRInfoView* self ) 
{
	if(self->hidden==1)return;
	self->info_shown=0;
	self->needs_redraw=1;
	PRInfoView_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->background)));
	PRInfoView_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->title)));
	PRInfoView_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->subtitle)));
	PRInfoView_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->description)));
}
void PRInfoView_load_large (struct PRInfoView* self ) 
{
	PRInfoView_set_image( self, self->large_path);
}
void PRInfoView_set_image (struct PRInfoView* self, char * the_image ) 
{
	if(self->picture!=NULL&&self->picture->parent!=NULL)PRInfoView_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->picture)));
	self->picture=GLUIImageArea_alloc( );
	GLUIImageArea_init_name_frame_path(self->picture, "GLUIListSquare.ui_image",MLVector4Create(50,-50,self->extent.x-100,self->extent.y+100),the_image);
	float wthdiff=(self->picture->extent).x/(float)self->picture->bitmap->width;
	float hthdiff=-(self->picture->extent).y/(float)self->picture->bitmap->height;
	if(fabs(wthdiff)<fabs(hthdiff))
	{
		float ratio=(self->picture->extent).x/(float)self->picture->bitmap->width;
		self->picture->_class->set_extent( (void*) self->picture->_components[0], MLVector3Create((float)self->picture->bitmap->width*ratio,-(float)self->picture->bitmap->height*ratio,0));
	}
	else
	{
		float ratio=-(self->picture->extent).y/(float)self->picture->bitmap->height;
		self->picture->_class->set_extent( (void*) self->picture->_components[0], MLVector3Create((float)self->picture->bitmap->width*ratio,-(float)self->picture->bitmap->height*ratio,0));
	}
	GLUIImageArea_set_origo(self->picture, MLVector3Create(50+(self->extent.x-100.0-(self->picture->extent).x)/2,50+(self->extent.y-100.0-(self->picture->extent).y)/2,0));
	PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->picture)));
}
void PRInfoView_update (struct PRInfoView* self ) 
{
	if(self->animator->animation!=NULL)
	{
		self->needs_redraw=1;
		MLMatrix4 new_trafo=MLMatrix4CreateIdentity();
		new_trafo=MLMatrix4Translate(new_trafo,(self->background->combined_origo).x+(self->background->extent).x/2,(self->background->combined_origo).y+(self->background->extent).y/2,0);
		new_trafo=MLMatrix4Multiply(new_trafo,self->animator->animation->actual->_class->matrix( (void*) self->animator->animation->actual->_components[0] ));
		new_trafo=MLMatrix4Translate(new_trafo,-(self->background->combined_origo).x-(self->background->extent).x/2,-(self->background->combined_origo).y-(self->background->extent).y/2,0);
		self->background->_class->set_trafo( (void*) self->background->_components[0], new_trafo,0);
		GLUITrafoAnimator_update(self->animator );
	}
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRInfoView_event (struct PRInfoView* self, int the_id , void * the_source , void * the_data ) 
{
	if(the_id==kGLUIAnimationFinished)
	{
		PRInfoView_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->description)));
		GLUIParagraph_animate_glyphs(self->description );
	}
}
void PRInfoView_init_name_frame (struct PRInfoView* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	PRInfoView_update_frame( self );
}
void PRInfoView_set_level (struct PRInfoView* self, int the_level ) 
{
	self->level=the_level;
}
void PRInfoView_set_group (struct PRInfoView* self, int the_group ) 
{
	self->group=the_group;
}
void PRInfoView_set_texture (struct PRInfoView* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void PRInfoView_set_texture_coords (struct PRInfoView* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void PRInfoView_set_color (struct PRInfoView* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void PRInfoView_set_origo (struct PRInfoView* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	PRInfoView_update_frame( self );
}
void PRInfoView_set_extent (struct PRInfoView* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	PRInfoView_update_frame( self );
}
void PRInfoView_set_trafo (struct PRInfoView* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)PRInfoView_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)PRInfoView_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)PRInfoView_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)PRInfoView_attach( self, one_drawer);
		}
	}
	PRInfoView_update_trafo( self );
}
void PRInfoView_update_frame (struct PRInfoView* self ) 
{
	struct CLLink*link6;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link6=self->kids->head;while( link6!=NULL){data=link6->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link6=link6->next;}
	}
}
void PRInfoView_update_trafo (struct PRInfoView* self ) 
{
	struct CLLink*link7;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link7=self->kids->head;while( link7!=NULL){data=link7->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link7=link7->next;}
	}
}
void PRInfoView_get_absolute_frame (struct PRInfoView* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void PRInfoView_finalize_frame (struct PRInfoView* self ) 
{
	MLVector3 a,b,c,d;
	PRInfoView_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void PRInfoView_add_element (struct PRInfoView* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void PRInfoView_remove_element (struct PRInfoView* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void PRInfoView_attach (struct PRInfoView* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link8;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	PRInfoView_update_frame( self );
	PRInfoView_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link8=self->kids->head;while( link8!=NULL){data=link8->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link8=link8->next;}
}
void PRInfoView_detach (struct PRInfoView* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link9;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link9=self->kids->head;while( link9!=NULL){data=link9->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link9=link9->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 PRInfoView_get_relative_touch_line_a_line_b (struct PRInfoView* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	PRInfoView_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void PRInfoView_intersect_line_a_line_b_elements (struct PRInfoView* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link10;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=PRInfoView_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link10=self->kids->head;while( link10!=NULL){data=link10->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link10=link10->next;}
	}
}
void PRInfoView_touch_began (struct PRInfoView* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRInfoView_touch_moved (struct PRInfoView* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRInfoView_touch_ended (struct PRInfoView* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRInfoView_key_down_characters (struct PRInfoView* self, char * the_characters ) 
{

}
void PRInfoView_key_up_characters (struct PRInfoView* self, char * the_characters ) 
{

}
void PRInfoView_scroll_x_y (struct PRInfoView* self, float the_x , float the_y ) 
{

}
void PRInfoView_focus_on (struct PRInfoView* self ) 
{

}
void PRInfoView_focus_off (struct PRInfoView* self ) 
{

}
void PRInfoView_init (struct PRInfoView* self ) 
{
	self->retain_count=1;
}
void PRInfoView_retain (struct PRInfoView* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRInfoView_release (struct PRInfoView* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRInfoView_describe (struct PRInfoView* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRFontManager_CreateClass( )
{
	PRFontManager_ClassInstance=malloc(sizeof(struct PRFontManager_Class));
	PRFontManager_ClassInstance->className="PRFontManager";
	PRFontManager_ClassInstance->classId=&PRFontManager_ClassInstance;
	PRFontManager_ClassInstance->init_settings=PRFontManager_init_settings;
	PRFontManager_ClassInstance->destruct=PRFontManager_destruct;
	PRFontManager_ClassInstance->font_for_name_size_r_g_b=PRFontManager_font_for_name_size_r_g_b;
	PRFontManager_ClassInstance->className_CLObject="CLObject";
	PRFontManager_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRFontManager_ClassInstance->init=PRFontManager_init;
	PRFontManager_ClassInstance->destruct_CLObject=PRFontManager_destruct;
	PRFontManager_ClassInstance->retain=PRFontManager_retain;
	PRFontManager_ClassInstance->release=PRFontManager_release;
	PRFontManager_ClassInstance->event=PRFontManager_event;
	PRFontManager_ClassInstance->describe=PRFontManager_describe;
	
}
struct PRFontManager* PRFontManager_alloc( )
{
	struct PRFontManager* result;
	if(PRFontManager_ClassInstance==NULL)PRFontManager_CreateClass( );
	result=malloc(sizeof(struct PRFontManager));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PRFontManager_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRFontManager_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PRFontManager_init_settings (struct PRFontManager* self, struct PRSettings * the_settings ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->fonts=CLDataList_alloc( );
	CLDataList_init(self->fonts );
	self->settings=the_settings;
}
void PRFontManager_destruct (struct PRFontManager* self ) 
{
	CLDataList_release(self->fonts );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
struct GLFontTrueType * PRFontManager_font_for_name_size_r_g_b (struct PRFontManager* self, char * the_name , float the_size , int the_r , int the_g , int the_b ) 
{
	struct CLLink*link11;
	void* fontData;
	struct GLFontTrueType*font;
	link11=self->fonts->head;while( link11!=NULL){fontData=link11->data; 
	
		font=fontData;
		if(font->name==the_name&&font->font_size==the_size&&font->r==the_r&&font->g==the_g&&font->b==the_b)return font;
	link11=link11->next;}
	struct CLString*path=self->settings->_class->path_for_file( (void*) self->settings->_components[0], the_name);
	char*path_c=path->_class->c_string( (void*) path->_components[0] );
	font=GLFontTrueType_alloc( );
	GLFontTrueType_init_name_path_size_r_g_b(font, the_name,path_c,the_size,the_r,the_g,the_b);
	CLDataList_add_data(self->fonts, font);
	CLString_release(path );
	free(path_c);
	return font;
}
void PRFontManager_init (struct PRFontManager* self ) 
{
	self->retain_count=1;
}
void PRFontManager_retain (struct PRFontManager* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRFontManager_release (struct PRFontManager* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRFontManager_event (struct PRFontManager* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRFontManager_describe (struct PRFontManager* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIImageArea_CreateClass( )
{
	GLUIImageArea_ClassInstance=malloc(sizeof(struct GLUIImageArea_Class));
	GLUIImageArea_ClassInstance->className="GLUIImageArea";
	GLUIImageArea_ClassInstance->classId=&GLUIImageArea_ClassInstance;
	GLUIImageArea_ClassInstance->init_name_frame_path=GLUIImageArea_init_name_frame_path;
	GLUIImageArea_ClassInstance->destruct=GLUIImageArea_destruct;
	GLUIImageArea_ClassInstance->className_GLUIElement="GLUIElement";
	GLUIImageArea_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	GLUIImageArea_ClassInstance->init_name_frame=GLUIImageArea_init_name_frame;
	GLUIImageArea_ClassInstance->destruct_GLUIElement=GLUIImageArea_destruct;
	GLUIImageArea_ClassInstance->set_level=GLUIImageArea_set_level;
	GLUIImageArea_ClassInstance->set_group=GLUIImageArea_set_group;
	GLUIImageArea_ClassInstance->set_texture=GLUIImageArea_set_texture;
	GLUIImageArea_ClassInstance->set_texture_coords=GLUIImageArea_set_texture_coords;
	GLUIImageArea_ClassInstance->set_color=GLUIImageArea_set_color;
	GLUIImageArea_ClassInstance->set_origo=GLUIImageArea_set_origo;
	GLUIImageArea_ClassInstance->set_extent=GLUIImageArea_set_extent;
	GLUIImageArea_ClassInstance->set_trafo=GLUIImageArea_set_trafo;
	GLUIImageArea_ClassInstance->update=GLUIImageArea_update;
	GLUIImageArea_ClassInstance->update_frame=GLUIImageArea_update_frame;
	GLUIImageArea_ClassInstance->update_trafo=GLUIImageArea_update_trafo;
	GLUIImageArea_ClassInstance->get_absolute_frame=GLUIImageArea_get_absolute_frame;
	GLUIImageArea_ClassInstance->finalize_frame=GLUIImageArea_finalize_frame;
	GLUIImageArea_ClassInstance->add_element=GLUIImageArea_add_element;
	GLUIImageArea_ClassInstance->remove_element=GLUIImageArea_remove_element;
	GLUIImageArea_ClassInstance->attach=GLUIImageArea_attach;
	GLUIImageArea_ClassInstance->detach=GLUIImageArea_detach;
	GLUIImageArea_ClassInstance->get_relative_touch_line_a_line_b=GLUIImageArea_get_relative_touch_line_a_line_b;
	GLUIImageArea_ClassInstance->intersect_line_a_line_b_elements=GLUIImageArea_intersect_line_a_line_b_elements;
	GLUIImageArea_ClassInstance->touch_began=GLUIImageArea_touch_began;
	GLUIImageArea_ClassInstance->touch_moved=GLUIImageArea_touch_moved;
	GLUIImageArea_ClassInstance->touch_ended=GLUIImageArea_touch_ended;
	GLUIImageArea_ClassInstance->key_down_characters=GLUIImageArea_key_down_characters;
	GLUIImageArea_ClassInstance->key_up_characters=GLUIImageArea_key_up_characters;
	GLUIImageArea_ClassInstance->scroll_x_y=GLUIImageArea_scroll_x_y;
	GLUIImageArea_ClassInstance->focus_on=GLUIImageArea_focus_on;
	GLUIImageArea_ClassInstance->focus_off=GLUIImageArea_focus_off;
	GLUIImageArea_ClassInstance->className_CLObject="CLObject";
	GLUIImageArea_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIImageArea_ClassInstance->init=GLUIImageArea_init;
	GLUIImageArea_ClassInstance->destruct_CLObject=GLUIImageArea_destruct;
	GLUIImageArea_ClassInstance->retain=GLUIImageArea_retain;
	GLUIImageArea_ClassInstance->release=GLUIImageArea_release;
	GLUIImageArea_ClassInstance->event=GLUIImageArea_event;
	GLUIImageArea_ClassInstance->describe=GLUIImageArea_describe;
	
}
struct GLUIImageArea* GLUIImageArea_alloc( )
{
	struct GLUIImageArea* result;
	if(GLUIImageArea_ClassInstance==NULL)GLUIImageArea_CreateClass( );
	result=malloc(sizeof(struct GLUIImageArea));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLUIImageArea_ClassInstance->className);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(GLUIImageArea_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIImageArea_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLUIElement);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLUIImageArea_init_name_frame_path (struct GLUIImageArea* self, char * the_name , MLVector4 the_frame , char * the_path ) 
{
	GLUIElement_init_name_frame(( cast_object( &GLUIElement_ClassInstance , self)),the_name,the_frame);
	self->bitmap=GLBitmapRGBAUtils_create_bitmap_pngpath(NULL,the_path);
	self->texturei=GLTextureSquare_alloc( );
	GLTextureSquare_init_width_height(self->texturei, self->bitmap->width,self->bitmap->height);
	GLTextureSquare_clone_bitmap(self->texturei, self->bitmap);
	self->texture=self->texturei->id;
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], 0,0,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], 0,self->texturei->hRatio,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], self->texturei->wRatio,self->texturei->hRatio,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], self->texturei->wRatio,0,3);
}
void GLUIImageArea_destruct (struct GLUIImageArea* self ) 
{
	GLBitmapRGBA_release(self->bitmap );
	GLTextureSquare_release(self->texturei );
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void GLUIImageArea_init_name_frame (struct GLUIImageArea* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	GLUIImageArea_update_frame( self );
}
void GLUIImageArea_set_level (struct GLUIImageArea* self, int the_level ) 
{
	self->level=the_level;
}
void GLUIImageArea_set_group (struct GLUIImageArea* self, int the_group ) 
{
	self->group=the_group;
}
void GLUIImageArea_set_texture (struct GLUIImageArea* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void GLUIImageArea_set_texture_coords (struct GLUIImageArea* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void GLUIImageArea_set_color (struct GLUIImageArea* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void GLUIImageArea_set_origo (struct GLUIImageArea* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	GLUIImageArea_update_frame( self );
}
void GLUIImageArea_set_extent (struct GLUIImageArea* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	GLUIImageArea_update_frame( self );
}
void GLUIImageArea_set_trafo (struct GLUIImageArea* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)GLUIImageArea_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)GLUIImageArea_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)GLUIImageArea_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)GLUIImageArea_attach( self, one_drawer);
		}
	}
	GLUIImageArea_update_trafo( self );
}
void GLUIImageArea_update (struct GLUIImageArea* self ) 
{
	struct CLLink*link12;
	void* data;
	struct GLUIElement*one_element;
	link12=self->kids->head;while( link12!=NULL){data=link12->data; 
	
		one_element=data;
		one_element->_class->update( (void*) one_element->_components[0] );
		if(one_element->needs_redraw==1)
		{
			one_element->needs_redraw=0;
			self->needs_redraw=1;
		}
	link12=link12->next;}
}
void GLUIImageArea_update_frame (struct GLUIImageArea* self ) 
{
	struct CLLink*link13;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link13=self->kids->head;while( link13!=NULL){data=link13->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link13=link13->next;}
	}
}
void GLUIImageArea_update_trafo (struct GLUIImageArea* self ) 
{
	struct CLLink*link14;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link14=self->kids->head;while( link14!=NULL){data=link14->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link14=link14->next;}
	}
}
void GLUIImageArea_get_absolute_frame (struct GLUIImageArea* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void GLUIImageArea_finalize_frame (struct GLUIImageArea* self ) 
{
	MLVector3 a,b,c,d;
	GLUIImageArea_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void GLUIImageArea_add_element (struct GLUIImageArea* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void GLUIImageArea_remove_element (struct GLUIImageArea* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void GLUIImageArea_attach (struct GLUIImageArea* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link15;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	GLUIImageArea_update_frame( self );
	GLUIImageArea_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link15=self->kids->head;while( link15!=NULL){data=link15->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link15=link15->next;}
}
void GLUIImageArea_detach (struct GLUIImageArea* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link16;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link16=self->kids->head;while( link16!=NULL){data=link16->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link16=link16->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 GLUIImageArea_get_relative_touch_line_a_line_b (struct GLUIImageArea* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	GLUIImageArea_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void GLUIImageArea_intersect_line_a_line_b_elements (struct GLUIImageArea* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link17;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=GLUIImageArea_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link17=self->kids->head;while( link17!=NULL){data=link17->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link17=link17->next;}
	}
}
void GLUIImageArea_touch_began (struct GLUIImageArea* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIImageArea_touch_moved (struct GLUIImageArea* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIImageArea_touch_ended (struct GLUIImageArea* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIImageArea_key_down_characters (struct GLUIImageArea* self, char * the_characters ) 
{

}
void GLUIImageArea_key_up_characters (struct GLUIImageArea* self, char * the_characters ) 
{

}
void GLUIImageArea_scroll_x_y (struct GLUIImageArea* self, float the_x , float the_y ) 
{

}
void GLUIImageArea_focus_on (struct GLUIImageArea* self ) 
{

}
void GLUIImageArea_focus_off (struct GLUIImageArea* self ) 
{

}
void GLUIImageArea_init (struct GLUIImageArea* self ) 
{
	self->retain_count=1;
}
void GLUIImageArea_retain (struct GLUIImageArea* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIImageArea_release (struct GLUIImageArea* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIImageArea_event (struct GLUIImageArea* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIImageArea_describe (struct GLUIImageArea* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIElement_CreateClass( )
{
	GLUIElement_ClassInstance=malloc(sizeof(struct GLUIElement_Class));
	GLUIElement_ClassInstance->className="GLUIElement";
	GLUIElement_ClassInstance->classId=&GLUIElement_ClassInstance;
	GLUIElement_ClassInstance->init_name_frame=GLUIElement_init_name_frame;
	GLUIElement_ClassInstance->destruct=GLUIElement_destruct;
	GLUIElement_ClassInstance->set_level=GLUIElement_set_level;
	GLUIElement_ClassInstance->set_group=GLUIElement_set_group;
	GLUIElement_ClassInstance->set_texture=GLUIElement_set_texture;
	GLUIElement_ClassInstance->set_texture_coords=GLUIElement_set_texture_coords;
	GLUIElement_ClassInstance->set_color=GLUIElement_set_color;
	GLUIElement_ClassInstance->set_origo=GLUIElement_set_origo;
	GLUIElement_ClassInstance->set_extent=GLUIElement_set_extent;
	GLUIElement_ClassInstance->set_trafo=GLUIElement_set_trafo;
	GLUIElement_ClassInstance->update=GLUIElement_update;
	GLUIElement_ClassInstance->update_frame=GLUIElement_update_frame;
	GLUIElement_ClassInstance->update_trafo=GLUIElement_update_trafo;
	GLUIElement_ClassInstance->get_absolute_frame=GLUIElement_get_absolute_frame;
	GLUIElement_ClassInstance->finalize_frame=GLUIElement_finalize_frame;
	GLUIElement_ClassInstance->add_element=GLUIElement_add_element;
	GLUIElement_ClassInstance->remove_element=GLUIElement_remove_element;
	GLUIElement_ClassInstance->attach=GLUIElement_attach;
	GLUIElement_ClassInstance->detach=GLUIElement_detach;
	GLUIElement_ClassInstance->get_relative_touch_line_a_line_b=GLUIElement_get_relative_touch_line_a_line_b;
	GLUIElement_ClassInstance->intersect_line_a_line_b_elements=GLUIElement_intersect_line_a_line_b_elements;
	GLUIElement_ClassInstance->touch_began=GLUIElement_touch_began;
	GLUIElement_ClassInstance->touch_moved=GLUIElement_touch_moved;
	GLUIElement_ClassInstance->touch_ended=GLUIElement_touch_ended;
	GLUIElement_ClassInstance->key_down_characters=GLUIElement_key_down_characters;
	GLUIElement_ClassInstance->key_up_characters=GLUIElement_key_up_characters;
	GLUIElement_ClassInstance->scroll_x_y=GLUIElement_scroll_x_y;
	GLUIElement_ClassInstance->focus_on=GLUIElement_focus_on;
	GLUIElement_ClassInstance->focus_off=GLUIElement_focus_off;
	GLUIElement_ClassInstance->className_CLObject="CLObject";
	GLUIElement_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIElement_ClassInstance->init=GLUIElement_init;
	GLUIElement_ClassInstance->destruct_CLObject=GLUIElement_destruct;
	GLUIElement_ClassInstance->retain=GLUIElement_retain;
	GLUIElement_ClassInstance->release=GLUIElement_release;
	GLUIElement_ClassInstance->event=GLUIElement_event;
	GLUIElement_ClassInstance->describe=GLUIElement_describe;
	
}
struct GLUIElement* GLUIElement_alloc( )
{
	struct GLUIElement* result;
	if(GLUIElement_ClassInstance==NULL)GLUIElement_CreateClass( );
	result=malloc(sizeof(struct GLUIElement));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUIElement_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIElement_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUIElement_init_name_frame (struct GLUIElement* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	GLUIElement_update_frame( self );
}
void GLUIElement_destruct (struct GLUIElement* self ) 
{
	CLDataList_release(self->kids );
	GLUIModel_release(self->model );
	frame:GLUIElement_release( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUIElement_set_level (struct GLUIElement* self, int the_level ) 
{
	self->level=the_level;
}
void GLUIElement_set_group (struct GLUIElement* self, int the_group ) 
{
	self->group=the_group;
}
void GLUIElement_set_texture (struct GLUIElement* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void GLUIElement_set_texture_coords (struct GLUIElement* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void GLUIElement_set_color (struct GLUIElement* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void GLUIElement_set_origo (struct GLUIElement* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	GLUIElement_update_frame( self );
}
void GLUIElement_set_extent (struct GLUIElement* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	GLUIElement_update_frame( self );
}
void GLUIElement_set_trafo (struct GLUIElement* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)GLUIElement_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)GLUIElement_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)GLUIElement_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)GLUIElement_attach( self, one_drawer);
		}
	}
	GLUIElement_update_trafo( self );
}
void GLUIElement_update (struct GLUIElement* self ) 
{
	struct CLLink*link18;
	void* data;
	struct GLUIElement*one_element;
	link18=self->kids->head;while( link18!=NULL){data=link18->data; 
	
		one_element=data;
		one_element->_class->update( (void*) one_element->_components[0] );
		if(one_element->needs_redraw==1)
		{
			one_element->needs_redraw=0;
			self->needs_redraw=1;
		}
	link18=link18->next;}
}
void GLUIElement_update_frame (struct GLUIElement* self ) 
{
	struct CLLink*link19;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link19=self->kids->head;while( link19!=NULL){data=link19->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link19=link19->next;}
	}
}
void GLUIElement_update_trafo (struct GLUIElement* self ) 
{
	struct CLLink*link20;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link20=self->kids->head;while( link20!=NULL){data=link20->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link20=link20->next;}
	}
}
void GLUIElement_get_absolute_frame (struct GLUIElement* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void GLUIElement_finalize_frame (struct GLUIElement* self ) 
{
	MLVector3 a,b,c,d;
	GLUIElement_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void GLUIElement_add_element (struct GLUIElement* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void GLUIElement_remove_element (struct GLUIElement* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void GLUIElement_attach (struct GLUIElement* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link21;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	GLUIElement_update_frame( self );
	GLUIElement_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link21=self->kids->head;while( link21!=NULL){data=link21->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link21=link21->next;}
}
void GLUIElement_detach (struct GLUIElement* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link22;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link22=self->kids->head;while( link22!=NULL){data=link22->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link22=link22->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 GLUIElement_get_relative_touch_line_a_line_b (struct GLUIElement* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	GLUIElement_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void GLUIElement_intersect_line_a_line_b_elements (struct GLUIElement* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link23;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=GLUIElement_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link23=self->kids->head;while( link23!=NULL){data=link23->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link23=link23->next;}
	}
}
void GLUIElement_touch_began (struct GLUIElement* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIElement_touch_moved (struct GLUIElement* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIElement_touch_ended (struct GLUIElement* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIElement_key_down_characters (struct GLUIElement* self, char * the_characters ) 
{

}
void GLUIElement_key_up_characters (struct GLUIElement* self, char * the_characters ) 
{

}
void GLUIElement_scroll_x_y (struct GLUIElement* self, float the_x , float the_y ) 
{

}
void GLUIElement_focus_on (struct GLUIElement* self ) 
{

}
void GLUIElement_focus_off (struct GLUIElement* self ) 
{

}
void GLUIElement_init (struct GLUIElement* self ) 
{
	self->retain_count=1;
}
void GLUIElement_retain (struct GLUIElement* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIElement_release (struct GLUIElement* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIElement_event (struct GLUIElement* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIElement_describe (struct GLUIElement* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIController_CreateClass( )
{
	GLUIController_ClassInstance=malloc(sizeof(struct GLUIController_Class));
	GLUIController_ClassInstance->className="GLUIController";
	GLUIController_ClassInstance->classId=&GLUIController_ClassInstance;
	GLUIController_ClassInstance->init_fov_width_height_nead_far=GLUIController_init_fov_width_height_nead_far;
	GLUIController_ClassInstance->destruct=GLUIController_destruct;
	GLUIController_ClassInstance->update=GLUIController_update;
	GLUIController_ClassInstance->render=GLUIController_render;
	GLUIController_ClassInstance->zoom_to_element=GLUIController_zoom_to_element;
	GLUIController_ClassInstance->zoom_to_ui_trafo=GLUIController_zoom_to_ui_trafo;
	GLUIController_ClassInstance->set_view_ui_trafo=GLUIController_set_view_ui_trafo;
	GLUIController_ClassInstance->set_view_trafo=GLUIController_set_view_trafo;
	GLUIController_ClassInstance->add_element=GLUIController_add_element;
	GLUIController_ClassInstance->remove_element=GLUIController_remove_element;
	GLUIController_ClassInstance->set_focus=GLUIController_set_focus;
	GLUIController_ClassInstance->intersected_elements_at_x_y=GLUIController_intersected_elements_at_x_y;
	GLUIController_ClassInstance->mouse_down_at_x_y=GLUIController_mouse_down_at_x_y;
	GLUIController_ClassInstance->mouse_up_at_x_y=GLUIController_mouse_up_at_x_y;
	GLUIController_ClassInstance->mouse_move_at_x_y=GLUIController_mouse_move_at_x_y;
	GLUIController_ClassInstance->key_down_characters=GLUIController_key_down_characters;
	GLUIController_ClassInstance->scroll_x_y=GLUIController_scroll_x_y;
	GLUIController_ClassInstance->className_CLObject="CLObject";
	GLUIController_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIController_ClassInstance->init=GLUIController_init;
	GLUIController_ClassInstance->destruct_CLObject=GLUIController_destruct;
	GLUIController_ClassInstance->retain=GLUIController_retain;
	GLUIController_ClassInstance->release=GLUIController_release;
	GLUIController_ClassInstance->event=GLUIController_event;
	GLUIController_ClassInstance->describe=GLUIController_describe;
	
}
struct GLUIController* GLUIController_alloc( )
{
	struct GLUIController* result;
	if(GLUIController_ClassInstance==NULL)GLUIController_CreateClass( );
	result=malloc(sizeof(struct GLUIController));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUIController_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIController_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUIController_init_fov_width_height_nead_far (struct GLUIController* self, float the_fov , float the_width , float the_height , float the_near , float the_far ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->shader=GLUIShader_alloc( );
	GLUIShader_init(self->shader );
	self->drawer=GLUIModelDrawer_alloc( );
	GLUIModelDrawer_init(self->drawer );
	GLUIModelDrawer_addAttribute_location_components_identifier(self->drawer, 0,3,"positionVector");
	GLUIModelDrawer_addAttribute_location_components_identifier(self->drawer, 1,4,"colorVector");
	GLUIModelDrawer_addAttribute_location_components_identifier(self->drawer, 2,2,"textureVector");
	self->drawer->trafo_location=self->shader->_class->uniform_location_for_identifier( (void*) self->shader->_components[0], "modelMatrix");
	self->drawer->notex_location=self->shader->_class->uniform_location_for_identifier( (void*) self->shader->_components[0], "notex");
	self->view_animator=GLUITrafoAnimator_alloc( );
	GLUITrafoAnimator_init(self->view_animator );
	self->view_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(self->view_trafo );
	self->base=GLUIElement_alloc( );
	GLUIElement_init_name_frame(self->base, "Base",MLVector4Create(0.0,0.0,0.0,0.0));
	GLUIElement_set_trafo(self->base, MLMatrix4CreateIdentity(),0);
	self->base->drawer=self->drawer;
	self->touched=NULL;
	self->focused=NULL;
	self->width=the_width;
	self->height=the_height;
	self->needs_redraw=1;
	self->mouse_is_down=0;
	self->projection_ul=self->shader->_class->uniform_location_for_identifier( (void*) self->shader->_components[0], "projectionMatrix");
	self->fov_x=the_fov*self->width/self->height;
	self->fov_y=the_fov;
	self->eye_z=(self->height/2.0)/(tanf(the_fov/2.0));
	self->view_matrix=MLMatrix4CreateTranslation(-self->width/2.0,self->height/2.0,-self->eye_z);
	self->perspective_matrix=MLMatrix4CreatePerspective(the_fov,self->width/self->height,the_near,the_far);
	self->projection_matrix=MLMatrix4Multiply(self->perspective_matrix,self->view_matrix);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glViewport(0.0,0.0,self->width,self->height);
	glClearColor(0.0,0.0,0.0,1.0);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
void GLUIController_destruct (struct GLUIController* self ) 
{
	GLUIElement_release(self->base );
	GLUIShader_release(self->shader );
	GLUIModelDrawer_release(self->drawer );
	GLUITrafo_release(self->view_trafo );
	GLUITrafoAnimator_release(self->view_animator );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUIController_update (struct GLUIController* self ) 
{
	GLUIElement_update(self->base );
	if(self->base->needs_redraw==1||self->view_animator->animation!=NULL)
	{
		if(self->view_animator->animation!=NULL)GLUIController_set_view_ui_trafo( self, self->view_animator->animation->actual);
		GLUITrafoAnimator_update(self->view_animator );
		self->base->needs_redraw=0;
		self->needs_redraw=2;
	}
}
void GLUIController_render (struct GLUIController* self ) 
{
	if(self->needs_redraw>0)
	{
		GLfloat matrix[16];
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		GLUIShader_use(self->shader );
		MLMatrix4ToArray(&self->projection_matrix,matrix);
		glUniformMatrix4fv(self->projection_ul,1,0,matrix);
		GLUIModelDrawer_render(self->drawer );
		self->needs_redraw-=1;
	}
}
void GLUIController_zoom_to_element (struct GLUIController* self, struct GLUIElement * the_element , int the_steps , char the_easing ) 
{
	MLVector3 a,b,c,d;
	struct GLUITrafo*new_trafo;
	the_element->_class->get_absolute_frame( (void*) the_element->_components[0], &a,&b,&c,&d);
	MLVector3 unit_x=MLVector3Sub(c,b);
	MLVector3 unit_y=MLVector3Sub(a,b);
	float scale_x=MLVector3Length(unit_x)/(the_element->extent).x;
	unit_x=MLVector3Scale(unit_x,1/MLVector3Length(unit_x));
	unit_y=MLVector3Scale(unit_y,1/MLVector3Length(unit_y));
	MLVector3 rotation=MLVector3GetXYUnitRotation(unit_x,unit_y);
	new_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(new_trafo );
	(new_trafo->scale).x=scale_x;
	(new_trafo->scale).y=scale_x;
	(new_trafo->scale).z=scale_x;
	new_trafo->rotation=rotation;
	new_trafo->translation=a;
	GLUIController_zoom_to_ui_trafo( self, new_trafo,the_steps,the_easing);
	GLUITrafo_release(new_trafo );
}
void GLUIController_zoom_to_ui_trafo (struct GLUIController* self, struct GLUITrafo * the_trafo , int the_steps , char the_easing ) 
{
	struct GLUITrafoAnimation*animation;
	if(self->view_animator->animation!=NULL)self->view_animator->_class->reset( (void*) self->view_animator->_components[0] );
	animation=GLUITrafoAnimation_alloc( );
	GLUITrafoAnimation_init_start_end_steps_easing(animation, self->view_trafo,the_trafo,the_steps,the_easing);
	GLUITrafoAnimator_add_animation(self->view_animator, animation);
	GLUITrafoAnimation_release(animation );
}
void GLUIController_set_view_ui_trafo (struct GLUIController* self, struct GLUITrafo * the_trafo ) 
{
	GLUIController_set_view_trafo( self, the_trafo->_class->matrix( (void*) the_trafo->_components[0] ));
	self->view_trafo->scale=the_trafo->scale;
	self->view_trafo->rotation=the_trafo->rotation;
	self->view_trafo->translation=the_trafo->translation;
}
void GLUIController_set_view_trafo (struct GLUIController* self, MLMatrix4 the_matrix ) 
{
	self->projection_matrix=MLMatrix4Invert(the_matrix,NULL);
	self->projection_matrix=MLMatrix4Multiply(self->view_matrix,self->projection_matrix);
	self->projection_matrix=MLMatrix4Multiply(self->perspective_matrix,self->projection_matrix);
	self->needs_redraw=2;
}
void GLUIController_add_element (struct GLUIController* self, struct GLUIElement * the_element ) 
{
	GLUIElement_add_element(self->base, the_element);
}
void GLUIController_remove_element (struct GLUIController* self, struct GLUIElement * the_element ) 
{
	GLUIElement_remove_element(self->base, the_element);
}
void GLUIController_set_focus (struct GLUIController* self, struct GLUIElement * the_element ) 
{
	if(the_element->accepts_focus==1)
	{
		if(self->focused!=NULL)self->focused->_class->focus_off( (void*) self->focused->_components[0] );
		self->focused=the_element;
		self->focused->_class->focus_on( (void*) self->focused->_components[0] );
	}
}
struct CLDataList * GLUIController_intersected_elements_at_x_y (struct GLUIController* self, float the_x , float the_y , MLVector3 * the_line_a , MLVector3 * the_line_b ) 
{
	MLVector4 vector_a,vector_b,result_a,result_b;
	MLVector3 line_a,line_b;
	struct CLDataList*elements;
	elements=CLDataList_alloc( );
	CLDataList_init(elements );
	vector_a=MLVector4Create(the_x,the_y,-1.0,0);
	vector_b=MLVector4Create(the_x,the_y,1.0,0);
	result_a=MLMatrix4UnProjectVector4FromScreen(self->projection_matrix,vector_a,self->width,self->height);
	result_b=MLMatrix4UnProjectVector4FromScreen(self->projection_matrix,vector_b,self->width,self->height);
	line_a=MLVector3Create(result_a.x,result_a.y,result_a.z);
	line_b=MLVector3Create(result_b.x,result_b.y,result_b.z);
	GLUIElement_intersect_line_a_line_b_elements(self->base, line_a,line_b,elements);
	*the_line_a=line_a;
	*the_line_b=line_b;
	return elements;
}
void GLUIController_mouse_down_at_x_y (struct GLUIController* self, float the_x , float the_y ) 
{
	struct CLDataList*elements;
	self->mouse_is_down=1;
	MLVector3 lineA;
	MLVector3 lineB;
	elements=GLUIController_intersected_elements_at_x_y( self, the_x,the_y,&lineA,&lineB);
	if(elements->length>0)
	{
		self->touched=elements->_class->last_data( (void*) elements->_components[0] );
		self->touched->_class->touch_began( (void*) self->touched->_components[0], lineA,lineB);
		GLUIController_set_focus( self, self->touched);
	}
	CLDataList_release(elements );
}
void GLUIController_mouse_up_at_x_y (struct GLUIController* self, float the_x , float the_y ) 
{
	struct CLDataList*elements;
	self->mouse_is_down=0;
	MLVector3 lineA;
	MLVector3 lineB;
	elements=GLUIController_intersected_elements_at_x_y( self, the_x,the_y,&lineA,&lineB);
	if(elements->length>0)
	{
		struct GLUIElement*element=elements->_class->last_data( (void*) elements->_components[0] );
		element->_class->touch_ended( (void*) element->_components[0], lineA,lineB);
		if(element==self->touched)self->touched=NULL;
	}
	if(self->touched!=NULL)self->touched->_class->touch_ended( (void*) self->touched->_components[0], lineA,lineB);
	self->touched=NULL;
	CLDataList_release(elements );
}
void GLUIController_mouse_move_at_x_y (struct GLUIController* self, float the_x , float the_y ) 
{
	struct CLDataList*elements;
	if(self->mouse_is_down==1)
	{
		MLVector3 lineA;
		MLVector3 lineB;
		elements=GLUIController_intersected_elements_at_x_y( self, the_x,the_y,&lineA,&lineB);
		if(elements->length>0)
		{
			struct GLUIElement*element=elements->_class->last_data( (void*) elements->_components[0] );
			element->_class->touch_moved( (void*) element->_components[0], lineA,lineB);
		}
		CLDataList_release(elements );
	}
}
void GLUIController_key_down_characters (struct GLUIController* self, char * the_characters ) 
{
	if(self->focused!=NULL)self->focused->_class->key_down_characters( (void*) self->focused->_components[0], the_characters);
}
void GLUIController_scroll_x_y (struct GLUIController* self, float the_x , float the_y ) 
{
	GLUIElement_scroll_x_y(self->base, the_x,the_y);
}
void GLUIController_init (struct GLUIController* self ) 
{
	self->retain_count=1;
}
void GLUIController_retain (struct GLUIController* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIController_release (struct GLUIController* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIController_event (struct GLUIController* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIController_describe (struct GLUIController* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUITrafo_CreateClass( )
{
	GLUITrafo_ClassInstance=malloc(sizeof(struct GLUITrafo_Class));
	GLUITrafo_ClassInstance->className="GLUITrafo";
	GLUITrafo_ClassInstance->classId=&GLUITrafo_ClassInstance;
	GLUITrafo_ClassInstance->init=GLUITrafo_init;
	GLUITrafo_ClassInstance->matrix=GLUITrafo_matrix;
	GLUITrafo_ClassInstance->describe=GLUITrafo_describe;
	GLUITrafo_ClassInstance->className_CLObject="CLObject";
	GLUITrafo_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUITrafo_ClassInstance->init_CLObject=GLUITrafo_init;
	GLUITrafo_ClassInstance->destruct=GLUITrafo_destruct;
	GLUITrafo_ClassInstance->retain=GLUITrafo_retain;
	GLUITrafo_ClassInstance->release=GLUITrafo_release;
	GLUITrafo_ClassInstance->event=GLUITrafo_event;
	GLUITrafo_ClassInstance->describe_CLObject=GLUITrafo_describe;
	
}
struct GLUITrafo* GLUITrafo_alloc( )
{
	struct GLUITrafo* result;
	if(GLUITrafo_ClassInstance==NULL)GLUITrafo_CreateClass( );
	result=malloc(sizeof(struct GLUITrafo));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUITrafo_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUITrafo_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUITrafo_init (struct GLUITrafo* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->scale=MLVector3Create(1.0,1.0,1.0);
	self->rotation=MLVector3Create(0.0,0.0,0.0);
	self->translation=MLVector3Create(0.0,0.0,0.0);
}
MLMatrix4 GLUITrafo_matrix (struct GLUITrafo* self ) 
{
	MLMatrix4 result=MLMatrix4CreateIdentity();
	result=MLMatrix4Translate(result,self->translation.x,self->translation.y,self->translation.z);
	result=MLMatrix4Scale(result,self->scale.x,self->scale.y,self->scale.z);
	result=MLMatrix4Rotate(result,self->rotation.z,0.0,0.0,1.0);
	result=MLMatrix4Rotate(result,self->rotation.y,0.0,1.0,0.0);
	result=MLMatrix4Rotate(result,self->rotation.x,1.0,0.0,0.0);
	return result;
}
void GLUITrafo_describe (struct GLUITrafo* self ) 
{
	printf("\nscale %f %f %f",self->scale.x,self->scale.y,self->scale.z);
	printf("\nrotation %f %f %f",self->rotation.x,self->rotation.y,self->rotation.z);
	printf("\ntranslation %f %f %f",self->translation.x,self->translation.y,self->translation.z);
}
void GLUITrafo_destruct (struct GLUITrafo* self ) 
{

}
void GLUITrafo_retain (struct GLUITrafo* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUITrafo_release (struct GLUITrafo* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUITrafo_event (struct GLUITrafo* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRCodingRoom_CreateClass( )
{
	PRCodingRoom_ClassInstance=malloc(sizeof(struct PRCodingRoom_Class));
	PRCodingRoom_ClassInstance->className="PRCodingRoom";
	PRCodingRoom_ClassInstance->classId=&PRCodingRoom_ClassInstance;
	PRCodingRoom_ClassInstance->init_name_frame_controller=PRCodingRoom_init_name_frame_controller;
	PRCodingRoom_ClassInstance->build=PRCodingRoom_build;
	PRCodingRoom_ClassInstance->className_PRRoom="PRRoom";
	PRCodingRoom_ClassInstance->classId_PRRoom=&PRRoom_ClassInstance;
	PRCodingRoom_ClassInstance->init_name_frame_controller_PRRoom=PRCodingRoom_init_name_frame_controller;
	PRCodingRoom_ClassInstance->destruct=PRCodingRoom_destruct;
	PRCodingRoom_ClassInstance->create_info_view=PRCodingRoom_create_info_view;
	PRCodingRoom_ClassInstance->create_empty_view=PRCodingRoom_create_empty_view;
	PRCodingRoom_ClassInstance->create_texture_area=PRCodingRoom_create_texture_area;
	PRCodingRoom_ClassInstance->create_image_area=PRCodingRoom_create_image_area;
	PRCodingRoom_ClassInstance->update=PRCodingRoom_update;
	PRCodingRoom_ClassInstance->step_right=PRCodingRoom_step_right;
	PRCodingRoom_ClassInstance->step_left=PRCodingRoom_step_left;
	PRCodingRoom_ClassInstance->build_PRRoom=PRCodingRoom_build;
	PRCodingRoom_ClassInstance->collapse=PRCodingRoom_collapse;
	PRCodingRoom_ClassInstance->className_GLUIElement="GLUIElement";
	PRCodingRoom_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	PRCodingRoom_ClassInstance->init_name_frame=PRCodingRoom_init_name_frame;
	PRCodingRoom_ClassInstance->destruct_GLUIElement=PRCodingRoom_destruct;
	PRCodingRoom_ClassInstance->set_level=PRCodingRoom_set_level;
	PRCodingRoom_ClassInstance->set_group=PRCodingRoom_set_group;
	PRCodingRoom_ClassInstance->set_texture=PRCodingRoom_set_texture;
	PRCodingRoom_ClassInstance->set_texture_coords=PRCodingRoom_set_texture_coords;
	PRCodingRoom_ClassInstance->set_color=PRCodingRoom_set_color;
	PRCodingRoom_ClassInstance->set_origo=PRCodingRoom_set_origo;
	PRCodingRoom_ClassInstance->set_extent=PRCodingRoom_set_extent;
	PRCodingRoom_ClassInstance->set_trafo=PRCodingRoom_set_trafo;
	PRCodingRoom_ClassInstance->update_GLUIElement=PRCodingRoom_update;
	PRCodingRoom_ClassInstance->update_frame=PRCodingRoom_update_frame;
	PRCodingRoom_ClassInstance->update_trafo=PRCodingRoom_update_trafo;
	PRCodingRoom_ClassInstance->get_absolute_frame=PRCodingRoom_get_absolute_frame;
	PRCodingRoom_ClassInstance->finalize_frame=PRCodingRoom_finalize_frame;
	PRCodingRoom_ClassInstance->add_element=PRCodingRoom_add_element;
	PRCodingRoom_ClassInstance->remove_element=PRCodingRoom_remove_element;
	PRCodingRoom_ClassInstance->attach=PRCodingRoom_attach;
	PRCodingRoom_ClassInstance->detach=PRCodingRoom_detach;
	PRCodingRoom_ClassInstance->get_relative_touch_line_a_line_b=PRCodingRoom_get_relative_touch_line_a_line_b;
	PRCodingRoom_ClassInstance->intersect_line_a_line_b_elements=PRCodingRoom_intersect_line_a_line_b_elements;
	PRCodingRoom_ClassInstance->touch_began=PRCodingRoom_touch_began;
	PRCodingRoom_ClassInstance->touch_moved=PRCodingRoom_touch_moved;
	PRCodingRoom_ClassInstance->touch_ended=PRCodingRoom_touch_ended;
	PRCodingRoom_ClassInstance->key_down_characters=PRCodingRoom_key_down_characters;
	PRCodingRoom_ClassInstance->key_up_characters=PRCodingRoom_key_up_characters;
	PRCodingRoom_ClassInstance->scroll_x_y=PRCodingRoom_scroll_x_y;
	PRCodingRoom_ClassInstance->focus_on=PRCodingRoom_focus_on;
	PRCodingRoom_ClassInstance->focus_off=PRCodingRoom_focus_off;
	PRCodingRoom_ClassInstance->className_CLObject="CLObject";
	PRCodingRoom_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRCodingRoom_ClassInstance->init=PRCodingRoom_init;
	PRCodingRoom_ClassInstance->destruct_CLObject=PRCodingRoom_destruct;
	PRCodingRoom_ClassInstance->retain=PRCodingRoom_retain;
	PRCodingRoom_ClassInstance->release=PRCodingRoom_release;
	PRCodingRoom_ClassInstance->event=PRCodingRoom_event;
	PRCodingRoom_ClassInstance->describe=PRCodingRoom_describe;
	
}
struct PRCodingRoom* PRCodingRoom_alloc( )
{
	struct PRCodingRoom* result;
	if(PRCodingRoom_ClassInstance==NULL)PRCodingRoom_CreateClass( );
	result=malloc(sizeof(struct PRCodingRoom));
	result->_components=malloc(sizeof(void*)*5);
	result->_class=(void*)&(PRCodingRoom_ClassInstance->className);
	result->_components_PRRoom=result->_components;
	result->_class_PRRoom=(void*)&(PRCodingRoom_ClassInstance->className_PRRoom);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(PRCodingRoom_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRCodingRoom_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_PRRoom);
	result->_components[2]=&(result->_class_GLUIElement);
	result->_components[3]=&(result->_class_CLObject);
	result->_components[4]=NULL;
	return result;
}
void PRCodingRoom_init_name_frame_controller (struct PRCodingRoom* self, char * the_name , MLVector4 the_frame , struct PRController * the_controller ) 
{
	PRRoom_init_name_frame_controller(( cast_object( &PRRoom_ClassInstance , self)),the_name,the_frame,the_controller);
	self->my_info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(self->my_info_view, "info_view",MLVector4Create(0,0,800,-600),the_controller);
	PRInfoView_set_color(self->my_info_view, 0,0,0,0);
	PRInfoView_set_level(self->my_info_view, 60);
	PRInfoView_set_title_label(self->my_info_view, "Cyberspace of Coding");
	PRInfoView_show(self->my_info_view );
	PRCodingRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->my_info_view)));
	CLDataList_add_data(self->info_views, self->my_info_view);
}
void PRCodingRoom_build (struct PRCodingRoom* self ) 
{
	struct CLString*wall_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], "grid.png");
	char*wall_path_c=wall_path->_class->c_string( (void*) wall_path->_components[0] );
	struct GLBitmapRGBA*bitmap=GLBitmapRGBAUtils_create_bitmap_pngpath(NULL,wall_path_c);
	struct GLTextureSquare*wall_texture;
	wall_texture=GLTextureSquare_alloc( );
	GLTextureSquare_init_width_height(wall_texture, bitmap->width,bitmap->height);
	GLTextureSquare_clone_bitmap(wall_texture, bitmap);
	GLBitmapRGBA_release(bitmap );
	CLString_release(wall_path );
	free(wall_path_c);
	PRCodingRoom_create_texture_area( self, wall_texture,4000,-600,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2,0),MLVector3Create(0,0,0));
	PRCodingRoom_create_texture_area( self, wall_texture,4000,-600,MLVector3Create(1,1,1),MLVector3Create(0,-M_PI/2,0),MLVector3Create(800,0,-4000));
	PRCodingRoom_create_texture_area( self, wall_texture,4000,-800,MLVector3Create(1,1,1),MLVector3Create(-M_PI/2,-M_PI/2,0),MLVector3Create(800,-600,-4000));
	PRCodingRoom_create_texture_area( self, wall_texture,4000,-800,MLVector3Create(1,1,1),MLVector3Create(M_PI/2,-M_PI/2,0),MLVector3Create(0,0,-4000));
	float alpha=-.8;
	float radius=150.0;
	PRCodingRoom_create_info_view( self, "enterprise.png","enterprise.png","1989","First Computer","I got my first computer in 1989, it was an Enterprise 128, the unique 8 bit computer of the eighties. I started programming IS-BASIC on this machine.",MLVector3Create(.15,.15,.15),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-200.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "pc.png","pc.png","1991","First PC","It was a 80286 clone with a monochrome VGA monitor. I picked up QuickBasic here.",MLVector3Create(.15,.15,.15),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-400.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "javacflash.png","javacflash.png","1991-2001","Programming languages","1994 - Pascal in High School \x000d 1998 - C and Java in University \x000d 2001 - Flash actionscript and Javascript",MLVector3Create(.15,.15,.15),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-600.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "experiments.png","experiments.png","2001-2007","Graphics, Physics based experiments and prototypes in flash","- Inverse Kinematics \x000d - Fluid surface stress simulation \x000d - Particle system animations \x000d - Motion detection from camera input \x000d - Multi-agent ant swarm simulation \x000d - Mass point dynamics simulation",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-800.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "tetrapod3.png","tetrapod3.png","2004","Tetrapod UI renderer","UI renderer written in flash with non-overlapping, pushable windows and window layers",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-1000.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "games.png","games.png","2001-2007","Flash Games","- Shooting galleries \x000d - Ant swarm strategy game \x000d - Tetris, Nibbles \x000d - Real physics and inverse kinematics based side scroller",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-1200.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "articles.png","articles.png","2001-2007","Articles, Tutorials","Advanced Inverse Kinematics ( 2004, gotoandplay.it ) Projection Plane Based Real 3D ( 2004, gotoandplay.it ) Getting started with ActionScript ( 2007, actionscript.org ) Camera-motion controlled ball ( 2007, actionscript.org ) Getting started with red5 media server ( 2007, actionscript.org ) Streaming and database connection with red5 ( 2007, actionscript.org ) Low level AS3 ( 2007, actionscript,org ) Creating a mandelbrot-set ( 2007, actionscript.org ) Object-Orientation : Creating an ant swarm ( 2007, actionscript.org ) Vector Intersection Calculations ( 2007 , actionscript.org )",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-1400.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "milenia.png","milenia.png","2007","Milenia Grafter Flash Media Server","I was among the first ones who reverse engineered Macromedia's RTMP protocol and decided to write a Flash Media Server replacement under 64 Kbytes. The final size of the java binary was 64321 bytes.",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-1600.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "termite.png","termite.png","2009","Termite iOS Game","My first iOS game, it is the ultimate real-time strategy experience based on my previous multi-agent and ant swarm simulations. It was a huge success among minimal game fans.",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-1800.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "kwiknote.png","kwiknote.png","2011","Kwiknote Text Editor for iOS","Swipe-controlled text editor with full-size keyboard and an own text renderer",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-2000.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "remotion.png","remotion.png","2012","Remotion Control for iOS/Mac","Remotion, the first game remote controller on a mobile phone with 3 degrees of freedom. I spoke about it at SzegedTech, even the regional newspaper wrote an article about it.",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-2200.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "gameprog.png","gameprog.png","2013","GameProg for iOS/Mac","Tutorials, source code and everything about OpenGL/Inverse Kinematics/Mass Point Dynamics programming.",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-2400.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "classc.png","classc.png","2013","Class-C programming language and compiler.","No more C++, no more Objective-C, just beautiful simple ANSI C with classes and instances without header maintainance. My C coding speed was boosted with a rocket engine.",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-2600.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "cortex.png","cortex.png","2013","Cerebral Cortex for iOS/Mac/BB10","A minimalistic ambient-reflex game with a twist. Selected for the best new games section by apple.",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-2800.0));
	alpha-=.8;
	PRCodingRoom_create_info_view( self, "milan.png","milan.png","2014","Thanks for watching!!!","",MLVector3Create(.2,.2,.2),MLVector3Create(-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0,-.25+(float)(rand()%5)/10.0),MLVector3Create(300.0+sinf(alpha)*radius,-200.0+cosf(alpha)*radius,-3000.0));
}
void PRCodingRoom_destruct (struct PRCodingRoom* self ) 
{
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRCodingRoom_create_info_view (struct PRCodingRoom* self, char * the_image , char * the_large_image , char * the_title_label , char * the_subtitle_label , char * the_description_label , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*small_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_image);
	struct CLString*large_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_large_image);
	char*small_path_c=small_path->_class->c_string( (void*) small_path->_components[0] );
	char*large_path_c=large_path->_class->c_string( (void*) large_path->_components[0] );
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	info_view->small_path=small_path_c;
	info_view->large_path=large_path_c;
	PRInfoView_set_color(info_view, 0,0,0,0);
	PRInfoView_set_level(info_view, 30-(int)self->info_views->length);
	PRInfoView_set_title_label(info_view, the_title_label);
	PRInfoView_set_subtitle_label(info_view, the_subtitle_label);
	PRInfoView_set_description_label(info_view, the_description_label);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	PRInfoView_set_image(info_view, info_view->small_path);
	PRCodingRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLString_release(small_path );
	CLString_release(large_path );
	GLUITrafo_release(local_trafo );
}
void PRCodingRoom_create_empty_view (struct PRCodingRoom* self, MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	PRInfoView_set_color(info_view, 0,0,0,.5);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	info_view->hidden=1;
	PRCodingRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	GLUITrafo_release(local_trafo );
}
void PRCodingRoom_create_texture_area (struct PRCodingRoom* self, struct GLTextureSquare * the_texture , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUIElement*area;
	struct GLUITrafo*area_trafo;
	area_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(area_trafo );
	area_trafo->scale=the_scale;
	area_trafo->rotation=the_rotation;
	area_trafo->translation=the_translation;
	area=GLUIElement_alloc( );
	GLUIElement_init_name_frame(area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height));
	GLUIElement_set_trafo(area, GLUITrafo_matrix(area_trafo ),0);
	GLUIElement_set_texture(area, the_texture->id);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,0,0);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,the_texture->hRatio,1);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,the_texture->hRatio,2);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,0,3);
	PRCodingRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , area)));
	GLUITrafo_release(area_trafo );
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , area)));
}
void PRCodingRoom_create_image_area (struct PRCodingRoom* self, char * the_path , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*image_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_path);
	char*image_path_c=image_path->_class->c_string( (void*) image_path->_components[0] );
	struct GLUITrafo*image_trafo;
	struct GLUIImageArea*image_area;
	image_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(image_trafo );
	image_trafo->scale=the_scale;
	image_trafo->rotation=the_rotation;
	image_trafo->translation=the_translation;
	image_area=GLUIImageArea_alloc( );
	GLUIImageArea_init_name_frame_path(image_area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height),image_path_c);
	GLUIImageArea_set_trafo(image_area, GLUITrafo_matrix(image_trafo ),0);
	PRCodingRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , image_area)));
	GLUITrafo_release(image_trafo );
	CLString_release(image_path );
	free(image_path_c);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , image_area)));
}
void PRCodingRoom_update (struct PRCodingRoom* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	if(self->counter>0)
	{
		self->counter-=1;
		if(self->counter==1)
		{
			self->last_room->_class->collapse( (void*) self->last_room->_components[0] );
			PRCodingRoom_build( self );
		}
	}
}
void PRCodingRoom_step_right (struct PRCodingRoom* self ) 
{
	if(self->counter>0)return;
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==0&&one_view->hidden==0)one_view->_class->show_with_animation( (void*) one_view->_components[0] );
	else
	{
		self->view_index+=1;
		if(self->view_index==self->info_views->length)
		{
			self->view_index=0;
			struct PRInfoView*next_info_view=self->next_room->info_views->_class->data_at_index( (void*) self->next_room->info_views->_components[0], 0);
			self->next_room->counter=151;
			self->controller->actual_room=self->next_room;
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , next_info_view)),150,kGLUIAnimationEaseIn);
		}
		else
		{
			one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRCodingRoom_step_left (struct PRCodingRoom* self ) 
{
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
	else
	{
		self->view_index-=1;
		if(self->view_index<0)self->view_index=0;
		else
		{
			struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRCodingRoom_collapse (struct PRCodingRoom* self ) 
{
	struct CLLink*link24;
	void* kid_data;
	link24=self->removables->head;while( link24!=NULL){kid_data=link24->data; 
	
		struct GLUIElement*kid=kid_data;
		PRCodingRoom_remove_element( self, kid);
		kid->_class->release( (void*) kid->_components[0] );
	link24=link24->next;}
	self->view_index=0;
	self->info_views->_class->remove_all_data( (void*) self->info_views->_components[0] );
	self->removables->_class->remove_all_data( (void*) self->removables->_components[0] );
	self->info_views->_class->add_data( (void*) self->info_views->_components[0], self->my_info_view);
}
void PRCodingRoom_init_name_frame (struct PRCodingRoom* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	PRCodingRoom_update_frame( self );
}
void PRCodingRoom_set_level (struct PRCodingRoom* self, int the_level ) 
{
	self->level=the_level;
}
void PRCodingRoom_set_group (struct PRCodingRoom* self, int the_group ) 
{
	self->group=the_group;
}
void PRCodingRoom_set_texture (struct PRCodingRoom* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void PRCodingRoom_set_texture_coords (struct PRCodingRoom* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void PRCodingRoom_set_color (struct PRCodingRoom* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void PRCodingRoom_set_origo (struct PRCodingRoom* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	PRCodingRoom_update_frame( self );
}
void PRCodingRoom_set_extent (struct PRCodingRoom* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	PRCodingRoom_update_frame( self );
}
void PRCodingRoom_set_trafo (struct PRCodingRoom* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)PRCodingRoom_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)PRCodingRoom_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)PRCodingRoom_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)PRCodingRoom_attach( self, one_drawer);
		}
	}
	PRCodingRoom_update_trafo( self );
}
void PRCodingRoom_update_frame (struct PRCodingRoom* self ) 
{
	struct CLLink*link25;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link25=self->kids->head;while( link25!=NULL){data=link25->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link25=link25->next;}
	}
}
void PRCodingRoom_update_trafo (struct PRCodingRoom* self ) 
{
	struct CLLink*link26;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link26=self->kids->head;while( link26!=NULL){data=link26->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link26=link26->next;}
	}
}
void PRCodingRoom_get_absolute_frame (struct PRCodingRoom* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void PRCodingRoom_finalize_frame (struct PRCodingRoom* self ) 
{
	MLVector3 a,b,c,d;
	PRCodingRoom_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void PRCodingRoom_add_element (struct PRCodingRoom* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void PRCodingRoom_remove_element (struct PRCodingRoom* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void PRCodingRoom_attach (struct PRCodingRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link27;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	PRCodingRoom_update_frame( self );
	PRCodingRoom_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link27=self->kids->head;while( link27!=NULL){data=link27->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link27=link27->next;}
}
void PRCodingRoom_detach (struct PRCodingRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link28;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link28=self->kids->head;while( link28!=NULL){data=link28->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link28=link28->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 PRCodingRoom_get_relative_touch_line_a_line_b (struct PRCodingRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	PRCodingRoom_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void PRCodingRoom_intersect_line_a_line_b_elements (struct PRCodingRoom* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link29;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=PRCodingRoom_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link29=self->kids->head;while( link29!=NULL){data=link29->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link29=link29->next;}
	}
}
void PRCodingRoom_touch_began (struct PRCodingRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRCodingRoom_touch_moved (struct PRCodingRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRCodingRoom_touch_ended (struct PRCodingRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRCodingRoom_key_down_characters (struct PRCodingRoom* self, char * the_characters ) 
{

}
void PRCodingRoom_key_up_characters (struct PRCodingRoom* self, char * the_characters ) 
{

}
void PRCodingRoom_scroll_x_y (struct PRCodingRoom* self, float the_x , float the_y ) 
{

}
void PRCodingRoom_focus_on (struct PRCodingRoom* self ) 
{

}
void PRCodingRoom_focus_off (struct PRCodingRoom* self ) 
{

}
void PRCodingRoom_init (struct PRCodingRoom* self ) 
{
	self->retain_count=1;
}
void PRCodingRoom_retain (struct PRCodingRoom* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRCodingRoom_release (struct PRCodingRoom* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRCodingRoom_event (struct PRCodingRoom* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRCodingRoom_describe (struct PRCodingRoom* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRDesignRoom_CreateClass( )
{
	PRDesignRoom_ClassInstance=malloc(sizeof(struct PRDesignRoom_Class));
	PRDesignRoom_ClassInstance->className="PRDesignRoom";
	PRDesignRoom_ClassInstance->classId=&PRDesignRoom_ClassInstance;
	PRDesignRoom_ClassInstance->init_name_frame_controller=PRDesignRoom_init_name_frame_controller;
	PRDesignRoom_ClassInstance->build=PRDesignRoom_build;
	PRDesignRoom_ClassInstance->className_PRRoom="PRRoom";
	PRDesignRoom_ClassInstance->classId_PRRoom=&PRRoom_ClassInstance;
	PRDesignRoom_ClassInstance->init_name_frame_controller_PRRoom=PRDesignRoom_init_name_frame_controller;
	PRDesignRoom_ClassInstance->destruct=PRDesignRoom_destruct;
	PRDesignRoom_ClassInstance->create_info_view=PRDesignRoom_create_info_view;
	PRDesignRoom_ClassInstance->create_empty_view=PRDesignRoom_create_empty_view;
	PRDesignRoom_ClassInstance->create_texture_area=PRDesignRoom_create_texture_area;
	PRDesignRoom_ClassInstance->create_image_area=PRDesignRoom_create_image_area;
	PRDesignRoom_ClassInstance->update=PRDesignRoom_update;
	PRDesignRoom_ClassInstance->step_right=PRDesignRoom_step_right;
	PRDesignRoom_ClassInstance->step_left=PRDesignRoom_step_left;
	PRDesignRoom_ClassInstance->build_PRRoom=PRDesignRoom_build;
	PRDesignRoom_ClassInstance->collapse=PRDesignRoom_collapse;
	PRDesignRoom_ClassInstance->className_GLUIElement="GLUIElement";
	PRDesignRoom_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	PRDesignRoom_ClassInstance->init_name_frame=PRDesignRoom_init_name_frame;
	PRDesignRoom_ClassInstance->destruct_GLUIElement=PRDesignRoom_destruct;
	PRDesignRoom_ClassInstance->set_level=PRDesignRoom_set_level;
	PRDesignRoom_ClassInstance->set_group=PRDesignRoom_set_group;
	PRDesignRoom_ClassInstance->set_texture=PRDesignRoom_set_texture;
	PRDesignRoom_ClassInstance->set_texture_coords=PRDesignRoom_set_texture_coords;
	PRDesignRoom_ClassInstance->set_color=PRDesignRoom_set_color;
	PRDesignRoom_ClassInstance->set_origo=PRDesignRoom_set_origo;
	PRDesignRoom_ClassInstance->set_extent=PRDesignRoom_set_extent;
	PRDesignRoom_ClassInstance->set_trafo=PRDesignRoom_set_trafo;
	PRDesignRoom_ClassInstance->update_GLUIElement=PRDesignRoom_update;
	PRDesignRoom_ClassInstance->update_frame=PRDesignRoom_update_frame;
	PRDesignRoom_ClassInstance->update_trafo=PRDesignRoom_update_trafo;
	PRDesignRoom_ClassInstance->get_absolute_frame=PRDesignRoom_get_absolute_frame;
	PRDesignRoom_ClassInstance->finalize_frame=PRDesignRoom_finalize_frame;
	PRDesignRoom_ClassInstance->add_element=PRDesignRoom_add_element;
	PRDesignRoom_ClassInstance->remove_element=PRDesignRoom_remove_element;
	PRDesignRoom_ClassInstance->attach=PRDesignRoom_attach;
	PRDesignRoom_ClassInstance->detach=PRDesignRoom_detach;
	PRDesignRoom_ClassInstance->get_relative_touch_line_a_line_b=PRDesignRoom_get_relative_touch_line_a_line_b;
	PRDesignRoom_ClassInstance->intersect_line_a_line_b_elements=PRDesignRoom_intersect_line_a_line_b_elements;
	PRDesignRoom_ClassInstance->touch_began=PRDesignRoom_touch_began;
	PRDesignRoom_ClassInstance->touch_moved=PRDesignRoom_touch_moved;
	PRDesignRoom_ClassInstance->touch_ended=PRDesignRoom_touch_ended;
	PRDesignRoom_ClassInstance->key_down_characters=PRDesignRoom_key_down_characters;
	PRDesignRoom_ClassInstance->key_up_characters=PRDesignRoom_key_up_characters;
	PRDesignRoom_ClassInstance->scroll_x_y=PRDesignRoom_scroll_x_y;
	PRDesignRoom_ClassInstance->focus_on=PRDesignRoom_focus_on;
	PRDesignRoom_ClassInstance->focus_off=PRDesignRoom_focus_off;
	PRDesignRoom_ClassInstance->className_CLObject="CLObject";
	PRDesignRoom_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRDesignRoom_ClassInstance->init=PRDesignRoom_init;
	PRDesignRoom_ClassInstance->destruct_CLObject=PRDesignRoom_destruct;
	PRDesignRoom_ClassInstance->retain=PRDesignRoom_retain;
	PRDesignRoom_ClassInstance->release=PRDesignRoom_release;
	PRDesignRoom_ClassInstance->event=PRDesignRoom_event;
	PRDesignRoom_ClassInstance->describe=PRDesignRoom_describe;
	
}
struct PRDesignRoom* PRDesignRoom_alloc( )
{
	struct PRDesignRoom* result;
	if(PRDesignRoom_ClassInstance==NULL)PRDesignRoom_CreateClass( );
	result=malloc(sizeof(struct PRDesignRoom));
	result->_components=malloc(sizeof(void*)*5);
	result->_class=(void*)&(PRDesignRoom_ClassInstance->className);
	result->_components_PRRoom=result->_components;
	result->_class_PRRoom=(void*)&(PRDesignRoom_ClassInstance->className_PRRoom);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(PRDesignRoom_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRDesignRoom_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_PRRoom);
	result->_components[2]=&(result->_class_GLUIElement);
	result->_components[3]=&(result->_class_CLObject);
	result->_components[4]=NULL;
	return result;
}
void PRDesignRoom_init_name_frame_controller (struct PRDesignRoom* self, char * the_name , MLVector4 the_frame , struct PRController * the_controller ) 
{
	PRRoom_init_name_frame_controller(( cast_object( &PRRoom_ClassInstance , self)),the_name,the_frame,the_controller);
	self->my_info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(self->my_info_view, "info_view",MLVector4Create(0,0,800,-600),the_controller);
	PRInfoView_set_color(self->my_info_view, 0,0,0,0);
	PRInfoView_set_level(self->my_info_view, 60);
	PRInfoView_set_title_label(self->my_info_view, "Room of Graphics");
	PRInfoView_show(self->my_info_view );
	PRDesignRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->my_info_view)));
	CLDataList_add_data(self->info_views, self->my_info_view);
}
void PRDesignRoom_build (struct PRDesignRoom* self ) 
{
	PRDesignRoom_create_image_area( self, "wall_design.png",600,-600,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2.0,0),MLVector3Create(0,0,-200));
	PRDesignRoom_create_image_area( self, "wall_design.png",800,-600,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(0,0,-800));
	PRDesignRoom_create_image_area( self, "floor.png",800,-600,MLVector3Create(1,1,1),MLVector3Create(-M_PI/2.0,0,0),MLVector3Create(0,-600,-800));
	PRDesignRoom_create_image_area( self, "table.png",300,-150,MLVector3Create(1,1,1),MLVector3Create(-M_PI/3,M_PI/2,0),MLVector3Create(0,-400,-300));
	PRDesignRoom_create_image_area( self, "table.png",300,-120,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2,0),MLVector3Create(130,-475,-300));
	PRDesignRoom_create_image_area( self, "table.png",400,-125,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(300,-475,-580));
	PRDesignRoom_create_image_area( self, "table.png",400,-220,MLVector3Create(1,1,1),MLVector3Create(-M_PI/2,0,0),MLVector3Create(300,-475,-800));
	PRDesignRoom_create_image_area( self, "monitor.png",300,-250,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(350,-230,-700));
	PRDesignRoom_create_empty_view( self, MLVector3Create(1,1,1),MLVector3Create(0,M_PI/3,0.0),MLVector3Create(0.0,0.0,-200.0));
	PRDesignRoom_create_info_view( self, "malom.png","malom.png","1990-1994","Elementary School","I was a gifted drawer as a child, so I took extra drawing classes in elementary school.",MLVector3Create(.15,.15,.15),MLVector3Create(-M_PI/3,M_PI/2,0.0),MLVector3Create(0.0,-400.0,-300.0));
	PRDesignRoom_create_info_view( self, "drawings.png","drawings.png","1994-2001","More Drawings","I love to draw, but since 2001 programming is more exciting to me, so I rarely draw nowadays.",MLVector3Create(.18,.18,.18),MLVector3Create(-M_PI/3,M_PI/2,0.0),MLVector3Create(0.0,-400.0,-440.0));
	PRDesignRoom_create_info_view( self, "3d.png","3d.png","1994-1998","3D modelling","After getting a faster PC ( 486DX ), and the release of 3D Studio R3 I submerged in 3D modelling and graphics.",MLVector3Create(.2,.2,.2),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-180.0,-250.0));
	PRDesignRoom_create_info_view( self, "dtp.png","dtp.png","2001-2003","Desktop Publishing","In 2001 I started working as a dtp/flash/web designer, these are some of my advertising brochures.",MLVector3Create(.3,.3,.3),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-30.0,-400.0));
	PRDesignRoom_create_info_view( self, "casino.png","casino.png","2001-2003","Gambling machine and casino decorations","I worked for a gambling/casino equipment factory back then, I did machine designs and smaller casino decorations.",MLVector3Create(.3,.3,.3),MLVector3Create(0.0,M_PI/2.0,0.0),MLVector3Create(0.0,-220.0,-550.0));
	PRDesignRoom_create_empty_view( self, MLVector3Create(.374,.374,.374),MLVector3Create(0,0,0),MLVector3Create(350,-230,-700));
	PRDesignRoom_create_info_view( self, "web.png","web.png","2001-2003","Web Designs","I had to do a lot of kind of designs, but minimalism is my eternal love.",MLVector3Create(.15,.15,.15),MLVector3Create(0.0,0.0,0.0),MLVector3Create(360.0,-250.0,-700.0));
	PRDesignRoom_create_info_view( self, "gameui.png","gameui.png","2005-","Game and UI Designs","Minimalism, minimalism, minimalism.",MLVector3Create(.2,.2,.2),MLVector3Create(0.0,0.0,0.0),MLVector3Create(480.0,-280.0,-700.0));
}
void PRDesignRoom_destruct (struct PRDesignRoom* self ) 
{
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRDesignRoom_create_info_view (struct PRDesignRoom* self, char * the_image , char * the_large_image , char * the_title_label , char * the_subtitle_label , char * the_description_label , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*small_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_image);
	struct CLString*large_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_large_image);
	char*small_path_c=small_path->_class->c_string( (void*) small_path->_components[0] );
	char*large_path_c=large_path->_class->c_string( (void*) large_path->_components[0] );
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	info_view->small_path=small_path_c;
	info_view->large_path=large_path_c;
	PRInfoView_set_color(info_view, 0,0,0,0);
	PRInfoView_set_level(info_view, 30-(int)self->info_views->length);
	PRInfoView_set_title_label(info_view, the_title_label);
	PRInfoView_set_subtitle_label(info_view, the_subtitle_label);
	PRInfoView_set_description_label(info_view, the_description_label);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	PRInfoView_set_image(info_view, info_view->small_path);
	PRDesignRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLString_release(small_path );
	CLString_release(large_path );
	GLUITrafo_release(local_trafo );
}
void PRDesignRoom_create_empty_view (struct PRDesignRoom* self, MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	PRInfoView_set_color(info_view, 0,0,0,.5);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	info_view->hidden=1;
	PRDesignRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	GLUITrafo_release(local_trafo );
}
void PRDesignRoom_create_texture_area (struct PRDesignRoom* self, struct GLTextureSquare * the_texture , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUIElement*area;
	struct GLUITrafo*area_trafo;
	area_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(area_trafo );
	area_trafo->scale=the_scale;
	area_trafo->rotation=the_rotation;
	area_trafo->translation=the_translation;
	area=GLUIElement_alloc( );
	GLUIElement_init_name_frame(area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height));
	GLUIElement_set_trafo(area, GLUITrafo_matrix(area_trafo ),0);
	GLUIElement_set_texture(area, the_texture->id);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,0,0);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,the_texture->hRatio,1);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,the_texture->hRatio,2);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,0,3);
	PRDesignRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , area)));
	GLUITrafo_release(area_trafo );
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , area)));
}
void PRDesignRoom_create_image_area (struct PRDesignRoom* self, char * the_path , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*image_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_path);
	char*image_path_c=image_path->_class->c_string( (void*) image_path->_components[0] );
	struct GLUITrafo*image_trafo;
	struct GLUIImageArea*image_area;
	image_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(image_trafo );
	image_trafo->scale=the_scale;
	image_trafo->rotation=the_rotation;
	image_trafo->translation=the_translation;
	image_area=GLUIImageArea_alloc( );
	GLUIImageArea_init_name_frame_path(image_area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height),image_path_c);
	GLUIImageArea_set_trafo(image_area, GLUITrafo_matrix(image_trafo ),0);
	PRDesignRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , image_area)));
	GLUITrafo_release(image_trafo );
	CLString_release(image_path );
	free(image_path_c);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , image_area)));
}
void PRDesignRoom_update (struct PRDesignRoom* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	if(self->counter>0)
	{
		self->counter-=1;
		if(self->counter==1)
		{
			self->last_room->_class->collapse( (void*) self->last_room->_components[0] );
			PRDesignRoom_build( self );
		}
	}
}
void PRDesignRoom_step_right (struct PRDesignRoom* self ) 
{
	if(self->counter>0)return;
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==0&&one_view->hidden==0)one_view->_class->show_with_animation( (void*) one_view->_components[0] );
	else
	{
		self->view_index+=1;
		if(self->view_index==self->info_views->length)
		{
			self->view_index=0;
			struct PRInfoView*next_info_view=self->next_room->info_views->_class->data_at_index( (void*) self->next_room->info_views->_components[0], 0);
			self->next_room->counter=151;
			self->controller->actual_room=self->next_room;
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , next_info_view)),150,kGLUIAnimationEaseIn);
		}
		else
		{
			one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRDesignRoom_step_left (struct PRDesignRoom* self ) 
{
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
	else
	{
		self->view_index-=1;
		if(self->view_index<0)self->view_index=0;
		else
		{
			struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRDesignRoom_collapse (struct PRDesignRoom* self ) 
{
	struct CLLink*link30;
	void* kid_data;
	link30=self->removables->head;while( link30!=NULL){kid_data=link30->data; 
	
		struct GLUIElement*kid=kid_data;
		PRDesignRoom_remove_element( self, kid);
		kid->_class->release( (void*) kid->_components[0] );
	link30=link30->next;}
	self->view_index=0;
	self->info_views->_class->remove_all_data( (void*) self->info_views->_components[0] );
	self->removables->_class->remove_all_data( (void*) self->removables->_components[0] );
	self->info_views->_class->add_data( (void*) self->info_views->_components[0], self->my_info_view);
}
void PRDesignRoom_init_name_frame (struct PRDesignRoom* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	PRDesignRoom_update_frame( self );
}
void PRDesignRoom_set_level (struct PRDesignRoom* self, int the_level ) 
{
	self->level=the_level;
}
void PRDesignRoom_set_group (struct PRDesignRoom* self, int the_group ) 
{
	self->group=the_group;
}
void PRDesignRoom_set_texture (struct PRDesignRoom* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void PRDesignRoom_set_texture_coords (struct PRDesignRoom* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void PRDesignRoom_set_color (struct PRDesignRoom* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void PRDesignRoom_set_origo (struct PRDesignRoom* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	PRDesignRoom_update_frame( self );
}
void PRDesignRoom_set_extent (struct PRDesignRoom* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	PRDesignRoom_update_frame( self );
}
void PRDesignRoom_set_trafo (struct PRDesignRoom* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)PRDesignRoom_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)PRDesignRoom_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)PRDesignRoom_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)PRDesignRoom_attach( self, one_drawer);
		}
	}
	PRDesignRoom_update_trafo( self );
}
void PRDesignRoom_update_frame (struct PRDesignRoom* self ) 
{
	struct CLLink*link31;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link31=self->kids->head;while( link31!=NULL){data=link31->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link31=link31->next;}
	}
}
void PRDesignRoom_update_trafo (struct PRDesignRoom* self ) 
{
	struct CLLink*link32;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link32=self->kids->head;while( link32!=NULL){data=link32->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link32=link32->next;}
	}
}
void PRDesignRoom_get_absolute_frame (struct PRDesignRoom* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void PRDesignRoom_finalize_frame (struct PRDesignRoom* self ) 
{
	MLVector3 a,b,c,d;
	PRDesignRoom_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void PRDesignRoom_add_element (struct PRDesignRoom* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void PRDesignRoom_remove_element (struct PRDesignRoom* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void PRDesignRoom_attach (struct PRDesignRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link33;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	PRDesignRoom_update_frame( self );
	PRDesignRoom_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link33=self->kids->head;while( link33!=NULL){data=link33->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link33=link33->next;}
}
void PRDesignRoom_detach (struct PRDesignRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link34;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link34=self->kids->head;while( link34!=NULL){data=link34->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link34=link34->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 PRDesignRoom_get_relative_touch_line_a_line_b (struct PRDesignRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	PRDesignRoom_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void PRDesignRoom_intersect_line_a_line_b_elements (struct PRDesignRoom* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link35;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=PRDesignRoom_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link35=self->kids->head;while( link35!=NULL){data=link35->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link35=link35->next;}
	}
}
void PRDesignRoom_touch_began (struct PRDesignRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRDesignRoom_touch_moved (struct PRDesignRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRDesignRoom_touch_ended (struct PRDesignRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRDesignRoom_key_down_characters (struct PRDesignRoom* self, char * the_characters ) 
{

}
void PRDesignRoom_key_up_characters (struct PRDesignRoom* self, char * the_characters ) 
{

}
void PRDesignRoom_scroll_x_y (struct PRDesignRoom* self, float the_x , float the_y ) 
{

}
void PRDesignRoom_focus_on (struct PRDesignRoom* self ) 
{

}
void PRDesignRoom_focus_off (struct PRDesignRoom* self ) 
{

}
void PRDesignRoom_init (struct PRDesignRoom* self ) 
{
	self->retain_count=1;
}
void PRDesignRoom_retain (struct PRDesignRoom* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRDesignRoom_release (struct PRDesignRoom* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRDesignRoom_event (struct PRDesignRoom* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRDesignRoom_describe (struct PRDesignRoom* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRMusicRoom_CreateClass( )
{
	PRMusicRoom_ClassInstance=malloc(sizeof(struct PRMusicRoom_Class));
	PRMusicRoom_ClassInstance->className="PRMusicRoom";
	PRMusicRoom_ClassInstance->classId=&PRMusicRoom_ClassInstance;
	PRMusicRoom_ClassInstance->init_name_frame_controller=PRMusicRoom_init_name_frame_controller;
	PRMusicRoom_ClassInstance->build=PRMusicRoom_build;
	PRMusicRoom_ClassInstance->className_PRRoom="PRRoom";
	PRMusicRoom_ClassInstance->classId_PRRoom=&PRRoom_ClassInstance;
	PRMusicRoom_ClassInstance->init_name_frame_controller_PRRoom=PRMusicRoom_init_name_frame_controller;
	PRMusicRoom_ClassInstance->destruct=PRMusicRoom_destruct;
	PRMusicRoom_ClassInstance->create_info_view=PRMusicRoom_create_info_view;
	PRMusicRoom_ClassInstance->create_empty_view=PRMusicRoom_create_empty_view;
	PRMusicRoom_ClassInstance->create_texture_area=PRMusicRoom_create_texture_area;
	PRMusicRoom_ClassInstance->create_image_area=PRMusicRoom_create_image_area;
	PRMusicRoom_ClassInstance->update=PRMusicRoom_update;
	PRMusicRoom_ClassInstance->step_right=PRMusicRoom_step_right;
	PRMusicRoom_ClassInstance->step_left=PRMusicRoom_step_left;
	PRMusicRoom_ClassInstance->build_PRRoom=PRMusicRoom_build;
	PRMusicRoom_ClassInstance->collapse=PRMusicRoom_collapse;
	PRMusicRoom_ClassInstance->className_GLUIElement="GLUIElement";
	PRMusicRoom_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	PRMusicRoom_ClassInstance->init_name_frame=PRMusicRoom_init_name_frame;
	PRMusicRoom_ClassInstance->destruct_GLUIElement=PRMusicRoom_destruct;
	PRMusicRoom_ClassInstance->set_level=PRMusicRoom_set_level;
	PRMusicRoom_ClassInstance->set_group=PRMusicRoom_set_group;
	PRMusicRoom_ClassInstance->set_texture=PRMusicRoom_set_texture;
	PRMusicRoom_ClassInstance->set_texture_coords=PRMusicRoom_set_texture_coords;
	PRMusicRoom_ClassInstance->set_color=PRMusicRoom_set_color;
	PRMusicRoom_ClassInstance->set_origo=PRMusicRoom_set_origo;
	PRMusicRoom_ClassInstance->set_extent=PRMusicRoom_set_extent;
	PRMusicRoom_ClassInstance->set_trafo=PRMusicRoom_set_trafo;
	PRMusicRoom_ClassInstance->update_GLUIElement=PRMusicRoom_update;
	PRMusicRoom_ClassInstance->update_frame=PRMusicRoom_update_frame;
	PRMusicRoom_ClassInstance->update_trafo=PRMusicRoom_update_trafo;
	PRMusicRoom_ClassInstance->get_absolute_frame=PRMusicRoom_get_absolute_frame;
	PRMusicRoom_ClassInstance->finalize_frame=PRMusicRoom_finalize_frame;
	PRMusicRoom_ClassInstance->add_element=PRMusicRoom_add_element;
	PRMusicRoom_ClassInstance->remove_element=PRMusicRoom_remove_element;
	PRMusicRoom_ClassInstance->attach=PRMusicRoom_attach;
	PRMusicRoom_ClassInstance->detach=PRMusicRoom_detach;
	PRMusicRoom_ClassInstance->get_relative_touch_line_a_line_b=PRMusicRoom_get_relative_touch_line_a_line_b;
	PRMusicRoom_ClassInstance->intersect_line_a_line_b_elements=PRMusicRoom_intersect_line_a_line_b_elements;
	PRMusicRoom_ClassInstance->touch_began=PRMusicRoom_touch_began;
	PRMusicRoom_ClassInstance->touch_moved=PRMusicRoom_touch_moved;
	PRMusicRoom_ClassInstance->touch_ended=PRMusicRoom_touch_ended;
	PRMusicRoom_ClassInstance->key_down_characters=PRMusicRoom_key_down_characters;
	PRMusicRoom_ClassInstance->key_up_characters=PRMusicRoom_key_up_characters;
	PRMusicRoom_ClassInstance->scroll_x_y=PRMusicRoom_scroll_x_y;
	PRMusicRoom_ClassInstance->focus_on=PRMusicRoom_focus_on;
	PRMusicRoom_ClassInstance->focus_off=PRMusicRoom_focus_off;
	PRMusicRoom_ClassInstance->className_CLObject="CLObject";
	PRMusicRoom_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRMusicRoom_ClassInstance->init=PRMusicRoom_init;
	PRMusicRoom_ClassInstance->destruct_CLObject=PRMusicRoom_destruct;
	PRMusicRoom_ClassInstance->retain=PRMusicRoom_retain;
	PRMusicRoom_ClassInstance->release=PRMusicRoom_release;
	PRMusicRoom_ClassInstance->event=PRMusicRoom_event;
	PRMusicRoom_ClassInstance->describe=PRMusicRoom_describe;
	
}
struct PRMusicRoom* PRMusicRoom_alloc( )
{
	struct PRMusicRoom* result;
	if(PRMusicRoom_ClassInstance==NULL)PRMusicRoom_CreateClass( );
	result=malloc(sizeof(struct PRMusicRoom));
	result->_components=malloc(sizeof(void*)*5);
	result->_class=(void*)&(PRMusicRoom_ClassInstance->className);
	result->_components_PRRoom=result->_components;
	result->_class_PRRoom=(void*)&(PRMusicRoom_ClassInstance->className_PRRoom);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(PRMusicRoom_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRMusicRoom_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_PRRoom);
	result->_components[2]=&(result->_class_GLUIElement);
	result->_components[3]=&(result->_class_CLObject);
	result->_components[4]=NULL;
	return result;
}
void PRMusicRoom_init_name_frame_controller (struct PRMusicRoom* self, char * the_name , MLVector4 the_frame , struct PRController * the_controller ) 
{
	PRRoom_init_name_frame_controller(( cast_object( &PRRoom_ClassInstance , self)),the_name,the_frame,the_controller);
	self->my_info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(self->my_info_view, "info_view",MLVector4Create(0,0,800,-600),the_controller);
	PRInfoView_set_color(self->my_info_view, 0,0,0,0);
	PRInfoView_set_level(self->my_info_view, 60);
	PRInfoView_set_title_label(self->my_info_view, "Room of Music");
	PRInfoView_show(self->my_info_view );
	PRMusicRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->my_info_view)));
	CLDataList_add_data(self->info_views, self->my_info_view);
}
void PRMusicRoom_build (struct PRMusicRoom* self ) 
{
	PRMusicRoom_create_image_area( self, "wall_music.png",600,-600,MLVector3Create(1,1,1),MLVector3Create(0,M_PI/2.0,0),MLVector3Create(0,0,-200));
	PRMusicRoom_create_image_area( self, "wall_music.png",800,-600,MLVector3Create(1,1,1),MLVector3Create(0,0,0),MLVector3Create(0,0,-800));
	PRMusicRoom_create_image_area( self, "floor_music.png",800,-600,MLVector3Create(1,1,1),MLVector3Create(-M_PI/2.0,0,0),MLVector3Create(0,-600,-800));
	PRMusicRoom_create_image_area( self, "guitar.png",90,-200,MLVector3Create(1,1,1),MLVector3Create(-0.2,M_PI/2.0,0),MLVector3Create(0,-400,-250));
	PRMusicRoom_create_image_area( self, "bass.png",100,-250,MLVector3Create(1,1,1),MLVector3Create(-0.2,M_PI/2.0,0),MLVector3Create(0,-350,-500));
	PRMusicRoom_create_empty_view( self, MLVector3Create(1,1,1),MLVector3Create(0,M_PI/3,0.0),MLVector3Create(0.0,0.0,-200.0));
	PRMusicRoom_create_info_view( self, "first.png","first.png","2000","Guitar","I started playing the guitar at the age of 20. I learned it from teacher for one year, and I stayed an average campfire musician since :).",MLVector3Create(.15,.15,.15),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-350.0,-330.0));
	PRMusicRoom_create_info_view( self, "drum.png","drum.png","2003","Drums","I learned it for one year, but I always slow down/speed up with the mood of music, I'm a bad drummer :)",MLVector3Create(.15,.15,.15),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-250.0,-400.0));
	PRMusicRoom_create_info_view( self, "lp.png","lp.png","2001","Bizarreium","In 2001 I established my one-man band. First album came in 2001 under the name of Silenzio. It is fully acoustic. I had a demo after this in 2003, called Falling. It seems that I am the only one who enjoys these, but I love them! :)",MLVector3Create(.15,.15,.15),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-200.0,-250.0));
	PRMusicRoom_create_info_view( self, "pagan.png","pagan.png","2009","Pagan Storm","First real band, we played very bad but killer black metal! :) It was disbanded after 1.5 years. I played the bass guitar.",MLVector3Create(.12,.12,.12),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-50.0,-320.0));
	PRMusicRoom_create_info_view( self, "werewolf.png","werewolf.png","2012","My Baby Is A Werewolf","I released a single called My Baby is a Werewolf under the band name The MilGra Experiment, it is my second one-man band. It's not so terrible, a lot of people liked it, a strange feeling!!! :)",MLVector3Create(.2,.2,.2),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-50.0,-450.0));
	PRMusicRoom_create_info_view( self, "qasong.png","qasong.png","2012","QA & SCRUM song","QA & SCRUM song by Zsuzsanna Sebestyen, produced and bassed by myself :) It was a huge success in the hungarian IT/Scrum scene.",MLVector3Create(.16,.16,.16),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-170.0,-620.0));
	PRMusicRoom_create_info_view( self, "tomjones.png","tomjones.png","2013","Tom Jones : If he should ever leave you","In 2012 I started learning singing at two professional singers, at the end of 2013 I covered and recorded this very very sweet song in a studio. This is my finest performance so far.",MLVector3Create(.15,.15,.15),MLVector3Create(0.0,M_PI/2,0.0),MLVector3Create(0.0,-350.0,-600.0));
}
void PRMusicRoom_destruct (struct PRMusicRoom* self ) 
{
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRMusicRoom_create_info_view (struct PRMusicRoom* self, char * the_image , char * the_large_image , char * the_title_label , char * the_subtitle_label , char * the_description_label , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*small_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_image);
	struct CLString*large_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_large_image);
	char*small_path_c=small_path->_class->c_string( (void*) small_path->_components[0] );
	char*large_path_c=large_path->_class->c_string( (void*) large_path->_components[0] );
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	info_view->small_path=small_path_c;
	info_view->large_path=large_path_c;
	PRInfoView_set_color(info_view, 0,0,0,0);
	PRInfoView_set_level(info_view, 30-(int)self->info_views->length);
	PRInfoView_set_title_label(info_view, the_title_label);
	PRInfoView_set_subtitle_label(info_view, the_subtitle_label);
	PRInfoView_set_description_label(info_view, the_description_label);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	PRInfoView_set_image(info_view, info_view->small_path);
	PRMusicRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLString_release(small_path );
	CLString_release(large_path );
	GLUITrafo_release(local_trafo );
}
void PRMusicRoom_create_empty_view (struct PRMusicRoom* self, MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	PRInfoView_set_color(info_view, 0,0,0,.5);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	info_view->hidden=1;
	PRMusicRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	GLUITrafo_release(local_trafo );
}
void PRMusicRoom_create_texture_area (struct PRMusicRoom* self, struct GLTextureSquare * the_texture , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUIElement*area;
	struct GLUITrafo*area_trafo;
	area_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(area_trafo );
	area_trafo->scale=the_scale;
	area_trafo->rotation=the_rotation;
	area_trafo->translation=the_translation;
	area=GLUIElement_alloc( );
	GLUIElement_init_name_frame(area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height));
	GLUIElement_set_trafo(area, GLUITrafo_matrix(area_trafo ),0);
	GLUIElement_set_texture(area, the_texture->id);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,0,0);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,the_texture->hRatio,1);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,the_texture->hRatio,2);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,0,3);
	PRMusicRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , area)));
	GLUITrafo_release(area_trafo );
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , area)));
}
void PRMusicRoom_create_image_area (struct PRMusicRoom* self, char * the_path , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*image_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_path);
	char*image_path_c=image_path->_class->c_string( (void*) image_path->_components[0] );
	struct GLUITrafo*image_trafo;
	struct GLUIImageArea*image_area;
	image_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(image_trafo );
	image_trafo->scale=the_scale;
	image_trafo->rotation=the_rotation;
	image_trafo->translation=the_translation;
	image_area=GLUIImageArea_alloc( );
	GLUIImageArea_init_name_frame_path(image_area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height),image_path_c);
	GLUIImageArea_set_trafo(image_area, GLUITrafo_matrix(image_trafo ),0);
	PRMusicRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , image_area)));
	GLUITrafo_release(image_trafo );
	CLString_release(image_path );
	free(image_path_c);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , image_area)));
}
void PRMusicRoom_update (struct PRMusicRoom* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	if(self->counter>0)
	{
		self->counter-=1;
		if(self->counter==1)
		{
			self->last_room->_class->collapse( (void*) self->last_room->_components[0] );
			PRMusicRoom_build( self );
		}
	}
}
void PRMusicRoom_step_right (struct PRMusicRoom* self ) 
{
	if(self->counter>0)return;
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==0&&one_view->hidden==0)one_view->_class->show_with_animation( (void*) one_view->_components[0] );
	else
	{
		self->view_index+=1;
		if(self->view_index==self->info_views->length)
		{
			self->view_index=0;
			struct PRInfoView*next_info_view=self->next_room->info_views->_class->data_at_index( (void*) self->next_room->info_views->_components[0], 0);
			self->next_room->counter=151;
			self->controller->actual_room=self->next_room;
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , next_info_view)),150,kGLUIAnimationEaseIn);
		}
		else
		{
			one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRMusicRoom_step_left (struct PRMusicRoom* self ) 
{
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
	else
	{
		self->view_index-=1;
		if(self->view_index<0)self->view_index=0;
		else
		{
			struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRMusicRoom_collapse (struct PRMusicRoom* self ) 
{
	struct CLLink*link36;
	void* kid_data;
	link36=self->removables->head;while( link36!=NULL){kid_data=link36->data; 
	
		struct GLUIElement*kid=kid_data;
		PRMusicRoom_remove_element( self, kid);
		kid->_class->release( (void*) kid->_components[0] );
	link36=link36->next;}
	self->view_index=0;
	self->info_views->_class->remove_all_data( (void*) self->info_views->_components[0] );
	self->removables->_class->remove_all_data( (void*) self->removables->_components[0] );
	self->info_views->_class->add_data( (void*) self->info_views->_components[0], self->my_info_view);
}
void PRMusicRoom_init_name_frame (struct PRMusicRoom* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	PRMusicRoom_update_frame( self );
}
void PRMusicRoom_set_level (struct PRMusicRoom* self, int the_level ) 
{
	self->level=the_level;
}
void PRMusicRoom_set_group (struct PRMusicRoom* self, int the_group ) 
{
	self->group=the_group;
}
void PRMusicRoom_set_texture (struct PRMusicRoom* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void PRMusicRoom_set_texture_coords (struct PRMusicRoom* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void PRMusicRoom_set_color (struct PRMusicRoom* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void PRMusicRoom_set_origo (struct PRMusicRoom* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	PRMusicRoom_update_frame( self );
}
void PRMusicRoom_set_extent (struct PRMusicRoom* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	PRMusicRoom_update_frame( self );
}
void PRMusicRoom_set_trafo (struct PRMusicRoom* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)PRMusicRoom_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)PRMusicRoom_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)PRMusicRoom_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)PRMusicRoom_attach( self, one_drawer);
		}
	}
	PRMusicRoom_update_trafo( self );
}
void PRMusicRoom_update_frame (struct PRMusicRoom* self ) 
{
	struct CLLink*link37;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link37=self->kids->head;while( link37!=NULL){data=link37->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link37=link37->next;}
	}
}
void PRMusicRoom_update_trafo (struct PRMusicRoom* self ) 
{
	struct CLLink*link38;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link38=self->kids->head;while( link38!=NULL){data=link38->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link38=link38->next;}
	}
}
void PRMusicRoom_get_absolute_frame (struct PRMusicRoom* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void PRMusicRoom_finalize_frame (struct PRMusicRoom* self ) 
{
	MLVector3 a,b,c,d;
	PRMusicRoom_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void PRMusicRoom_add_element (struct PRMusicRoom* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void PRMusicRoom_remove_element (struct PRMusicRoom* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void PRMusicRoom_attach (struct PRMusicRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link39;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	PRMusicRoom_update_frame( self );
	PRMusicRoom_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link39=self->kids->head;while( link39!=NULL){data=link39->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link39=link39->next;}
}
void PRMusicRoom_detach (struct PRMusicRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link40;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link40=self->kids->head;while( link40!=NULL){data=link40->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link40=link40->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 PRMusicRoom_get_relative_touch_line_a_line_b (struct PRMusicRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	PRMusicRoom_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void PRMusicRoom_intersect_line_a_line_b_elements (struct PRMusicRoom* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link41;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=PRMusicRoom_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link41=self->kids->head;while( link41!=NULL){data=link41->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link41=link41->next;}
	}
}
void PRMusicRoom_touch_began (struct PRMusicRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRMusicRoom_touch_moved (struct PRMusicRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRMusicRoom_touch_ended (struct PRMusicRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRMusicRoom_key_down_characters (struct PRMusicRoom* self, char * the_characters ) 
{

}
void PRMusicRoom_key_up_characters (struct PRMusicRoom* self, char * the_characters ) 
{

}
void PRMusicRoom_scroll_x_y (struct PRMusicRoom* self, float the_x , float the_y ) 
{

}
void PRMusicRoom_focus_on (struct PRMusicRoom* self ) 
{

}
void PRMusicRoom_focus_off (struct PRMusicRoom* self ) 
{

}
void PRMusicRoom_init (struct PRMusicRoom* self ) 
{
	self->retain_count=1;
}
void PRMusicRoom_retain (struct PRMusicRoom* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRMusicRoom_release (struct PRMusicRoom* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRMusicRoom_event (struct PRMusicRoom* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRMusicRoom_describe (struct PRMusicRoom* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void PRRoom_CreateClass( )
{
	PRRoom_ClassInstance=malloc(sizeof(struct PRRoom_Class));
	PRRoom_ClassInstance->className="PRRoom";
	PRRoom_ClassInstance->classId=&PRRoom_ClassInstance;
	PRRoom_ClassInstance->init_name_frame_controller=PRRoom_init_name_frame_controller;
	PRRoom_ClassInstance->destruct=PRRoom_destruct;
	PRRoom_ClassInstance->create_info_view=PRRoom_create_info_view;
	PRRoom_ClassInstance->create_empty_view=PRRoom_create_empty_view;
	PRRoom_ClassInstance->create_texture_area=PRRoom_create_texture_area;
	PRRoom_ClassInstance->create_image_area=PRRoom_create_image_area;
	PRRoom_ClassInstance->update=PRRoom_update;
	PRRoom_ClassInstance->step_right=PRRoom_step_right;
	PRRoom_ClassInstance->step_left=PRRoom_step_left;
	PRRoom_ClassInstance->build=PRRoom_build;
	PRRoom_ClassInstance->collapse=PRRoom_collapse;
	PRRoom_ClassInstance->className_GLUIElement="GLUIElement";
	PRRoom_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	PRRoom_ClassInstance->init_name_frame=PRRoom_init_name_frame;
	PRRoom_ClassInstance->destruct_GLUIElement=PRRoom_destruct;
	PRRoom_ClassInstance->set_level=PRRoom_set_level;
	PRRoom_ClassInstance->set_group=PRRoom_set_group;
	PRRoom_ClassInstance->set_texture=PRRoom_set_texture;
	PRRoom_ClassInstance->set_texture_coords=PRRoom_set_texture_coords;
	PRRoom_ClassInstance->set_color=PRRoom_set_color;
	PRRoom_ClassInstance->set_origo=PRRoom_set_origo;
	PRRoom_ClassInstance->set_extent=PRRoom_set_extent;
	PRRoom_ClassInstance->set_trafo=PRRoom_set_trafo;
	PRRoom_ClassInstance->update_GLUIElement=PRRoom_update;
	PRRoom_ClassInstance->update_frame=PRRoom_update_frame;
	PRRoom_ClassInstance->update_trafo=PRRoom_update_trafo;
	PRRoom_ClassInstance->get_absolute_frame=PRRoom_get_absolute_frame;
	PRRoom_ClassInstance->finalize_frame=PRRoom_finalize_frame;
	PRRoom_ClassInstance->add_element=PRRoom_add_element;
	PRRoom_ClassInstance->remove_element=PRRoom_remove_element;
	PRRoom_ClassInstance->attach=PRRoom_attach;
	PRRoom_ClassInstance->detach=PRRoom_detach;
	PRRoom_ClassInstance->get_relative_touch_line_a_line_b=PRRoom_get_relative_touch_line_a_line_b;
	PRRoom_ClassInstance->intersect_line_a_line_b_elements=PRRoom_intersect_line_a_line_b_elements;
	PRRoom_ClassInstance->touch_began=PRRoom_touch_began;
	PRRoom_ClassInstance->touch_moved=PRRoom_touch_moved;
	PRRoom_ClassInstance->touch_ended=PRRoom_touch_ended;
	PRRoom_ClassInstance->key_down_characters=PRRoom_key_down_characters;
	PRRoom_ClassInstance->key_up_characters=PRRoom_key_up_characters;
	PRRoom_ClassInstance->scroll_x_y=PRRoom_scroll_x_y;
	PRRoom_ClassInstance->focus_on=PRRoom_focus_on;
	PRRoom_ClassInstance->focus_off=PRRoom_focus_off;
	PRRoom_ClassInstance->className_CLObject="CLObject";
	PRRoom_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PRRoom_ClassInstance->init=PRRoom_init;
	PRRoom_ClassInstance->destruct_CLObject=PRRoom_destruct;
	PRRoom_ClassInstance->retain=PRRoom_retain;
	PRRoom_ClassInstance->release=PRRoom_release;
	PRRoom_ClassInstance->event=PRRoom_event;
	PRRoom_ClassInstance->describe=PRRoom_describe;
	
}
struct PRRoom* PRRoom_alloc( )
{
	struct PRRoom* result;
	if(PRRoom_ClassInstance==NULL)PRRoom_CreateClass( );
	result=malloc(sizeof(struct PRRoom));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(PRRoom_ClassInstance->className);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(PRRoom_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PRRoom_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLUIElement);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void PRRoom_init_name_frame_controller (struct PRRoom* self, char * the_name , MLVector4 the_frame , struct PRController * the_controller ) 
{
	GLUIElement_init_name_frame(( cast_object( &GLUIElement_ClassInstance , self)),the_name,the_frame);
	self->controller=the_controller;
	self->info_views=CLDataList_alloc( );
	CLDataList_init(self->info_views );
	self->removables=CLDataList_alloc( );
	CLDataList_init(self->removables );
	self->view_index=0;
	self->counter=0;
}
void PRRoom_destruct (struct PRRoom* self ) 
{
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void PRRoom_create_info_view (struct PRRoom* self, char * the_image , char * the_large_image , char * the_title_label , char * the_subtitle_label , char * the_description_label , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*small_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_image);
	struct CLString*large_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_large_image);
	char*small_path_c=small_path->_class->c_string( (void*) small_path->_components[0] );
	char*large_path_c=large_path->_class->c_string( (void*) large_path->_components[0] );
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	info_view->small_path=small_path_c;
	info_view->large_path=large_path_c;
	PRInfoView_set_color(info_view, 0,0,0,0);
	PRInfoView_set_level(info_view, 30-(int)self->info_views->length);
	PRInfoView_set_title_label(info_view, the_title_label);
	PRInfoView_set_subtitle_label(info_view, the_subtitle_label);
	PRInfoView_set_description_label(info_view, the_description_label);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	PRInfoView_set_image(info_view, info_view->small_path);
	PRRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLString_release(small_path );
	CLString_release(large_path );
	GLUITrafo_release(local_trafo );
}
void PRRoom_create_empty_view (struct PRRoom* self, MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUITrafo*local_trafo;
	struct PRInfoView*info_view;
	local_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(local_trafo );
	local_trafo->scale=the_scale;
	local_trafo->rotation=the_rotation;
	local_trafo->translation=the_translation;
	info_view=PRInfoView_alloc( );
	PRInfoView_init_name_frame_controller(info_view, "pic_a_view",MLVector4Create(0,0,800,-600),self->controller);
	PRInfoView_set_color(info_view, 0,0,0,.5);
	PRInfoView_set_trafo(info_view, GLUITrafo_matrix(local_trafo ),0);
	info_view->hidden=1;
	PRRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , info_view)));
	CLDataList_add_data(self->info_views, info_view);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , info_view)));
	GLUITrafo_release(local_trafo );
}
void PRRoom_create_texture_area (struct PRRoom* self, struct GLTextureSquare * the_texture , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct GLUIElement*area;
	struct GLUITrafo*area_trafo;
	area_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(area_trafo );
	area_trafo->scale=the_scale;
	area_trafo->rotation=the_rotation;
	area_trafo->translation=the_translation;
	area=GLUIElement_alloc( );
	GLUIElement_init_name_frame(area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height));
	GLUIElement_set_trafo(area, GLUITrafo_matrix(area_trafo ),0);
	GLUIElement_set_texture(area, the_texture->id);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,0,0);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], 0,the_texture->hRatio,1);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,the_texture->hRatio,2);
	area->model->_class->set_texture_coord( (void*) area->model->_components[0], the_texture->wRatio,0,3);
	PRRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , area)));
	GLUITrafo_release(area_trafo );
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , area)));
}
void PRRoom_create_image_area (struct PRRoom* self, char * the_path , float the_width , float the_height , MLVector3 the_scale , MLVector3 the_rotation , MLVector3 the_translation ) 
{
	struct CLString*image_path=self->controller->settings->_class->path_for_file( (void*) self->controller->settings->_components[0], the_path);
	char*image_path_c=image_path->_class->c_string( (void*) image_path->_components[0] );
	struct GLUITrafo*image_trafo;
	struct GLUIImageArea*image_area;
	image_trafo=GLUITrafo_alloc( );
	GLUITrafo_init(image_trafo );
	image_trafo->scale=the_scale;
	image_trafo->rotation=the_rotation;
	image_trafo->translation=the_translation;
	image_area=GLUIImageArea_alloc( );
	GLUIImageArea_init_name_frame_path(image_area, "GLUIListSquare.ui_image",MLVector4Create(0,0,the_width,the_height),image_path_c);
	GLUIImageArea_set_trafo(image_area, GLUITrafo_matrix(image_trafo ),0);
	PRRoom_add_element( self, (cast_object( &GLUIElement_ClassInstance , image_area)));
	GLUITrafo_release(image_trafo );
	CLString_release(image_path );
	free(image_path_c);
	CLDataList_add_data(self->removables, (cast_object( &GLUIElement_ClassInstance , image_area)));
}
void PRRoom_update (struct PRRoom* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	if(self->counter>0)
	{
		self->counter-=1;
		if(self->counter==1)
		{
			self->last_room->_class->collapse( (void*) self->last_room->_components[0] );
			PRRoom_build( self );
		}
	}
}
void PRRoom_step_right (struct PRRoom* self ) 
{
	if(self->counter>0)return;
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==0&&one_view->hidden==0)one_view->_class->show_with_animation( (void*) one_view->_components[0] );
	else
	{
		self->view_index+=1;
		if(self->view_index==self->info_views->length)
		{
			self->view_index=0;
			struct PRInfoView*next_info_view=self->next_room->info_views->_class->data_at_index( (void*) self->next_room->info_views->_components[0], 0);
			self->next_room->counter=151;
			self->controller->actual_room=self->next_room;
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , next_info_view)),150,kGLUIAnimationEaseIn);
		}
		else
		{
			one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRRoom_step_left (struct PRRoom* self ) 
{
	struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
	if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
	else
	{
		self->view_index-=1;
		if(self->view_index<0)self->view_index=0;
		else
		{
			struct PRInfoView*one_view=self->info_views->_class->data_at_index( (void*) self->info_views->_components[0], self->view_index);
			if(one_view->info_shown==1)one_view->_class->hide( (void*) one_view->_components[0] );
			self->controller->ui_controller->_class->zoom_to_element( (void*) self->controller->ui_controller->_components[0], (cast_object( &GLUIElement_ClassInstance , one_view)),150,kGLUIAnimationEaseIn);
		}
	}
}
void PRRoom_build (struct PRRoom* self ) 
{

}
void PRRoom_collapse (struct PRRoom* self ) 
{
	struct CLLink*link42;
	void* kid_data;
	link42=self->removables->head;while( link42!=NULL){kid_data=link42->data; 
	
		struct GLUIElement*kid=kid_data;
		PRRoom_remove_element( self, kid);
		kid->_class->release( (void*) kid->_components[0] );
	link42=link42->next;}
	self->view_index=0;
	self->info_views->_class->remove_all_data( (void*) self->info_views->_components[0] );
	self->removables->_class->remove_all_data( (void*) self->removables->_components[0] );
	self->info_views->_class->add_data( (void*) self->info_views->_components[0], self->my_info_view);
}
void PRRoom_init_name_frame (struct PRRoom* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	PRRoom_update_frame( self );
}
void PRRoom_set_level (struct PRRoom* self, int the_level ) 
{
	self->level=the_level;
}
void PRRoom_set_group (struct PRRoom* self, int the_group ) 
{
	self->group=the_group;
}
void PRRoom_set_texture (struct PRRoom* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void PRRoom_set_texture_coords (struct PRRoom* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void PRRoom_set_color (struct PRRoom* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void PRRoom_set_origo (struct PRRoom* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	PRRoom_update_frame( self );
}
void PRRoom_set_extent (struct PRRoom* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	PRRoom_update_frame( self );
}
void PRRoom_set_trafo (struct PRRoom* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)PRRoom_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)PRRoom_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)PRRoom_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)PRRoom_attach( self, one_drawer);
		}
	}
	PRRoom_update_trafo( self );
}
void PRRoom_update_frame (struct PRRoom* self ) 
{
	struct CLLink*link43;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link43=self->kids->head;while( link43!=NULL){data=link43->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link43=link43->next;}
	}
}
void PRRoom_update_trafo (struct PRRoom* self ) 
{
	struct CLLink*link44;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link44=self->kids->head;while( link44!=NULL){data=link44->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link44=link44->next;}
	}
}
void PRRoom_get_absolute_frame (struct PRRoom* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void PRRoom_finalize_frame (struct PRRoom* self ) 
{
	MLVector3 a,b,c,d;
	PRRoom_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void PRRoom_add_element (struct PRRoom* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void PRRoom_remove_element (struct PRRoom* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void PRRoom_attach (struct PRRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link45;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	PRRoom_update_frame( self );
	PRRoom_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link45=self->kids->head;while( link45!=NULL){data=link45->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link45=link45->next;}
}
void PRRoom_detach (struct PRRoom* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link46;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link46=self->kids->head;while( link46!=NULL){data=link46->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link46=link46->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 PRRoom_get_relative_touch_line_a_line_b (struct PRRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	PRRoom_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void PRRoom_intersect_line_a_line_b_elements (struct PRRoom* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link47;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=PRRoom_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link47=self->kids->head;while( link47!=NULL){data=link47->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link47=link47->next;}
	}
}
void PRRoom_touch_began (struct PRRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRRoom_touch_moved (struct PRRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRRoom_touch_ended (struct PRRoom* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void PRRoom_key_down_characters (struct PRRoom* self, char * the_characters ) 
{

}
void PRRoom_key_up_characters (struct PRRoom* self, char * the_characters ) 
{

}
void PRRoom_scroll_x_y (struct PRRoom* self, float the_x , float the_y ) 
{

}
void PRRoom_focus_on (struct PRRoom* self ) 
{

}
void PRRoom_focus_off (struct PRRoom* self ) 
{

}
void PRRoom_init (struct PRRoom* self ) 
{
	self->retain_count=1;
}
void PRRoom_retain (struct PRRoom* self ) 
{
	self->retain_count=self->retain_count+1;
}
void PRRoom_release (struct PRRoom* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PRRoom_event (struct PRRoom* self, int the_id , void * the_source , void * the_data ) 
{

}
void PRRoom_describe (struct PRRoom* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLBitmapRGBA_CreateClass( )
{
	GLBitmapRGBA_ClassInstance=malloc(sizeof(struct GLBitmapRGBA_Class));
	GLBitmapRGBA_ClassInstance->className="GLBitmapRGBA";
	GLBitmapRGBA_ClassInstance->classId=&GLBitmapRGBA_ClassInstance;
	GLBitmapRGBA_ClassInstance->init_width_height=GLBitmapRGBA_init_width_height;
	GLBitmapRGBA_ClassInstance->destruct=GLBitmapRGBA_destruct;
	GLBitmapRGBA_ClassInstance->fill_sx_sy_ex_ey_r_g_b_a=GLBitmapRGBA_fill_sx_sy_ex_ey_r_g_b_a;
	GLBitmapRGBA_ClassInstance->gradient_sx_sy_ex_ey_r_g_b_a_r_g_b_a=GLBitmapRGBA_gradient_sx_sy_ex_ey_r_g_b_a_r_g_b_a;
	GLBitmapRGBA_ClassInstance->set_x_y_r_g_b_a=GLBitmapRGBA_set_x_y_r_g_b_a;
	GLBitmapRGBA_ClassInstance->get_x_y_r_g_b_a=GLBitmapRGBA_get_x_y_r_g_b_a;
	GLBitmapRGBA_ClassInstance->add_shadow=GLBitmapRGBA_add_shadow;
	GLBitmapRGBA_ClassInstance->push_shadow_with_distance=GLBitmapRGBA_push_shadow_with_distance;
	GLBitmapRGBA_ClassInstance->blend_bitmap_x_y=GLBitmapRGBA_blend_bitmap_x_y;
	GLBitmapRGBA_ClassInstance->className_CLObject="CLObject";
	GLBitmapRGBA_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLBitmapRGBA_ClassInstance->init=GLBitmapRGBA_init;
	GLBitmapRGBA_ClassInstance->destruct_CLObject=GLBitmapRGBA_destruct;
	GLBitmapRGBA_ClassInstance->retain=GLBitmapRGBA_retain;
	GLBitmapRGBA_ClassInstance->release=GLBitmapRGBA_release;
	GLBitmapRGBA_ClassInstance->event=GLBitmapRGBA_event;
	GLBitmapRGBA_ClassInstance->describe=GLBitmapRGBA_describe;
	
}
struct GLBitmapRGBA* GLBitmapRGBA_alloc( )
{
	struct GLBitmapRGBA* result;
	if(GLBitmapRGBA_ClassInstance==NULL)GLBitmapRGBA_CreateClass( );
	result=malloc(sizeof(struct GLBitmapRGBA));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLBitmapRGBA_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLBitmapRGBA_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLBitmapRGBA_init_width_height (struct GLBitmapRGBA* self, int theWidth , int theHeight ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=theWidth;
	self->height=theHeight;
	self->length=4*self->width*self->height;
	self->data=calloc(self->length,sizeof(unsigned char*));
}
void GLBitmapRGBA_destruct (struct GLBitmapRGBA* self ) 
{
	free(self->data);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLBitmapRGBA_fill_sx_sy_ex_ey_r_g_b_a (struct GLBitmapRGBA* self, int theSX , int theSY , int theEX , int theEY , float the_r , float the_g , float the_b , float theA ) 
{
	int x,y,position;
	unsigned int r,g,b,a;
	if(theEX<theSX)return;
	if(theEY<theSY)return;
	if(theSX<0)theSX=0;
	if(theSY<0)theSY=0;
	if(theEX>=self->width)theEX=self->width-1;
	if(theEY>=self->height)theEY=self->height-1;
	r=(int)(the_r*255.0);
	g=(int)(the_g*255.0);
	b=(int)(the_b*255.0);
	a=(int)(theA*255.0);
	for(y=theSY;
	y<theEY;
	y++)
	{
		for(x=theSX;
		x<theEX;
		x++)
		{
			position=(y*self->width+x)*4;
			self->data[position]=r;
			self->data[position+1]=g;
			self->data[position+2]=b;
			self->data[position+3]=a;
		}
	}
}
void GLBitmapRGBA_gradient_sx_sy_ex_ey_r_g_b_a_r_g_b_a (struct GLBitmapRGBA* self, int theSX , int theSY , int theEX , int theEY , float theSR , float theSG , float theSB , float theSA , float theER , float theEG , float theEB , float theEA ) 
{
	int x,y,position;
	float r,g,b,a,dr,dg,db,da,step;
	if(theEX<theSX)return;
	if(theEY<theSY)return;
	if(theSX<0)theSX=0;
	if(theSY<0)theSY=0;
	if(theEX>=self->width)theEX=self->width-1;
	if(theEY>=self->height)theEY=self->height-1;
	step=(float)(theEX-theSX);
	dr=(theER-theSR)/step;
	dg=(theEG-theSG)/step;
	db=(theEB-theSB)/step;
	da=(theEA-theSA)/step;
	for(y=theSY;
	y<theEY;
	y++)
	{
		r=theSR;
		g=theSG;
		b=theSB;
		a=theSA;
		for(x=theSX;
		x<theEX;
		x++)
		{
			position=(y*self->width+x)*4;
			self->data[position]=(int)(r*255.0);
			self->data[position+1]=(int)(g*255.0);
			self->data[position+2]=(int)(b*255.0);
			self->data[position+3]=(int)(a*255.0);
			r+=dr;
			g+=dg;
			b+=db;
			a+=da;
		}
	}
}
void GLBitmapRGBA_set_x_y_r_g_b_a (struct GLBitmapRGBA* self, int the_x , int the_y , int the_r , int the_g , int the_b , int theA ) 
{

}
void GLBitmapRGBA_get_x_y_r_g_b_a (struct GLBitmapRGBA* self, int the_x , int the_y , int * the_r , int * the_g , int * the_b , int * theA ) 
{

}
void GLBitmapRGBA_add_shadow (struct GLBitmapRGBA* self ) 
{
	int x,y,NI,SI,EI,WI,NI2,SI2,EI2,WI2;
	unsigned char*clone;
	clone=malloc(self->length);
	memcpy(clone,self->data,self->length);
	for(y=0;
	y<self->height;
	y++)
	{
		for(x=0;
		x<self->width;
		x++)
		{
			int srcIndex=(y*self->width+x)*4;
			unsigned int srcA=clone[srcIndex+3];
			if(srcA>0)
			{
				NI=((y-1)*self->width+x)*4;
				SI=((y+1)*self->width+x)*4;
				EI=(y*self->width+x-1)*4;
				WI=(y*self->width+x+1)*4;
				if(NI>0&&clone[NI+3]==0)
				{
					self->data[NI+3]=155;
					NI2=((y-2)*self->width+x)*4;
					if(NI2>0&&clone[NI2+3]==0)self->data[NI2+3]=55;
				}
				if(SI<self->length&&clone[SI+3]==0)
				{
					self->data[SI+3]=155;
					SI2=((y+2)*self->width+x)*4;
					if(SI2<self->length&&clone[SI2+3]==0)self->data[SI2+3]=55;
				}
				if(x-1>0&&clone[EI+3]==0)
				{
					self->data[EI+3]=155;
					EI2=(y*self->width+x-2)*4;
					if(EI2>0&&clone[EI2+3]==0)self->data[EI2+3]=55;
				}
				if(x+1<self->width&&clone[WI+3]==0)
				{
					self->data[WI+3]=155;
					WI2=(y*self->width+x+2)*4;
					if(WI2<self->length&&clone[WI2+3]==0)self->data[WI2+3]=55;
				}
			}
		}
	}
	free(clone);
}
void GLBitmapRGBA_push_shadow_with_distance (struct GLBitmapRGBA* self, int theDistance ) 
{
	int x,y;
	unsigned char*clone;
	clone=malloc(self->length);
	memcpy(clone,self->data,self->length);
	for(y=0;
	y<self->height;
	y++)
	{
		for(x=0;
		x<self->width;
		x++)
		{
			int srcIndex=(y*self->width+x)*4;
			unsigned int srcA=clone[srcIndex+3];
			if(srcA>0)
			{
				self->data[srcIndex]=clone[srcIndex];
				self->data[srcIndex+1]=clone[srcIndex+1];
				self->data[srcIndex+2]=clone[srcIndex+2];
				self->data[srcIndex+3]=clone[srcIndex+3];
				if(x+theDistance<self->width&&y+theDistance<self->height)
				{
					int dstIndex=((y+theDistance)*self->width+(x+theDistance))*4;
					self->data[dstIndex]=0;
					self->data[dstIndex+1]=0;
					self->data[dstIndex+2]=0;
					self->data[dstIndex+3]=clone[srcIndex+3];
				}
			}
		}
	}
}
void GLBitmapRGBA_blend_bitmap_x_y (struct GLBitmapRGBA* self, struct GLBitmapRGBA * the_bitmap , int the_x , int the_y ) 
{
	int x,y,bx,by,srcIndex,dstIndex;
	float srcR,srcG,srcB,srcA,dstR,dstG,dstB,dstA,outA,outR,outG,outB;
	unsigned char*srcData;
	unsigned char*dstData;
	bx=the_x+the_bitmap->width;
	if(bx>self->width)bx=self->width;
	by=the_y+the_bitmap->height;
	if(by>self->height)by=self->height;
	srcData=the_bitmap->data;
	dstData=self->data;
	for(y=the_y;
	y<by;
	y++)
	{
		for(x=the_x;
		x<bx;
		x++)
		{
			srcIndex=((y-the_y)*the_bitmap->width+(x-the_x))*4;
			dstIndex=(y*self->width+x)*4;
			srcR=(float)srcData[srcIndex]/255.0;
			srcG=(float)srcData[srcIndex+1]/255.0;
			srcB=(float)srcData[srcIndex+2]/255.0;
			srcA=(float)srcData[srcIndex+3]/255.0;
			dstR=(float)dstData[dstIndex]/255.0;
			dstG=(float)dstData[dstIndex+1]/255.0;
			dstB=(float)dstData[dstIndex+2]/255.0;
			dstA=(float)dstData[dstIndex+3]/255.0;
			outA=srcA+dstA*(1-srcA);
			outR=(srcR*srcA+dstR*dstA*(1-srcA))/outA;
			outG=(srcG*srcA+dstG*dstA*(1-srcA))/outA;
			outB=(srcB*srcA+dstB*dstA*(1-srcA))/outA;
			dstData[dstIndex]=(int)(outR*255.0);
			dstData[dstIndex+1]=(int)(outG*255.0);
			dstData[dstIndex+2]=(int)(outB*255.0);
			dstData[dstIndex+3]=(int)(outA*255.0);
		}
	}
}
void GLBitmapRGBA_init (struct GLBitmapRGBA* self ) 
{
	self->retain_count=1;
}
void GLBitmapRGBA_retain (struct GLBitmapRGBA* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLBitmapRGBA_release (struct GLBitmapRGBA* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLBitmapRGBA_event (struct GLBitmapRGBA* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLBitmapRGBA_describe (struct GLBitmapRGBA* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLTextureSquare_CreateClass( )
{
	GLTextureSquare_ClassInstance=malloc(sizeof(struct GLTextureSquare_Class));
	GLTextureSquare_ClassInstance->className="GLTextureSquare";
	GLTextureSquare_ClassInstance->classId=&GLTextureSquare_ClassInstance;
	GLTextureSquare_ClassInstance->init_width_height=GLTextureSquare_init_width_height;
	GLTextureSquare_ClassInstance->destruct=GLTextureSquare_destruct;
	GLTextureSquare_ClassInstance->clone_bitmap=GLTextureSquare_clone_bitmap;
	GLTextureSquare_ClassInstance->className_CLObject="CLObject";
	GLTextureSquare_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLTextureSquare_ClassInstance->init=GLTextureSquare_init;
	GLTextureSquare_ClassInstance->destruct_CLObject=GLTextureSquare_destruct;
	GLTextureSquare_ClassInstance->retain=GLTextureSquare_retain;
	GLTextureSquare_ClassInstance->release=GLTextureSquare_release;
	GLTextureSquare_ClassInstance->event=GLTextureSquare_event;
	GLTextureSquare_ClassInstance->describe=GLTextureSquare_describe;
	
}
struct GLTextureSquare* GLTextureSquare_alloc( )
{
	struct GLTextureSquare* result;
	if(GLTextureSquare_ClassInstance==NULL)GLTextureSquare_CreateClass( );
	result=malloc(sizeof(struct GLTextureSquare));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLTextureSquare_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLTextureSquare_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLTextureSquare_init_width_height (struct GLTextureSquare* self, int the_width , int the_height ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->r=0.0;
	self->g=0.0;
	self->b=0.0;
	self->a=0.0;
	self->width=the_width;
	self->height=the_height;
	self->tex_width=2;
	self->tex_height=2;
	while(self->tex_width<self->width)self->tex_width*=2;
	while(self->tex_height<self->height)self->tex_height*=2;
	self->wRatio=(float)self->width/(float)self->tex_width;
	self->hRatio=(float)self->height/(float)self->tex_height;
	glGenTextures(1,&self->id);
	glBindTexture(GL_TEXTURE_2D,self->id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);
}
void GLTextureSquare_destruct (struct GLTextureSquare* self ) 
{
	glDeleteTextures(1,&self->id);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLTextureSquare_clone_bitmap (struct GLTextureSquare* self, struct GLBitmapRGBA * the_bitmap ) 
{
	struct GLBitmapRGBA*texture;
	texture=GLBitmapRGBA_alloc( );
	GLBitmapRGBA_init_width_height(texture, self->tex_width,self->tex_height);
	GLBitmapRGBA_fill_sx_sy_ex_ey_r_g_b_a(texture, 0,0,self->tex_width,self->tex_height,self->r,self->g,self->b,self->a);
	GLBitmapRGBA_blend_bitmap_x_y(texture, the_bitmap,0,0);
	glBindTexture(GL_TEXTURE_2D,self->id);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,self->tex_width,self->tex_height,0,GL_RGBA,GL_UNSIGNED_BYTE,texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	GLBitmapRGBA_release(texture );
}
void GLTextureSquare_init (struct GLTextureSquare* self ) 
{
	self->retain_count=1;
}
void GLTextureSquare_retain (struct GLTextureSquare* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLTextureSquare_release (struct GLTextureSquare* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLTextureSquare_event (struct GLTextureSquare* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLTextureSquare_describe (struct GLTextureSquare* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLBitmapRGBAUtils_CreateClass( )
{
	GLBitmapRGBAUtils_ClassInstance=malloc(sizeof(struct GLBitmapRGBAUtils_Class));
	GLBitmapRGBAUtils_ClassInstance->className="GLBitmapRGBAUtils";
	GLBitmapRGBAUtils_ClassInstance->classId=&GLBitmapRGBAUtils_ClassInstance;
	GLBitmapRGBAUtils_ClassInstance->create_bitmap_width_height_text_size=GLBitmapRGBAUtils_create_bitmap_width_height_text_size;
	GLBitmapRGBAUtils_ClassInstance->create_bitmap_map_width_height_r_g_b=GLBitmapRGBAUtils_create_bitmap_map_width_height_r_g_b;
	GLBitmapRGBAUtils_ClassInstance->create_bitmap_pngpath=GLBitmapRGBAUtils_create_bitmap_pngpath;
	
}
struct GLBitmapRGBAUtils* GLBitmapRGBAUtils_alloc( )
{
	struct GLBitmapRGBAUtils* result;
	if(GLBitmapRGBAUtils_ClassInstance==NULL)GLBitmapRGBAUtils_CreateClass( );
	result=malloc(sizeof(struct GLBitmapRGBAUtils));
	result->_components=malloc(sizeof(void*)*2);
	result->_class=(void*)&(GLBitmapRGBAUtils_ClassInstance->className);
	result->_components[0]=&(result->_class);
	result->_components[1]=NULL;
	return result;
}
struct GLBitmapRGBA * GLBitmapRGBAUtils_create_bitmap_width_height_text_size (struct GLBitmapRGBAUtils* self, int the_width , int the_height , char * the_text , int the_size ) 
{
	int index;
	float x,y,dx,dy;
	float*cdata;
	struct CLLink*link;
	struct GLBitmapRGBA*bitmap;
	struct TLPixelFont*font;
	struct TLPixelText*pixelText;
	pixelText=TLPixelText_alloc( );
	TLPixelText_init_cstring(pixelText, the_text);
	bitmap=GLBitmapRGBA_alloc( );
	GLBitmapRGBA_init_width_height(bitmap, the_width,the_height);
	dx=(float)bitmap->width-pixelText->width*the_size;
	dy=(float)bitmap->height-pixelText->height*the_size;
	dx/=2;
	dy/=2;
	link=pixelText->letters->head;
	while(link!=NULL)
	{
		font=link->data;
		cdata=font->data;
		if(font->length>0)
		{
			for(index=0;
			index<font->length;
			index+=2)
			{
				x=(int)dx+cdata[index]*the_size;
				y=(int)dy+cdata[index+1]*the_size;
				bitmap->_class->fill_sx_sy_ex_ey_r_g_b_a( (void*) bitmap->_components[0], x,y,x+the_size,y+the_size,1,1,1,1);
			}
		}
		dx+=font->width*the_size;
		link=link->next;
	}
	GLBitmapRGBA_add_shadow(bitmap );
	TLPixelText_release(pixelText );
	return bitmap;
}
struct GLBitmapRGBA * GLBitmapRGBAUtils_create_bitmap_map_width_height_r_g_b (struct GLBitmapRGBAUtils* self, unsigned char * the_map , int the_width , int the_height , int r , int g , int b ) 
{
	int index;
	struct GLBitmapRGBA*bitmap;
	bitmap=GLBitmapRGBA_alloc( );
	GLBitmapRGBA_init_width_height(bitmap, the_width,the_height);
	for(index=0;
	index<the_width*the_height;
	index++)
	{
		bitmap->data[index*4]=r;
		bitmap->data[index*4+1]=g;
		bitmap->data[index*4+2]=b;
		bitmap->data[index*4+3]=the_map[index];
	}
	return bitmap;
}
struct GLBitmapRGBA * GLBitmapRGBAUtils_create_bitmap_pngpath (struct GLBitmapRGBAUtils* self, char * the_path ) 
{
	struct GLBitmapRGBA*bitmap;
	unsigned char*image=NULL;
	unsigned width=0;
	unsigned height=0;
	if(the_path!=NULL)
	{
		int x,y,n;
		image=stbi_load(the_path,&x,&y,&n,4);
		width=x;
		height=y;
	}
	bitmap=GLBitmapRGBA_alloc( );
	GLBitmapRGBA_init_width_height(bitmap, width,height);
	free(bitmap->data);
	bitmap->data=image;
	return bitmap;
}
void GLUIModel_CreateClass( )
{
	GLUIModel_ClassInstance=malloc(sizeof(struct GLUIModel_Class));
	GLUIModel_ClassInstance->className="GLUIModel";
	GLUIModel_ClassInstance->classId=&GLUIModel_ClassInstance;
	GLUIModel_ClassInstance->init_name=GLUIModel_init_name;
	GLUIModel_ClassInstance->destruct=GLUIModel_destruct;
	GLUIModel_ClassInstance->set_color=GLUIModel_set_color;
	GLUIModel_ClassInstance->set_texture_coord=GLUIModel_set_texture_coord;
	GLUIModel_ClassInstance->set_position=GLUIModel_set_position;
	GLUIModel_ClassInstance->className_CLObject="CLObject";
	GLUIModel_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIModel_ClassInstance->init=GLUIModel_init;
	GLUIModel_ClassInstance->destruct_CLObject=GLUIModel_destruct;
	GLUIModel_ClassInstance->retain=GLUIModel_retain;
	GLUIModel_ClassInstance->release=GLUIModel_release;
	GLUIModel_ClassInstance->event=GLUIModel_event;
	GLUIModel_ClassInstance->describe=GLUIModel_describe;
	
}
struct GLUIModel* GLUIModel_alloc( )
{
	struct GLUIModel* result;
	if(GLUIModel_ClassInstance==NULL)GLUIModel_CreateClass( );
	result=malloc(sizeof(struct GLUIModel));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUIModel_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIModel_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUIModel_init_name (struct GLUIModel* self, char * the_name ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	GLfloat const_data[]=
	{
		0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,-1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f
	}
	;
	self->vertex_elements=9;
	self->vertex_count=6;
	self->data_size=sizeof(GLfloat)*self->vertex_count*self->vertex_elements;
	self->name=the_name;
	self->data=malloc(self->data_size);
	memcpy(self->data,const_data,self->data_size);
}
void GLUIModel_destruct (struct GLUIModel* self ) 
{
	free(self->data);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUIModel_set_color (struct GLUIModel* self, float the_r , float the_g , float the_b , float the_a , GLuint the_corner ) 
{
	int index_a=0;
	int index_b=0;
	if(the_corner==0)
	{
		index_a=0;
		index_b=3;
	}
	else if(the_corner==1)
	{
		index_a=1;
		index_b=1;
	}
	else if(the_corner==2)
	{
		index_a=2;
		index_b=4;
	}
	else if(the_corner==3)
	{
		index_a=5;
		index_b=5;
	}
	self->data[3+index_a*9]=the_r;
	self->data[4+index_a*9]=the_g;
	self->data[5+index_a*9]=the_b;
	self->data[6+index_a*9]=the_a;
	self->data[3+index_b*9]=the_r;
	self->data[4+index_b*9]=the_g;
	self->data[5+index_b*9]=the_b;
	self->data[6+index_b*9]=the_a;
}
void GLUIModel_set_texture_coord (struct GLUIModel* self, float the_x , float the_y , GLuint the_corner ) 
{
	int index_a=0;
	int index_b=0;
	if(the_corner==0)
	{
		index_a=0;
		index_b=3;
	}
	else if(the_corner==1)
	{
		index_a=1;
		index_b=1;
	}
	else if(the_corner==2)
	{
		index_a=2;
		index_b=4;
	}
	else if(the_corner==3)
	{
		index_a=5;
		index_b=5;
	}
	self->data[7+index_a*9]=the_x;
	self->data[8+index_a*9]=the_y;
	self->data[7+index_b*9]=the_x;
	self->data[8+index_b*9]=the_y;
}
void GLUIModel_set_position (struct GLUIModel* self, float the_x , float the_y , float the_z , GLuint the_corner ) 
{
	int index_a=0;
	int index_b=0;
	if(the_corner==0)
	{
		index_a=0;
		index_b=3;
	}
	else if(the_corner==1)
	{
		index_a=1;
		index_b=1;
	}
	else if(the_corner==2)
	{
		index_a=2;
		index_b=4;
	}
	else if(the_corner==3)
	{
		index_a=5;
		index_b=5;
	}
	self->data[0+index_a*9]=the_x;
	self->data[1+index_a*9]=the_y;
	self->data[2+index_a*9]=the_z;
	self->data[0+index_b*9]=the_x;
	self->data[1+index_b*9]=the_y;
	self->data[2+index_b*9]=the_z;
}
void GLUIModel_init (struct GLUIModel* self ) 
{
	self->retain_count=1;
}
void GLUIModel_retain (struct GLUIModel* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIModel_release (struct GLUIModel* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIModel_event (struct GLUIModel* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIModel_describe (struct GLUIModel* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIModelDrawer_CreateClass( )
{
	GLUIModelDrawer_ClassInstance=malloc(sizeof(struct GLUIModelDrawer_Class));
	GLUIModelDrawer_ClassInstance->className="GLUIModelDrawer";
	GLUIModelDrawer_ClassInstance->classId=&GLUIModelDrawer_ClassInstance;
	GLUIModelDrawer_ClassInstance->init=GLUIModelDrawer_init;
	GLUIModelDrawer_ClassInstance->destruct=GLUIModelDrawer_destruct;
	GLUIModelDrawer_ClassInstance->addAttribute_location_components_identifier=GLUIModelDrawer_addAttribute_location_components_identifier;
	GLUIModelDrawer_ClassInstance->get_array_for_group_level_texture_trafo=GLUIModelDrawer_get_array_for_group_level_texture_trafo;
	GLUIModelDrawer_ClassInstance->add_model_group_level_texture_trafo=GLUIModelDrawer_add_model_group_level_texture_trafo;
	GLUIModelDrawer_ClassInstance->remove_model_group_level_texture_trafo=GLUIModelDrawer_remove_model_group_level_texture_trafo;
	GLUIModelDrawer_ClassInstance->upload=GLUIModelDrawer_upload;
	GLUIModelDrawer_ClassInstance->resend=GLUIModelDrawer_resend;
	GLUIModelDrawer_ClassInstance->render=GLUIModelDrawer_render;
	GLUIModelDrawer_ClassInstance->className_CLObject="CLObject";
	GLUIModelDrawer_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIModelDrawer_ClassInstance->init_CLObject=GLUIModelDrawer_init;
	GLUIModelDrawer_ClassInstance->destruct_CLObject=GLUIModelDrawer_destruct;
	GLUIModelDrawer_ClassInstance->retain=GLUIModelDrawer_retain;
	GLUIModelDrawer_ClassInstance->release=GLUIModelDrawer_release;
	GLUIModelDrawer_ClassInstance->event=GLUIModelDrawer_event;
	GLUIModelDrawer_ClassInstance->describe=GLUIModelDrawer_describe;
	
}
struct GLUIModelDrawer* GLUIModelDrawer_alloc( )
{
	struct GLUIModelDrawer* result;
	if(GLUIModelDrawer_ClassInstance==NULL)GLUIModelDrawer_CreateClass( );
	result=malloc(sizeof(struct GLUIModelDrawer));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUIModelDrawer_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIModelDrawer_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUIModelDrawer_init (struct GLUIModelDrawer* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->needs_reload=0;
	self->arrays=CLDataList_alloc( );
	CLDataList_init(self->arrays );
	self->models_to_resend=CLDataList_alloc( );
	CLDataList_init(self->models_to_resend );
	self->trafo_location=0;
	self->notex_location=0;
	self->buffer_name=0;
	self->buffer_size=0;
	self->buffer_size_previous=0;
	self->buffer_data=NULL;
	self->attribute_stride=0;
	self->attribute_counter=0;
	self->attribute_components=malloc(sizeof(int));
	self->attribute_offset_sizes=malloc(sizeof(long));
	glGenBuffers(1,&self->buffer_name);
	#ifdef DEBUG
	gl_errors_show("GenBuffers");
	#endif
}
void GLUIModelDrawer_destruct (struct GLUIModelDrawer* self ) 
{
	CLDataList_release(self->arrays );
	CLDataList_release(self->models_to_resend );
	if(self->buffer_name!=0)glDeleteBuffers(1,&self->buffer_name);
	if(self->buffer_data!=NULL)free(self->buffer_data);
	free(self->attribute_components);
	free(self->attribute_offset_sizes);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUIModelDrawer_addAttribute_location_components_identifier (struct GLUIModelDrawer* self, int the_location , int the_component_count , const char * the_identifier ) 
{
	self->attribute_components=realloc(self->attribute_components,sizeof(int)*(self->attribute_counter+1));
	self->attribute_offset_sizes=realloc(self->attribute_offset_sizes,sizeof(long)*(self->attribute_counter+1));
	self->attribute_components[self->attribute_counter]=the_component_count;
	self->attribute_offset_sizes[self->attribute_counter]=self->attribute_stride*sizeof(GLfloat);
	self->attribute_stride+=the_component_count;
	self->attribute_counter+=1;
}
struct GLUIVertexArray * GLUIModelDrawer_get_array_for_group_level_texture_trafo (struct GLUIModelDrawer* self, GLuint the_group , GLuint the_level , GLuint the_texture , MLMatrix4 * the_trafo ) 
{
	long counter=0;
	struct GLUIVertexArray*array;
	struct GLUIVertexArray*newArray;
	struct CLLink*arrayLink=self->arrays->head;
	while(arrayLink!=NULL)
	{
		array=arrayLink->data;
		if(array->group>the_group)
		{
			newArray=GLUIVertexArray_alloc( );
			GLUIVertexArray_init(newArray, the_group,the_level,the_texture,the_trafo);
			CLDataList_add_data_at_index(self->arrays, newArray,counter);
			return newArray;
		}
		else if(array->group==the_group)
		{
			if(array->level>the_level)
			{
				newArray=GLUIVertexArray_alloc( );
				GLUIVertexArray_init(newArray, the_group,the_level,the_texture,the_trafo);
				CLDataList_add_data_at_index(self->arrays, newArray,counter);
				return newArray;
			}
			else if(array->level==the_level)
			{
				if(array->texture>the_texture)
				{
					newArray=GLUIVertexArray_alloc( );
					GLUIVertexArray_init(newArray, the_group,the_level,the_texture,the_trafo);
					CLDataList_add_data_at_index(self->arrays, newArray,counter);
					return newArray;
				}
				else if(array->texture==the_texture)
				{
					if(array->trafo==the_trafo)return array;
				}
			}
		}
		arrayLink=arrayLink->next;
		counter++;
	}
	newArray=GLUIVertexArray_alloc( );
	GLUIVertexArray_init(newArray, the_group,the_level,the_texture,the_trafo);
	CLDataList_add_data(self->arrays, newArray);
	return newArray;
}
void GLUIModelDrawer_add_model_group_level_texture_trafo (struct GLUIModelDrawer* self, struct GLUIModel * the_model , GLuint the_group , GLuint the_level , GLuint the_texture , MLMatrix4 * the_trafo ) 
{
	struct GLUIVertexArray*array=GLUIModelDrawer_get_array_for_group_level_texture_trafo( self, the_group,the_level,the_texture,the_trafo);
	if(array->models->_class->contains_data( (void*) array->models->_components[0], the_model)==0)
	{
		the_model->_class->retain( (void*) the_model->_components[0] );
		self->buffer_size+=the_model->data_size;
		array->models->_class->add_data( (void*) array->models->_components[0], the_model);
	}
	else printf("\nWARNING : DOUBLE ADDITION ATTEMPT TO MODEL DRAWER");
	self->needs_reload=1;
}
void GLUIModelDrawer_remove_model_group_level_texture_trafo (struct GLUIModelDrawer* self, struct GLUIModel * the_model , GLuint the_group , GLuint the_level , GLuint the_texture , MLMatrix4 * the_trafo ) 
{
	struct GLUIVertexArray*array=GLUIModelDrawer_get_array_for_group_level_texture_trafo( self, the_group,the_level,the_texture,the_trafo);
	char exists=array->models->_class->remove_data( (void*) array->models->_components[0], the_model);
	if(exists==1)
	{
		the_model->_class->release( (void*) the_model->_components[0] );
		self->buffer_size-=the_model->data_size;
	}
	else printf("\nWARNING : DOUBLE REMOVAL ATTEMPT FROM MODEL DRAWER");
	if(array->models->length==0)
	{
		self->arrays->_class->remove_data( (void*) self->arrays->_components[0], array);
		GLUIVertexArray_release(array );
	}
	self->needs_reload=1;
}
void GLUIModelDrawer_upload (struct GLUIModelDrawer* self ) 
{
	struct CLLink*link49;
	void* model_data;
	struct CLLink*link48;
	void* array_data;
	GLuint bufferIndex;
	GLuint vertexIndex;
	GLfloat*buffer_data_temp;
	struct GLUIModel*model;
	self->needs_reload=0;
	CLDataList_remove_all_data(self->models_to_resend );
	bufferIndex=0;
	vertexIndex=0;
	if(self->buffer_size_previous!=self->buffer_size)
	{
		if(self->buffer_data==NULL)self->buffer_data=malloc(self->buffer_size);
		else self->buffer_data=realloc(self->buffer_data,self->buffer_size);
		self->buffer_size_previous=self->buffer_size;
	}
	buffer_data_temp=self->buffer_data;
	link48=self->arrays->head;while( link48!=NULL){array_data=link48->data; 
	
		struct GLUIVertexArray*array=array_data;
		array->vertex_index=vertexIndex;
		array->vertex_count=(unsigned int)array->models->length*6;
		link49=array->models->head;while( link49!=NULL){model_data=link49->data; 
		
			model=model_data;
			model->position_in_buffer=bufferIndex;
			memcpy(buffer_data_temp,model->data,model->data_size);
			vertexIndex+=model->vertex_count;
			bufferIndex+=model->data_size;
			buffer_data_temp+=model->data_size/sizeof(GLfloat);
		link49=link49->next;}
	link48=link48->next;}
	glBindBuffer(GL_ARRAY_BUFFER,self->buffer_name);
	glBufferData(GL_ARRAY_BUFFER,self->buffer_size,self->buffer_data,GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	#ifdef DEBUG
	#endif
}
void GLUIModelDrawer_resend (struct GLUIModelDrawer* self ) 
{
	struct CLLink*link50;
	void* squareData;
	struct GLUIModel*square;
	glBindBuffer(GL_ARRAY_BUFFER,self->buffer_name);
	link50=self->models_to_resend->head;while( link50!=NULL){squareData=link50->data; 
	
		square=squareData;
		glBufferSubData(GL_ARRAY_BUFFER,square->position_in_buffer,square->data_size,square->data);
	link50=link50->next;}
	CLDataList_remove_all_data(self->models_to_resend );
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
void GLUIModelDrawer_render (struct GLUIModelDrawer* self ) 
{
	struct CLLink*link51;
	void* array_data;
	GLuint last_texture;
	long long last_trafo;
	if(self->needs_reload==1)GLUIModelDrawer_upload( self );
	if(self->models_to_resend->length>0)GLUIModelDrawer_resend( self );
	glBindBuffer(GL_ARRAY_BUFFER,self->buffer_name);
	for(int index=0;
	index<self->attribute_counter;
	index++)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,self->attribute_components[index],GL_FLOAT,GL_FALSE,self->attribute_stride*sizeof(GLfloat),(const GLvoid*)(self->attribute_offset_sizes[index]));
	}
	last_trafo=0;
	last_texture=INT_MAX;
	link51=self->arrays->head;while( link51!=NULL){array_data=link51->data; 
	
		struct GLUIVertexArray*array=array_data;
		if(last_texture!=array->texture)
		{
			glUniform1i(self->notex_location,(int)array->texture==0);
			glBindTexture(GL_TEXTURE_2D,array->texture);
			last_texture=array->texture;
		}
		if(last_trafo!=(long long)array->trafo)
		{
			GLfloat trafoa[16];
			MLMatrix4ToArray(array->trafo,trafoa);
			glUniformMatrix4fv(self->trafo_location,1,0,trafoa);
			last_trafo=(long long)array->trafo;
		}
		glDrawArrays(GL_TRIANGLES,array->vertex_index,array->vertex_count);
		#ifdef DEBUG
		gl_errors_show("DrawArrays");
		#endif
	link51=link51->next;}
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
void GLUIModelDrawer_retain (struct GLUIModelDrawer* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIModelDrawer_release (struct GLUIModelDrawer* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIModelDrawer_event (struct GLUIModelDrawer* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIModelDrawer_describe (struct GLUIModelDrawer* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIParagraph_CreateClass( )
{
	GLUIParagraph_ClassInstance=malloc(sizeof(struct GLUIParagraph_Class));
	GLUIParagraph_ClassInstance->className="GLUIParagraph";
	GLUIParagraph_ClassInstance->classId=&GLUIParagraph_ClassInstance;
	GLUIParagraph_ClassInstance->init_name_frame_font_type_align_multiline=GLUIParagraph_init_name_frame_font_type_align_multiline;
	GLUIParagraph_ClassInstance->destruct=GLUIParagraph_destruct;
	GLUIParagraph_ClassInstance->focus_on=GLUIParagraph_focus_on;
	GLUIParagraph_ClassInstance->focus_off=GLUIParagraph_focus_off;
	GLUIParagraph_ClassInstance->add_text=GLUIParagraph_add_text;
	GLUIParagraph_ClassInstance->remove_all_text=GLUIParagraph_remove_all_text;
	GLUIParagraph_ClassInstance->add_glyph=GLUIParagraph_add_glyph;
	GLUIParagraph_ClassInstance->remove_glyph=GLUIParagraph_remove_glyph;
	GLUIParagraph_ClassInstance->update_paragraph=GLUIParagraph_update_paragraph;
	GLUIParagraph_ClassInstance->update=GLUIParagraph_update;
	GLUIParagraph_ClassInstance->animate_glyphs=GLUIParagraph_animate_glyphs;
	GLUIParagraph_ClassInstance->select=GLUIParagraph_select;
	GLUIParagraph_ClassInstance->touch_began=GLUIParagraph_touch_began;
	GLUIParagraph_ClassInstance->touch_moved=GLUIParagraph_touch_moved;
	GLUIParagraph_ClassInstance->touch_ended=GLUIParagraph_touch_ended;
	GLUIParagraph_ClassInstance->key_down_characters=GLUIParagraph_key_down_characters;
	GLUIParagraph_ClassInstance->remove_dead_glyphs=GLUIParagraph_remove_dead_glyphs;
	GLUIParagraph_ClassInstance->show_gylphs_between_x1_x2=GLUIParagraph_show_gylphs_between_x1_x2;
	GLUIParagraph_ClassInstance->show_gylphs_between_y1_y2=GLUIParagraph_show_gylphs_between_y1_y2;
	GLUIParagraph_ClassInstance->className_GLUIElement="GLUIElement";
	GLUIParagraph_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	GLUIParagraph_ClassInstance->init_name_frame=GLUIParagraph_init_name_frame;
	GLUIParagraph_ClassInstance->destruct_GLUIElement=GLUIParagraph_destruct;
	GLUIParagraph_ClassInstance->set_level=GLUIParagraph_set_level;
	GLUIParagraph_ClassInstance->set_group=GLUIParagraph_set_group;
	GLUIParagraph_ClassInstance->set_texture=GLUIParagraph_set_texture;
	GLUIParagraph_ClassInstance->set_texture_coords=GLUIParagraph_set_texture_coords;
	GLUIParagraph_ClassInstance->set_color=GLUIParagraph_set_color;
	GLUIParagraph_ClassInstance->set_origo=GLUIParagraph_set_origo;
	GLUIParagraph_ClassInstance->set_extent=GLUIParagraph_set_extent;
	GLUIParagraph_ClassInstance->set_trafo=GLUIParagraph_set_trafo;
	GLUIParagraph_ClassInstance->update_GLUIElement=GLUIParagraph_update;
	GLUIParagraph_ClassInstance->update_frame=GLUIParagraph_update_frame;
	GLUIParagraph_ClassInstance->update_trafo=GLUIParagraph_update_trafo;
	GLUIParagraph_ClassInstance->get_absolute_frame=GLUIParagraph_get_absolute_frame;
	GLUIParagraph_ClassInstance->finalize_frame=GLUIParagraph_finalize_frame;
	GLUIParagraph_ClassInstance->add_element=GLUIParagraph_add_element;
	GLUIParagraph_ClassInstance->remove_element=GLUIParagraph_remove_element;
	GLUIParagraph_ClassInstance->attach=GLUIParagraph_attach;
	GLUIParagraph_ClassInstance->detach=GLUIParagraph_detach;
	GLUIParagraph_ClassInstance->get_relative_touch_line_a_line_b=GLUIParagraph_get_relative_touch_line_a_line_b;
	GLUIParagraph_ClassInstance->intersect_line_a_line_b_elements=GLUIParagraph_intersect_line_a_line_b_elements;
	GLUIParagraph_ClassInstance->touch_began_GLUIElement=GLUIParagraph_touch_began;
	GLUIParagraph_ClassInstance->touch_moved_GLUIElement=GLUIParagraph_touch_moved;
	GLUIParagraph_ClassInstance->touch_ended_GLUIElement=GLUIParagraph_touch_ended;
	GLUIParagraph_ClassInstance->key_down_characters_GLUIElement=GLUIParagraph_key_down_characters;
	GLUIParagraph_ClassInstance->key_up_characters=GLUIParagraph_key_up_characters;
	GLUIParagraph_ClassInstance->scroll_x_y=GLUIParagraph_scroll_x_y;
	GLUIParagraph_ClassInstance->focus_on_GLUIElement=GLUIParagraph_focus_on;
	GLUIParagraph_ClassInstance->focus_off_GLUIElement=GLUIParagraph_focus_off;
	GLUIParagraph_ClassInstance->className_CLObject="CLObject";
	GLUIParagraph_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIParagraph_ClassInstance->init=GLUIParagraph_init;
	GLUIParagraph_ClassInstance->destruct_CLObject=GLUIParagraph_destruct;
	GLUIParagraph_ClassInstance->retain=GLUIParagraph_retain;
	GLUIParagraph_ClassInstance->release=GLUIParagraph_release;
	GLUIParagraph_ClassInstance->event=GLUIParagraph_event;
	GLUIParagraph_ClassInstance->describe=GLUIParagraph_describe;
	
}
struct GLUIParagraph* GLUIParagraph_alloc( )
{
	struct GLUIParagraph* result;
	if(GLUIParagraph_ClassInstance==NULL)GLUIParagraph_CreateClass( );
	result=malloc(sizeof(struct GLUIParagraph));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLUIParagraph_ClassInstance->className);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(GLUIParagraph_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIParagraph_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLUIElement);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLUIParagraph_init_name_frame_font_type_align_multiline (struct GLUIParagraph* self, char * the_name , MLVector4 the_frame , struct GLFontTrueType * the_font , char the_type , char the_align , char the_multiline_flag ) 
{
	GLUIElement_init_name_frame(( cast_object( &GLUIElement_ClassInstance , self)),the_name,the_frame);
	self->text=NULL;
	self->text_length=0;
	self->type=the_type;
	self->align=the_align;
	self->multiline=the_multiline_flag;
	self->touch_delay=0;
	self->touch_began_flag=0;
	self->selection_began_flag=0;
	self->cursor=NULL;
	self->delegate=NULL;
	self->selection=NULL;
	self->end_index=0;
	self->start_index=0;
	self->glyph_a=NULL;
	self->glyph_b=NULL;
	self->font=the_font;
	GLFontTrueType_retain(self->font );
	self->glyphs=CLDataList_alloc( );
	CLDataList_init(self->glyphs );
	self->metrics=TLTextMetrics_alloc( );
	TLTextMetrics_init_type_align_lineheight_width(self->metrics, self->multiline,the_align,self->font->font_size,0);
	if(self->type==kGLUIParagraphTypeInput)self->accepts_focus=1;
	self->minimum_extent=self->extent;
	self->metrics->width=self->extent.x;
	if(self->type==kGLUIParagraphTypeInput)
	{
		self->cursor=GLUICursor_alloc( );
		GLUICursor_init_name_frame(self->cursor, "cursor",MLVector4Create(0,0,2,-self->font->font_size));
		GLUICursor_set_color(self->cursor, 0,0,0,1);
		self->cursor->accepts_mouse=0;
		self->selection=GLUIElement_alloc( );
		GLUIElement_init_name_frame(self->selection, "selection",MLVector4Create(0,0,10,-self->font->font_size));
		GLUIElement_set_color(self->selection, 0,0,0,.3);
		self->selection->accepts_mouse=0;
	}
}
void GLUIParagraph_destruct (struct GLUIParagraph* self ) 
{
	GLFontTrueType_release(self->font );
	CLDataList_release(self->glyphs );
	TLTextMetrics_release(self->metrics );
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void GLUIParagraph_focus_on (struct GLUIParagraph* self ) 
{
	printf("\nfocus off");
	if(self->cursor->parent==NULL)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
}
void GLUIParagraph_focus_off (struct GLUIParagraph* self ) 
{
	if(self->cursor->parent!=NULL)GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
}
void GLUIParagraph_add_text (struct GLUIParagraph* self, char * the_text ) 
{
	if(the_text==NULL)return;
	int codepoint;
	int utflength;
	unsigned long codelength;
	unsigned char*utfbuffer;
	unsigned long new_length=self->text_length+strlen(the_text);
	self->text=realloc(self->text,new_length);
	memcpy(self->text+self->text_length,the_text,strlen(the_text));
	self->text_length=new_length;
	utfbuffer=malloc(sizeof(char)*5);
	utflength=utf8_strlen((unsigned char*)the_text);
	for(int index=0;
	index<utflength;
	index++)
	{
		utf8_get_nth_char((unsigned char*)the_text,utfbuffer,0,NULL,0,8);
		codelength=strlen((char*)utfbuffer);
		codepoint=utf8_get_codepoint(utfbuffer,codelength);
		the_text+=codelength;
		GLUIParagraph_add_glyph( self, codepoint);
	}
	free(utfbuffer);
	GLUIParagraph_update_paragraph( self );
}
void GLUIParagraph_remove_all_text (struct GLUIParagraph* self ) 
{
	struct CLLink*link52;
	void* glyph_data;
	TLTextMetrics_remove_all_fonts(self->metrics );
	struct GLUIGlyph*one_glyph;
	link52=self->glyphs->head;while( link52!=NULL){glyph_data=link52->data; 
	
		one_glyph=glyph_data;
		if(one_glyph->parent!=NULL)GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , one_glyph)));
		GLUIGlyph_release(one_glyph );
	link52=link52->next;}
	CLDataList_remove_all_data(self->glyphs );
	self->end_index=0;
	self->start_index=0;
	self->glyph_a=NULL;
	self->glyph_b=NULL;
	self->minimum_extent=self->extent;
	self->metrics->width=self->extent.x;
	GLUIParagraph_update_paragraph( self );
}
void GLUIParagraph_add_glyph (struct GLUIParagraph* self, int the_codepoint ) 
{
	float kerning_a;
	float kerning_b;
	struct GLUIGlyph*glglyph;
	struct TLFontMetrics*font_metrics;
	GLuint glyph_texture;
	MLVector4 glyph_frame;
	MLVector4 glyph_coords;
	kerning_a=0;
	kerning_b=0;
	if(self->glyph_a!=NULL)
	{
		GLFontTrueType_kerning_for_codeA_codeB(self->font, &kerning_a,self->glyph_a->code,the_codepoint);
		self->glyph_a->kerning=kerning_a;
	}
	if(self->glyph_b!=NULL) GLFontTrueType_kerning_for_codeA_codeB(self->font, &kerning_b,the_codepoint,self->glyph_b->code);
	GLFontTrueType_texture_frame_coords_for_codepoint(self->font, &glyph_texture,&glyph_frame,&glyph_coords,the_codepoint);
	font_metrics=TLFontMetrics_alloc( );
	TLFontMetrics_init(font_metrics );
	font_metrics->code=the_codepoint;
	font_metrics->dead=0;
	font_metrics->frame=MLVector4Create(0,0,fabs(glyph_frame.z),fabs(glyph_frame.w));
	font_metrics->kerning=kerning_b;
	if(the_codepoint==13)(font_metrics->frame).z=0.0;
	if(self->start_index==self->metrics->fonts->length) TLTextMetrics_add_font(self->metrics, font_metrics);
	else TLTextMetrics_add_font_index(self->metrics, font_metrics,self->start_index);
	self->start_index++;
	char*sbuffer=malloc(sizeof(char)*50);
	sprintf(sbuffer,"GLUIGlyph %s %lu",self->name,self->glyphs->length);
	glglyph=GLUIGlyph_alloc( );
	GLUIGlyph_init_name_frame(glglyph, sbuffer,font_metrics->frame);
	glglyph->_class->set_texture( (void*) glglyph->_components[0], glyph_texture);
	GLUIGlyph_set_texture_coords(glglyph, glyph_coords);
	glglyph->accepts_mouse=0;
	glglyph->codepoint=the_codepoint;
	glglyph->metrics=font_metrics;
	glglyph->texcoords=glyph_coords;
	CLDataList_add_data(self->glyphs, glglyph);
	self->glyph_a=font_metrics;
}
void GLUIParagraph_remove_glyph (struct GLUIParagraph* self ) 
{
	if(self->metrics->fonts->length>0)
	{
		if(self->start_index>=self->metrics->fonts->length)
		{
			self->start_index=self->metrics->fonts->length;
			TLTextMetrics_remove(self->metrics );
			self->glyph_a=self->metrics->fonts->_class->last_data( (void*) self->metrics->fonts->_components[0] );
		}
		else
		{
			TLTextMetrics_remove_index(self->metrics, self->start_index-1);
			self->glyph_a=self->metrics->fonts->_class->data_at_index( (void*) self->metrics->fonts->_components[0], self->start_index-2);
		}
		self->start_index--;
		GLUIParagraph_update_paragraph( self );
	}
}
void GLUIParagraph_update_paragraph (struct GLUIParagraph* self ) 
{
	struct CLLink*link53;
	void* data;
	TLTextMetrics_update(self->metrics );
	struct GLUIGlyph*glyph;
	link53=self->glyphs->head;while( link53!=NULL){data=link53->data; 
	
		glyph=data;
		if(glyph->expanded==1)
		{
			GLUIGlyph_set_origo(glyph, MLVector3Create(roundf((glyph->metrics->frame).x),roundf(-(glyph->metrics->frame).y),0));
			GLUIGlyph_set_extent(glyph, MLVector3Create((glyph->metrics->frame).z,-(glyph->metrics->frame).w,0));
		}
		if(glyph->parent==NULL&&glyph->visible==1)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , glyph)));
	link53=link53->next;}
	if(self->type==kGLUIParagraphTypeInput)
	{
		if(self->glyph_a==NULL) GLUICursor_set_origo(self->cursor, MLVector3Create(0,0,0));
		else GLUICursor_set_origo(self->cursor, MLVector3Create((self->glyph_a->frame).x+(self->glyph_a->frame).z,-(self->glyph_a->frame).y,0));
	}
	MLVector3 new_extent=self->extent;
	if(self->metrics->width>self->minimum_extent.x)new_extent.x=self->metrics->width;
	if(self->metrics->height>-self->minimum_extent.y)new_extent.y=-self->metrics->height;
	if(self->extent.x!=new_extent.x||self->extent.y!=new_extent.y)
	{
		GLUIParagraph_set_extent( self, new_extent);
		if(self->delegate!=NULL)self->delegate->_class->event( (void*) self->delegate->_components[0], 0,self,NULL);
	}
	self->needs_redraw=1;
}
void GLUIParagraph_update (struct GLUIParagraph* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	if(self->touch_began_flag==1)
	{
		self->touch_delay+=1;
		if(self->touch_delay==30)
		{
			self->touch_delay=0;
			self->touch_began_flag=0;
			self->selection_began_flag=1;
			if(self->cursor!=NULL&&self->cursor->parent!=NULL)GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
			if(self->selection->parent==NULL)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->selection)));
			self->end_index=self->start_index;
			self->glyph_a=self->metrics->fonts->_class->data_at_index( (void*) self->metrics->fonts->_components[0], self->start_index);
			self->glyph_b=self->glyph_a;
			GLUIParagraph_select( self );
		}
	}
}
void GLUIParagraph_animate_glyphs (struct GLUIParagraph* self ) 
{
	struct CLLink*link54;
	void* data;
	struct GLUIGlyph*glyph;
	int counter=0;
	link54=self->glyphs->head;while( link54!=NULL){data=link54->data; 
	
		glyph=data;
		GLUIGlyph_animate_to_position(glyph, counter++);
		counter++;
	link54=link54->next;}
}
void GLUIParagraph_select (struct GLUIParagraph* self ) 
{
	long start=self->start_index;
	long end=self->end_index;
	if(self->end_index<self->start_index)
	{
		start=self->end_index;
		end=self->start_index;
	}
	struct TLFontMetrics*font_a=self->metrics->fonts->_class->data_at_index( (void*) self->metrics->fonts->_components[0], start);
	struct TLFontMetrics*font_b=self->metrics->fonts->_class->data_at_index( (void*) self->metrics->fonts->_components[0], end);
	if(font_b!=NULL)
	{
		GLUIElement_set_origo(self->selection, MLVector3Create((font_a->frame).x,-(font_a->frame).y,0));
		GLUIElement_set_extent(self->selection, MLVector3Create((font_b->frame).x+(font_b->frame).z-(font_a->frame).x,-self->font->font_size,0));
	}
	self->needs_redraw=1;
}
void GLUIParagraph_touch_began (struct GLUIParagraph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 touch=GLUIParagraph_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
	self->touch_began_flag=1;
	self->start_index= TLTextMetrics_glyph_index_at_x_y(self->metrics, touch.x,fabs(touch.y));
	if(self->selection_began_flag==1)
	{
		if(self->selection->parent!=NULL)GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->selection)));
		self->selection_began_flag=0;
		self->needs_redraw=1;
	}
}
void GLUIParagraph_touch_moved (struct GLUIParagraph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 touch=GLUIParagraph_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
	if(self->selection_began_flag==1)
	{
		unsigned long glyphIndex= TLTextMetrics_glyph_index_at_x_y(self->metrics, touch.x,fabs(touch.y));
		self->glyph_b=self->metrics->fonts->_class->data_at_index( (void*) self->metrics->fonts->_components[0], glyphIndex);
		self->end_index=glyphIndex;
		GLUIParagraph_select( self );
	}
}
void GLUIParagraph_touch_ended (struct GLUIParagraph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 touch=GLUIParagraph_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
	self->touch_began_flag=0;
	self->touch_delay=0;
	if(self->selection_began_flag==0)
	{
		if(self->type==kGLUIParagraphTypeInput&&self->metrics->fonts->length>0)
		{
			unsigned long glyphIndex= TLTextMetrics_glyph_index_at_x_y(self->metrics, touch.x,fabs(touch.y));
			struct TLFontMetrics*font_metrics;
			if(glyphIndex>=self->metrics->fonts->length)
			{
				self->start_index=glyphIndex;
				font_metrics=self->metrics->fonts->_class->last_data( (void*) self->metrics->fonts->_components[0] );
				GLUICursor_set_origo(self->cursor, MLVector3Create((font_metrics->frame).x+(font_metrics->frame).z,-(font_metrics->frame).y,0));
				if(self->cursor->parent==NULL)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
			}
			else
			{
				self->start_index=glyphIndex;
				font_metrics=self->metrics->fonts->_class->data_at_index( (void*) self->metrics->fonts->_components[0], glyphIndex);
				self->glyph_a=font_metrics;
				GLUICursor_set_origo(self->cursor, MLVector3Create((font_metrics->frame).x-1,-(font_metrics->frame).y,0));
				if(self->cursor->parent==NULL)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
			}
		}
	}
}
void GLUIParagraph_key_down_characters (struct GLUIParagraph* self, char * the_characters ) 
{
	if(self->type==kGLUIParagraphTypeInput)
	{
		if(self->selection->parent!=NULL)
		{
			if(self->end_index<self->start_index)
			{
				long tempIndex=self->start_index;
				self->start_index=self->end_index;
				self->end_index=tempIndex;
			}
			if(self->end_index>=self->metrics->fonts->length)self->end_index=self->metrics->fonts->length-1;
			for(int index=0;
			index<self->end_index-self->start_index+1;
			index++)self->metrics->_class->remove_index( (void*) self->metrics->_components[0], self->start_index);
			if(self->selection->parent!=NULL)GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->selection)));
			if(self->cursor->parent==NULL)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
			self->selection_began_flag=0;
			self->needs_redraw=1;
		}
		if(strlen(the_characters)==1&&the_characters[0]==127)GLUIParagraph_remove_glyph( self );
		else GLUIParagraph_add_text( self, the_characters);
		GLUIParagraph_remove_dead_glyphs( self );
	}
}
void GLUIParagraph_remove_dead_glyphs (struct GLUIParagraph* self ) 
{
	struct CLLink*link56;
	struct CLLink*link55;
	void* glyph_data;
	struct CLDataList*dead_list;
	dead_list=CLDataList_alloc( );
	CLDataList_init(dead_list );
	link55=self->glyphs->head;while( link55!=NULL){glyph_data=link55->data; 
	
		struct GLUIGlyph*glyph=glyph_data;
		if(glyph->metrics->dead==1)
		{
			GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , glyph)));
			CLDataList_add_data(dead_list, glyph);
		}
	link55=link55->next;}
	link56=dead_list->head;while( link56!=NULL){glyph_data=link56->data; 
	
		struct GLUIGlyph*glyph=glyph_data;
		CLDataList_remove_data(self->glyphs, glyph);
		GLUIGlyph_release(glyph );
	link56=link56->next;}
	CLDataList_release(dead_list );
}
void GLUIParagraph_show_gylphs_between_x1_x2 (struct GLUIParagraph* self, float the_x1 , float the_x2 ) 
{
	struct CLLink*link57;
	void* glyph_data;
	if(self->cursor!=NULL)
	{
		if((self->cursor->origo).x>the_x1&&(self->cursor->origo).x<the_x2)
		{
			if(self->cursor->parent==NULL)GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
		}
		else
		{
			if(self->cursor->parent!=NULL)GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , self->cursor)));
		}
	}
	struct GLUIGlyph*one_glyph;
	link57=self->glyphs->head;while( link57!=NULL){glyph_data=link57->data; 
	
		one_glyph=glyph_data;
		if((one_glyph->metrics->frame).x<the_x1)
		{
			if((one_glyph->metrics->frame).x+(one_glyph->metrics->frame).z>the_x1)
			{
				if(one_glyph->visible==0)
				{
					GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , one_glyph)));
					one_glyph->visible=1;
				}
				GLUIGlyph_shrink(one_glyph, (one_glyph->metrics->frame).x+(one_glyph->metrics->frame).z-the_x1,0);
			}
			else
			{
				if(one_glyph->visible==1)
				{
					GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , one_glyph)));
					one_glyph->visible=0;
				}
			}
		}
		else if((one_glyph->metrics->frame).x+(one_glyph->metrics->frame).z>the_x2)
		{
			if((one_glyph->metrics->frame).x<the_x2)
			{
				if(one_glyph->visible==0)
				{
					GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , one_glyph)));
					one_glyph->visible=1;
				}
				GLUIGlyph_shrink(one_glyph, the_x2-(one_glyph->metrics->frame).x,1);
			}
			else
			{
				if(one_glyph->visible==1)
				{
					GLUIParagraph_remove_element( self, (cast_object( &GLUIElement_ClassInstance , one_glyph)));
					one_glyph->visible=0;
				}
			}
		}
		else
		{
			if(one_glyph->visible==0)
			{
				GLUIParagraph_add_element( self, (cast_object( &GLUIElement_ClassInstance , one_glyph)));
				one_glyph->visible=1;
			}
			GLUIGlyph_expand(one_glyph );
		}
	link57=link57->next;}
}
void GLUIParagraph_show_gylphs_between_y1_y2 (struct GLUIParagraph* self, float the_y1 , float the_y2 ) 
{

}
void GLUIParagraph_init_name_frame (struct GLUIParagraph* self, char * the_name , MLVector4 the_frame ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=the_name;
	self->needs_redraw=1;
	self->accepts_mouse=0;
	self->accepts_focus=0;
	self->group=0;
	self->level=0;
	self->texture=0;
	self->origo=MLVector3Create(the_frame.x,the_frame.y,0.0);
	self->extent=MLVector3Create(the_frame.z,the_frame.w,0.0);
	self->combined_origo=self->origo;
	self->trafo=NULL;
	self->combined_trafo=NULL;
	self->model= self->model=GLUIModel_alloc( );
	self->drawer=NULL;
	self->kids= self->kids=CLDataList_alloc( );
	self->parent=NULL;
	CLDataList_init(self->kids );
	GLUIModel_init_name(self->model, self->name);
	GLUIParagraph_update_frame( self );
}
void GLUIParagraph_set_level (struct GLUIParagraph* self, int the_level ) 
{
	self->level=the_level;
}
void GLUIParagraph_set_group (struct GLUIParagraph* self, int the_group ) 
{
	self->group=the_group;
}
void GLUIParagraph_set_texture (struct GLUIParagraph* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void GLUIParagraph_set_texture_coords (struct GLUIParagraph* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void GLUIParagraph_set_color (struct GLUIParagraph* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void GLUIParagraph_set_origo (struct GLUIParagraph* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	GLUIParagraph_update_frame( self );
}
void GLUIParagraph_set_extent (struct GLUIParagraph* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	GLUIParagraph_update_frame( self );
}
void GLUIParagraph_set_trafo (struct GLUIParagraph* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)GLUIParagraph_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)GLUIParagraph_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)GLUIParagraph_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)GLUIParagraph_attach( self, one_drawer);
		}
	}
	GLUIParagraph_update_trafo( self );
}
void GLUIParagraph_update_frame (struct GLUIParagraph* self ) 
{
	struct CLLink*link58;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link58=self->kids->head;while( link58!=NULL){data=link58->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link58=link58->next;}
	}
}
void GLUIParagraph_update_trafo (struct GLUIParagraph* self ) 
{
	struct CLLink*link59;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link59=self->kids->head;while( link59!=NULL){data=link59->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link59=link59->next;}
	}
}
void GLUIParagraph_get_absolute_frame (struct GLUIParagraph* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void GLUIParagraph_finalize_frame (struct GLUIParagraph* self ) 
{
	MLVector3 a,b,c,d;
	GLUIParagraph_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void GLUIParagraph_add_element (struct GLUIParagraph* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void GLUIParagraph_remove_element (struct GLUIParagraph* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void GLUIParagraph_attach (struct GLUIParagraph* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link60;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	GLUIParagraph_update_frame( self );
	GLUIParagraph_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link60=self->kids->head;while( link60!=NULL){data=link60->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link60=link60->next;}
}
void GLUIParagraph_detach (struct GLUIParagraph* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link61;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link61=self->kids->head;while( link61!=NULL){data=link61->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link61=link61->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 GLUIParagraph_get_relative_touch_line_a_line_b (struct GLUIParagraph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	GLUIParagraph_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void GLUIParagraph_intersect_line_a_line_b_elements (struct GLUIParagraph* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link62;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=GLUIParagraph_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link62=self->kids->head;while( link62!=NULL){data=link62->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link62=link62->next;}
	}
}
void GLUIParagraph_key_up_characters (struct GLUIParagraph* self, char * the_characters ) 
{

}
void GLUIParagraph_scroll_x_y (struct GLUIParagraph* self, float the_x , float the_y ) 
{

}
void GLUIParagraph_init (struct GLUIParagraph* self ) 
{
	self->retain_count=1;
}
void GLUIParagraph_retain (struct GLUIParagraph* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIParagraph_release (struct GLUIParagraph* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIParagraph_event (struct GLUIParagraph* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIParagraph_describe (struct GLUIParagraph* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUITrafoAnimator_CreateClass( )
{
	GLUITrafoAnimator_ClassInstance=malloc(sizeof(struct GLUITrafoAnimator_Class));
	GLUITrafoAnimator_ClassInstance->className="GLUITrafoAnimator";
	GLUITrafoAnimator_ClassInstance->classId=&GLUITrafoAnimator_ClassInstance;
	GLUITrafoAnimator_ClassInstance->init=GLUITrafoAnimator_init;
	GLUITrafoAnimator_ClassInstance->destruct=GLUITrafoAnimator_destruct;
	GLUITrafoAnimator_ClassInstance->add_animation=GLUITrafoAnimator_add_animation;
	GLUITrafoAnimator_ClassInstance->remove_animation=GLUITrafoAnimator_remove_animation;
	GLUITrafoAnimator_ClassInstance->start=GLUITrafoAnimator_start;
	GLUITrafoAnimator_ClassInstance->reset=GLUITrafoAnimator_reset;
	GLUITrafoAnimator_ClassInstance->update=GLUITrafoAnimator_update;
	GLUITrafoAnimator_ClassInstance->className_CLObject="CLObject";
	GLUITrafoAnimator_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUITrafoAnimator_ClassInstance->init_CLObject=GLUITrafoAnimator_init;
	GLUITrafoAnimator_ClassInstance->destruct_CLObject=GLUITrafoAnimator_destruct;
	GLUITrafoAnimator_ClassInstance->retain=GLUITrafoAnimator_retain;
	GLUITrafoAnimator_ClassInstance->release=GLUITrafoAnimator_release;
	GLUITrafoAnimator_ClassInstance->event=GLUITrafoAnimator_event;
	GLUITrafoAnimator_ClassInstance->describe=GLUITrafoAnimator_describe;
	
}
struct GLUITrafoAnimator* GLUITrafoAnimator_alloc( )
{
	struct GLUITrafoAnimator* result;
	if(GLUITrafoAnimator_ClassInstance==NULL)GLUITrafoAnimator_CreateClass( );
	result=malloc(sizeof(struct GLUITrafoAnimator));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUITrafoAnimator_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUITrafoAnimator_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUITrafoAnimator_init (struct GLUITrafoAnimator* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->animations=CLDataList_alloc( );
	CLDataList_init(self->animations );
	self->delegate=NULL;
	self->animation=NULL;
}
void GLUITrafoAnimator_destruct (struct GLUITrafoAnimator* self ) 
{
	CLDataList_release(self->animations );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUITrafoAnimator_add_animation (struct GLUITrafoAnimator* self, struct GLUITrafoAnimation * the_animation ) 
{
	char exists= CLDataList_contains_data(self->animations, the_animation);
	if(exists==0)
	{
		the_animation->_class->retain( (void*) the_animation->_components[0] );
		CLDataList_add_data(self->animations, the_animation);
		GLUITrafoAnimator_start( self );
	}
}
void GLUITrafoAnimator_remove_animation (struct GLUITrafoAnimator* self, struct GLUITrafoAnimation * the_animation ) 
{
	char exists= CLDataList_remove_data(self->animations, the_animation);
	if(exists==1)
	{
		the_animation->_class->release( (void*) the_animation->_components[0] );
		GLUITrafoAnimator_start( self );
	}
}
void GLUITrafoAnimator_start (struct GLUITrafoAnimator* self ) 
{
	if(self->animation==NULL&&self->animations->length>0)
	{
		self->animation= CLDataList_remove_data_at_index(self->animations, 0);
	}
	else
	{
		if(self->delegate!=NULL)self->delegate->_class->event( (void*) self->delegate->_components[0], kGLUITrafoAnimatorFinished,self,NULL);
	}
}
void GLUITrafoAnimator_reset (struct GLUITrafoAnimator* self ) 
{
	struct CLLink*link63;
	void* animation_data;
	link63=self->animations->head;while( link63!=NULL){animation_data=link63->data; 
	
		struct GLUITrafoAnimation*one_animation=animation_data;
		one_animation->_class->release( (void*) one_animation->_components[0] );
	link63=link63->next;}
	self->animations->_class->remove_all_data( (void*) self->animations->_components[0] );
	if(self->animation!=NULL) GLUITrafoAnimation_release(self->animation );
	self->animation=NULL;
}
void GLUITrafoAnimator_update (struct GLUITrafoAnimator* self ) 
{
	if(self->animation!=NULL)
	{
		GLUITrafoAnimation_update(self->animation );
		if(self->animation->finished==1)
		{
			GLUITrafoAnimation_release(self->animation );
			self->animation=NULL;
			GLUITrafoAnimator_start( self );
		}
	}
}
void GLUITrafoAnimator_retain (struct GLUITrafoAnimator* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUITrafoAnimator_release (struct GLUITrafoAnimator* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUITrafoAnimator_event (struct GLUITrafoAnimator* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUITrafoAnimator_describe (struct GLUITrafoAnimator* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUITrafoAnimation_CreateClass( )
{
	GLUITrafoAnimation_ClassInstance=malloc(sizeof(struct GLUITrafoAnimation_Class));
	GLUITrafoAnimation_ClassInstance->className="GLUITrafoAnimation";
	GLUITrafoAnimation_ClassInstance->classId=&GLUITrafoAnimation_ClassInstance;
	GLUITrafoAnimation_ClassInstance->init_start_end_steps_easing=GLUITrafoAnimation_init_start_end_steps_easing;
	GLUITrafoAnimation_ClassInstance->destruct=GLUITrafoAnimation_destruct;
	GLUITrafoAnimation_ClassInstance->update=GLUITrafoAnimation_update;
	GLUITrafoAnimation_ClassInstance->className_CLObject="CLObject";
	GLUITrafoAnimation_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUITrafoAnimation_ClassInstance->init=GLUITrafoAnimation_init;
	GLUITrafoAnimation_ClassInstance->destruct_CLObject=GLUITrafoAnimation_destruct;
	GLUITrafoAnimation_ClassInstance->retain=GLUITrafoAnimation_retain;
	GLUITrafoAnimation_ClassInstance->release=GLUITrafoAnimation_release;
	GLUITrafoAnimation_ClassInstance->event=GLUITrafoAnimation_event;
	GLUITrafoAnimation_ClassInstance->describe=GLUITrafoAnimation_describe;
	
}
struct GLUITrafoAnimation* GLUITrafoAnimation_alloc( )
{
	struct GLUITrafoAnimation* result;
	if(GLUITrafoAnimation_ClassInstance==NULL)GLUITrafoAnimation_CreateClass( );
	result=malloc(sizeof(struct GLUITrafoAnimation));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUITrafoAnimation_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUITrafoAnimation_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUITrafoAnimation_init_start_end_steps_easing (struct GLUITrafoAnimation* self, struct GLUITrafo * the_start , struct GLUITrafo * the_end , int the_steps , char the_easing ) 
{
	int index,iterations;
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->easing=the_easing;
	self->finished=0;
	self->delegate=NULL;
	self->actual_steps=0;
	self->needed_steps=the_steps>0?the_steps:1;
	iterations=self->needed_steps;
	if(self->easing==kGLUIAnimationEaseIn||self->easing==kGLUIAnimationEaseOut)
	{
		iterations=0;
		for(index=0;
		index<self->needed_steps+1;
		index++)iterations+=index;
	}
	self->step=GLUITrafo_alloc( );
	GLUITrafo_init(self->step );
	self->delta=GLUITrafo_alloc( );
	GLUITrafo_init(self->delta );
	self->actual=GLUITrafo_alloc( );
	GLUITrafo_init(self->actual );
	self->actual->scale=the_start->scale;
	self->actual->rotation=the_start->rotation;
	self->actual->translation=the_start->translation;
	self->delta->scale=MLVector3Sub(the_end->scale,self->actual->scale);
	self->delta->rotation=MLVector3Sub(the_end->rotation,self->actual->rotation);
	self->delta->translation=MLVector3Sub(the_end->translation,self->actual->translation);
	self->delta->scale=MLVector3Scale(self->delta->scale,1.0/(float)iterations);
	self->delta->rotation=MLVector3Scale(self->delta->rotation,1.0/(float)iterations);
	self->delta->translation=MLVector3Scale(self->delta->translation,1.0/(float)iterations);
	self->step->scale=self->delta->scale;
	self->step->rotation=self->delta->rotation;
	self->step->translation=self->delta->translation;
	if(self->easing==kGLUIAnimationEaseIn)
	{
		self->step->scale=MLVector3Scale(self->step->scale,self->needed_steps);
		self->step->rotation=MLVector3Scale(self->step->rotation,self->needed_steps);
		self->step->translation=MLVector3Scale(self->step->translation,self->needed_steps);
	}
}
void GLUITrafoAnimation_destruct (struct GLUITrafoAnimation* self ) 
{
	GLUITrafo_release(self->step );
	GLUITrafo_release(self->delta );
	GLUITrafo_release(self->actual );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUITrafoAnimation_update (struct GLUITrafoAnimation* self ) 
{
	self->actual->scale=MLVector3Add(self->actual->scale,self->step->scale);
	self->actual->rotation=MLVector3Add(self->actual->rotation,self->step->rotation);
	self->actual->translation=MLVector3Add(self->actual->translation,self->step->translation);
	if(self->easing==kGLUIAnimationEaseOut)
	{
		self->step->scale=MLVector3Add(self->step->scale,self->delta->scale);
		self->step->rotation=MLVector3Add(self->step->rotation,self->delta->rotation);
		self->step->translation=MLVector3Add(self->step->translation,self->delta->translation);
	}
	else if(self->easing==kGLUIAnimationEaseIn)
	{
		self->step->scale=MLVector3Sub(self->step->scale,self->delta->scale);
		self->step->rotation=MLVector3Sub(self->step->rotation,self->delta->rotation);
		self->step->translation=MLVector3Sub(self->step->translation,self->delta->translation);
	}
	if(self->actual_steps==self->needed_steps)
	{
		self->finished=1;
		if(self->delegate!=NULL)self->delegate->_class->event( (void*) self->delegate->_components[0], kGLUIAnimationFinished,self,NULL);
	}
	self->actual_steps+=1;
}
void GLUITrafoAnimation_init (struct GLUITrafoAnimation* self ) 
{
	self->retain_count=1;
}
void GLUITrafoAnimation_retain (struct GLUITrafoAnimation* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUITrafoAnimation_release (struct GLUITrafoAnimation* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUITrafoAnimation_event (struct GLUITrafoAnimation* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUITrafoAnimation_describe (struct GLUITrafoAnimation* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLFontTrueType_CreateClass( )
{
	GLFontTrueType_ClassInstance=malloc(sizeof(struct GLFontTrueType_Class));
	GLFontTrueType_ClassInstance->className="GLFontTrueType";
	GLFontTrueType_ClassInstance->classId=&GLFontTrueType_ClassInstance;
	GLFontTrueType_ClassInstance->init_name_path_size_r_g_b=GLFontTrueType_init_name_path_size_r_g_b;
	GLFontTrueType_ClassInstance->destuct=GLFontTrueType_destuct;
	GLFontTrueType_ClassInstance->texture_frame_coords_for_codepoint=GLFontTrueType_texture_frame_coords_for_codepoint;
	GLFontTrueType_ClassInstance->kerning_for_codeA_codeB=GLFontTrueType_kerning_for_codeA_codeB;
	GLFontTrueType_ClassInstance->className_CLObject="CLObject";
	GLFontTrueType_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLFontTrueType_ClassInstance->init=GLFontTrueType_init;
	GLFontTrueType_ClassInstance->destruct=GLFontTrueType_destruct;
	GLFontTrueType_ClassInstance->retain=GLFontTrueType_retain;
	GLFontTrueType_ClassInstance->release=GLFontTrueType_release;
	GLFontTrueType_ClassInstance->event=GLFontTrueType_event;
	GLFontTrueType_ClassInstance->describe=GLFontTrueType_describe;
	
}
struct GLFontTrueType* GLFontTrueType_alloc( )
{
	struct GLFontTrueType* result;
	if(GLFontTrueType_ClassInstance==NULL)GLFontTrueType_CreateClass( );
	result=malloc(sizeof(struct GLFontTrueType));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLFontTrueType_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLFontTrueType_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLFontTrueType_init_name_path_size_r_g_b (struct GLFontTrueType* self, char * the_name , char * the_path , float the_size , int the_r , int the_g , int the_b ) 
{
	long size;
	FILE*font_file;
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->r=the_r;
	self->g=the_g;
	self->b=the_b;
	self->name=the_name;
	self->font_size=the_size;
	self->map=GLTextureMap_alloc( );
	GLTextureMap_init_width_height(self->map, 512,512);
	font_file=fopen(the_path,"rb");
	fseek(font_file,0,SEEK_END);
	size=ftell(font_file);
	fseek(font_file,0,SEEK_SET);
	self->font_buffer=malloc(size);
	fread(self->font_buffer,size,1,font_file);
	fclose(font_file);
	if(stbtt_InitFont(&self->font_info,self->font_buffer,stbtt_GetFontOffsetForIndex(self->font_buffer,0))==1)
	{
		stbtt_GetFontVMetrics(&self->font_info,&self->font_ascent,&self->font_descent,&self->font_gap);
		self->font_scale=stbtt_ScaleForPixelHeight(&self->font_info,self->font_size);
	}
	else printf("\nERROR : CANNOT INIT FONT");
}
void GLFontTrueType_destuct (struct GLFontTrueType* self ) 
{
	GLTextureMap_release(self->map );
	free(self->font_buffer);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
char GLFontTrueType_texture_frame_coords_for_codepoint (struct GLFontTrueType* self, GLuint * the_texture , MLVector4 * the_frame , MLVector4 * the_coords , int the_codepoint ) 
{
	int width,height,asc,x1,y1,x2,y2,diff,offset;
	char found;
	float fwidth;
	unsigned char*graymap;
	struct GLBitmapRGBA*bitmap;
	found= GLTextureMap_texture_frame_coords_for_key(self->map, the_texture,the_frame,the_coords,the_codepoint);
	if(found==0)
	{
		stbtt_GetCodepointHMetrics(&self->font_info,the_codepoint,&width,0);
		stbtt_GetCodepoint_bitmapBox(&self->font_info,the_codepoint,self->font_scale,self->font_scale,&x1,&y1,&x2,&y2);
		fwidth=(float)width*self->font_scale;
		asc=(int)roundf((float)self->font_ascent*self->font_scale);
		width=(int)roundf(fwidth);
		height=(int)roundf(self->font_size);
		if(width<(x2-x1))width=x2-x1;
		diff=(width-(x2-x1))>>1;
		offset=diff+(asc+y1)*width;
		graymap=calloc(width*height,sizeof(unsigned char*));
		stbtt_MakeCodepoint_bitmap(&self->font_info,graymap+offset,x2-x1,y2-y1,width,self->font_scale,self->font_scale,the_codepoint);
		bitmap=GLBitmapRGBAUtils_create_bitmap_map_width_height_r_g_b(NULL,graymap,width,height,self->r,self->g,self->b);
		GLTextureMap_add_bitmap_for_key(self->map, bitmap,the_codepoint);
		GLTextureMap_texture_frame_coords_for_key(self->map, the_texture,the_frame,the_coords,the_codepoint);
		GLBitmapRGBA_release(bitmap );
		free(graymap);
	}
	return 1;
}
char GLFontTrueType_kerning_for_codeA_codeB (struct GLFontTrueType* self, float * the_kerning , int the_code_a , int the_code_b ) 
{
	int kerni;
	float kernf;
	kerni=stbtt_GetCodepointKernAdvance(&self->font_info,the_code_a,the_code_b);
	kernf=(float)kerni*self->font_scale;
	*the_kerning=kernf;
	return 1;
}
void GLFontTrueType_init (struct GLFontTrueType* self ) 
{
	self->retain_count=1;
}
void GLFontTrueType_destruct (struct GLFontTrueType* self ) 
{

}
void GLFontTrueType_retain (struct GLFontTrueType* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLFontTrueType_release (struct GLFontTrueType* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLFontTrueType_event (struct GLFontTrueType* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLFontTrueType_describe (struct GLFontTrueType* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIShader_CreateClass( )
{
	GLUIShader_ClassInstance=malloc(sizeof(struct GLUIShader_Class));
	GLUIShader_ClassInstance->className="GLUIShader";
	GLUIShader_ClassInstance->classId=&GLUIShader_ClassInstance;
	GLUIShader_ClassInstance->init=GLUIShader_init;
	GLUIShader_ClassInstance->className_GLShader="GLShader";
	GLUIShader_ClassInstance->classId_GLShader=&GLShader_ClassInstance;
	GLUIShader_ClassInstance->init_name=GLUIShader_init_name;
	GLUIShader_ClassInstance->destruct=GLUIShader_destruct;
	GLUIShader_ClassInstance->add_vertex_shader_source=GLUIShader_add_vertex_shader_source;
	GLUIShader_ClassInstance->add_fragment_shader_source=GLUIShader_add_fragment_shader_source;
	GLUIShader_ClassInstance->add_attribute_identifier_location=GLUIShader_add_attribute_identifier_location;
	GLUIShader_ClassInstance->add_uniform_identifier=GLUIShader_add_uniform_identifier;
	GLUIShader_ClassInstance->attribute_location_for_identifier=GLUIShader_attribute_location_for_identifier;
	GLUIShader_ClassInstance->uniform_location_for_identifier=GLUIShader_uniform_location_for_identifier;
	GLUIShader_ClassInstance->link=GLUIShader_link;
	GLUIShader_ClassInstance->compile_shader_type_source=GLUIShader_compile_shader_type_source;
	GLUIShader_ClassInstance->link_program=GLUIShader_link_program;
	GLUIShader_ClassInstance->use=GLUIShader_use;
	GLUIShader_ClassInstance->className_CLObject="CLObject";
	GLUIShader_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIShader_ClassInstance->init_CLObject=GLUIShader_init;
	GLUIShader_ClassInstance->destruct_CLObject=GLUIShader_destruct;
	GLUIShader_ClassInstance->retain=GLUIShader_retain;
	GLUIShader_ClassInstance->release=GLUIShader_release;
	GLUIShader_ClassInstance->event=GLUIShader_event;
	GLUIShader_ClassInstance->describe=GLUIShader_describe;
	
}
struct GLUIShader* GLUIShader_alloc( )
{
	struct GLUIShader* result;
	if(GLUIShader_ClassInstance==NULL)GLUIShader_CreateClass( );
	result=malloc(sizeof(struct GLUIShader));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLUIShader_ClassInstance->className);
	result->_components_GLShader=result->_components;
	result->_class_GLShader=(void*)&(GLUIShader_ClassInstance->className_GLShader);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIShader_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLShader);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLUIShader_init (struct GLUIShader* self ) 
{
	#ifdef OSX
	const char*VERTEX="attribute   vec4 positionVector;\n""attribute   vec4 colorVector;\n""attribute   vec2 textureVector;\n""varying 	 vec2 textureVectorOut;\n""varying     vec4 colorVectorOut;\n""uniform     mat4 modelMatrix;\n""uniform     mat4 projectionMatrix;\n""void main ( )\n""{\n""gl_PointSize    = 1.0;\n""gl_Position     = modelMatrix * positionVector;\n""gl_Position     = projectionMatrix * gl_Position;\n""colorVectorOut = colorVector;\n""textureVectorOut = textureVector;\n""}\n";
	const char*FRAGMENT="varying vec2 textureVectorOut;\n""varying vec4 colorVectorOut;\n""uniform int notex;\n""uniform sampler2D texture;\n""void main ( )\n""{\n""    if ( notex == 0 ) gl_FragColor = texture2D( texture , textureVectorOut);\n""    else gl_FragColor = colorVectorOut;\n""}\n";
	#elif defined(IOS) || defined(BBY)
	const char*VERTEX_ES="attribute   vec4 positionVector;\n""attribute   vec4 colorVector;\n""attribute   vec2 textureVector;\n""varying 	 lowp vec2 textureVectorOut;\n""varying     lowp vec4 colorVectorOut;\n""uniform     mat4 modelMatrix;\n""uniform     mat4 projectionMatrix;\n""void main ( )\n""{\n""gl_PointSize    = 1.0;\n""gl_Position     = modelMatrix * positionVector;\n""gl_Position     = projectionMatrix * gl_Position;\n""colorVectorOut = colorVector;\n""textureVectorOut = textureVector;\n""}\n";
	const char*FRAGMENT_ES="varying lowp vec2 textureVectorOut;\n""varying lowp vec4 colorVectorOut;\n""uniform int notex;\n""uniform sampler2D texture;\n""void main ( )\n""{\n""    if ( notex == 0 ) gl_FragColor = texture2D( texture , textureVectorOut);\n""    else gl_FragColor = colorVectorOut;\n""}\n";
	#endif
	GLShader_init_name(( cast_object( &GLShader_ClassInstance , self)),"UI PT32");
	#ifdef OSX
	GLUIShader_add_vertex_shader_source( self, VERTEX);
	GLUIShader_add_fragment_shader_source( self, FRAGMENT);
	#elif defined(IOS) || defined(BBY)
	GLUIShader_add_vertex_shader_source( self, VERTEX_ES);
	GLUIShader_add_fragment_shader_source( self, FRAGMENT_ES);
	#else
	printf("Don't forget to set OSX, IOS, BBY macros!!!");
	#endif
	GLUIShader_add_attribute_identifier_location( self, "positionVector",0);
	GLUIShader_add_attribute_identifier_location( self, "colorVector",1);
	GLUIShader_add_attribute_identifier_location( self, "textureVector",2);
	GLUIShader_add_uniform_identifier( self, "projectionMatrix");
	GLUIShader_add_uniform_identifier( self, "modelMatrix");
	GLUIShader_add_uniform_identifier( self, "texture");
	GLUIShader_add_uniform_identifier( self, "notex");
	GLUIShader_link( self );
}
void GLUIShader_init_name (struct GLUIShader* self, char * the_name ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->uniform_counter=0;
	self->uniform_locations=malloc(sizeof(GLint));
	self->uniform_identifiers=malloc(sizeof(const char*));
	self->attribute_counter=0;
	self->attribute_locations=malloc(sizeof(GLuint));
	self->attribute_identifiers=malloc(sizeof(const char*));
	self->name=the_name;
	self->program=glCreateProgram();
	#ifdef DEBUG
	gl_errors_show("CreateProgram");
	#endif
}
void GLUIShader_destruct (struct GLUIShader* self ) 
{
	if(self->program!=0)glDeleteProgram(self->program);
	free(self->uniform_locations);
	free(self->uniform_identifiers);
	free(self->attribute_locations);
	free(self->attribute_identifiers);
	self->program=0;
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUIShader_add_vertex_shader_source (struct GLUIShader* self, const char * the_source ) 
{
	self->vertex_source=the_source;
}
void GLUIShader_add_fragment_shader_source (struct GLUIShader* self, const char * the_source ) 
{
	self->fragment_source=the_source;
}
void GLUIShader_add_attribute_identifier_location (struct GLUIShader* self, const char * the_identifier , GLuint the_location ) 
{
	self->attribute_counter+=1;
	self->attribute_locations=realloc(self->attribute_locations,sizeof(GLuint)*self->attribute_counter);
	self->attribute_identifiers=realloc(self->attribute_identifiers,sizeof(const char*)*self->attribute_counter);
	self->attribute_locations[self->attribute_counter-1]=the_location;
	self->attribute_identifiers[self->attribute_counter-1]=the_identifier;
}
void GLUIShader_add_uniform_identifier (struct GLUIShader* self, const char * the_identifier ) 
{
	self->uniform_counter+=1;
	self->uniform_locations=realloc(self->uniform_locations,sizeof(GLint)*self->uniform_counter);
	self->uniform_identifiers=realloc(self->uniform_identifiers,sizeof(const char*)*self->uniform_counter);
	self->uniform_identifiers[self->uniform_counter-1]=the_identifier;
}
GLuint GLUIShader_attribute_location_for_identifier (struct GLUIShader* self, const char * the_identifier ) 
{
	int index;
	for(index=0;
	index<self->uniform_counter;
	index++)
	{
		if(strcmp(self->attribute_identifiers[index],the_identifier)==0)return self->attribute_locations[index];
	}
	return 0;
}
GLint GLUIShader_uniform_location_for_identifier (struct GLUIShader* self, const char * the_identifier ) 
{
	int index;
	for(index=0;
	index<self->uniform_counter;
	index++)
	{
		if(strcmp(self->uniform_identifiers[index],the_identifier)==0)return self->uniform_locations[index];
	}
	return 0;
}
void GLUIShader_link (struct GLUIShader* self ) 
{
	int index;
	char success;
	success=GLUIShader_compile_shader_type_source( self, &self->vertex_shader,GL_VERTEX_SHADER,self->vertex_source);
	if(success==1)
	{
		glAttachShader(self->program,self->vertex_shader);
		#ifdef DEBUG
		gl_errors_show("AttachVertex");
		#endif
		success=GLUIShader_compile_shader_type_source( self, &self->fragment_shader,GL_FRAGMENT_SHADER,self->fragment_source);
		if(success==1)
		{
			glAttachShader(self->program,self->fragment_shader);
			#ifdef DEBUG
			gl_errors_show("AttachFragment");
			#endif
		}
		else printf("\nShader %s : Failed to compile fragment shader",self->name);
		for(index=0;
		index<self->attribute_counter;
		index++)
		{
			glBindAttribLocation(self->program,self->attribute_locations[index],self->attribute_identifiers[index]);
		}
		success=GLUIShader_link_program( self );
		if(success==1)
		{
			for(index=0;
			index<self->uniform_counter;
			index++)
			{
				self->uniform_locations[index]=glGetUniformLocation(self->program,self->uniform_identifiers[index]);
			}
		}
		else printf("\nShader %s : Failed to link program: %d",self->name,self->program);
	}
	else printf("\nShader %s : Failed to compile vertex shader",self->name);
	if(self->vertex_shader>0)
	{
		glDetachShader(self->program,self->vertex_shader);
		glDeleteShader(self->vertex_shader);
	}
	if(self->fragment_shader>0)
	{
		glDetachShader(self->program,self->fragment_shader);
		glDeleteShader(self->fragment_shader);
	}
	self->vertex_shader=0;
	self->fragment_shader=0;
}
char GLUIShader_compile_shader_type_source (struct GLUIShader* self, GLuint * the_shader , GLenum the_type , const GLchar * the_source ) 
{
	GLint status,logLength,realLength;
	GLchar*log;
	status=0;
	*the_shader=glCreateShader(the_type);
	#ifdef DEBUG
	gl_errors_show("CreateShader");
	#endif
	if(*the_shader>0)
	{
		glShaderSource(*the_shader,1,&the_source,NULL);
		#ifdef DEBUG
		gl_errors_show("ShaderSource");
		#endif
		glCompileShader(*the_shader);
		#ifdef DEBUG
		gl_errors_show("compile_shader_type_source");
		#endif
		glGetShaderiv(*the_shader,GL_INFO_LOG_LENGTH,&logLength);
		if(logLength>0)
		{
			log=(GLchar*)malloc(logLength);
			glGetShaderInfoLog(*the_shader,logLength,&realLength,log);
			printf("\nShader %s : compile log:\n%s",self->name,log);
			free(log);
		}
		glGetShaderiv(*the_shader,GL_COMPILE_STATUS,&status);
		if(status==GL_TRUE)return 1;
	}
	else printf("\nCannot create shader");
	return 0;
}
char GLUIShader_link_program (struct GLUIShader* self ) 
{
	GLint status,logLength;
	GLchar*log;
	glLinkProgram(self->program);
	#ifdef DEBUG
	gl_errors_show("LinkProgram");
	#endif
	glGetProgramiv(self->program,GL_INFO_LOG_LENGTH,&logLength);
	if(logLength>0)
	{
		log=(GLchar*)malloc(logLength);
		glGetProgramInfoLog(self->program,logLength,&logLength,log);
		printf("\nShader %s : Program link log:\n%s",self->name,log);
		free(log);
	}
	glGetProgramiv(self->program,GL_LINK_STATUS,&status);
	if(status==GL_TRUE)return 1;
	return 0;
}
void GLUIShader_use (struct GLUIShader* self ) 
{
	glUseProgram(self->program);
	#ifdef DEBUG
	gl_errors_show("UseProgram");
	#endif
}
void GLUIShader_retain (struct GLUIShader* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIShader_release (struct GLUIShader* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIShader_event (struct GLUIShader* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIShader_describe (struct GLUIShader* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void TLPixelFont_CreateClass( )
{
	TLPixelFont_ClassInstance=malloc(sizeof(struct TLPixelFont_Class));
	TLPixelFont_ClassInstance->className="TLPixelFont";
	TLPixelFont_ClassInstance->classId=&TLPixelFont_ClassInstance;
	TLPixelFont_ClassInstance->init_character=TLPixelFont_init_character;
	TLPixelFont_ClassInstance->destruct=TLPixelFont_destruct;
	TLPixelFont_ClassInstance->pattern_character=TLPixelFont_pattern_character;
	TLPixelFont_ClassInstance->className_CLObject="CLObject";
	TLPixelFont_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	TLPixelFont_ClassInstance->init=TLPixelFont_init;
	TLPixelFont_ClassInstance->destruct_CLObject=TLPixelFont_destruct;
	TLPixelFont_ClassInstance->retain=TLPixelFont_retain;
	TLPixelFont_ClassInstance->release=TLPixelFont_release;
	TLPixelFont_ClassInstance->event=TLPixelFont_event;
	TLPixelFont_ClassInstance->describe=TLPixelFont_describe;
	
}
struct TLPixelFont* TLPixelFont_alloc( )
{
	struct TLPixelFont* result;
	if(TLPixelFont_ClassInstance==NULL)TLPixelFont_CreateClass( );
	result=malloc(sizeof(struct TLPixelFont));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(TLPixelFont_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(TLPixelFont_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void TLPixelFont_init_character (struct TLPixelFont* self, char the_character ) 
{
	const char*pattern;
	const char*counter;
	int index;
	float x;
	float y;
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	pattern=TLPixelFont_pattern_character( self, the_character);
	counter=pattern;
	self->character=the_character;
	self->length=0;
	while(*counter!='\0')
	{
		if(*counter=='1')self->length+=2;
		counter+=1;
	}
	self->data=malloc(sizeof(float)*self->length);
	index=0;
	x=0.0;
	y=0.0;
	while(*pattern!='\0')
	{
		switch(*pattern)
		{
			case'1':
			{
				self->data[index++]=x;
				self->data[index++]=y;
				x+=1.0;
				break;
			}
			case'0':
			{
				x+=1.0;
				break;
			}
			case' ':
			{
				self->width=x+1;
				x=0.0;
				y+=1;
				break;
			}
		}
		self->height=y+1;
		pattern+=1;
	}
}
void TLPixelFont_destruct (struct TLPixelFont* self ) 
{
	free(self->data);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
const char * TLPixelFont_pattern_character (struct TLPixelFont* self, char the_character ) 
{
	switch(the_character)
	{
		case'A':return"000 111 101 111 101 101";
		break;
		case'B':return"000 110 101 110 101 110";
		break;
		case'C':return"000 111 100 100 100 111";
		break;
		case'D':return"000 110 101 101 101 110";
		break;
		case'E':return"000 111 100 111 100 111";
		break;
		case'F':return"000 111 100 111 100 100";
		break;
		case'G':return"000 111 100 101 101 111";
		break;
		case'H':return"000 101 101 111 101 101";
		break;
		case'I':return"0 1 1 1 1 1";
		break;
		case'J':return"000 001 001 001 101 111";
		break;
		case'K':return"000 101 101 110 101 101";
		break;
		case'L':return"000 100 100 100 100 111";
		break;
		case'M':return"00000 11111 10101 10101 10101 10101";
		break;
		case'N':return"000 111 101 101 101 101";
		break;
		case'O':return"000 111 101 101 101 111";
		break;
		case'P':return"000 111 101 111 100 100";
		break;
		case'Q':return"000 111 101 101 101 111 001";
		break;
		case'R':return"000 111 101 110 101 101";
		break;
		case'S':return"000 111 100 111 001 111";
		break;
		case'T':return"000 111 010 010 010 010";
		break;
		case'U':return"000 101 101 101 101 111";
		break;
		case'V':return"000 101 101 101 101 010";
		break;
		case'W':return"00000 10101 10101 10101 10101 11111";
		break;
		case'X':return"000 101 101 010 101 101";
		break;
		case'Y':return"000 101 101 111 010 010";
		break;
		case'Z':return"000 111 001 111 100 111";
		break;
		case'0':return"000 010 101 101 101 010";
		break;
		case'1':return"00 01 11 01 01 01";
		break;
		case'2':return"000 110 001 010 100 111";
		break;
		case'3':return"000 110 001 110 001 110";
		break;
		case'4':return"000 100 101 111 010 010";
		break;
		case'5':return"000 111 100 111 001 110";
		break;
		case'6':return"000 011 100 111 101 111";
		break;
		case'7':return"000 111 001 011 001 001";
		break;
		case'8':return"000 111 101 111 101 111";
		break;
		case'9':return"000 111 101 111 001 111";
		break;
		case'.':return"0 0 0 0 0 1";
		break;
		case'!':return"0 1 1 1 0 1";
		break;
		case'?':return"0000 0110 1001 0010 0000 0010";
		break;
		case':':return"0 0 1 0 1 0";
		break;
		case' ':return"0 0 0 0 0 0";
		break;
		case'/':return"000 001 001 010 100 100";
		break;
		case'-':return"000 000 000 111 000 000";
		break;
		case'+':return"000 000 010 111 010 000";
		break;
		case'l':return"000 001 010 100 010 001";
		break;
		case'r':return"000 100 010 001 010 100";
		break;
		case'u':return"00000 00000 00100 01010 10001 00000";
		break;
		case'd':return"00000 00000 10001 01010 00100 00000";
		break;
		case'<':return"0000 1111 1000 1000 1000 0000";
		break;
		case'>':return"0000 1111 0001 0001 0001 0000";
		break;
	}
	return"\0";
}
void TLPixelFont_init (struct TLPixelFont* self ) 
{
	self->retain_count=1;
}
void TLPixelFont_retain (struct TLPixelFont* self ) 
{
	self->retain_count=self->retain_count+1;
}
void TLPixelFont_release (struct TLPixelFont* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLPixelFont_event (struct TLPixelFont* self, int the_id , void * the_source , void * the_data ) 
{

}
void TLPixelFont_describe (struct TLPixelFont* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void TLPixelText_CreateClass( )
{
	TLPixelText_ClassInstance=malloc(sizeof(struct TLPixelText_Class));
	TLPixelText_ClassInstance->className="TLPixelText";
	TLPixelText_ClassInstance->classId=&TLPixelText_ClassInstance;
	TLPixelText_ClassInstance->init_string=TLPixelText_init_string;
	TLPixelText_ClassInstance->init_cstring=TLPixelText_init_cstring;
	TLPixelText_ClassInstance->destruct=TLPixelText_destruct;
	TLPixelText_ClassInstance->className_CLObject="CLObject";
	TLPixelText_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	TLPixelText_ClassInstance->init=TLPixelText_init;
	TLPixelText_ClassInstance->destruct_CLObject=TLPixelText_destruct;
	TLPixelText_ClassInstance->retain=TLPixelText_retain;
	TLPixelText_ClassInstance->release=TLPixelText_release;
	TLPixelText_ClassInstance->event=TLPixelText_event;
	TLPixelText_ClassInstance->describe=TLPixelText_describe;
	
}
struct TLPixelText* TLPixelText_alloc( )
{
	struct TLPixelText* result;
	if(TLPixelText_ClassInstance==NULL)TLPixelText_CreateClass( );
	result=malloc(sizeof(struct TLPixelText));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(TLPixelText_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(TLPixelText_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void TLPixelText_init_string (struct TLPixelText* self, struct CLString * the_string ) 
{
	struct CLChar*link;
	struct TLPixelFont*font;
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=0;
	self->height=0;
	self->letters=CLDataList_alloc( );
	self->letters->_class->init( (void*) self->letters->_components[0] );
	link=the_string->head;
	while(link!=NULL)
	{
		font=TLPixelFont_alloc();
		TLPixelFont_init_character(font, link->character);
		CLDataList_add_data(self->letters, font);
		self->width=self->width+font->width;
		if(self->height<font->height)self->height=font->height;
		link=link->next;
	}
}
void TLPixelText_init_cstring (struct TLPixelText* self, char * the_string ) 
{
	struct TLPixelFont*font;
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=0;
	self->height=0;
	self->letters=CLDataList_alloc( );
	self->letters->_class->init( (void*) self->letters->_components[0] );
	while(*the_string!='\0')
	{
		font=TLPixelFont_alloc();
		TLPixelFont_init_character(font, *the_string);
		CLDataList_add_data(self->letters, font);
		self->width=self->width+font->width;
		if(self->height<font->height)self->height=font->height;
		the_string+=1;
	}
}
void TLPixelText_destruct (struct TLPixelText* self ) 
{
	struct CLLink*link;
	struct TLPixelFont*font;
	link=self->letters->head;
	while(link!=NULL)
	{
		font=link->data;
		font->_class->release( (void*) font->_components[0] );
		link=link->next;
	}
	self->letters->_class->release( (void*) self->letters->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void TLPixelText_init (struct TLPixelText* self ) 
{
	self->retain_count=1;
}
void TLPixelText_retain (struct TLPixelText* self ) 
{
	self->retain_count=self->retain_count+1;
}
void TLPixelText_release (struct TLPixelText* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLPixelText_event (struct TLPixelText* self, int the_id , void * the_source , void * the_data ) 
{

}
void TLPixelText_describe (struct TLPixelText* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIVertexArray_CreateClass( )
{
	GLUIVertexArray_ClassInstance=malloc(sizeof(struct GLUIVertexArray_Class));
	GLUIVertexArray_ClassInstance->className="GLUIVertexArray";
	GLUIVertexArray_ClassInstance->classId=&GLUIVertexArray_ClassInstance;
	GLUIVertexArray_ClassInstance->init=GLUIVertexArray_init;
	GLUIVertexArray_ClassInstance->destruct=GLUIVertexArray_destruct;
	GLUIVertexArray_ClassInstance->className_CLObject="CLObject";
	GLUIVertexArray_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIVertexArray_ClassInstance->init_CLObject=GLUIVertexArray_init;
	GLUIVertexArray_ClassInstance->destruct_CLObject=GLUIVertexArray_destruct;
	GLUIVertexArray_ClassInstance->retain=GLUIVertexArray_retain;
	GLUIVertexArray_ClassInstance->release=GLUIVertexArray_release;
	GLUIVertexArray_ClassInstance->event=GLUIVertexArray_event;
	GLUIVertexArray_ClassInstance->describe=GLUIVertexArray_describe;
	
}
struct GLUIVertexArray* GLUIVertexArray_alloc( )
{
	struct GLUIVertexArray* result;
	if(GLUIVertexArray_ClassInstance==NULL)GLUIVertexArray_CreateClass( );
	result=malloc(sizeof(struct GLUIVertexArray));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLUIVertexArray_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIVertexArray_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLUIVertexArray_init (struct GLUIVertexArray* self, GLuint the_group , GLuint the_level , GLuint the_texture , MLMatrix4 * the_trafo ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->models=CLDataList_alloc( );
	CLDataList_init(self->models );
	self->group=the_group;
	self->level=the_level;
	self->trafo=the_trafo;
	self->texture=the_texture;
	self->vertex_index=0;
	self->vertex_count=0;
}
void GLUIVertexArray_destruct (struct GLUIVertexArray* self ) 
{
	CLDataList_release(self->models );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUIVertexArray_retain (struct GLUIVertexArray* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIVertexArray_release (struct GLUIVertexArray* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIVertexArray_event (struct GLUIVertexArray* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUIVertexArray_describe (struct GLUIVertexArray* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUICursor_CreateClass( )
{
	GLUICursor_ClassInstance=malloc(sizeof(struct GLUICursor_Class));
	GLUICursor_ClassInstance->className="GLUICursor";
	GLUICursor_ClassInstance->classId=&GLUICursor_ClassInstance;
	GLUICursor_ClassInstance->init_name_frame=GLUICursor_init_name_frame;
	GLUICursor_ClassInstance->update=GLUICursor_update;
	GLUICursor_ClassInstance->className_GLUIElement="GLUIElement";
	GLUICursor_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	GLUICursor_ClassInstance->init_name_frame_GLUIElement=GLUICursor_init_name_frame;
	GLUICursor_ClassInstance->destruct=GLUICursor_destruct;
	GLUICursor_ClassInstance->set_level=GLUICursor_set_level;
	GLUICursor_ClassInstance->set_group=GLUICursor_set_group;
	GLUICursor_ClassInstance->set_texture=GLUICursor_set_texture;
	GLUICursor_ClassInstance->set_texture_coords=GLUICursor_set_texture_coords;
	GLUICursor_ClassInstance->set_color=GLUICursor_set_color;
	GLUICursor_ClassInstance->set_origo=GLUICursor_set_origo;
	GLUICursor_ClassInstance->set_extent=GLUICursor_set_extent;
	GLUICursor_ClassInstance->set_trafo=GLUICursor_set_trafo;
	GLUICursor_ClassInstance->update_GLUIElement=GLUICursor_update;
	GLUICursor_ClassInstance->update_frame=GLUICursor_update_frame;
	GLUICursor_ClassInstance->update_trafo=GLUICursor_update_trafo;
	GLUICursor_ClassInstance->get_absolute_frame=GLUICursor_get_absolute_frame;
	GLUICursor_ClassInstance->finalize_frame=GLUICursor_finalize_frame;
	GLUICursor_ClassInstance->add_element=GLUICursor_add_element;
	GLUICursor_ClassInstance->remove_element=GLUICursor_remove_element;
	GLUICursor_ClassInstance->attach=GLUICursor_attach;
	GLUICursor_ClassInstance->detach=GLUICursor_detach;
	GLUICursor_ClassInstance->get_relative_touch_line_a_line_b=GLUICursor_get_relative_touch_line_a_line_b;
	GLUICursor_ClassInstance->intersect_line_a_line_b_elements=GLUICursor_intersect_line_a_line_b_elements;
	GLUICursor_ClassInstance->touch_began=GLUICursor_touch_began;
	GLUICursor_ClassInstance->touch_moved=GLUICursor_touch_moved;
	GLUICursor_ClassInstance->touch_ended=GLUICursor_touch_ended;
	GLUICursor_ClassInstance->key_down_characters=GLUICursor_key_down_characters;
	GLUICursor_ClassInstance->key_up_characters=GLUICursor_key_up_characters;
	GLUICursor_ClassInstance->scroll_x_y=GLUICursor_scroll_x_y;
	GLUICursor_ClassInstance->focus_on=GLUICursor_focus_on;
	GLUICursor_ClassInstance->focus_off=GLUICursor_focus_off;
	GLUICursor_ClassInstance->className_CLObject="CLObject";
	GLUICursor_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUICursor_ClassInstance->init=GLUICursor_init;
	GLUICursor_ClassInstance->destruct_CLObject=GLUICursor_destruct;
	GLUICursor_ClassInstance->retain=GLUICursor_retain;
	GLUICursor_ClassInstance->release=GLUICursor_release;
	GLUICursor_ClassInstance->event=GLUICursor_event;
	GLUICursor_ClassInstance->describe=GLUICursor_describe;
	
}
struct GLUICursor* GLUICursor_alloc( )
{
	struct GLUICursor* result;
	if(GLUICursor_ClassInstance==NULL)GLUICursor_CreateClass( );
	result=malloc(sizeof(struct GLUICursor));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLUICursor_ClassInstance->className);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(GLUICursor_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUICursor_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLUIElement);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLUICursor_init_name_frame (struct GLUICursor* self, char * the_name , MLVector4 the_frame ) 
{
	GLUIElement_init_name_frame(( cast_object( &GLUIElement_ClassInstance , self)),the_name,the_frame);
	self->counter=0;
}
void GLUICursor_update (struct GLUICursor* self ) 
{
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
	self->counter++;
	if(self->counter<20)
	{
		GLUICursor_set_color( self, 0.0,0.0,0.0,(float)self->counter/20.0);
		self->needs_redraw=1;
		if(self->drawer!=NULL)self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
	}
	else if(self->counter<41)
	{
		GLUICursor_set_color( self, 0.0,0.0,0.0,1.0-((float)(self->counter-20)/20.0));
		self->needs_redraw=1;
		if(self->drawer!=NULL)self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
	}
	else if(self->counter<60)
	{
	}
	else if(self->counter==60)self->counter=0;
}
void GLUICursor_destruct (struct GLUICursor* self ) 
{
	CLDataList_release(self->kids );
	GLUIModel_release(self->model );
	frame:GLUICursor_release( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLUICursor_set_level (struct GLUICursor* self, int the_level ) 
{
	self->level=the_level;
}
void GLUICursor_set_group (struct GLUICursor* self, int the_group ) 
{
	self->group=the_group;
}
void GLUICursor_set_texture (struct GLUICursor* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void GLUICursor_set_texture_coords (struct GLUICursor* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void GLUICursor_set_color (struct GLUICursor* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void GLUICursor_set_origo (struct GLUICursor* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	GLUICursor_update_frame( self );
}
void GLUICursor_set_extent (struct GLUICursor* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	GLUICursor_update_frame( self );
}
void GLUICursor_set_trafo (struct GLUICursor* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)GLUICursor_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)GLUICursor_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)GLUICursor_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)GLUICursor_attach( self, one_drawer);
		}
	}
	GLUICursor_update_trafo( self );
}
void GLUICursor_update_frame (struct GLUICursor* self ) 
{
	struct CLLink*link64;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link64=self->kids->head;while( link64!=NULL){data=link64->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link64=link64->next;}
	}
}
void GLUICursor_update_trafo (struct GLUICursor* self ) 
{
	struct CLLink*link65;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link65=self->kids->head;while( link65!=NULL){data=link65->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link65=link65->next;}
	}
}
void GLUICursor_get_absolute_frame (struct GLUICursor* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void GLUICursor_finalize_frame (struct GLUICursor* self ) 
{
	MLVector3 a,b,c,d;
	GLUICursor_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void GLUICursor_add_element (struct GLUICursor* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void GLUICursor_remove_element (struct GLUICursor* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void GLUICursor_attach (struct GLUICursor* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link66;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	GLUICursor_update_frame( self );
	GLUICursor_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link66=self->kids->head;while( link66!=NULL){data=link66->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link66=link66->next;}
}
void GLUICursor_detach (struct GLUICursor* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link67;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link67=self->kids->head;while( link67!=NULL){data=link67->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link67=link67->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 GLUICursor_get_relative_touch_line_a_line_b (struct GLUICursor* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	GLUICursor_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void GLUICursor_intersect_line_a_line_b_elements (struct GLUICursor* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link68;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=GLUICursor_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link68=self->kids->head;while( link68!=NULL){data=link68->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link68=link68->next;}
	}
}
void GLUICursor_touch_began (struct GLUICursor* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUICursor_touch_moved (struct GLUICursor* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUICursor_touch_ended (struct GLUICursor* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUICursor_key_down_characters (struct GLUICursor* self, char * the_characters ) 
{

}
void GLUICursor_key_up_characters (struct GLUICursor* self, char * the_characters ) 
{

}
void GLUICursor_scroll_x_y (struct GLUICursor* self, float the_x , float the_y ) 
{

}
void GLUICursor_focus_on (struct GLUICursor* self ) 
{

}
void GLUICursor_focus_off (struct GLUICursor* self ) 
{

}
void GLUICursor_init (struct GLUICursor* self ) 
{
	self->retain_count=1;
}
void GLUICursor_retain (struct GLUICursor* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUICursor_release (struct GLUICursor* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUICursor_event (struct GLUICursor* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLUICursor_describe (struct GLUICursor* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLUIGlyph_CreateClass( )
{
	GLUIGlyph_ClassInstance=malloc(sizeof(struct GLUIGlyph_Class));
	GLUIGlyph_ClassInstance->className="GLUIGlyph";
	GLUIGlyph_ClassInstance->classId=&GLUIGlyph_ClassInstance;
	GLUIGlyph_ClassInstance->init_name_frame=GLUIGlyph_init_name_frame;
	GLUIGlyph_ClassInstance->destruct=GLUIGlyph_destruct;
	GLUIGlyph_ClassInstance->shrink=GLUIGlyph_shrink;
	GLUIGlyph_ClassInstance->expand=GLUIGlyph_expand;
	GLUIGlyph_ClassInstance->animate_to_position=GLUIGlyph_animate_to_position;
	GLUIGlyph_ClassInstance->update=GLUIGlyph_update;
	GLUIGlyph_ClassInstance->event=GLUIGlyph_event;
	GLUIGlyph_ClassInstance->className_GLUIElement="GLUIElement";
	GLUIGlyph_ClassInstance->classId_GLUIElement=&GLUIElement_ClassInstance;
	GLUIGlyph_ClassInstance->init_name_frame_GLUIElement=GLUIGlyph_init_name_frame;
	GLUIGlyph_ClassInstance->destruct_GLUIElement=GLUIGlyph_destruct;
	GLUIGlyph_ClassInstance->set_level=GLUIGlyph_set_level;
	GLUIGlyph_ClassInstance->set_group=GLUIGlyph_set_group;
	GLUIGlyph_ClassInstance->set_texture=GLUIGlyph_set_texture;
	GLUIGlyph_ClassInstance->set_texture_coords=GLUIGlyph_set_texture_coords;
	GLUIGlyph_ClassInstance->set_color=GLUIGlyph_set_color;
	GLUIGlyph_ClassInstance->set_origo=GLUIGlyph_set_origo;
	GLUIGlyph_ClassInstance->set_extent=GLUIGlyph_set_extent;
	GLUIGlyph_ClassInstance->set_trafo=GLUIGlyph_set_trafo;
	GLUIGlyph_ClassInstance->update_GLUIElement=GLUIGlyph_update;
	GLUIGlyph_ClassInstance->update_frame=GLUIGlyph_update_frame;
	GLUIGlyph_ClassInstance->update_trafo=GLUIGlyph_update_trafo;
	GLUIGlyph_ClassInstance->get_absolute_frame=GLUIGlyph_get_absolute_frame;
	GLUIGlyph_ClassInstance->finalize_frame=GLUIGlyph_finalize_frame;
	GLUIGlyph_ClassInstance->add_element=GLUIGlyph_add_element;
	GLUIGlyph_ClassInstance->remove_element=GLUIGlyph_remove_element;
	GLUIGlyph_ClassInstance->attach=GLUIGlyph_attach;
	GLUIGlyph_ClassInstance->detach=GLUIGlyph_detach;
	GLUIGlyph_ClassInstance->get_relative_touch_line_a_line_b=GLUIGlyph_get_relative_touch_line_a_line_b;
	GLUIGlyph_ClassInstance->intersect_line_a_line_b_elements=GLUIGlyph_intersect_line_a_line_b_elements;
	GLUIGlyph_ClassInstance->touch_began=GLUIGlyph_touch_began;
	GLUIGlyph_ClassInstance->touch_moved=GLUIGlyph_touch_moved;
	GLUIGlyph_ClassInstance->touch_ended=GLUIGlyph_touch_ended;
	GLUIGlyph_ClassInstance->key_down_characters=GLUIGlyph_key_down_characters;
	GLUIGlyph_ClassInstance->key_up_characters=GLUIGlyph_key_up_characters;
	GLUIGlyph_ClassInstance->scroll_x_y=GLUIGlyph_scroll_x_y;
	GLUIGlyph_ClassInstance->focus_on=GLUIGlyph_focus_on;
	GLUIGlyph_ClassInstance->focus_off=GLUIGlyph_focus_off;
	GLUIGlyph_ClassInstance->className_CLObject="CLObject";
	GLUIGlyph_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLUIGlyph_ClassInstance->init=GLUIGlyph_init;
	GLUIGlyph_ClassInstance->destruct_CLObject=GLUIGlyph_destruct;
	GLUIGlyph_ClassInstance->retain=GLUIGlyph_retain;
	GLUIGlyph_ClassInstance->release=GLUIGlyph_release;
	GLUIGlyph_ClassInstance->event_CLObject=GLUIGlyph_event;
	GLUIGlyph_ClassInstance->describe=GLUIGlyph_describe;
	
}
struct GLUIGlyph* GLUIGlyph_alloc( )
{
	struct GLUIGlyph* result;
	if(GLUIGlyph_ClassInstance==NULL)GLUIGlyph_CreateClass( );
	result=malloc(sizeof(struct GLUIGlyph));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLUIGlyph_ClassInstance->className);
	result->_components_GLUIElement=result->_components;
	result->_class_GLUIElement=(void*)&(GLUIGlyph_ClassInstance->className_GLUIElement);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLUIGlyph_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLUIElement);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLUIGlyph_init_name_frame (struct GLUIGlyph* self, char * the_name , MLVector4 the_frame ) 
{
	GLUIElement_init_name_frame(( cast_object( &GLUIElement_ClassInstance , self)),the_name,the_frame);
	self->visible=1;
	self->animated=0;
	self->expanded=1;
	self->animator=GLUITrafoAnimator_alloc( );
	GLUITrafoAnimator_init(self->animator );
	self->animator->delegate=(cast_object( &CLObject_ClassInstance , self));
}
void GLUIGlyph_destruct (struct GLUIGlyph* self ) 
{
	GLUITrafoAnimator_release(self->animator );
	GLUIElement_destruct(( cast_object( &GLUIElement_ClassInstance , self)));
}
void GLUIGlyph_shrink (struct GLUIGlyph* self, float the_size , char the_side ) 
{
	float tex_dx;
	self->expanded=0;
	if(the_size>0)
	{
		tex_dx=self->texcoords.z-self->texcoords.x;
		tex_dx*=the_size/(self->metrics->frame).z;
		if(the_side==0)
		{
			GLUIGlyph_set_origo( self, MLVector3Create((self->metrics->frame).x+(self->metrics->frame).z-the_size,-(self->metrics->frame).y,0));
			GLUIGlyph_set_extent( self, MLVector3Create(the_size,-(self->metrics->frame).w,0));
			GLUIGlyph_set_texture_coords( self, MLVector4Create(self->texcoords.z-tex_dx,self->texcoords.y,self->texcoords.z,self->texcoords.w));
		}
		else
		{
			GLUIGlyph_set_extent( self, MLVector3Create(the_size,-(self->metrics->frame).w,0));
			GLUIGlyph_set_texture_coords( self, MLVector4Create(self->texcoords.x,self->texcoords.y,self->texcoords.x+tex_dx,self->texcoords.w));
		}
	}
}
void GLUIGlyph_expand (struct GLUIGlyph* self ) 
{
	if(self->expanded==0)
	{
		self->expanded=1;
		GLUIGlyph_set_origo( self, MLVector3Create(roundf((self->metrics->frame).x),roundf(-(self->metrics->frame).y),0));
		GLUIGlyph_set_extent( self, MLVector3Create((self->metrics->frame).z,-(self->metrics->frame).w,0));
		GLUIGlyph_set_texture_coords( self, self->texcoords);
	}
}
void GLUIGlyph_animate_to_position (struct GLUIGlyph* self, int the_steps ) 
{
	if(self->animated==0)
	{
		self->animated=1;
		struct GLUITrafoAnimation*animation;
		struct GLUITrafo*old_trafo;
		struct GLUITrafo*new_trafo;
		old_trafo=GLUITrafo_alloc( );
		GLUITrafo_init(old_trafo );
		(old_trafo->scale).x=2.0;
		(old_trafo->scale).y=2.0;
		(old_trafo->translation).z=1000.0;
		new_trafo=GLUITrafo_alloc( );
		GLUITrafo_init(new_trafo );
		animation=GLUITrafoAnimation_alloc( );
		GLUITrafoAnimation_init_start_end_steps_easing(animation, old_trafo,old_trafo,the_steps,1);
		GLUITrafoAnimator_add_animation(self->animator, animation);
		GLUITrafoAnimation_release(animation );
		animation=GLUITrafoAnimation_alloc( );
		GLUITrafoAnimation_init_start_end_steps_easing(animation, old_trafo,new_trafo,50,1);
		GLUITrafoAnimator_add_animation(self->animator, animation);
		GLUITrafoAnimation_release(animation );
		GLUIGlyph_set_trafo( self, GLUITrafo_matrix(old_trafo ),0);
		GLUITrafo_release(old_trafo );
		GLUITrafo_release(new_trafo );
	}
}
void GLUIGlyph_update (struct GLUIGlyph* self ) 
{
	if(self->animator->animation!=NULL)
	{
		self->needs_redraw=1;
		MLMatrix4 new_trafo=MLMatrix4CreateIdentity();
		new_trafo=MLMatrix4Translate(new_trafo,self->combined_origo.x+self->extent.x/2,self->combined_origo.y+self->extent.y/2,0);
		new_trafo=MLMatrix4Multiply(new_trafo,self->animator->animation->actual->_class->matrix( (void*) self->animator->animation->actual->_components[0] ));
		new_trafo=MLMatrix4Translate(new_trafo,-self->combined_origo.x-self->extent.x/2,-self->combined_origo.y-self->extent.y/2,0);
		GLUIGlyph_set_trafo( self, new_trafo,0);
		GLUITrafoAnimator_update(self->animator );
	}
	GLUIElement_update(( cast_object( &GLUIElement_ClassInstance , self)));
}
void GLUIGlyph_event (struct GLUIGlyph* self, int the_id , void * the_source , void * the_data ) 
{
	if(the_id==kGLUITrafoAnimatorFinished)
	{
		self->animated=0;
		GLUIGlyph_set_trafo( self, MLMatrix4CreateIdentity(),1);
	}
}
void GLUIGlyph_set_level (struct GLUIGlyph* self, int the_level ) 
{
	self->level=the_level;
}
void GLUIGlyph_set_group (struct GLUIGlyph* self, int the_group ) 
{
	self->group=the_group;
}
void GLUIGlyph_set_texture (struct GLUIGlyph* self, GLuint the_texture ) 
{
	self->texture=the_texture;
}
void GLUIGlyph_set_texture_coords (struct GLUIGlyph* self, MLVector4 theCoords ) 
{
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.y,0);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.x,theCoords.w,1);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.w,2);
	self->model->_class->set_texture_coord( (void*) self->model->_components[0], theCoords.z,theCoords.y,3);
}
void GLUIGlyph_set_color (struct GLUIGlyph* self, float the_r , float the_g , float the_b , float theA ) 
{
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,0);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,1);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,2);
	GLUIModel_set_color(self->model, the_r,the_g,the_b,theA,3);
}
void GLUIGlyph_set_origo (struct GLUIGlyph* self, MLVector3 the_origo ) 
{
	self->origo=the_origo;
	GLUIGlyph_update_frame( self );
}
void GLUIGlyph_set_extent (struct GLUIGlyph* self, MLVector3 the_extent ) 
{
	self->extent=the_extent;
	GLUIGlyph_update_frame( self );
}
void GLUIGlyph_set_trafo (struct GLUIGlyph* self, MLMatrix4 the_trafo , char the_identity_flag ) 
{
	struct GLUIModelDrawer*one_drawer=self->drawer;
	if(the_identity_flag==0)
	{
		if(self->trafo==NULL)
		{
			if(one_drawer!=NULL)GLUIGlyph_detach( self, one_drawer);
			self->trafo=malloc(sizeof(MLMatrix4));
			self->combined_trafo=malloc(sizeof(MLMatrix4));
			if(one_drawer!=NULL)GLUIGlyph_attach( self, one_drawer);
		}
		*self->trafo=the_trafo;
		*self->combined_trafo=the_trafo;
	}
	else
	{
		if(self->trafo!=NULL)
		{
			if(one_drawer!=NULL)GLUIGlyph_detach( self, one_drawer);
			free(self->trafo);
			free(self->combined_trafo);
			self->trafo=NULL;
			if(self->parent!=NULL)self->combined_trafo=self->parent->combined_trafo;
			if(one_drawer!=NULL)GLUIGlyph_attach( self, one_drawer);
		}
	}
	GLUIGlyph_update_trafo( self );
}
void GLUIGlyph_update_frame (struct GLUIGlyph* self ) 
{
	struct CLLink*link69;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL)self->combined_origo=MLVector3Add(self->parent->combined_origo,self->origo);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y,0.0,0);
	GLUIModel_set_position(self->model, self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,2);
	GLUIModel_set_position(self->model, self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,3);
	if(self->drawer!=NULL)
	{
		self->drawer->models_to_resend->_class->add_data( (void*) self->drawer->models_to_resend->_components[0], self->model);
		link69=self->kids->head;while( link69!=NULL){data=link69->data; 
		
			one_element=data;
			one_element->_class->update_frame( (void*) one_element->_components[0] );
		link69=link69->next;}
	}
}
void GLUIGlyph_update_trafo (struct GLUIGlyph* self ) 
{
	struct CLLink*link70;
	void* data;
	struct GLUIElement*one_element;
	if(self->parent!=NULL&&self->parent->combined_trafo!=NULL)
	{
		if(self->trafo==NULL)self->combined_trafo=self->parent->combined_trafo;
		else*self->combined_trafo=MLMatrix4Multiply(*(self->parent->combined_trafo),*self->trafo);
	}
	if(self->drawer!=NULL)
	{
		link70=self->kids->head;while( link70!=NULL){data=link70->data; 
		
			one_element=data;
			one_element->_class->update_trafo( (void*) one_element->_components[0] );
		link70=link70->next;}
	}
}
void GLUIGlyph_get_absolute_frame (struct GLUIGlyph* self, MLVector3 * the_a , MLVector3 * the_b , MLVector3 * the_c , MLVector3 * the_d ) 
{
	MLVector4 a,b,c,d;
	a=MLVector4Create(self->combined_origo.x,self->combined_origo.y,0.0,1);
	b=MLVector4Create(self->combined_origo.x,self->combined_origo.y+self->extent.y,0.0,1);
	c=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y+self->extent.y,0.0,1);
	d=MLVector4Create(self->combined_origo.x+self->extent.x,self->combined_origo.y,0.0,1);
	if(self->combined_trafo!=NULL)
	{
		a=MLMatrix4MultiplyVector4(*self->combined_trafo,a);
		b=MLMatrix4MultiplyVector4(*self->combined_trafo,b);
		c=MLMatrix4MultiplyVector4(*self->combined_trafo,c);
		d=MLMatrix4MultiplyVector4(*self->combined_trafo,d);
	}
	*the_a=MLVector3Create(a.x,a.y,a.z);
	*the_b=MLVector3Create(b.x,b.y,b.z);
	*the_c=MLVector3Create(c.x,c.y,c.z);
	*the_d=MLVector3Create(d.x,d.y,d.z);
}
void GLUIGlyph_finalize_frame (struct GLUIGlyph* self ) 
{
	MLVector3 a,b,c,d;
	GLUIGlyph_get_absolute_frame( self, &a,&b,&c,&d);
	GLUIModel_set_position(self->model, a.x,a.y,0.0,0);
	GLUIModel_set_position(self->model, b.x,b.y,0.0,1);
	GLUIModel_set_position(self->model, c.x,c.y,0.0,2);
	GLUIModel_set_position(self->model, d.x,d.y,0.0,3);
}
void GLUIGlyph_add_element (struct GLUIGlyph* self, struct GLUIElement * the_element ) 
{
	char exists=self->kids->_class->contains_data( (void*) self->kids->_components[0], the_element);
	if(exists==0)
	{
		the_element->parent=(cast_object( &GLUIElement_ClassInstance , self));
		if(self->drawer!=NULL)the_element->_class->attach( (void*) the_element->_components[0], self->drawer);
		CLDataList_add_data(self->kids, the_element);
		self->needs_redraw=1;
	}
}
void GLUIGlyph_remove_element (struct GLUIGlyph* self, struct GLUIElement * the_element ) 
{
	char exists= CLDataList_remove_data(self->kids, the_element);
	if(exists==1)
	{
		if(self->drawer!=NULL)the_element->_class->detach( (void*) the_element->_components[0], self->drawer);
		the_element->parent=NULL;
		self->needs_redraw=1;
	}
}
void GLUIGlyph_attach (struct GLUIGlyph* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link71;
	void* data;
	if(self->group==0)self->group=self->parent->group;
	self->level=self->parent->level+self->level;
	GLUIGlyph_update_frame( self );
	GLUIGlyph_update_trafo( self );
	self->drawer=the_drawer;
	GLUIModelDrawer_add_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	struct GLUIElement*one_element;
	link71=self->kids->head;while( link71!=NULL){data=link71->data; 
	
		one_element=data;
		one_element->_class->attach( (void*) one_element->_components[0], self->drawer);
	link71=link71->next;}
}
void GLUIGlyph_detach (struct GLUIGlyph* self, struct GLUIModelDrawer * the_drawer ) 
{
	struct CLLink*link72;
	void* data;
	if(self->parent==NULL||self->drawer==NULL)printf("\ndetach MALFUNCTION, already detached");
	struct GLUIElement*one_element;
	link72=self->kids->head;while( link72!=NULL){data=link72->data; 
	
		one_element=data;
		one_element->_class->detach( (void*) one_element->_components[0], self->drawer);
	link72=link72->next;}
	GLUIModelDrawer_remove_model_group_level_texture_trafo(self->drawer, self->model,self->group,self->level,self->texture,self->combined_trafo);
	self->drawer=NULL;
	self->level-=self->parent->level;
	self->group=0;
}
MLVector3 GLUIGlyph_get_relative_touch_line_a_line_b (struct GLUIGlyph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{
	MLVector3 plane_a,plane_b,plane_c,plane_d,vector_ab,vector_ad,vector_n,vector_ai,point_is;
	GLUIGlyph_get_absolute_frame( self, &plane_a,&plane_b,&plane_c,&plane_d);
	vector_ab=MLVector3Sub(plane_b,plane_a);
	vector_ad=MLVector3Sub(plane_d,plane_a);
	vector_n=MLVector3Cross(vector_ab,vector_ad);
	point_is=MLVector3IntersectWithPlane(the_line_a,the_line_b,plane_a,vector_n);
	vector_ai=MLVector3Sub(point_is,plane_a);
	float angle_ab_ai=MLVector3Angle(vector_ab,vector_ai);
	float angle_ad_ai=MLVector3Angle(vector_ad,vector_ai);
	float length_vector_ai=MLVector3Length(vector_ai);
	MLVector3 one_touch;
	one_touch.x=cos(angle_ad_ai)*length_vector_ai;
	one_touch.y=-sin(angle_ad_ai)*length_vector_ai;
	one_touch.z=0.0;
	if(angle_ab_ai>M_PI/2&&angle_ad_ai>M_PI/2)one_touch.y*=-1;
	else if(angle_ab_ai>M_PI/2&&angle_ad_ai<M_PI/2)one_touch.y*=-1;
	return one_touch;
}
void GLUIGlyph_intersect_line_a_line_b_elements (struct GLUIGlyph* self, MLVector3 the_line_a , MLVector3 the_line_b , struct CLDataList * elements ) 
{
	struct CLLink*link73;
	void* data;
	char found;
	struct GLUIElement*one_element;
	found=0;
	if(self->accepts_mouse==1)
	{
		MLVector3 one_touch=GLUIGlyph_get_relative_touch_line_a_line_b( self, the_line_a,the_line_b);
		if(one_touch.x>0&&one_touch.x<=self->extent.x&&one_touch.y<0&&one_touch.y>=self->extent.y)
		{
			CLDataList_add_data(elements, (cast_object( &GLUIElement_ClassInstance , self)));
			found=1;
		}
	}
	else found=1;
	if(found==1)
	{
		link73=self->kids->head;while( link73!=NULL){data=link73->data; 
		
			one_element=data;
			one_element->_class->intersect_line_a_line_b_elements( (void*) one_element->_components[0], the_line_a,the_line_b,elements);
		link73=link73->next;}
	}
}
void GLUIGlyph_touch_began (struct GLUIGlyph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIGlyph_touch_moved (struct GLUIGlyph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIGlyph_touch_ended (struct GLUIGlyph* self, MLVector3 the_line_a , MLVector3 the_line_b ) 
{

}
void GLUIGlyph_key_down_characters (struct GLUIGlyph* self, char * the_characters ) 
{

}
void GLUIGlyph_key_up_characters (struct GLUIGlyph* self, char * the_characters ) 
{

}
void GLUIGlyph_scroll_x_y (struct GLUIGlyph* self, float the_x , float the_y ) 
{

}
void GLUIGlyph_focus_on (struct GLUIGlyph* self ) 
{

}
void GLUIGlyph_focus_off (struct GLUIGlyph* self ) 
{

}
void GLUIGlyph_init (struct GLUIGlyph* self ) 
{
	self->retain_count=1;
}
void GLUIGlyph_retain (struct GLUIGlyph* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLUIGlyph_release (struct GLUIGlyph* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLUIGlyph_describe (struct GLUIGlyph* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void TLTextMetrics_CreateClass( )
{
	TLTextMetrics_ClassInstance=malloc(sizeof(struct TLTextMetrics_Class));
	TLTextMetrics_ClassInstance->className="TLTextMetrics";
	TLTextMetrics_ClassInstance->classId=&TLTextMetrics_ClassInstance;
	TLTextMetrics_ClassInstance->init_type_align_lineheight_width=TLTextMetrics_init_type_align_lineheight_width;
	TLTextMetrics_ClassInstance->destruct=TLTextMetrics_destruct;
	TLTextMetrics_ClassInstance->add_font=TLTextMetrics_add_font;
	TLTextMetrics_ClassInstance->add_font_index=TLTextMetrics_add_font_index;
	TLTextMetrics_ClassInstance->remove=TLTextMetrics_remove;
	TLTextMetrics_ClassInstance->remove_index=TLTextMetrics_remove_index;
	TLTextMetrics_ClassInstance->remove_all_fonts=TLTextMetrics_remove_all_fonts;
	TLTextMetrics_ClassInstance->update=TLTextMetrics_update;
	TLTextMetrics_ClassInstance->update_single_line=TLTextMetrics_update_single_line;
	TLTextMetrics_ClassInstance->update_multiline=TLTextMetrics_update_multiline;
	TLTextMetrics_ClassInstance->justify_line=TLTextMetrics_justify_line;
	TLTextMetrics_ClassInstance->center_line=TLTextMetrics_center_line;
	TLTextMetrics_ClassInstance->glyph_index_at_x_y=TLTextMetrics_glyph_index_at_x_y;
	TLTextMetrics_ClassInstance->className_CLObject="CLObject";
	TLTextMetrics_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	TLTextMetrics_ClassInstance->init=TLTextMetrics_init;
	TLTextMetrics_ClassInstance->destruct_CLObject=TLTextMetrics_destruct;
	TLTextMetrics_ClassInstance->retain=TLTextMetrics_retain;
	TLTextMetrics_ClassInstance->release=TLTextMetrics_release;
	TLTextMetrics_ClassInstance->event=TLTextMetrics_event;
	TLTextMetrics_ClassInstance->describe=TLTextMetrics_describe;
	
}
struct TLTextMetrics* TLTextMetrics_alloc( )
{
	struct TLTextMetrics* result;
	if(TLTextMetrics_ClassInstance==NULL)TLTextMetrics_CreateClass( );
	result=malloc(sizeof(struct TLTextMetrics));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(TLTextMetrics_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(TLTextMetrics_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void TLTextMetrics_init_type_align_lineheight_width (struct TLTextMetrics* self, char the_type , char the_align , float the_size , float the_width ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->type=the_type;
	self->align=the_align;
	self->width=the_width;
	self->height=the_size;
	self->line_height=the_size;
	self->fonts=CLDataList_alloc( );
	CLDataList_init(self->fonts );
}
void TLTextMetrics_destruct (struct TLTextMetrics* self ) 
{
	CLDataList_release(self->fonts );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void TLTextMetrics_add_font (struct TLTextMetrics* self, struct TLFontMetrics * the_glyph ) 
{
	CLDataList_add_data(self->fonts, the_glyph);
}
void TLTextMetrics_add_font_index (struct TLTextMetrics* self, struct TLFontMetrics * the_glyph , long the_index ) 
{
	CLDataList_add_data_at_index(self->fonts, the_glyph,the_index);
}
void TLTextMetrics_remove (struct TLTextMetrics* self ) 
{
	TLTextMetrics_remove_index( self, self->fonts->length-1);
}
void TLTextMetrics_remove_index (struct TLTextMetrics* self, long the_index ) 
{
	struct TLFontMetrics*font= CLDataList_remove_data_at_index(self->fonts, the_index);
	font->dead=1;
}
void TLTextMetrics_remove_all_fonts (struct TLTextMetrics* self ) 
{
	CLDataList_remove_all_data(self->fonts );
}
void TLTextMetrics_update (struct TLTextMetrics* self ) 
{
	if(self->type==kTLTextMetricsTypeSingleLine)TLTextMetrics_update_single_line( self );
	else TLTextMetrics_update_multiline( self );
}
void TLTextMetrics_update_single_line (struct TLTextMetrics* self ) 
{
	struct CLLink*link74;
	void* glyph_data;
	struct TLFontMetrics*glyph;
	float cursor_x=0;
	float cursor_y=0;
	link74=self->fonts->head;while( link74!=NULL){glyph_data=link74->data; 
	
		glyph=glyph_data;
		(glyph->frame).x=cursor_x;
		(glyph->frame).y=cursor_y;
		cursor_x+=(glyph->frame).z+glyph->kerning;
	link74=link74->next;}
	self->width=cursor_x;
}
void TLTextMetrics_update_multiline (struct TLTextMetrics* self ) 
{
	struct CLLink*link76;
	void* word_data;
	struct CLLink*link75;
	void* glyph_data;
	long spaces=0;
	float line_x=0;
	float cursor_x=0;
	float cursor_y=0;
	struct CLDataList*line;
	struct CLDataList*word;
	struct TLFontMetrics*glyph;
	struct TLFontMetrics*word_glyph;
	line=CLDataList_alloc( );
	CLDataList_init(line );
	word=CLDataList_alloc( );
	CLDataList_init(word );
	link75=self->fonts->head;while( link75!=NULL){glyph_data=link75->data; 
	
		glyph=glyph_data;
		if(cursor_x+(glyph->frame).z>self->width)
		{
			if(spaces==0)
			{
				CLDataList_add_data_list(line, word);
				CLDataList_remove_all_data(word );
			}
			if(self->align==kTLTextMetricsAlignJustify)TLTextMetrics_justify_line( self, &line_x,spaces,cursor_y,line);
			else if(self->align==kTLTextMetricsAlignCenter)TLTextMetrics_center_line( self, &line_x,cursor_y,line);
			cursor_y+=self->line_height;
			cursor_x=0;
			spaces=0;
			CLDataList_remove_all_data(line );
			link76=word->head;while( link76!=NULL){word_data=link76->data; 
			
				word_glyph=word_data;
				(word_glyph->frame).x=cursor_x;
				(word_glyph->frame).y=cursor_y;
				cursor_x+=(word_glyph->frame).z+word_glyph->kerning;
			link76=link76->next;}
		}
		if(glyph->code==13)
		{
			if(self->align==kTLTextMetricsAlignCenter)TLTextMetrics_center_line( self, &cursor_x,cursor_y,line);
			cursor_y+=self->line_height;
			cursor_x=0;
			spaces=0;
			CLDataList_remove_all_data(line );
			CLDataList_remove_all_data(word );
		}
		(glyph->frame).x=cursor_x;
		(glyph->frame).y=cursor_y;
		cursor_x+=(glyph->frame).z+glyph->kerning;
		CLDataList_add_data(word, glyph);
		if(glyph->code==32)
		{
			spaces++;
			line_x=cursor_x-(glyph->frame).z-glyph->kerning;
			CLDataList_add_data_list(line, word);
			CLDataList_remove_all_data(word );
		}
	link75=link75->next;}
	CLDataList_add_data_list(line, word);
	if(self->align==kTLTextMetricsAlignCenter)TLTextMetrics_center_line( self, &cursor_x,cursor_y,line);
	self->height=cursor_y+self->line_height;
	CLDataList_release(line );
	CLDataList_release(word );
}
void TLTextMetrics_justify_line (struct TLTextMetrics* self, float * the_line_x , long the_spaces , float the_cursor_y , struct CLDataList * the_line ) 
{
	struct CLLink*link77;
	void* line_data;
	float gap=0;
	struct TLFontMetrics*line_glyph;
	if(the_spaces>1)gap=(self->width-*the_line_x)/(float)(the_spaces-1);
	*the_line_x=0;
	link77=the_line->head;while( link77!=NULL){line_data=link77->data; 
	
		line_glyph=line_data;
		(line_glyph->frame).x=*the_line_x;
		(line_glyph->frame).y=the_cursor_y;
		*the_line_x+=(line_glyph->frame).z+line_glyph->kerning;
		if(line_glyph->code==32)*the_line_x+=gap;
	link77=link77->next;}
}
void TLTextMetrics_center_line (struct TLTextMetrics* self, float * the_line_x , float the_cursor_y , struct CLDataList * the_line ) 
{
	struct CLLink*link78;
	void* line_data_a;
	struct TLFontMetrics*line_glyph;
	*the_line_x=(self->width-*the_line_x)/2;
	link78=the_line->head;while( link78!=NULL){line_data_a=link78->data; 
	
		line_glyph=line_data_a;
		(line_glyph->frame).x=*the_line_x;
		(line_glyph->frame).y=the_cursor_y;
		*the_line_x+=(line_glyph->frame).z+line_glyph->kerning;
	link78=link78->next;}
}
unsigned long TLTextMetrics_glyph_index_at_x_y (struct TLTextMetrics* self, float the_x , float the_y ) 
{
	struct CLLink*link79;
	void* glyph_data;
	struct TLFontMetrics*glyph;
	unsigned long glyph_index=0;
	link79=self->fonts->head;while( link79!=NULL){glyph_data=link79->data; 
	
		glyph=glyph_data;
		if((glyph->frame).x+(glyph->frame).z>the_x&&(glyph->frame).y+(glyph->frame).w>the_y)return glyph_index;
		glyph_index++;
	link79=link79->next;}
	return glyph_index;
}
void TLTextMetrics_init (struct TLTextMetrics* self ) 
{
	self->retain_count=1;
}
void TLTextMetrics_retain (struct TLTextMetrics* self ) 
{
	self->retain_count=self->retain_count+1;
}
void TLTextMetrics_release (struct TLTextMetrics* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLTextMetrics_event (struct TLTextMetrics* self, int the_id , void * the_source , void * the_data ) 
{

}
void TLTextMetrics_describe (struct TLTextMetrics* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void TLFontMetrics_CreateClass( )
{
	TLFontMetrics_ClassInstance=malloc(sizeof(struct TLFontMetrics_Class));
	TLFontMetrics_ClassInstance->className="TLFontMetrics";
	TLFontMetrics_ClassInstance->classId=&TLFontMetrics_ClassInstance;
	TLFontMetrics_ClassInstance->className_CLObject="CLObject";
	TLFontMetrics_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	TLFontMetrics_ClassInstance->init=TLFontMetrics_init;
	TLFontMetrics_ClassInstance->destruct=TLFontMetrics_destruct;
	TLFontMetrics_ClassInstance->retain=TLFontMetrics_retain;
	TLFontMetrics_ClassInstance->release=TLFontMetrics_release;
	TLFontMetrics_ClassInstance->event=TLFontMetrics_event;
	TLFontMetrics_ClassInstance->describe=TLFontMetrics_describe;
	
}
struct TLFontMetrics* TLFontMetrics_alloc( )
{
	struct TLFontMetrics* result;
	if(TLFontMetrics_ClassInstance==NULL)TLFontMetrics_CreateClass( );
	result=malloc(sizeof(struct TLFontMetrics));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(TLFontMetrics_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(TLFontMetrics_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void TLFontMetrics_init (struct TLFontMetrics* self ) 
{
	self->retain_count=1;
}
void TLFontMetrics_destruct (struct TLFontMetrics* self ) 
{

}
void TLFontMetrics_retain (struct TLFontMetrics* self ) 
{
	self->retain_count=self->retain_count+1;
}
void TLFontMetrics_release (struct TLFontMetrics* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLFontMetrics_event (struct TLFontMetrics* self, int the_id , void * the_source , void * the_data ) 
{

}
void TLFontMetrics_describe (struct TLFontMetrics* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLTextureMap_CreateClass( )
{
	GLTextureMap_ClassInstance=malloc(sizeof(struct GLTextureMap_Class));
	GLTextureMap_ClassInstance->className="GLTextureMap";
	GLTextureMap_ClassInstance->classId=&GLTextureMap_ClassInstance;
	GLTextureMap_ClassInstance->init_width_height=GLTextureMap_init_width_height;
	GLTextureMap_ClassInstance->destruct=GLTextureMap_destruct;
	GLTextureMap_ClassInstance->create_bitmap_texture=GLTextureMap_create_bitmap_texture;
	GLTextureMap_ClassInstance->texture_frame_coords_for_key=GLTextureMap_texture_frame_coords_for_key;
	GLTextureMap_ClassInstance->add_bitmap_for_key=GLTextureMap_add_bitmap_for_key;
	GLTextureMap_ClassInstance->className_CLObject="CLObject";
	GLTextureMap_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLTextureMap_ClassInstance->init=GLTextureMap_init;
	GLTextureMap_ClassInstance->destruct_CLObject=GLTextureMap_destruct;
	GLTextureMap_ClassInstance->retain=GLTextureMap_retain;
	GLTextureMap_ClassInstance->release=GLTextureMap_release;
	GLTextureMap_ClassInstance->event=GLTextureMap_event;
	GLTextureMap_ClassInstance->describe=GLTextureMap_describe;
	
}
struct GLTextureMap* GLTextureMap_alloc( )
{
	struct GLTextureMap* result;
	if(GLTextureMap_ClassInstance==NULL)GLTextureMap_CreateClass( );
	result=malloc(sizeof(struct GLTextureMap));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLTextureMap_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLTextureMap_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLTextureMap_init_width_height (struct GLTextureMap* self, int theWidth , int theHeight ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=theWidth;
	self->height=theHeight;
	self->row_height=0;
	self->cursor_x=0;
	self->cursor_y=0;
	self->keys=CLDataList_alloc( );
	CLDataList_init(self->keys );
	self->names=CLDataList_alloc( );
	CLDataList_init(self->names );
	self->frames=CLDataList_alloc( );
	CLDataList_init(self->frames );
	self->coords=CLDataList_alloc( );
	CLDataList_init(self->coords );
	self->bitmaps=CLDataList_alloc( );
	CLDataList_init(self->bitmaps );
	self->names_by_bitmap=CLDataList_alloc( );
	CLDataList_init(self->names_by_bitmap );
	GLTextureMap_create_bitmap_texture( self );
}
void GLTextureMap_destruct (struct GLTextureMap* self ) 
{
	struct CLLink*link85;
	struct CLLink*link84;
	struct CLLink*link83;
	struct CLLink*link82;
	struct CLLink*link81;
	struct CLLink*link80;
	void* data;
	link80=self->bitmaps->head;while( link80!=NULL){data=link80->data; 
	
		struct GLBitmapRGBA*bitmap=data;
		GLBitmapRGBA_release(bitmap );
	link80=link80->next;}
	CLDataList_release(self->bitmaps );
	link81=self->names_by_bitmap->head;while( link81!=NULL){data=link81->data; 
	
		GLuint*name=data;
		glDeleteTextures(1,name);
	link81=link81->next;}
	CLDataList_release(self->names_by_bitmap );
	link82=self->keys->head;while( link82!=NULL){data=link82->data; 
	
		int*key=data;
		free(key);
	link82=link82->next;}
	CLDataList_release(self->keys );
	link83=self->names->head;while( link83!=NULL){data=link83->data; 
	
		int*name=data;
		free(name);
	link83=link83->next;}
	CLDataList_release(self->names );
	link84=self->frames->head;while( link84!=NULL){data=link84->data; 
	
		MLVector4*frame=data;
		free(frame);
	link84=link84->next;}
	CLDataList_release(self->frames );
	link85=self->coords->head;while( link85!=NULL){data=link85->data; 
	
		MLVector4*coord=data;
		free(coord);
	link85=link85->next;}
	CLDataList_release(self->coords );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLTextureMap_create_bitmap_texture (struct GLTextureMap* self ) 
{
	GLuint*name;
	struct GLBitmapRGBA*bitmap;
	name=malloc(sizeof(GLuint));
	bitmap=GLBitmapRGBA_alloc( );
	GLBitmapRGBA_init_width_height(bitmap, self->width,self->height);
	glGenTextures(1,name);
	glBindTexture(GL_TEXTURE_2D,*name);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);
	CLDataList_add_data(self->bitmaps, bitmap);
	CLDataList_add_data(self->names_by_bitmap, name);
	self->cursor_x=0;
	self->cursor_y=0;
}
char GLTextureMap_texture_frame_coords_for_key (struct GLTextureMap* self, GLuint * the_texture , MLVector4 * the_frame , MLVector4 * the_coords , int the_key ) 
{
	struct CLLink*key_link=self->keys->head;
	struct CLLink*name_link=self->names->head;
	struct CLLink*frame_link=self->frames->head;
	struct CLLink*coord_link=self->coords->head;
	while(key_link!=NULL)
	{
		int*key=(int*)(key_link->data);
		if(*key==the_key)
		{
			*the_frame=*((MLVector4*)frame_link->data);
			*the_coords=*((MLVector4*)coord_link->data);
			*the_texture=*((GLuint*)name_link->data);
			return 1;
		}
		key_link=key_link->next;
		name_link=name_link->next;
		frame_link=frame_link->next;
		coord_link=coord_link->next;
	}
	return 0;
}
MLVector4 GLTextureMap_add_bitmap_for_key (struct GLTextureMap* self, struct GLBitmapRGBA * the_bitmap , int the_key ) 
{
	if(self->cursor_x+the_bitmap->width>=self->width)
	{
		self->cursor_y+=self->row_height;
		self->cursor_x=0;
		self->row_height=0;
	}
	if(self->cursor_y+the_bitmap->height>=self->height)GLTextureMap_create_bitmap_texture( self );
	GLuint*name=self->names_by_bitmap->_class->last_data( (void*) self->names_by_bitmap->_components[0] );
	struct GLBitmapRGBA*bitmap=self->bitmaps->_class->last_data( (void*) self->bitmaps->_components[0] );
	GLBitmapRGBA_blend_bitmap_x_y(bitmap, the_bitmap,self->cursor_x,self->cursor_y);
	MLVector4*bitmap_frame=malloc(sizeof(MLVector4));
	MLVector4*bitmap_coord=malloc(sizeof(MLVector4));
	int*bitmap_key=malloc(sizeof(int));
	int*bitmap_texture=malloc(sizeof(GLuint));
	bitmap_coord->x=(float)self->cursor_x/(float)bitmap->width;
	bitmap_coord->y=(float)self->cursor_y/(float)bitmap->height;
	bitmap_coord->z=((float)self->cursor_x+(float)the_bitmap->width)/(float)bitmap->width;
	bitmap_coord->w=((float)self->cursor_y+(float)the_bitmap->height)/(float)bitmap->height;
	bitmap_frame->x=(float)self->cursor_x;
	bitmap_frame->y=(float)self->cursor_y;
	bitmap_frame->z=(float)the_bitmap->width;
	bitmap_frame->w=(float)-the_bitmap->height;
	*bitmap_key=the_key;
	*bitmap_texture=*name;
	CLDataList_add_data(self->keys, bitmap_key);
	CLDataList_add_data(self->names, bitmap_texture);
	CLDataList_add_data(self->frames, bitmap_frame);
	CLDataList_add_data(self->coords, bitmap_coord);
	self->cursor_x+=the_bitmap->width;
	if(self->row_height<the_bitmap->height)self->row_height=the_bitmap->height;
	glBindTexture(GL_TEXTURE_2D,*name);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,bitmap->width,bitmap->height,0,GL_RGBA,GL_UNSIGNED_BYTE,bitmap->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	return*bitmap_frame;
}
void GLTextureMap_init (struct GLTextureMap* self ) 
{
	self->retain_count=1;
}
void GLTextureMap_retain (struct GLTextureMap* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLTextureMap_release (struct GLTextureMap* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLTextureMap_event (struct GLTextureMap* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLTextureMap_describe (struct GLTextureMap* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
void GLShader_CreateClass( )
{
	GLShader_ClassInstance=malloc(sizeof(struct GLShader_Class));
	GLShader_ClassInstance->className="GLShader";
	GLShader_ClassInstance->classId=&GLShader_ClassInstance;
	GLShader_ClassInstance->init_name=GLShader_init_name;
	GLShader_ClassInstance->destruct=GLShader_destruct;
	GLShader_ClassInstance->add_vertex_shader_source=GLShader_add_vertex_shader_source;
	GLShader_ClassInstance->add_fragment_shader_source=GLShader_add_fragment_shader_source;
	GLShader_ClassInstance->add_attribute_identifier_location=GLShader_add_attribute_identifier_location;
	GLShader_ClassInstance->add_uniform_identifier=GLShader_add_uniform_identifier;
	GLShader_ClassInstance->attribute_location_for_identifier=GLShader_attribute_location_for_identifier;
	GLShader_ClassInstance->uniform_location_for_identifier=GLShader_uniform_location_for_identifier;
	GLShader_ClassInstance->link=GLShader_link;
	GLShader_ClassInstance->compile_shader_type_source=GLShader_compile_shader_type_source;
	GLShader_ClassInstance->link_program=GLShader_link_program;
	GLShader_ClassInstance->use=GLShader_use;
	GLShader_ClassInstance->className_CLObject="CLObject";
	GLShader_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLShader_ClassInstance->init=GLShader_init;
	GLShader_ClassInstance->destruct_CLObject=GLShader_destruct;
	GLShader_ClassInstance->retain=GLShader_retain;
	GLShader_ClassInstance->release=GLShader_release;
	GLShader_ClassInstance->event=GLShader_event;
	GLShader_ClassInstance->describe=GLShader_describe;
	
}
struct GLShader* GLShader_alloc( )
{
	struct GLShader* result;
	if(GLShader_ClassInstance==NULL)GLShader_CreateClass( );
	result=malloc(sizeof(struct GLShader));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLShader_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLShader_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLShader_init_name (struct GLShader* self, char * the_name ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->uniform_counter=0;
	self->uniform_locations=malloc(sizeof(GLint));
	self->uniform_identifiers=malloc(sizeof(const char*));
	self->attribute_counter=0;
	self->attribute_locations=malloc(sizeof(GLuint));
	self->attribute_identifiers=malloc(sizeof(const char*));
	self->name=the_name;
	self->program=glCreateProgram();
	#ifdef DEBUG
	gl_errors_show("CreateProgram");
	#endif
}
void GLShader_destruct (struct GLShader* self ) 
{
	if(self->program!=0)glDeleteProgram(self->program);
	free(self->uniform_locations);
	free(self->uniform_identifiers);
	free(self->attribute_locations);
	free(self->attribute_identifiers);
	self->program=0;
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLShader_add_vertex_shader_source (struct GLShader* self, const char * the_source ) 
{
	self->vertex_source=the_source;
}
void GLShader_add_fragment_shader_source (struct GLShader* self, const char * the_source ) 
{
	self->fragment_source=the_source;
}
void GLShader_add_attribute_identifier_location (struct GLShader* self, const char * the_identifier , GLuint the_location ) 
{
	self->attribute_counter+=1;
	self->attribute_locations=realloc(self->attribute_locations,sizeof(GLuint)*self->attribute_counter);
	self->attribute_identifiers=realloc(self->attribute_identifiers,sizeof(const char*)*self->attribute_counter);
	self->attribute_locations[self->attribute_counter-1]=the_location;
	self->attribute_identifiers[self->attribute_counter-1]=the_identifier;
}
void GLShader_add_uniform_identifier (struct GLShader* self, const char * the_identifier ) 
{
	self->uniform_counter+=1;
	self->uniform_locations=realloc(self->uniform_locations,sizeof(GLint)*self->uniform_counter);
	self->uniform_identifiers=realloc(self->uniform_identifiers,sizeof(const char*)*self->uniform_counter);
	self->uniform_identifiers[self->uniform_counter-1]=the_identifier;
}
GLuint GLShader_attribute_location_for_identifier (struct GLShader* self, const char * the_identifier ) 
{
	int index;
	for(index=0;
	index<self->uniform_counter;
	index++)
	{
		if(strcmp(self->attribute_identifiers[index],the_identifier)==0)return self->attribute_locations[index];
	}
	return 0;
}
GLint GLShader_uniform_location_for_identifier (struct GLShader* self, const char * the_identifier ) 
{
	int index;
	for(index=0;
	index<self->uniform_counter;
	index++)
	{
		if(strcmp(self->uniform_identifiers[index],the_identifier)==0)return self->uniform_locations[index];
	}
	return 0;
}
void GLShader_link (struct GLShader* self ) 
{
	int index;
	char success;
	success=GLShader_compile_shader_type_source( self, &self->vertex_shader,GL_VERTEX_SHADER,self->vertex_source);
	if(success==1)
	{
		glAttachShader(self->program,self->vertex_shader);
		#ifdef DEBUG
		gl_errors_show("AttachVertex");
		#endif
		success=GLShader_compile_shader_type_source( self, &self->fragment_shader,GL_FRAGMENT_SHADER,self->fragment_source);
		if(success==1)
		{
			glAttachShader(self->program,self->fragment_shader);
			#ifdef DEBUG
			gl_errors_show("AttachFragment");
			#endif
		}
		else printf("\nShader %s : Failed to compile fragment shader",self->name);
		for(index=0;
		index<self->attribute_counter;
		index++)
		{
			glBindAttribLocation(self->program,self->attribute_locations[index],self->attribute_identifiers[index]);
		}
		success=GLShader_link_program( self );
		if(success==1)
		{
			for(index=0;
			index<self->uniform_counter;
			index++)
			{
				self->uniform_locations[index]=glGetUniformLocation(self->program,self->uniform_identifiers[index]);
			}
		}
		else printf("\nShader %s : Failed to link program: %d",self->name,self->program);
	}
	else printf("\nShader %s : Failed to compile vertex shader",self->name);
	if(self->vertex_shader>0)
	{
		glDetachShader(self->program,self->vertex_shader);
		glDeleteShader(self->vertex_shader);
	}
	if(self->fragment_shader>0)
	{
		glDetachShader(self->program,self->fragment_shader);
		glDeleteShader(self->fragment_shader);
	}
	self->vertex_shader=0;
	self->fragment_shader=0;
}
char GLShader_compile_shader_type_source (struct GLShader* self, GLuint * the_shader , GLenum the_type , const GLchar * the_source ) 
{
	GLint status,logLength,realLength;
	GLchar*log;
	status=0;
	*the_shader=glCreateShader(the_type);
	#ifdef DEBUG
	gl_errors_show("CreateShader");
	#endif
	if(*the_shader>0)
	{
		glShaderSource(*the_shader,1,&the_source,NULL);
		#ifdef DEBUG
		gl_errors_show("ShaderSource");
		#endif
		glCompileShader(*the_shader);
		#ifdef DEBUG
		gl_errors_show("compile_shader_type_source");
		#endif
		glGetShaderiv(*the_shader,GL_INFO_LOG_LENGTH,&logLength);
		if(logLength>0)
		{
			log=(GLchar*)malloc(logLength);
			glGetShaderInfoLog(*the_shader,logLength,&realLength,log);
			printf("\nShader %s : compile log:\n%s",self->name,log);
			free(log);
		}
		glGetShaderiv(*the_shader,GL_COMPILE_STATUS,&status);
		if(status==GL_TRUE)return 1;
	}
	else printf("\nCannot create shader");
	return 0;
}
char GLShader_link_program (struct GLShader* self ) 
{
	GLint status,logLength;
	GLchar*log;
	glLinkProgram(self->program);
	#ifdef DEBUG
	gl_errors_show("LinkProgram");
	#endif
	glGetProgramiv(self->program,GL_INFO_LOG_LENGTH,&logLength);
	if(logLength>0)
	{
		log=(GLchar*)malloc(logLength);
		glGetProgramInfoLog(self->program,logLength,&logLength,log);
		printf("\nShader %s : Program link log:\n%s",self->name,log);
		free(log);
	}
	glGetProgramiv(self->program,GL_LINK_STATUS,&status);
	if(status==GL_TRUE)return 1;
	return 0;
}
void GLShader_use (struct GLShader* self ) 
{
	glUseProgram(self->program);
	#ifdef DEBUG
	gl_errors_show("UseProgram");
	#endif
}
void GLShader_init (struct GLShader* self ) 
{
	self->retain_count=1;
}
void GLShader_retain (struct GLShader* self ) 
{
	self->retain_count=self->retain_count+1;
}
void GLShader_release (struct GLShader* self ) 
{
	self->retain_count=self->retain_count-1;
	if(self->retain_count==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLShader_event (struct GLShader* self, int the_id , void * the_source , void * the_data ) 
{

}
void GLShader_describe (struct GLShader* self ) 
{
	printf("\nObject %li retain_count %li",(long)self,self->retain_count);
}
