# Fashion Police Squad 모작 팀 프로젝트

Mopeful Games 회사의 FPS 장르인 Fashion Police Squad 라는 3D 게임을 팀으로 모작하였습니다.

## 사용된 기술
-   ![C](https://img.shields.io/badge/C%20-%232370ED.svg?&logo=c&logoColor=white)
 ![C++](https://img.shields.io/badge/C++%20-%2300599C.svg?&logo=c%2B%2B&logoColor=white)
 ![WinAPI](https://img.shields.io/badge/WinAPI%20-%236DA252.svg?&logo=WinAPI&logoColor=white)

<br>
<br/>

<!--프로젝트 대문 -->
[![Video Label](https://ifh.cc/g/Q22Mxc.jpg)](https://youtu.be/rMgPxKtVPes?t=17)

# 개발 기간 및 참여 인원
   
 개발기간 : 2023.06.29 ~ 2023.07.13
   
 참여 인원 : 1 people

# 중점 구현 사항

가장 처음으로 제작해본 모작 프로젝트였습니다.

- 객체지향 중심의 코드를 작성했으며 플레이어를 비롯한 NPC들이 모두 자신 만의 기능을 구현하게 했습니다.

- 플레이어는 키입력에 의해 조작하며 NPC들은 AI 로직을 수행합니다.

- 충돌은 AABB 충돌을 사용하였고, 무한 충돌을 막기위해 충돌 대기 시간을 두어 처리했습니다.
  
- 스프라이트 애니메이션은 각 NPC들의 상태(공격, 피격 등)에 해당하는 애니메이션 개수에 따라 재생할 프레임을 처리했습니다.
  
- 보스 방 입장시에 타이머를 작동해 클리어 타임을 계산했습니다.
  
- HP와 MP UI의 프레임 형태에 맞게 가로, 세로 형태로 비율을 계산했습니다.
  
- 스왑 알고리즘과 벡터 컨테이너를 사용하여 인벤토리와 장비창의 기능을 구현했습니다.

- 싱글턴 패턴과 키 입력, 충돌, 스테이지 등의 매니저 객체들을 작성했습니다.
