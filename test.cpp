
class A {
public:
	const static int ourLenVar = 1;
};


template<typename T, T instance>
struct enable_if {};

template<>
struct enable_if<A, > {
	static const int length = A::ourLenVar;
};



template<typename T>
int len(const T & a) {
	return a.length;
}