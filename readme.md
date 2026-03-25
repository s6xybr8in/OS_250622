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
여러 태스크 번갈아 실행
2. Scheduler
실행 순서 결정
Round Robin 등 구현
🎓 교수의 조언
OSDev Wiki 적극 활용
디버깅이 90%
qemu -serial stdio 사용 필수
Multiboot 정보 활용
eax, ebx로 전달된 구조체 파싱
메모리 크기, 모듈 정보 확인