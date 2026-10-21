/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file runtime.hpp
 * @brief Declaration of runtime services that used by interpreters or compiled code.
 */
#pragma once
#ifndef __OPENDRAFT_CORE_RUNTIME_HPP__
#define __OPENDRAFT_CORE_RUNTIME_HPP__

#include "om.hpp"
#include <functional>

namespace opendraft::core
{
    // forward declarations.
    class context;

    /**
     * @brief Represents a function invocation in the runtime.
     * @param ctx The execution context.
     * @param args The arguments to the function.
     * @return The result of the function invocation.
     */
    typedef std::shared_ptr<object> function_invocation(
        context& ctx,
        const std::vector<std::shared_ptr<object>>& args);

    /**
     * @brief Represents a template invocation in the runtime.
     * @param ctx The execution context.
     * @param args The arguments to the template.
     */
    typedef void template_invocation(
        context& ctx,
        const std::vector<std::shared_ptr<object>>& args);

    /**
     * @brief Represents a scope of evaluation in the runtime.
     */
    class scope
    {
    public:
        void define_variable(const std::string& name, std::shared_ptr<object> value);
        std::shared_ptr<object> get_variable(const std::string& name) const;

        std::shared_ptr<scope> begin();
    private:
        std::shared_ptr<scope> _parent;
        std::map<std::string, std::shared_ptr<object>> _variables;
        // disable copy and assignment.
        scope(const scope&) = delete;
        scope& operator=(const scope&) = delete;
    };

    /**
     * @brief Represents a table used to register function and template invocations in the runtime.
     */
    class dispatch_table
    {
    public:
        void register_function(
            const std::string& signature, 
            const std::function<function_invocation>& func);
        void register_template(
            const std::string& signature, 
            const std::function<template_invocation>& func);

    private:
        std::map<std::string, std::function<function_invocation>> _functions;
        std::map<std::string, std::function<template_invocation>> _templates;

        // disable copy and assignment.
        dispatch_table(const dispatch_table&) = delete;
        dispatch_table& operator=(const dispatch_table&) = delete;
    };

    /**
     * @brief Represents the execution context in the runtime.
     * @note The context class is not intended to have any derivations.
     */
    class context
    {
    public:
        ~context() = default;


        std::shared_ptr<context> begin_scope();

    private:
        std::shared_ptr<context> _parent;
        std::map<std::string, std::shared_ptr<object>> _variables;
        
        // disable copy and assignment
        context(const context&) = delete;
        context& operator=(const context&) = delete;
    };
}

#endif // __OPENDRAFT_CORE_RUNTIME_HPP__
