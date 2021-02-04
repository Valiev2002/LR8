#include <iostream>
#include <string>
struct Lab_8
{
    double x;
    double y;
    double z;
};
std::ostream& operator<< (std::ostream& out, const Lab_8& list_element)
{
    out << std::endl;
    out << "" << list_element.x << " \"" << list_element.y << list_element.z <<"\"" << std::endl;
    return out;
}
bool operator!=(const Lab_8 &left, const Lab_8 &right) {
    return left.x != right.x;
}
template <typename T>
struct Element//структура для каждогог отдельного элемента
{
    Element* le_prev = nullptr;//указатель на предыдущий элемент
    Element* le_next = nullptr;//указатель на следующий элемент
    T value{};//значение
};
template <typename T>
struct List//главная структура
{
    Element<T>* l_begin;//указаткль на первый элемент
    Element<T>* l_end;//указатель на последний элемент
};
template <typename T>
void constructor_List(List<T>& l)
{
    l.l_begin = nullptr;
    l.l_end = nullptr;
}
template <typename T>
void destructor_List(List<T>& l)
{
    if (l.l_begin == nullptr) {
        return;
    }
    auto *next=l.l_begin;
    auto *next2=next->le_next;
    while(next2!=nullptr)
    {
        delete next;
        next=next2;
        next2=next2->le_next;
    }
    delete next;
    l.l_begin =nullptr;
}
template <typename T>
unsigned int count_of_elements(List<T>& l)
{
    Element<T>* current;
    current = l.l_begin;
    if (current == nullptr)
        return 0;
    else {
        unsigned int counter = 1;
        while (current != l.l_end) {
            counter++;
            current = current->le_next;
        }
        return counter;
    }
}
template <typename T>
void push_begin(List<T>& l, T n)
{
    auto* newList = new Element<T>;
    newList->value = n;
    if (l.l_begin == nullptr) {
        l.l_begin = newList;
        l.l_end = newList;
        newList->le_next = newList;
        newList->le_prev = newList;
    }
    else {
        l.l_begin->le_prev = newList;
        newList->le_next = l.l_begin;
        l.l_begin = newList;
        l.l_begin->le_prev = l.l_end;
    }
}
template <typename T>
void push_back(List<T>& l, T n)
{
    auto* newList = new Element<T>;
    newList->value = n;
    if (l.l_begin == nullptr) {
        l.l_begin = newList;
        l.l_end = newList;
        newList->le_next = newList;
        newList->le_prev = newList;
    }
    else {
        l.l_end->le_next = newList;
        newList->le_prev = l.l_end;
        l.l_end = newList;
        l.l_end->le_next = l.l_begin;
    }
}
template <typename T>
void insert_index(List<T>& l, T n, unsigned int i)
{
    unsigned int counter = 0;
    Element<T>* current;
    current = l.l_begin;
    while (counter != i)
    {
        current = current->le_next;
        ++counter;
    }
    auto* newList = new Element<T>;
    newList->value = n;
    newList->le_prev = current->le_prev;
    current->le_prev->le_next = newList;
    current->le_prev = newList;
    newList->le_next = current;
}
template <typename T>
T pop_begin(List<T>& l)
{
    l.l_end->le_next = l.l_begin->le_next;
    l.l_begin->le_next->le_prev = l.l_end;
    T rez = l.l_begin->value;
    Element<T>* tmp;
    tmp = l.l_begin->le_next;
    delete l.l_begin;
    l.l_begin = tmp;
    return rez;
}
template <typename T>
T pop_back(List<T>& l)
{
    l.l_end->le_prev->le_next = l.l_begin;
    l.l_begin->le_prev = l.l_end->le_prev;
    T rez = l.l_end->value;
    Element<T>* tmp;
    tmp = l.l_end->le_prev;
    delete l.l_end;
    l.l_end = tmp;
    return rez;
}
template <typename T>
T pop_index(List<T>& l, unsigned int i)
{
    unsigned int counter = 0;
    Element<T>* current;
    current = l.l_begin;
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
T find_value(List<T>& l, unsigned int i)
{
    unsigned int counter = 0;
    Element<T>* current;
    current = l.l_begin;
    while (counter != i)
    {
        current = current->le_next;
        counter++;
    }
    return current->value;
}
template <typename T>
unsigned int find_pos(List<T>& l, T n)
{
    Element<T>* current;
    current = l.l_begin;
    unsigned int i = 0;
    while (current->value != n) {
        ++i;
        current = current->le_next;
    }
    return i;
}
template <typename T>
void print(List<T>& l)
{
    if (l.l_begin == nullptr)
    {
        std::cout << "List is empty" << std::endl;
    }
    else
    {
        Element<T>* current;
        current = l.l_begin;
        unsigned int i = 0;
        std::cout << i << ": " << current->value << std::endl;
        ++i;
        while (current != l.l_end) {
            current = current->le_next;
            std::cout << i << ": " << current->value << std::endl;
            ++i;
        }
    }
}
int main()
{
    List<double> l{};
    constructor_List(l);
    destructor_List(l);
    print(l);
    push_back(l, 3.5);
    push_begin(l, 1.0);
    push_begin(l, 5.5);
    push_back(l, 32.7);
    print(l);
    std::cout << find_pos(l, 32.7) << std::endl;
    std::cout << find_value(l, 3.5) << std::endl;
    std::cout << count_of_elements(l) << std::endl;
    insert_index(l, 10.0, 3.5);
    push_back(l, 256.3);
    print(l);
    std::cout << pop_back(l) << std::endl;
    std::cout << pop_begin(l) << std::endl;
    print(l);
    push_back(l, 36.6);
    push_back(l, 4.9);
    print(l);
    std::cout << count_of_elements(l) << std::endl;
    std::cout << pop_index(l, 3) << std::endl;
    print(l);
    //проверка для пользовательского типа
    Lab_8 val1{};
    Lab_8 val2{};
    Lab_8 val3{};
    Lab_8 val4{};//структуры,которые добавляются в список
    val1.x = 1.5;
    val1.y = 2.5;
    val1.z = 3.5;
    val2.x = 8.0;
    val2.y=1.0;
    val2.z = 3.7;
    val3.x = 5.5;
    val3.y = 6.4;
    val3.z = 7.8;
    val4.x = 8.2;
    val4.y = 3.1;
    val4.z = 7.6;
    List<Lab_8> l1{};
    constructor_List(l1);
    destructor_List(l1);
    push_begin(l1, val1);
    push_back(l1, val2);
    push_begin(l1, val3);
    print(l1);
    std::cout << find_pos(l1, val1) << std::endl;
    std::cout << find_value(l1, 36) << std::endl;
    std::cout << count_of_elements(l1) << std::endl;
    insert_index(l1, val4, 57);
    print(l1);
    std::cout << pop_back(l1);
    std::cout << pop_begin(l1);
    print(l1);
    return 0;
}