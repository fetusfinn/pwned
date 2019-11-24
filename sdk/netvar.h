/*
 *  netvar.h
 */
#pragma once

#define sdk_get_offset(type, table, netvar) *(type*)((uintptr_t)this + g_offsets.table.netvar);
#define sdk_get_pointer(type, table, netvar) (type*)((uintptr_t)this + g_offsets.table.netvar);
#define sdk_netvar(type, func, table, netvar) type& func() { static uintptr_t offset = g_netvar.get_offset(table, netvar); return *(type*)((uintptr_t)this + offset); }

class netvar_manager_t
{
private:
    
    vector<recv_table_t*> m_tables;
    
private:
    
    vector<recv_table_t*> get_all_tables();
    
public:
    
    void init();
    
    recv_table_t* get_table(string table_name);
    
    int get_offset(string table_name, string prop_name);
    int get_prop(string table_name, string prop_name, recv_prop_t** prop = nullptr);
    int get_prop(recv_table_t* table, string prop_name, recv_prop_t** prop = nullptr);
    string dump_table(recv_table_t* table, int depth);
    uintptr_t hook(string table_name, string prop_name, recv_var_proxy_fn func);
    void print_netvars();
};

extern netvar_manager_t g_netvar;
