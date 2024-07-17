#ifndef T_PAGE_H
#define T_PAGE_H

#include <string>

enum t_page_type {
    MAIN_PAGE = 0,
    PLANT_PAGE = 1,
    ON_OFF_TIME_SET_PAGE = 2,
    NET_INFO_PAGE = 3
};

struct t_page {
    int page_number;
    t_page_type type;
    t_page(int page_number = 0, t_page_type type = MAIN_PAGE);
    t_page& operator=(int value);
    t_page& operator=(t_page_type type);
    bool operator==(const t_page_type& other) const;
};

#endif // T_PAGE_H
