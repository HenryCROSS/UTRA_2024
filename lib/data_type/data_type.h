#ifndef _DATA_TYPE_

#include <mini_std.h>

enum op_code_t
{
  OP_TURN_RIGHT = -1,
  OP_GO_STRAIGHT = 0,   
  OP_TURN_LEFT = 1,
};

enum stage_t
{

};

struct status_t {
    mini::stack<op_code_t, 20> op_stack{};
    int op_sum = 0;
};

#endif // ! _DATA_TYPE_