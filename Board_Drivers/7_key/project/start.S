.global _start
.global _bss_start

_bss_start:
    .word __bss_start   /*变量 */

.global _bss_end

_bss_end:
    .word __bss_end

_start:
    /*设置进入SVC模式 */
    MRS r0,cpsr    /*读取CPSR */
    BIC r0,r0,#0x1f /*清除CPSR的bit4-0 */
    ORR r0,r0,#0x13   /*置为SVC模式 */
    MSR cpsr,r0    /*写入CPSR*/

    /*清除bss段 */
    ldr r0,=__bss_start   /*保存bss的起始地址 */
    ldr r1,=__bss_end
    mov r2,#0
bss_loop:
    stmia r0!,{r2}    /*自增进行覆写 */
    cmp r0,r1     /*比较值 */
    ble bss_loop   /*如果r0小于等于r1，则跳转 */

    /*设置SP指针 */
    LDR SP,=0x80200000
    /*跳转到C语言 */
    b main        /*跳转到c语言main函数 */
    