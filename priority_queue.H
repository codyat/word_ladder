/*
 * Course: CS 100 Summer Session 2 2012
 *
 * First Name: Cody 
 * Last Name: Troyer
 * Username: ctroy001
 * email address: ctroy001@ucr.edu
 *
 *
 * Assignment: assn5
 * Filename : priority_queue.H
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there 
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 

#ifndef PQ_ZERO_H_
#define PQ_ZERO_H_

#include <vector>
#include <map>

using namespace std;

template<typename Item>
class priority_queue
{
  private:
    vector<Item> heap; // The heap expands/shrinks to fit data
    typedef int indx; // index with heap
    map<Item,indx> index; // records each Item's place in heap
    map<Item,float> priority; //records each Item's priority
    void build_heap()
    {
			//traverses the vector and percolates down at each index from the
			//half way point to the beginning
			for (int x = (heap.size()/2) - 1; x >= 0; --x )
				percolate_down(x);
		}
		void swap(Item& a, Item& b)
		{
			Item temp = a;
			a = b;
			b = temp;
		}
    void percolate_up(indx i)
    {
			//loops until Item percolates to the root, or item has a less
			//priority.than its parent.
			while(i > 0 && priority[heap[i]] <= priority[heap[get_parent(i)]])
			{
				//moves hole upward
			  swap(heap[i], heap[get_parent(i)]);
			  index[heap[i]] = get_parent(i);
			  index[heap[get_parent(i)]] = i;
			  i = get_parent(i);
			}
		}
    void percolate_down(indx i)
    {
			//end recursion if index has no children
			if((i * 2 + 2) > (int)heap.size()) return;
			//end recursion if item has higher priority then both of its
			//children
			if(priority[heap[i]] < priority[heap[get_left(i)]] &&
			   priority[heap[i]] < priority[heap[get_right(i)]]) return;
			//if both chilred have higher priority than the parent, then 
			//decide which (left or right) has higher priority and percolate
			//down that way.
			else if(priority[heap[i]] > priority[heap[get_left(i)]] &&
			        priority[heap[i]] > priority[heap[get_right(i)]])
			{
				//check to percolate right
				if(priority[heap[get_left(i)]] > priority[heap[get_right(i)]])
				{
					swap(heap[i], heap[get_right(i)]);
					index[heap[i]] = get_right(i);
					index[heap[get_right(i)]] = i;
				  percolate_down(get_right(i));
			  }
			  //check to percolate left
			  else
			  {
					swap(heap[i], heap[get_left(i)]);
					index[heap[i]] = get_left(i);
					index[heap[get_left(i)]] = i;
  				percolate_down(get_left(i));
				}
			}
			//check to percolate left 
			else if(priority[heap[i]] > priority[heap[get_left(i)]])
			{
				swap(heap[i], heap[get_left(i)]);
				index[heap[i]] = get_left(i);
				index[heap[get_left(i)]] = i;
				percolate_down(get_left(i));
			}
			//check to percolate right
			else if(priority[heap[i]] > priority[heap[get_right(i)]])
			{
				swap(heap[i], heap[get_right(i)]);
				index[heap[i]] = get_right(i);
				index[heap[get_right(i)]] = i;
				percolate_down(get_right(i));
			}
		}	  
		//literally gets the left child
    const indx get_left(indx i) const {return (2 * i + 1);}
    //literally gets the right child
    const indx get_right(indx i) const {return (2 * i + 2);}
    //literally gets the parent
    const indx get_parent(indx i) const {return ((i - 1) / 2);}
  public:
    priority_queue(){}
    //constructor that creates the priority queue
		priority_queue(const vector<Item>& v1, const vector<float>& v2)
    {
			for(int i = 0; i < (int)v1.size(); i++)
			  push(v1[i], v2[i]);
			build_heap();
		}
    // These use the min-heap functions above.
    int size() const {return heap.size();}
    bool empty() const {return heap.empty();}
    const Item& top() const {return heap[0];}
    //removes the top item in the priority queue
    void pop() 
    {
			if(heap.empty()) return;
			heap[0] = heap[heap.size() - 1];
			heap.pop_back();
			percolate_down(0);
		}
		//adds another item to the priority queue
    void push(const Item& w, float prio)
    {
			heap.push_back(w);
			priority.insert(pair<Item, float>(w, prio));
			index.insert(pair<Item, indx>(w, heap.size() - 1));
			percolate_up(heap.size() - 1);
		}
};

#endif
