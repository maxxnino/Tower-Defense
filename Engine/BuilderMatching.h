#pragma once
#include <functional>
#include <unordered_map>
#include <typeinfo>
#include <type_traits>
#include <assert.h>

template <class Object>
class BuilderMatching
{
public:
	template<class T, class U, class F>
	void Case(F f)
	{
		static_assert(std::is_base_of<Object, T>::value, "Template param type T must be derived from Box::ColorTrait!");
		static_assert(std::is_base_of<Object, U>::value, "Template param type U must be derived from Box::ColorTrait!");
		Handlers[{&typeid(T), &typeid(U)}] = f;
		Handlers[{&typeid(U), &typeid(T)}] = std::bind(
			f, std::placeholders::_2, std::placeholders::_1
		);
	}
	template<class T, class U>
	bool HasCase() const
	{
		static_assert(std::is_base_of<Object, T>::value, "Template param type T must be derived from Box::ColorTrait!");
		static_assert(std::is_base_of<Object, U>::value, "Template param type U must be derived from Box::ColorTrait!");
		return Handlers.count({ &typeid(T),&typeid(U) }) > 0;
	}
	template<class T, class U>
	void ClearCase()
	{
		static_assert(std::is_base_of<Object, T>::value, "Template param type T must be derived from Box::ColorTrait!");
		static_assert(std::is_base_of<Object, U>::value, "Template param type U must be derived from Box::ColorTrait!");
		Handlers.erase({ &typeid(T),&typeid(U) });
		Handlers.erase({ &typeid(U),&typeid(T) });
	}
	/*template<class F>
	void Default(F f)
	{
		def = f;
	}*/
	Object* Create(Object* Obj01, Object* Obj02)
	{
		return Switch(*Obj01, *Obj02);
	}
private:
	Object* Switch(Object& a, Object& b)
	{
		auto i = Handlers.find({
			&typeid(a),
			&typeid(b)
			});
		if (i != Handlers.end())
		{
			return std::move(i->second(a, b));
		}
		else
		{
			assert(false);
			return &a;
		}
	}
private:
	std::unordered_map<TypePair, std::function<Object*(Object&, Object&)>> Handlers;
	//std::function<std::unique_ptr<Object>(Object&, Object&)> def = [](Object&, Object&) {};
};