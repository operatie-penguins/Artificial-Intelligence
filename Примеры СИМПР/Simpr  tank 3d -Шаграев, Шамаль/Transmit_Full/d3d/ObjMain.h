#pragma once

#include "Utils.h"
#include <string>
#include <set>
#include <map>
#include <hash_map>
#include <d3dx9math.h>

class GObject
{
private:
	// Базовые х-ки.
	GObject							*Master;
	std::string						ClassName;
	static std::map< std::string,
		std::set<GObject*> >		ObjectBins;
protected:
	
	// Регистрирует класс в списке связей.
	void Register( const std::string& ClassNameStr )
	{
		ClassName = ClassNameStr;
		ObjectBins[ClassNameStr].insert( this );
	}
	void Unregister( const std::string& ClassNameStr )
	{
		ObjectBins[ClassNameStr].erase( this );
		if ( ObjectBins[ClassNameStr].empty() )
			ObjectBins.erase( ClassNameStr );
	}
	GObject( GObject *pMaster = 0 )
		: Master(pMaster)
	{
		Register( "GObject" );
	}
public:
	
	// Здесь производить обновление объектов.
	virtual void BeginFrame( float CurTime ) = 0;
	virtual void EndFrame( float CurTime ) = 0;

	class GObjIterator
	{
		std::set<GObject*>::iterator	It;
		std::set<GObject*>				*Holder;
		GObjIterator( std::set<GObject*> *ObjSet )
			: Holder(ObjSet)
		{
			if( Holder )
				It = Holder->begin();
		}
		friend class GObject;
	public:
		GObject& operator*() const
		{
			return **It;
		}
		GObject* operator->() const
		{
			return *It;
		}
		GObjIterator& operator++()
		{
			++It;
			return *this;
		}
		bool AtTheEnd() const
		{
			return( !Holder || It == Holder->end() );
		}
	};
	// Возвращает подмножество объектов.
	static GObjIterator GetClassBin( const std::string& ClassNameStr )
	{
		if( ObjectBins.find(ClassNameStr) != ObjectBins.end() )
			return GObjIterator( &ObjectBins[ClassNameStr] );
		else
			return GObjIterator( 0 );
	}
	const std::string& GetClassNameStr() const
	{
		return ClassName;
	}
	// Деструктор.
	virtual ~GObject()
	{
		Unregister( "GObject" );
	}
};

// Объект, который можно рисовать.
class GRenderable : public GObject
{
public:
	GRenderable( GObject *Master = 0) : GObject(Master)
	{
		Register( "GRenderable" );
	}
	~GRenderable()
	{
		Unregister( "GRenderable" );
	}
	virtual void Draw() = 0;
};
