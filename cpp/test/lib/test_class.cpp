/**
 * Implementation of the base class for unit tests.
 */
#include <testfx.hpp>
#include <iostream>

namespace testfx
{
    test_class* test_class::_head = nullptr;

    void test_class::init_instances(std::map<std::string, test_class*>& instances)
    {
        test_class* current = _head;
        while (current)
        {
            instances[current->name()] = current;
            current = current->_next;
        }
    }
    
    test_class::test_class(const std::string& name)
        : _name(name), _context(nullptr)
    {
        _next = _head;
        _head = this;
    }

    void test_class::init(test_context& context)
    {
        _context = &context;
    }

    test_context& test_class::context() const
    {
        if (!_context)
        {
            throw assert_exception("Test context is not initialized.");
        }

        return *_context;
    }

    void test_class::add(const std::string& name, test_method method)
    {
        // Implementation for adding a test method
        _tests[name] = method;
    }
}