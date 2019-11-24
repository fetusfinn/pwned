/*
 *  notifications.h
 */
#pragma once

#include <deque>

struct notification_t
{
    std::string m_message;          // notification message
    long        m_time;             // timestamp of when the notification was sent
    float       m_alpha     = 255;  // message alpha
};

class notification_manager_t
{
private:
    
    std::deque<notification_t> m_notifications;
    
public:
    
    void add(const std::string& msg);
    void draw();
    
};

extern notification_manager_t* g_notifications;
