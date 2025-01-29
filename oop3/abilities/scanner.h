#ifndef OOP_PROG_SCANNER_H
#define OOP_PROG_SCANNER_H

#include "abilitiy.h"
#include "../field.h"
#include "../cursor.h"

class Scanner : public Ability {
    GameBoard &field;
    Cursor cursor;
public:
    Scanner(GameBoard &field, Cursor cursor) : field(field), cursor(cursor) {}
    std::string use() const;
};



#endif //OOP_PROG_SCANNER_H
