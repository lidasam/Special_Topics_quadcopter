clear all % 清空workspace
clc       % 清空command window
close all 


k=361.2/0.000443/4500
num=45000*k
Gp=tf(num,[10 3612 0]);
sys1=tf(num,[10 3612]);
[Gm,Pm,Wcg,Wcp]=margin(Gp);
Wcp
Gm=20*log10(Gm)
Wcg
Pm


sys0=feedback(Gp,1)
step(sys0,'b')
hold on
grid on

Kp=1; Ki=0; Kd=0.00177;
Gc=tf([Kd Kp Ki],[1 0]);
sys=feedback(series(Gc,Gp),1);
step(sys,'g')
hold on

Kp2=0.08; Ki2=0.08; Kd2=0;
Gc2=tf([Kd2 Kp2 Ki2],[1 0]);
sys2=feedback(series(Gc2,Gp),1);
step(sys2,'r')
hold on

Kp3=0.08014; Ki3=0.08; Kd3=0.0001416;
Gc3=tf([Kd3 Kp3 Ki3],[1 0]);
sys3=feedback(series(Gc3,Gp),1);
step(sys3,'c')
legend ('Original System','PD controller: Kp=1, Kd=0.000177','PI controller: Kp=0.08, Ki=0.08','PID controller: Kp=0.08014, ki=0.08, Kd=0.0001416')
hold on

bw=bandwidth(sys0,-3)





