// to set a different entry point
// @entry newPath

section .code:
    global _start

// the brackets are only for readability, this does not affect the code
_start: {
    mov rax, 0x04
    mov rdi, 0x01
    mov rsi, Message
    mov rdx, @Length(Message)
    syscall

    mov rax, 0x3C
    xor rdi, rdi
    syscall
}

/*newPath: {
    mov rax, 0x3C
    mov rdi, 0x01
    syscall
}*/

section .data:
    // 8 is used to represent the alignment
    Message(8) = "Hello world!", 0x0A