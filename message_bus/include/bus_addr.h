#pragma once

#include <cstddef>
#include <functional>
#include <typeindex>
#include <random>

namespace bus {

class MsgAddress {
private:
	

public:
	enum class Type { Class, Instance, Group };

	MsgAddress()
	: m_type{Type::Instance}  {
		auto seeder = []() {
			std::random_device rd;
			return rd();
		};

		static std::mt19937 gen{ seeder() };
		
		m_addr = gen();
	}

	template<typename T>
	static MsgAddress create(const T& obj) {
		std::hash<T> hashFunc;
		return MsgAddress{ Type::Group, hashFunc(obj) };
	}

	template<typename T>
	static MsgAddress create() {
		const auto& typeInfo = typeid(T);
		return  MsgAddress{ Type::Class, std::type_index(typeInfo).hash_code() };
	}

	operator std::size_t() const {
		return m_addr;
	}

private:
	MsgAddress(const Type _type, const std::size_t _addr)
	: m_type{_type}
	, m_addr{_addr} {}

private:
	Type        m_type;
	std::size_t m_addr;
};

}  // namespace bus
