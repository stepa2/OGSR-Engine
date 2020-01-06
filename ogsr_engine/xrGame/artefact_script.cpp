#include "StdAfx.h"
#include "Artifact.h"

using namespace luabind;

#pragma optimize("s",on)
void CArtefact::script_register(lua_State* L)
{
	module(L)
	[
		class_<CArtefact, CInventoryItemObject>("CArtefact")
		.def_readwrite("can_spawn_zone", &CArtefact::m_bCanSpawnZone)

		.def_readwrite("health_restore_speed", &CArtefact::m_fHealthRestoreSpeed)
		.def_readwrite("psy_health_restore_speed", &CArtefact::m_fPsyHealthRestoreSpeed)
		.def_readwrite("radiation_restore_speed", &CArtefact::m_fRadiationRestoreSpeed)
		.def_readwrite("satiety_restore_speed", &CArtefact::m_fSatietyRestoreSpeed)
		.def_readwrite("power_restore_speed", &CArtefact::m_fPowerRestoreSpeed)
		.def_readwrite("bleeding_restore_speed", &CArtefact::m_fBleedingRestoreSpeed)
		.def_readwrite("thirst_restore_speed", &CArtefact::m_fThirstRestoreSpeed)

		.def_readwrite("additional_inventory_weight", &CArtefact::m_additional_weight)
		.def_readwrite("additional_inventory_weight2", &CArtefact::m_additional_weight2)

	];
}
