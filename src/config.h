#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_

/* ============================================================
 * CympleEye 工程公共配置
 * 说明：本文件由仓库缺失文件补齐（camCfg.h / esp32cam.cpp /
 *       serialMsg.h 均 #include "config.h"）。
 * ============================================================ */

/* lwIP TCP MSS：用于计算图像分片最大长度 (esp32cam.cpp)。
 * 若平台 (sdkconfig) 已定义则沿用平台值；否则取 TCP 默认 MSS 1460。 */
#ifndef CONFIG_TCP_MSS
#define CONFIG_TCP_MSS 1460
#endif

#endif /* _PROJECT_CONFIG_H_ */
