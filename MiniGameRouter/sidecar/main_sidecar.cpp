# include "SideCar.h"


int main(int argc, char* argv[]) {
    std::string port_str = argv[1];
    int port = std::stoi(port_str);
    std::string namesvr_address = "localhost:54321";
    std::string route_file = "routing_config.txt";
    // std::cout << "hello" << std::endl;
    // int port = 50001;
    //std::cin >> port;
    SideCar sidecar(namesvr_address, route_file, port);
    // std::cout << "wait for connect" << std::endl;
    sidecar.Init();
    // std::cout << "finish connect" << std::endl;
    int s_count = 0;
    while(true) {
        bool o2s = sidecar.OutToSvc(); // 把外面的消息传给svc
        bool s2o = sidecar.SvcToOut();
        bool t = sidecar.Tick();
        if(!(o2s || s2o || t)) {        // 让sidecar休息
            s_count++;
            if(s_count == 10) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                s_count = 0;
            } 
        }
    }
}