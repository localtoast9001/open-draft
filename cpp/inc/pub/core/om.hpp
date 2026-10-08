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
#include <initializer_list>
#include <vector>

namespace opendraft::core
{
    // forward declarations.
    class type;
    class object;
    class object_storage;
    class type_system;

    /**
     * @brief Underlying storage for an object.
     */
    class object_storage
    {
    public:
        virtual ~object_storage() = default;

        /**
         * @brief Gets the length of the object along the specified dimension.
         * @param dim The dimension for which to get the length.
         * @return The length of the object along the specified dimension.
         */
        virtual long length(long dim) const = 0;

        constexpr long length() const
        {
            return length(0);
        }

        virtual long get_integer(long ordinal) const = 0;
        virtual double get_real(long ordinal) const = 0;
        virtual uint8_t get_byte(long ordinal) const = 0;
        virtual bool get_boolean(long ordinal) const = 0;
        virtual std::string_view get_string(long ordinal) const = 0;

        virtual std::shared_ptr<object> get_object(long ordinal) const = 0;
    };

    /**
     * Core representation of data. 
     */
    class object
    {
    public:
        ~object() = default;

        inline const type& type() const
        {
            return *_type;
        }

        inline const object_storage& storage() const
        {
            return *_storage;
        }

        object(
            const std::shared_ptr<opendraft::core::type>& type,
            const std::shared_ptr<object_storage>& storage)
            : _type(type), _storage(storage)
        {
        }

    private:
        std::shared_ptr<opendraft::core::type> _type;
        std::shared_ptr<object_storage> _storage;

        // Disable copy and assignment.
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
        
        // Interface contracts for classes.
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
     * @brief Represents a field in a user-defined class.
     */
    class field
    {
    public:
        field(
            const std::string& name, 
            const std::shared_ptr<type>& field_type);
        ~field() = default;
        field(const field&) = default;
        field(field&&) = default;

        field& operator=(const field&) = default;
        field& operator=(field&&) = default;

        inline const std::string& name() const
        {
            return _name;
        }

        inline const std::shared_ptr<type>& field_type() const
        {
            return _field_type;
        }

    private:
        std::string _name;
        std::shared_ptr<type> _field_type;
    };

    /**
     * @brief A parameter declaration in a template or function.
     */
    class parameter_declaration
    {
    public:
        parameter_declaration(
            const std::string& name,
            const std::shared_ptr<core::type>& type);
        ~parameter_declaration() = default;
        parameter_declaration(const parameter_declaration&) = default;
        parameter_declaration(parameter_declaration&&) = default;

        parameter_declaration& operator=(const parameter_declaration&) = default;
        parameter_declaration& operator=(parameter_declaration&&) = default;

        inline const std::string& name() const
        {
            return _name;
        }

        inline const std::shared_ptr<core::type>& type() const
        {
            return _type;
        }

    private:
        std::string _name;
        std::shared_ptr<core::type> _type;
    };

    /**
     * @brief Base declaration for functions and templates.
     */
    class method_declaration
    {
    public:
        inline const std::string& name() const
        {
            return _name;
        }

        inline const std::vector<parameter_declaration>& parameters() const
        {
            return _parameters;
        }

    protected:
        method_declaration(
            const std::string& name,
            const std::vector<parameter_declaration>& parameters);
        virtual ~method_declaration() = default;

    private:
        std::string _name;
        std::vector<parameter_declaration> _parameters;
    };

    /**
     * @brief Represents a function declaration in the object model.
     */
    class function_declaration : public method_declaration
    {
    public:
        function_declaration(
            const std::string& name,
            const std::vector<parameter_declaration>& parameters,
            const std::shared_ptr<core::type>& return_type);

        inline const std::shared_ptr<core::type>& return_type() const
        {
            return _return_type;
        }

    private:
        std::shared_ptr<core::type> _return_type;
    };

    /**
     * @brief Represents a template declaration in the object model.
     */
    class template_declaration : public method_declaration
    {
    public:
        template_declaration(
            const std::string& name,
            const std::vector<parameter_declaration>& parameters);
    };

    /**
     * @brief Represents a user-defined class type in the object model.
     */
    class class_type : public type
    {
    public:
        class_type(
            const std::string& name,
            const std::shared_ptr<type>& base_type,
            std::initializer_list<field> fields,
            std::initializer_list<field> static_fields,
            std::initializer_list<std::shared_ptr<method_declaration>> methods,
            std::initializer_list<std::shared_ptr<method_declaration>> static_methods);
        virtual ~class_type() = default;

        type_kind kind() const override;

        inline const std::vector<field>& fields() const
        {
            return _fields;
        }

        inline const std::vector<std::shared_ptr<method_declaration>>& methods() const
        {
            return _methods;
        }

        inline const std::vector<std::shared_ptr<method_declaration>>& static_methods() const
        {
            return _static_methods;
        }

        inline const std::vector<field>& static_fields() const
        {
            return _static_fields;
        }

    private:
        std::shared_ptr<type> _base_type;
        std::vector<field> _fields;
        std::vector<field> _static_fields;
        std::vector<std::shared_ptr<method_declaration>> _methods;
        std::vector<std::shared_ptr<method_declaration>> _static_methods;
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

        /**
         * @brief Creates an object representing a boolean value.
         */
        std::shared_ptr<object> create(bool value);

        /**
         * @brief Creates an object representing an integer value.
         */
        std::shared_ptr<object> create(long value);

        /**
         * @brief Creates an object representing a real (double) value.
         */
        std::shared_ptr<object> create(double value);

        /**
         * @brief Creates an object representing a byte (uint8_t) value.
         */
        std::shared_ptr<object> create(uint8_t value);

        /**
         * @brief Creates an object representing a string value.
         */
        std::shared_ptr<object> create(const char* value);

        /**
         * @brief Creates an object representing a string value.
         */
        std::shared_ptr<object> create(const std::string_view& value);

        /**
         * @brief Creates an object representing an array of boolean values.
         */
        std::shared_ptr<object> create(std::initializer_list<bool> value);

        /**
         * @brief Creates an object representing an array of integer values.
         */
        std::shared_ptr<object> create(std::initializer_list<long> value);

        /**
         * @brief Creates an object representing an array of real (double) values.
         */
        std::shared_ptr<object> create(std::initializer_list<double> value);

        /**
         * @brief Creates an object representing an array of byte (uint8_t) values.
         */
        std::shared_ptr<object> create(std::initializer_list<uint8_t> value);

        /**
         * @brief Creates an object representing an array of objects of a specified type or a complex type.
         */
        std::shared_ptr<object> create(
            const std::shared_ptr<core::type>& type,
            std::initializer_list<std::shared_ptr<object>> values);

        /**
         * @brief Creates an object representing a multi-dimensional array of boolean values.
         */
        std::shared_ptr<object> create(
            std::initializer_list<long> dimensions,
            std::initializer_list<bool> value);

        /**
         * @brief Creates an object representing a multi-dimensional array of integer values.
         */
        std::shared_ptr<object> create(
            std::initializer_list<long> dimensions,
            std::initializer_list<long> value);

        /**
         * @brief Creates an object representing a multi-dimensional array of real (double) values.
         */
        std::shared_ptr<object> create(
            std::initializer_list<long> dimensions,
            std::initializer_list<double> value);

        /**
         * @brief Creates an object representing a multi-dimensional array of byte (uint8_t) values.
         */
        std::shared_ptr<object> create(
            std::initializer_list<long> dimensions,
            std::initializer_list<uint8_t> value);
            
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
