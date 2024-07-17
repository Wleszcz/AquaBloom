#include "headers/page.h"

t_page::t_page(int page_number, t_page_type type)
    : page_number(page_number), type(type) {}

t_page &t_page::operator=(int value)
{
    page_number = value;
    type = static_cast<t_page_type>(value);

    return *this;
}

t_page &t_page::operator=(t_page_type value)
{
    page_number = static_cast<int>(value);
    type = value;

    return *this;
}

bool t_page::operator==(const t_page_type& other) const {
    return  type == other;
}