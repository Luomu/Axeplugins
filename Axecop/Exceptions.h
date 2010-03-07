#ifndef Exceptions_h__
#define Exceptions_h__

struct Axception : public std::exception
{
	std::string s;
	Axception(std::string ss) : s(ss) {}
	const char* what() const throw() { return s.c_str(); }
};

#endif // Exceptions_h__