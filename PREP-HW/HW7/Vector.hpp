/*
 * Реализация сложного контейнера:
 * 4) Vector
 * 
 * Использование
 * Необходимо написать простой пример использования обоих контейнеров, все что захотите.
 * 
 * Требования к реализации
 * - шаблоны - поддержать любой тип данных
 * - исключения - корректно обрабатывать
 * 
 * доп. баллы
 * - совместимость с range based loop (не забыть про const) - 1 балл
 * - совместимость с std::allocator - 2 балла
 * - полный набор конструкторов - как у STL (move constructor, std::initializer_list, с итераторов, …) - 1 балл
 * - перегрузить необходимые операторы для математических операций над контейнерами, использовав decltype + кастомный string literal = 1 балл
 */
#ifndef VECTOR_H_
#define VECTOR_H_
#include <cassert>
#include <new>
#include <initializer_list>	

namespace drmatters {
template <class T, class Alloc = std::allocator<T>>
class Vector {
public:
  typedef Alloc allocatorType;
  typedef typename Alloc::value_type valueType;
  typedef typename Alloc::reference reference;
  typedef typename Alloc::const_reference constReference;
  typedef typename Alloc::difference_type differenceType;
  typedef typename Alloc::size_type sizeType;
  
  class iterator;
  class const_iterator;
  
  //constructors
  explicit Vector(const allocatorType& alloc = allocatorType()) : Al(alloc), size(0), capacity(8),
	  pBeg(Al.allocate(capacity + 1)), tobegin(nullptr), toend(nullptr) {
  }
  explicit Vector(sizeType n) : size(0), capacity(n), pBeg(Al.allocate(capacity + 1)),
	  tobegin(nullptr), toend(nullptr) {
  }
  template <class inputIterator>
  Vector(inputIterator first, inputIterator last, const allocatorType& alloc = allocatorType()) : Al(alloc) {
	while(first != last) {
	  pushBack(*first);
	  first++;
	}
  }
  Vector(const Vector& tocpy); //copy-constructor
  Vector(Vector&& tomove) : Al(tomove.Al), size(tomove.size), capacity(tomove.capacity), pBeg(tomove.pBeg) { //move-constructor
	tomove.pBeg = nullptr;
  }
  Vector(Vector&& tomove, const allocatorType& alloc = allocatorType()); //move-constructor
  Vector(const std::initializer_list<valueType> il, //initializer-list
	const allocatorType& alloc = allocatorType()) : Al(alloc), size(il.size()), capacity(il.size()),
		pBeg(Al.allocate(capacity + 1)), tobegin(nullptr), toend(nullptr) {
	for(auto& item : il) {
	  pushBack(item);
	}
  }
  ~Vector() {
	for(sizeType i = 0; i < size; i++) {
	  Al.destroy(&(pBeg[i]));
	}
	Al.deallocate(pBeg, capacity + 1);
  }
  
  sizeType getsize() {
    return size;
  }
  T& at(sizeType index);
  const T& at(sizeType index) const;
  Vector& operator=(Vector arg);
  void pushBack(const valueType& val);
  void reserve(sizeType n);
  iterator begin() {
	return tobegin;
  }
  iterator end() {
	return toend;
  }
  iterator cbegin() const noexcept {
    return begin;
  }
  iterator cend() const noexcept {
    return end;
  }
  struct iterator : std::iterator<std::random_access_iterator_tag, valueType> {
	typedef typename Alloc::difference_type differenceType;
	typedef typename Alloc::value_type valueType;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::pointer pointer;
	
	iterator() : pObj(nullptr) { }
	iterator(const iterator& tocpy) : pObj(tocpy.pObj) { }
	
	iterator& operator=(const iterator& toeq) {
	  pObj = toeq.pObj;
	  return *this;
	}
	iterator& operator=(pointer ptr) {
	  pObj = ptr;
	  return *this;
	}
	bool operator==(const iterator& arg) const {
	  return pObj == arg.pObj;
	}
	bool operator!=(const iterator& arg) const {
	  return (pObj != arg.pObj);
	}
	iterator& operator++() {
	  ++pObj;
	  return *this;
	}
	reference operator*() const {
	  return *pObj;
	}
	pointer operator->() const {
	  return pObj;
	}
	reference operator[](differenceType index) const {
	  return *(pObj + index);
	}
    iterator(pointer p) : pObj(p) {	}
  private:
	pointer pObj;

  };
  
  friend void swap(Vector& lh, Vector& rh) {
	using std::swap;
	
	swap(lh.tobegin, rh.tobegin);
	swap(lh.toend, rh.toend);
	swap(lh.Al, rh.Al);
	swap(lh.pBeg, rh.pBeg);
	swap(lh.size, rh.size);
	swap(lh.capacity, rh.capacity);
  }
  private:
  allocatorType Al;
  sizeType size;
  sizeType capacity;
  valueType* pBeg;
  
  iterator tobegin;
  iterator toend;
};

template <class T, class A>
Vector<T, A>::Vector(const Vector& tocpy) : Al(tocpy.Al),
	size(tocpy.size), capacity(tocpy.capacity), pBeg(Al.allocate(capacity + 1)),
	tobegin(size == 0 ? nullptr : pBeg), toend(size == 0 ? nullptr : pBeg + size) {
  for(sizeType i = 0; i < size; i++) {
	pBeg[i] = tocpy.pBeg[i];
  }
}

template <class T, class A>
void Vector<T, A>::pushBack(const valueType& val) {
  if(capacity <= size) {
	reserve(capacity * 2);
  }
  Al.construct(pBeg + size, val);
  ++size;
  tobegin = pBeg;
  toend = pBeg + size;
}

template <class T, class A>
void Vector<T, A>::reserve(sizeType n)  {
  if(n > capacity) {
	Vector temp(n);
	capacity = n;
	std::copy(pBeg, pBeg + size, temp.pBeg);
	
	swap(*this, temp);
  }
}
template <class T, class A>
Vector<T, A>& Vector<T, A>::operator=(Vector arg) {
  
  swap(*this, arg);
  return *this;
}
template <class T, class A>
T& Vector<T, A>::at(sizeType index) {
  if(index < getsize()) {
    return pBeg[index];
  } else {
    throw std::out_of_range("Wrong argument of \"at\" function");
  }
}
template <class T, class A>
const T& Vector<T, A>::at(sizeType index) const {
  if(index < getsize()) {
    return pBeg[index];
  } else {
    throw std::out_of_range("Wrong argument of \"at\" function");
  }
}
}
#endif