#include <iterator>
#include <algorithm>
#include <functional>

namespace drmatters {
template <typename BidirIt, typename Compare = std::less<>>
void merge_sort(BidirIt first, BidirIt last, Compare cmp = Compare {})
{
    const auto n = std::distance(first, last);
    
    if (n > 1) {
        const auto middle = std::next(first, n / 2);
        
        merge_sort(first, middle, cmp);
        merge_sort(middle, last, cmp);
        
        std::inplace_merge(first, middle, last, cmp);
    }
}
}