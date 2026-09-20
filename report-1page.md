# Report 1 Page – FIT4012 Lab 2

## 1. Mục tiêu
Nắm vững nguyên lý và cài đặt hoàn chỉnh hai hệ mã hóa cổ điển đại diện cho kỹ thuật thay thế (Caesar Cipher) và kỹ thuật hoán vị (Rail Fence Cipher); rèn luyện kỹ năng xử lý chuỗi ký tự (chữ hoa, chữ thường, khoảng trắng), kiểm tra tính hợp lệ của đầu vào (input validation), đọc ghi file dữ liệu và đánh giá độ an toàn cơ bản của hệ mật.

## 2. Cách làm
- Hoàn thiện Caesar Cipher cho chữ thường, dấu cách và giải mã.
- Hoàn thiện Rail Fence Cipher cho giải mã, giữ dấu cách, kiểm tra đầu vào và đọc file.
- Chạy thử trên nhiều test case.

## 3. Kết quả chính
### 3.1 Caesar Cipher
| Input | Key | Ciphertext / Plaintext | Nhận xét |
|---|---:|---|---|
| I LOVE YOU | 3 | L ORYH BRX | Mã hóa chính xác chữ in hoa, giữ nguyên dấu cách. |
| hello world | 5 | mjqqt btwqi | Mã hóa chính xác chữ thường, khoảng cách không bị thay đổi. |
| LORYH BRX | 3 | I LOVE YOU | Giải mã dịch lùi 3 vị trí khôi phục hoàn hảo bản rõ ban đầu. |

### 3.2 Rail Fence Cipher
| Input | Rails | Ciphertext / Plaintext | Nhận xét |
|---|---:|---|---|
| I LOVE YOU | 2 | ILVEYOE OU | Zigzag 2 tầng: Hàng 0 lấy vị trí chẵn, Hàng 1 lấy vị trí lẻ. |
| I LOVE YOU | 4 | I EVUOLYO | Chu kỳ zigzag 2 x (4 - 1) = 6, ký tự phân bố đều 4 hàng. |
| IOEOLVYU | 2 | I LOVE YOU | Tách 2 nửa và ghép xen kẽ chính xác về bản rõ gốc. |

### 3.3 Input validation / file input
- Trường hợp đầu vào không hợp lệ:
+Khóa Caesar âm hoặc quá lớn: Tự động chuẩn hóa bằng công thức ((k % 26) + 26) % 26.
+Khóa Rail Fence với rails =< 1 hoặc >= độ dài chuỗi: Chương trình đưa ra cảnh báo lỗi hợp lệ (thông báo yêu cầu rails nằm trong khoảng hợp lệ và không thể tạo chu trình zigzag).
+Tệp rỗng: Báo lỗi và dừng chương trình an toàn, tránh lỗi truy cập bộ nhớ ngoài biên (out of range).
- Kết quả đọc từ `data/input.txt`:Chương trình mở tệp thành công, đọc toàn bộ nội dung dòng bản rõ mẫu, thực hiện lần lượt các chu trình mã hóa và giải mã với các bộ tham số khác nhau và ghi kết quả tương ứng ra terminal/file log mà không làm biến dạng dữ liệu gốc.

## 4. Kết luận
  Kiến thức thu nhận: Hiểu sâu sắc sự khác biệt giữa mật mã thay thế (thay đổi giá trị ký tự) và mật mã hoán vị (chỉ thay đổi vị trí ký tự). Thấy rõ cả hai phương pháp đều có không gian khóa rất nhỏ và không an toàn trước các cuộc tấn công vét cạn (brute-force) hoặc phân tích tần suất ký tự.
  Khó khăn lớn nhất: Việc khôi phục chuỗi ở thuật toán giải mã Rail Fence khi có sự xuất hiện của dấu cách, đặc biệt là logic đánh dấu chính xác tọa độ ma trận zigzag trước khi điền ký tự ciphertext.
  Yếu tố giúp hiểu bài rõ hơn: Việc vẽ ma trận zigzag ra giấy nháp trước khi code và viết bảng theo dõi vết chỉ số hàng (row, direction) giúp việc cài đặt thuật toán trở nên trực quan, hạn chế tối đa lỗi lệch chỉ mục (off-by-one).
