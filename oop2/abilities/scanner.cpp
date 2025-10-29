#include "scanner.h"
#include "ability_registry.h"
#include "player.h"

std::string Scanner::use() const
{
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            if (x < 0 || y < 0 || x >= field.getWidth() || y >= field.getHeight())
                continue;

            CellStatus &status = field.getCellStatus(cursor.x + x, cursor.y + y);
            if (status.has_fog && status.ship != nullptr) {
                return "Ship found in this 2x2 area";
            }
        }
    }

    return "Ship not found";
}

std::shared_ptr<Ability> CreateScanner(Player &user, Player &target)
{
    return std::make_shared<Scanner>(target.Field, user.cursor);
}

static bool registration = AbilityRegistry::instance().registerAbility(CreateScanner);