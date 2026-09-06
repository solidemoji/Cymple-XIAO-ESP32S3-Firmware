# Cymple XIAO ESP32-S3 Sense Firmware

Cymple 嘴部追踪固件的 **Seeed Studio XIAO ESP32-S3 Sense** 移植版。

> ⚠️ **第三方适配声明 / Third-party Adaptation Notice**
>
> 本项目是 [Dominocs/Project_Cymple](https://github.com/Dominocs/Project_Cymple) 仓库中
> `esp源代码`（开源版固件，版本 DIY_1_3_3）的**硬件适配分支**。
> 原作者 **Dominocs** 保留原始代码的全部版权；本项目作者与原作者**无任何关联**，仅作为第三方
> 为其固件增加了 XIAO ESP32-S3 Sense 开发板支持，并以 GPL-3.0 协议公开。
>
> This project is a **hardware-adaptation fork** of the `esp源代码` (open-source firmware,
> version DIY_1_3_3) from [Dominocs/Project_Cymple](https://github.com/Dominocs/Project_Cymple).
> All copyright of the original code belongs to **Dominocs**. The author of this repository is an
> **unaffiliated third party** who merely added Seeed XIAO ESP32-S3 Sense board support, released
> under GPL-3.0.

---

## 主要修改 / Key Changes

与原始 `esp源代码` 相比，本仓库的修改包括：

| 修改 | 说明 |
|---|---|
| 🎯 **支持 XIAO ESP32-S3 Sense** | `camCfg.h` 按 `ARDUINO_XIAO_ESP32S3` 宏自动切换为 XIAO 官方摄像头扩展板引脚（OV2640/OV5640） |
| 🔌 **新增有线 (WIRE) 模式** | `platformio.ini` 新增 `xiao-esp32s3-wire` 环境（`-DCYMPLE_TRANSMIT_WIRE`）：图像经 USB 串口直传 CympleApp，免配网、低延迟 |
| 📡 **保留无线 (WIRELESS) 模式** | 默认环境 `xiao-esp32s3`：WiFi 推流，AP 配网（热点 `Cymple_Face` → `192.168.4.1`） |
| 👄 **默认设备位置 = 嘴部 (MOUTH)** | `esp32cam.cpp` 中 EEPROM 未初始化时默认 `FLAG_MOUTH_E`（原版默认左眼） |
| 🐛 **修复缺失 `config.h`** | 原工程引用但未提交该头文件，本仓库补齐（含 `CONFIG_TCP_MSS` 定义） |
| 🧹 **有线模式串口纯净** | WIRE 模式下抑制日志帧、跳过 WiFi 初始化，避免污染图像串口流 |

## 硬件要求 / Hardware

- **Seeed Studio XIAO ESP32-S3 Sense**（带官方 OV2640/OV5640 摄像头扩展板）
- USB 数据线（支持数据传输）
- 电脑端软件：**CympleApp**（Cymple 官方 PC 应用，嘴部追踪模块）

## 编译 / Build

需要 [PlatformIO](https://platformio.org/)（VSCode + PlatformIO IDE 扩展，或 CLI）。

```bash
# 无线版（WiFi 推流）
pio run -e xiao-esp32s3

# 有线版（USB 串口推流）
pio run -e xiao-esp32s3-wire

# 烧录（替换 COM5 为实际端口）
pio run -e xiao-esp32s3 -t upload -p COM5
pio run -e xiao-esp32s3-wire -t upload -p COM5
```

> 注：XIAO 有线版烧录如遇 `No serial data received`（高速 stub 失联），本仓库已在
> `xiao-esp32s3-wire` 环境配置 `upload_speed = 115200` + `upload_flags = --no-stub` 规避。

## 使用 / Usage

| 模式 | 首次使用 |
|---|---|
| **无线版** | 设备开机 → 连接热点 `Cymple_Face` → 浏览器打开 `192.168.4.1` 配置 WiFi → 打开 CympleApp |
| **有线版** | USB 插电脑 → 打开 CympleApp → App 自动识别 COM 口并接收图像（无需 WiFi） |

设备位置已默认设为**嘴部 (MOUTH)**，CympleApp 中应显示为 `CympleFace_Mouth` 并自动开始 ROI 标定。

若需改为左眼/右眼：修改 `src/esp32cam.cpp` 中默认值为 `FLAG_LEFT_EYE_E` / `FLAG_RIGHT_EYE_E`，
或通过串口下发 `POSITION_CFG`(type 6) 消息写入 EEPROM。

## 原版开源固件 / Original Source

- 原固件目录：`Dominocs/Project_Cymple` 仓库内 `esp源代码` 文件夹
- 原版版本号：`DIY_1_3_3`
- 在线刷写（原版官方硬件）：见 Cymple 项目文档

## License

[GPL-3.0](LICENSE) —— 保留原作者 Dominocs 版权声明，衍生作品同样以 GPL-3.0 公开。
