#pragma once
#include <string>
#include <afxwin.h>

#include <functional>
#include <vector>
#include <map>

namespace game_framework {


    class EventManager {
    public:
        //Event definition
        enum EventType {
            EnemyReachedBlueDoor,  
            PlayerHealthDepleted,            
        };

        using Callback = std::function<void()>; 

    private:
        std::map<EventType, std::vector<Callback>> subscribers;     //subscribers for each event

    public:
        
        void subscribe(EventType type, Callback callback) {
            subscribers[type].push_back(callback);
        }

        void notify(EventType type) {
            for (auto& callback : subscribers[type]) {
                callback();
            }
        }
    };
}