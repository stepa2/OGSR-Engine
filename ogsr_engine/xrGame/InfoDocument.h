///////////////////////////////////////////////////////////////
// InfoDocument.h
// InfoDocument - документ, содержащий сюжетную информацию
///////////////////////////////////////////////////////////////


#pragma once

#include "inventory_item_object.h"
#include "InfoPortionDefs.h"
#include "script_export_space.h"

class CInfoDocument : public CInventoryItemObject
{
private:
	typedef CInventoryItemObject inherited;
public:
	CInfoDocument(void);
	virtual ~CInfoDocument(void);

	BOOL net_Spawn(CSE_Abstract* DC) override;
	void Load(LPCSTR section) override;
	void net_Destroy() override;
	void shedule_Update(u32 dt) override;
	void UpdateCL() override;
	void renderable_Render() override;

	void OnH_A_Chield() override;
	void OnH_B_Independent(bool just_before_destroy) override;

DECLARE_SCRIPT_REGISTER_FUNCTION

protected:
	//индекс информации, содержащейся в документе
	std::vector<std::string> m_Info;
};

add_to_type_list(CInfoDocument)
#undef script_type_list
#define script_type_list save_type_list(CInfoDocument)
