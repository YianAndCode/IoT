# 台灯控制

## 电路
本程序接法是从 GPIO 引脚接出三根线到继电器（5V 驱动），VCC 口接 5V，GND 接 GND，IN 口接的是 WiringPi 编号为 `15` 的引脚，即实际编号为 `8` 的引脚。  
继电器的另一端用了 `COM` 口和 `NO` 口，与插座相连。

**继电器是接在 220V 交流电下的，切记注意用电安全！**  
**继电器是接在 220V 交流电下的，切记注意用电安全！**  
**继电器是接在 220V 交流电下的，切记注意用电安全！**  

若你用的 GPIO 口和我不同，可根据你的实际情况修改 `PHP/lamp.php` 中 `exec()` 相关的参数，具体用法见下方 C 程序部分的介绍。

## 编译
首先确保你已经安装了 WiringPi 库以及 GCC。  
运行以下命令进行编译

```bash
cd C
gcc -Wall -o gpioctrl gpioctrl.c -lwiringPi
```

编译好后建议复制到 `/usr/bin` 目录中使用

```bash
sudo cp gpioctrl /usr/bin
```

然后就可以使用 `gpioctrl <action> <pin>` 执行。  
其中 `<pin>` 为你要操作的引脚的 WiringPi 编号， `<action>` 可以传递的参数有 `on`、`off`、`status`，分别对应给 `<pin>` 引脚输出 `HIGH`、`LOW` 和读取该引脚的电压状态（`HIGH` 或 `LOW`）。

## 给 PHP 赋予执行权限
首先把 `PHP` 目录下的文件复制到你的 web 目录中。

PHP 脚本默认是不能以 sudo 身份执行 gpioctrl 的，而 gpioctrl 又需要 sudo 权限。

那么我们需要创建（默认是不存在的）并编辑 `/etc/sudoers.d/mount` 这个文件，添加下面这行：
```
www-data ALL=(ALL:ALL) NOPASSWD:/usr/bin/gpioctrl
```
这样 PHP 就可以以 `www-data` 用户的身份免密码运行 `gpioctrl` 了。