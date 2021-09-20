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
    add $8, %rax
    /**
    I have no idea what I'm doing but the tests are passing
    */
    mov (%rax), %rax
    callq *%rax
    leaq transmogrify_returns(%rip), %rax 
    add $8, %rax
    mov (%rax), %rax
    jmp *%rax
assembly_stub_3:
    push %rbp
    mov %rsp, %rbp
    leaq transmogrify_hooks(%rip), %rax
    add $16, %rax
    /**
    I have no idea what I'm doing but the tests are passing
    */
    mov (%rax), %rax
    callq *%rax
    leaq transmogrify_returns(%rip), %rax 
    add $16, %rax
    mov (%rax), %rax
    jmp *%rax
assembly_stub_4:
    push %rbp
    mov %rsp, %rbp
    leaq transmogrify_hooks(%rip), %rax
    add $24, %rax
    /**
    I have no idea what I'm doing but the tests are passing
    */
    mov (%rax), %rax
    callq *%rax
    leaq transmogrify_returns(%rip), %rax 
    add $24, %rax
    mov (%rax), %rax
    jmp *%rax
