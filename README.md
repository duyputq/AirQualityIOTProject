# Hệ thống giám sát chất lượng không khí

## I. Giới thiệu
Chất lượng không khí ở Hà Nội đang trở thành một vấn đề báo động đối với công đồng và các nhà quản lý. Theo các báo cáo gần đây, Hà Nội thường xuyên nằm trong danh sách các thành phố có chất lượng không khí kém nhất thế giới

Hệ thống giám sát chất lượng không khí là một giải pháp nhằm đo lường, giám sát và phân tích mức độ ô nhiễm không khí. Hệ thống này sử dụng các cảm biến để theo dõi các thông số liên quan đến chất lượng không khí, như nồng độ bụi mịn (PM2.5, PM10), khí CO, và  nhiệt độ, độ ẩm để tính toán AQI

Chỉ số Chất lượng Không khí (AQI) được phát triển bởi Cơ quan Bảo vệ Môi trường Hoa Kỳ (EPA) vào những năm 1970. AQI được thiết kế để giúp người dân dễ dàng hiểu và đánh giá mức độ ô nhiễm không khí trong khu vực của họ.

![img](https://github.com/user-attachments/assets/1e9deaec-3fbe-4df2-b41c-586827650763)

## II. Các Linh kiện sử dụng

**Input Parts: để đo được các thống số, ta cần các các biển không khí**

- MQ2: Nồng độ khí CO

<img src="https://static.cytron.io/image/cache/catalog/products/SN-MQ2-MOD/MQ2%20(2)-min-800x800.jpg" width="200" height="200" />

- GP2Y1014AU: Mật độ bụi mịn PM2.5

<img src="https://m.media-amazon.com/images/I/51SE8WYO3DL.jpg" width="200" height="200" />

- DHT11: Nhiệt độ và độ ẩm

<img src="https://vn.szks-kuongshun.com/Content/upload/201884835/201811131511263384442.jpg" width="200" height="200" />


**Output parts: Các acutators và LED**

- DC Motor (Cooling Fan)
<img src="https://github.com/user-attachments/assets/20139474-8acc-4d1a-ba8b-d06f1f171ca9" width="200" height="200" />


- 3 LED ứng với chất lượng không khí (dựa trên AQI)
<img src="https://github.com/user-attachments/assets/b92badb0-c146-4010-a73d-d0e2e57c9ac6" width="200" height="200" />

- Dữ liệu thu thập được đẩy lên app Blynk.

## III. Nguyên lý hoạt động

### 1.Mô hình hệ thống

![model](https://github.com/user-attachments/assets/b1384394-4ace-46dc-99b6-f89e2c7bff14)

Dữ liệu từ các cảm biến GP2Y1010AU0F, DHT11, MQ2 sau khi được thu thập sẽ được gửi đến vi điều khiển Arduino UNO R3. Tiếp theo, Arduino UNO R3 sẽ truyền dữ liệu này tới vi điều khiển ESP8266 thông qua giao tiếp UART. 

ESP8266 đảm nhiệm việc chuyển dữ liệu lên nền tảng Blynk bằng cách sử dụng giao thức wifi và giao thức ứng dụng HTTP. Tại đây, người dùng có thể theo dõi thông tin trực quan và điều khiển thiết bị dễ dàng.

### 2.Thiết lập Fuzzy Logic cho hệ thống

#### 2.1. Biến ngôn ngữ

a. Nồng độ khí CO từ MQ2
- 0 − 6.5 ppm: Tốt
- 4.5 − 12.5 ppm: Bình thường
- 10 − 15.5 ppm: Xấu
- \>15.5 ppm: Xấu

b. Mật độ bụi mịn PM2.5 từ GP2Y1014AU (PM2.5 hoặc PM10)
- 0 − 18 μg/m3: Tốt
- 12 − 35.5 μg/m3: Bình thường
- 30 − 55.5 μg/m3: Xấu
- \> 55.5 μg/m3: Xấu

c. Ngoài ra còn nhiệt độ và độ ẩm ảnh hưởng gián tiếp 

#### 2.2. Kết quả đầu ra
Output là chất lượng không khí theo chỉ số AQI

Chỉ số AQI:
- 0 − 50: Tốt
- 50 − 100: Bình thường
- 100 − 150: Xấu

#### 2.3. Nguyên tắc mờ
Nguyên tắc mờ dựa trên luật mờ Max-Min đề xuất bởi Zadeh
![image](https://github.com/user-attachments/assets/f23a7182-3ac9-4c46-bc84-1abc70718c83)

#### 2.4. Các luật mờ (fuzzy rules) của hệ thống
Luật mờ được xây dựng dựa trên phép giao theo luật Max-min, do đó ta được các luật như sau:
- Nếu CO là tốt và PM2.5 là tốt thì AQI là tốt.
- Nếu CO là tốt và PM2.5 là bình thường thì AQI là bình thường.
- Nếu CO là tốt và PM2.5 là xấu thì AQI là xấu.
- Nếu CO là bình thường và PM2.5 là tốt thì AQI là bình thường.
- Nếu CO là bình thường và PM2.5 là bình thường thì AQI là bình thường.
- Nếu CO là bình thường và PM2.5 là xấu thì AQI là xấu.
- Nếu CO là xấu và PM2.5 là tốt thì AQI là xấu.
- Nếu CO là xấu và PM2.5 là bình thường thì AQI là xấu.
- Nếu CO là xấu và PM2.5 là xấu thì AQI là xấu.

Kết quả sau khi thiết lập trên Matlab:
![fuzzy-logic](https://github.com/user-attachments/assets/827a1ac0-90cb-4deb-b6f1-cc218a17d565)


### 3. Điều khiển Acuator dựa trên CLKK
- Hiển thị: Sự dụng 3 đèn màu LED để biểu thị chất lượng Ko khí
Số liệu chất lượng không khí theo gian thực được theo dõi trên app Blynk

- Actuator: Bật quạt thông gió (cooling fan) nếu CLKK xấu, bật cho đến khi các khí độc bị thổi đi. Hoặc người dùng có thể tự bật tắt theo ý muốn thông qua app Blynk

- Dữ liệu các cảm biến quan sát thông qua Blynk (web/app)

## IV. Kết quả:
Mô hình hoàn thiện hệ thống:
![final](https://github.com/user-attachments/assets/d30e6542-7b00-4ac8-bc03-d99fd8fa6b84)

Chất lượng không khí khi ở mức bình thường (đèn xanh):
![den-xanh](https://github.com/user-attachments/assets/29e42245-9f27-4672-86c1-626f8042ea50)

Chất lượng không khí khi phát hiện khí độc (AQI = 131). Hiện thị trên IDE của ESP8266:
![chup-man-hinh](https://github.com/user-attachments/assets/44ee7243-0973-4e5d-91f8-81927abaf178)

Chất lượng không khí khi phát hiện khí độc (đèn đỏ):
![den-do](https://github.com/user-attachments/assets/3983bd50-224e-44e1-ad01-d86eef85e147)

Hình ảnh khi hệ thống kết nối với app Blynk (web) (khi mật độ bụi mịn cao):
![blynk-xau](https://github.com/user-attachments/assets/ff7e7837-6edf-4bec-9144-bb2a96516d64)

Hình ảnh CLKK bình thường trên app Blynk (điện thoại):
<div style="text-align:center;">
    <img src="https://github.com/user-attachments/assets/317a120e-289f-4049-ab3e-514749aa28a4" alt="blynk-tot" width="40%">
</div>

## V. Kết luận

Dự án giám sát chất lượng không khí ứng dụng logic mờ đã đạt mục tiêu: cung cấp dữ liệu chính xác, hiển thị trên Blynk.io và hỗ trợ điều khiển từ xa. Hệ thống sử dụng các cảm biến như MQ2, DHT11, GP2Y1010AU0F kết hợp với ESP8266 và Arduino UNO R3, đảm bảo ổn định và chính xác trong thu thập và truyền tải dữ liệu. Các cảm biến, motor và đèn LED hoạt động nhanh chóng, đồng bộ.

Hệ thống có tiềm năng mở rộng, bao gồm tích hợp thêm cảm biến O3, SO2, áp dụng AI để phân tích và dự đoán chất lượng không khí, cải thiện giao diện với biểu đồ xu hướng và cảnh báo tự động. Dự kiến sẽ tăng số lượng cảm biến lên 8 để đánh giá toàn diện chỉ số AQI. Cảm biến ngoài trời và thiết bị công suất cao cũng sẽ được nghiên cứu. Dữ liệu cảm biến sẽ lưu trữ cục bộ, giúp theo dõi và huấn luyện AI dự đoán xu hướng ô nhiễm.



