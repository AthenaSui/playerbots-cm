
#include "playerbot/playerbot.h"
#include "NearestCorpsesValue.h"

#include "playerbot/ServerFacade.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;
using namespace MaNGOS;

class AnyDeadUnitInObjectRangeCheck
{
public:
    AnyDeadUnitInObjectRangeCheck(WorldObject const* obj, float range) : i_obj(obj), i_range(range) {}
    WorldObject const& GetFocusObject() const { return *i_obj; }
    bool operator()(Unit* u)
    {
        return !sServerFacade.IsAlive(u) && i_obj->IsWithinDistInMap(u, i_range);
    }
private:
    WorldObject const* i_obj;
    float i_range;
};

void NearestCorpsesValue::FindUnits(std::list<Unit*> &targets)
{
    AnyDeadUnitInObjectRangeCheck u_check(bot,  range);
    UnitListSearcher<AnyDeadUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

bool NearestCorpsesValue::AcceptUnit(Unit* unit)
{
    return true;
}
