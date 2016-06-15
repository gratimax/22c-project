#ifndef LinkedLiseNode_H
#define LinkedLiseNode_H

template <class Type>
class ADTNode {
 private:
  Type data;

 public:
  ADTNode* next;
  int key;
  ADTNode(Type t, int k) {
    data = t;
    next = nullptr;
    key = k;
  }

  void setData(Type d) { data = d; }

  int getKey() { return key; }

  Type getData() { return data; }
};
#endif  // !LinkedLiseNode_H
