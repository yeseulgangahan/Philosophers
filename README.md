# Philosophers
![image](https://github.com/yeseulgangahan/Philosophers/assets/88709878/4ed31d17-edc9-4b11-af79-b22154ead202)

철학자들이 공평하게 밥을 먹고 잠을 자고 생각하는 멀티스레드/멀티프로세스 시뮬레이션입니다. 운영체제의 Deadlock 상태를 설명하는 대표적인 예시인 식사하는 철학자 문제를 해결하고 있습니다.

## Preview
<img width="760" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/40653501-7a07-4ad2-97a8-33662e63ec5d">

<img width="760" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/791fc3d2-9956-41a0-b94a-da8c06f90a92">


## Features
- 사용자가 지정한 수만큼의 스레드 및 프로세스를 스케줄링
- 데드락을 예방하고 기아를 방지
- 타임스탬프와 함께 각 철학자의 현재 행동을 설명하는 메시지 출력
- 철학자가 죽었을 시 10ms 이내에 메시지 출력 중단

## Usage
### 1. 빌드하기
```
make
```
로 스레드와 뮤텍스를 사용하는 프로그램을,
```
make bonus
```
로 프로세스와 세마포어를 사용하는 프로그램을 빌드합니다.

### 2. 실행하기
인자와 함께 프로그램을 실행합니다.
```
./philo <number of philosophers> <time to die> <time to eat> <time to sleep> (<number of times each philosopher must eat>)
```

- number of philosophers: 철학자의 수이자 포크의 수입니다.
- time to die: 철학자는 마지막 먹은 후로 time to die 시간 전에 먹지 못하면 죽습니다. (millisecond 단위)
- time to eat: 철학자가 먹는 데에 걸리는 시간입니다. 먹는 동안 2개의 포크가 필요합니다. (millisecond 단위)
- time to sleep: 철학자가 자는 데에 걸리는 시간입니다. (millisecond 단위)
- number of times each philosopher must eat: 이 인자는 옵션입니다. 모든 철학자가 number of times each philosopher must eat 만큼 먹으면 시뮬레이션은 멈춥니다. 인자가 설정되지 않으면 시뮬레이션은 철학자가 죽었을 때 끝납니다.

## Peer Reviews
<img width="532" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/beaa7d0e-db5d-436b-b33f-0219f21cee4d">
<img width="532" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/6f6910a4-5510-4954-a71f-b40d01294ba7">
<img width="532" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/4ba0d87e-dee6-419c-82e3-bbe16564434c">
<img width="532" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/4fef8d63-da70-4cc6-b15a-00da41e036c6">
<img width="532" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/3848e8fd-c0aa-4baa-b1a4-b33b98f3b69b">
<img width="532" alt="image" src="https://github.com/yeseulgangahan/Philosophers/assets/88709878/0700ee35-3a3f-4b5e-840f-14195a296d64">
