#include "hash_list.h"

hash_list::hash_list() {

	head = NULL;
	size = 0;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {
	node* start = head;
	
	while(start != nullptr){
		if(start->key == key){
			start->value = value;
			return;
		}
		start = start->next;
	}

	node* toIns = new node;
	toIns->key = key;
	toIns->value = value;
	toIns->next = head;
	head = toIns;
	delete start;
}

std::optional<float> hash_list::get_value(int key) const { 

	node* start = head;	
	while(start != nullptr){
		if((start->key == key)){
			return start->value;
		}
		start = start->next;
	}

	delete start;
	return std::nullopt; }

bool hash_list::remove(int key) {

	node* start = head;
	node* prev = nullptr;

	while(start != nullptr){
		if(start->key == key){
			if(prev == nullptr){
				head = start->next;
			}
			else {
				prev->next = start->next;
			}
			delete start;
			return true;
		}

		prev = start;
		start = start->next;
	}

	return false; }

size_t hash_list::get_size() const { 

	size_t size = 0;
	node* start = head;
	while(start != nullptr){
		size++;
		start = start->next;
	}
	delete start;
	return size; }

hash_list::~hash_list() {
	node* start = head;
	while(start != nullptr){
		node* next = start->next;
		delete start;
		start = next;
	}
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) 
{
	head = NULL;
	size = 0;
	iter_ptr = other.head;
	while(!this->iter_at_end())
	{
		this->insert(iter_ptr->key, iter_ptr->value);
		this->increment_iter();
	}
}

hash_list &hash_list::operator=(const hash_list &other) { 
	this->~hash_list();
	head = NULL;
	size = 0;
	node * ptr = other.head;
	while(ptr != NULL)
	{
		this->insert(ptr->key, ptr->value);
		ptr = ptr -> next;
	}
	return *this; 
}

void hash_list::reset_iter() {
	iter_ptr = size > 0 ? head : NULL;
}


void hash_list::increment_iter() {
	if(iter_ptr == NULL){
		return;
	}
	if(iter_ptr->next == NULL){
		iter_ptr = NULL;
		return;
	}
	iter_ptr = iter_ptr->next;
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
	if(iter_ptr == NULL){
	return std::nullopt;
	}
	return std::make_pair(&iter_ptr->key, &iter_ptr->value);
}


bool hash_list::iter_at_end() { 
	return iter_ptr == NULL ? true : false;
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
