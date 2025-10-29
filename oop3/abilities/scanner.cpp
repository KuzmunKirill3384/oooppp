#include "scanner.h"
#include "ability_registry.h"
#include "player.h"

std::string Scanner::use() const
{
    for (int y = cursor.y; y < cursor.y + 2; y++) {
        for (int x = cursor.x; x < cursor.x + 2; x++) {
            if (x < 0 || y < 0 || x >= field.getWidth() || y >= field.getHeight())
                continue;

            CellStatus &status = field.getCellStatus(x, y);
            if (status.has_fog && status.ship != nullptr) {
                return "Ship found in this 2x2 area";
            }
        }
    }

    return "Ship not found";
}

class ScannerCreator : public AbilityCreator {
    std::shared_ptr<Ability> create(Player &user, Player &target) const
    {
        return std::make_shared<Scanner>(target.Field, user.cursor);
    }

    const char* getName() const { return "Scanner"; }
};

static ScannerCreator creator;
static bool registration = AbilityRegistry::instance().registerAbility(&creator);
