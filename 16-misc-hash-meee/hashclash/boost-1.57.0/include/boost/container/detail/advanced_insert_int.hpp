//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP
#define BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/destroyers.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/utilities.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/iterators.hpp>
#include <iterator>  //std::iterator_traits
#include <boost/assert.hpp>
#include <boost/core/no_exceptions_support.hpp>

namespace boost { namespace container { namespace container_detail {

template<class A, class FwdIt, class Iterator>
struct move_insert_range_proxy
{
   typedef typename allocator_traits<A>::size_type size_type;
   typedef typename allocator_traits<A>::value_type value_type;

   explicit move_insert_range_proxy(FwdIt first)
      :  first_(first)
   {}

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::uninitialized_move_alloc_n_source
         (a, this->first_, n, p);
   }

   void copy_n_and_update(A &, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::move_n_source(this->first_, n, p);
   }

   FwdIt first_;
};


template<class A, class FwdIt, class Iterator>
struct insert_range_proxy
{
   typedef typename allocator_traits<A>::size_type size_type;
   typedef typename allocator_traits<A>::value_type value_type;

   explicit insert_range_proxy(FwdIt first)
      :  first_(first)
   {}

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::uninitialized_copy_alloc_n_source(a, this->first_, n, p);
   }

   void copy_n_and_update(A &, Iterator p, size_type n)
   {
      this->first_ = ::boost::container::copy_n_source(this->first_, n, p);
   }

   FwdIt first_;
};


template<class A, class Iterator>
struct insert_n_copies_proxy
{
   typedef typename allocator_traits<A>::size_type size_type;
   typedef typename allocator_traits<A>::value_type value_type;

   explicit insert_n_copies_proxy(const value_type &v)
      :  v_(v)
   {}

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n) const
   {  boost::container::uninitialized_fill_alloc_n(a, v_, n, p);  }

   void copy_n_and_update(A &, Iterator p, size_type n) const
   {
	   for (; 0 < n; --n, ++p){
		   *p = v_;
      }
   }

   const value_type &v_;
};

template<class A, class Iterator>
struct insert_value_initialized_n_proxy
{
   typedef ::boost::container::allocator_traits<A> alloc_traits;
   typedef typename allocator_traits<A>::size_type size_type;
   typedef typename allocator_traits<A>::value_type value_type;

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n) const
   {  boost::container::uninitialized_value_init_alloc_n(a, n, p);  }

   void copy_n_and_update(A &, Iterator, size_type) const
   {  BOOST_ASSERT(false); }
};

template<class A, class Iterator>
struct insert_default_initialized_n_proxy
{
   typedef ::boost::container::allocator_traits<A> alloc_traits;
   typedef typename allocator_traits<A>::size_type size_type;
   typedef typename allocator_traits<A>::value_type value_type;

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n) const
   {  boost::container::uninitialized_default_init_alloc_n(a, n, p);  }

   void copy_n_and_update(A &, Iterator, size_type) const
   {  BOOST_ASSERT(false); }
};

template<class A, class Iterator>
struct insert_copy_proxy
{
   typedef boost::container::allocator_traits<A> alloc_traits;
   typedef typename alloc_traits::size_type size_type;
   typedef typename alloc_traits::value_type value_type;

   explicit insert_copy_proxy(const value_type &v)
      :  v_(v)
   {}

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( a, iterator_to_raw_pointer(p), v_);
   }

   void copy_n_and_update(A &, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p =v_;
   }

   const value_type &v_;
};


template<class A, class Iterator>
struct insert_move_proxy
{
   typedef boost::container::allocator_traits<A> alloc_traits;
   typedef typename alloc_traits::size_type size_type;
   typedef typename alloc_traits::value_type value_type;

   explicit insert_move_proxy(value_type &v)
      :  v_(v)
   {}

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( a, iterator_to_raw_pointer(p), ::boost::move(v_) );
   }

   void copy_n_and_update(A &, Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p = ::boost::move(v_);
   }

   value_type &v_;
};

template<class It, class A>
insert_move_proxy<A, It> get_insert_value_proxy(BOOST_RV_REF(typename std::iterator_traits<It>::value_type) v)
{
   return insert_move_proxy<A, It>(v);
}

template<class It, class A>
insert_copy_proxy<A, It> get_insert_value_proxy(const typename std::iterator_traits<It>::value_type &v)
{
   return insert_copy_proxy<A, It>(v);
}

}}}   //namespace boost { namespace container { namespace container_detail {

#ifdef BOOST_CONTAINER_PERFECT_FORWARDING

#include <boost/container/detail/variadic_templates_tools.hpp>
#include <boost/move/utility_core.hpp>
#include <typeinfo>
//#include <iostream> //For debugging purposes

namespace boost {
namespace container {
namespace container_detail {

template<class A, class Iterator, class ...Args>
struct insert_non_movable_emplace_proxy
{
   typedef boost::container::allocator_traits<A>   alloc_traits;
   typedef typename alloc_traits::size_type        size_type;
   typedef typename alloc_traits::value_type       value_type;

   typedef typename build_number_seq<sizeof...(Args)>::type index_tuple_t;

   explicit insert_non_movable_emplace_proxy(Args&&... args)
      : args_(args...)
   {}

   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n)
   {  this->priv_uninitialized_copy_some_and_update(a, index_tuple_t(), p, n);  }

   private:
   template<int ...IdxPack>
   void priv_uninitialized_copy_some_and_update(A &a, const index_tuple<IdxPack...>&, Iterator p, size_type n)
   {
      BOOST_ASSERT(n == 1); (void)n;
      alloc_traits::construct( a, iterator_to_raw_pointer(p), ::boost::forward<Args>(get<IdxPack>(this->args_))... );
   }

   protected:
   tuple<Args&...> args_;
};

template<class A, class Iterator, class ...Args>
struct insert_emplace_proxy
   :  public insert_non_movable_emplace_proxy<A, Iterator, Args...>
{
   typedef insert_non_movable_emplace_proxy<A, Iterator, Args...> base_t;
   typedef boost::container::allocator_traits<A>   alloc_traits;
   typedef typename base_t::value_type             value_type;
   typedef typename base_t::size_type              size_type;
   typedef typename base_t::index_tuple_t          index_tuple_t;

   explicit insert_emplace_proxy(Args&&... args)
      : base_t(::boost::forward<Args>(args)...)
   {}

   void copy_n_and_update(A &a, Iterator p, size_type n)
   {  this->priv_copy_some_and_update(a, index_tuple_t(), p, n);  }

   private:

   template<int ...IdxPack>
   void priv_copy_some_and_update(A &a, const index_tuple<IdxPack...>&, Iterator p, size_type n)
   {
      BOOST_ASSERT(n ==1); (void)n;
      aligned_storage<sizeof(value_type), alignment_of<value_type>::value> v;
      value_type *vp = static_cast<value_type *>(static_cast<void *>(&v));
      alloc_traits::construct(a, vp,
         ::boost::forward<Args>(get<IdxPack>(this->args_))...);
      BOOST_TRY{
         *p = ::boost::move(*vp);
      }
      BOOST_CATCH(...){
         alloc_traits::destroy(a, vp);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      alloc_traits::destroy(a, vp);
   }
};

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class A, class Iterator>
struct insert_emplace_proxy<A, Iterator, typename boost::container::allocator_traits<A>::value_type>
   : public insert_move_proxy<A, Iterator>
{
   explicit insert_emplace_proxy(typename boost::container::allocator_traits<A>::value_type &&v)
   : insert_move_proxy<A, Iterator>(v)
   {}
};

//We use "add_const" here as adding "const" only confuses MSVC12(and maybe later) provoking
//compiler error C2752 (?more than one partial specialization matches?).
//Any problem is solvable with an extra layer of indirection? ;-)
template<class A, class Iterator>
struct insert_emplace_proxy<A, Iterator
   , typename boost::container::container_detail::add_const<typename boost::container::allocator_traits<A>::value_type>::type
   >
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

template<class A, class Iterator>
struct insert_emplace_proxy<A, Iterator, typename boost::container::allocator_traits<A>::value_type &>
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

template<class A, class Iterator>
struct insert_emplace_proxy<A, Iterator
   , typename boost::container::container_detail::add_const<typename boost::container::allocator_traits<A>::value_type>::type &
   >
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

}}}   //namespace boost { namespace container { namespace container_detail {

#else //#ifdef BOOST_CONTAINER_PERFECT_FORWARDING

#include <boost/container/detail/preprocessor.hpp>
#include <boost/container/detail/value_init.hpp>

namespace boost {
namespace container {
namespace container_detail {

#define BOOST_PP_LOCAL_MACRO(N)                                                     \
template<class A, class Iterator BOOST_PP_ENUM_TRAILING_PARAMS(N, class P) >        \
struct BOOST_PP_CAT(insert_non_movable_emplace_proxy_arg, N)                        \
{                                                                                   \
   typedef boost::container::allocator_traits<A> alloc_traits;                      \
   typedef typename alloc_traits::size_type size_type;                              \
   typedef typename alloc_traits::value_type value_type;                            \
                                                                                    \
   explicit BOOST_PP_CAT(insert_non_movable_emplace_proxy_arg, N)                   \
      ( BOOST_PP_ENUM(N, BOOST_CONTAINER_PP_PARAM_LIST, _) )                        \
      BOOST_PP_EXPR_IF(N, :) BOOST_PP_ENUM(N, BOOST_CONTAINER_PP_PARAM_INIT, _)     \
   {}                                                                               \
                                                                                    \
   void uninitialized_copy_n_and_update(A &a, Iterator p, size_type n)              \
   {                                                                                \
      BOOST_ASSERT(n == 1); (void)n;                                                \
      alloc_traits::construct                                                       \
         ( a, iterator_to_raw_pointer(p)                                            \
         BOOST_PP_ENUM_TRAILING(N, BOOST_CONTAINER_PP_MEMBER_FORWARD, _)            \
         );                                                                         \
   }                                                                                \
                                                                                    \
   void copy_n_and_update(A &, Iterator, size_type)                                 \
   {  BOOST_ASSERT(false);   }                                                      \
                                                                                    \
   protected:                                                                       \
   BOOST_PP_REPEAT(N, BOOST_CONTAINER_PP_PARAM_DEFINE, _)                           \
};                                                                                  \
                                                                                    \
template<class A, class Iterator BOOST_PP_ENUM_TRAILING_PARAMS(N, class P) >        \
struct BOOST_PP_CAT(insert_emplace_proxy_arg, N)                                    \
   : BOOST_PP_CAT(insert_non_movable_emplace_proxy_arg, N)                          \
         < A, Iterator BOOST_PP_ENUM_TRAILING_PARAMS(N, P) >                        \
{                                                                                   \
   typedef BOOST_PP_CAT(insert_non_movable_emplace_proxy_arg, N)                    \
         <A, Iterator BOOST_PP_ENUM_TRAILING_PARAMS(N, P) > base_t;                 \
   typedef typename base_t::value_type       value_type;                            \
   typedef typename base_t::size_type  size_type;                                   \
   typedef boost::container::allocator_traits<A> alloc_traits;                      \
                                                                                    \
   explicit BOOST_PP_CAT(insert_emplace_proxy_arg, N)                               \
      ( BOOST_PP_ENUM(N, BOOST_CONTAINER_PP_PARAM_LIST, _) )                        \
      : base_t(BOOST_PP_ENUM(N, BOOST_CONTAINER_PP_PARAM_FORWARD, _) )              \
   {}                                                                               \
                                                                                    \
   void copy_n_and_update(A &a, Iterator p, size_type n)                            \
   {                                                                                \
      BOOST_ASSERT(n == 1); (void)n;                                                \
      aligned_storage<sizeof(value_type), alignment_of<value_type>::value> v;       \
      value_type *vp = static_cast<value_type *>(static_cast<void *>(&v));          \
      alloc_traits::construct(a, vp                                                 \
         BOOST_PP_ENUM_TRAILING(N, BOOST_CONTAINER_PP_MEMBER_FORWARD, _));          \
      BOOST_TRY{                                                                    \
         *p = ::boost::move(*vp);                                                   \
      }                                                                             \
      BOOST_CATCH(...){                                                             \
         alloc_traits::destroy(a, vp);                                              \
         BOOST_RETHROW                                                              \
      }                                                                             \
      BOOST_CATCH_END                                                               \
      alloc_traits::destroy(a, vp);                                                 \
   }                                                                                \
};                                                                                  \
//!
#define BOOST_PP_LOCAL_LIMITS (0, BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
#include BOOST_PP_LOCAL_ITERATE()

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class A, class Iterator>
struct insert_emplace_proxy_arg1<A, Iterator, ::boost::rv<typename boost::container::allocator_traits<A>::value_type> >
   : public insert_move_proxy<A, Iterator>
{
   explicit insert_emplace_proxy_arg1(typename boost::container::allocator_traits<A>::value_type &v)
   : insert_move_proxy<A, Iterator>(v)
   {}
};

template<class A, class Iterator>
struct insert_emplace_proxy_arg1<A, Iterator, typename boost::container::allocator_traits<A>::value_type>
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

#else //e.g. MSVC10 & MSVC11

//Specializations to avoid an unneeded temporary when emplacing from a single argument o type value_type
template<class A, class Iterator>
struct insert_emplace_proxy_arg1<A, Iterator, typename boost::container::allocator_traits<A>::value_type>
   : public insert_move_proxy<A, Iterator>
{
   explicit insert_emplace_proxy_arg1(typename boost::container::allocator_traits<A>::value_type &&v)
   : insert_move_proxy<A, Iterator>(v)
   {}
};

//We use "add_const" here as adding "const" only confuses MSVC10&11 provoking
//compiler error C2752 (?more than one partial specialization matches?).
//Any problem is solvable with an extra layer of indirection? ;-)
template<class A, class Iterator>
struct insert_emplace_proxy_arg1<A, Iterator
   , typename boost::container::container_detail::add_const<typename boost::container::allocator_traits<A>::value_type>::type
   >
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

template<class A, class Iterator>
struct insert_emplace_proxy_arg1<A, Iterator, typename boost::container::allocator_traits<A>::value_type &>
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

template<class A, class Iterator>
struct insert_emplace_proxy_arg1<A, Iterator
   , typename boost::container::container_detail::add_const<typename boost::container::allocator_traits<A>::value_type>::type &
   >
   : public insert_copy_proxy<A, Iterator>
{
   explicit insert_emplace_proxy_arg1(const typename boost::container::allocator_traits<A>::value_type &v)
   : insert_copy_proxy<A, Iterator>(v)
   {}
};

#endif

}}}   //namespace boost { namespace container { namespace container_detail {

#endif   //#ifdef BOOST_CONTAINER_PERFECT_FORWARDING

#include <boost/container/detail/config_end.hpp>

#endif //#ifndef BOOST_CONTAINER_ADVANCED_INSERT_INT_HPP
