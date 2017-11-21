#pragma once

template<typename E>
class CListBase
{
private:
	void operator =(const class&){}
	CListBase(const CListBase&){}

public:
	CListBase(void){}
	virtual ~CListBase(void){}

	virtual void clear() = 0;

	virtual void insert(const E& item) = 0;

	virtual void append(const E& item) = 0;

	virtual E remove() = 0;

	virtual void moveToStart() = 0;

	virtual void moveToEnd() = 0;

	virtual void prev() = 0;

	virtual void next() = 0;

	virtual int length() const = 0;

	virtual int currPos() const = 0;

	virtual void moveToPos(int pos) = 0;

	virtual const E& getValue() const = 0;
};

//singly linked list node
template<typename E> 
class Link
{
public:
	E element; //value for this node
	Link *next; //pointer to next node in list

	Link(const E& elemval, Link* nextval =NULL)
	{
		element = elemval;
		next = nextval;
	}

	Link(Link* nextval =NULL)
	{
		next = nextval;
	}

};

template<typename E>
class CLinkList:public CListBase<E>
{
private:
	Link<E>* head;//pointer to list header
	Link<E>* tail;//pointer to last element
	Link<E>* curr;//access to current element
	int cnt;//size of list

	void init() //initialization 
	{
		curr = tail = head = new Link<E>;
		cnt = 0;
	}

	void removeall() // delete all link nodes
	{
		while(head!=NULL)
		{
			curr = head;
			head = head->next();
			delete curr;
		}
	}

public:
	CLinkList(int size=20)
	{
		init();
	}
	~CLinkList()
	{
		removeall();
	}

	void print() const; //print list contents

	void clear() //clear list, reset list
	{
		removeall();
		init();
	}

	//insert "it" at current position
	void insert(const E& it)
	{
		curr->next = new Link<E>(it, curr->next);
		if (tail==curr)
		{
			tail = curr->next();
		}
		cnt++;
	}

	//append "it" to list
	void append(const E& it)
	{
		tail = tail->next = new Link<E>(it, NULL);
		cnt++;
	}

	//remove and return current element
	E remove() 
	{
		assert(curr->next != NULL);
		E it = curr->next->element; //remember value
		Link<E>* ltemp = curr->next; //remember link node
		if (tail == curr->next) //reset tail
		{
			tail = curr;
		}
		curr->next = curr->next->next; //remove from list
		delete ltemp; //reclaim space
		cnt--;
		return it;
	}

	void moveToStart() //place curr at list start
	{
		curr = head;
	}

	void moveToEnd() //place curr at list end
	{
		curr = tail;
	}

	//move curr one step left; no change if already at head
	void prev()
	{
		if (curr==head) //no previous element
		{
			return;
		}
		Link<E>* temp = head;
		//march down list until we find the previous element
		while(temp->next!=curr)
		{
			temp = temp->next;
		}
		curr = temp;
	}

	//move curr one step right; no change if already at end
	void next()
	{
		if (curr!=tail)
		{
			curr = curr->next;
		}
	}

	int length() const
	{
		return cnt;
	}

	//return the position of the current element
	int currPos() const 
	{
		Link<E>* temp = head;
		int i;
		for (i=0; curr!=temp;i++)
		{
			temp = temp->next;
		}

		return i;
	}

	//move down list to "pos" position
	void moveToPos(int pos)
	{
		assert((pos>=0)&&(pos<=cnt));
		curr = head;
		for (int i=0; i<pos; i++)
		{
			curr = curr->next;
		}
	}

	//return current element
	const E& getValue() const
	{
		assert(curr->next!=NULL);
		return curr->next->element;
	}
};
