#ifndef ADTNODE_H
#define ADTNODE_H

template<class Type>
class ADTNode{
private:
	Type data;
public:
	ADTNode* right;
	ADTNode* left;
	ADTNode* next;
	ADTNode(Type t){
		data = t;
		right = nullptr;
		left = nullptr;
		next = nullptr;
	}
	void setData(Type d){ data = d; }
	Type getData(){ return data; }
};
#endif // !ADTNODE_H
