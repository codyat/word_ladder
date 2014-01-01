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
 * Filename : dijkstras.cc
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there 
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "priority_queue.H"

using namespace std;

map<string,string> dijkstra(map< string, set<string> >& neighbors, string source) 
{
  map<string,string> parent; // tree to be returned
  map<string,int> dist; // per-string distances to source
  priority_queue<string> worklist;
  dist[source] = 0; //sets start distance to 0
  worklist.push( source, 0 );
  //while worklist is not empty, get the top of the priority queue and 
  //store it to temp. then pop then push all neighbors of the temp to 
  //the priority queue for the next iteration of the loop. along with 
  //adding them to the maps of parnets and distance.
  while (!worklist.empty()) 
  {
		string temp = worklist.top();
		worklist.pop();
    // proceed as described above.
    for(set<string>::iterator it = neighbors[temp].begin(); 
		       it != neighbors[temp].end(); it++)
		{
			if(parent[temp] == *it) continue;
			//if the distance = 0, the word has not been visited
			//or if the dist of the parent +1 is less than the current dist at
			//the word.
			else if(dist[*it] == 0 || (dist[temp] + 1) < dist[*it]) 
			{
				parent[*it] = temp;           //update the parent
				dist[*it] = dist[temp] + 1;   //update the distance
				worklist.push(*it, dist[*it]);//push updated info to the priority queue
			}
		}		
  }
  return parent;
}

int main(int argc, char* argv[])
{
	//error checking user input
	if(argc != 3)
	{
    cerr << argv[0] << " usage: start end < dictionary/n";
    exit(1);
	}
	
	map<string,bool> in_dictionary;
  map< string, set<string> > neighbors;
  // default is false
  // for each single-letter variant of s, if it is in the
  // dictionary, add it to the neighbors of s and add s to
  // its neighbors.
  for (string s; cin >> s;) in_dictionary[s] = true;   
	//this is the building of the graph
	//the first loop steps through each word in the dictionary
	//the second loop steps through each index of the word
	//the third loop alters the letter of each index
	//inside of the 3rd loop, checks if that sample word is in the dictionary
	//if it is, add it to the adjacency list, if not then skip to the next
	//iteration
	for(map<string,bool>::iterator it = in_dictionary.begin(); it != in_dictionary.end(); it++)
  {	
		//creates a temp so i dont alter the actual word
		string word = it->first;
		//creats a temp set of strings to prevent duplicates
	  set<string> temp;
		for(int i = 0; i < (int)word.size(); i++)
		{
			//creates another temp of the word
			string temp_word = word;
		  for(char letter = 'a'; letter <= 'z'; letter++)
		  {
				//if the letter is the same as the letter that is already there
				//dont add to the adjacency list
			  if(letter == it->first[i]) continue;
			  else
			  {
					//alter letters
				  temp_word[i] = letter;
				  //if the word created exists in the dictionary then add it to 
				  //the list
				  if(in_dictionary.count(temp_word))  temp.insert(temp_word);
			  }
		  }
		}
		//insert the word and the set created to the map
		neighbors.insert(pair<string, set<string> > (it->first, temp));
	}
  map<string,string> parent = dijkstra(neighbors, string(argv[2]));
  // the root and un-reachables lack parents
  for (string s = argv[1]; s != ""; s = parent[s]) 
  {
    cout << s << endl;
    if (s == argv[2]) exit(0); // ladder found
  }
  cerr << "No such ladder found." << endl;
  exit(1); // failure
	return 0;
}
