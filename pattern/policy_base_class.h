#ifndef POLICY_BASE_CLASS_H
#define POLICY_BASE_CLASS_H

#include <stdio.h>
#include <stdlib.h> 


class Widget;

namespace policy {

template <class T>
struct OpNewCreator {
	static T* Create() {
		return new T;
	} 
protected:
	/// Because the destructor is protected, only derived classes can destroy policy objects, 
	/// so it's impossible for outsiders to apply delete to a pointer to a policy class. 
	/// The destructor, however, is not virtual, so there is no size or speed overhead.
	~OpNewCreator() {}
};

template <class T>
struct MallocCreator {
	static T* Create() {
		void* buf = malloc(sizeof(T));
		if (!buf) return 0;
		return new(buf) T;
	} 
protected:
	~MallocCreator() {}
};

template <class T>
struct PrototypeCreator {
	PrototypeCreator(T* pObj = 0):pPrototype_(pObj) {}

	T* Create() {
		return pPrototype_ ? pPrototype_->Clone() : 0; 
	}

	T* GetPrototype() { return pPrototype_; }

	void SetPrototype(T* pObj) { pPrototype_ = pObj; } 
protected:
	~PrototypeCreator() {
		if(pPrototype_) delete pPrototype_;
		pPrototype_ = NULL;
	}
private:
	T* pPrototype_;
};


// simple
template <class CreationPolicy>
class WidgetManager : public CreationPolicy {
public:
	WidgetManager(){}
	~WidgetManager(){}

private:
};

template <template <class Created> class CreationPolicy = OpNewCreator> 
class WidgetManager2 : public CreationPolicy<Widget> {
public:
	WidgetManager2(){}
	~WidgetManager2(){}

	/// According to the C++ standard, the degree of syntax checking for unused template functions 
	/// is up to the implementation. The compiler does not do any semantic checking except perhaps for syntax checking.
	/// —for example: symbols are not looked up.
	void SwitchPrototype(Widget* pNewPrototype){
		CreationPolicy<Widget>& myPolicy = *this;
		delete myPolicy.GetPrototype(); // decide myPolicy.GetPrototype in compile time .
		myPolicy.SetPrototype(pNewPrototype);
	}
};


} // policy namespace

#endif
