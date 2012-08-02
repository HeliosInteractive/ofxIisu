#pragma once
#include <Platform/SkPlatform.h>
#include <algorithm>
#include<Framework/Types/FunctionTypeTrait.h>

namespace SK
{
	//! \cond FUNCTORS
	class IFunctor
	{
	public:
		virtual bool isMemberFunctor()const=0;
		virtual void destroy() { delete this; }
	};
	template<typename R = void()>
	class BaseFunctor;

	template<typename R> 
	struct BaseFunctor<R()>	: public IFunctor 
	{
		virtual R operator()() const=0;
		virtual BaseFunctor<R()>* clone()=0;
		virtual bool operator==(const BaseFunctor<R()>& other)const=0;
		bool operator!=(const BaseFunctor<R()>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1> 
	struct BaseFunctor<R(P1)> : public IFunctor 
	{
		virtual R operator()(P1 p1) const=0;
		virtual BaseFunctor<R(P1)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2>
	struct BaseFunctor<R(P1, P2)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2) const =0;
		virtual BaseFunctor<R(P1, P2)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2, typename P3>
	struct BaseFunctor<R(P1, P2, P3)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3) const =0;
		virtual BaseFunctor<R(P1, P2, P3)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4>
	struct BaseFunctor<R(P1, P2, P3, P4)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) const =0;
		virtual BaseFunctor<R(P1, P2, P3, P4)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3, P4)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct BaseFunctor<R(P1, P2, P3, P4, P5)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const =0;
		virtual BaseFunctor<R(P1, P2, P3, P4, P5)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3, P4, P5)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	struct BaseFunctor<R(P1, P2, P3, P4, P5, P6)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const =0;
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3, P4, P5, P6)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	struct BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) const =0;
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>& other)const {return !(*this == other);}
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	struct BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) const =0;
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const {return !(*this == other);}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	struct BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public IFunctor 
	{
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) const =0;
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>* clone()=0;
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const=0;
		bool operator!=(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const {return !(*this == other);}
	};
	
	template<typename R = void()>
	class Functor;
	
	template<typename R>
	class Functor<R()> : public BaseFunctor<R()> 
	{
	private:
		typedef R (*func_t)();

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()() const {return m_func();}
		virtual BaseFunctor<R()>* clone(){return new Functor<R()>(*this);}
		virtual bool operator==(const BaseFunctor<R()>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R()>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1>
	class Functor<R(P1)> : public BaseFunctor<R(P1)> 
	{
	private:
		typedef R (*func_t)(P1);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1) const {
			return m_func(p1);
		}
		virtual BaseFunctor<R(P1)>* clone(){return new Functor<R(P1)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2>
	class Functor<R(P1, P2)> : public BaseFunctor<R(P1, P2)> 
	{
	private:
		typedef R (*func_t)(P1, P2);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2) const {return m_func(p1, p2);}
		virtual BaseFunctor<R(P1, P2)>* clone(){return new Functor<R(P1, P2)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3>
	class Functor<R(P1, P2, P3)> : public BaseFunctor<R(P1, P2, P3)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3) const {return m_func(p1, p2, p3);}
		virtual BaseFunctor<R(P1, P2, P3)>* clone(){return new Functor<R(P1, P2, P3)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class Functor<R(P1, P2, P3, P4)> : public BaseFunctor<R(P1, P2, P3, P4)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) const {return m_func(p1, p2, p3, p4);}
		virtual BaseFunctor<R(P1, P2, P3, P4)>* clone(){return new Functor<R(P1, P2, P3, P4)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3, P4)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class Functor<R(P1, P2, P3, P4, P5)> : public BaseFunctor<R(P1, P2, P3, P4, P5)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {return m_func(p1, p2, p3, p4, p5);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5)>* clone(){return new Functor<R(P1, P2, P3, P4, P5)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3, P4, P5)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class Functor<R(P1, P2, P3, P4, P5, P6)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const {return m_func(p1, p2, p3, p4, p5, p6);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6)>* clone(){return new Functor<R(P1, P2, P3, P4, P5, P6)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3, P4, P5, P6)>& >(other).m_func;
		}


	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class Functor<R(P1, P2, P3, P4, P5, P6, P7)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6, P7);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) const {return m_func(p1, p2, p3, p4, p5, p6, p7);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>* clone(){return new Functor<R(P1, P2, P3, P4, P5, P6, P7)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3, P4, P5, P6, P7)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class Functor<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6, P7, P8);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) const {return m_func(p1, p2, p3, p4, p5, p6, p7, p8);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>* clone(){return new Functor<R(P1, P2, P3, P4, P5, P6, P7, P8)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3, P4, P5, P6, P7, P8)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class Functor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

	public:
		Functor(func_t f):m_func(f){}
		virtual ~Functor(){}

	protected:
		virtual bool isMemberFunctor()const{return false;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) const {return m_func(p1, p2, p3, p4, p5, p6, p7, p8, p9);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>* clone(){return new Functor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const
		{
			if(other.isMemberFunctor())return false;
			return m_func == static_cast<const Functor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& >(other).m_func;
		}

	private:
		func_t m_func;
	};


	template<class C, class R = void()>
	class MemberFunctor;

	template<class C, class R>
	class MemberFunctor<C, R()> : public BaseFunctor<R()> 
	{
	private:
		typedef R (C::*func_t)();

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()() const {return (m_object->*m_func)();}
		virtual BaseFunctor<R()>* clone(){return new MemberFunctor<C, R()>(*this);}
		virtual bool operator==(const BaseFunctor<R()>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R()>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R()>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1>
	class MemberFunctor<C, R(P1)> : public BaseFunctor<R(P1)> 
	{
	private:
		typedef R (C::*func_t)(P1);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1) const 
		{
			return (m_object->*m_func)(p1);
		}
		virtual BaseFunctor<R(P1)>* clone(){return new MemberFunctor<C, R(P1)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2>
	class MemberFunctor<C, R(P1, P2)> : public BaseFunctor<R(P1, P2)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2) const {return (m_object->*m_func)(p1, p2);}
		virtual BaseFunctor<R(P1, P2)>* clone(){return new MemberFunctor<C, R(P1, P2)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3>
	class MemberFunctor<C, R(P1, P2, P3)> : public BaseFunctor<R(P1, P2, P3)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3) const {return (m_object->*m_func)(p1, p2, p3);}
		virtual BaseFunctor<R(P1, P2, P3)>* clone(){return new MemberFunctor<C, R(P1, P2, P3)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4>
	class MemberFunctor<C, R(P1, P2, P3, P4)> : public BaseFunctor<R(P1, P2, P3, P4)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) const {return (m_object->*m_func)(p1, p2, p3, p4);}
		virtual BaseFunctor<R(P1, P2, P3, P4)>* clone(){return new MemberFunctor<C, R(P1, P2, P3, P4)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class MemberFunctor<C, R(P1, P2, P3, P4, P5)> : public BaseFunctor<R(P1, P2, P3, P4, P5)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {return (m_object->*m_func)(p1, p2, p3, p4, p5);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5)>* clone(){return new MemberFunctor<C, R(P1, P2, P3, P4, P5)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class MemberFunctor<C, R(P1, P2, P3, P4, P5, P6)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6)>* clone(){return new MemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6, P7);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6, p7);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>* clone(){return new MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6, P7, P8);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6, p7, p8);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>* clone(){return new MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};
	
	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

	public:
		MemberFunctor(C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~MemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>* clone(){return new MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& >(other).m_func && m_object == static_cast<const MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& >(other).m_object;
		}

	private:
		C* m_object;
		func_t m_func;
	};



	template<class C, class R = void()>
	class ConstMemberFunctor;
	
	template<class C, class R>
	class ConstMemberFunctor<C, R()> : public BaseFunctor<R()> 
	{
	private:
		typedef R (C::*func_t)()const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()() const {return (m_object->*m_func)();}
		virtual BaseFunctor<R()>* clone(){return new ConstMemberFunctor<C, R()>(*this);}
		virtual bool operator==(const BaseFunctor<R()>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R()>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R()>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1>
	class ConstMemberFunctor<C, R(P1)> : public BaseFunctor<R(P1)> 
	{
	private:
		typedef R (C::*func_t)(P1)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1) const {return (m_object->*m_func)(p1);}
		virtual BaseFunctor<R(P1)>* clone(){return new ConstMemberFunctor<C, R(P1)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2>
	class ConstMemberFunctor<C, R(P1, P2)> : public BaseFunctor<R(P1, P2)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2) const {return (m_object->*m_func)(p1, p2);}
		virtual BaseFunctor<R(P1, P2)>* clone(){return new ConstMemberFunctor<C, R(P1, P2)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3>
	class ConstMemberFunctor<C, R(P1, P2, P3)> : public BaseFunctor<R(P1, P2, P3)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3) const {return (m_object->*m_func)(p1, p2, p3);}
		virtual BaseFunctor<R(P1, P2, P3)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4>
	class ConstMemberFunctor<C, R(P1, P2, P3, P4)> : public BaseFunctor<R(P1, P2, P3, P4)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) const {return (m_object->*m_func)(p1, p2, p3, p4);}
		virtual BaseFunctor<R(P1, P2, P3, P4)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3, P4)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class ConstMemberFunctor<C, R(P1, P2, P3, P4, P5)> : public BaseFunctor<R(P1, P2, P3, P4, P5)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const {return (m_object->*m_func)(p1, p2, p3, p4, p5);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6, P7)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6, p7);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};

	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6, P7, P8)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6, p7, p8);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};
	
	template<class C, class R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> 
	{
	private:
		typedef R (C::*func_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9)const;

	public:
		ConstMemberFunctor(const C& o, func_t f):m_object(&o),m_func(f){}
		virtual ~ConstMemberFunctor(){}

	protected:
		virtual bool isMemberFunctor()const{return true;}

	public:
		virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) const {return (m_object->*m_func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);}
		virtual BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>* clone(){return new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>(*this);}
		virtual bool operator==(const BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const
		{
			if(!other.isMemberFunctor())return false;
			return m_func == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& >(other).m_func && m_object == static_cast<const ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& >(other).m_object;
		}

	private:
		const C* m_object;
		func_t m_func;
	};
	//! \endcond

	//! \cond FUNCTIONS

	class IFunction
	{
	public:
		virtual ~IFunction(){}
		virtual bool isValid()const=0;
		virtual IFunction* clone()const=0;
		virtual void destroy() { delete this; }
	};

	template<typename R = void()>
	class Function;


	template<typename R>
	class Function<R()> : public IFunction 
	{
	private:
		typedef R (*func_t)();
		typedef Functor<R()> functor_t;
		typedef BaseFunctor<R()> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R()>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R()>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R()>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R()>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()() const 
		{
			assert(m_func != NULL);
			return (*m_func)();
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1>
	class Function<R(P1)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1);
		typedef Functor<R(P1)> functor_t;
		typedef BaseFunctor<R(P1)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1);
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2>
	class Function<R(P1, P2)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2);
		typedef Functor<R(P1, P2)> functor_t;
		typedef BaseFunctor<R(P1, P2)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2);
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2, typename P3>
	class Function<R(P1, P2, P3)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3);
		typedef Functor<R(P1, P2, P3)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3) const {return (*m_func)(p1, p2, p3);}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class Function<R(P1, P2, P3, P4)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4);
		typedef Functor<R(P1, P2, P3, P4)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3, P4)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3, P4)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3, P4)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3, P4)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3, P4)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2, p3, p4);
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class Function<R(P1, P2, P3, P4, P5)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5);
		typedef Functor<R(P1, P2, P3, P4, P5)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3, P4, P5)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3, P4, P5)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3, P4, P5)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3, P4, P5)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2, p3, p4, p5);
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class Function<R(P1, P2, P3, P4, P5, P6)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6);
		typedef Functor<R(P1, P2, P3, P4, P5, P6)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3, P4, P5, P6)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3, P4, P5, P6)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3, P4, P5, P6)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3, P4, P5, P6)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2, p3, p4, p5, p6);
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class Function<R(P1, P2, P3, P4, P5, P6, P7)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef Functor<R(P1, P2, P3, P4, P5, P6, P7)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3, P4, P5, P6, P7)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3, P4, P5, P6, P7)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3, P4, P5, P6, P7)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2, p3, p4, p5, p6, p7);
		}

	private:
		base_functor_t* m_func;
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class Function<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef Functor<R(P1, P2, P3, P4, P5, P6, P7, P8)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3, P4, P5, P6, P7, P8)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3, P4, P5, P6, P7, P8)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2, p3, p4, p5, p6, p7, p8);
		}

	private:
		base_functor_t* m_func;
	};
	
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class Function<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public IFunction 
	{
	private:
		typedef R (*func_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef Functor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> functor_t;
		typedef BaseFunctor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> base_functor_t;

	public:
		Function():m_func(NULL){}
		Function(func_t f):m_func(new functor_t(f)){}
		template<class C, class F> Function(C& c, const F& f):m_func(new typename SK::MethodTypeTrait<C,F>::memberFunctor_t(c, f)){}
		template<class C, class F> Function(const C& c, const F& f):m_func(new ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>(c, f)){}
		virtual ~Function(){if(NULL != m_func) m_func->destroy();}
		virtual bool operator==(const Function<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const{return *m_func == *other.m_func;}
		bool operator!=(const Function<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& other)const{return !(*this == other);}

		Function(const Function& other):m_func(other.m_func->clone()){}
		Function& operator=(const Function& other)
		{
			Function tmp = other;
			swap(tmp);
			return *this;
		}
		virtual bool isValid()const {return m_func!= NULL;}
		virtual Function<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>* clone()const {return new Function(*this);}

	private:
		void swap(Function& other) {std::swap(m_func, other.m_func);}

	public:
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) const 
		{
			assert(m_func != NULL);
			return (*m_func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
		}

	private:
		base_functor_t* m_func;
	};

	template <class T>
	SK::Function<typename SK::FunctionTypeTrait<T>::function_t> make_function(T func)
	{
		return SK::Function<typename SK::FunctionTypeTrait<T>::function_t>(func);
	}
	template <class C, class T>
	SK::Function<typename SK::MethodTypeTrait<C, T>::method_t> make_function(C& obj, T func)
	{
		return SK::Function<typename SK::MethodTypeTrait<C, T>::method_t>(obj, func);
	}
	template <class C, class T>
	SK::Function<typename SK::MethodTypeTrait<C, T>::method_t> make_function(const C& obj, T const func)
	{
		return SK::Function<typename SK::MethodTypeTrait<C, T>::method_t>(obj, func);
	}
	//! \endcond

}
