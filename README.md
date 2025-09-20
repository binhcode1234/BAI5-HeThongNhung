# STM32F103C8T6 – UART LED Control  

## 📌 Giới thiệu  
Dự án này sử dụng **STM32F103C8T6** (Blue Pill) để giao tiếp UART với máy tính qua module USB-UART (CP2102, CH340, FT232...).  

- Khi gửi chuỗi `"ON"` từ terminal → LED tại chân **PB12** sẽ bật.  
- Khi gửi chuỗi `"OFF"` → LED sẽ tắt.  
- Nếu gửi lệnh sai, STM32 sẽ phản hồi:
  
Ngoài ra, STM32 sẽ echo (phản hồi lại) từng ký tự nhập từ terminal và gửi thông báo trạng thái LED.  

---

## ⚙️ Yêu cầu phần cứng  
- STM32F103C8T6 (hoặc board Blue Pill).  
- Module USB-UART (CP2102, CH340, FT232...).  
- LED nối với **chân PB12** (có thể kèm điện trở hạn dòng 220Ω).  
- Dây jumper để kết nối.  

### Sơ đồ nối dây (UART1):  
| STM32 | USB-UART |
|-------|----------|
| PA9 (TX1)  | RXD |
| PA10 (RX1) | TXD |
| GND        | GND |

---

## 💻 Yêu cầu phần mềm  
- **Keil uVision** (hoặc STM32CubeIDE nếu muốn chuyển sang HAL).  
- **STM32 Standard Peripheral Library (SPL)**.  
- Một phần mềm terminal UART như:  
- PuTTY  
- TeraTerm  
- RealTerm  
- Arduino Serial Monitor  

---

## 🚀 Cách sử dụng  
1. Nạp chương trình vào STM32F103C8T6.  
2. Mở terminal (baudrate **9600**, 8N1).  
3. Gửi lệnh:  
 - `ON` → LED bật  
 - `OFF` → LED tắt  
 - Chuỗi khác → thông báo lỗi  
 
