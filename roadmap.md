# IDT, ISR, PIC 구현 로드맵

현재 GDT가 구현되었으므로, 시스템의 인터럽트 처리를 위한 다음 단계인 IDT와 PIC 구현 로드맵을 제시합니다.

## 1단계: IDT(Interrupt Descriptor Table) 기초 설계
- **`src/kernel/i386/idt.h` 완성**:
  - `idt_entry`, `idtr` 구조체 정의 (현재 `idt.c`에 있는 것을 이동).
  - 인터럽트 게이트 타입(Interrupt Gate, Trap Gate) 정의.
- **`src/kernel/i386/idt.c` 구현**:
  - `idt_set_gate` 함수: 특정 인덱스에 인터럽트 핸들러를 등록하는 로직.
  - `idt_init` 함수: 전체 IDT를 초기화하고 초기 핸들러들을 등록.

## 2단계: ISR(Interrupt Service Routines) 어셈블리 래퍼
- **`src/kernel/i386/interrupt.asm` 작성**:
  - CPU 예외(0~31번) 처리를 위한 공통 래퍼 코드.
  - 레지스터 상태(`pusha`) 저장 및 C 핸들러 호출 로직.
  - `iret`을 이용한 복귀 처리.
- **`src/include/asmb.h` 업데이트**:
  - `lidt` 명령어를 실행할 `load_idt` 프로토타입 추가.

## 3단계: PIC(Programmable Interrupt Controller) 리매핑
- **`src/kernel/i386/pic.c` 완성**:
  - 하드웨어 인터럽트(IRQ 0~15)가 CPU 예외 번호와 겹치지 않도록 리매핑 (기본 0x08~0x0F -> 0x20~0x2F).
  - `pic_send_eoi` 함수: 인터럽트 종료 신호 전송 로직.
  - `pic_mask` / `pic_unmask`: 특정 IRQ 활성화/비활성화.

## 4단계: 공통 인터럽트 핸들러 (C 영역)
- **`src/kernel/i386/isr.c` (또는 idt.c 내부에 구현)**:
  - 어셈블리에서 넘겨준 레지스터 상태(`registers_t`)를 인자로 받는 C 함수.
  - 예외 번호에 따른 메시지 출력 (예: Division by Zero, Page Fault).
  - 하드웨어 인터럽트(IRQ) 분기 처리.

## 5단계: 시스템 통합 및 테스트
- **`src/kernel/main.c` 수정**:
  - `init()` 함수 내에서 `init_idt()` 및 `init_pic()` 호출.
- **인터럽트 활성화**:
  - `asm volatile("sti")`를 호출하여 CPU 인터럽트 허용.
- **테스트**:
  - `int $0x03` (Breakpoint) 또는 0으로 나누기 등의 소프트웨어 예외를 발생시켜 핸들러가 정상 작동하는지 확인.
  - 타이머(PIT) 인터럽트를 통해 주기적인 IRQ 발생 확인.

---
**교수의 조언:** 
인터럽트는 커널의 심장입니다. 특히 어셈블리와 C 사이의 스택 프레임(Stack Frame)이 일치하지 않으면 시스템이 즉시 `Triple Fault`로 재부팅될 수 있으니, 레지스터 저장 순서에 주의하십시오.
