// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

#define LE_DELETE_COPY(ClassName)         \
	ClassName(const ClassName&) = delete; \
	ClassName& operator=(const ClassName&) = delete;

#define LE_DELETE_MOVE(ClassName)    \
	ClassName(ClassName&&) = delete; \
	ClassName& operator=(ClassName&&) = delete;

#define LE_DELETE_MOVE_COPY(ClassName) \
	LE_DELETE_COPY(ClassName)          \
	LE_DELETE_MOVE(ClassName)
