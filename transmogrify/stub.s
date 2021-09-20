    .global assembly_stub_1, assembly_stub_2, assembly_stub_3, assembly_stub_4
    .text
assembly_stub_1:
    push %rbp
    mov %rsp, %rbp              
    callq *transmogrify_hooks(%rip)
    jmp *transmogrify_returns(%rip)
assembly_stub_2:
    push %rbp
    mov %rsp, %rbp
    leaq transmogrify_hooks(%rip), %rax
    /**
    I have no idea what I'm doing but the tests are passing
    */
    mov 8(%rax), %rax
    callq *%rax
    leaq transmogrify_returns(%rip), %rax 
    mov 8(%rax), %rax
    jmp *%rax
assembly_stub_3:
    push %rbp
    mov %rsp, %rbp
    leaq transmogrify_hooks(%rip), %rax
    /**
    I have no idea what I'm doing but the tests are passing
    */
    mov 16(%rax), %rax
    callq *%rax
    leaq transmogrify_returns(%rip), %rax 
    mov 16(%rax), %rax
    jmp *%rax
assembly_stub_4:
    push %rbp
    mov %rsp, %rbp
    leaq transmogrify_hooks(%rip), %rax
    /**
    I have no idea what I'm doing but the tests are passing
    */
    mov 24(%rax), %rax
    callq *%rax
    leaq transmogrify_returns(%rip), %rax 
    mov 24(%rax), %rax
    jmp *%rax
