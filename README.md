# 电池测试系统（Qt 上位机）

基于 Qt Widgets 开发的电池测试上位机，通过串口与 BMS 设备通信，
实时采集电压、电流、温度和 SOC，支持实时曲线、数据持久化和历史记录查询。

## 功能

- 串口通信（基于 Qt SerialPort）
- Modbus RTU 协议读写保持寄存器（0x03 功能码）
- 电压 / 电流 / 温度 / SOC 实时采集与显示
- 实时曲线绘制（QChart，每秒刷新）
- SQLite 数据库持久化测试记录与采样数据
- 历史记录查询与明细查看
- 多页面切换（QStackedWidget）
- 状态栏实时显示串口 / 设备 / 测试状态

## 技术栈

| 类别 | 技术 |
|---|---|
| 语言 | C++17 |
| 框架 | Qt 6.11（Widgets、SerialPort、SQL、Charts） |
| 协议 | Modbus RTU（串口） |
| 数据库 | SQLite |
| 构建 | qmake |

## 项目结构

```text
BatteryTester/
├── main.cpp                          # 程序入口
├── mainwindow.cpp/h/ui               # 主窗口
├── homepage.cpp/h                    # 首页
├── testpage.cpp/h                    # 测试页
├── datapage.cpp/h                    # 数据页
├── alarmpage.cpp/h                   # 警报页
├── communicationpage.cpp/h           # 通信配置页
├── settingpage.cpp/h                 # 设置页
├── serialportmanager.cpp/h           # 串口管理
├── modbusdevice.cpp/h                # Modbus 设备（协议层）
├── modbusrtu.cpp/h                   # Modbus RTU 组帧与解析
├── batterytestmanager.cpp/h          # 测试业务逻辑
├── databasemanager.cpp/h             # 数据库管理
├── batterydata.h                     # 电池数据结构
└── BatteryTester.pro                 # qmake 工程文件
```

## 架构设计

分层架构，各层通过信号槽解耦：

```text
UI 层（TestPage / DataPage / CommunicationPage ...）
        ↕ 信号槽
业务层（BatteryTestManager）
        ↕
协议层（ModbusDevice / ModbusRTU）
        ↕
通信层（SerialPortManager）
        ↕
串口（QSerialPort）
        ↕
数据层（DatabaseManager → SQLite）
```

## 运行环境

- Qt 6.11 或更高
- MinGW 13.1 或 MSVC 2019+
- 支持 Windows / Linux / macOS

## 编译与运行

```bash
# 1. 克隆项目
git clone <仓库地址>

# 2. 用 Qt Creator 打开 BatteryTester.pro
# 3. 选择构建套件，构建并运行
```

## 打包发布

```bash
windeployqt BatteryTester.exe
```

## 作者

MXY
