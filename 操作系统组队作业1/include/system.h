#pragma once
#include "process.h"
#include <map>
#include <list>
#include <memory>
#include <optional>
#include <queue>
#include <vector>
#include <set>
#include <functional>
class System {
    // std::list<int> ready_q;
    std::list<int> block_q;
    std::list<int> suspend_q;
    std::optional<int> run_pid;
    std::map<int, std::shared_ptr<Process>> process_map;
    std::optional<int> next_run_pid();
    static std::string status_name[5]; 
    int mx_pid = 0;
    std::function<bool(int,int)> cmp = [this](int lhs, int rhs) {
        return process_map[lhs]->get_priority() > process_map[rhs]->get_priority();
    };
    std::set<int, decltype(cmp)> ready_q{cmp};
    // std::set<int, [](int lhs, int rhs) {
    //     return process_map[lhs].priority < process_map[rhs].priority;
    // }> ready_q;
public:
    int create_process(std::size_t time_stamp, std::size_t priority_);
    void time_pass();
    bool request_IO();
    bool release_process(int pid);
    bool kill_process(int pid);
    bool suspend_process(int pid);
    bool activate_process(int pid);
    void show_all();

};