# 모의시험 1

[모의시험 목록](../README.md) · [전체 목차](../../README.md) · [12 실전 연습](../../units/12-practice/README.md)

- 제한 시간: **60분**, 4문제
- 범위: 구현, 문자열, 정렬, 해시, 누적합 중심
- 문제는 대체로 쉬운 것부터 조금 더 생각해야 하는 순서로 놓여 있지만, 체감 난이도는 사람마다 다르다. 시작할 때 네 문제를 모두 훑어본다.

## 시험 규칙 (스스로 지킬 것)

1. 타이머를 60분으로 맞추고, 끝나면 풀던 문제가 있어도 멈춘다.
2. 시험 중에는 힌트(`hints.md`), 해설(`solutions/`), 단원 설명, 테스트 파일(`tests/`)을 열지 않는다.
   [STL 치트시트](../../docs/cheatsheet.md)는 문법 확인용으로 봐도 된다.
3. 채점(`./ct test <ID>`)은 횟수 제한 없이 해도 된다. 다만 실패한 테스트의 입력을 보고 답을 끼워 맞추지 않는다.
4. 문제 제목과 본문에는 사용할 알고리즘이 적혀 있지 않다. 입력 제한을 보고 스스로 고른다.

## 문제

| 번호 | ID | 문제 | 풀이 파일 | 채점 |
|---|---|---|---|---|
| 1 | e1a | [연속 문자 세기](../../problems/e1a-run-count/problem.md) | [main.cpp](../../problems/e1a-run-count/main.cpp) | `./ct test e1a` |
| 2 | e1b | [마라톤 기록](../../problems/e1b-marathon/problem.md) | [main.cpp](../../problems/e1b-marathon/main.cpp) | `./ct test e1b` |
| 3 | e1c | [출입 기록](../../problems/e1c-entry-log/problem.md) | [main.cpp](../../problems/e1c-entry-log/main.cpp) | `./ct test e1c` |
| 4 | e1d | [묶음 포장](../../problems/e1d-bundle/problem.md) | [main.cpp](../../problems/e1d-bundle/main.cpp) | `./ct test e1d` |

## 진행 방법

```bash
./ct exam 1            # 문제 목록 확인 후 타이머 시작
./ct test e1a            # 문제별 채점 (다른 문제도 같은 방식)
./ct run e1a             # 직접 입력을 넣어 실행해 보기
./ct exam 1 --grade    # 종료 후 4문제 일괄 채점
```

## 권장 시간 배분

| 시간 | 할 일 |
|---|---|
| 0~5분 | 네 문제를 모두 읽고 풀 순서를 정한다. 각 문제의 입력 제한과 출력 조건에 표시한다. |
| 5~15분 | 가장 쉬워 보이는 문제 |
| 15~30분 | 두 번째 문제 |
| 30~55분 | 남은 두 문제. 15분 이상 진전이 없으면 다른 문제로 넘어간다. |
| 55~60분 | 새 코드는 쓰지 않고, 통과한 풀이의 경계조건(최소 입력, 최댓값, 답 없음)을 점검한다. |

이 배분은 연습을 위한 기준일 뿐이다. 실제 시험의 구성은 시험마다 다르다.

## 시험이 끝난 뒤

1. `./ct exam 1 --grade`로 결과를 확인한다.
2. [회고 양식](../retrospective-template.md)을 복사해 문제별로 작성한다.
3. 못 푼 문제는 시간 제한 없이 다시 시도 → 그래도 막히면 힌트 1단계 → 2단계 → 해설 순으로 본다.
4. 해설에서 "사용한 방법"과 관련 단원을 확인하고, 해당 단원의 체크리스트를 다시 점검한다.

<details>
<summary>해설 링크 (시험이 끝난 뒤에 펼칠 것)</summary>

- [1번 해설](../../solutions/e1a-run-count/solution.md)
- [2번 해설](../../solutions/e1b-marathon/solution.md)
- [3번 해설](../../solutions/e1c-entry-log/solution.md)
- [4번 해설](../../solutions/e1d-bundle/solution.md)

</details>
