# Hệ thống giám sát chất lượng không khí

## I. Giới thiệu
Hệ thống giám sát chất lượng không khí là một giải pháp công nghệ nhằm đo lường, giám sát và phân tích mức độ ô nhiễm không khí. Hệ thống này sử dụng các cảm biến để theo dõi các thông số liên quan đến chất lượng không khí, như nồng độ bụi mịn (PM2.5, PM10), khí CO, và  nhiệt độ, độ ẩm.

Chỉ số Chất lượng Không khí (AQI) được phát triển bởi Cơ quan Bảo vệ Môi trường Hoa Kỳ (EPA) vào những năm 1970. AQI được thiết kế để giúp người dân dễ dàng hiểu và đánh giá mức độ ô nhiễm không khí trong khu vực của họ.

## II. Linh kiện
Input Part:

- mq2

<img src="https://static.cytron.io/image/cache/catalog/products/SN-MQ2-MOD/MQ2%20(2)-min-800x800.jpg" width="200" height="200" />

- GP2Y1014AU

<img src="https://m.media-amazon.com/images/I/51SE8WYO3DL.jpg" width="200" height="200" />

- dht 11

<img src="https://vn.szks-kuongshun.com/Content/upload/201884835/201811131511263384442.jpg" width="200" height="200" />



Output part:
- DC Motor (Cooling Fan)
- 3 LED ứng với chất lượng không khí
- Máy lọc không khí

## III. Nguyên lý hoạt động

### Sơ đồ hệ thống

![model](https://github.com/user-attachments/assets/84d56c6a-5ff0-4096-9e03-00bb6a224229)


### 1. Biến ngôn ngữ

a. Nồng độ khí CO từ MQ2
- 0 - 4.4 ppm: tốt -6.5
- 4.5 - 12.5 ppm: bình thường
- 11 - 15.5 ppm: xấu 10-23

b. Mật độ bụi mịn PM2.5 từ GP2Y1014AU (PM2.5 hoặc PM10)
- 0 - 11.9 µg/m³: tốt 18
- 12 - 35.5 µg/m³: bình thường 
- 35.5 - 55.5 µg/m³: xấu - 30-70

c. Ngoài ra còn nhiệt độ và độ ẩm ảnh hưởng gián tiếp 

### 2. Kết quả đầu ra
Output là chất lượng không khí theo chỉ số AQI

Chỉ số AQI:
- 0 - 49: tốt
- 50 - 99: bình thường
- 100 - 150: xấu

### 3. Nguyên tắc mờ
Nguyên tắc mờ dựa trên luật Max-Min đề xuất bởi Zadeh

### 4. Luật mờ
Luật mờ được xây dựng dựa trên phép giao theo luật Max, do đó ta được các fuzzy rules như sau:
- Nếu CO là tốt và PM2.5 là tốt thì AQI là tốt.
- Nếu CO là tốt và PM2.5 là bình thường thì AQI là bình thường.
- Nếu CO là tốt và PM2.5 là xấu thì AQI là xấu.
- Nếu CO là bình thường và PM2.5 là tốt thì AQI là bình thường.
- Nếu CO là bình thường và PM2.5 là bình thường thì AQI là bình thường.
- Nếu CO là bình thường và PM2.5 là xấu thì AQI là xấu.
- Nếu CO là xấu và PM2.5 là tốt thì AQI là xấu.
- Nếu CO là xấu và PM2.5 là bình thường thì AQI là xấu.
- Nếu CO là xấu và PM2.5 là xấu thì AQI là xấu.

### 5. Điều khiển Acuator dựa trên CLKK
- Hiển thị
Sự dụng 3 đèn màu LED để biểu thị chất lượng Ko khí
Số liệu chất lượng không khí theo gian thực được theo dõi trên app Blynk

- Actuator:
Bật quạt nếu CLKK xấu, bật cho đến khi các khí độc bị thổi đi.
Còi Buzzer để cảnh báo chất lượng ko khí xấu.

## IV. Mô hình thực tế
![fan-control](https://github.com/user-attachments/assets/c8246146-a865-4965-848c-4f46e3c95f59)

![devices](https://github.com/user-attachments/assets/eb823e1a-11c9-4831-a8c4-945aa29b8768)

![stastics](https://github.com/user-attachments/assets/8508a6cf-2278-43a5-a2fc-8f08c5cc8efa)


