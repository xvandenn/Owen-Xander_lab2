#include "hash_list.h"

hash_list::hash_list() 
{
    head = NULL;
    size = 0;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) 
{
    node * curr;
    if (!head)
    {
        head = build_node(key, value);
        size += 1;
        return;
    }

    curr = head;
    while(curr)
    {
        if(curr -> key == key)
        {
            curr -> value = value;
            return;
        }
        curr = curr -> next;
    }

    curr = build_node(key, value);
    curr -> next = head;
    head = curr;
    size += 1;
}

std::optional<float> hash_list::get_value(int key) const 
{
    if(!head)
    {
        return std::nullopt;
    }

    node * curr = head;
    while(curr)
    {
        if(curr -> key == key)
        {
            return curr -> value;
        }
        curr = curr -> next;
    }
    return std::nullopt; 
}

bool hash_list::remove(int key) 
{ 
    node * temp;
    node * curr;
    if(!head)
    {
        return false;
    }

    if(head -> key == key)
    {
        temp = head -> next;
        delete head;
        head = temp;
        size -= 1;
        return true;
    }

    curr = head;
    while(curr -> next)
    {
        if((curr -> next) -> key == key)
        {
            temp = (curr -> next) -> next;
            delete curr -> next;
            curr -> next = temp;
            size -= 1;
            return true;
        }
        curr = curr -> next;
    }
    return false; 
}

size_t hash_list::get_size() const { return size; }

hash_list::~hash_list() 
{
    if(!head)
    {
        return;
    }
    node * temp;
    while (head)
    {
        temp = head -> next;
        delete head;
        head = temp;
    }
}

//personal helper functions below:

node * hash_list::build_node(int key, float value)
{
    node * temp = new node;
    temp -> next = NULL;
    temp -> key = key;
    temp -> value = value;

    return temp;
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
	this->reset_iter();
}

hash_list &hash_list::operator=(const hash_list &other) {
	if(head == other.head)
	{
		return *this;
	}
	this->~hash_list();
	head = NULL;
	size = 0;
	iter_ptr = other.head;
	while(!this->iter_at_end())
	{
		this->insert(iter_ptr->key, iter_ptr->value);
		this->increment_iter();
	}
	this->reset_iter();
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
