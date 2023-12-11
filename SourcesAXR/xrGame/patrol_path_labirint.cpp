#include "stdafx.h"
#include "patrol_path_labirint.h"

#include "patrol_path.h"

CPatrolPathLabirint::CPatrolPathLabirint(CPatrolPathParams* Path)
{
	VERIFY(Path);
	this->Path = Path;

	using Vertex = CVertex<CPatrolPoint, unsigned, CGraphAbstract<CPatrolPoint>>;

	xr_set<const Vertex*> Processed;
	xr_stack<const Vertex*> ToProcess;
	ToProcess.push(Path->m_path->vertex(0));

	while(!ToProcess.empty())
	{
		auto Vertex = ToProcess.top();
		ToProcess.pop();
		for(const auto Connected : Vertex->GetVertices())
		{
			
		}
		Processed.insert(Vertex);
	}

}
