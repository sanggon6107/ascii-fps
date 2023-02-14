# Maze-runner

## 서문
콘솔에 유니코드를 이용해 3D 미로를 만들어주는 프로그램. Youtube 채널 "javidx9"이 그의 영상에서 작성한 코드를 기반으로 작성하였으며, 일부는 개량하기도, 또 일부는 본인이 기능을 추가하였다. "C++로 3D 공간을 어떻게 그려낼 수 있을까?"라는 단순한 호기심에 시작했다. 

이 소스코드를 작성하면서 게임, 특히 그래픽스 분야가 내 편견과는 다르게 매우 고도의 수학적 지식이 필요한 분야라는 인상을 받았다.

한편으로는 프로그래밍을 독학하던 시절 인터넷에 돌아다니는 다양한 코딩 문제를 풀다가 배운, "Hunt and kill algorithm"을 활용해볼 수 있었던 경험은 과거에 배웠던 알고리즘을 복습할 수 있어 매우 귀중한 시간이 되었다.

몇몇 줄의 코드는 더 나은 코드를 고민할 거리가 되기도 했는데, 가령 벽의 바운더리를 그리는 알고리즘은 참고가 된 영상의 방법이 너무 복잡한데다가 항상 완벽하게 화면상의 바운더리를 잡아주지는 못한다는 단점도 가지고 있었기 때문에, 후술할 몇번의 시행착오를 거쳐 현재의 간단하면서도 비교적으로 안정적인 형태가 되었다.


![gameplay](https://github.com/sanggon6107/ascii-fps/blob/master/Media/gameplay.gif?raw=true)