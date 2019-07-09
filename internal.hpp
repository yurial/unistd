#pragma once

#include "internal.hpp"
#include <algorithm>
#include <string>
#include <bitset>

namespace unistd
{
namespace internal
{

template <class T>
class escape_iterator
{
public:
    typedef T container_type;
    typedef std::bitset<256> escape_mask_type;
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

protected:
    container_type& m_container;
    escape_mask_type m_escape_mask;

public:
    inline escape_iterator(container_type& output, const escape_mask_type& mask);
    inline escape_iterator(container_type& output, const std::string& chars);
    inline escape_iterator& operator=(typename container_type::const_reference value);
    inline escape_iterator& operator*();
    inline escape_iterator& operator++();
    inline escape_iterator& operator++(int);
};

template <class T>
escape_iterator<T>::escape_iterator(container_type& container, const escape_mask_type& mask):
        m_container(container),
        m_escape_mask(mask)
    {
    }

template <class T>
escape_iterator<T>::escape_iterator(container_type& container, const std::string& chars):
        m_container(container),
        m_escape_mask()
    {
    std::for_each(chars.begin(), chars.end(), [&](char chr) { m_escape_mask.set(static_cast<unsigned char>(chr)); });
    }

template <class T>
escape_iterator<T>& escape_iterator<T>::operator=(typename container_type::const_reference value)
    {
    if (m_escape_mask.test(static_cast<unsigned char>(value)))
        m_container.push_back('\\');
    m_container.push_back(value);
    return *this;
    }

template <class T>
escape_iterator<T>& escape_iterator<T>::operator*()
    {
    return *this;
    }

template <class T>
escape_iterator<T>& escape_iterator<T>::operator++()
    {
    return *this;
    }

template <class T>
escape_iterator<T>& escape_iterator<T>::operator++(int)
    {
    return *this;
    }

template <typename T = std::string>
T escape(const T& str, const T& chars)
    {
    T result;
    result.reserve(str.size() * 2); // pessimistic allocation
    std::copy(str.begin(), str.end(), internal::escape_iterator<T>(result, chars));
    return result;
    }

std::string escape_posix(const std::string& str);
std::string escape_html(const std::string& str);
// make std::string using vasptrinf
std::string mkstr(const char* fmt, ...);

} // namespace internal
} // namespace unistd

