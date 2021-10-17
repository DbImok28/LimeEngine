#pragma once
#include "../Base/Map.hpp"

class TestMap : public Map
{
public:
	TestMap(Engine* engine) : Map(engine) {}
	void LoadScane() override;
};