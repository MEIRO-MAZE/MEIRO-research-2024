# MEIRO-research-2024  
*Autonomous Hexapod SAR Robot – KRSRI 2024 Edition*  
(Standarized Documentation of Research – SDR)

---

## 📘 About the Research
- **Team / Division:** MEIRO  
- **Lead Developer:** Luhur Pambudi
- **Platform:** STM32F407VGT6 + NVIDIA Jetson Nano 4 GB  
- **Timeline:** 01 Aug 2023 – 30 May 2024  
- **Status:** ✅ v1.0 released  

---

## 📚 Background
The *Kontes Robot SAR Indonesia (KRSRI) 2024* challenges teams to build **autonomous legged robots** that navigate **post-earthquake terrain**:

- **Terrain:** cracked floors, 50 cm slopes, 2 cm steps, loose coral (3–5 cm), marble “mud” (15–17 mm).  
- **Victim Mission:** detect **5 real orange victims** vs **3 dummy decoys**, pick-up, and deliver to **paired Safety Zones** within **≤ 300 s**.  
- **Arena Size:** 360 cm × 120 cm (Region) / 360 cm × 240 cm (National).  

> Full rules: see [Buku Pedoman KRSRI 2024](./docs/Buku_Pedoman_KRSRI_2024.pdf).

---

## 🎯 Objectives
| General Objective | Specific Milestone |
|-------------------|--------------------|
| Finish all 5 victim rescues within 300 s. | • 5/5 victims rescued + reach Finish. |
| Improve terrain stability vs 2023. | • Zero foot sinkage on marble & coral. |
| Upgrade perception pipeline. | • ≥ 90 % victim-vs-dummy accuracy @ 10 FPS. |

---

## 📂 Repository Structure
```
📦 MEIRO-research-2024
├── 📂 MEIRO_Library          → STM32 gait & navigation (IK, PID, gait engine)
├── 📂 cmsis                  → STM32 CMSIS core & DSP
├── 📂 logs                   → Flash-backed run-time logs
├── 📂 syscalls               → Newlib system-call stubs
├── 📂 modules
│   └── 📂 victim-detection-v1 → Git submodule (Jetson Nano CV pipeline)
├── 📄 PHOENIX_LIB.rar         → Legacy helper library (compressed)
├── 📄 main.c                  → Main program entry
└── 📜 README.md               ← this file
```

---

## 🔬 Methodology
| Component | Description | Model / Version |
|-----------|-------------|-----------------|
| **MCU** | STM32F407VGT6 | STM32CubeMX 6.10 |
| **Actuators** | 18× Dynamixel AX-12A | Firmware v41 |
| **Distance Sensors** | • 3-pin **Laser PING** (side) <br> • **VL53L0X** ToF (front) | 2 cm – 4 m |
| **Vision** | Jetson Nano 4 GB + YOLOv5n (INT8) | JetPack 4.6.1 |
| **Power** | 3S 11.1 V 5000 mAh (actuators) <br> 2S 7.4 V 2200 mAh (logic) | - |
| **Comm.** | UART @ 115 200 b/s between STM32 ↔ Jetson | - |
| **IDE** | CooCox CoIDE | 2.0.6 |
| **Language** | C (ARM GCC) | 10.3.1 |

---

## 🧪 Experiments & Evaluation
| Scenario | Arena | Victims | Result |
|----------|-------|---------|--------|
| **Regional Qualifier 2024** | 360 × 120 cm | 5 real + 3 dummy | **3/5 victims rescued** <br> Furthest obstacle: **R9 (final step of the stair)** <br> **Best time to R9: 7 min 00 s (exceeds 5 min limit)** <br> **Status:** *Did not qualify for National round* |

---

## 📊 Key Improvements vs 2023
| Aspect | 2023 | 2024 |
|--------|------|------|
| Victim sensor | TCS3200 colour only | Jetson Nano + YOLOv5n |
| Distance sensor | 4-pin PING | 3-pin **Laser PING** side + **VL53L0X** front |
| CV latency | 320 ms | **95 ms** |
| Mission success | 4/5 victims | **3/5 victims, stuck at R10** |

---

## ✅ Next Steps (2025 Road-map)
- **Sensor R&D**  
  • Replace **Laser PING** with **VL53L0X as primary navigation rangefinder**.  
- **Actuator R&D**  
  • Evaluate **HiWonder LX-16A** smart servos for higher torque & feedback.  
- **Kinematics**  
  • **Revise inverse-kinematic equations** to correct positional inaccuracies.  
- **Gait & Balance**  
  • **Redesign foot trajectory & gait pattern** for smoother, more precise motion.  
- **Control**  
  • **Re-tune PID Controller** gains for improved stability on uneven terrain.

---

## 🕒 Revision History
| Version | Date | Description | Author |
|---------|------|-------------|--------|
| 1.0 | 2024-05-30 | KRSRI 2024 release | Luhur Pambudi |

---
