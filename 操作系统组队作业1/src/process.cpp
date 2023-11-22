#include "process.h"
#include <cassert>
#include <cstddef>
#include <iostream>

// bool Process::wake_up() {
//     if(st != status::STATIONARY_BLOCK && st != status::STATIONARY_READY) {return false;}
//     if(st == status::STATIONARY_BLOCK) {
        // std::cout << "进程状态由静止阻塞变成了活跃阻塞: " << pid << '\n';
//         st = status::ACT_BLOCK;
//     }
//     else {
//         std::cout << "进程状态由静止阻塞变成了活跃阻塞: " << pid << '\n';
//         st = status::ACT_READY;
//     }
//     return true;
// }

bool Process::decrease_time() {
    assert(time_res > 0);
    std::cout << "pid为如下的进程正在被cpu运行: " << pid << "\n";
    time_res--;
    if(!time_res) {
        time_res = time_stamp;
        st = status::ACT_READY;
        return false;
    }
    return true;
}

int Process::get_pid() {
    return pid;
}

size_t Process::get_priority() {
    return priority;
}

std::size_t Process::get_time_stamp() {return time_stamp;}

std::size_t Process::get_time_res() {return time_res;}

void Process::set_status(status st_) {
    st = st_;
}

void Process::request_IO() {
    assert(st == status::RUN);
    st = status::ACT_BLOCK;
    time_res = time_stamp;
}

bool Process::release() {
    if(st != status::STATIONARY_BLOCK && st != status::ACT_BLOCK) {return false;}
    if(st == status::STATIONARY_BLOCK) {
        st = status::STATIONARY_READY;
        std::cout << "进程状态由静止阻塞变成了静止就绪: " << pid << '\n';
    }
    else {
        st = status::ACT_READY;
        std::cout << "进程状态由活跃阻塞变成了活跃就绪: " << pid << '\n';
    }
    return true;
}

bool Process::suspend() {
    if(st != status::ACT_READY && st != status::RUN && st != status::ACT_BLOCK) {return false;}
    if(st == status::ACT_BLOCK) {
        st = STATIONARY_BLOCK;
        std::cout << "进程状态由活跃阻塞变成了静止阻塞: " << pid << '\n';
    }
    else if(st == status::ACT_READY){
        std::cout << "进程状态由活跃就绪变成了静止就绪: " << pid << '\n';
        st = STATIONARY_READY;
    }
    else {
        time_res = time_stamp;
        st = STATIONARY_READY;
    }
    return true;
}

Process::status Process::get_status() {
    return st;
}

bool Process::activate() {
    if(st != STATIONARY_BLOCK && st != STATIONARY_READY) {return false;}
    if(st == STATIONARY_BLOCK) {
        st = ACT_BLOCK;
        std::cout << "进程状态由静止阻塞变成了活跃阻塞: " << pid << '\n';
    }
    else {
        st = ACT_READY;
        std::cout << "进程状态由静止就绪变成了活跃就绪: " << pid << '\n';
    }
    return true;
}