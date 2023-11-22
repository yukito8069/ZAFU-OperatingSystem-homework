#include "system.h" 
#include "process.h"
#include <list>
// #include <ranges>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>

std::string System::status_name[5]= {"ACT_READY", "STATIONARY_READY", "ACT_BLOCK", "STATIONARY_BLOCK", "RUN"};

std::optional<int> System::next_run_pid() {
    if(ready_q.empty()) return {};
    // int ret = ready_q.front();
    int ret = *ready_q.cbegin();
    process_map[ret]->set_status(Process::status::RUN);
    ready_q.erase(ready_q.cbegin());
    return ret;
}

void System::time_pass() {
    if(!run_pid.has_value()) {
        if(ready_q.empty()) {
            std::cout << "无可进入运行状态的进程\n";
            return;
        }
        else {
            run_pid = next_run_pid();
        }
    }
    auto run_pro = process_map[run_pid.value()];
    if(!run_pro->decrease_time()) {
        std::cout << "pid为如下的进程时间片用完了: " << run_pid.value() << "\n";
        ready_q.insert(run_pid.value());
        run_pid = next_run_pid();
    }
}

int System::create_process(std::size_t time_stamp, std::size_t priority_) {
    std::shared_ptr<Process> pro_pt = std::make_shared<Process>(time_stamp, ++mx_pid, priority_);
    process_map[pro_pt->get_pid()] = pro_pt;
    ready_q.insert(pro_pt->get_pid());
    std::cout << "创建新进程，其pid为: " << pro_pt->get_pid() << "\n";
    return pro_pt->get_pid();
}


bool System::request_IO() {
    // if(!run_pid.has_value()) {
    //     run_pid = next_run_pid();
    if(!run_pid.has_value()) {
        std::cout << "没有正在运行中的程序和就绪的程序\n";
        return false;
    }
    // }
    process_map[run_pid.value()]->request_IO();
    block_q.emplace_back(run_pid.value());
    run_pid = next_run_pid();
    return true;
}

bool System::suspend_process(int pid) {
    if(process_map.find(pid) == process_map.end()) {
        std::cout << "该进程并不存在\n";
        return false;
    }
    auto pro = process_map[pid];
    if(pro->get_status() == Process::RUN) {
        run_pid = next_run_pid();
        pro->set_status(Process::STATIONARY_READY);
        suspend_q.emplace_back(pid);
        std::cout << "pid为如下的进程从运行态进入静态就绪: \n" << pid << "\n";
        return true;
    }
    if(!pro->suspend()) {
        std::cout << "该进程并不在活动状态\n";
        return false;
    }
    suspend_q.emplace_back(pid);
    if(pro->get_status() == Process::STATIONARY_BLOCK) {
        auto iter = std::find(block_q.begin(), block_q.end(), pid);
        block_q.erase(iter);
    }
    else {
        auto iter = std::find(ready_q.begin(), ready_q.end(), pid);
        ready_q.erase(iter);
    }
    return true;
}


bool System::release_process(int pid) {
    if(process_map.find(pid) == process_map.end()) {
        std::cout << "该进程并不存在\n";
        return false;
    }
    auto pro = process_map[pid];
    if(!pro->release()) {
        std::cout << "该进程并不在阻塞状态\n";
        return false;
    }
    if(pro->get_status() == Process::ACT_READY) {
        ready_q.insert(pid);
        auto iter = std::find(block_q.begin(), block_q.end(), pid);
        block_q.erase(iter);
    }

    return true;
}


bool System::activate_process(int pid) {
    if(process_map.find(pid) == process_map.end()) {
        std::cout << "该进程并不存在\n";
        return false;
    }
    auto pro = process_map[pid];
    if(!pro->activate()) {
        std::cout << "该进程并不在静止状态\n";
        return false;
    }
    auto iter = std::find(suspend_q.begin(), suspend_q.end(), pid);
    suspend_q.erase(iter);

    if(pro->get_status() == Process::ACT_READY) {
        ready_q.insert(pid);
    }
    else {
        block_q.emplace_back(pid);
    }
    return true;
}

bool System::kill_process(int pid) {
    if(process_map.find(pid) == process_map.end()) {
        std::cout << "不存在该进程\n";
        return false;
    }
    auto pro = process_map[pid];
    if(pro->get_status() == Process::ACT_READY) {
        // std::erase(ready_q, pid);
        ready_q.erase(pid);
    }
    else if(pro->get_status() == Process::ACT_BLOCK) {
        // std::erase(block_q, pid);
        block_q.erase(std::find(block_q.begin(), block_q.end(), pid));
    }
    else if(pro->get_status() != Process::RUN) {
        // std::erase(suspend_q, pid);
        suspend_q.erase(std::find(suspend_q.begin(), suspend_q.end(), pid));
    }
    else {
        run_pid = next_run_pid();
    }
    process_map.erase(pid);
    std::cout << "以下进程被删除: " << pid << "\n";
    return true;
}


void System::show_all() {
    std::cout << "pid  进程状态  优先级  被分配的时间片 还剩下的时间片\n";
    for (auto [pid, pro] : process_map) {
        std::cout << pid << " " << status_name[pro->get_status()] << " " << pro->get_priority() << " " << pro->get_time_stamp() << " " << pro->get_time_res() << "\n";
    }
}