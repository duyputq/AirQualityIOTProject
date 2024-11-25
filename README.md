# Hệ thống giám sát chất lượng không khí

## I. Giới thiệu
Hệ thống giám sát chất lượng không khí là một giải pháp công nghệ nhằm đo lường, giám sát và phân tích mức độ ô nhiễm không khí. Hệ thống này sử dụng các cảm biến để theo dõi các thông số liên quan đến chất lượng không khí, như nồng độ bụi mịn (PM2.5, PM10), khí CO, và  nhiệt độ, độ ẩm.

## II. Linh kiện
Input Part:
- dht 11

<img src="https://static.cytron.io/image/cache/catalog/products/SN-MQ2-MOD/MQ2%20(2)-min-800x800.jpg" width="200" height="200" />


- mq2

<img src="https://vn.szks-kuongshun.com/Content/upload/201884835/201811131511263384442.jpg" width="200" height="200" />

- GP2Y1014AU

<img src="https://m.media-amazon.com/images/I/51SE8WYO3DL.jpg" width="200" height="200" />

Output part:
- DC Motor (Fan)

- 3 LED ứng với chất lượng không khí
- Máy lọc không khí

## III. Nguyên lý hoạt động
### 1. Biến ngôn ngữ

a. Nồng độ khí từ MQ2
- 0 - 50 ppm: thấp
- 51 - 100 ppm: bình thường
- trên 100 ppm: cao

b. Độ ẩm từ DHT11
- 0 - 30%: thâp
- 40% - 70%: bình thường
- trên 60%: cao

c. Nhiệt độ từ DHT11
- 0 - 15°C: thấp
- 15°C - 30°C: bình thường
- trên 30°C: cao

d. Mật độ bụi mịn từ GP2Y1014AU (PM2.5 hoặc PM10)
- 0 - 50 µg/m³: thấp
- 51 - 100 µg/m³: vừa
- trên 100 µg/m³: cao

### 2. Các quy tắc mờ

- Nếu nồng độ khí là cao và độ ẩm là ẩm và nhiệt độ là nóng và mật độ bụi - là cao, thì chất lượng không khí là xấu.
- Nếu nồng độ khí là cao và độ ẩm là vừa phải và nhiệt độ là bình thường và mật độ bụi là cao, thì chất lượng không khí là xấu.
- Nếu nồng độ khí là vừa phải và độ ẩm là vừa phải và nhiệt độ là bình thường và mật độ bụi là vừa phải, thì chất lượng không khí là bình thường.
- Nếu nồng độ khí là thấp và độ ẩm là khô và nhiệt độ là lạnh và mật độ bụi là thấp, thì chất lượng không khí là  tốt.
- Nếu nồng độ khí là thấp và độ ẩm là vừa phải và nhiệt độ là bình thường và mật độ bụi là thấp, thì chất lượng không khí  tốt.

### 3. Hợp thành mờ
Luật hợp thành đơn cấu trúc MISO, đưa ra kết luật CLKK

### 4. Điều khiển Acuator dựa trên CLKK
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


