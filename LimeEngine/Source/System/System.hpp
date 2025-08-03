// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Reflection.hpp"

#define LE_DEFINE_SUBSYSTEM_HOLDER(InSubsystemHolderType, InSubsystemInitializerType)             \
public:                                                                                           \
	using SubsystemInitializerType = InSubsystemInitializerType;                                  \
                                                                                                  \
	inline void InstantiateSubsystems(const InSubsystemInitializerType& Initializer)              \
	{                                                                                             \
		LE_LOG_TRACE(LogSubsystem, "Instantiate subsystems of {}", #InSubsystemHolderType);       \
		SubsystemManager::Get().InstantiateSubsystems<InSubsystemHolderType>(*this, Initializer); \
	}

#define LE_DEFINE_AND_REGISTER_SUBSYSTEM_HOLDER(InSubsystemHolderType, InSubsystemInitializerType) \
	LE_DEFINE_SUBSYSTEM_HOLDER(InSubsystemHolderType, InSubsystemInitializerType)                  \
                                                                                                   \
	inline static void RegisterSubsystemHolder()                                                   \
	{                                                                                              \
		LE_LOG_TRACE(LogSubsystem, "Register subsystem holder {}", #InSubsystemHolderType);        \
		SubsystemManager& subsystemManager = SubsystemManager::Get();                              \
		subsystemManager.RegisterSubsystemHolder<InSubsystemHolderType>();                         \
	}                                                                                              \
	LE_STATIC_INITIALIZE(RegisterSubsystemHolder, SubsystemConstants::RegisterSubsystemHolderPriority)

#define LE_DEFINE_SUBSYSTEM(InSubsystemType, InSubsystemHolderType)                                                                    \
public:                                                                                                                                \
	using SubsystemHolderType = InSubsystemHolderType;                                                                                 \
	inline static URef<Subsystem> CreateSubsystem(const SubsystemInitializer& Initializer)                                             \
	{                                                                                                                                  \
		LE_LOG_TRACE(LogSubsystem, "Creating subsystem {} in {}", #InSubsystemType, #InSubsystemHolderType);                           \
		return std::make_unique<InSubsystemType>(reinterpret_cast<const SubsystemHolderType::SubsystemInitializerType&>(Initializer)); \
	}                                                                                                                                  \
                                                                                                                                       \
private:                                                                                                                               \
	inline explicit InSubsystemType(const SubsystemInitializer& BaseInitializer) :                                                     \
		InSubsystemType(reinterpret_cast<const SubsystemHolderType::SubsystemInitializerType&>(BaseInitializer))                       \
	{}

#define LE_DEFINE_AND_REGISTER_SUBSYSTEM(InSubsystemType, InSubsystemHolderType)                             \
	LE_DEFINE_SUBSYSTEM(InSubsystemType, InSubsystemHolderType)                                              \
                                                                                                             \
	inline static void RegisterSubsystem()                                                                   \
	{                                                                                                        \
		LE_LOG_TRACE(LogSubsystem, "Register subsystem {} in {}", #InSubsystemType, #InSubsystemHolderType); \
		SubsystemManager& subsystemManager = SubsystemManager::Get();                                        \
		subsystemManager.RegisterSubsystem<SubsystemHolderType, InSubsystemType>();                          \
	}                                                                                                        \
	LE_STATIC_INITIALIZE(RegisterSubsystem, SubsystemConstants::RegisterSubsystemPriority)

namespace LimeEngine
{
	LE_DECLARE_EXTERN_LOGGER(LogSubsystem);

	struct LE_API SubsystemConstants
	{
	public:
		static constexpr uint32_t RegisterSubsystemHolderPriority = 200u;
		static constexpr uint32_t RegisterSubsystemPriority = 100u;
	};

	class LE_API SubsystemInitializer
	{
	public:
		virtual ~SubsystemInitializer() = default;
	};

	class LE_API Subsystem
	{
	public:
		virtual ~Subsystem() = default;
		explicit Subsystem(const SubsystemInitializer& Initializer) {};
	};

	class LE_API SubsystemHolder
	{
		LE_DELETE_COPY(SubsystemHolder);

	public:
		SubsystemHolder() noexcept = default;
		virtual ~SubsystemHolder() = default;

		void Reserve(uint32 capacity);
		void AddSubsystem(URef<Subsystem>&& subsystem);

	private:
		// TODO: Replace URef to buffer, count of systems is constant. System Collection maybe
		std::vector<URef<Subsystem>> subsystems;
	};

	class LE_API SubsystemManager final
	{
	public:
		using CreateSubsystemFunc = std::function<URef<Subsystem>(const SubsystemInitializer&)>;

		template <std::derived_from<SubsystemHolder> TSubsystemHolder>
		void RegisterSubsystemHolder();

		template <std::derived_from<SubsystemHolder> TSubsystemHolder, std::derived_from<Subsystem> TSubsystem>
		void RegisterSubsystem();

		template <std::derived_from<SubsystemHolder> TSubsystemHolder>
		void InstantiateSubsystems(TSubsystemHolder& subsystemHolder, const SubsystemInitializer& Initializer) const;

		static SubsystemManager& Get();

	private:
		void RegisterSubsystemHolderInternal(uint32 SubsystemHolderTypeIndex);
		void RegisterSubsystemInternal(uint32 SubsystemHolderTypeIndex, uint32 SubsystemTypeIndex, const CreateSubsystemFunc& CreateFunc);
		void InstantiateSubsystemsInternal(SubsystemHolder& subsystemHolder, uint32 subsystemHolderTypeIndex, const SubsystemInitializer& Initializer) const;

	private:
		// TODO: Change TypeIndex to DeriveTypeIndex
		std::unordered_map<uint32, std::unordered_map<uint32, CreateSubsystemFunc>> subsystemRegistry;
		static SubsystemManager instance;
	};

	template <std::derived_from<SubsystemHolder> TSubsystemHolder>
	void SubsystemManager::RegisterSubsystemHolder()
	{
		RegisterSubsystemHolderInternal(TypeIndexOf<TSubsystemHolder>::index);
	}

	template <std::derived_from<SubsystemHolder> TSubsystemHolder, std::derived_from<Subsystem> TSubsystem>
	void SubsystemManager::RegisterSubsystem()
	{
		RegisterSubsystemInternal(TypeIndexOf<TSubsystemHolder>::index, TypeIndexOf<TSubsystem>::index, TSubsystem::CreateSubsystem);
	}

	template <std::derived_from<SubsystemHolder> TSubsystemHolder>
	void SubsystemManager::InstantiateSubsystems(TSubsystemHolder& subsystemHolder, const SubsystemInitializer& Initializer) const
	{
		InstantiateSubsystemsInternal(subsystemHolder, TypeIndexOf<TSubsystemHolder>::index, Initializer);
	}
}
