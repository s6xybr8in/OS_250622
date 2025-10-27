this prac will prepare to Interupt

1. PIC
2. IDT
    - sti -> something loop
        - pic wait i/o 
        o_wait:
    out 0x80, al
    ret

    remap_pic:
        cli
        mov al, 0x11
        out 0x20, al
        call io_wait
        out 0xA0, al
        call io_wait

        mov al, 0x20 ; master offset = 0x20
        out 0x21, al
        call io_wait
        mov al, 0x28 ; slave offset = 0x28
        out 0xA1, al
        call io_wait

        mov al, 0x04 ; tell master there is a slave at IRQ2
        out 0x21, al
        call io_wait
        mov al, 0x02 ; tell slave its cascade identity
        out 0xA1, al
        call io_wait

        mov al, 0x01 ; 8086 mode
        out 0x21, al
        call io_wait
        out 0xA1, al
        call io_wait

        sti
        ret
    모든 IRQ 마스크 + STI: PIC 마스크(0x21,0xA1)에 0xFF 씌우고 sti. 만약 루프 멈추면 IRQ가 원인.

    IDT를 안전한 'ignore' 핸들러로 가득 채우기: 모든 벡터를 ignore_handler (단순 iret만 하는 핸들러)로 채운 뒤 lidt → sti. 루프 멈추면 기존 ISR들이 문제.

    ISR 내부에 hlt 추가(테스트용): ISR 맨 끝에 hlt 넣어보고 QEMU가 멈추는지 확인(단, 실사용 아님).

    예를 들어:

    IDT를 ignore_handler로 채운다.

    lidt, sti 호출.

    CPU가 루프 돌면 IDT/GDT/스택 문제. 루프 멈추면 이전 ISR 구현 문제.

    ignore_handler 예:

    ignore_handler:
        iret

3. ISR(Interupt Service Rootine)


