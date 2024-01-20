#ifndef _DATA_TYPE_

#include <mini_std.h>

enum op_code_t
{
  OP_TURN_RIGHT = -1,
  OP_GO_STRAIGHT = 0,   
  OP_TURN_LEFT = 1,
  OP_TURNING_POINT = 2, 
  OP_DEAD_POINT = 3,
  
};

struct command_t
{
    op_code_t code;
    int arg1 = 0;
    int arg2 = 0;
    int arg3 = 0;
};

enum stage_t
{
    STG_NORMAL,
    STG_REVERT_DOING,
    STG_REVERT_DONE,
};

struct status_t {
    mini::stack<command_t, 20> op_stack{};
    stage_t current_cmd;
    int direction_checksum = 0; // 1, 0, -1
};

#endif // ! _DATA_TYPE_