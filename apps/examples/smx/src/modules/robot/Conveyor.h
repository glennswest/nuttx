/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "Module.h"
#include "HeapRing.h"

using namespace std;
#include <string>
#include <vector>

class Gcode;
class Block;

class Conveyor : public Module
{
public:
    Conveyor();

    void on_module_loaded(void);
    void on_idle(void *);
    void on_main_loop(void *);
    void on_block_end(void *);
    void on_halt(void *);
    void on_config_reload(void *);

    void notify_block_finished(Block *);

    void wait_for_empty_queue();
    bool is_queue_empty() { return queue.is_empty(); };
    bool is_queue_full() { return queue.is_full(); };

    void ensure_running(void);

    void append_gcode(Gcode *);
    void queue_head_block(void);

    void dump_queue(void);
    void flush_queue(void);
    bool is_flushing() const { return flush; }

    friend class Planner; // for queue

private:
    typedef HeapRing<Block> Queue_t;

    Queue_t queue;  // Queue of Blocks
    volatile unsigned int gc_pending;

    struct {
        volatile bool running:1;
        volatile bool flush:1;
        volatile bool halted:1;
    };

};

#endif // CONVEYOR_H