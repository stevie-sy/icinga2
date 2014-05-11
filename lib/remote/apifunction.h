/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2014 Icinga Development Team (http://www.icinga.org)    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef APIFUNCTION_H
#define APIFUNCTION_H

#include "remote/i2-remote.h"
#include "remote/messageorigin.h"
#include "base/registry.h"
#include "base/value.h"
#include "base/dictionary.h"
#include <vector>
#include <boost/function.hpp>

namespace icinga
{

/**
 * An API function.
 *
 * @ingroup base
 */
class I2_REMOTE_API ApiFunction : public Object
{
public:
	DECLARE_PTR_TYPEDEFS(ApiFunction);

	typedef boost::function<Value(const MessageOrigin& origin, const Dictionary::Ptr&)> Callback;

	ApiFunction(const Callback& function);

	Value Invoke(const MessageOrigin& origin, const Dictionary::Ptr& arguments);

	static ApiFunction::Ptr GetByName(const String& name);
	static void Register(const String& name, const ApiFunction::Ptr& function);
	static void Unregister(const String& name);

private:
	Callback m_Callback;
};

/**
 * A registry for API functions.
 *
 * @ingroup base
 */
class I2_REMOTE_API ApiFunctionRegistry : public Registry<ApiFunctionRegistry, ApiFunction::Ptr>
{
public:
	static ApiFunctionRegistry *GetInstance(void);
};

/**
 * Helper class for registering ApiFunction implementation classes.
 *
 * @ingroup base
 */
class I2_REMOTE_API RegisterApiFunctionHelper
{
public:
	RegisterApiFunctionHelper(const String& name, const ApiFunction::Callback& function);
};

#define REGISTER_APIFUNCTION(name, ns, callback) \
	I2_EXPORT icinga::RegisterApiFunctionHelper g_RegisterAF_ ## name(#ns "::" #name, callback)

}

#endif /* APIFUNCTION_H */
