#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food information
struct Food
{
    string foodName;
    int id;
    double price;
    struct Food* next;
};

//class LinkedList will contains a linked list of foods
class LinkedList
{
    private:
        struct Food* head;

    public:
        LinkedList();
        ~LinkedList();
        bool isFound(int foodId);
        bool add(string foodName, int foodId, double foodPrice);
        bool removeById(int foodId);
        bool removeByName(string foodName);
        bool changeFoodName(int foodId, string newFoodName);
        bool changeFoodPrice(int foodId, double newPrice);
        void printFoodList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int foodCount = 0;
    struct Food* temp;
    while (head != NULL){
      temp = head->next;
      free(head);
      head = temp;
      foodCount += 1;
    }
    head = NULL;

    cout << "The number of deleted food items is: " << foodCount <<"\n";
}

//A function to identify whether the parameterized food is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::isFound(int foodId)
{
  Food *temp = head;
	while (temp != NULL){
    if(temp->id == foodId){
      return true;
    }
    temp = temp->next;
  }
  return false;
}

//Creates a new node and inserts it into the list at the right place.
//It maintains an alphabetical ordering of foods by their names. Each
//food item has a unique id, if two food items have exactly the same name,
//then insert it into the list in the increasing order of their IDs.
//Return value: true if it is successfully inserted and false in case of failures.
// bool LinkedList::add(string foodName, int foodId, double foodPrice)
// {
//   Food *temp = head;
//   Food *prev = temp;
//   Food *newFood = new Food;
//   newFood->foodName = foodName;
//   newFood->id = foodId;
//   newFood->price = foodPrice;
//   if (head == NULL){
//     head = newFood;
//   }
//   else if(head->foodName.compare(newFood->foodName) > 0){
//     head = newFood;
//     head->next = temp;
//   }
//   else {
//     while (temp->foodName.compare(newFood->foodName) < 0){
//       prev = temp;
//       temp = temp->next;
//       if (temp == NULL){
//         temp = prev;
//         break;
//       }
//     }
//     if (temp == prev){
//       prev->next = newFood;
//     }
//     else if (temp->foodName.compare(newFood->foodName) == 0){
//       if (temp->id < newFood->id){
//         prev = temp;
//         temp = temp->next;
//         prev->next = newFood;
//         newFood->next = temp;
//       }
//       else {
//         if (temp == head){  
//           newFood->next = prev;
//           head = newFood;
//         }
//         else{ 
//           prev->next = newFood;
//           newFood->next = temp;
//         }
//       }
//     }
//     else {
//       prev->next = newFood;
//       newFood->next = temp;
//     }
//   }
//   return true;
// }


bool LinkedList::add(string foodName, int foodId, double foodPrice)
{
  // New food first
  Food *newFood = new Food;
  newFood->foodName = foodName;
  newFood->id = foodId;
  newFood->price = foodPrice;

  // if the list is empty, then just give the head;
  if (head == NULL){
    head = newFood;
    return true;
  }
  
  // if list not empty, start to find the correct position
  Food *prev = NULL;
  Food *temp = head;

  
  // compare the name with prev, we need to keep tempName not equals to newFood name;
  while (temp && newFood->foodName.compare(temp->foodName) != 0 && newFood->foodName.compare(temp->foodName)>0){
    prev = temp;
    temp = temp->next;
  }

  // compare the id with temp, we need to keep newFood's name equals to tempName, and compare with the temp.
  while(temp && newFood->foodName.compare(temp->foodName) == 0  && newFood->id>temp->id){
    prev = temp;
    temp = temp->next;
  }
  
  // if prev equal head and temp, then we need to insert at first place.
  if(prev == NULL){
    head = newFood;
    newFood->next = temp;
  }
  // if temp equals NULL, then we just insert to the last.
  else if(temp == NULL){
    prev->next = newFood;
  }
  // if in the middle
  else{
    prev->next = newFood;
    newFood->next = temp;
  }
  return true;
}

//Removes the given food by Id from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int foodId)
{
  Food *temp = head;
	while (temp != NULL){
    if(temp->id == foodId){
      temp->next = temp->next->next;
      free(temp);
      return true;
    }
    else 
      temp = temp->next;
    return false;
  }
}

//Removes the given food by name from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all foods with
//the parameterized name should be removed from the list.
bool LinkedList::removeByName(string foodName)
{
  Food *temp = head;
	while (temp != NULL){
    if(temp->foodName == foodName){
      temp->next = temp->next->next;
      free(temp);
      return true;
    }
    temp = temp->next;
  }
  return false;
}

//Modifies the name of the given Food item. Return true if it modifies successfully and
//false otherwise. Note: after changing a food name, the linked list must still be
//in alphabetical order of foods name
bool LinkedList::changeFoodName(int oldFoodId, string newFoodName)
{
  while (head != NULL){
    if(head->id == oldFoodId){
      head->foodName = newFoodName;
      return true;
    }
    head = head->next;
  }
  return false;
}

//Modifies the price of the given food item. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::changeFoodPrice(int foodId, double newPrice)
{
  while (head != NULL){
    if(head->id == foodId){
      head->price = newPrice;
      return true;
    }
    head = head->next;
  }
  return false;
}

//Prints all the elements in the linked list starting from the head node.
void LinkedList::printFoodList()
{
  Food *temp = head;
  while (temp != NULL){
    cout << temp->foodName << "   " << temp->id << "     " << temp->price << endl;
    temp = temp->next;
  }
}