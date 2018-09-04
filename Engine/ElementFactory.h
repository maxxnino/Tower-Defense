#pragma once
#include "Element.h"
#include "BuilderMatching.h"
class ElementFactory
{
public:
	ElementFactory()
	{
		builder.Case<Fire,Ice>([](Element& f, Element& i)
		{
			return std::make_unique<FireIce>();
		});
		builder.Case<Fire, Fire>([](Element& f, Element& i)
		{
			return std::make_unique<FireFire>();
		});
		builder.Case<Ice, Ice>([](Element& f, Element& i)
		{
			return std::make_unique<IceIce>();
		});
		builder.Case<Ice, Lighting>([](Element& f, Element& i)
		{
			return std::make_unique<IceLight>();
		});
		builder.Case<Lighting, Lighting>([](Element& f, Element& i)
		{
			return std::make_unique<LightLight>();
		});
		builder.Case<Fire, Lighting>([](Element& f, Element& i)
		{
			return std::make_unique<FireLight>();
		});
		/*builder.Default([](Element& f, Element& i)
		{
			return std::move(f.Clone());
		});*/
	}
	std::unique_ptr<Element> MakeElement(Element* a, Element* b)
	{
		return std::move(builder.Create(a, b));
	}
private:
	BuilderMatching<Element> builder;
};