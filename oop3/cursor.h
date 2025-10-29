#ifndef OOP_PROG_CURSOR_H
#define OOP_PROG_CURSOR_H

#include <nlohmann/json.hpp>
using namespace nlohmann;

struct Cursor {
    int x;
    int y;

    Cursor(int x, int y) : x(x), y(y) {}

    Cursor(const json &j) : x(j["x"]), y(j["y"]) {}
    friend void to_json(json &j, const Cursor &cursor)
    {
        j = json{{"x", cursor.x}, {"y", cursor.y}};
    }
};

#endif //OOP_PROG_CURSOR_H
