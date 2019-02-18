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
/// \brief ����ָ����ģ��
///
/// ֧����ͨ����ָ��ͳ�Ա����ָ��ı��棬�Ƚϣ����õȲ��������ڳ�Ա������
/// Ҫ����ֻ������ͨ������ǵ��̳е��࣬�����Ƕ�̳л���̳е��ࡣFUNCTION_FUNCTION��һ���꣬
/// ���ݲ��������ᱻ�滻��TFunctionN���û�ͨ��TFunctionN<R, T1, T2, T3,..,TN>��ʽ��ʹ�ã�
/// R��ʾ����ֵ���ͣ�TN��ʾ�������ͣ� N��ʾ��������������Ŀǰ������Ϊ6��ʾ�����£�
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
    typedef R (X::*MEM_FUNCTION)(FUNCTION_TYPES); //����ָ������
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
    /// ȱʡ���캯��
    FUNCTION_FUNCTION( )
    :m_type(typeEmpty)
    {
    }

    /// ���ܳ�Ա����ָ�빹�캯��������ĳ�Ա������������ָ��󶨲����档
    /// \param [in] f ��ĳ�Ա����
    /// \param [in] o ������ָ��
    template<typename O>
    FUNCTION_FUNCTION(R(O::*f)(FUNCTION_TYPES), const O * o)
    {
        m_type = typeMember;
        m_function.memFunction.proc = horrible_cast<MEM_FUNCTION>(f); //what's safty, hei hei
        m_function.memFunction.obj = horrible_cast<X*>(o);
    }

    /// ������ͨ����ָ�빹�캯����������ͨ����ָ�롣
    /// \param [in] f ����ָ��
    FUNCTION_FUNCTION(PTR_FUNCTION f)
    {
        m_type = typePointer;
        m_function.ptrFunction = f;
    }

    /// �չ��캯����������ָ������Ϊ0
    /// \param [in] zero ֻ��Ϊ0������Ϊ����ֵ
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

    /// �������캯��
    /// \param [in] f Դ����ָ�����
    FUNCTION_FUNCTION& operator=(const FUNCTION_FUNCTION& f)
    {
        if (&f == this)
        return *this;
        m_function = f.m_function;
        m_type = f.m_type;
        return *this;
    }

    /// ����ĳ�Ա������������ָ��󶨲����档�������͵ĺ���ָ�����=���������ʽת��ֱ����ɡ�
    template<typename O>
    void bind(R(O::*f)(FUNCTION_TYPES), const O * o)
    {
        *this = FUNCTION_FUNCTION(f, o);
    }

    /// �жϺ���ָ���Ƿ�Ϊ��
    bool empty()
    {
        return (m_type == typeEmpty);
    }

    /// �Ƚ���������ָ���Ƿ����
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

    /// ����()������������Ժ����������ʽ�����ñ���ĺ���ָ�롣
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

