#pragma once
#include "inventory_item_object.h"
#include "..\xr_3da\feel_touch.h"
#include "hudsound.h"

class CCustomZone;

//описание типа зоны
struct ZONE_TYPE
{
	//интервал частот отыгрывания звука
	float min_freq;
	float max_freq;
	//звук реакции детектора на конкретную зону
	//	ref_sound	detect_snd;
	HUD_SOUND detect_snds;

	shared_str zone_map_location;
	float m_fRadius;
};

//описание зоны, обнаруженной детектором
struct ZONE_INFO
{
	u32 snd_time;
	//текущая частота работы датчика
	float cur_freq;
	//particle for night-vision mode
	CParticlesObject* pParticle;

	ZONE_INFO();
	~ZONE_INFO();
};

class CInventoryOwner;

class CCustomDetector :
	public CInventoryItemObject,
	public Feel::Touch
{
	using inherited = CInventoryItemObject;
public:
	CCustomDetector(void);
	virtual ~CCustomDetector(void);

	BOOL net_Spawn(CSE_Abstract* DC) override;
	void Load(LPCSTR section) override;

	void OnH_A_Chield() override;
	void OnH_B_Independent(bool just_before_destroy) override;

	void shedule_Update(u32 dt) override;
	void UpdateCL() override;

	void feel_touch_new(CObject* O) override;
	void feel_touch_delete(CObject* O) override;
	BOOL feel_touch_contact(CObject* O) override;

	void TurnOn();
	void TurnOff();
	bool IsWorking() { return m_bWorking; }

	void OnMoveToSlot() override;
	void OnMoveToRuck() override;
	void OnMoveToBelt() override;

protected:
	void StopAllSounds();
	void UpdateMapLocations();
	void AddRemoveMapSpot(CCustomZone* pZone, bool bAdd);
	void UpdateNightVisionMode();

	bool m_bWorking;

	float m_fRadius;

	//если хозяин текущий актер
	CActor* m_pCurrentActor;
	CInventoryOwner* m_pCurrentInvOwner;

	//информация об онаруживаемых зонах
	DEFINE_MAP(CLASS_ID, ZONE_TYPE, ZONE_TYPE_MAP, ZONE_TYPE_MAP_IT);
	ZONE_TYPE_MAP m_ZoneTypeMap;

	//список обнаруженных зон и информация о них
	DEFINE_MAP(CCustomZone*, ZONE_INFO, ZONE_INFO_MAP, ZONE_INFO_MAP_IT);
	ZONE_INFO_MAP m_ZoneInfoMap;

	shared_str m_nightvision_particle;

	bool m_detect_actor_radiation;
	u32 radiation_snd_time;
	void update_actor_radiation();

protected:
	u32 m_ef_detector_type;

public:
	u32 ef_detector_type() const override;
};
