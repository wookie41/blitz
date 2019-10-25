#pragma once

namespace blitz
{
    template <typename T>
    struct ListNode
    {
        T* node;
        ListNode<T>* next;
    };
}