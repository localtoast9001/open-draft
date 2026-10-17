/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 * @file object_storage_impl.hpp
 * @brief Contains the implementations of subclasses of object_storage.
 */
#pragma once
#ifndef __OPEN_DRAFT_PRIVATE_CORE_OBJECT_STORAGE_IMPL_HPP__
#define __OPEN_DRAFT_PRIVATE_CORE_OBJECT_STORAGE_IMPL_HPP__

#include <om.hpp>
#include <concepts>

namespace opendraft::core
{
    template<typename T>
    concept primitive_storage_type =
        std::same_as<T, bool> || std::same_as<T, uint8_t> || std::same_as<T, long> || std::same_as<T, double>;

    template<typename T>
        requires primitive_storage_type<T>
    class primitive_object_storage;

    template<typename T>
        requires primitive_storage_type<T>
    class vector_object_storage;

    class vector_ref_object_storage;

    template<typename T>
        requires primitive_storage_type<T>
    class multi_dimensional_object_storage;

    class multi_dimensional_ref_object_storage;

    /**
     * @brief Storage for a single primitive value.
     */
    template<typename T>
        requires primitive_storage_type<T>
    class primitive_object_storage : public object_storage
    {
    public:
        primitive_object_storage(
            T value)
            : _value(value)
        {
        }

        virtual ~primitive_object_storage() = default;

        long length(long dim) const override
        {
            return 1;
        }

        long get_integer(long ordinal) const override
        {
            if (ordinal != 0)
            {
                throw std::out_of_range("Invalid ordinal for primitive object");
            }

            return (long)_value;
        }
        
        double get_real(long ordinal) const override
        {
            if (ordinal != 0)
            {
                throw std::out_of_range("Invalid ordinal for primitive object");
            }

            return (double)_value;
        }
        
        uint8_t get_byte(long ordinal) const override
        {
            if (ordinal != 0)
            {
                throw std::out_of_range("Invalid ordinal for primitive object");
            }

            return (uint8_t)_value;
        }

        bool get_boolean(long ordinal) const override
        {
            if (ordinal != 0)
            {
                throw std::out_of_range("Invalid ordinal for primitive object");
            }

            return (bool)_value;
        }

        std::string_view get_string(long ordinal) const override
        {
            throw std::logic_error("Invalid access for primitive object");
        }
        
        std::shared_ptr<object> get_object(long ordinal) const override
        {
            throw std::logic_error("Invalid access for primitive object");
        }

    private:
        T _value;
    };

    /**
     * @brief Represents a single dimension array of elements of uniform type or a structured object with fields of uniform type.
     */
    template<typename T>
        requires primitive_storage_type<T>
    class vector_object_storage : public object_storage
    {
    public:
        virtual ~vector_object_storage() = default;

        long length(long dim) const override
        {
            if (dim != 0)
            {
                throw std::out_of_range("Invalid dimension for vector object.");
            }

            return _length;
        }

        long get_integer(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= _length)
            {
                throw std::out_of_range("Invalid ordinal for vectored object.");
            }

            return (long)_data[ordinal];
        }
        
        double get_real(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= _length)
            {
                throw std::out_of_range("Invalid ordinal for vectored object.");
            }

            return (double)_data[ordinal];
        }
        
        uint8_t get_byte(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= _length)
            {
                throw std::out_of_range("Invalid ordinal for vectored object.");
            }

            return (uint8_t)_data[ordinal];
        }

        bool get_boolean(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= _length)
            {
                throw std::out_of_range("Invalid ordinal for vectored object.");
            }

            return (bool)_data[ordinal];
        }

        std::string_view get_string(long ordinal) const override
        {
            if (ordinal != 0 || sizeof(T) != sizeof(uint8_t))
            {
                throw std::logic_error("Invalid access for vectored primitive object.");
            }

            return std::string_view(reinterpret_cast<const char*>(_data), _length);
        }
        
        std::shared_ptr<object> get_object(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= _length)
            {
                throw std::out_of_range("Invalid ordinal for vectored object.");
            }

            return _type_system.create(_data[ordinal]);
        }

        static std::shared_ptr<object_storage> create(
            type_system& ts,
            std::initializer_list<T> values)
        {
            long length = static_cast<long>(values.size());
            auto storage = inner_create(ts, length);
            T* p = storage->_data;
            for (auto e : values)
            {
                *p++ = e;
            }

            return std::shared_ptr<object_storage>(storage);
        }

        static std::shared_ptr<object_storage> create(
            type_system& ts,
            const T* data,
            long length)
        {
            auto storage = inner_create(ts, length);
            const T* src = data;
            const T* end = data + length;
            T* dest = storage->_data;
            for (; src != end; src++)
            {
                *dest++ = *src;
            }

            return std::shared_ptr<object_storage>(storage);
        }

        static std::shared_ptr<object_storage> create(
            type_system& ts,
            long length,
            T value)
        {
            auto storage = inner_create(ts, length);
            T* end = storage->_data + length;
            for (T* p = storage->_data; p != end; ++p)
            {
                *p = value;
            }

            return std::shared_ptr<object_storage>(storage);
        }

    private:
        type_system& _type_system;
        long _length;
        T _data[];

        vector_object_storage(
            type_system& ts,
            long length)
            : _type_system(ts),
              _length(length)
        {
        }

        static vector_object_storage* inner_create(
            type_system& ts,
            long length)
        {
            uint8_t* p = new uint8_t[sizeof(vector_object_storage<T>) + sizeof(T) * length];
            return new (p) vector_object_storage<T>(ts, length);
        }
    };

    inline size_t get_total_element_count(const std::vector<long>& dimensions)
    {
        size_t count = 1;
        for (long dim : dimensions)
        {
            count *= static_cast<size_t>(dim);
        }

        return count;
    }

    /**
     * @brief Storage class for multi-dimensional arrays.
     */
    template<typename T>
        requires primitive_storage_type<T>
    class multi_dimensional_object_storage : public object_storage
    {
    public:
        virtual ~multi_dimensional_object_storage() = default;

        long length(long dim) const override
        {
            if (dim < 0 || dim >= (long)_dimensions.size())
            {
                throw std::out_of_range("Invalid dimension for multi-dimensional object.");
            }

            return _dimensions[dim];
        }

        bool get_boolean(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= get_total_element_count(_dimensions))
            {
                throw std::out_of_range("Invalid ordinal for multi-dimensional object.");
            }

            return static_cast<bool>(_data[ordinal]);
        }

        long get_integer(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= get_total_element_count(_dimensions))
            {
                throw std::out_of_range("Invalid ordinal for multi-dimensional object.");
            }

            return static_cast<long>(_data[ordinal]);
        }

        double get_real(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= get_total_element_count(_dimensions))
            {
                throw std::out_of_range("Invalid ordinal for multi-dimensional object.");
            }

            return static_cast<double>(_data[ordinal]);
        }

        uint8_t get_byte(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= get_total_element_count(_dimensions))
            {
                throw std::out_of_range("Invalid ordinal for multi-dimensional object.");
            }

            return static_cast<uint8_t>(_data[ordinal]);
        }

        std::string_view get_string(long ordinal) const override
        {
            throw new std::logic_error("String access is not supported for this storage type.");
        }

        std::shared_ptr<object> get_object(long ordinal) const override
        {
            if (ordinal < 0 || ordinal >= get_total_element_count(_dimensions))
            {
                throw std::out_of_range("Invalid ordinal for multi-dimensional object.");
            }
            
            return _type_system.create(_data[ordinal]);
        }

        static std::shared_ptr<object_storage> create(
            type_system& ts,
            const std::vector<long>& dimensions,
            T value)
        {
            size_t total_element_count = 0;
            auto storage = inner_create(ts, dimensions, total_element_count);
            T* end = storage->_data + total_element_count;
            for (T* p = storage->_data; p != end; ++p)
            {
                *p = value;
            }

            return std::shared_ptr<object_storage>(storage);
        }

        static std::shared_ptr<object_storage> create(
            type_system& ts,
            const std::vector<long>& dimensions,
            std::initializer_list<T> value)
        {
            size_t total_element_count = get_total_element_count(dimensions);
            if (value.size() != total_element_count)
            {
                throw std::invalid_argument("Initializer list size does not match total element count.");
            }

            return create(ts, dimensions, value.begin());
        }

        static std::shared_ptr<object_storage> create(
            type_system& ts,
            const std::vector<long>& dimensions,
            const T* data)
        {
            size_t total_element_count = 0;
            auto storage = inner_create(ts, dimensions, total_element_count);
            T* end = storage->_data + total_element_count;
            T* dest = storage->_data;
            const T* src = data;
            for (; dest != end; dest++, src++)
            {
                *dest = *src;
            }

            return std::shared_ptr<object_storage>(storage);
        }

    private:
        type_system& _type_system;
        std::vector<long> _dimensions;
        T _data[];

        multi_dimensional_object_storage(
            type_system& ts,
            const std::vector<long>& dimensions)
            : _type_system(ts),
              _dimensions(dimensions)
        {
        }

        static multi_dimensional_object_storage* inner_create(
            type_system& ts,
            const std::vector<long>& dimensions,
            size_t& total_element_count)
        {
            if (dimensions.size() < 2)
            {
                throw std::invalid_argument("Multi-dimensional object must have at least 2 dimensions.");
            }

            total_element_count = get_total_element_count(dimensions);

            uint8_t* p = new uint8_t[sizeof(multi_dimensional_object_storage<T>) + sizeof(T) * total_element_count];
            return new (p) multi_dimensional_object_storage<T>(ts, dimensions);
        }
    };

    /**
     * @brief Storage class for vectors of references.
     */
    class vector_ref_object_storage : public object_storage
    {
    public:
        virtual ~vector_ref_object_storage();

        static std::shared_ptr<object_storage> create(
            long length,
            std::shared_ptr<object> value);

        static std::shared_ptr<object_storage> create(
            std::initializer_list<std::shared_ptr<object>> value);

        static std::shared_ptr<object_storage> create(
            const std::shared_ptr<object>* data,
            long length);

        virtual long length(long dimension) const override;
        virtual long get_integer(long ordinal) const override;
        virtual double get_real(long ordinal) const override;
        virtual uint8_t get_byte(long ordinal) const override;
        virtual bool get_boolean(long ordinal) const override;
        virtual std::string_view get_string(long ordinal) const override;
        virtual std::shared_ptr<object> get_object(long ordinal) const override;        

    private:
        long _length;
        uint8_t _data[];

        vector_ref_object_storage(
            long length,
            const std::shared_ptr<object>& value);

        vector_ref_object_storage(
            const std::shared_ptr<object>* data,
            long length);

        static uint8_t* alloc(long length);

        inline std::shared_ptr<object>* data()
        {
            return reinterpret_cast<std::shared_ptr<object>*>(_data);
        }

        inline const std::shared_ptr<object>* cdata() const
        {
            return reinterpret_cast<const std::shared_ptr<object>*>(_data);
        }
    };

    /**
     * @brief Storage class for multi-dimensional arrays of references.
     */
    class multi_dimensional_ref_object_storage : public object_storage
    {
    public:
        virtual ~multi_dimensional_ref_object_storage();

        static std::shared_ptr<object_storage> create(
            const std::vector<long>& dimensions,
            const std::shared_ptr<object>* data);

        static std::shared_ptr<object_storage> create(
            const std::vector<long>& dimensions,
            const std::shared_ptr<object>& value);

        static std::shared_ptr<object_storage> create(
            const std::vector<long>& dimensions,
            std::initializer_list<std::shared_ptr<object>> values);

        virtual long length(long dimension) const override;
        virtual long get_integer(long ordinal) const override;
        virtual double get_real(long ordinal) const override;
        virtual uint8_t get_byte(long ordinal) const override;
        virtual bool get_boolean(long ordinal) const override;
        virtual std::string_view get_string(long ordinal) const override;
        virtual std::shared_ptr<object> get_object(long ordinal) const override;        

    private:
        std::vector<long> _dimensions;
        uint8_t _data[];

        multi_dimensional_ref_object_storage(
            const std::vector<long>& dimensions,
            const std::shared_ptr<object>* data,
            size_t total_element_count);

        multi_dimensional_ref_object_storage(
            const std::vector<long>& dimensions,
            size_t total_element_count,
            const std::shared_ptr<object>& value);

        size_t total_element_count() const;

        static uint8_t* alloc(const std::vector<long>& dimensions, size_t& total_element_count);

        inline std::shared_ptr<object>* data()
        {
            return reinterpret_cast<std::shared_ptr<object>*>(_data);
        }

        inline const std::shared_ptr<object>* cdata() const
        {
            return reinterpret_cast<const std::shared_ptr<object>*>(_data);
        }
    };
}

#endif // __OPEN_DRAFT_PRIVATE_CORE_OBJECT_STORAGE_IMPL_HPP__