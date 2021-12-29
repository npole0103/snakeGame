# snakeGame
**snakeGameProjectCpp**

2020/12/10 ~ 2020/12/13

Time required : About 13 hours

Written : 2020/12/13

---
## Project Purpose
1. Studying and Practicing Class and OOP in CPP
2. Console control
3. Improving my coding skills.
4. Preparing to return to college in the third year

---
## Up to date error

Creating Item beyond the map // 2020/12/12 fix

Up and Down direction is faster than Left and Right direction //2020/12/12 fix

reason : Because Console size is x 120 and y 30, So I am to fix the gotoxy method x, y -> 2x, y

---

## Production review


### 개요
처음 SNAKEGAME을 만드려고 했을 때는 단순히 프로젝트라는 것을 하고 싶어서 막연히 시작했다.
2년 동안 군대에 있으면서 프로그램의 논리 구조를 설계하고 에러를 캐치하는 능력이 현저히 낮아졌을 거라 생각했다.
그러나 군대에서도 꾸준히 공부를 해놔서 그런지 예상외로 술술 풀렸고, 오히려 재학생 때보다 실력이 향상되었다는 느낌을 받았다.
시간은 생각보다 많이 걸렸지만 머리가 굳지 않았다는 것에 감사했다.

### 코드 논리제어 설명

#### 프로그램의 프레임
큰 틀은 다음과 같다.
```cpp
enum GameState {
	InitVeiw,
	Pause,
	GameStart,
	GameOver,
};
```
while loop 안에 있는 switch 문에서 GameState 상태를 제어한다.

> InitVeiw 메인 화면 출력
> 
> Pause 잠시 화면을 정지시킴
> 
> GameStart 게임 화면을 출력하며 게임 제어
> 
> GameOver 게임 종료 후 스코어 출력

initVeiw, Pause 그리고 GameOver는 사실상 단순하기 때문에 코드만 봐도 이해할 수 있다.

이 프로젝트의 메인 파트는 GameStart안에 있는 snake의 메소드 들이다.

---
#### 뱀이 움직이는 로직

> 초기에 길이 6짜리 뱀을 출력하고 방향키 키를 입력 받는다.
> 
> 입력 받은 키의 방향으로 가서 머리를 출력하고 꼬리를 지운다  
> *(무한루프 안에 있는 snakeMove 메소드는 우리 눈엔 움직이는 것처럼 보인다)*
> 
> item을 맵 내에서 계속 생성하며, 뱀의 머리 부분과 아이템이 충돌하면 몸통 길이를 1 늘린다.
> 
> 만약 뱀이 자기 몸과 충돌하거나 맵 밖으로 나가게 되면 GameState를 GameOver로 바꾸고 게임을 종료한다.

---
### 독특한 기능

만들다 보니 재미들려서 원래는 계획에 없었던 기능들을 추가 했다

- [ ] map의 클래스화 << ~~그냥 함수로 짰으면 금방할 거 였는데 삽질했다~~
- [ ] Best Score 도입
- [ ] RESTART
- [ ] PAUSE
- [ ] EXIT
- [ ] MODE에 따른 SPEED - EASY / NORMAL / HARD
- [ ] 초기 메인화면 SNAKEGAME 반짝 효과

---
### 직면했던 에러

#### _getch()

```cpp
key = _getch();

	if (key == 69 || key == 101) //easy mode
	{
		mode = 6;
		system("cls");
		gameState = GameStart;
		break;
	}
	else if (key == 78 || key == 110) // normal mode
	{
		mode = 4;
		system("cls");
		gameState = GameStart;
		break;
	}
	else if (key == 72 || key == 104) // hard mode
	{
		mode = 3;
		system("cls");
		gameState = GameStart;
		break;
	}
	else
	{
		int a = _getch();
		//erase buffer
		//Because UP key is 224 + 72
		//If int a = _getch() is not exist, its program would excute hard mode accroding to 72
		continue;
	}
```
원래는 else 문에 continue 하나만 있었다. 근데 실행하고 나니 버그가 생겼다.
메인화면에서 코드와 같이 E, N, H만 입력 받도록 코드를 짰는데 UP방향키를 입력하면 Hard 모드로 설정이 되는 것이었다.
나는 이런 현상을 처음엔 이해할 수 없었다.

그러던 중 처음 방향키 입력에 대해서 공부할 때 떠올렸던 2바이트가 생각났다.
방향키 UP은 2바이트 짜리이므로 224가 먼저 들어오고 72가 들어와야 UP으로 인식된다는 것을 공부하였다.
그런데 공교롭게도 H가 아스키코드 72다. 이 때문에 UP을 눌렀을 때 이런 일이 발생한다는 것을 직감했다.
 

_getch()가 없다면 UP키를 눌렀을 때 buffer에 224와 72가 들어가는데 224는 else문으로
들어가 continue를 만나고 다시 while문에 돌아가고 거기서 72라는 입력이 전달되어
Hard모드가 실행되게 된다. 이를 방지하기 위해 else문에 int a = _getch()를 통해 찌꺼기 buffer를 비워주어 해결하였다.

#### Pause
모든 기능을 잠깐 정지시키려면 어떻게 해야할지 고민했었다. 처음엔 initVeiw로 가게끔 하니까 잘 Pause 기능이 잘 작동되었다.
하지만 EASY, NORMAL, HARD 모드를 추가하면서 PAUSE는 그 기능을 잃었다. 게임을 잠시 멈추는 역할인데 InitVeiw로 가게 된다면
모드를 다시 설정해야한다. 이는 HARD모드에서 EASY모드로 바꿀 수 있는 일종의 버그였고 PAUSE 기능의 본질을 잃는 행동이었다.
그래서 최종적으로는 PAUSE 열거형을 하나 더 생성했다. 여기서 느낀점은 확실히
기능을 많이 세분화 해놓을 수록 수정과 구현이 빠르다는 것이었다. 밑에서도 언급하겠지만
OOP의 장점이 확연히 들어나는 부분이었다. 옛날 재학생 때는 프로젝트 당시 A에 오류가 있어 바꾸게 되면
B또한 바꿔야하고 B를 바꾸면 C도 바꿔야하는 연쇄 반응(?)이 일어났다. 근데 클래스나 열거형으로 기능을 나눠놓으니
에러가 발생하더라도 그 부분만 수정하거나 생성하면 되어 오류 제어적 측면에서 편리함이 보장되었다.

#### Up/Down speed and Left/Right speed different speeds

gotoxy라는 method는 콘솔에서 원하는 위치에 cout을 할 때 사용된다.
```cpp
void gotoxy(int x, int y)
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//why set the 2*x? Because console size is 120 : 30 = x : y
// if I set the 1*x and 1*y, it would be UP and DOWN faster than LEFT and RIGHT
```

현재는 2x, y로 설정되어있는데 처음에는 x, y로 설정하였다. 보통 사람들이라면 당연히 나처럼 생각할 것이다.
그런데 x,y로 설정해놓고 실행해보니 출력도 끊겼고, 상하로 움직일 때랑 좌우로 움직일 때랑 속도가 다르다는 것을 깨달았다.
왜 이런 것인가 생각해봤는데 콘솔 크기와 출력 화면에서 그 해답을 찾을 수 있었다. 백준에서 2차원 배열 문제를 풀 때도 많이 느꼈는데
콘솔창에서 n*n 배열을 출력해도 크기가 생각하는 것 만큼 균일하지 않다. 이때의 경험을 떠올리며 x를 2배해주었다.
그랬더니 속도도 비슷해졌고 출력도 균일하게 되는 것을 확인할 수 있었다.

---
### 마치며

대학교 1학년 수준의 프로젝트였지만 전역하고 나서 구현한 첫 프로젝트라 그런지 느낀 것이 많았다.

재학생 때는 OOP를 왜 쓰는지 이해가 가지 않았다. **get? set? 아무리 캡슐화를 해서 정보은닉을 하면 뭐해? 참조할 때 귀찮게 메소드 만들어야하는데**라고 생각했던 나였다.
아마 제대로 된 OOP 프로젝트를 해보지 않아서 그런 생각을 했었던 거 같다. get과 set을 쓰는 것이 지금보니 깔끔하였고
무엇보다 클래스 내에서 메소드를 구현하니 수정이 간편하였고 코드가 일관성이 있었다.
앞으로도 OOP를 자주 활용하여야겠다는 생각이 들었다.

또한 이번 프로젝트를 하면서 Divide and conquer의 중요성을 가장 크게 깨달았다.
2017년 1학년 때 C언어를 배우며 모듈화와 분할의 중요성에 대해 배운 적이 있다. 이때는 
잘 이해가 가지 않았다. 오히려 **한 곳에다 때려놓아두면 찾기 편하고 수정이 간단한 거 아닌가?** 라는 생각을 했다
지금 생각해보면 우물 안 개구리였다. A에 오류가 생겨 A를 고치면 B를 고쳐야하고 B를 고치자니 C를 고쳐야하고 이런 문제를 재학생 때 프로젝트 당시 많이 느꼈던 거 같다.
과거의 나는 모듈화와 분할에 대해 무지했던 게 아닌가 싶다. 이번 프로젝트에선
가장 큰 제어를 GameState로 하면서 화면의 제어가 간편하였다. 또 위에서 언급했던 것처럼 메소드가 클래스 내에 있으니
수정하기 간편하였다. 몇 줄 안되는 코드여서 파일을 분할하진 않았지만, 나름 신경써서 코드를 모듈화, 메소드화 하고 main 함수에 들어갈 코드를 최소화 했다.

과거의 모듈화를 소홀히 해서 고생했던 내가 없었더라면 느끼지 못할 경험이었다.

이래서 실패는 성공의 어머니라고 하나보다

이렇게 작은 사이드 프로젝트를 하면서 느낀 것도 많은데 더 큰 프로젝트를 하면 얼마나 뼈저리게 느낄까 라는 생각도 든다.

나는 한참 부족하다. 스스로를 평가해보고 주위에 잘하는 사람들을 봐도
아직 내 자신은 프로그래머로서 20%도 도달하지 못했다는 생각이든다.

배움의 길에 있어서 항상 새로운 것을 받아들이려는 자세를 취해야겠다.

나는 아직도 배고프다.

---
## CODE COMMENT

**코드 피드백 언제나 환영합니다**

[@Nevation](https://www.github.com/Nevation)

### 1. 함수 200줄 정도 되면 파일 나누기
### 2. 전역변수 쓰는 것보다 클래스 만드는 것이 메모리적으로 효율 증대
### 3. 파일 네이밍 규약 (스네이크 케이스, 카멜 케이스)
### 4. `key = getKey()`
### 5. 135 Lines `quit = (i != (snakeLen - 1));`
### 6. x, y 좌표를 #define 이나 const 로 작성할 것.
### 7. 151 Lines `snakeLen += (snakeLen < MAXLEN - 1);`
### 8. Map Class에 소멸자 넣기
### 9. Pause에 break 넣기
### 10. STL 많이 활용하기 -> 포인터 쓰면 메모리 누수 잡는 것이 힘듦. STL은 알아서 해결해 줌

---
## 코드 참고
[메인화면 글자 뼈대 출처](https://blog.naver.com/forcommang/221495736927)

[방향키 입력 참고](https://blog.naver.com/sharonichoya/220875372940)

[snakeMove / gotoxy 메소드 참고](https://blog.naver.com/whddnr746/221808605143)

[2차원 배열 heap 메모리에 할당하는 법](https://blog.naver.com/dic1224/220975113201)

[������ �����]()

### 1. ���� ���� �ʹ� ����ߴ�. �� ���� � �������� �˾ƺ��� �����.


---

