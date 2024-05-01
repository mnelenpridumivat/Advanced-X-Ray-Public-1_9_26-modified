#pragma once
#include <mutex>

#include "xr_smart_pointers.h"


namespace FSM {
	class Builder;
	class FSM;

	class XRCORE_API Controller
	{
		friend Builder;

		static Controller* pinstance_;
		static std::mutex mutex_;

		/*struct Hash {
			template <typename T>
			std::size_t operator() (std::shared_ptr<T> const& p) const {
				return std::hash<T>()(p.get());
			}

			template <typename T>
			std::size_t operator() (T* & p) const {
				return std::hash<T>()(p);
			}
		};
		struct Compare {
			template <typename T>
			size_t operator() (std::shared_ptr<T> const& a,
				std::shared_ptr<T> const& b) const {
				return a.get() == b.get();
			}

			template <typename T>
			size_t operator() (T* & a,	std::shared_ptr<T> const& b) const {
				return a == b.get();
			}

			template <typename T>
			size_t operator() (std::shared_ptr<T> const& a,	T* & b) const {
				return a.get() == b;
			}
		};*/

		DEFINE_USET(xr_shared_ptr<FSM>, FSMVec, FSMVecIt);
		

		FSMVec ActiveFSM;
		FSMVec InactiveFSM;

	protected:

		void AddFSM(const xr_shared_ptr<FSM>& SM);

	public:
		~Controller() {};
		Controller() {};
		Controller(Controller& other) = delete;
		void operator=(const Controller&) = delete;

		static Controller* GetInstance();

		void ActivateFSM(const std::weak_ptr<FSM>& SM);
		void DeactivateFSM(const std::weak_ptr<FSM>& SM);
		void UpdateFSM(float DeltaTime) const;
		bool IsActive(const std::weak_ptr<FSM>& SM);

		void RemoveFSM(const std::weak_ptr<FSM>& SM);

	};
}

