// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class TypeIndexBase
	{
	protected:
		TypeIndexBase(uint32 index) noexcept : instanceIndex(index) {}

		static uint32 GenerateStaticIndex()
		{
			static uint32 counter = 0u;
			return ++counter;
		}

	private:
		uint32 instanceIndex = 0u;
	};

	template <typename T>
	class TypeIndexOf : public TypeIndexBase
	{
	private:
		TypeIndexOf() = default;

	public:
		static inline uint32 index = TypeIndexBase::GenerateStaticIndex();
	};

	class DeriveTypeIndexBase
	{
	private:
		DeriveTypeIndexBase() = default;

	protected:
		DeriveTypeIndexBase(uint32 index) noexcept : instanceIndex(index) {}

		static uint32 GenerateStaticIndex()
		{
			static uint32 counter = 0u;
			return ++counter;
		}

	private:
		uint32 instanceIndex = 0u;
	};

	template <typename TBase, std::derived_from<TBase> T>
	class DeriveTypeIndexOf : public DeriveTypeIndexBase
	{
	public:
		static inline uint32 index = DeriveTypeIndexBase::GenerateStaticIndex();
	};
}
