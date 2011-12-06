	.asg _irq_handle_udef, C_INTUDEF
	.asg _irq_handle_swi, C_INTSWI
	.asg _irq_handle_pabt, C_INTPABT
	.asg _irq_handle_dabt, C_INTDABT
	.asg _irq_handle, C_INTIRQ

	.global _c_int00
	.global C_INTUDEF	; Undefined Exception
	.global C_INTSWI	; Software Interrupt
	.global C_INTPABT	; Prefetch abort
	.global C_INTDABT	; Data abort
	.global C_INTIRQ	; Interrupt Request

	; interrupt sections
	.sect ".intvecs"
	B _c_int00    ; Reset Interrupt
	B C_INTUDEF ; Undefined Exception
	B C_INTSWI ; Software interrupt
	B C_INTPABT ; Prefetch abort
	B C_INTDABT ; Data abort
	.word 0
	B C_INTIRQ ; Interrupt Request
	.word 0




