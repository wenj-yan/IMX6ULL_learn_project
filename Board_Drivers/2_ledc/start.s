
.global __start

__start:
    /*设置进入SVC模式 */
    MRS R0,cpsr    /*读取CPSR */
    BIC R0,R0,#0x1f /*清除CPSR的bit4-0 */
    ORR R0,R0,0x13   /*置为SVC模式 */
    MSR cpsr,R0    /*写入CPSR*/

    /*设置SP指针 */
    LDR SP,=0x80200000
    /*跳转到C语言 */
    b main        /*跳转到c语言main函数 */
    