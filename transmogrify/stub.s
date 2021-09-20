    .global assembly_stub
    .text
assembly_stub:
    push %rbp
    mov %rsp, %rbp              
    callq *transmogrify_hook(%rip)
    jmp *transmogrify_return(%rip)

