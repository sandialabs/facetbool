//-------------------------------------------------------------------------
// Filename      : OrderedSet.hpp
//
// Purpose       : A DLIList that does not allow duplicates and is faster
//                 at inserting uniquely than DLIList.
//
// Creator       : Matt Staten
//
// Creation Date : 09/22/2005
//
// Owner         : Matt Staten
//-------------------------------------------------------------------------

#ifndef OrderedSet_HPP
#define OrderedSet_HPP

#include <set>
#include "DLIList.hpp"

template<class X> class OrderedSet
{
private:
    DLIList<X> mList;
    std::set<X> mSet;

public:

    OrderedSet( void ) {};
    OrderedSet( const DLIList<X> list )
    {
        int i;
        for ( i = 0; i < list.size(); i++ )
        {
            append( list[i] );
        }
    };

    CubitBoolean is_in_list( X item ) const
    {
        if ( mSet.find( item ) == mSet.end() )
        {
            return CUBIT_FALSE;
        }
        return CUBIT_TRUE;
    };

    int where_is_item( X item )
    {
        CubitBoolean stat = is_in_list( item );
        if ( stat == CUBIT_TRUE )
        {
            return mList.where_is_item( item );
        }
        return -1;
    };

    CubitBoolean insert( X new_item )
    {
        if ( !is_in_list( new_item ) )
        {
            force_insert( new_item );
            return CUBIT_TRUE;
        }
        return CUBIT_FALSE;
    }

    // Append to the end of this list.
    CubitBoolean append( X new_item )
    {
        return insert( new_item );
    }

    // insert at the beginning of the list.
    CubitBoolean prepend( X new_item )
    {
        if ( !is_in_list( new_item ) )
        {
            mList.insert_first( new_item );
            mSet.insert( new_item );
            return CUBIT_TRUE;
        }
        return CUBIT_FALSE;
    }

    void force_insert( X new_item )
    {
        mList.append( new_item );
        mSet.insert( new_item );
    };

    void reverse( void )
    {
        mList.reverse();
    };

    void reset( void )
    {
        mList.reset();
    };

    void reserve( int min_size )
    {
      mList.reserve(min_size);
    };
  
    X get_and_step( int n = 1 ) 
    {
        X temp = get();
        step( n );
        return temp;
    };

    void step( int n = 1 )
    {
        mList.step( n );
    };

    X get() const
    {
        return mList.get();
    };

    X & operator[](int index) const;
    OrderedSet<X>& operator=(const DLIList<X>& from);
    OrderedSet<X>& operator+=(const DLIList<X>& from);
    OrderedSet<X>& operator+=(const OrderedSet<X>& from);
    OrderedSet<X>& operator+=( X from );
    OrderedSet<X>& operator-=(const DLIList<X>& from);
    OrderedSet<X>& operator-=(const OrderedSet<X> &from);
    OrderedSet<X>& operator-=(const OrderedSet<X> *from);
    OrderedSet<X>& operator-=( X from );

    CubitBoolean empty( void ) const { return ( mList.size() == 0 ? CUBIT_TRUE : CUBIT_FALSE ); };
    int size( void ) const { return mList.size(); };
    X pop( void )
    {
        X item = mList.pop();
        mSet.erase( item );
        return item;
    };
    void remove( X item )
    {
        if ( !is_in_list( item ) )
            return;
        mList.remove_all_with_value( item );
        mSet.erase( item );
    };

    void clean_out( void )
    {
        mList.clean_out();
        mSet.clear();
    };

    void list( DLIList<X> &list ) const
    {
        list = mList;
    }
    const DLIList<X> * list( void ) const
    {
        return &mList;
    }
};

template <class X> inline
X & OrderedSet<X>::operator[](int index) const
{
    return mList[index];
}

template <class X> inline 
OrderedSet<X>& OrderedSet<X>::operator=(const DLIList<X>& list)
{ 
    mList.clean_out();
    mSet.clear();
    int i;
    for ( i = 0; i < list.size(); i++ )
    {
        this->insert( list[i] );
    }
    return *this; 
}

template <class X> inline
OrderedSet<X>& OrderedSet<X>::operator+=( X from )
{
    this->insert( from );
    return *this;
}

template <class X> inline
OrderedSet<X>& OrderedSet<X>::operator-=( X from )
{
    this->remove( from );
    return *this;
}

template <class X> inline 
OrderedSet<X>& OrderedSet<X>::operator+=(const DLIList<X>& list)
{ 
    int i;
    for ( i = 0; i < list.size(); i++ )
    {
        this->insert( list[i] );
    }
    return *this; 
}

template <class X> inline 
OrderedSet<X>& OrderedSet<X>::operator+=(const OrderedSet<X>& list)
{ 
    int i;
    for ( i = 0; i < list.size(); i++ )
    {
        this->insert( list[i] );
    }
    return *this; 
}

template <class X> inline 
OrderedSet<X>& OrderedSet<X>::operator-=(const DLIList<X>& list)
{ 
    int i;
    for ( i = 0; i < list.size(); i++ )
    {
        this->remove( list[i] );
    }
    return *this; 
}

template <class X> inline 
OrderedSet<X>& OrderedSet<X>::operator-=(const OrderedSet<X>& list)
{ 
    int i;
    for ( i = 0; i < list.size(); i++ )
    {
        this->remove( list[i] );
    }
    return *this; 
}

template <class X> inline 
OrderedSet<X>& OrderedSet<X>::operator-=(const OrderedSet<X> *list)
{ 
    int i;
    for ( i = 0; i < list->size(); i++ )
    {
        this->remove( (*list)[i] );
    }
    return *this; 
}

#endif // OrderedSet_HPP
