#include "process.h"
#include "system.h"
#include <cstddef>
#include <iostream>

int main() {
    System system;
    while(1) {
        std::cout << "输入 1 创建一个进程\n输入 2 执行一个时间片\n输入 3 运行中的进程请求IO资源\n输入 4 使进程得到资源\n输入 5 挂起进程\n输入 6 激活进程\n输入 7 终止进程\n输入 8 查看所有存在的进程的状态\n";
        int op; std::cin >> op;
        switch(op) {
            case 1: {
                std::cout << "输入该进程每次被分配的时间片数量和进程优先级\n";
                std::size_t time_stamp, priority;
                std::cin >> time_stamp >> priority;
                system.create_process(time_stamp, priority);
                break;
            }
            case 2: {
                system.time_pass();
                break;
            }
            case 3: {
                system.request_IO();
                break;
            }
            case 4: {
                std::cout << "输入得到资源的进程的pid: \n";
                int pid; std::cin >> pid;
                system.release_process(pid);
                break;
            }
            case 5: {
                std::cout << "输入你要挂起的进程的pid: \n";
                int pid; std::cin >> pid;
                system.suspend_process(pid);
                break;
            }
            case 6: {
                std::cout << "输入你要激活的进程的pid: \n";
                int pid; std::cin >> pid;
                system.activate_process(pid);
                break;
            }
            case 7: {
                std::cout << "输入你要终止的进程的pid: \n";
                int pid; std::cin >> pid;
                system.kill_process(pid);
                break;
            }
            case 8: {
                system.show_all();
                break;
            }

        }
            
    }
}