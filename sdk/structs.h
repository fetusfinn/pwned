/*
 *  structs.h
 *  todo : comment what the structs are and what theyre used in
 */
#pragma once

struct item_t
{
    item_t(const char* display_name, const char* entity_name, const char* model, const char* killicon = nullptr) :
           display_name(display_name), entity_name(entity_name), model(model), killicon(killicon) {}
    
    const char* display_name;
    const char* entity_name;
    const char* model;
    const char* killicon;
};

struct model_t
{
    char name[255];
};

// bounding box for a player
struct player_box_t
{
    float x, y, w, h;
    bool  valid = false;
};

struct weapon_info_t
{
    char    _pad1[8];           // 0x0
    char*   m_szConsoleName;    // 0x8
    char    _pad2[8];           // 0x12
    int     m_iClipSize;        // 0x20
    char    _pad3[220];         // 0x24
    char*   m_szHUDName;
    char    _pad4[64];
    int     m_WeaponType;
    char    _pad5[36];
    bool    m_bIsFullAuto;
    char    _pad6[3];
    int     m_iDamage;
    float   m_flArmorRatio;
    int     m_iBulletsPerShot;
    float   m_flPenetration;
    char    _pad7[8];
    float   m_flRange;
    float   m_flRangeModifier;
    float   m_flThrowVelocity;
    char    _pad8[12];
    bool    m_bHasSilencer;
    char    _pad9[163];
    int     m_iZoomLevels;      // 0x1B0
    int     m_iZoomFOV1;        //
    int     m_iZoomFOV2;        //
    float   m_flZoomTime[3];
    char    _pad0[152];
    bool    m_bHasBurstMode;
    bool    m_bIsRevolver;
    bool    m_bCanShootUnderwater;
};

typedef struct player_info_s
{
    int64_t __pad0;
    union
    {
        int64_t xuid;
        struct
        {
            int xuidlow;
            int xuidhigh;
        };
    };
    char            name[128];
    int             userid;
    char            guid[33];
    unsigned int    friends_id;
    char            friends_name[128];
    bool            fake_player;
    bool            is_hltv;
    unsigned int    custom_files[4];
    unsigned char   files_downloaded;
    
}player_info_t;

/*
 *  recv_prop
 */

struct recv_prop_t;

struct dvariant_t
{
    union
    {
        float   m_float;
        long    m_int;
        char*   m_string;
        void*   m_data;
        float   m_vector[3];
        int64_t m_int64;
    };
    
    int m_type;
};

struct recv_proxy_data_t
{
    const recv_prop_t*  m_recv_prop;
    dvariant_t          m_value;
    int                 m_element;
    int                 m_object_id;
};

struct recv_table_t
{
    recv_prop_t*m_props;
    int         m_prop_count;
    void*       m_decoder;
    char*       m_net_table_name;
    bool        m_initialized;
    bool        m_in_main_list;
};

typedef void (*recv_var_proxy_fn) (const recv_proxy_data_t* data, void* _struct, void* out);

struct recv_prop_t
{
    char*       m_var_name;
    int         m_recv_type;
    int         m_flags;
    int         m_string_buffer_size;
    bool        m_inside_array;
    const void* m_extra_data;
    recv_prop_t*m_array_prop;
    void*       m_array_length_proxy;
    recv_var_proxy_fn   m_proxy_fn;
    void*       m_data_table_proxy_fn;
    recv_table_t* m_data_table;
    int         m_offset;
    int         m_element_stride;
    int         m_element_count;
    const char* m_parent_array_prop_name;
};

/*
 *  client_class 
 */

class   client_networkable_t;
typedef client_networkable_t* (*create_client_class_fn)(int ent_num, int serial_num);

struct client_class_t
{
    create_client_class_fn  m_create_fn;
    void*                   m_create_event_fn;
    char*                   m_network_name;
    recv_table_t*           m_recv_table;
    client_class_t*         m_next;
    int                     m_class_id;
};
