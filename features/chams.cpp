/*  chams.cpp
 *
 *
 */
#include "common.h"
#include "chams.h"

chams_manager_t* g_chams = new chams_manager_t;

/*
 *  materials
 */
static material_t *mat_flat_vis = nullptr, *mat_flat_ign = nullptr, *mat_text_vis = nullptr, *mat_text_ign = nullptr;

/*
 *
 *
 */
static bool does_file_exist(const std::string& str)
{
    std::fstream f(str);
    return f.good();
}

/*
 *
 *
 */
static material_t* create_material(string filename, string type, bool ignorez, bool wireframe)
{
    if(does_file_exist(filename))
        return;
    
    std::string path = util_execute_cmd("pwd") + "csgo/materials/" + filename + ".vmt";
    std::stringstream ss;
    
    ss << "\"" + type + "\"\n" << endl;
    ss << "{\n" << endl;
    ss << "\t\"$basetexture\" \"VGUI/white_additive\"\n" << endl;
    ss << "\t\"$nofog\" \"1\"\n" << endl;
    ss << "\t\"$ignorez\" \"" + to_string(ignorez) + "\"\n" << endl;
    ss << "\t\"$wireframe\" \""+ to_string(wireframe) +"\"\n" << endl;
    ss << "\t\"$halflambert\" \"1\"\n" << endl;
    ss << "}\n" << endl;
    
    ofstream f;
    f.open(path);
    f << ss.str();
    f.close();
    
    material_t* mat = g_mat_system->find_material(filename.c_str(), TEXTURE_GROUP_MODEL);
    
    mat->increment_reference_count();
    
    return mat;
}

/*
 *
 *
 */
void chams_manager_t::create_materials(bool reload)
{
    static bool created = false;
    
    // if we want to relaod then create again
    if(reload)
        created = false;
    
    // if we havent created yet
    if(!created)
    {
        mat_flat_vis = create_material("VertexLitGeneric",  "pwned_flat",       false, false);
        mat_flat_ign = create_material("VertexLitGeneric",  "pwned_flat_ign",   true,  false);
        mat_text_vis = create_material("UnlitGeneric",      "pwned_text",       false, false);
        mat_text_ign = create_material("UnlitGeneric",      "pwned_text_ign", 	true,  false);
        
        created = true;
        
        skeep("Chams materials created");
    }
}

/*
 *
 *
 */
void chams_manager_t::hands(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    
}

/*
 *
 *
 */
void chams_manager_t::player(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    player_t* player = (player_t*)g_ent_list->get_entity(model_info.m_entity_index);
    
    if(!player)
        return;
    
    if(!player->is_player())
        return;
    
}

/*
 *
 *
 */
void chams_manager_t::weapons(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    
}

/*
 *
 *
 */
void chams_manager_t::fake_lag(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    
}

/*
 *
 *
 */
void chams_manager_t::backtrack(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    
}

/*
 *
 *
 */
void chams_manager_t::fake_angles(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    
}
