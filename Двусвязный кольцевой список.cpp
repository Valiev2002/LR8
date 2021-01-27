#include <iostream>
#include <string>
//Cмысл  данного списка
// Есть как бы главная структура List в которой хранятся указатели на начало и конец списка
//Есть еще одна структура,для каждого отдельного элемента списка(не включая начало и конец)
// внем мы запоминаем указатели на следующий и предыдущий элемент и также значение,которое хранится в нем
//через оператор new создаю новую структуру(динамическую) какого то элемента
// и обновляю значение первого и последнего элемента в главной структуре

//для пользователя
struct Lab_8
{
    std::string s;
    int aya = 3;
};
std::ostream& operator<< (std::ostream& out, const Lab_8& list_element)
{
    out << std::endl;
    out << "" << list_element.aya << " \"" << list_element.s << "\"" << std::endl;
    return out;
}
bool operator!=(const Lab_8 &left, const Lab_8 &right) {
    return left.aya != right.aya;
}
//хватит пользоваться
template <typename T>
struct Element//структура для каждогог отдельного элемента
{
    Element* le_prev = nullptr;//указатель на предыдущий элемент
    Element* le_next = nullptr;//указатель на следующий элемент
    T value;//значение

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
unsigned int size_of_ls(List<T>& l)
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

  Element<T>* newList = new Element<T>;
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
void push_end(List<T>& l, T n)
{

   Element<T>* newList = new Element<T>;
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
    Element<T>* newList = new Element<T>;
    newList->value = n;
    newList->le_prev = current->le_prev;
    current->le_prev->le_next = newList;
    current->le_prev = newList;
    newList->le_next = current;
}

template <typename T>
void insert_pointer(List<T>& l, T n, List<T>* k)
{
    List<T>* current;
    current = l.rl_begin;
    while (current != k) current = current->rle_next;
    current = current->rle_next;
    Element<T>* newList = new List<T>;
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
T pop_end(List<T>& l)
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
T pop_index_pointer(List<T>& l, List<T>* i)
{
    List<T>* current;
    current = l.l_begin;
    while (current != i) current = current->rle_next;
    T rez = current->value;
    current->rle_prev->rle_next = current->rle_next;
    current->rle_next->rle_prev = current->rle_prev;
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
void show_list(List<T>& l)
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
        std::cout << "0-0" << std::endl;
        std::cout << i << ": " << current->value << std::endl;
        ++i;
        while (current != l.l_end) {
            current = current->le_next;
            std::cout << i << ": " << current->value << std::endl;
            ++i;
        }
        std::cout << "--------------" << std::endl;
    }
}

template <typename T>
void destructor_l(List<T>& l)
{
    Element<T>* current;
    current = l.l_begin;
    while (current != l.l_end)
    {
        current = current->le_next;
        delete l.l_begin;
        l.l_begin = current;
    }
    delete current;
}

int main()
{
    //проверка для int
    List<int> l;
    constructor_List(l);
    show_list(l);
    push_end(l, 3);
    push_begin(l, 1);
    push_begin(l, 17);
    push_end(l, 13);
    show_list(l);
    std::cout << find_pos(l, 3) << std::endl;
    std::cout << find_value(l, 3) << std::endl;
    std::cout << size_of_ls(l) << std::endl;
    insert_index(l, 42, 3);
    push_end(l, 93);
    show_list(l);
    std::cout << pop_end(l) << std::endl;
    std::cout << pop_begin(l) << std::endl;
    show_list(l);
    push_end(l, 38);
    push_end(l, 48);
    show_list(l);
    std::cout << size_of_ls(l) << std::endl;
    std::cout << pop_index(l, 3) << std::endl;
    show_list(l);
    destructor_l(l);
    //проверка для пользовательского типа
    Lab_8 val1,val2,val3,val4;//структуры,которые добавляются в список
    val1.aya = 1;
    val1.s = "NE CHUVSTVUYU";
    val2.aya = 2;
    val2.s = "MOZG";
    val3.s =3;
    val3.s = "YA";
    val4.aya = 4;
    val4.s = "USTAL";
    List<Lab_8> l1;
    constructor_List(l1);
    push_begin(l1, val1);
    push_end(l1, val2);
    push_begin(l1, val3);
    show_list(l1);
    std::cout << find_pos(l1, val1) << std::endl;
    std::cout << find_value(l1, 36) << std::endl;
    std::cout << size_of_ls(l1) << std::endl;
    insert_index(l1, val4, 57);
    show_list(l1);
    std::cout << pop_end(l1);
    std::cout << pop_begin(l1);
    show_list(l1);
    destructor_l(l1);
    return 0;
}