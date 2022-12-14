# 6-Legged
pinocchio UNIST robot club legacy
## Introduction
- 현재 유니스트 석박과정중인 황재박씨가 남겼던 유산이 소실되었다. 그의 노고를 기리고자 6족 로봇을 복원했다.

  그러나 이전의 프로젝트에 비해 오로지 HW 부품만 같고, 회로와 펌웨어 및 제어가 달라서 아예 다른 로봇이라고 할 수 있다.
  
  시간이 지남에 따라 기술도 발전했기에, 이 프로젝트의 발전 가능성을 고려해서 몇가지 업그레이드를 했다.
  
  ### 발전1. 파워 시스템
  파워 서플라이로 사용하지 않고, 배터리로 안정적으로 전력을 공급하는 회로를 만들었다.

  ### 발전2. 비동기 제어 
  코드를 통해 시분할 시스템을 만들어  쓰지 않고, 멀티쓰레딩이 가능한 보드를 써서 펌웨어 구성을 쉽게 했다.

  ### 발전 3. 시뮬레이션
  서보모터의 각도를 일일히 계산해서 코드에 사용하하는 방식이 아니라, 각도를 알아내는 용도의 유니티 프로젝트를 만들어 직관적으로 실험해볼 수 있게 했다.
  
- The legacy left by Hwang Jae-bak, who is currently studying for a master's degree at UNIST, has been lost. 

  To honor his hard work, I decided to restore the 6-legged robot.
  
  Compared to the previous project, only the HW parts are the same, the circuit, firmware and control system are different, so they are a completely different robots.
  
  As technology has improved over time, I have made several upgrades considering the sustainability of this project.

  ### Improvement1. power system
  Circuit that stably supplies power with a battery without using it as a power supply.

  ### Improvement 2. asynchronous control
  Instead of creating a time-sharing system through C programming, board capable of multi-threading is used to simplify firmware code.

  ### Improvement 3. Simulation
  Rather than calculating the angle of the servomotor by hand, I created a Unity project to find out the angle of the motor so that I could experiment intuitively.
