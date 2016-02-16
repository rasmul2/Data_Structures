// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.  
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
using namespace std;

// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}
//-----------------------------------------------------------------
template <class number_type, class label_type>
class Node {
public:
  Node() : parent(NULL), children{NULL, NULL, NULL, NULL} {}
  Node(const Point<number_type> & initn, const label_type& initc) : pt(initn), label(initc), parent(NULL), children{NULL, NULL, NULL, NULL} {}
  Point <number_type> pt;
  label_type label;
  Node<number_type, label_type>* children[4];
  Node<number_type, label_type>* parent;
};

template <class number_type, class label_type> class QuadTree;

template<class number_type, class label_type>
class DepthIterator{
public:
  DepthIterator(): ptr_(NULL) {}
  DepthIterator(Node<number_type,label_type>* p): ptr_(p) {}
  ~DepthIterator();

  /* data */

private:
  Node<number_type,label_type>* ptr_;

};

//===============================================================
template <class number_type, class label_type>
class tree_iterator {
public:
  tree_iterator() : ptr_(NULL), label_('A'), depth_(0) {}
  tree_iterator(Node<number_type, label_type>* p) : ptr_(p), depth_(0) {}
  tree_iterator(const tree_iterator& old) : ptr_(old.ptr_), depth_(0) {}
  ~tree_iterator() {}
  tree_iterator& operator=(const tree_iterator& old) { ptr_ = old.ptr_;  return *this; }
  // operator* gives constant access to the value at the pointer
  const Point<number_type> & operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const tree_iterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const tree_iterator& rgt) { return ptr_ != rgt.ptr_; }
  // increment & decrement will be discussed in Lecture 19 and Lab 11
  char getLabel(){return ptr_->label;}
  int getDepth() { return depth_;}
  DepthIterator& operator++(Node<number_type, label_type> & ptr_){ *this;}
  tree_iterator& operator++(int){}
  //===================================================================

private:
  // representation
  Node<number_type, label_type>* ptr_;
  label_type label_;
  int depth_;
};


//==============================================================
template <class number_type, class label_type>
class QuadTree {
public:
  QuadTree() : root_(NULL), size_(0), height_(-1) {}
  // QuadTree(const QuadTree<number_type, label_type>& old) : size_(old.size_) { 
  //   root_ = this->copy_tree(old.root_); }
  // QuadTree() { this->destroy_tree(root_);  root_ = NULL; }
  // QuadTree& operator=(const QuadTree<number_type, label_type>& old) {
  //   if (&old != this) {
  //     this->destroy_tree(root_);
  //     root_ = this->copy_tree(old.root_);
  //     size_ = old.size_;
  //   }
  //   return *this;
  // }

  typedef tree_iterator <number_type, label_type> iterator;
  typedef tree_iterator <number_type, label_type> bf_iterator;

  unsigned int size() const { return size_; }
  int height() {return height(root_);}
  //char getLabel() const {return label_;}
  bool operator==(const QuadTree<number_type,label_type>& old) const { return (old.root_ == this->root_); }

  // FIND, INSERT & ERASE
  iterator find(int x, int y) 
  { Point<number_type> key_int(x,y);
    label_type key_char;
    return find(key_int, key_char, root_); }
  std::pair< iterator, bool > 
  insert( Point <number_type> const & key_int, label_type const  & key_char)
     { return insert(key_int, key_char, root_); }

  iterator begin() const { return begin(root_);}


  // ITERATORS
  iterator begin(Node <number_type, label_type> *p) const { 
    if (p-> parent != NULL){
      p = p->parent;
    }
    return iterator(p);
  }
  iterator end() const { return iterator(NULL); }

  bf_iterator bf_begin(){}
  bf_iterator bf_end(){}


  // PRIVATE HELPER FUNCTIONS
  // Node<number_type, label_type>*  copy_tree(Node<number_type, label_type>* old_root) {
  //   // Implemented in Lab 10
  //   Node<number_type, label_type> * new_root = new Node<number_type, label_type>();
  //   if (old_root != NULL)
  //   {
  //     new_root->label = old_root->label;
  //     new_root->children[0] = copy_tree(old_root->children[0]);
  //     new_root->children[1] = copy_tree(old_root->children[1]);
  //   }
  //   else return NULL;
  //   return new_root;
    
  // }

  // void destroy_tree(Node<number_type, label_type>* p) { /* Implemented in Lecture 19 */  }


//======================================================================
   std::pair<iterator,bool> insert(const Point<number_type> & key_int, const label_type& key_char, Node<number_type, label_type>*& p) {
    if (!p) {
      p = new Node<number_type, label_type>(key_int, key_char);
      this->size_++;
      p->label = key_char;
      return std::pair<iterator,bool>(iterator(p), true);
    }
    else if (key_int.x < p->pt.x && key_int.y < p->pt.y)
      return insert(key_int, key_char, p->children[0]);
    else if (key_int.x > p->pt.x && key_int.y < p->pt.y)
      return insert(key_int, key_char, p->children[1]);
    else if (key_int.x > p->pt.x && key_int.y > p->pt.y)
      return insert(key_int, key_char, p->children[3]);
    else if (key_int.x < p->pt.x && key_int.y > p->pt.y)
      return insert(key_int, key_char, p->children[2]);
    else
      return std::pair<iterator,bool>(iterator(p), false);
  }

  iterator find(const Point<number_type> & key_int, const label_type& key_char, Node<number_type, label_type>*& p) {
    if (!p) return iterator(NULL);
    else if (key_int.x < p->pt.x && key_int.y < p->pt.y)
      return find(key_int, key_char, p->children[0]);
    else if (key_int.x > p->pt.x && key_int.y < p->pt.y)
      return find(key_int, key_char,  p->children[1]);
    else if (key_int.x > p->pt.x && key_int.y > p->pt.y)
      return find(key_int, key_char, p->children[3]);
    else if (key_int.x < p->pt.x && key_int.y > p->pt.y)
      return find(key_int, key_char, p->children[2]);
    else
      return iterator(p);
  }

  int height(Node <number_type, label_type>* & p){
    if (!p)
    {
      return -1;
    }
    else{
      int child0 = height(p->children[0]);
      int child1 = height(p->children[1]);
      int child2 = height(p->children[2]);
      int child3 = height(p->children[3]);

      if (child0 >= child1 && child0 >= child2 && child0 >= child3)
      {
        return child0+1;
      }

      if (child1 >= child0 && child1 >= child2 && child1 >= child3)
      {
        return child1+1;
      }

      if (child2 >= child1 && child2 >= child0 && child2 >= child3)
      {
        return child2+1;
      }

      if (child3 >= child1 && child3 >= child2 && child3 >= child0)
      {
        return child3+1;
      }

    }
  }




  // ==============================================================
// PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
// ==============================================================

// NOTE: this function only works for quad trees with non negative
// integer coordinates and char labels

// NOTE2: this function assumes that no two points have the same x
// coordinate or the same y coordinate.

// plot driver function
// takes in the maximum x and y coordinates for these data points
// the optional argument draw_lines defaults to true
void plot(int max_x, int max_y, bool draw_lines=true) const {
  // allocate blank space for the center of the board
  std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
  // edit the board to add the point labels and draw vertical and
  // horizontal subdivisions
  plot(root_,board,0,max_x,0,max_y,draw_lines);
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  for (int i = 0; i <= max_y; i++) {
    // print each row of the board between vertical border bars
    std::cout << "|" << board[i] << "|" << std::endl;
  }
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
}

// actual recursive function for plotting
void plot(Node<number_type,label_type> *p, std::vector<std::string> &board,
          int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
  // base case, draw nothing if this node is NULL
  if (p == NULL) return;
  // check that the dimensions range of this node make sense
  assert (x_min >= 0 && x_min <= x_max);
  assert (y_min >= 0 && y_min <= y_max);
  assert (board.size() >= y_max);
  assert (board[0].size() >= x_max);
  // verify that the point stored at this node fits on the board
  assert (p->pt.y >= 0 && p->pt.y < board.size());
  assert (p->pt.x >= 0 && p->pt.x < board[0].size());
  // draw the vertical and horizontal bars extending across the
  // range of this node
  if (draw_lines) {
    for (int x = x_min; x <= x_max; x++) {
      board[p->pt.y][x] = '-';
    }
    for (int y = y_min; y <= y_max; y++) {
      board[y][p->pt.x] = '|';
    }
  }
  // draw this label
  board[p->pt.y][p->pt.x] = p->label;
  // recurse on the 4 children
  plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
  plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
  plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
  plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
}


// ==============================================================

// prints all of the tree data with a pre-order (node first, then
// children) traversal of the tree structure

// driver function
void print_sideways() const { print_sideways(root_,""); }

// actual recursive function
void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
  // base case
  if (p == NULL) return;
  // print out this node
  std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
  // recurse on each of the children trees
  // increasing the indentation
  print_sideways(p->children[0],indent+"  ");
  print_sideways(p->children[1],indent+"  ");
  print_sideways(p->children[2],indent+"  ");
  print_sideways(p->children[3],indent+"  ");
}

private:
  // REPRESENTATION
  Node<number_type, label_type>* root_;
  unsigned int size_;
  int height_;
  //char label_;

  // PRIVATE HELPER FUNCTIONS
  // TreeNode<T>*  copy_tree(TreeNode<T>* old_root) {
  //   // Implemented in Lab 10
  //   TreeNode<T> * new_root = new TreeNode<T>();
  //   if (old_root != NULL)
  //   {
  //     new_root->value = old_root->value;
  //     new_root->right = copy_tree(old_root->right);
  //     new_root->left = copy_tree(old_root->left);
  //   }
  //   else return NULL;
  //   return new_root;
    
  // }



};

// ==============================================================
// ==============================================================


#endif
