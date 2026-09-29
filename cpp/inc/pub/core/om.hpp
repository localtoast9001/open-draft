/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file om.hpp
 * @brief Contains the declarations for the object model and type system.
# */

#pragma once

#ifndef __OPEN_DRAFT_CORE_OM_HPP__
#define __OPEN_DRAFT_CORE_OM_HPP__

#include <memory>
#include <string_view>
#include <map>

namespace opendraft::core
{
    // forward declarations.
    class type;
    class object;
    class type_system;

    /**
     * Core representation of data. 
     */
    class object
    {
    public:
        ~object();

        inline const type& type() const
        {
            return *_type;
        }

        /**
         * @brief Gets the length of the object along the specified dimension.
         * @param dim The dimension for which to get the length.
         * @return The length of the object along the specified dimension.
         */
        long length(long dim) const;

        constexpr long length() const
        {
            return length(0);
        }

        long get_integer(long ordinal) const;
        double get_real(long ordinal) const;
        uint8_t get_byte(long ordinal) const;
        bool get_boolean(long ordinal) const;
        std::string_view get_string(long ordinal) const;

        std::shared_ptr<object> get_object(long ordinal) const;

        static std::shared_ptr<object> create(bool value);
        static std::shared_ptr<object> create(long value);
        static std::shared_ptr<object> create(double value);
        static std::shared_ptr<object> create(uint8_t value);
        static std::shared_ptr<object> create(const char* value);

    private:
        std::shared_ptr<opendraft::core::type> _type;
        long _length;
        uint8_t _data[];

        object(const object&) = delete;
        object& operator=(const object&) = delete;
    };

    /**
     * @brief Represents the different kinds of types in the object model.
     */
    enum type_kind
    {
        // Default invalid type.
        TYPE_KIND_INVALID = 0,
        
        // Primitive types like int, float, etc.
        TYPE_KIND_PRIMITIVE,
        
        // User-defined classes.
        TYPE_KIND_CLASS,
        
        // Arrays of other types.
        TYPE_KIND_ARRAY,
        
        // Function pointers or callable objects.
        TYPE_KIND_DELEGATE,
        
        // Bindings of delegates to specific instances.
        TYPE_KIND_DELEGATE_BINDING,
        
        // Key-value collections.
        TYPE_KIND_DICTIONARY,
        
        // Interfaces defining contracts for classes.
        TYPE_KIND_INTERFACE,
    };

    /**
     * @brief Represents a type in the object model.
     */
    class type
    {
    public:
        virtual ~type() = default;

        inline const std::string& name() const
        {
            return _name;
        }

        /**
         * @brief Gets the kind of the type.
         * @return The kind of the type.
         */
        virtual type_kind kind() const = 0;

        /**
         * @brief Gets the number of dimensions of the type.
         * @return The number of dimensions of the type.
         */
        virtual size_t dimension_count() const;

    protected:
        inline type(const std::string& name)
            : _name(name)
        {
        }

    private:
        std::string _name;

        type(const type&) = delete;
        type& operator=(const type&) = delete;
    };

    /**
     * @brief Represents the different kinds of primitive types in the object model.
     */
    enum primitive_kind
    {
        PRIMITIVE_KIND_INVALID = 0,
        PRIMITIVE_KIND_BOOLEAN,
        PRIMITIVE_KIND_INTEGER,
        PRIMITIVE_KIND_REAL,
        PRIMITIVE_KIND_BYTE,
        PRIMITIVE_KIND_STRING,
    };

    /**
     * @brief Represents a primitive type in the object model.
     */
    class primitive_type : public type
    {
    public:
        primitive_type(const std::string& name, core::primitive_kind kind);
        virtual ~primitive_type() = default;
        
        inline primitive_kind primitive_kind() const
        {
            return _kind;
        }

        type_kind kind() const override;

    private:
        core::primitive_kind _kind;
    };

    /**
     * @brief Represents a user-defined class type in the object model.
     */
    class class_type : public type
    {
    public:
        class_type(const std::string& name);
        virtual ~class_type() = default;

        type_kind kind() const override;

    private:
    };

    /**
     * @brief Represents an array type in the object model.
     */
    class array_type : public type
    {
    public:
        array_type(
            const std::string& name,
            const std::shared_ptr<type>& element_type,
            size_t dimension_count = 1);

        virtual ~array_type() = default;

        type_kind kind() const override;

        virtual size_t dimension_count() const override;

        inline const std::shared_ptr<type>& element_type() const
        {
            return _element_type;
        }

    private:
        std::shared_ptr<type> _element_type;
        size_t _dimension_count;
    };

    /**
     * @brief Represents the singleton type system in the object model.
     */
    class type_system
    {
    public:
        static type_system instance;

        type_system();
        ~type_system() = default;

        inline const std::shared_ptr<type>& boolean_type() const
        {
            return _boolean_type;
        }

        inline const std::shared_ptr<type>& integer_type() const
        {
            return _integer_type;
        }

        inline const std::shared_ptr<type>& real_type() const
        {
            return _real_type;
        }

        inline const std::shared_ptr<type>& byte_type() const
        {
            return _byte_type;
        }

        inline const std::shared_ptr<type>& string_type() const
        {
            return _string_type;
        }

        std::shared_ptr<type> get_type_by_name(const std::string& name) const;

        std::shared_ptr<type> get_array_type(
            const std::shared_ptr<type>& element_type,
            size_t dimension_count = 1);

    private:
        std::shared_ptr<type> _boolean_type;
        std::shared_ptr<type> _integer_type;
        std::shared_ptr<type> _real_type;
        std::shared_ptr<type> _byte_type;
        std::shared_ptr<type> _string_type;
        std::map<std::string, std::shared_ptr<type>> _types_by_name;
        
        type_system(const type_system&) = delete;
        type_system& operator=(const type_system&) = delete;
    };
}

#endif /* __OPEN_DRAFT_CORE_OM_HPP__ */
