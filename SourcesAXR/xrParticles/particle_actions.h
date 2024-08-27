//---------------------------------------------------------------------------
#include <typeindex>
#ifndef particle_actionsH
#define particle_actionsH


namespace PAPI{
// refs
	struct ParticleEffect;
	struct PARTICLES_API			ParticleAction
	{
		enum{
			ALLOW_ROTATE	= (1<<1)
		};

		enum class Variables : u8 {
			eFlags = 0,
			eType,
			eNextVariable
		};

		template<typename T>
		T* GetVariable(u8 ID) {
			auto Var = GetVariableProtected(ID);
#ifdef DEBUG
			R_ASSERT(Var.type == typeid(T));
			return reinterpret_cast<T*>(Var.ptr);
#else
			return reinterpret_cast<T*>(Var);
#endif
		}

		Flags32			m_Flags;
		PActionEnum		type;	// Type field
		ParticleAction	(){m_Flags.zero();}
        
		virtual void 	Execute		(ParticleEffect *pe, const float dt, float& m_max)	= 0;
		virtual void 	Transform	(const Fmatrix& m)				= 0;

		virtual void 	Load		(IReader& F)=0;
		virtual void 	Save		(IWriter& F)=0;

	protected:

#ifdef DEBUG
		struct AnyTypePtr {
			void* ptr = nullptr;
			std::type_index type;

			AnyTypePtr() : type(typeid(void)) {}

			template<typename T>
			AnyTypePtr(T* value) : ptr(value), type(typeid(T)) {
			}

		};
#else
		using AnyTypePtr = void*;
#endif

		virtual AnyTypePtr GetVariableProtected(u8 ID) {
			switch (ID) {
			case (u8)Variables::eFlags: {
				return &m_Flags;
			}
			case (u8)Variables::eType: {
				return &type;
			}
			}
#ifdef DEBUG
			return AnyTypePtr();
#else
			return nullptr;
#endif
		}

	};
    DEFINE_VECTOR(ParticleAction*,PAVec,PAVecIt);
	class ParticleActions
	{
		PAVec			m_actions;
	public:
		std::mutex m_bLocked;
						ParticleActions	()	{m_actions.reserve(4);}
						~ParticleActions()	{clear();}
		IC void			clear			()
        {
			for (PAVecIt it = m_actions.begin(); it != m_actions.end(); it++)
				xr_delete(*it);
			m_actions.clear();
		}
		ParticleAction* find(PActionEnum type)
		{
			for (PAVecIt it = m_actions.begin(); it != m_actions.end(); it++) {
				if((*it)->type == type)
				{
					return *it;
				}
			}
			return nullptr;
		}
		IC void			append			(ParticleAction* pa)	{ m_actions.push_back(pa);	}
		IC bool			empty			()						{return	m_actions.empty();}
		IC PAVecIt		begin			()						{return	m_actions.begin();}
		IC PAVecIt		end				()						{return m_actions.end();	}
        IC int			size			()						{return m_actions.size();	}
        void			copy			(ParticleActions* src);
	};
};
//---------------------------------------------------------------------------
#endif
