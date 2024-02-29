#include "../include/BitArray.h"
#include <gtest/gtest.h>
using namespace std;


TEST(Array, Main) {
	// SET/RESET/INITIALIZE

	BitArray b = BitArray(); // Init 32 bits with 0 only val
	ASSERT_TRUE(!b.empty());
	ASSERT_TRUE(b.none()); // not have any true bits
	b.set(1); // set b[1] as true
	try {
		b.set(1000);
	}
	catch (WrongNum& t) {
		t.what();
	}
	ASSERT_TRUE(b.any()); // is true bit
	//b.printArr();
	BitArray c = b;
	BitArray f(b);
	ASSERT_TRUE(f == c);
	ASSERT_TRUE(c == b);
	ASSERT_EQ(c[1], b[1]);
	ASSERT_TRUE(c[0] != c[1]);
	b.reset(); // set all zero
	ASSERT_TRUE(c[1] != b[1]);
	b.clear(); // clear
	ASSERT_TRUE(b.empty());
	try {
		b.any();
	}
	catch (WrongArr& e) {
		e.what();
	}
	b.resize(10, 0);
	ASSERT_TRUE(!(b.empty()));
	c.swap(b);
	ASSERT_EQ(c.size(), 10);
	c.swap(b);
	ASSERT_EQ(c[1], 1);
	BitArray t = c;

	// OPERATIONS
	~c; // invert
	ASSERT_EQ(c[1], 0);
	ASSERT_EQ(c[0], 1);
	c.push_back(1);
	t.push_back(0);
	ASSERT_EQ(c.size(), 33);
	BitArray tmp = BitArray(33, 1); // init using size and start mask
	ASSERT_EQ(tmp.size(), c.size());
	tmp.resize(40); //increase size of c
	ASSERT_EQ(tmp[37], 0); // using indexation

	// BIT OPERATIONS
	BitArray res = c ^ t; // xor two alternative arrs
	ASSERT_TRUE(res.any());
	c | t;
	ASSERT_TRUE(res.any());
	res = c & t;
	//res.printArr();
	ASSERT_TRUE(res.none()); // logical AND gives 0 everywhere
	res |= c;
	ASSERT_TRUE(res == c);
	res &= c;
	ASSERT_TRUE(res == c);
	res ^= c;
	ASSERT_TRUE(res.none());
	//res.printArr();

	// Binary moves
	c.set(5);
	//c.printArr();
	BitArray c_cpy = c;
	//c_cpy.printArr();
	c <<= 3;
	ASSERT_TRUE(c_cpy[5] == c[8]);
	ASSERT_EQ(c.size(), (c_cpy.size() + 3));
	ASSERT_EQ(c[2], 0); // sets 0 to new bits
	try {
		c >>= 3;
	}
	catch (WrongNum& st) {
		st.what();
	}
	try {
		c >>= 10000;
	}
	catch (WrongNum& st) {
		st.what();
	}
	try {
		c >> 10000;
	}
	catch (WrongNum& st) {
		st.what();
	}
	//c.printArr();
	//c_cpy.printArr();
	ASSERT_TRUE(c_cpy == c);

	string p = c.to_string();
	ASSERT_EQ(p.length(), c.size());
	int ttt = p[2] - 48;
	ASSERT_EQ(ttt, c[2]);
	BitArray ex1 = BitArray(31, 0);
	BitArray ex2 = BitArray(32, 123);
	
	// invalid sizes check
	try {
		ex1 &= ex2;
	} 
	catch (WrongLen& a) {
		a.what();
	}
	try {
		ex1 |= ex2;
	}
	catch (WrongLen& a) {
		a.what();
	}
	try {
		ex1 ^= ex2;
	}
	catch (WrongLen& a) {
		a.what();
	}
	try {
		ex1 = ex1 & ex2;
	}
	catch (WrongLen& a) {
		a.what();
	}
	try {
		ex1 = ex1 | ex2;
	}
	catch (WrongLen& a) {
		a.what();
	}
	try {
		ex1 = ex1 ^ ex2;
	}
	catch (WrongLen& a) {
		a.what();
	}

	// same for |, &, ^
}

int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
