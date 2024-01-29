#include <vector>

using namespace std;

class Vertex
{
   public:
      vector<int>*keys;
      vector<Vertex*>* children;
      Vertex* parent; 
      
      Vertex(){};
      ~Vertex();
};


class Abtree
{
   public:
      Abtree(int a, int b);
      ~Abtree();
      bool Find(int x, Vertex& vertex, int& index);
      void Insert(int x);
      bool Delete(int x)
   private:
      Vertex* root;
      int a;
      int b;
      
      //Split();
      //Merge();
      void Add(int x, Vertex* vertex, int index);
      void Erase(int x, Vertex* vertex, int index); 
} 

//end of header, start of implementation


//Vertex destructor
Vertex::~Vertex()
{
   for(auto ptr = this->children->begin(); ptr != this->children->end(); ++ptr)
   {
      delete(ptr);
   }
   for(auto ptr = this->keys->begin(); ptr != this->keys->end(); ++ptr)
   {
      delete(ptr);
   }
   delete(this->children);
   delete(this->keys);
}


//Abtree constructor
//a,b specifies (a,b)-tree
Abtree::Abtree(int a, int b)
: a{a}, b{b}
{
   root = new Vertex();
   root->children = new vector<Vertex*>();
   root->children->reserve(b);
   root->children->push_back(NULL);
   root->keys = new vector<int>(); 
   root->keys->reserve(b);
   root->parent = NULL;   
}

//Abtree descructor
Abtree::~Abtree()
{
   delete(root);
}

//finds x
//returns true if x was found and false if not, 
// inclomplete!!!!!!!!!
bool Abtree::Find(int x, Vertex* vertex, int& index)
{
   vector<int>::iterator ptr; 
   vertex = root;
   Vertex* parent;
   while (vertex != NULL)
   {
      ptr = lower_bound(vertex->keys->begin(),vertex->keys->end(), x);
      if (*ptr == x)
      {
         index = distance(vertex->keys->begin(), ptr);
         return true;
      }
      parent = vertex;
      vertex = vertex->children->at(distance(vertex->keys->begin(), ptr));     
   }
   vertex = parent;  
   return false;  
}

//the function insert x in the tree
//returns true if x wasn't in the tree and now is inserted, false if x is already in the tree
bool Abtree::Insert(int x)
{
   Vertex* vertex;
   int index;
   if (Find(x,vertex,index)) return false;
   Add(x,vertex,index);
     
}

//the function deletes x from the tree
//returns true if x was found in the tree, false if x wasn't found
bool Abtree::Delete(int x)
{
   Vertex* vertex;
   int index;
   if (!Find(x,vertex,index)) return false;
   Erase(x,vertex,index);      
}

//the function adds vertex child to children of vertex on the spceific index, key added will be x
void Abtree::Add(int x, Vertex* vertex, Vertex* child, int index)
{
   int size = vertex->children->size;
   if (size == b)
   {
      Vertex* newVertex = new Vertex();
      if (vertex->parent == NULL)
      {
         vertex->parent = new Vertex();
         vertex->parent->children = new vector<Vertex*>();
         vertex->parent->children->reserve(b);
         vertex->parent->children->push_back(vertex);
         vertex->parent->children->push_back(newVertex);
         vertex->parent->keys = new vector<int>();
         vertex->parent->parent = NULL;
      }
      newVertex->parent = vertex->parent;
      newVertex->children(vertex->children->begin()+size/2,vertex->children->end());
      vertex->children->erase(vertex->children->begin()+size/2,vertex->children->end());
      //for(auto ptr = newVertex->children->begin(); prt != newVertex->children->end(), ++ptr) newVertex->children->parent = newVertex;
      newVertex->keys(vertex->keys->begin() + size/2,vertex->keys->end());
      vertex->keys(vertex->keys->begin()+size/2-1,vertex->keys->end());
      int xx = *(vertex->keys->begin() + size/2);
      int ii = distance(newVertex->parent->keys->begin(), 
      lower_bound(newVertex->parent->keys->begin(), newVertex->parent->keys->end(),xx)); 
      Add(xx, vertex->parent, newVertex, ii);
   }
   vertex->children->insert(index,child); 
   vertex->keys->insert(index,x);
}

//this is incomplete!!!!!!!!!!!!!!!!
//the function erases 
void Abtree::Erase(int x, Vertex* vertex, int index)
{
   if (vertex->children->size == a)
   {
   
   }
   vertex->children->erase(index); 
   vertex->keys->erase(index);
} 
