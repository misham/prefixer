#include <string>

#include "Prefixer.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Prefixer Test"
#include <boost/test/unit_test.hpp>


std::vector<std::string>
convert_string_to_vector( std::string expression ) {
	std::vector<std::string> parsed_exp ;
	std::string tmp ;
	size_t expression_len = expression.length() ;
	for( size_t i = 0; i < expression_len; ++i ) {
		if( ' ' != expression[i] ) {
			tmp.push_back( expression[i] ) ;
		}
		else {
			parsed_exp.push_back( tmp ) ;
			tmp.clear() ;
		}
	}
	//
	if( !tmp.empty() ) {
		parsed_exp.push_back( tmp ) ;
	}
	//
	return parsed_exp ;
}


//
// Test 3
//
BOOST_AUTO_TEST_CASE( test_single_value ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "3" ) ;
	std::string expected_result = "3" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( false ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
}

//
// Test 1 + 1 => (+ 1 1)
//
BOOST_AUTO_TEST_CASE( test_two_values ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "1 + 1" ) ;
	std::string expected_result = "(+ 1 1)" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( false ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
	//
	test_expr = convert_string_to_vector( "1 + 2" ) ;
	expected_result = "(+ 1 2)" ;
	prefixer::Prefixer second_test_prefixer( test_expr ) ;	
	second_test_prefixer.ConvertInfixToPrefix( false ) ;
	result = second_test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
	//
	test_expr = convert_string_to_vector( "2 + 1" ) ;
	expected_result = "(+ 2 1)" ;
	prefixer::Prefixer third_test_prefixer( test_expr ) ;	
	third_test_prefixer.ConvertInfixToPrefix( false ) ;
	result = third_test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
}

//
// Test 2 * 5 + 1 => (+ (* 2 5) 1)
//
BOOST_AUTO_TEST_CASE( test_three_values ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "2 * 5 + 1" ) ;
	std::string expected_result = "(+ (* 2 5) 1)" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( false ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
}

//
// Test 2 * ( 5 + 1 ) => (* 2 (+ 5 1))
//
BOOST_AUTO_TEST_CASE( test_parens ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "2 * ( 5 + 1 )" ) ;
	std::string expected_result = "(* 2 (+ 5 1))" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( false ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
}

//
// Test 3 * x + ( 9 + y ) / 4 => (+ (* 3 x) (/ (+ 9 y) 4))
//
BOOST_AUTO_TEST_CASE( test_expression ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "3 * x + ( 9 + y ) / 4" ) ;
	std::string expected_result = "(+ (* 3 x) (/ (+ 9 y) 4))" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( false ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
}

//
// Test reduce 3 * ( 2 + 4 ) / 2 => 9
//
BOOST_AUTO_TEST_CASE( test_reduce ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "3 * ( 2 + 4 ) / 2" ) ;
	std::string expected_result = "9" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( true ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
}

//
// Test reduce 3 * ( 2 + 4 ) / x => (/ 18 x)
//
BOOST_AUTO_TEST_CASE( test_expression_reduce ) {
	std::vector<std::string> test_expr = convert_string_to_vector( "3 * ( 2 + 4 ) / x" ) ;
	std::string expected_result = "(/ 18 x)" ;
	prefixer::Prefixer test_prefixer( test_expr ) ;	
	test_prefixer.ConvertInfixToPrefix( true ) ;
	std::string result = test_prefixer.PrintPrefixExpression() ;
	//
	BOOST_CHECK( result == expected_result ) ;
} // */

