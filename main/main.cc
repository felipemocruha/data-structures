#include <iostream>
#include <string>
#include <vector>

//#include <memory>
//#include <functional>

// TODO:
// - move semantics e ownership
// - destructors
// - inicializacao com {} e o que significa usar ":"

template <typename T>
class ListNode {
public:
  T value;
  std::unique_ptr<ListNode> next;

  ListNode(const T& val) {
    value = val;
    next = nullptr;
  }
};

template <typename T>
class LinkedList {
public:
  std::unique_ptr<ListNode<T>> head;

  LinkedList() {
    head = nullptr;
  }
  ~LinkedList() = default;

  void push(const T& value) {
    auto node = std::make_unique<ListNode<T>>(value);
    if (!head) {
      head = std::move(node);
      return;
    }

    node->next = std::move(head);
    head = std::move(node);
  }

  void print() {
    if (!head) {
      std::cout << "[]" << std::endl;
      return;
    }

    auto count = 0;
    auto index = head.get();
    while (index) {
      if (count == 0) std::cout << "[ ";
      std::cout << index->value << " ";
      index = index->next.get();
      count++;
    }
    std::cout << "]" << std::endl;
  }
};

#define VECTOR_DEFAULT_SIZE 1024

template <typename T>
class Vector {
public:
  int64_t length;
  int64_t capacity;
  std::unique_ptr<T[]> data;

  Vector() {
    length = 0;
    capacity = VECTOR_DEFAULT_SIZE;
    data = std::make_unique<T[]>(capacity);
  }

  void push(const T& value) {
    if (length == 0 || length + 1 <= capacity) {
      data[length] = value;
      length++;
      return;
    }

    std::cout << "making new allocation and copy..." << std::endl;
    auto new_buffer = std::make_unique<T[]>(capacity + VECTOR_DEFAULT_SIZE);
    capacity += VECTOR_DEFAULT_SIZE;
    for (auto i = 0; i < length; i++) {
      new_buffer[i] = data[i];
    }
    data = std::move(new_buffer);
    data[length] = value;
    length++;
  }

  ~Vector() = default;

  T operator[](const int64_t& index) {
    if (index >= length) {
      throw std::runtime_error("index out of bounds");
    }

    return data[index];
  }

  void print() {
    if (length == 0) {
      std::cout << "[]" << std::endl;
      return;
    }

    std::cout << "[ ";
    for (auto i = 0; i < length; i++) {
      std::cout << std::to_string(data[i]) << " ";
    }
    std::cout << "]" << std::endl;
  }
};


template<typename K, typename V>
class Pair {
  K key;
  std::unique_ptr<V> value;

  Pair(K& k, V& v) {
    key = k;
    value = std::make_unique<V>(v);
  }
  ~Pair() = default;
};

template<
  typename K,
  typename V,
  typename Hash = std::hash<K>,
  typename Eq = std::equal_to<K>
>
class HashMap {
public:
  Vector<LinkedList<Pair<K,V>>> buckets;

  HashMap() {
    buckets = Vector<LinkedList<Pair<K,V>>>();
  }
  ~HashMap() = default;
};

int main() {
  auto list = LinkedList<std::string>();
  list.push("batata");
  list.push("laranja");
  list.push("abacaxi");
  list.print();

  auto vec = Vector<double>();
  vec.push(0.3);
  vec.push(2.0);
  vec.push(4);
  vec.print();

  auto x = std::hash<std::string>()("batata");
  std::cout << x << std::endl;

  auto y = std::hash<std::string>()("pereba");
  std::cout << y << std::endl;

  auto z = std::hash<int64_t>()(2343435);
  std::cout << z << " -> " << z % 10 << std::endl;

  //auto hm = HashMap<std::string, int>();

  return 0;
}
