#pragma once
/*
* SharedPtr - simple reference counted pointer.
*
* The is a non-intrusive implementation that allocates an additional
* int32_t and pointer for every counted object.
*/
namespace SK {

	/**
	 * \class	SharedPtr
	 *
	 * \brief	Simple reference counted pointer. 
	 * 			
	 * The is a non-intrusive implementation that allocates an additional
	 * int32_t and pointer for every counted object.
	 */

	template <class X> class SharedPtr
	{
	public:
		typedef X element_type;

		/**
		 * \fn	explicit SharedPtr::SharedPtr(X* p = 0)
		 *
		 * \brief	Constructor, allocate a new counter
		 *
		 * \param	p	(optional) [in,out] If non-null, the pointer to share.
		 */

		explicit SharedPtr(X* p = 0) // allocate a new counter
			: itsCounter(0) {if (p) itsCounter = new counter(p);}

		/**
		 * \fn	SharedPtr::~SharedPtr()
		 *
		 * \brief	Destructor, release one counter when destroyed
		 */

		~SharedPtr()
		{release();}

		/**
		 * \fn	SharedPtr::SharedPtr(const SharedPtr& r) throw()
		 *
		 * \brief	Copy constructor, shares the pointer with the copy
		 *
		 * \param	r	The other object to copy from.
		 */

		SharedPtr(const SharedPtr& r) throw()
		{acquire(r.itsCounter);}

		/**
		 * \fn	SharedPtr& SharedPtr::operator=(const SharedPtr& r)
		 *
		 * \brief	Assignment operator, release the counter on thr current pointer and acquire a counter on the new one.
		 *
		 * \param	r	The other object to copy from.
		 *
		 * \return	A shallow copy of this object.
		 */

		SharedPtr& operator=(const SharedPtr& r)
		{
			if (this != &r) {
				release();
				acquire(r.itsCounter);
			}
			return *this;
		}

		/**
		 * \fn	X& SharedPtr::operator*() const throw()
		 *
		 * \brief	Indirection operator.
		 *
		 * \return	The a reference to the shared pointer object.
		 */

		X& operator*()  const {return *itsCounter->ptr;}

		/**
		 * \fn	X* SharedPtr::operator->() const
		 *
		 * \brief	Allows the use of the SharedPtr as a pointer of the template X type.
		 *
		 * \return	The dereferenced object.
		 */

		X* operator->() const {return itsCounter->ptr;}

		/**
		 * \fn	X* SharedPtr::get() const
		 *
		 * \brief	Gets the pointer.
		 *
		 * \return	null if there is no pointer, else the pointer.
		 */

		X* get()        const {return itsCounter ? itsCounter->ptr : 0;}

		/**
		 * \fn	bool SharedPtr::unique() const
		 *
		 * \brief	Tells if the shared pointer is the only one managing this pointer.
		 *
		 * \return	true if the sahred pointer is unique, false if several shared pointer point to the pointer in this SharedPtr.
		 */

		bool unique()   const 
		{return (itsCounter ? itsCounter->count == 1 : true);}

	private:

		struct counter {
			counter(X* p = 0, unsigned c = 1) : ptr(p), count(c) {}

			// guarantees that ptr and counter are created and deleted in same complication unit and therefore same module
			// assuming that ptr was allocated in same module as first SharedPtr instance it was assigned to
			virtual void destroy()
			{
				delete ptr;
				delete this;
			}
			X*          ptr;
			unsigned    count;
		}* itsCounter;

		void acquire(counter* c) throw()
		{ // increment the count
			itsCounter = c;
			if (c) ++c->count;
		}

		void release()
		{ // decrement the count, delete if it is 0
			if (itsCounter) {
				if (--itsCounter->count == 0) {
					itsCounter->destroy();
				}
				itsCounter = 0;
			}
		}

		// this class should never be instanced on the heap on its own
		// so new and delete are not defined and put as private to prevent their use
	private:
#pragma push_macro("new")
#undef new
		void *operator new (size_t size); 
		void operator delete (void *ptr);	
#pragma pop_macro("new")

	};
}


