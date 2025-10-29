#ifndef OOP_PROG_DOUBLE_DAMAGE_H
#define OOP_PROG_DOUBLE_DAMAGE_H

#include "abilitiy.h"

class DoubleDamage : public Ability {
    bool &double_damage_flag;
public:
    DoubleDamage(bool &double_damage_flag) : double_damage_flag(double_damage_flag) {}
    std::string use() const;
};

#endif //OOP_PROG_SCANNER_H
