#ifndef ABILITIES_H
#define ABILITIES_H

#include <string>

class Ability {
public:
    virtual std::string use() const = 0;
protected:
};


#endif // ABILITIES_H
