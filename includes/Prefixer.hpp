#ifndef PREFIXER_HPP__
#define PREFIXER_HPP__

#include <map>
#include <string>
#include <vector>
#include <stack>

#include "Node.hpp"

namespace prefixer {

/*! \brief Prefixer class for storing and printing infix expresions.
 *
 * Prefixer supports converting infix to prefix.
 * The format of the input expression is highly restricted. All values
 * are either single alphabetic characters or positive integers.
 * All operators, including ( and ), are always separated by at least
 * one space from other values or operators.
 *
 * Examples: 1 + 1 outputs (+ 1 1)
 *           3 * x + ( 9 + y ) outputs (+ (* 3 x) (/ (+ 9 y) 4))
 *
 * When creating the prefix expression, the class supports a reduce
 * flag.  The reduction is done for all operations when both operands
 * are integers.  So 3 * 3 will be reduced to 9 and 3 * ( 2 + 4 ) / x
 * will be reduced to 18 / x equivalent.
 */
class Prefixer {
  public:

    /*! Constructor
     *
     * An instance of Prefixer must be passed a valid expression
     *
     * @pram algebraicExpression Valid algebraic expression to convert.
     */
		Prefixer( std::vector<std::string> algebraicExpression ) ;

    /*! Destructor
     *
     */
    ~Prefixer() ;

    /*! Convert infix expression to prefix form
     *
     * Function has to be called explicitely for the conversion
     * to take place.  The function takes an optional argument
     * whether to reduce the expression or not.
     *
     * @param reduce Flag whether to reduce the expression.
     */
		void ConvertInfixToPrefix( bool reduce = false ) ;

    /*! Get expression in prefix notation
     *
     * @return Expression in prefix notation.
     */
    std::string PrintPrefixExpression() ;

  private:

    /*! An enum for supported operations
     *
     * The enum is sorted in ascending operator precendence order.
     */
		enum Operations {
			OPEN_PAREN = -6,
			CLOSE_PAREN = -5,
			SUBTRACT = -4,
			ADD = -3,
			DIVIDE = -2,
			MULTIPLY = -1
		} ;

    /*! Check if the value is an operator
     *
     * @param val Value to check
     *
     * @return True if value is an operator, false otherwise.
     */
		bool isOperator( std::string val ) ;

    /*! Get the precendence of the operator
     *
     * @param op Operator to check
     *
     * @return Numerical precedence value
     */
		int PrecedenceOf( std::string op ) ;

    /*! Creates a node using the operator and leaf nodes.
     *
     * Function used for creating a new node using the provided
     * operator and leaf nodes. Expects valid leaf nodes.  Function
     * takes in a reduce flag.  If flag is set, the function will 
     * attempt to reduce the expression by performing the specified
     * operation using the values of the leaves.  If the leaves are
     * integers, it will return a node containing the result, otherwise
     * a valid node containg the operation with the values will be created.
     *
     * @param op Operation for the value of the node
     * @param left_op Left leaf node
     * @param right_op Right leaf node
     * @param reduce Flag for whether to reduce the expression
     *
     * @return Valid node containg either a reduced expression or
     *         a tree node with operator as value and 2 leaf nodes
     *         pointing to the operands of the passed in operation.
     */
    Node* CreateNodeFromOperator( std::string op, Node* left_op, Node* right_op, bool reduce ) ;

    /*! Used for printing the tree
     *
     * Internal function for printing the expresion in prefix form
     *
     * @param cur Root node to print
     */
		void PrintSide( Node* cur ) ;

    /*! Original infix notation parsed into a vector
     *  where each vector element is expression element, whether
     *  operand or operator
     */
		std::vector<std::string> mInfix ;

    Node* mAst ; /*!< Head of the converted expression */

    /*! Hash of available operations */
		std::map<std::string, enum Operations> mAvailableOperations ;

    std::string mPrefix ;
} ;

}
#endif

