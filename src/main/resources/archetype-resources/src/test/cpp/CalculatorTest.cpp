#set( $H = '#' )
${H}include <cppunit/extensions/HelperMacros.h>
${H}include "Calculator.h"
${H}include <cstring>

class CalculatorTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(CalculatorTest);
	CPPUNIT_TEST(testSum);
	CPPUNIT_TEST_SUITE_END();

	private:

	public:

	void setUp() {
	}

	void tearDown() {
	}

	void testSum() {
		Calculator calculator;

		CPPUNIT_ASSERT_EQUAL(4,calculator.sum(2,2));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CalculatorTest);
