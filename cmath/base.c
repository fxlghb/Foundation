
#include <stdio.h>



/*****************************************************************************
 Function     : baseCheck2Deep
 Description  : ����޷��������Ƿ�Ϊ2��ڤ
 Input        : const unsigned int param  
 Output       : None
 Return Value : �����2��ڤ���򷵻�0��������򷵻ط�0
*****************************************************************************/
inline char baseCheck2Deep(const unsigned int param)
{
    return param&(param-1);
}


/*****************************************************************************
 Function     : baseCheck2DeepSub1
 Description  : ����޷��������Ƿ�Ϊ2��ڤ-1
 Input        : const unsigned int param  
 Output       : None
 Return Value : �����2��ڤ-1���򷵻�0��������򷵻ط�0
*****************************************************************************/
inline char baseCheck2DeepSub1(const unsigned int param)
{
    return param&(param+1);
}

/*****************************************************************************
 Function     : baseDetectLastRightBit1
 Description  : ���������Ҳ��ֵΪ1��λ
 Input        : const unsigned int param  
 Output       : None
 Return Value : �������Ҳ�ֵΪ1��λ��ֵ�����򷵻�0
*****************************************************************************/
inline int baseDetectLastRightBit1(const int param)
{
    return param&(-param);
}

/*****************************************************************************
 Function     : baseDetectLastRightBit0
 Description  : ���������Ҳ��ֵΪ0��λ
 Input        : const unsigned int param  
 Output       : None
 Return Value : �������Ҳ�ֵΪ0��λ��ֵ�����򷵻�0
*****************************************************************************/
inline int baseDetectLastRightBit0(const int param)
{
    return  ~param&(param+1);
}

/*****************************************************************************
 Function     : baseStructSuffixMaskBit0
 Description  : ����ʶ���׺0������,ָ�����
 Input        : const int param  
 Output       : None
 Return Value : ���param=0����������λ��Ϊ1����
*****************************************************************************/
inline int baseStructSuffixMaskBit0(const int param)
{
    return  ~param&(param-1);//~(param|-param)  //(param&-param)-1
}


inline int baseStructSuffixMaskFirstBit1(const int param)
{
    return  param^(param-1);
}



//�������Ҳ�λ
void baseOperateRightBit(void)
{
    int param= 0x100ff0;
    
    printf("param = [0x%x][0x%x]\n",param,-param);
    printf("baseDetectLastRightBit0  = 0x%x \n",baseDetectLastRightBit0(param));
    printf("baseStructSuffixMaskBit0 = 0x%x \n",baseStructSuffixMaskBit0(param));
}




int main(int argc, char *argv[])
{
    baseOperateRightBit();
    return 0;
}










