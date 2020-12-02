#include <iostream>
#include <string>

struct List_str
{
    std::string name = "List";
    std::string klass = "0";
    int list_num = 0;
};

std::ostream& operator<< (std::ostream& out, const List_str& list)
{
    out << std::endl;
    out << "List" << list.list_num << " \"" << list.name << "\"" << std::endl;
    out << "Class of the object: " << list.klass << std::endl;
    return out;
}

bool operator!=(const List_str& left, const List_str& right) {
    return left.list_num != right.list_num;
}

template <typename T>
struct list_element
{
    T value;list_element* le_prev = nullptr;list_element* le_next = nullptr;
};

template <typename T>
struct list_struct
{
  list_element<T>* list_begin;list_element<T>* list_end;
};
template <typename T>
T pop_begin(list_struct<T>& l)//уд нач
{
    l.list_end->le_next = l.list_begin->le_next;
    l.list_begin->le_next->le_prev = l.list_end;
    T rez = l.list_begin->value;
    list_element<T>* tmp = new list_element<T>;
    tmp = l.list_begin->le_next;
    delete l.list_begin;
    l.list_begin = tmp;
    return rez;
}

template <typename T>
T pop_end(list_struct<T>& l)//уд кон
{
    l.list_end->le_prev->le_next = l.list_begin;
    l.list_begin->le_prev = l.list_end->le_prev;
    T rez = l.list_end->value;
    list_element<T>* tmp = new list_element<T>;
    tmp = l.list_end->le_prev;
    delete l.list_end;
    l.list_end = tmp;
    return rez;
}

template <typename T>
void constructor_l(list_struct<T>& l)//констр
{
    l.list_begin = nullptr;
    l.list_end = nullptr;
}

template <typename T>
unsigned int size_of_l(list_struct<T>& l)//разм
{
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    if (current == nullptr) return 0;
    else {
        unsigned int counter = 1;
        while (current != l.list_end) {
            counter++;
            current = current->le_next;
        }
        return counter;
    }
}

template <typename T>
void push_begin(list_struct<T>& l, T k)//доб нач
{
    if (l.list_begin == nullptr) {
        list_element<T>* newl_e = new list_element<T>;
        newl_e->value = k;
        l.list_begin = newl_e;
        l.list_end = newl_e;
        newl_e->le_next = newl_e;
        newl_e->le_prev = newl_e;
    }
    else {
        list_element<T>* newRl_e = new list_element<T>;
        newRl_e->value = k;
        l.list_begin->le_prev = newRl_e;
        newRl_e->le_next = l.list_begin;
        l.list_begin = newRl_e;
        l.list_begin->le_prev = l.list_end;
    }
}

template <typename T>
void push_end(list_struct<T>& l, T k)//доб кон
{
    if (l.list_begin == nullptr) {
        list_element<T>* newl_e = new list_element<T>;
        newl_e->value = k;
        l.list_begin = newl_e;
        l.list_end = newl_e;
        newl_e->le_next = newl_e;
        newl_e->le_prev = newl_e;
    }
    else {
       list_element<T>* newl_e = new list_element<T>;
        newl_e->value = k;
        l.list_end->le_next = newl_e;
        newl_e->le_prev = l.list_end;
        l.list_end = newl_e;
        l.list_end->le_next = l.list_begin;
    }
}

template <typename T>
void insert_index(list_struct<T>& l, T n, unsigned int i)// по индексу
{
    unsigned int counter = 0;
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    while (counter != i)
    {
        current = current->le_next;
        ++counter;
    }
    list_element<T>* newl_e = new list_element<T>;
    newl_e->value = n;
    newl_e->le_prev = current->le_prev;
    current->le_prev->le_next = newl_e;
    current->le_prev = newl_e;
    newl_e->le_next = current;
}

template <typename T>
void insert_pointer(list_struct<T>& l, T n, list_element<T>* i)
{list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    while (current != i) current = current->rle_next;
    list_element<T>* newl_e = new list_element<T>;
    newl_e->value = n;
    newl_e->le_prev = current->rle_prev;
    current->rle_prev->rle_next = newl_e;
    current->le_prev = newl_e;
    newl_e->rle_next = current;
}


template <typename T>
T pop_index(list_struct<T>& l, unsigned int i)
{
    unsigned int counter = 0;
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    //std::cout << i << std::endl;
    while (counter != i)
    {
        current = current->le_next;
        //std::cout << counter << "-";
        ++counter;
    }
    T rez = current->value;
    current->le_prev->le_next = current->le_next;
    current->le_next->le_prev = current->le_prev;
    delete current;
    return rez;
}

template <typename T>
T pop_index_pointer(list_struct<T>& l, list_element<T>* i)
{
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    while (current != i) current = current->rle_next;
    T rez = current->value;
    current->rle_prev->rle_next = current->rle_next;
    current->rle_next->rle_prev = current->rle_prev;
    delete current;
    return rez;
}

template <typename T>
T find_value(list_struct<T>& l, unsigned int i)//найти
{
    unsigned int counter = 0;
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    while (counter != i)
    {
        current = current->le_next;
        counter++;
    }
    return current->value;
}

template <typename T>
unsigned int find_pos(list_struct<T>& l, T k)
{
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    unsigned int i = 0;
    while (current->value != k) {
        ++i;
        current = current->le_next;
    }
    return i;
}

template <typename T>
void show_list(list_struct<T>& l)
{
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    unsigned int i = 0;
    std::cout <<"0" << std::endl;
    std::cout << i << ": " << current->value << std::endl;
    ++i;
    while (current != l.list_end) {
        current = current->le_next;
        std::cout << i << ": " << current->value << std::endl;
        ++i;
    }
    std::cout << " nothing" << std::endl;
}

template <typename T>
void destructor_l(list_struct<T>& l)
{
    list_element<T>* current = new list_element<T>;
    current = l.list_begin;
    unsigned int count = size_of_l(l);
    unsigned int counter = 0;
    while (counter != count)
    {
        current = current->le_next;
        delete l.list_begin;
        l.list_begin = current;
        ++counter;
    }
}


int main()
{
    list_struct<int> l0;
    constructor_l(l0);
    push_end(l0, 5);
    push_begin(l0, 13);
    push_begin(l0, 88);
    push_end(l0, 16);
    show_list(l0);
    std::cout << find_pos(l0, 5) << std::endl;
    std::cout << find_value(l0, 45) << std::endl;
    std::cout << size_of_l(l0) << std::endl;
    insert_index(l0, 23, 5);
    push_end(l0, 88);
    show_list(l0);
    std::cout << pop_end(l0) << std::endl;
    std::cout << pop_begin(l0) << std::endl;
    show_list(l0);
    push_end(l0, 13);
    push_end(l0, 24);
    show_list(l0);
    std::cout << size_of_l(l0) << std::endl;
    std::cout << pop_index(l0, 11) << std::endl;
    show_list(l0);
    destructor_l(l0);
    List_str listStr0, listStr1, listStr2, listStr3;
    listStr0.list_num = 7;
    listStr0.name = "19";
    listStr0.klass = "20";
    listStr1.list_num= 96;
    listStr1.name = "21";
    listStr1.klass = "22";
    listStr2.list_num = 159;
    listStr2.name = "23";
    listStr2.klass = "Kobe";
    listStr3.list_num = 949;
    listStr3.name = "25";
    listStr3.klass = "Mamba Mentality";
    list_struct<List_str> l1;
    constructor_l(l1);
    push_begin(l1,listStr0);
    push_end(l1,listStr2 );
    push_begin(l1, listStr2);
    show_list(l1);
    std::cout << find_pos(l1, listStr0) << std::endl;
    std::cout << find_value(l1, 28) << std::endl;
    std::cout << size_of_l(l1) << std::endl;
    insert_index(l1, listStr3, 79);
    show_list(l1);
    std::cout << pop_end(l1);
    std::cout << pop_begin(l1);
    show_list(l1);
    destructor_l(l1);
    return 0;
}