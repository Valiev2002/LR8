#include <iostream>
template <class T>
struct List_above_Student{
List_above_Student<T>*previos;
List_above_Student<T>*next;
T value;
};
template<class T>
struct List_of_group{
    List_above_Student<T>*first;
    int size;
};
template<class T>
void constructor(List_of_group<T>&list)
{
    list.size=0;
    list.first=nullptr;
}
template<class T>
void destructor(List_of_group<T>&list){
    for (int i = 1; i < list.size; i++)
    {
        list.first = list.first->next;
        delete list.first->previos;
    }
    delete list.first;
    list.first = nullptr;
    list.size = 0;
}
template<typename T>
int size(List_of_group<T>& list)
{
    return list.size;
}
template <class T>
void push_front(List_of_group<T>&list,T value){
    auto*ptr = new List_above_Student<T>;
    ptr->value = value;
    if (list.first == nullptr)
    {
        list.first = ptr;
        ptr->next = ptr;
        ptr->previos = ptr;
    }
    else
    {
        list.first->previos->next = ptr;
        ptr->previos = list.first->previos;
        list.first->previos = ptr;
        ptr->next = list.first;
        list.first = ptr;
    }
    list.size++;
}
template<typename T>
void push_back(List_of_group<T>&list,T value)
{
    auto*ptr = new List_above_Student<T>;
    ptr->value = value;
    if (list.first == nullptr)
    {
        list.first = ptr;
        ptr->next = ptr;
        ptr->previos = ptr;
    }
    else
    {
        list.first->previos->next = ptr;
        ptr->previos = list.first->previos;
        list.first->previos = ptr;
        ptr->next = list.first;
    }
    list.size++;
}
template <typename T>
void insert_index(List_of_group<T>& list, T data, int index)
{
    auto* ptr = new List_above_Student<T>;
    ptr->next = list.first;
    ptr->value = data;
    for (int i = 0; i < index; ++i)
    {
        ptr->next = ptr->next->next;
    }
    ptr->previos = ptr->next->previos;
    ptr->next->previos = ptr;
    ptr->previos->next = ptr;
    list.size++;
}
template <typename T>
void print(List_of_group<T>& list)
{
    List_above_Student<T>* a = list.first;
    for (int i = 0; i < list.size; ++i)
    {
        std::cout << a->value << ' ';
        a = a->next;
    }
}
template <typename T>
void insert_pointer
        (List_of_group<T>& list, T data, List_above_Student<T>* z)
{
    auto* ptr = new List_above_Student<T>;
    ptr->value = data;
    ptr->next = z->next;
    ptr->previos = z;
    ptr->next->previos = ptr;
    ptr->previos->next = ptr;
    list.size++;
}
template<typename T>
T pop_first(List_of_group<T>& list)
{
    T data;
    if (list.first != nullptr)
    {
        List_above_Student<T>* z = list.first;
        list.first->previos->next = list.first->next;
        list.first = list.first->next;
        list.first->previos = z->previos;
        data = z->value;
        delete z;
        list.size--;
    }
    return data;
}
template<typename T>
T pop_end(List_of_group<T>& list)
{
    T data;
    if (list.first != nullptr)
    {
        List_above_Student<T>* z = list.first->previos;
        list.first->previos = list.first->previos->previos;
        list.first->previos->next = list.first;
        data = z->value;
        delete z;
        list.size--;
    }
    return data;
}
template <typename T>
T get(List_of_group<T>& list, int index)
{
    T data;
    List_above_Student<T>* ptr = list.first;
    for (int i = 0; i < index; ++i)
    {
        ptr = ptr->next;
    }
    if (ptr != nullptr)
    {
        ptr->next->previos = ptr->previos;
        ptr->previos->next = ptr->next;
        data = ptr->value;
        delete ptr;
        list.size--;
    }
    return data;
}
template <typename T>
T get_by_pointer(List_of_group<T>& list, List_above_Student<T>* a)
{
    T data;
    List_above_Student<T>* ptr;
    if (a == list.first)
    {
        a = list.first->next;
    }
    if (a != nullptr)
    {
        ptr = a;
        ptr->next->previos = ptr->previos;
        ptr->previos->next = ptr->next;
        data = ptr->value;
        delete ptr;
        list.size--;
    }
    return data;
}

template <typename T>
T get_by_index(List_of_group<T>& list, int index)
{
    T data;
    List_above_Student<T>* ptr = list.first;
    if (ptr != nullptr)
    {
        for (int i = 0; i < index; ++i)
        {
            ptr = ptr->next;
        }
        data = ptr->value;
        std::cout << data << std::endl;
    }
    return data;
}
int main() {
    List_of_group<int> group{};
    constructor(group);
    destructor(group);
    size(group);
    push_front(group, 5);
    push_back(group, 3);
    int index = 3;
    insert_index(group, 3, index);
    print(group);
    insert_pointer(group,4,group.first->next->next);
    insert_index(group,13,14);
    get(group,index);
    get_by_index(group,2);
    get_by_pointer(group,group.first);
    pop_end(group);
    pop_first(group);
}