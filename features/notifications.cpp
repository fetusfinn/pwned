/*
 *  notifications
 */
#include "common.h"
#include "renderer.h"
#include "notifications.h"

notification_manager_t* g_notifications = new notification_manager_t();

void notification_manager_t::add(const std::string& msg)
{
    m_notifications.push_front({msg, util_timestamp()});
    
    if(set.misc.notifications.at(3))
        skeep(msg);
}

void notification_manager_t::draw()
{
    long time = util_timestamp();
    
    for(int i = 0; i < m_notifications.size(); i++)
    {
        notification_t notif = m_notifications.at(i);
        
        // more than 5 sec
        if(time - notif.m_time > 5.f)
            notif.m_alpha -= 5;
        
        // start to hide the notifcation
        if(notif.m_alpha < 255)
            notif.m_alpha -= 25;
        
        if(notif.m_alpha > 0)
            g_render->draw_string(10, 10 + (14 * i), renderer_t::tahoma12, notif.m_message, color_t::white);
        
        // notification expired so remove it
        else
            m_notifications.pop_back();
    }
}
