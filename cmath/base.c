
#include <stdio.h>



/*****************************************************************************
 Function     : baseCheck2Deep
 Description  : 检测无符号整数是否为2的冥
 Input        : const unsigned int param  
 Output       : None
 Return Value : 如果是2的冥，则返回0，否则否则返回非0
*****************************************************************************/
inline char baseCheck2Deep(const unsigned int param)
{
    return param&(param-1);
}


/*****************************************************************************
 Function     : baseCheck2DeepSub1
 Description  : 检测无符号整数是否为2的冥-1
 Input        : const unsigned int param  
 Output       : None
 Return Value : 如果是2的冥-1，则返回0，否则否则返回非0
*****************************************************************************/
inline char baseCheck2DeepSub1(const unsigned int param)
{
    return param&(param+1);
}

/*****************************************************************************
 Function     : baseDetectLastRightBit1
 Description  : 分析出最右侧的值为1的位
 Input        : const unsigned int param  
 Output       : None
 Return Value : 返回最右侧值为1的位的值，否则返回0
*****************************************************************************/
inline int baseDetectLastRightBit1(const int param)
{
    return param&(-param);
}

/*****************************************************************************
 Function     : baseDetectLastRightBit0
 Description  : 分析出最右侧的值为0的位
 Input        : const unsigned int param  
 Output       : None
 Return Value : 返回最右侧值为0的位的值，否则返回0
*****************************************************************************/
inline int baseDetectLastRightBit0(const int param)
{
    return  ~param&(param+1);
}

/*****************************************************************************
 Function     : baseStructSuffixMaskBit0
 Description  : 构造识别后缀0的掩码,指令级并行
 Input        : const int param  
 Output       : None
 Return Value : 如果param=0，生成所有位都为1的字
*****************************************************************************/
inline int baseStructSuffixMaskBit0(const int param)
{
    return  ~param&(param-1);//~(param|-param)  //(param&-param)-1
}


inline int baseStructSuffixMaskFirstBit1(const int param)
{
    return  param^(param-1);
}



//操作最右侧位
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










