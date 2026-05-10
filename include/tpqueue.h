// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>
template<typename T>
class TPQueue {
 private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;  // указатель на начало очереди
    int count;   // количество элементов в очереди

 public:
    // Конструктор
    TPQueue() : head(nullptr), count(0) {}
    // Деструктор
    ~TPQueue() {
        while (!isEmpty()) {
            pop();
        }
    }
    // Проверка на пустоту
    bool isEmpty() const {
        return head == nullptr;
    }
    // Получение количества элементов
    int size() const {
        return count;
    }
    // Добавление элемента с учетом приоритета (O(n))
    void push(const T& item) {
        Node* newNode = new Node(item);
        // Если очередь пуста или новый элемент имеет наивысший приоритет
        if (isEmpty() || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
        } else {
            // Поиск места для вставки (сохраняем порядок для равных приоритетов)
            Node* current = head;
            while (current->next != nullptr && current->next->data.prior >= item.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
    }
    // Извлечение элемента из начала очереди (O(1))
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("TPQueue is empty");
        }
        Node* temp = head;
        T result = head->data;
        head = head->next;
        delete temp;
        count--;
        return result;
    }
    // Просмотр первого элемента без извлечения
    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("TPQueue is empty");
        }
        return head->data;
    }
    // Очистка очереди
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
    // Запрещаем копирование
    TPQueue(const TPQueue&) = delete;
    TPQueue& operator=(const TPQueue&) = delete;
    // Разрешаем перемещение
    TPQueue(TPQueue&& other) noexcept
        : head(other.head), count(other.count) {
        other.head = nullptr;
        other.count = 0;
    }
    TPQueue& operator=(TPQueue&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
