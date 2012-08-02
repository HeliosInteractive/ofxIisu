#pragma once


namespace SK
{
	/**
	 * \struct	Accessibility
	 *
	 * \brief	Accessibility of an iisu path. 
	 */

	struct Accessibility
	{
		enum Enum
		{
			PRIVATE = 0x00000001,
			PUBLIC  = 0x00000002,

			MASK	= 0x0000000F 
		};
	};

	/**
	 * \struct	Lifecycle
	 *
	 * \brief	Life cycle of an iisu path. 
	 * 			
	 * 			This only applies to data/parameters paths.
	 */

	struct Lifecycle
	{
		enum Enum
		{
			TRANSIENT	  = 0x00000010,
			SERIALIZABLE  = 0x00000020,

			MASK		  = 0x000000F0
		};
	};

	/**
	 * \struct	Permission
	 *
	 * \brief	Permission of an iisu path.
	 * 			
	 * 			This only applies to data/parameters paths.
	 */

	struct Permission
	{
		enum Enum
		{
			READ_ONLY		= 0x00000100,
			READ_WRITE		= 0x00000200,

			MASK			= 0x00000F00
		};
	};

	/**
	 * \struct	Ownership
	 *
	 * \brief	Internal use 
	 */

	struct Ownership
	{
		enum Enum
		{
			INTERNAL	= 0x00001000,
			EXTERNAL	= 0x00002000,

			MASK		= 0x0000F000
		};
	};

	/**
	 * \struct	NodeType
	 *
	 * \brief	Type of the iisu path 
	 */

	struct NodeType
	{
		enum Enum
		{
			DATA		= 0x00010000,
			PARAMETER	= 0x00020000,
			COMMAND		= 0x00040000,
			EVENT		= 0x00080000,

			MASK		= 0x000F0000
		};
	};

	/**
	 * \struct	Consistence
	 *
	 * \brief	Internal use 
	 */

	struct Consistence
	{

		enum Enum
		{
			// The value never changes. 
			CONSTANT	= 0x00100000,
			// The value changes at each frame. 
			VOLATILE	= 0x00200000, 
			// The value may changes but not necessary at each frame. 
			MUTABLE		= 0x00400000,

			MASK		= 0x00F00000
		};
	};

	/**
	 * \struct	Synchronicity
	 *
	 * \brief	Synchronicity of an iisu path.
	 * 			
	 * 			This only applies to command/event paths.
	 */

	struct Synchronicity
	{
		enum Enum
		{
			///< Is executed instantly. 
			SYSTEM		= 0x01000000, 
			///< Is delayed until all processing for the current frame is done. 
			INTER_PULSE	= 0x02000000, 

			MASK		= 0x0F000000
		};
	};

	/**
	 * \class	Attributes
	 *
	 * \brief	Attributes of an iisu path.
	 * 			 
	 * 			 An iisu path can point to a data, a parameter, a command or an event.
	 */

	class Attributes
	{
	private:
		enum Enum
		{
			PRIVATE			= SK::Accessibility::PRIVATE,
			PUBLIC			= SK::Accessibility::PUBLIC,

			TRANSIENT		= SK::Lifecycle::TRANSIENT,
			SERIALIZABLE	= SK::Lifecycle::SERIALIZABLE,

			READ_ONLY		= SK::Permission::READ_ONLY,
			READ_WRITE		= SK::Permission::READ_WRITE,

			INTERNAL		= SK::Ownership::INTERNAL,
			EXTERNAL		= SK::Ownership::EXTERNAL,

			DATA			= SK::NodeType::DATA,
			PARAMETER		= SK::NodeType::PARAMETER,
			COMMAND			= SK::NodeType::COMMAND,
			EVENT			= SK::NodeType::EVENT,

			CONSTANT		= SK::Consistence::CONSTANT,	// do not change
			VOLATILE		= SK::Consistence::VOLATILE,	// change at each frame
			MUTABLE			= SK::Consistence::MUTABLE,		// can change but not at each frame

			SYSTEM			= SK::Synchronicity::SYSTEM,
			INTER_PULSE		= SK::Synchronicity::INTER_PULSE
		}m_value;

	public:
		explicit Attributes(uint32_t id = 0): m_value(static_cast<Enum>(id)){}

		/**
		 * \fn	uint32_t Attributes::getRawValue()const
		 *
		 * \brief	Gets the raw value as an unsigned integer of 32bit.
		 *
		 * \return	The raw value.
		 */

		uint32_t getRawValue()const {return m_value;}

		/**
		 * \fn	void Attributes::setRawValue(uint32_t value)
		 *
		 * \brief	Sets a raw value as an unsigned integer of 32bit.
		 *
		 * \param	value	The value.
		 */

		void setRawValue(uint32_t value) {m_value = static_cast<Enum>(value);}

		/**
		 * \fn	template <typename T> typename T::Enum Attributes::as() const
		 *
		 * \brief	converts the attributes to an Enum.
		 *
		 * \return	The type of the enum is given as a template parameter and this parameter must be one of the following class: 
		 * 			Accessibility, Lifecycle, Permission, Ownership, NodeType, Consistence, Synchronicity.
		 */
		template <typename T> 
		typename T::Enum as() const
		{
			return static_cast<typename T::Enum>(m_value & T::MASK);
		}

		/**
		 * \fn	friend bool Attributes::operator==(SK::Attributes p_lhs, SK::Attributes p_rhs)
		 *
		 * \brief	Compare two attributes.
		 *
		 * \param	p_lhs	The first instance to compare.
		 * \param	p_rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */

		friend bool operator==(SK::Attributes p_lhs, SK::Attributes p_rhs) {return (p_lhs.m_value == p_rhs.m_value);}

		/**
		 * \fn	friend bool Attributes::operator==(SK::Attributes p_attributes, SK::Accessibility::Enum flag)
		 *
		 * \brief	Compare the accessibility of this attribute with an SK::Accessibility::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the accessibility of this attribute equals the flag.
		 */

		friend bool operator==(SK::Attributes p_attributes, SK::Accessibility::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Accessibility::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the accessibility of this attribute with SK::Accessibility::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the accessibility of this attribute equals the flag.
		 */

		friend bool operator==(SK::Accessibility::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Attributes p_attributes, SK::Permission::Enum flag)
		 *
		 * \brief	Compare the permission of this attribute with a SK::Permission::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the permission of this attribute equals the flag.
		 */

		friend bool operator==(SK::Attributes p_attributes, SK::Permission::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Permission::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the permission of this attribute with a SK::Permission::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the permission of this attribute equals the flag.
		 */

		friend bool operator==(SK::Permission::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Attributes p_attributes, SK::Consistence::Enum flag)
		 *
		 * \brief	Compare the consistence of this attribute with a SK::Consistence::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the consistence of this attribute equals the flag.
		 */
		
		friend bool operator==(SK::Attributes p_attributes, SK::Consistence::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Consistence::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the consistence of this attribute with a SK::Consistence::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the consistence of this attribute equals the flag.
		 */
		
		friend bool operator==(SK::Consistence::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Attributes p_attributes, SK::Lifecycle::Enum flag)
		 *
		 * \brief	Compare the life cycle of this attribute with a SK::Lifecycle::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the life cycle of this attribute equals the flag.
		 */
		
		friend bool operator==(SK::Attributes p_attributes, SK::Lifecycle::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Lifecycle::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the life cycle of this attribute with a SK::Lifecycle::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the life cycle of this attribute equals the flag.
		 */

		friend bool operator==(SK::Lifecycle::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Attributes p_attributes, SK::NodeType::Enum flag)
		 *
		 * \brief	Compare the node type of this attribute with a SK::NodeType::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the node type of this attribute equals the flag.
		 */

		friend bool operator==(SK::Attributes p_attributes, SK::NodeType::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::NodeType::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the node type of this attribute with a SK::NodeType::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the node type of this attribute equals the flag.
		 */

		friend bool operator==(SK::NodeType::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Attributes p_attributes, SK::Ownership::Enum flag)
		 *
		 * \brief	Compare the ownership of this attribute with a SK::Ownership::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the ownership of this attribute equals the flag.
		 */

		friend bool operator==(SK::Attributes p_attributes, SK::Ownership::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Ownership::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the ownership of this attribute with a SK::Ownership::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the ownership of this attribute equals the flag.
		 */

		friend bool operator==(SK::Ownership::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Attributes p_attributes, SK::Synchronicity::Enum flag)
		 *
		 * \brief	Compare the synchronicity of this attribute with a SK::Synchronicity::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the synchronicity of this attribute equals the flag.
		 */

		friend bool operator==(SK::Attributes p_attributes, SK::Synchronicity::Enum flag) {return ((p_attributes.m_value&flag) > 0);}

		/**
		 * \fn	friend bool operator==(SK::Synchronicity::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the synchronicity of this attribute with a SK::Synchronicity::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the synchronicity of this attribute equals the flag.
		 */

		friend bool operator==(SK::Synchronicity::Enum flag, SK::Attributes p_attributes) {return ((p_attributes.m_value&flag) > 0);}


		/**
		 * \fn	friend bool operator!=(SK::Attributes p_lhs, SK::Attributes p_rhs)
		 *
		 * \brief	Compare two attributes.
		 *
		 * \param	p_lhs	The first instance to compare.
		 * \param	p_rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */
		 
		friend bool operator!=(SK::Attributes p_lhs, SK::Attributes p_rhs) {return !(p_lhs == p_rhs);}


		
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::Accessibility::Enum flag)
		 *
		 * \brief	Compare the accessibility of this attribute with a SK::Accessibility::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the accessibility of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::Accessibility::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Accessibility::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the accessibility of this attribute with a SK::Accessibility::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the accessibility of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Accessibility::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::Permission::Enum flag)
		 *
		 * \brief	Compare the permission of this attribute with a SK::Permission::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the permission of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::Permission::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Permission::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the permission of this attribute with a SK::Permission::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the permission of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Permission::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::Consistence::Enum flag
		 *
		 * \brief	Compare the consistence of this attribute with a SK::Consistence::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the consistence of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::Consistence::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Consistence::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the consistence of this attribute with a SK::Consistence::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the consistence of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Consistence::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::Lifecycle::Enum flag)
		 *
		 * \brief	Compare the life cycle of this attribute with a SK::Lifecycle::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the life cycle of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::Lifecycle::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Lifecycle::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the life cycle of this attribute with a SK::Lifecycle::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the life cycle of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Lifecycle::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::NodeType::Enum flag)
		 *
		 * \brief	Compare the node type of this attribute with a SK::NodeType::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the node type of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::NodeType::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::NodeType::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the node type of this attribute with a SK::NodeType::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the node type of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::NodeType::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::Ownership::Enum flag)
		 *
		 * \brief	Compare the ownership of this attribute with a SK::Ownership::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the ownership of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::Ownership::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Ownership::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the ownership of this attribute with a SK::Ownership::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the ownership of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Ownership::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}
	
		/**
		 * \fn	friend bool operator!=(SK::Attributes p_attributes, SK::Synchronicity::Enum flag)
		 *
		 * \brief	Compare the synchronicity of this attribute with a SK::Synchronicity::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the synchronicity of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Attributes p_attributes, SK::Synchronicity::Enum flag) {return !(p_attributes == flag);}
		
		/**
		 * \fn	friend bool operator!=(SK::Synchronicity::Enum flag, SK::Attributes p_attributes)
		 *
		 * \brief	Compare the synchronicity of this attribute with a SK::Synchronicity::Enum.
		 *
		 * \param	p_attributes	The first instance to compare.
		 * \param	flag			The second instance to compare.
		 *
		 * \return	true if the synchronicity of this attribute do not equals the flag.
		 */
		
		friend bool operator!=(SK::Synchronicity::Enum flag, SK::Attributes p_attributes) {return !(p_attributes == flag);}




		/**
		 * \fn	template <typename T> bool Attributes::has()
		 *
		 * \brief	Tells if this attribute has a given property.
		 *
		 * \return	true if it succeeds, false if it fails.
		 * 			
		 * 			The property is one of the following class: Accessibility, Lifecycle, Permission, Ownership, NodeType, Consistence, Synchronicity.
		 */
		
		template <typename T> 
		bool has() 
		{
			return (SK::Attributes::as<T>() > 0);
		}

		/**
		 * \fn	template <typename T> bool Attributes::has()
		 *
		 * \brief	clears the given property from this attribute.
		 *
		 * 			The property is one of the following class: Accessibility, Lifecycle, Permission, Ownership, NodeType, Consistence, Synchronicity.
		 */
		
		template <typename T> 
		void clear() 
		{
			m_value = static_cast<Enum>(m_value & (~T::MASK));
		}

		/**
		 * \fn	template <typename T> SK::Attributes& Attributes::setFlag(typename T::Enum flag)
		 *
		 * \brief	Sets a flag of a given property.
		 *
		 * \param	flag	The flag.
		 *
		 * \return	this attribute.
		 *
		 * 			The property is one of the following class: Accessibility, Lifecycle, Permission, Ownership, NodeType, Consistence, Synchronicity.
		 */

		template <typename T> 
		SK::Attributes& setFlag(typename T::Enum flag) 
		{
			clear<T>();
			m_value = static_cast<Enum>(m_value | flag);

			return *this;
		}

		/**
		 * \fn	template <typename T> bool validate()
		 *
		 * \brief	Tells if the attribute has a valid flag for a given property
		 *
		 * \return	true if valid.
		 *
		 * 			A property is valid if it contains only one flag amongst the possible flag of that property (e.g: an attribute's accessibility is invalid if it is PUBLIC 
		 * 			and PRIVATE at the same time)
		 * 			The property is one of the following class: Accessibility, Lifecycle, Permission, Ownership, NodeType, Consistence, Synchronicity.
		 */
		template <typename T> 
		bool validate()
		{
			return (std::bitset<32>(as<T>()).count() <= 1);
		}
		
		/**
		 * \fn	bool validateAll()
		 *
		 * \brief	Tells if the attribute has a valid flag for all properties.
		 *
		 * \return	true if valid.
		 *
		 */

		bool validateAll()
		{
			return (validate<SK::Accessibility>()	&& 
					validate<SK::Permission>()		&& 
					validate<SK::Consistence>()		&& 
					validate<SK::Lifecycle>()		&& 
					validate<SK::NodeType>()		&& 
					validate<SK::Ownership>()		&& 
					validate<SK::Synchronicity>()
				   );
		}


			 
	};

}
