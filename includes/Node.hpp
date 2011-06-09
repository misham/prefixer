#ifndef NODE_HPP__
#define NODE_HPP__

#include <string>
#include <cctype>
#include <stdlib.h>

#include <boost/lexical_cast.hpp>

namespace prefixer {

/*! \brief Node class for storing each operand and operator
 *
 * Class is used to build up a BinaryTree representing each operand
 * and operator in the tree.
 *
 * The class provides basic functionality for set/get of each leaf.
 * The value is non-mutable.
 */
class Node {

	private:
    std::string mValue ;
    bool mResult ;
		Node* mLeft ;
		Node* mRight ;

    /*!
     * Clean up function used for freeing each node recursively.
     */
    void CleanUp() {
      if( NULL != mLeft) {
        mLeft->CleanUp() ;
        delete mLeft ;
        mLeft = NULL ;
      }
      //
      if( NULL != mRight) {
        mRight->CleanUp() ;
        delete mRight ;
        mRight = NULL ;
      }
    }

	public:

    /*!
     * Constructor that will initialize the node to the
     * value provided.
     *
     * @param val Node value to store.
     */
    Node( std::string val ) :
      mResult( false ),
      mLeft( NULL ),
      mRight( NULL )
    {
      mValue = val ;
    }

    /*!
     * Destructor.
     */
    ~Node() {
      CleanUp() ;
    }

    /*!
     * Setter for the left leaf.
     *
     * @param left Node for the left leaf.
     */
		void SetLeft( Node* left ) {
			if( NULL != left ) {
				mLeft = left ;
			}
		}

    /*!
     * Setter for the right leaf.
     *
     * @param right Node for the right leaf.
     */
    void SetRight( Node* right ) {
			if( NULL != right ) {
				mRight = right ;
			}
		}

    /*!
     * Getter for the left leaf.
     *
     * @return Node pointed to by the left leaf.
     */
		Node* GetLeft() {
			return mLeft ;
		}

    /*!
     * Getter for the right leaf.
     *
     * @return Node pointed to by the right leaf.
     */
		Node* GetRight() {
			return mRight ;
		}

    /*!
     * Getter for the Node value.
     *
     * @param Value of the node.
     */
		std::string GetValue() { return mValue ; }
} ;

} // namespace
#endif

