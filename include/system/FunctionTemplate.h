//
//  "$Id: FunctionTemplate.h 518 2009-10-24 10:35:00Z eric.yu $"
//
//  Copyright (c)1992-2007, Shanghai VisionDigi Technology CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#define FUNCTION_FUNCTION MACRO_JOIN(TFunction,FUNCTION_NUMBER)

/// \class FUNCTION_FUNCTION
/// \brief 函数指针类模块
///
/// 支持普通函数指针和成员函数指针的保存，比较，调用等操作。对于成员函数，
/// 要求类只能是普通类或者是单继承的类，不能是多继承或虚继承的类。FUNCTION_FUNCTION是一个宏，
/// 根据参数个数会被替换成TFunctionN，用户通过TFunctionN<R, T1, T2, T3,..,TN>方式来使用，
/// R表示返回值类型，TN表示参数类型， N表示函数参数个数，目前最大参数为6。示例如下：
/// \code
/// int g(int x)
/// {
/// 	return x * 2;
/// }
/// class G
/// {
/// public:
/// 	int g(int x)
/// 	{
/// 		return x * 3;
/// 	}
/// }gg;
/// void test()
/// {
/// 	TFunction1<int, int> f1(g);
/// 	TFunction1<int, int> f2(&G::g, &gg);
/// 	assert(f1(1) = 2);
/// 	assert(f2(1) = 3);
/// 	f1 = f2;
/// 	assert(f1 == f2);
/// }
/// \endcode

template <FUNCTION_CLASS_TYPES>
class FUNCTION_FUNCTION
{
    class X
    {};

    enum FunctionType
    {
        typeEmpty,
        typeMember,
        typePointer,
        typeObject,
    };
    typedef R (X::*MEM_FUNCTION)(FUNCTION_TYPES); //函数指针类型
    typedef R (*PTR_FUNCTION)(FUNCTION_TYPES);

    union
    {
        struct
        {
            MEM_FUNCTION proc;
            X* obj;
        }memFunction;
        PTR_FUNCTION ptrFunction;
    }m_function;

    FunctionType m_type;

public:
    /// 缺省构造函数
    FUNCTION_FUNCTION( )
    :m_type(typeEmpty)
    {
    }

    /// 接受成员函数指针构造函数，将类的成员函数和类对象的指针绑定并保存。
    /// \param [in] f 类的成员函数
    /// \param [in] o 类对象的指针
    template<typename O>
    FUNCTION_FUNCTION(R(O::*f)(FUNCTION_TYPES), const O * o)
    {
        m_type = typeMember;
        m_function.memFunction.proc = horrible_cast<MEM_FUNCTION>(f); //what's safty, hei hei
        m_function.memFunction.obj = horrible_cast<X*>(o);
    }

    /// 接受普通函数指针构造函数，保存普通函数指针。
    /// \param [in] f 函数指针
    FUNCTION_FUNCTION(PTR_FUNCTION f)
    {
        m_type = typePointer;
        m_function.ptrFunction = f;
    }

    /// 空构造函数，将函数指针设置为0
    /// \param [in] zero 只能为0，不能为其他值
    FUNCTION_FUNCTION(int zero)
    {
        m_type = typeEmpty;
        assert(zero == 0);
    }

    FUNCTION_FUNCTION(const FUNCTION_FUNCTION& f)
    {
        m_function = f.m_function;
        m_type = f.m_type;
    }

    /// 拷贝构造函数
    /// \param [in] f 源函数指针对象
    FUNCTION_FUNCTION& operator=(const FUNCTION_FUNCTION& f)
    {
        if (&f == this)
        return *this;
        m_function = f.m_function;
        m_type = f.m_type;
        return *this;
    }

    /// 将类的成员函数和类对象的指针绑定并保存。其他类型的函数指针可以=运算符和隐式转换直接完成。
    template<typename O>
    void bind(R(O::*f)(FUNCTION_TYPES), const O * o)
    {
        *this = FUNCTION_FUNCTION(f, o);
    }

    /// 判断函数指针是否为空
    bool empty()
    {
        return (m_type == typeEmpty);
    }

    /// 比较两个函数指针是否相等
    bool operator==(const FUNCTION_FUNCTION& f)
    {
        if(m_type != f.m_type)
        {
            return false;
        }
        if(m_type == typeMember)
        {
            return (m_function.memFunction.proc == f.m_function.memFunction.proc
                    && m_function.memFunction.obj == f.m_function.memFunction.obj);
        }
        else if(m_type == typePointer)
        {
            return (m_function.ptrFunction == f.m_function.ptrFunction);
        }
        else
        {
            return true;
        }
    }

    /// 重载()运算符，可以以函数对象的形式来调用保存的函数指针。
    inline R operator()(FUNCTION_TYPE_ARGS)
    {
        if(m_type == typeMember)
        {
            return (m_function.memFunction.obj->*m_function.memFunction.proc)(FUNCTION_ARGS);
        }
        else
        {
            return m_function.ptrFunction(FUNCTION_ARGS);
        }
    }
};

#undef FUNCTION_FUNCTION

