#ifndef OOP_PROG_EXCEPTION_H
#define OOP_PROG_EXCEPTION_H

class GameException {
public:
    virtual const char *what() = 0;
};

#endif //OOP_PROG_EXCEPTION_H
