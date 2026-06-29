/**
 * @file source_reference.cpp
 * @brief Contains the definitions for the source_reference class and related functions.
 */
#include "source_reference.hpp"
#include <sstream>

namespace opendraft
{
    namespace lang
    {
        source_reference::source_reference()
            : _path(), 
            _line(0), 
            _column(0),
            _end_line(0),
            _end_column(0)
        {
        }

        /**
         * @brief Constructs a new source_reference object.
         * @param path The path to the source file.
         * @param line The starting line number.
         * @param column The starting column number.
         * @param end_line The ending line number.
         * @param end_column The ending column number.
         */
        source_reference::source_reference(
            const std::string& path,
            int line /* = 0 */,
            int column /* = 0 */,
            int end_line /* = 0 */,
            int end_column /* = 0 */)
            : _path(path), 
            _line(line), 
            _column(column), 
            _end_line(end_line > 0 ? end_line : line), 
            _end_column(end_column > 0 ? end_column : column)
        {
        }

        /**
         * @brief Converts the source_reference object to a string representation.
         * @return A string representation of the source_reference object.
         */
        std::string source_reference::to_string() const
        {
            std::ostringstream oss;
            oss << _path;
            if (_line > 0)
            {
                oss << ":" << _line;
                if (_column > 0)
                {
                    oss << ":" << _column;
                }
            }
            if (_end_line != _line || _end_column != _column)
            {
                oss << "-" << _end_line;
                if (_end_column > 0)
                {
                    oss << ":" << _end_column;
                }
            }

            return oss.str();
        }
    }
}