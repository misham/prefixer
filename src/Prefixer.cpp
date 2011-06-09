#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <boost/algorithm/string.hpp>

#include "Prefixer.hpp"

namespace prefixer {

Prefixer::Prefixer( std::vector<std::string> algebraicExpression ) :
	mInfix( algebraicExpression ),
  mAst( NULL )
{
	if( mInfix.empty() ) {
		return ;
	}
	//
  mAvailableOperations["*"] = MULTIPLY ;
	mAvailableOperations["/"] = DIVIDE ;
	mAvailableOperations["+"] = ADD ;
	mAvailableOperations["-"] = SUBTRACT ;
	mAvailableOperations["("] = OPEN_PAREN ;
	mAvailableOperations[")"] = CLOSE_PAREN ;
}

Prefixer::~Prefixer() {
  if( NULL != mAst ) {
    delete mAst ;
    mAst = NULL ;
  }
}

void
Prefixer::ConvertInfixToPrefix( bool reduce ) {
	if( this->mInfix.empty() ) {
		return ;
	}
	//
	std::stack<std::string> operator_stack ;
	std::stack<Node*> operand_stack ;
	std::string value ;
  Node* right_op = NULL ;
  Node* left_op = NULL ;
  Node* node = NULL ;
  //
	for( size_t i = 0 ; i < mInfix.size() ; ++i ) {
    value = mInfix[i] ;
    //
    if( isOperator(value) ) {
      if( operator_stack.empty() || "(" == value ) {
        operator_stack.push( value ) ;
      }
      else if( ")" == value ) {
        std::string op = operator_stack.top() ;
        operator_stack.pop() ;
        while( "(" != op ) {
          right_op = operand_stack.top() ;
          operand_stack.pop() ;
          left_op = operand_stack.top() ;
          operand_stack.pop() ;
          //
          node = CreateNodeFromOperator( op, left_op, right_op, reduce ) ;
          operand_stack.push( node ) ;
          //
          op = operator_stack.top() ;
          operator_stack.pop() ;
        }
      }
      else {
        //
        std::string top_op = operator_stack.top() ;
        if( PrecedenceOf(top_op) > PrecedenceOf(value) ) {
          operator_stack.pop() ;
          operator_stack.push( value ) ;
          //
          right_op = operand_stack.top() ;
          operand_stack.pop() ;
          left_op = operand_stack.top() ;
          operand_stack.pop() ;
          node = CreateNodeFromOperator( top_op, left_op, right_op, reduce ) ;
          operand_stack.push( node ) ;
        } else {
          operator_stack.push( value ) ;
        }
      }
    }
		else if( isalnum(value.c_str()[0]) ) {
      node = new Node( value ) ;
      operand_stack.push( node ) ;
    }
		else {
			std::string error_message ;
			error_message.append( value ) ;
			error_message.append( " is not a valid operator or operand" ) ;
			throw std::invalid_argument( error_message ) ;
		}
  }
  //
  std::string op ;
  while( !operator_stack.empty() ) {
    op = operator_stack.top() ;
    right_op = operand_stack.top() ;
    operand_stack.pop() ;
    left_op = operand_stack.top() ;
    operand_stack.pop() ;
    node = CreateNodeFromOperator( op, left_op, right_op, reduce ) ;
    //
    operand_stack.push( node ) ;
    //
    operator_stack.pop() ;
  }
  //
  mAst = operand_stack.top() ;
  //
}

bool
Prefixer::isOperator( std::string val ) {
  if( val.empty() || 1 < val.length() ) {
    return false ;
  }
  //
  if( mAvailableOperations.end() != mAvailableOperations.find(val) ) {
    return true ;
  }
  //
  return false ;
}

int
Prefixer::PrecedenceOf( std::string op ) {
  std::map<std::string, enum Operations>::iterator it = mAvailableOperations.find( op ) ;
  return ( it == mAvailableOperations.end() ? -1 : mAvailableOperations[op] ) ;
}

std::string
Prefixer::PrintPrefixExpression() {
  if( NULL == mAst ) {
    return "" ;
  }
  //
  PrintSide( mAst) ;
  //
	boost::trim( mPrefix ) ;
  return mPrefix ;
}

void
Prefixer::PrintSide( Node* cur) {
  if( NULL == cur ) {
    return ;
  }
  //
  std::string current_value = cur->GetValue() ;
  if( isOperator(current_value) ) {
    mPrefix.append( " (" ) ;
    mPrefix.append( current_value ) ;
  }
  else {
    mPrefix.append( " " ) ;
    mPrefix.append( current_value ) ;
  }
  //
  if( NULL != cur->GetLeft() ) {
    PrintSide( cur->GetLeft() ) ;
  }
  if( NULL != cur->GetRight() ) {
    PrintSide( cur->GetRight() ) ;
    mPrefix.append( ")" ) ;
  }
}

Node*
Prefixer::CreateNodeFromOperator( std::string op,
                                  Node* left_op,
                                  Node* right_op,
                                  bool reduce ) {
  if( op.empty() ) {
		std::string error_message = "Invalid operation string: " ;
		error_message.append( op ) ;
		throw std::logic_error( error_message ) ;
    return NULL ;
  }
  else if( NULL == left_op || NULL == right_op ) {
		throw std::logic_error( "Both operands have to be provided" ) ;
		return NULL ;
	}
  //
  Node* node = NULL ;
  int left_operand_value = 0 ;
  int right_operand_value = 0 ;
  std::string left_operand_text = left_op->GetValue() ;
  std::string right_operand_text = right_op->GetValue() ;
  if( reduce &&
      (isdigit(left_operand_text.c_str()[0]) &&
       isdigit(right_operand_text.c_str()[0])) ) {
    left_operand_value = boost::lexical_cast<int>(left_operand_text) ;
    right_operand_value = boost::lexical_cast<int>(right_operand_text) ;
    //
    int result = 0 ;
    switch( op.c_str()[0] ) {
      case '+':
        result = left_operand_value + right_operand_value ;
        break ;

      case '-':
        result = left_operand_value - right_operand_value ;
        break ;

      case '*':
        result = left_operand_value * right_operand_value ;
        break ;

      case '/':
        if( 0 == right_operand_value ) {
					throw std::logic_error( "Cannot divide by 0" ) ;
          return NULL ;
        }
        result = left_operand_value / right_operand_value ;
        break ;
    }
    node = new Node( boost::lexical_cast<std::string>(result) ) ;
    delete left_op ;
    delete right_op ;
  }
  else {
    node = new Node( op ) ;
    node->SetLeft( left_op ) ;
    node->SetRight( right_op ) ;
  }
  //
  return node ;
}

} // namespace

