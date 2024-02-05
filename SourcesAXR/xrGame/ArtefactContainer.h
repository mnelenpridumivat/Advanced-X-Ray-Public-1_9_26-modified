#pragma once

#include "inventory_item_object.h"

class CArtefactContainer : public CInventoryItemObject
{
	typedef CInventoryItemObject inherited;

protected:
	size_t					m_iContainerSize;
	xr_vector<CArtefact*>	m_sArtefactsInside;

public:

	CArtefactContainer(void);
	~CArtefactContainer(void) override;

	void			Load						(LPCSTR section) override;
	BOOL			net_Spawn					(CSE_Abstract* DC) override;

	void			save						(NET_Packet& output_packet) override;
	void			load						(IReader& input_packet) override;

	u32				Cost						() const override;
	float			Weight						() const override;

	size_t					GetContainerSize			() const { return m_iContainerSize; }
	void					SetContainerSize			(size_t new_size) { m_iContainerSize = new_size; }
	xr_vector<CArtefact*>	GetArtefactsInside			() { return m_sArtefactsInside; }
	bool					IsFull						() const { return m_sArtefactsInside.size() >= m_iContainerSize; }

	void					PutArtefactToContainer		(const CArtefact& artefact);
	void					TakeArtefactFromContainer	(CArtefact* artefact);
};
