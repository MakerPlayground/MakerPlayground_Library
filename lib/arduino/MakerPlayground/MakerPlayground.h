#include <Arduino.h>

#ifdef MP_DEBUG
    #define PRINT_DEBUG(content) Serial.println(content); delay(100);
#else
    #define PRINT_DEBUG(content) ;
#endif

#define MP_LOG_INTERVAL_DEFAULT 1000

int status_code = 0;
unsigned long currentTime = 0;
unsigned long latestLogTime = 0;

class Scene;
class Condition {
public:
    Condition(bool (*condition)(void)): condition(condition) {}
    void linkNextScene(Scene* scene) { nextScene = scene; }
private:
    bool(*condition)(void);
    Scene* nextScene = NULL;
    Condition* _next = NULL;
    friend class Scene;
    friend class MakerPlayground;
};

class Scene {
public:
    Scene(int delay_millis): delay_millis(delay_millis) {}
    Scene(void (*action)(void), unsigned int delay_millis = 0): action(action), delay_millis(delay_millis) {}
    void linkNextScene(Scene* scene) { nextScene = scene; }
    template<typename... Condition_list> 
    void linkConditions(Condition* condition, Condition_list ...args) {
        if (condition_head == NULL) { condition_head = condition; } 
        else { 
            Condition* c = condition_head;
            while(c->_next != NULL) { c = c->_next; }
            c->_next = condition;
        }
        linkConditions(args...);
    }
private:
    void linkConditions () {}
    void(*action)(void) = NULL;
    Scene* nextScene = NULL;
    Condition* condition_head = NULL;
    unsigned int delay_millis = 0;
    friend class MakerPlayground;
};

template<typename T>
class DoubleProperty {
public:
    DoubleProperty(T& device, double(T::*evalFn)(void), unsigned int update_interval = 0)
        : obj(&device)
        , evalFn(evalFn)
        , update_interval(update_interval)
        , value((obj->*evalFn)()) {}
    operator double() {
        if (millis() - last_update_time >= update_interval) {
            value = (obj->*evalFn)();
            last_update_time = millis();
        }
        return value;
    }
private:
    unsigned int last_update_time = millis();
    T* obj;
    double (T::*evalFn)(void) = NULL;
    unsigned int update_interval = 0;
    double value;
};

void mp_logging();
void loop() {}

class MakerPlayground {
public:
    Scene BEGIN = Scene(0);
    void run() {
        Scene* currentScene = &BEGIN;
        while(true) {
            PRINT_DEBUG(String("Scene: ") + (int) currentScene);
            update();
            // do scene's action
            if(currentScene->action != NULL) currentScene->action();

            // delay
            unsigned long time1 = millis();
            while (currentTime - time1 < currentScene->delay_millis) update();
            
            // case 1: have next scene
            if (currentScene->nextScene) { 
                PRINT_DEBUG("have next scene, change current");
                currentScene = currentScene->nextScene; 
            }
            // case 2: have conditions
            else if (currentScene->condition_head) {
                PRINT_DEBUG("have condition, check");
                Condition* c = currentScene->condition_head;
                bool pass = false;
                while (!pass) {
                    update();
                    c = currentScene->condition_head;
                    bool complete = false;
                    while(!complete && !pass) {
                        if (c->condition()) { pass = true; }
                        else if (c->_next == NULL) { complete = true; }
                        else { c = c->_next; }
                    }
                }
                PRINT_DEBUG(String("Pass with c = ") + (int) c);
                PRINT_DEBUG(String("next scene is ") + (int) (c->nextScene));
                currentScene = c->nextScene ? c->nextScene : &BEGIN;
            }
            // case 3: have nothing, back to BEGIN
            else {
                PRINT_DEBUG(String("back to BEGIN (c=") + (int) &BEGIN + String(")"));
                currentScene = &BEGIN;
            }
        }
    }
    void setLoggingFn(void (*loggingFn)(void), int logInterval = 1000) {
        _logging = loggingFn;
        _logInterval = logInterval;
    }
    void schedule(void (*func)(void)) {
        Function* newFunc = new Function();
        newFunc->Fn = func;
        if(!_custom_head) { _custom_head = newFunc; return; }
        Function* current = _custom_head;
        while(current -> _next != NULL && current->Fn != func) current = current -> _next;
        if (current->Fn != func) current -> _next = newFunc;
    }
    void unschedule(void (*func)(void)) {
        if (_custom_head->Fn == func) {
            _custom_head = _custom_head->_next;
            return;
        }
        Function* prev = _custom_head;
        Function* current = _custom_head -> _next;
        while (current != NULL) {
            if (current->Fn == func) {
                prev->_next = current->_next;
                return;
            }
            prev = prev->_next;
            current = current->_next;
        }
    }
private:
    unsigned int _logInterval = MP_LOG_INTERVAL_DEFAULT;
    struct Function {
        void (*Fn)(void);
        struct Function* _next = NULL;
    };
    void (*_logging)(void) = NULL;
    Function* _custom_head = NULL;
    void update() {
        currentTime = millis();

        Function* custom_current = _custom_head;
        while(custom_current != NULL) {
            custom_current->Fn();
            custom_current = custom_current->_next;
        }

        if (_logging != NULL && currentTime - latestLogTime > _logInterval) {
            _logging();
            latestLogTime = millis();
        }
    }
} MP;

#define __MP_LOG_INIT(name) { Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] Initializing")); Serial.println('\0'); }
#define __MP_LOG(device, name) { Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); device.printStatus(); Serial.println('\0'); }
#define __MP_ERR(device, name, status_code) { Serial.print(F("[[ERROR]] ")); Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(&(device.ERRORS[status_code])))); Serial.println('\0'); }
#define __MP_LOG_P(device, name) { Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); device->printStatus(); Serial.println('\0'); }
#define __MP_ERR_P(device, name, status_code) { Serial.print(F("[[ERROR]] ")); Serial.print(F("[[")); Serial.print(F(name)); Serial.print(F("]] ")); Serial.println(reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(&(device->ERRORS[status_code])))); Serial.println('\0'); }

#define MP_INIT_DEVICE_WITH_OUTPUT(device) { __MP_LOG_INIT(#device); status_code = device.init(); if (status_code != 0) { __MP_ERR(device, #device, status_code); while(1); } } MP.schedule([]()->void{ device.update(currentTime); });
#define MP_INIT_CLOUD_WITH_OUTPUT(device) { __MP_LOG_INIT(#device); status_code = device->init(); if (status_code != 0) { __MP_ERR_P(device, #device, status_code); while(1); } } MP.schedule([]()->void{ device->update(currentTime); });
#define MP_INIT_DEVICE_NO_OUTPUT(device) if (device.init() != 0) { while(1); } MP.schedule([]()->void{ device.update(currentTime); });
#define MP_INIT_CLOUD_NO_OUTPUT(device) if (device->init() != 0) { while(1); } MP.schedule([]()->void{ device->update(currentTime); });
#define MP_SET_LOG_INTERVAL(interval) MP.logInterval = interval
#define MP_LOG_DEVICE(device) { __MP_LOG(device, #device); }
#define MP_LOG_CLOUD(device) { __MP_LOG_P(device, #device); }

#if defined(MP_NO_INIT_LOG)
    #define MP_INIT_DEVICE(device) MP_INIT_DEVICE_NO_OUTPUT(device)
    #define MP_INIT_CLOUD(device) MP_INIT_CLOUD_NO_OUTPUT(device)
#else
    #define MP_INIT_DEVICE(device) MP_INIT_DEVICE_WITH_OUTPUT(device)
    #define MP_INIT_CLOUD(device) MP_INIT_CLOUD_WITH_OUTPUT(device)
#endif