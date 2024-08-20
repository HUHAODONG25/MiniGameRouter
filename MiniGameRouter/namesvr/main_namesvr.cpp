#include "namesvr.h"
 

int main() {
    std::string ip_address = "localhost";
    int port = 54321;
    int ttl = 2;
    int tts = 20;
    NameSvr namesvr(ip_address, port, ttl, tts);
    std::cout << "namesvr init" << std::endl;
    int s_count = 0;
    while(true) {
        bool r = namesvr.Run();
        namesvr.Tick();
        bool s = namesvr.Sync();
        if(!(r || s)) {
            s_count++;
            if(s_count == 10) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                s_count = 0;
            } 
        }
    }
}