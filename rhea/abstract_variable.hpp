//---------------------------------------------------------------------------
/// \file   abstract_variable.hpp
/// \brief  Base class for variables
//
// This file is part of Rhea.  Rhea is free software: you can redistribute
// it and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version 3
// of the License, or (at your option) any later version.
//
// Rhea is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Rhea.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2014, nocte@hippie.nu
//---------------------------------------------------------------------------
#pragma once

#include <cassert>
#include <string>
#include "errors.hpp"

namespace rhea
{

/** Base class for variables. */
class abstract_variable
{
public:

    typedef std::function<void(void)> set_cb;
    typedef std::function<void(void)> change_cb;

    /** Gets called whenever `set_value` is called. */
    set_cb on_set;
    /** Gets called whenever `change_value` is called. */
    change_cb on_change;

public:
    abstract_variable() {}

    virtual ~abstract_variable() {}

    /** Return true if this is a floating point variable.
     * \sa float_variable */
    virtual bool is_float() const { return false; }

    /** Return true if this is a variable in a finite domain. */
    virtual bool is_fd() const { return false; }

    /** Return true if this a dummy variable.
     * Dummies are used as a marker variable for required equality
     * constraints.  Such variables aren't allowed to enter the basis
     *  when pivoting. \sa dummy_variable */
    virtual bool is_dummy() const { return false; }

    /** Return true if this a variable known outside the solver. */
    virtual bool is_external() const { return false; }

    /** Return true if we can pivot on this variable.
     * \sa simplex_solver::pivot() */
    virtual bool is_pivotable() const
    {
        throw too_difficult("variable not usable inside simplex_solver");
    }

    /** Return true if this is a restricted (or slack) variable.
     * Such variables are constrained to be non-negative and occur only
     * internally to the simplex solver.
     * \sa slack_variable */
    virtual bool is_restricted() const
    {
        throw too_difficult("variable not usable inside simplex_solver");
    }

    /** Get the value of this variable. */
    virtual double value() const { return 0.0; }

    /** Get the value of this variable as an integer */
    virtual int int_value() const { return 0; }

    // LCOV_EXCL_START
    virtual void set_value(double) { assert(false); }

    virtual void change_value(double) { assert(false); }
    // LCOV_EXCL_STOP

    /** Get the value as a string. */
    virtual std::string to_string() const { return "abstract"; }
};

} // namespace rhea
