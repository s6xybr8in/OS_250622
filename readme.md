Phase 1: 기반 다지기 (CPU 제어)

커널이 올라갔지만, 아직 CPU는 부트로더가 설정해준 최소한의 환경에서 동작합니다.
이를 커널에 맞게 재정의해야 합니다.

1. GDT (Global Descriptor Table)
32비트 보호 모드에서 메모리 세그먼트 정의
커널 코드/데이터, 유저 코드/데이터 세그먼트 분리
2. IDT (Interrupt Descriptor Table) 및 ISR
CPU 예외 (Divide by Zero, Page Fault 등) 처리
하드웨어 인터럽트 처리
없으면 오류 발생 시 Triple Fault로 시스템 정지
3. PIC (Programmable Interrupt Controller) 리매핑
하드웨어 인터럽트 번호를 CPU 예외와 겹치지 않게 재배치
Phase 2: 소통의 창구 마련 (I/O)

--nographic 환경 기준 → VGA보다 Serial이 우선

Serial Port Driver
COM1 포트로 출력
printf 구현 → QEMU 콘솔 로그 출력
디버깅 핵심
PIT (Programmable Interval Timer)
주기적 인터럽트 발생
멀티태스킹의 기반
Phase 3: 자원 관리 (메모리)

가장 중요한 핵심 단계

1. PMM (Physical Memory Manager)
RAM 사용 여부 관리
방식: Bitmap / Stack 추천
Multiboot Memory Map 활용
2. Paging (Virtual Memory)
가상 메모리 구현
프로세스별 메모리 공간 분리
Higher-half kernel 구성
3. Heap Allocator (kmalloc)
커널 내부 동적 메모리 할당
Phase 4: 생명력 (멀티태스킹)
1. Context Switching
레지스터 상태 저장/복원

---
## 📅 학습 기록 (Learning Logs)

### [2026-03-29] 인터럽트 시스템 및 I/O 구현 원리
**1. 인터럽트 메커니즘의 이해**
- **PIC Remapping**: 하드웨어 IRQ(0~15)를 CPU 예외와 겹치지 않게 IDT 32번 이후로 재배치하는 이유와 방법 학습.
- **ISR 구조**: 어셈블리 래퍼를 통한 Context Save/Restore의 중요성 및 `iret` 명령어를 통한 복귀 메커니즘 파악.
- **IDT**: 게이트 디스크립터를 통해 인터럽트 핸들러를 등록하는 전체적인 흐름 정리.

**2. 커널 전용 printf 구현**
- **가변 인자 처리**: `stdarg.h` 없이 스택 포인터 연산(`(char*)&fmt + sizeof(fmt)`)으로 인자를 추출하는 원리 습득.
- **문자열 파싱**: `%d`, `%x`, `%s` 등 포맷 문자를 분석하여 적절한 출력 함수로 분기하는 로직 설계.
- **주의 사항**: `str++`를 통한 루프 진행 보장, `print_int`에서 0 및 음수 처리의 필수성 확인.
**3. Freestanding C 환경**
- `argc`/`argv`가 자동 제공되지 않는 이유와 Multiboot 정보를 통한 커널 인자 획득 방법 이해.

### [2026-03-31] IDT 및 인터럽트 게이트 설계 심화
**1. IDT (Interrupt Descriptor Table) 구조 설계**
- **Gate Descriptor**: 8바이트 구조 내에서 주소(Offset)가 쪼개져 있는 이유(역사적 호환성)와 `Selector`, `Access Byte`의 역할을 이해함.
- **IDTR**: 6바이트 크기의 특수 레지스터 구조와 `lidt` 명령어 사용 시 '간접 참조'의 중요성(스택의 주소값이 아닌 주소가 가리키는 실제 데이터를 로드)을 파악.

**2. Interrupt Gate vs Trap Gate**
- **Interrupt Gate (0xE)**: 진입 시 CPU가 자동으로 `IF`(Interrupt Flag)를 Clear하여 중첩 인터럽트를 방지함. 하드웨어 IRQ 처리에 적합.
- **Trap Gate (0xF)**: `IF` 비트를 유지하여 핸들러 내부에서도 인터럽트가 발생할 수 있게 함. 소프트웨어 예외 및 시스템 콜에 적합.
- **초기 설계 전략**: 커널 안정성을 위해 우선 모든 엔트리를 Interrupt Gate로 설정하여 원자적(Atomic) 처리를 보장하는 것이 유리함을 학습.

**3. 어셈블리 인터페이스 구현 시 주의사항**
- `load_idt` 구현 시 `mov eax, [esp+4]` 후 `lidt [eax]`를 호출해야 함을 확인 (포인터와 값의 차이).
- C 구조체 정의 시 `__attribute__((packed))`를 사용하여 컴파일러의 패딩 삽입을 방지해야 함.

**4. ISR (Interrupt Service Routine) 구현 원리**
- **Error Code 처리**: CPU가 에러 코드를 자동으로 푸시하는 예외(8, 10-14번 등)와 그렇지 않은 예외를 구분하여, 일관된 스택 프레임을 위해 에러 코드가 없는 경우 가짜(Dummy) 에러 코드 `0`을 푸시함.
- **Context Save/Restore**: `pusha`를 통해 범용 레지스터를 저장하고, `ds`, `es` 등 세그먼트 레지스터를 커널 데이터 세그먼트로 교체하여 안전한 실행 환경을 구축함.
- **Stack Frame Alignment**: 어셈블리에서 `push`하는 순서와 C언어의 `registers_t` 구조체 멤버 순서를 정확히 일치시켜야 핸들러에서 올바른 레지스터 값을 읽을 수 있음.
- **Stack Cleanup & iret**: 핸들러 종료 시 `add esp, 8`을 통해 우리가 임의로 푸시한 인터럽트 번호와 에러 코드를 제거하고, 반드시 `iret` 명령어를 사용하여 `EIP`, `CS`, `EFLAGS`를 원자적으로 복원해야 함.
---