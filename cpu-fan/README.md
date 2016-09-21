# CPU 风扇自动控制

## 工作原理
CPU 温度信息是可以通过读取 `/sys/class/thermal/thermal_zone0/temp` 得到的，如
```bash
cat /sys/class/thermal/thermal_zone0/temp
```
你将会得到类似于 `42236` 这样的数字，将这个数字除以 1000 即为 CPU 的核心温度，单位为`℃`

## 电路
本程序接法是从 GPIO 引脚接出三根线到继电器（5V 驱动），VCC 口接 5V，GND 接 GND，IN 口接的是 WiringPi 编号为 `0` 的引脚，即实际编号为 `11` 的引脚。  
继电器的另一端 `COM` 口由 GPIO 的 `5V` 引出（若你的风扇 3.3V 可以驱动，也可以从 3.3V 引出），`NO` 口与风扇正极相连，风扇负极与 GPIO 引脚中的 GND 相连。

## 触发温度
本程序启动后将启动风扇，运转 30s 后进入循环。  
触发风扇启动的温度为 `45℃`，只要高于 45℃，风扇将启动。  
风扇运转后温度下降到 `37℃` 以下时，停止运转。

## 编译
首先确保你已经安装了 WiringPi 库以及 GCC。  
运行以下命令进行编译

```bash
gcc -Wall -o fan fan.c -lwiringPi
```

编译好后即可执行

```bash
sudo ./fan
```