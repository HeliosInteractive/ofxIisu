
#pragma once

#include <Framework/Types/RefTypeTrait.h>
#include <Foundation/Services/Types/RawData.h>
#include <Foundation/Services/Types/FunctionTypeInfo.h>
#include <Foundation/DataTypes/MetaInformation/MetaInfoImpl.h>

namespace SK
{
	class CommandManager ;

	/**
	 * \brief	Interface of a generic Command. 
	 */

	class ICommand 
	{
	public:

		/**
		 * \fn	virtual const char* ICommand::getName() const = 0;
		 *
		 * \brief	Gets the command name.
		 *
		 * \return	The command name
		 */

		virtual const char* getName() const = 0;

		/**
		 * \fn	virtual SK::Return<SK::Attributes> ICommand::getAttributes() const =0;
		 *
		 * \brief	Gets the commant attributes field.
		 *
		 * \return	The attributes, if successful
		 */

		virtual SK::Return<SK::Attributes> getAttributes() const =0;

		/**
		 * \fn	virtual SK::Return<bool> ICommand::isValid()const =0;
		 *
		 * \brief	returns true if the command handle is valid
		 *
		 * \return	true if the command pointer  is valid
		 */

		virtual SK::Return<bool> isValid()const =0;
	};

	/**
	 * \class	CommandBase
	 *
	 * \brief	Base template interface for command handle. 
	 */
	template <typename T>
	class CommandBase : public ICommand
	{
	public:

		/**
		 * \fn	virtual SK::Return< SK::MetaInfo<T> > CommandBase::getMetaInfo() const = 0;
		 *
		 * \brief	Gets the command's meta information.
		 *
		 * \return	The meta information.
		 */

		virtual SK::Return< SK::MetaInfo<T> > getMetaInfo() const = 0;
	};

	namespace ReturnValue
	{
		/**
		 * \enum	Attribute
		 *
		 * \brief	Values that represent Command call return behaviors. 
		 */

		enum Attribute
		{
			IMMEDIATE,
			DROP,
			DELAY
		};
	}
	

	/**
	 * \class	Command
	 *
	 * \brief	Command handles specialized interface. (internal use) 
	 */
	template<typename R = void()>
	class Command;
	
	//! \cond COMMANDS
	template<typename R>
	class Command<R()> : public CommandBase<R()>
	{
	public:
		virtual SK::Return<R> operator()(SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1>
	class Command<R(P1)> : public CommandBase<R(P1)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2>
	class Command<R(P1, P2)> : public CommandBase<R(P1, P2)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3>
	class Command<R(P1, P2, P3)> : public CommandBase<R(P1, P2, P3)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class Command<R(P1, P2, P3, P4)> : public CommandBase<R(P1, P2, P3, P4)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class Command<R(P1, P2, P3, P4, P5)> : public CommandBase<R(P1, P2, P3, P4, P5)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class Command<R(P1, P2, P3, P4, P5, P6)> : public CommandBase<R(P1, P2, P3, P4, P5, P6)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class Command<R(P1, P2, P3, P4, P5, P6, P7)> : public CommandBase<R(P1, P2, P3, P4, P5, P6, P7)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class Command<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public CommandBase<R(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>

	

	class Command<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public CommandBase<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
	public:

		
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;


		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	//! \endcond

	//! \cond COMMANDS_VOID
	template<>
	class Command<void()> : public CommandBase<void()>
	{
	public:
		virtual SK::Result operator()() const = 0;
	};
	template<typename P1>
	class Command<void(P1)> : public CommandBase<void(P1)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1) const = 0;
	};
	template<typename P1, typename P2>
	class Command<void(P1, P2)> : public CommandBase<void(P1, P2)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2) const = 0;
	};
	template<typename P1, typename P2, typename P3>
	class Command<void(P1, P2, P3)> : public CommandBase<void(P1, P2, P3)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3) const = 0;
	};
	template<typename P1, typename P2, typename P3, typename P4>
	class Command<void(P1, P2, P3, P4)> : public CommandBase<void(P1, P2, P3, P4)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4) const = 0;
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	class Command<void(P1, P2, P3, P4, P5)> : public CommandBase<void(P1, P2, P3, P4, P5)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5) const = 0;
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class Command<void(P1, P2, P3, P4, P5, P6)> : public CommandBase<void(P1, P2, P3, P4, P5, P6)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6) const = 0;
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class Command<void(P1, P2, P3, P4, P5, P6, P7)> : public CommandBase<void(P1, P2, P3, P4, P5, P6, P7)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7) const = 0;
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class Command<void(P1, P2, P3, P4, P5, P6, P7, P8)> : public CommandBase<void(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8) const = 0;
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class Command<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public CommandBase<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
	public:
		virtual SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9) const = 0;
	};
	//! \endcond
	
	//! \cond COMMANDS_RETURN
	template<typename R>
	class Command<SK::Return<R>()> : public CommandBase<SK::Return<R>()>
	{
	public:
		virtual SK::Return<R> operator()(SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1>
	class Command<SK::Return<R>(P1)> : public CommandBase<SK::Return<R>(P1)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2>
	class Command<SK::Return<R>(P1, P2)> : public CommandBase<SK::Return<R>(P1, P2)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3>
	class Command<SK::Return<R>(P1, P2, P3)> : public CommandBase<SK::Return<R>(P1, P2, P3)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class Command<SK::Return<R>(P1, P2, P3, P4)> : public CommandBase<SK::Return<R>(P1, P2, P3, P4)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class Command<SK::Return<R>(P1, P2, P3, P4, P5)> : public CommandBase<SK::Return<R>(P1, P2, P3, P4, P5)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class Command<SK::Return<R>(P1, P2, P3, P4, P5, P6)> : public CommandBase<SK::Return<R>(P1, P2, P3, P4, P5, P6)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class Command<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7)> : public CommandBase<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class Command<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8)> : public CommandBase<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};


	 template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class Command<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public CommandBase<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
	public:
		virtual SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const = 0;
		virtual SK::Return<R> waitForReturnValue(int32_t timeout)const = 0;
		virtual SK::Return<bool> isReturnValueReady() const = 0;
		virtual SK::Return<R> tryGetReturnValue() const = 0;
	};
	//! \endcond
	
	//! \cond COMMAN_MANAGER_PROXY
	
	class IISUSDK_API CommandManagerProxy {
	public:
		CommandManagerProxy(SK::CommandManager &commandManager) ;
		CommandManagerProxy() ;
		~CommandManagerProxy() ;
		SK::Result sendCommand(const SK::String&  sCmd, const SK::Array<SK::RawData>& params, const SK::FunctionTypeInfo& typeInfo, uint64_t& commandCallerID, bool dropReturn = false)  ;
		SK::Result waitForReturnValue(uint64_t& commandCallerID, SK::RawData &returnValue, int32_t timeout = 0) ;
		SK::Return<bool> isReturnValueReady(uint64_t commandCallerID)  ;
		SK::Result tryGetReturnValue(uint64_t& commandCallerID, SK::RawData& returnValue) ;

		bool isValid()const;
		SK::Return<bool> commandIsRegistered(const SK::String& name) const;

		virtual SK::Return<SK::Attributes> getAttributes(const SK::String& commandName)const;
		template<typename T>
		SK::Return< SK::MetaInfo<T> > getMetaInfo(const SK::String& commandName)const
		{
			SK::Return<SK::RawData> res = getMetaInfoImpl(commandName, SK::Type< SK::MetaInfo<T> >::INFO);
			RETURN_IF_FAILED(res) ;
			return res.get().getRef< SK::MetaInfo<T> >();
		}

	private:
		virtual SK::Return<SK::RawData> getMetaInfoImpl(const SK::String& commandName, const SK::TypeInfo& typeInfo)const;
		SK::CommandManager *m_commandManager ;
	} ;

	//! \endcond

	/**
	 * \class	ICommandHandle
	 *
	 * \brief	Implementation of Command's non function template specific functions. (internal use) 
	 */

	template <typename T>
	class ICommandHandle : public Command<T>
	{
	protected:
		ICommandHandle(SK::CommandManager &pCommandManager, const char* name): 
		m_proxy(pCommandManager), 
		m_name(name?name:""), 
		m_typeInfo(SK::FunctionType<T>::INFO),
		m_id(0)
		{
		}
		ICommandHandle():
		m_name(""), 
		m_typeInfo(SK::FunctionType<T>::INFO),
		m_id(0)
		{

		}
		virtual ~ICommandHandle() {}

	public:

		virtual const char* getName() const {return m_name.ptr ();}
		virtual SK::Return<SK::Attributes> getAttributes() const
		{
			return m_proxy.getAttributes(m_name);
		}
		virtual SK::Return< SK::MetaInfo<T> > getMetaInfo() const
		{
			return m_proxy.getMetaInfo<T>(m_name);
		}
		virtual SK::Return<bool> isValid()const
		{
			if(!m_proxy.isValid()) return false;
			return m_proxy.commandIsRegistered(m_name);
		}

	protected:
 		SK::Result sendCommand(const SK::Array<SK::RawData>& params, bool dropReturn) const
 		{
			if(!m_proxy.isValid()) return SK::Result("Command is not properly registered", SK::INVALID_HANDLE);
 			return m_proxy.sendCommand(m_name, params, m_typeInfo, m_id, dropReturn);
 		}
		SK::Result waitForReturnValue(SK::RawData &returnValue, int32_t timeout = 0)const
 		{
			if(!m_proxy.isValid()) return SK::Result("Command is not properly registered", SK::INVALID_HANDLE);
 			return m_proxy.waitForReturnValue(m_id, returnValue, timeout);
 		}
 		SK::Return<bool> isReturnValueReady()const 
 		{
			if(!m_proxy.isValid()) return SK::Result("Command is not properly registered", SK::INVALID_HANDLE);
 			return m_proxy.isReturnValueReady(m_id);
 		}
 		SK::Result tryGetReturnValue(SK::RawData &returnValue)const 
 		{
			if(!m_proxy.isValid()) return SK::Result("Command is not properly registered", SK::INVALID_HANDLE);
 			return m_proxy.tryGetReturnValue(m_id, returnValue);
 		}

	public:
		ICommandHandle(const ICommandHandle& other):
	    m_name(other.m_name),
		m_typeInfo(other.m_typeInfo),
		m_id(0),
		m_proxy(other.m_proxy)
		{
		}

	protected:
		virtual void swap(ICommandHandle& other)
		{
			std::swap(m_name, other.m_name);
			std::swap(m_typeInfo, other.m_typeInfo);
			std::swap(m_id, other.m_id);
			std::swap(m_proxy, other.m_proxy);
		}


	protected:
		SK::String m_name;
		SK::FunctionTypeInfo m_typeInfo;
		mutable uint64_t m_id;
		mutable CommandManagerProxy m_proxy ;
	};

	template<typename R = void()>
	class CommandHandle;

	//! \cond COMMAND_HANDLES
	template<typename R>
	class CommandHandle<R()> : public ICommandHandle<R()>
	{
		typedef ICommandHandle<R()> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path) {}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
		
			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}

		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1>
	class CommandHandle<R(P1)> : public ICommandHandle<R(P1)>
	{
		typedef ICommandHandle<R(P1)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>();// SK::RawDataConverter<R>(rd).convert(true);
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>();//SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2>
	class CommandHandle<R(P1, P2)> : public ICommandHandle<R(P1, P2)>
	{
		typedef ICommandHandle<R(P1, P2)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3>
	class CommandHandle<R(P1, P2, P3)> : public ICommandHandle<R(P1, P2, P3)>
	{
		typedef ICommandHandle<R(P1, P2, P3)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class CommandHandle<R(P1, P2, P3, P4)> : public ICommandHandle<R(P1, P2, P3, P4)>
	{
		typedef ICommandHandle<R(P1, P2, P3, P4)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class CommandHandle<R(P1, P2, P3, P4, P5)> : public ICommandHandle<R(P1, P2, P3, P4, P5)>
	{
		typedef ICommandHandle<R(P1, P2, P3, P4, P5)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class CommandHandle<R(P1, P2, P3, P4, P5, P6)> : public ICommandHandle<R(P1, P2, P3, P4, P5, P6)>
	{
		typedef ICommandHandle<R(P1, P2, P3, P4, P5, P6)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class CommandHandle<R(P1, P2, P3, P4, P5, P6, P7)> : public ICommandHandle<R(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef ICommandHandle<R(P1, P2, P3, P4, P5, P6, P7)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class CommandHandle<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public ICommandHandle<R(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef ICommandHandle<R(P1, P2, P3, P4, P5, P6, P7, P8)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};
	//! \endcond
	/**
	 * 
	 * \brief	The CommandHandle class provides access to direct calls to specific functions of iisu. 
	 * 			
	 *	        
	 *
	 * \tparam	R 	Type of the return value.
	 * \tparam	P1	    Type of the first parameter.
	 * \tparam	P2  	Type of the second parameter.
	 * \tparam	P3  	Type of the third parameter.
	 * \tparam	P4  	Type of the fourth parameter.
	 * \tparam	P5  	Type of the fifth parameter.
	 * \tparam	P6  	Type of the sixth parameter.
	 * \tparam	P7  	Type of the seventh parameter.
	 * \tparam	P8  	Type of the eighth parameter.
	 * \tparam	P9  	Type of the ninth parameter.
	 *	  
	 *	 	   
	 *	 
	 *	 The CommandHandle acts as a function object and, to use it, you need only to call the its () operator. <br/>
	 * 			This class is a specialization with a return type and 9 arguments. The number of arguments can vary from zero to nine.<br/>
	 * 			 Only this specialization with 9 parameters is documented, the other specializations aren't but their documentation is very similar to this one.			
	 */

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class CommandHandle<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public ICommandHandle<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef ICommandHandle<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> base_t;
	public:

		/**
		 * \brief	Constructor.
		 *
		 * \param [in,out]	pCommandManager	the CommandManager.
		 * \param	path				   	iisu path of the command (syntax : "LAYER.SUBPATH.CommandName").
		 */

		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}

		/**
		 *
		 * \brief	Default constructor.
		 */

		CommandHandle():base_t() {}

		/**
		 *
		 * \brief	Destructor.
		 */

		virtual ~CommandHandle() {}

		/**
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		CommandHandle(const CommandHandle& other):base_t(other) {}

		/**
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A shallow copy of this object.
		 */

		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}

		/**
		 *
		 * \brief	Call operator.
		 *
		 * \param	p1	    The first parameter.
		 * \param	p2  	The second parameter.
		 * \param	p3  	The third parameter.
		 * \param	p4  	The fourth parameter.
		 * \param	p5  	The fifth parameter.
		 * \param	p6  	The sixth parameter.
		 * \param	p7  	The seventh parameter.
		 * \param	p8  	The eighth parameter.
		 * \param	p9  	The ninth parameter.
		 * \param   returnBehavior if set to IMMEDIATE, the call to the function is made directly and waits to return a SK::Return<R> containing the return value.<br/>
		 *						   if set to DELAY, the call returns immediately a SK::Result (no return value). The availability of the real return value can then be obtained by calling waitForReturnValue and the real value can be obtained by calling tryGetReturnValue()<br/>
		 *						   if set to DROP, tells the command to just ignore the return value. The call returns immediately.				   
		 *		 
		 *	\return A Return<R> object containing return value (if returnBehavior is set to IMMEDIATE) or error code
		 *			
		 *	If R is of the for SK::Return<X> the the return type should be SK::Return<SK::Return<X>>, to avoid the 
		 *	burden to check for both of the Return the api merge those two Return. So that if R is SK::Return<X> then 
		 *	SK::Return<R> is Return<X>.
		 *	\sa tryGetReturnValue
		 *	\sa isReturnValueReady
		 */


		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));params.pushBack(SK::RawData(p9, SK::Type<P9>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}

		/**
		 *
		 * \brief	Waits for the command call to be completed before returning its return value.
		 *
		 * \param	timeout	(optional) the timeout.
		 *
		 * \return	A Return<R> object containing the return value of the command call.
		 * 			
		 *	If R is of the for SK::Return<X> the the return type should be SK::Return<SK::Return<X>>, to avoid the 
		 *	burden to check for both of the Return the api merge those two Return. So that if R is SK::Return<X> then 
		 *	SK::Return<R> is Return<X>.
		 */

		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}

		/**
		 * \brief	Checks if the return value of a DELAY call is ready.
		 *
		 * \return	The result of the query.
		 */

		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}

		/**
		 * \brief	Tries to get the return value of a DELAY call, If it's not yet ready, return an error
		 *
		 * \return	A Return<R> object containing either the return value of the command call, or an error message.
		 * 			
		 *	If R is of the for SK::Return<X> the the return type should be SK::Return<SK::Return<X>>, to avoid the 
		 *	burden to check for both of the Return the api merge those two Return. So that if R is SK::Return<X> then 
		 *	SK::Return<R> is Return<X>.
		 */

		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type<R>::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy<R>(); //SK::RawDataConverter<R>(rd).convert();
		}
	};

	//! \cond COMMAND_HANDLES_VOID
	template<>
	class CommandHandle<void()> : public ICommandHandle<void()>
	{
		typedef ICommandHandle<void()> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path) {}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()() const
		{
			SK::Array<RawData> params;

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1>
	class CommandHandle<void(P1)> : public ICommandHandle<void(P1)>
	{
		typedef ICommandHandle<void(P1)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}

		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2>
	class CommandHandle<void(P1, P2)> : public ICommandHandle<void(P1, P2)>
	{
		typedef ICommandHandle<void(P1, P2)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2, typename P3>
	class CommandHandle<void(P1, P2, P3)> : public ICommandHandle<void(P1, P2, P3)>
	{
		typedef ICommandHandle<void(P1, P2, P3)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2, typename P3, typename P4>
	class CommandHandle<void(P1, P2, P3, P4)> : public ICommandHandle<void(P1, P2, P3, P4)>
	{
		typedef ICommandHandle<void(P1, P2, P3, P4)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	class CommandHandle<void(P1, P2, P3, P4, P5)> : public ICommandHandle<void(P1, P2, P3, P4, P5)>
	{
		typedef ICommandHandle<void(P1, P2, P3, P4, P5)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class CommandHandle<void(P1, P2, P3, P4, P5, P6)> : public ICommandHandle<void(P1, P2, P3, P4, P5, P6)>
	{
		typedef ICommandHandle<void(P1, P2, P3, P4, P5, P6)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class CommandHandle<void(P1, P2, P3, P4, P5, P6, P7)> : public ICommandHandle<void(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef ICommandHandle<void(P1, P2, P3, P4, P5, P6, P7)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class CommandHandle<void(P1, P2, P3, P4, P5, P6, P7, P8)> : public ICommandHandle<void(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef ICommandHandle<void(P1, P2, P3, P4, P5, P6, P7, P8)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));

			return base_t::sendCommand(params, true);
		}
	};
	//! \endcond
	/**
	 * 
	 * \brief	The CommandHandle class provides access to direct calls to specific functions of iisu with no return type. 
	 * 			
	 *	        
	 *
	 * \tparam	P1	    Type of the first parameter.
	 * \tparam	P2  	Type of the second parameter.
	 * \tparam	P3  	Type of the third parameter.
	 * \tparam	P4  	Type of the fourth parameter.
	 * \tparam	P5  	Type of the fifth parameter.
	 * \tparam	P6  	Type of the sixth parameter.
	 * \tparam	P7  	Type of the seventh parameter.
	 * \tparam	P8  	Type of the eighth parameter.
	 * \tparam	P9  	Type of the ninth parameter.
	 *	  
	 *	 	   
	 *	 
	 *	 The CommandHandle acts as a function object and, to use it, you need only to call the its () operator. <br/>
	 * 			This class is a specialization with a return type and 9 arguments. The number of arguments can vary from zero to nine.<br/>
	 * 			 Only this specialization with 9 parameters is documented, the other specializations aren't but their documentation is very similar to this one.			
	 */
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class CommandHandle<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public ICommandHandle<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef ICommandHandle<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)> base_t;
	public:
		/**
		 * \brief	Constructor.
		 *
		 * \param [in,out]	pCommandManager	the CommandManager.
		 * \param	path				   	iisu path of the command (syntax : "LAYER.SUBPATH.CommandName").
		 */
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		/**
		 *
		 * \brief	Default constructor.
		 */
		CommandHandle():base_t() {}
		/**
		 *
		 * \brief	Destructor.
		 */
		virtual ~CommandHandle() {}

		/**
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */
		CommandHandle(const CommandHandle& other):base_t(other) {}
		/**
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A shallow copy of this object.
		 */
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		/**
		 *
		 * \brief	Call operator.
		 *
		 * \param	p1	    The first parameter.
		 * \param	p2  	The second parameter.
		 * \param	p3  	The third parameter.
		 * \param	p4  	The fourth parameter.
		 * \param	p5  	The fifth parameter.
		 * \param	p6  	The sixth parameter.
		 * \param	p7  	The seventh parameter.
		 * \param	p8  	The eighth parameter.
		 * \param	p9  	The ninth parameter.
		 *
		 *	\return A Result object containing error code related to the command call.
		 *			
		 *	The Result returned by this call is not related to the command itself (since the command signature is void) 
		 *	but to the command call that can potentially fail.
		 */
		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));params.pushBack(SK::RawData(p9, SK::Type<P9>::INFO));

			return base_t::sendCommand(params, true);
		}
	};

	//! \cond COMMAND_HANDLES_RETURN
	template<typename R>
	class CommandHandle<SK::Return<R>()> : public ICommandHandle<SK::Return<R>()>
	{
		typedef ICommandHandle<SK::Return<R>()> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path) {}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}

		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1>
	class CommandHandle<SK::Return<R>(P1)> : public ICommandHandle<SK::Return<R>(P1)>
	{
		typedef ICommandHandle<SK::Return<R>(P1)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2>
	class CommandHandle<SK::Return<R>(P1, P2)> : public ICommandHandle<SK::Return<R>(P1, P2)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3>
	class CommandHandle<SK::Return<R>(P1, P2, P3)> : public ICommandHandle<SK::Return<R>(P1, P2, P3)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	class CommandHandle<SK::Return<R>(P1, P2, P3, P4)> : public ICommandHandle<SK::Return<R>(P1, P2, P3, P4)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3, P4)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class CommandHandle<SK::Return<R>(P1, P2, P3, P4, P5)> : public ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class CommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6)> : public ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class CommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7)> : public ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class CommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8)> : public ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class CommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef ICommandHandle<SK::Return<R>(P1, P2, P3, P4, P5, P6, P7, P8, P9)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Return<R> operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));params.pushBack(SK::RawData(p9, SK::Type<P9>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Return<R> waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Return<R> tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Return<R> >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getCopy< SK::Return<R> >(); //SK::RawDataConverter< SK::Return<R> >(rd).convert();
		}
	};
	//! \endcond

	//! \cond COMMAND_HANDLES_RESULT
	template<>
	class CommandHandle<SK::Result()> : public ICommandHandle<SK::Result()>
	{
		typedef ICommandHandle<SK::Result()> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path) {}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}

		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1>
	class CommandHandle<SK::Result(P1)> : public ICommandHandle<SK::Result(P1)>
	{
		typedef ICommandHandle<SK::Result(P1)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2>
	class CommandHandle<SK::Result(P1, P2)> : public ICommandHandle<SK::Result(P1, P2)>
	{
		typedef ICommandHandle<SK::Result(P1, P2)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3>
	class CommandHandle<SK::Result(P1, P2, P3)> : public ICommandHandle<SK::Result(P1, P2, P3)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3, typename P4>
	class CommandHandle<SK::Result(P1, P2, P3, P4)> : public ICommandHandle<SK::Result(P1, P2, P3, P4)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3, P4)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	class CommandHandle<SK::Result(P1, P2, P3, P4, P5)> : public ICommandHandle<SK::Result(P1, P2, P3, P4, P5)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3, P4, P5)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class CommandHandle<SK::Result(P1, P2, P3, P4, P5, P6)> : public ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class CommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7)> : public ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class CommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)> : public ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class CommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef ICommandHandle<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)> base_t;
	public:
		CommandHandle(SK::CommandManager &pCommandManager, const char *path):base_t(pCommandManager, path){}
		CommandHandle():base_t() {}
		virtual ~CommandHandle() {}

		CommandHandle(const CommandHandle& other):base_t(other) {}
		CommandHandle& operator=(const CommandHandle& other)
		{
			CommandHandle tmp = other;
			this->swap(tmp);
			return *this;
		}



		SK::Result operator()(typename SK::RefTypeTrait<P1>::add_const_ref_t p1, typename SK::RefTypeTrait<P2>::add_const_ref_t p2, typename SK::RefTypeTrait<P3>::add_const_ref_t p3, typename SK::RefTypeTrait<P4>::add_const_ref_t p4, typename SK::RefTypeTrait<P5>::add_const_ref_t p5, typename SK::RefTypeTrait<P6>::add_const_ref_t p6, typename SK::RefTypeTrait<P7>::add_const_ref_t p7, typename SK::RefTypeTrait<P8>::add_const_ref_t p8, typename SK::RefTypeTrait<P9>::add_const_ref_t p9, SK::ReturnValue::Attribute returnBehavior = SK::ReturnValue::IMMEDIATE, int32_t timeout = 0) const
		{
			SK::Array<RawData> params;
			params.pushBack(SK::RawData(p1, SK::Type<P1>::INFO));params.pushBack(SK::RawData(p2, SK::Type<P2>::INFO));params.pushBack(SK::RawData(p3, SK::Type<P3>::INFO));params.pushBack(SK::RawData(p4, SK::Type<P4>::INFO));params.pushBack(SK::RawData(p5, SK::Type<P5>::INFO));params.pushBack(SK::RawData(p6, SK::Type<P6>::INFO));params.pushBack(SK::RawData(p7, SK::Type<P7>::INFO));params.pushBack(SK::RawData(p8, SK::Type<P8>::INFO));params.pushBack(SK::RawData(p9, SK::Type<P9>::INFO));

			SK::Result res = base_t::sendCommand(params, (returnBehavior == SK::ReturnValue::DROP));
			if(res.failed())return res;
			return (returnBehavior != SK::ReturnValue::IMMEDIATE)?res:waitForReturnValue(timeout);
		}
		SK::Result waitForReturnValue(int32_t timeout = 0) const 
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::waitForReturnValue(rd, timeout);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
		SK::Return<bool> isReturnValueReady() const {return base_t::isReturnValueReady();}
		SK::Result tryGetReturnValue()const
		{
			SK::RawData rd((void*)NULL, SK::Type< SK::Result >::INFO, false);
			SK::Result res = base_t::tryGetReturnValue(rd);
			if(res.failed())return res;
			return rd.getRef<SK::Result>();
		}
	};
	//! \endcond



}
