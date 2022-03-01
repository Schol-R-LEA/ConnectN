#ifndef __CONNECTN_AI_H__
#define __CONNECTN_AI_H__ 1

#include "connectnboard.h"


class ConnectN_AI
{
private:
    ConnectNBoard& board;

public:
    ConnectN_AI(ConnectNBoard& b);
    grid_size_t move();

    friend class ConnectNBoard;
};

#endif
