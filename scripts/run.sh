#!/bin/bash

SESSION="os_dev"

# 1. 빌드
make clean
make

# 2. 기존 세션 제거
pkill qemu
tmux kill-session -t $SESSION 2>/dev/null || true

# 3. 새 세션 생성 (빈 bash)
tmux new-session -d -s $SESSION -n main

# 4. pane 2개를 좌우(-h)로 생성
tmux split-window -h -t $SESSION:main.0

#현재 구조
# pane 0 (왼쪽)
# pane 1 (오른쪽)

# 5. 왼쪽 pane(0)에 QEMU 실행
tmux send-keys -t $SESSION:main.0 'make debug' C-m

sleep 1

# 6. 오른쪽 pane(1)에 GDB 실행
tmux send-keys -t $SESSION:main.1 \
'gdb' C-m

# 7. 왼쪽으로 포커스
# tmux select-pane -t $SESSION:main.0

# 8. attach
tmux attach -t $SESSION