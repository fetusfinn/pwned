/*
 *  hooks.h
 */
#pragma once

// todo :
//  override_view
//  sdl_poll_event

#define print_hook() do{ static bool print = false; if(!print) { skeep(std::string(__FUNCTION__) + " hooked"); print = true; } }while(0)
#define get_orig(vmt, type, index) vmt->get_orignal_method<type>(index)

#define INDEX_PAINT_TRAVERSE        42
#define INDEX_LOCK_CURSOR           67
#define INDEX_KEY_EVENT             21
#define INDEX_FRAME_STAGE_NOTIFY    37
#define INDEX_CREATE_MOVE           25
#define INDEX_DRAW_MODEL_EXE        21
#define INDEX_OVERRIDE_VIEW         19

typedef void(*paint_traverse_fn)(void*, VPANEL, bool, bool);
typedef int (*key_event_fn)(void*, int, int, const char*);
typedef void(*frame_stage_notify_fn)(void*, frame_stage_t);
typedef bool(*create_move_fn)(void*, float, user_cmd_t*);
typedef void(*draw_model_execute_fn)(void*, void*, void*, const model_render_info_t&, matrix3x4_t*);
typedef void(*override_view_fn)(void*, view_setup_t*);

void paint_traverse_hook(void* thisptr, VPANEL panel, bool repaint, bool allow_force);
void lock_cursor_hook(void* thisptr);
int  key_event_hook(void* thisptr, int event_code, int key_code, const char* cur_binding);
void frame_stage_notify_hook(void* thisptr, frame_stage_t frame_stage);
bool create_move_hook(void* thisptr, float sample, user_cmd_t* cmd);
void draw_model_execute_hook(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix);
void override_view_hook(void* thisptr, view_setup_t* setup);
void open_gl_hook();

/*
#define INDEX_PAINTTRAVERSE 42
#define INDEX_FRAMESTAGENOTIFY 37
#define INDEX_INKEYEVENT 21
#define INDEX_HUDUPDATE 11
#define INDEX_DRAWMODELEXECUTE 21
#define INDEX_OVERRIDEVIEW 19
#define INDEX_CREATEMOVE 25
#define INDEX_FIREEVENT 9
#define INDEX_ONSCREENSIZECHANGED 116
#define INDEX_OVERRIDECONFIG 21
#define INDEX_SHOWPIXELS 14
#define INDEX_PUMPWINDOWSMESSAGELOOP 19
#define INDEX_GETEVENTS 12
#define INDEX_SETKEYCODESTATE 92
#define INDEX_SETMOUSECODESTATE 93
#define INDEX_EMITSOUND 6
#define INDEX_DOPOSTSCREENSPACEEFFECTS 45
#define INDEX_READPACKET 18
#define INDEX_SCENEEND 9
#define INDEX_LOCKCURSOR 67
#define INDEX_HUDPROCESSINPUT 10
#define INDEX_IN_ACTIVATEMOUSE 16
#define INDEX_GETLOCALPLAYER 12
#ifdef GOSX_RAGE_MODE
#   define INDEX_BEGINFRAME 42
#endif
*/
