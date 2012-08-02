#include <assert.h>
#include <Platform/SkPlatform.h>


namespace SK {

	template <typename X>
	Return<X>::Return(typename SK::ReturnTrait<X>::return_t value)
	{
		m_value=SK::ReturnTrait<X>::createContainer(value); 
	}

	template <typename X>
	Return<X>::Return()
	{
		m_error=Error("Using uninitialized return") ;
	}

	template <typename X>
	Return<X>::Return(const Return<X> &other)
	{
		m_error=other.m_error ;
		m_value=other.m_value ;
		other.m_checked = true ;
	}

	template <typename X>
	Return<X>::Return(const Return<void> &other)
	{
		if (!other.m_error.hasError()) {
			m_error=SK::Error("Return<X> constructed from non-failed Result") ;
		} else {
			m_error=other.m_error ;
		}
		other.m_checked = true ;
	}

	template <typename X>
	Return<X>::~Return() {
	}

	template <typename X>
	Return <X> &Return<X>::operator =(const Return<X> &other) {
		if (&other != this) {
			m_error = other.m_error ;
			other.m_checked = true ;
			m_value = other.m_value ;
		}
		return *this ;
	}

	namespace
	{
		SK_NO_RETURN void fatal_error()
		{
			SK_TRACE("You cannot access a data if the call failed. Please always check for the success of your call before accessing the return values.");
		}
	}

	template <typename X>
	typename SK::ReturnTrait<X>::return_t Return<X>::get()const
	{
#ifdef SK_RETURN_CHECK
		assert(m_checked) ;
#endif
		assert(SK::ReturnTrait<X>::check(m_value));
		if (SK::ReturnTrait<X>::check(m_value))
		{
			return SK::ReturnTrait<X>::returnValue(m_value); 
		} 
		fatal_error();
	} 

	template <typename X>
	Return<void> Return<X>::toResult() {
		return SK::Return<void>(*this) ;
	}
} 
