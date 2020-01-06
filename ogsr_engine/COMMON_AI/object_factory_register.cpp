////////////////////////////////////////////////////////////////////////////
//	Module 		: object_factory_register.cpp
//	Created 	: 27.05.2004
//  Modified 	: 27.05.2004
//	Author		: Dmitriy Iassenev
//	Description : Object factory
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "object_factory_impl.h"

// server entities includes
#include "xrServer_Objects_ALife_All.h"
#include "clsid_game.h"

// client entities includes
#	include "../xr_3da/std_classes.h"
#	include "level.h"
#	include "gamepersistent.h"
#	include "hudmanager.h"
#	include "actor.h"
#	include "spectator.h"

#	include "ai/monsters/flesh/flesh.h"
#	include "ai/monsters/chimera/chimera.h"
#	include "ai/monsters/dog/dog.h"
#	include "ai/stalker/ai_stalker.h"
#	include "ai/monsters/bloodsucker/bloodsucker.h"
#	include "ai/monsters/boar/boar.h"
#	include "ai/monsters/pseudodog/pseudodog.h"
#	include "ai/monsters/pseudodog/psy_dog.h"
#	include "ai/monsters/Burer/burer.h"
#	include "ai/monsters/PseudoGigant/pseudo_gigant.h"
#	include "ai/monsters/controller/controller.h"
#	include "ai/monsters/poltergeist/poltergeist.h"
#	include "ai/monsters/zombie/zombie.h"
#	include "ai/monsters/fracture/fracture.h"
#	include "ai/monsters/snork/snork.h"
#	include "ai/monsters/cat/cat.h"
#	include "ai/monsters/tushkano/tushkano.h"

#	include "ai/phantom/phantom.h"

#	include "ai/trader/ai_trader.h"

#	include "ai/crow/ai_crow.h"
#	ifdef DEBUG
#	include "../xr_3da/StatGraph.h"
#	include "PHDebug.h"
#	endif // DEBUG

#	include "hit.h"
#	include "PHDestroyable.h"
#	include "car.h"

#	include "helicopter.h"

#	include "weaponFN2000.h"
#	include "weaponAK74.h"
#	include "weaponLR300.h"
#	include "weaponHPSA.h"
#	include "weaponPM.h"
#	include "weaponAMMO.h"
#	include "weaponFORT.h"
#	include "weaponBINOCULARS.h"
#	include "weaponShotgun.h"
#	include "weaponsvd.h"
#	include "weaponsvu.h"
#	include "weaponrpg7.h"
#	include "weaponval.h"
#	include "weaponvintorez.h"
#	include "weaponwalther.h"
#	include "weaponusp45.h"
#	include "weapongroza.h"
#	include "weaponknife.h"
#	include "weaponBM16.h"
#	include "weaponRG6.h"
#	include "WeaponMounted.h"
#	include "WeaponStatMgun.h"

#	include "scope.h"
#	include "silencer.h"
#	include "grenadelauncher.h"

#	include "bolt.h"
#	include "medkit.h"
#	include "antirad.h"
#	include "fooditem.h"
#	include "bottleitem.h"
#	include "explosiveitem.h"

#	include "infodocument.h"
#	include "attachable_item.h"

#	include "ScientificOutfit.h"
#	include "StalkerOutfit.h"
#	include "MilitaryOutfit.h"
#	include "ExoOutfit.h"

#	include "f1.h"
#	include "rgd5.h"

#	include "explosiverocket.h"

#	include "customzone.h"
#	include "mosquitobald.h"
#	include "mincer.h"
#	include "gravizone.h"
#	include "radioactivezone.h"
#	include "level_changer.h"
#	include "script_zone.h"
#	include "team_base_zone.h"
#	include "torridZone.h"
#	include "ZoneVisual.h"
#	include "hairszone.h"
#	include "amebazone.h"
#	include "nogravityzone.h"

#	include "torch.h"
#	include "pda.h"

#	include "searchlight.h"

#	include "HangingLamp.h"
#	include "physicobject.h"
#	include "script_object.h"
#	include "BreakableObject.h"
#	include "PhysicsSkeletonObject.h"
#	include "DestroyablePhysicsObject.h"

#	include "game_sv_single.h"

#	include "game_cl_single.h"

#	include "UIGameSP.h"
#	include	"climableobject.h"
#	include "space_restrictor.h"
#	include "smart_zone.h"
#	include "InventoryBox.h"
#	include "inventoryContainer.h"
#include "GraviArtifact.h"


void CObjectFactory::register_classes()
{
	// client entities
	add<CLevel>(CLSID_GAME_LEVEL, "level");
	add<CGamePersistent>(CLSID_GAME_PERSISTANT, "game");
	add<CHUDManager>(CLSID_HUDMANAGER, "hud_manager");

	//Server Game type
	add<game_sv_Single>(CLSID_SV_GAME_SINGLE, "game_sv_single");
	//Client Game type
	add<game_cl_Single>(CLSID_CL_GAME_SINGLE, "game_cl_single");

	//Game UI type
	add<CUIGameSP>(CLSID_GAME_UI_SINGLE, "game_ui_single");

	add<CActor, CSE_ALifeCreatureActor>(CLSID_OBJECT_ACTOR, "actor");

	// server entities
	add<CSE_ALifeGroupTemplate<CSE_ALifeMonsterBase>>(CLSID_AI_FLESH_GROUP, "flesh_group");
	//	add<CSE_SpawnGroup>											(CLSID_AI_SPAWN_GROUP			,"spawn_group");
	add<CSE_ALifeGraphPoint>(CLSID_AI_GRAPH, "graph_point");
	add<CSE_ALifeOnlineOfflineGroup>(CLSID_ONLINE_OFFLINE_GROUP, "online_offline_group");

	// client and server entities
	add<CSpectator, CSE_Spectator>(CLSID_SPECTATOR, "spectator");

	add<CAI_Flesh, CSE_ALifeMonsterBase>(CLSID_AI_FLESH, "flesh");
	add<CChimera, CSE_ALifeMonsterBase>(CLSID_AI_CHIMERA, "chimera");
	add<CAI_Dog, CSE_ALifeMonsterBase>(CLSID_AI_DOG_RED, "dog_red");
	add<CAI_Stalker, CSE_ALifeHumanStalker>(CLSID_AI_STALKER, "stalker");
	add<CAI_Bloodsucker, CSE_ALifeMonsterBase>(CLSID_AI_BLOODSUCKER, "bloodsucker");
	add<CAI_Boar, CSE_ALifeMonsterBase>(CLSID_AI_BOAR, "boar");
	add<CAI_PseudoDog, CSE_ALifeMonsterBase>(CLSID_AI_DOG_BLACK, "dog_black");
	add<CPsyDog, CSE_ALifeMonsterBase>(CLSID_AI_DOG_PSY, "psy_dog");
	add<CPsyDogPhantom, CSE_ALifePsyDogPhantom>(CLSID_AI_DOG_PSY_PHANTOM, "psy_dog_phantom");
	add<CBurer, CSE_ALifeMonsterBase>(CLSID_AI_BURER, "burer");
	add<CPseudoGigant, CSE_ALifeMonsterBase>(CLSID_AI_GIANT, "pseudo_gigant");
	add<CController, CSE_ALifeMonsterBase>(CLSID_AI_CONTROLLER, "controller");
	add<CPoltergeist, CSE_ALifeMonsterBase>(CLSID_AI_POLTERGEIST, "poltergeist");
	add<CZombie, CSE_ALifeMonsterBase>(CLSID_AI_ZOMBIE, "zombie");
	add<CFracture, CSE_ALifeMonsterBase>(CLSID_AI_FRACTURE, "fracture");
	add<CSnork, CSE_ALifeMonsterBase>(CLSID_AI_SNORK, "snork");
	add<CCat, CSE_ALifeMonsterBase>(CLSID_AI_CAT, "cat");
	add<CTushkano, CSE_ALifeMonsterBase>(CLSID_AI_TUSHKANO, "tushkano");

	add<CPhantom, CSE_ALifeCreaturePhantom>(CLSID_AI_PHANTOM, "phantom");

	// Trader
	add<CAI_Trader, CSE_ALifeTrader>(CLSID_AI_TRADER, "trader");

	add<CAI_Crow, CSE_ALifeCreatureCrow>(CLSID_AI_CROW, "crow");
	add<CCar, CSE_ALifeCar>(CLSID_CAR, "car");

	add<CHelicopter, CSE_ALifeHelicopter>(CLSID_VEHICLE_HELICOPTER, "helicopter");


	add<CGraviArtefact, CSE_ALifeItemArtefact>(CLSID_ARTEFACT, "artefact");

	//  [8/15/2006]
	add<CWeaponMagazined, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_MAGAZINED, "wpn_wmagaz");
	//  [8/15/2006]
	//  [8/17/2006]
	add<CWeaponMagazinedWGrenade, CSE_ALifeItemWeaponMagazinedWGL>(CLSID_OBJECT_W_MAGAZWGL, "wpn_wmaggl");
	//  [8/17/2006]
	add<CWeaponFN2000, CSE_ALifeItemWeaponMagazinedWGL>(CLSID_OBJECT_W_FN2000, "wpn_fn2000");
	add<CWeaponAK74, CSE_ALifeItemWeaponMagazinedWGL>(CLSID_OBJECT_W_AK74, "wpn_ak74");
	add<CWeaponLR300, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_LR300, "wpn_lr300");
	add<CWeaponHPSA, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_HPSA, "wpn_hpsa");
	add<CWeaponPM, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_PM, "wpn_pm");
	add<CWeaponFORT, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_FORT, "wpn_fort");
	add<CWeaponBinoculars, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_BINOCULAR, "wpn_binocular");
	add<CWeaponShotgun, CSE_ALifeItemWeaponShotGun>(CLSID_OBJECT_W_SHOTGUN, "wpn_shotgun");
	add<CWeaponSVD, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_SVD, "wpn_svd");
	add<CWeaponSVU, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_SVU, "wpn_svu");
	add<CWeaponRPG7, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_RPG7, "wpn_rpg7");
	add<CWeaponVal, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_VAL, "wpn_val");
	add<CWeaponVintorez, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_VINTOREZ, "wpn_vintorez");
	add<CWeaponWalther, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_WALTHER, "wpn_walther");
	add<CWeaponUSP45, CSE_ALifeItemWeaponMagazined>(CLSID_OBJECT_W_USP45, "wpn_usp45");
	add<CWeaponGroza, CSE_ALifeItemWeaponMagazinedWGL>(CLSID_OBJECT_W_GROZA, "wpn_groza");
	add<CWeaponKnife, CSE_ALifeItemWeapon>(CLSID_OBJECT_W_KNIFE, "wpn_knife");
	add<CWeaponBM16, CSE_ALifeItemWeaponShotGun>(CLSID_OBJECT_W_BM16, "wpn_bm16");
	add<CWeaponRG6, CSE_ALifeItemWeaponShotGun>(CLSID_OBJECT_W_RG6, "wpn_rg6");
	//-----------------------------------------------------------------------------------------------------
	add<CWeaponAmmo, CSE_ALifeItemAmmo>(CLSID_OBJECT_AMMO, "wpn_ammo");
	add<CWeaponAmmo, CSE_ALifeItemAmmo>(CLSID_OBJECT_A_VOG25, "wpn_ammo_vog25");
	add<CWeaponAmmo, CSE_ALifeItemAmmo>(CLSID_OBJECT_A_OG7B, "wpn_ammo_og7b");
	add<CWeaponAmmo, CSE_ALifeItemAmmo>(CLSID_OBJECT_A_M209, "wpn_ammo_m209");
	//-----------------------------------------------------------------------------------------------------

	//Weapons add-on
	add<CScope, CSE_ALifeItem>(CLSID_OBJECT_W_SCOPE, "wpn_scope");
	add<CSilencer, CSE_ALifeItem>(CLSID_OBJECT_W_SILENCER, "wpn_silencer");
	add<CGrenadeLauncher, CSE_ALifeItem>(CLSID_OBJECT_W_GLAUNCHER, "wpn_grenade_launcher");

	// Inventory
	add<CBolt, CSE_ALifeItemBolt>(CLSID_IITEM_BOLT, "obj_bolt");
	add<CMedkit, CSE_ALifeItem>(CLSID_IITEM_MEDKIT, "obj_medkit");
	add<CMedkit, CSE_ALifeItem>(CLSID_IITEM_BANDAGE, "obj_bandage");
	add<CAntirad, CSE_ALifeItem>(CLSID_IITEM_ANTIRAD, "obj_antirad");
	add<CFoodItem, CSE_ALifeItem>(CLSID_IITEM_FOOD, "obj_food");
	add<CBottleItem, CSE_ALifeItem>(CLSID_IITEM_BOTTLE, "obj_bottle");
	add<CExplosiveItem, CSE_ALifeItemExplosive>(CLSID_IITEM_EXPLOSIVE, "obj_explosive");

	//Info Document
	add<CInfoDocument, CSE_ALifeItemDocument>(CLSID_IITEM_DOCUMENT, "obj_document");
	add<CInventoryItemObject, CSE_ALifeItem>(CLSID_IITEM_ATTACH, "obj_attachable");

	//Equipment outfit
	add<CScientificOutfit, CSE_ALifeItemCustomOutfit>(CLSID_EQUIPMENT_SCIENTIFIC, "equ_scientific");
	add<CStalkerOutfit, CSE_ALifeItemCustomOutfit>(CLSID_EQUIPMENT_STALKER, "equ_stalker");
	add<CMilitaryOutfit, CSE_ALifeItemCustomOutfit>(CLSID_EQUIPMENT_MILITARY, "equ_military");
	add<CExoOutfit, CSE_ALifeItemCustomOutfit>(CLSID_EQUIPMENT_EXO, "equ_exo");

	// Grenades
	add<CF1, CSE_ALifeItemGrenade>(CLSID_GRENADE_F1, "wpn_grenade_f1");
	add<CRGD5, CSE_ALifeItemGrenade>(CLSID_GRENADE_RGD5, "wpn_grenade_rgd5");

	// Rockets
	add<CExplosiveRocket, CSE_Temporary>(CLSID_OBJECT_G_RPG7, "wpn_grenade_rpg7");
	add<CExplosiveRocket, CSE_Temporary>(CLSID_OBJECT_G_FAKE, "wpn_grenade_fake");

	// Zones
	add<CCustomZone, CSE_ALifeCustomZone>(CLSID_ZONE, "zone");
	add<CMosquitoBald, CSE_ALifeAnomalousZone>(CLSID_Z_MBALD, "zone_mosquito_bald");
	add<CMincer, CSE_ALifeAnomalousZone>(CLSID_Z_MINCER, "zone_mincer");
	add<CMosquitoBald, CSE_ALifeAnomalousZone>(CLSID_Z_ACIDF, "zone_acid_fog");
	add<CMincer, CSE_ALifeAnomalousZone>(CLSID_Z_GALANT, "zone_galantine");
	add<CRadioactiveZone, CSE_ALifeAnomalousZone>(CLSID_Z_RADIO, "zone_radioactive");
	add<CHairsZone, CSE_ALifeZoneVisual>(CLSID_Z_BFUZZ, "zone_bfuzz");
	add<CHairsZone, CSE_ALifeZoneVisual>(CLSID_Z_RUSTYH, "zone_rusty_hair");
	add<CMosquitoBald, CSE_ALifeAnomalousZone>(CLSID_Z_DEAD, "zone_dead");
	add<CLevelChanger, CSE_ALifeLevelChanger>(CLSID_LEVEL_CHANGER, "level_changer");
	add<CScriptZone, CSE_ALifeSpaceRestrictor>(CLSID_SCRIPT_ZONE, "script_zone");
	add<CSmartZone, CSE_ALifeSmartZone>(CLSID_SMART_ZONE, "smart_zone");
	add<CTeamBaseZone, CSE_ALifeTeamBaseZone>(CLSID_Z_TEAM_BASE, "team_base_zone");
	add<CTorridZone, CSE_ALifeTorridZone>(CLSID_Z_TORRID, "torrid_zone");
	add<CSpaceRestrictor, CSE_ALifeSpaceRestrictor>(CLSID_SPACE_RESTRICTOR, "space_restrictor");
	add<CAmebaZone, CSE_ALifeZoneVisual>(CLSID_Z_AMEBA, "ameba_zone");
	add<CNoGravityZone, CSE_ALifeAnomalousZone>(CLSID_Z_NOGRAVITY, "nogravity_zone");
	// Detectors
	add<CSimpleDetector, CSE_ALifeItemDetector>(CLSID_DETECTOR_SIMPLE, "device_detector_simple");

	// Devices
	add<CTorch, CSE_ALifeItemTorch>(CLSID_DEVICE_TORCH, "device_torch");
	add<CPda, CSE_ALifeItemPDA>(CLSID_DEVICE_PDA, "device_pda");

	// objects
	add<CProjector, CSE_ALifeObjectProjector>(CLSID_OBJECT_PROJECTOR, "projector");
	add<CWeaponMounted, CSE_ALifeMountedWeapon>(CLSID_OBJECT_W_MOUNTED, "wpn_mounted");
	add<CWeaponStatMgun, CSE_ALifeStationaryMgun>(CLSID_OBJECT_W_STATMGUN, "wpn_stat_mgun");
	//	add<CTrigger				,CSE_Trigger					>(CLSID_OBJECT_TRIGGER			,"trigger");

	// entity
	add<CHangingLamp, CSE_ALifeObjectHangingLamp>(CLSID_OBJECT_HLAMP, "hanging_lamp");
	add<CPhysicObject, CSE_ALifeObjectPhysic>(CLSID_OBJECT_PHYSIC, "obj_physic");
	add<CScriptObject, CSE_ALifeDynamicObjectVisual>(CLSID_SCRIPT_OBJECT, "script_object");
	add<CBreakableObject, CSE_ALifeObjectBreakable>(CLSID_OBJECT_BREAKABLE, "obj_breakable");
	add<CClimableObject, CSE_ALifeObjectClimable>(CLSID_OBJECT_CLIMABLE, "obj_climable");
	add<CPhysicsSkeletonObject, CSE_ALifePHSkeletonObject>(CLSID_PH_SKELETON_OBJECT, "obj_phskeleton");
	add<CDestroyablePhysicsObject, CSE_ALifeObjectPhysic>(CLSID_PHYSICS_DESTROYABLE, "obj_phys_destroyable");

	add<CInventoryBox, CSE_InventoryBox>(CLSID_INVENTORY_BOX, "inventory_box");
	add<CInventoryContainer, CSE_InventoryContainer>(CLSID_CONTAINER, "inventory_container");
}
