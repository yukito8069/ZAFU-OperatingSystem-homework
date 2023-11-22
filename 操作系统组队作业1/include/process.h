#pragma once
#include <cstddef>
#include <string>
class Process {
public:
    enum status {
        ACT_READY, STATIONARY_READY, ACT_BLOCK, STATIONARY_BLOCK, RUN
    };
    Process() = default;
    Process(size_t time_stamp_, int pid_, int priority_) : time_stamp(time_stamp_), time_res(time_stamp_), pid(pid_), priority(priority_){}
    bool decrease_time();
    void request_IO();
    bool wake_up();
    int get_pid();
    void set_status(status st_);
    bool release();
    bool suspend();
    status get_status();
    bool activate();
    std::size_t get_priority();
    std::size_t get_time_stamp();
    std::size_t get_time_res();

private:
    std::size_t time_stamp;
    std::size_t time_res;
    int pid;
    status st = status::ACT_READY;
    std::size_t priority;

};